#include "config.h"
#include "backend.h"
#if defined(LIBTCC_FOUND)
#include "compiler/backend.h"
#endif
#include "interpreter/backend.h"

#include <stdlib.h>
#include <assert.h>

struct dbfi_basic_backend
{
    dbfi_backend_type_t type_;
};

dbfi_backend_t dbfi_backend_init(dbfi_backend_type_t type)
{
    static struct dbfi_basic_backend dummy = { DBFI_BACKEND_DUMMY };
    
    switch (type)
    {
    default:                       return &dummy;                          break;
#if defined(LIBTCC_FOUND)
    case DBFI_BACKEND_COMPILER:    return dbfi_compiler_backend_init();    break;
#endif /* LIBTCC_FOUND */
    case DBFI_BACKEND_INTERPRETER: return dbfi_interpreter_backend_init(); break;
    };
}

void dbfi_backend_release(dbfi_backend_t _this)
{
    struct dbfi_basic_backend * THIS = _this;
    
    switch (THIS->type_)
    {
    default: /* do nothing */ break;
    case DBFI_BACKEND_COMPILER:
        dbfi_compiler_backend_release(_this);
        /* fall through */
    case DBFI_BACKEND_INTERPRETER:
        free(_this);
    }
}

void dbfi_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt)
{
    struct dbfi_basic_backend * THIS = _this;
    
    assert(_this);
    
    switch (THIS->type_)
    {
    default:                       /* the dummy does nothing */                                    break;
#if defined(LIBTCC_FOUND)
    case DBFI_BACKEND_COMPILER:    dbfi_compiler_backend_process_parser_tree(_this, pt);    break;
#endif /* LIBTCC_FOUND */
    case DBFI_BACKEND_INTERPRETER: dbfi_interpreter_backend_process_parser_tree(_this, pt); break;
    }
}

void dbfi_backend_finalize(dbfi_backend_t _this, char const * filename)
{
    struct dbfi_basic_backend * THIS = _this;
    
    assert(_this);
    
    if (THIS->type_ == DBFI_BACKEND_COMPILER)
        dbfi_compiler_backend_finalize(_this, filename);
}
