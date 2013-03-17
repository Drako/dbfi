#include "backend.h"
#include "compiler/backend.h"
#include "interpreter/backend.h"

#include <stdlib.h>
#include <assert.h>

struct dbfi_basic_backend
{
    dbfi_backend_type_t type_;
};

dbfi_backend_t dbfi_backend_init(dbfi_backend_type_t type)
{
    static struct dbfi_backend dummy = { DBFI_BACKEND_DUMMY };
    
    switch (type)
    {
    default:                       return &dummy;                          break;
    case DBFI_BACKEND_COMPILER:    return dbfi_compiler_backend_init();    break;
    case DBFI_BACKEND_INTERPRETER: return dbfi_interpreter_backend_init(); break;
    };
}

void dbfi_backend_release(dbfi_backend_t _this)
{
    /* the dummy must not be free'd */
    if (_this != dbfi_backend_init(DBFI_BACKEND_DUMMY))
    {
        free(_this);
    }
}

void dbfi_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt)
{
    struct dbfi_basic_backend * THIS = (struct dbfi_basic_backend *)_this;
    
    assert(_this);
    
    switch (THIS->type_)
    {
    default:                       /* the dummy does nothing */                                    break;
    case DBFI_BACKEND_COMPILER:    return dbfi_compiler_backend_process_parser_tree(_this, pt);    break;
    case DBFI_BACKEND_INTERPRETER: return dbfi_interpreter_backend_process_parser_tree(_this, pt); break;
    }
}
