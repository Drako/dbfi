#if !defined(DBFI_PARSER_H)
#define DBFI_PARSER_H

#include "lexer.h"
#include "parser_tree.h"

struct dbfi_parser;
typedef struct dbfi_parser * dbfi_parser_t;

dbfi_parser_t dbfi_parser_init(void);
void dbfi_parser_release(dbfi_parser_t _this);

dbfi_parser_tree_t dbfi_parser_generate_tree(dbfi_parser_t _this, dbfi_lexer_t lexer);

#endif /* DBFI_PARSER_H */
