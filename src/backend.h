#if !defined(DBFI_BACKEND_H)
#define DBFI_BACKEND_H

#include "parser_tree.h"

typedef void * dbfi_backend_t;

typedef enum dbfi_backend_type
{
    DBFI_BACKEND_INTERPRETER = 0,
    DBFI_BACKEND_COMPILER,
    
    DBFI_BACKEND_DUMMY /* does nothing */
} dbfi_backend_type_t;

dbfi_backend_t dbfi_backend_init(dbfi_backend_type_t type);
void dbfi_backend_release(dbfi_backend_t _this);

void dbfi_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt);
void dbfi_backend_finalize(dbfi_backend_t _this, char const * filename);

#endif /* DBFI_BACKEND_H */
