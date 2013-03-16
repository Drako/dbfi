#if !defined(DBFI_PARSER_TREE)
#define DBFI_PARSER_TREE

#include "token.h"

typedef enum dbfi_node_type
{
    DBFI_NODE_COMMAND = 0,
    DBFI_NODE_SCOPE,
} dbfi_node_type_t;

typedef struct dbfi_node
{
    dbfi_node_type_t type_;
    struct dbfi_node * next_;
    
    union
    {
        /* type_ == DBFI_NODE_COMMAND */
        dbfi_token_type_t command_;
        
        /* type_ == DBFI_NODE_SCOPE */
        struct dbfi_node * scope_;
    };
} dbfi_node_t;

#endif /* DBFI_PARSER_TREE */
