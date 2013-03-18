#if !defined(DBFI_COMPILER_BACKEND_H)
#define DBFI_COMPILER_BACKEND_H

#include "../backend.h"

dbfi_backend_t dbfi_compiler_backend_init(void);
void dbfi_compiler_backend_release(dbfi_backend_t _this);
void dbfi_compiler_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt);
void dbfi_compiler_backend_handle_command(dbfi_backend_t _this, dbfi_token_type_t command);
void dbfi_compiler_backend_finalize(dbfi_backend_t _this, char const * filename);

#endif /* DBFI_COMPILER_BACKEND_H */
