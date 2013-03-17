#include "config.h"
#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void dbfi_help(char * app)
{
    printf(
        "Usage: %s {options} [filename]\n\n"
        "Available options:\n"
        "  --help,-?               - Show this help message\n"
        "  --version,-v            - Show version information\n"
        "  --compile,-c            - Compile to native program instead of interpreting\n"
        "  --output,-o  [filename] - Alternative output filename for --compile\n"
    , app);
}

void dbfi_version(void)
{
    printf(
        "Dragon BrainFuck Interpreter (dbfi) Version " DBFI_VERSION "\n"
        "Copyright (C) 2013, Felix Bytow <felix.bytow@googlemail.com>\n\n"
        "Git-Hash:   " DBFI_GIT_HASH "\n"
        "Build-Type: " DBFI_BUILD_TYPE "\n"
    );
}

char const * dbfi_next_arg(char *** current_arg, char ** end)
{
    if (*current_arg + 1 == end)
    {
        fprintf(stderr, "Error: \"--output,-o\" requires a filename as a parameter.\n");
        exit(1);
    }
    
    ++(*current_arg);
    return (**current_arg);
}

int dbfi_main(char * filename, int compile, char * output)
{
    dbfi_lexer_t lexer = dbfi_lexer_init(filename);
    dbfi_parser_t parser = dbfi_parser_init();
    dbfi_parser_tree_t pt;
    
    assert(lexer);
    assert(parser);
    
    pt = dbfi_parser_generate_tree(parser, lexer);
    
    dbfi_parser_release(parser);
    dbfi_lexer_release(lexer);
    
    assert(pt);
    return 0;
}

int main(int argc, char ** argv)
{
    char ** arg;
    int compile = 0;
#if defined(__linux__)
    /* on Linux we default to stdin if no filename is given */
    char filename[1024] = "/dev/stdin";
#else
    /* on Windows the filename is mandatory */
    char filename[1024] = "";
#endif /* __linux__ */
    char output[1024] = "";
    
    for (arg = argv + 1; arg != argv + argc; ++arg)
    {
        /* show help message */
        if ((!strcmp(*arg, "--help")) || (!strcmp(*arg, "-?")))
        {
            dbfi_help(argv[0]);
            return 0;
        }
        
        /* show version information */
        else if ((!strcmp(*arg, "--version")) || (!strcmp(*arg, "-v")))
        {
            dbfi_version();
            return 0;
        }
        
        /* switch to compiler mode */
        else if ((!strcmp(*arg, "--compile")) || (!strcmp(*arg, "-c")))
        {
            compile = 1;
        }
        
        /* set output filename for compiler mode */
        else if ((!strcmp(*arg, "--output")) || (!strcmp(*arg, "-o")))
        {
            strncpy(output, dbfi_next_arg(&arg, argv + argc), sizeof(output));
        }
        
        /* other things starting with '-' are invalid options */
        else if ((*arg)[0] == '-')
        {
            fprintf(stderr, "Error: Unknown command line option. See --help for available options.\n");
            return 1;
        }
        
        /* the source filename */
        else
        {
            strncpy(filename, *arg, sizeof(filename));
        }
    }
    
    if (filename[0] == '\0')
    {
        fprintf(stderr, "Error: No filename of a brainfuck script has been given.\n");
        return 1;
    }
    
    return dbfi_main(filename, compile, output);
}
