#if !defined(DBFI_INTERPRETER_BACKEND_H)
#define DBFI_INTERPRETER_BACKEND_H

#include "../backend.h"

dbfi_backend_t dbfi_interpreter_backend_init(void);
void dbfi_interpreter_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt);
void dbfi_interpreter_backend_handle_command(dbfi_backend_t _this, dbfi_token_type_t command);

#endif /* DBFI_INTERPRETER_BACKEND_H */
