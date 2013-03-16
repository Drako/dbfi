#if !defined(DBFI_LEXER_H)
#define DBFI_LEXER_H

#include "token.h"

struct dbfi_lexer;
typedef struct dbfi_lexer * dbfi_lexer_t;

dbfi_lexer_t dbfi_lexer_init(char const * filename);
void dbfi_lexer_release(dbfi_lexer_t this);

dbfi_token_info_t * dbfi_lexer_next_token(dbfi_lexer_t this);

#endif /* DBFI_LEXER_H */
