#if !defined(DBFI_LEXER_H)
#define DBFI_LEXER_H

#include "token.h"

struct dbfi_lexer;

struct dbfi_lexer * dbfi_lexer_init(char const * filename);
void dbfi_lexer_release(struct dbfi_lexer * this);

dbfi_token_info_t * dbfi_lexer_next_token(struct dbfi_lexer * this);

#endif /* DBFI_LEXER_H */
