#include "backend.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <libtcc.h>

struct dbfi_compiler_backend
{
    dbfi_backend_type_t type_;
    
    /* the source code memory */
    char * code_;
    uint32_t size_; /* buffer size */
    uint32_t used_;
};

/* private functions */

int dbfi_compiler_backend_max(int x, int y)
{
    return (x > y ? x : y);
}

void dbfi_compiler_backend_add_code(dbfi_backend_t _this, char const * code)
{
    struct dbfi_compiler_backend * THIS = _this;
    int length = strlen(code);
    
    assert(_this);
    
    /* memory not yet allocated (first code chunk) */
    if (!(THIS->code_))
    {
        THIS->size_ = dbfi_compiler_backend_max(1024, length + 1);
        THIS->code_ = malloc(THIS->size_);
        THIS->used_ = 0;
    }
    /* buffer size reached... reallocate */
    else if (THIS->used_ + length > THIS->size_)
    {
        THIS->size_ = dbfi_compiler_backend_max(THIS->size_ * 2, THIS->used_ + length + 1);
        THIS->code_ = realloc(THIS->code_, THIS->size_);
    }
    
    assert(THIS->code_);
    
    /* copy code and increment used */
    memcpy(THIS->code_ + THIS->used_, code, length);
    THIS->used_ += length;
    THIS->code_[THIS->used_] = '\0';
}

/* public functions */

dbfi_backend_t dbfi_compiler_backend_init(void)
{
    struct dbfi_compiler_backend * backend = malloc(sizeof(struct dbfi_compiler_backend));
    if (!backend)
        return NULL;
    
    backend->type_ = DBFI_BACKEND_COMPILER;
    backend->code_ = NULL;
    backend->size_ = backend->used_ = 0;
    
    /* the runtime environment */
    dbfi_compiler_backend_add_code(
        backend,
        "#include <stdio.h>\n"
        "#include <stdint.h>\n"
        "#include <string.h>\n"
#if defined(_WIN32)
        "#include <conio.h>\n"
#elif defined(__linux__)
        "#include <termios.h>\n"
#endif
        "\n"
        "int memory[65536];\n"
        "uint16_t memptr;\n"
        "\n"
        "int dbfi_getch(void)\n"
        "{\n"
#if defined(_WIN32)
        "\treturn _getch();\n"
#elif defined(__linux__)
        "\tstruct termios old, cur;\n"
        "\tint result;\n"
        "\t\n"
        "\ttcgetattr(0, &old);\n"
        "\tcur = old;\n"
        "\tcur.c_lflag &= ~ICANON;\n"
        "\tcur.c_lflag &= ~ECHO;\n"
        "\ttcsetattr(0, TCSANOW, &cur);\n"
        "\t\n"
        "\tresult = getchar();\n"
        "\t\n"
        "\ttcsetattr(0, TCSANOW, &old);\n"
        "\t\n"
        "\treturn result;\n"
#endif
        "}\n"
        "\n"
        "int main(void)\n"
        "{\n"
        "\tmemset(memory, 0, sizeof(memory));\n"
        "\tmemptr = 0;\n"
        "\n"
    );
    
    return backend;
}

void dbfi_compiler_backend_release(dbfi_backend_t _this)
{
    struct dbfi_compiler_backend * THIS = _this;
    if (THIS)
        free(THIS->code_);
}

void dbfi_compiler_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt)
{
    dbfi_node_t * node = pt;
    struct dbfi_compiler_backend * THIS = _this;
    
    assert(_this);
    
    while (node)
    {
        switch (node->type_)
        {
        default: /* do nothing */ break;
        case DBFI_NODE_SCOPE:
            {
                dbfi_compiler_backend_add_code(
                    _this,
                    "\twhile(memory[memptr])\n"
                    "\t{\n"
                );
                dbfi_compiler_backend_process_parser_tree(_this, node->scope_);
                dbfi_compiler_backend_add_code(
                    _this,
                    "\t}\n"
                );
            } break;
        case DBFI_NODE_COMMAND:
            {
                dbfi_compiler_backend_handle_command(_this, node->command_);
            } break;
        }
        
        node = node->next_;
    }
}

void dbfi_compiler_backend_handle_command(dbfi_backend_t _this, dbfi_token_type_t command)
{
    /* assert(_this); */
    
    switch (command)
    {
    default: /* other tokens than those below may not appear hear */ break;
    case DBFI_TOKEN_PLUS:
        {
            dbfi_compiler_backend_add_code(_this, "\t++(memory[memptr]);\n");
        } break;
    case DBFI_TOKEN_MINUS:
        {
            dbfi_compiler_backend_add_code(_this, "\t--(memory[memptr]);\n");
        } break;
    case DBFI_TOKEN_LT:
        {
            dbfi_compiler_backend_add_code(_this, "\t--memptr;\n");
        } break;
    case DBFI_TOKEN_GT:
        {
            dbfi_compiler_backend_add_code(_this, "\t++memptr;\n");
        } break;
    case DBFI_TOKEN_DOT:
        {
            dbfi_compiler_backend_add_code(_this, "\tputchar((char)(memory[memptr]));\n");
        } break;
    case DBFI_TOKEN_COMMA:
        {
            dbfi_compiler_backend_add_code(_this, "\tmemory[memptr] = dbfi_getch();\n");
        } break;
    }
}

void dbfi_compiler_backend_finalize(dbfi_backend_t _this, char const * filename)
{
    struct dbfi_compiler_backend * THIS = _this;
    TCCState * tcc = tcc_new();
    
    assert(_this);
    assert(tcc);
    
    dbfi_compiler_backend_add_code(
        _this,
        "\t\n"
        "\treturn 0;\n"
        "}\n"
    );
    
    tcc_set_output_type(tcc, TCC_OUTPUT_EXE);
    
    if (tcc_compile_string(tcc, THIS->code_) != 0)
    {
        /* error */
        fprintf(stderr, "Error: Compilation failed.\n");
        abort();
    }
    
    tcc_output_file(tcc, filename);
    
    tcc_delete(tcc);
}
