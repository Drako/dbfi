#if !defined(DBFI_TOKEN_H)
#define DBFI_TOKEN_H

#include <stdint.h>

typedef enum dbfi_token_type
{
    DBFI_TOKEN_PLUS = 0, /* + */
    DBFI_TOKEN_MINUS,    /* - */
    DBFI_TOKEN_GT,       /* > */
    DBFI_TOKEN_LT,       /* < */
    DBFI_TOKEN_BLEFT,    /* [ */
    DBFI_TOKEN_BRIGHT,   /* ] */
    DBFI_TOKEN_DOT,      /* . */
    DBFI_TOKEN_COMMA,    /* , */
    
    DBFI_TOKEN_EOF
} dbfi_token_type_t;

typedef struct dbfi_token_info
{
    dbfi_token_type_t type_;
    uint32_t row_;
    uint32_t column_;
    char const * filename_;
} dbfi_token_info_t;

#endif /* DBFI_TOKEN_H */
