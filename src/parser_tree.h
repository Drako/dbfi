#if !defined(DBFI_PARSER_TREE)
#define DBFI_PARSER_TREE

#include "token.h"

typedef enum dbfi_node_type
{
    DBFI_NODE_COMMAND = 0,
    DBFI_NODE_SCOPE,
    
    DBFI_NODE_NONE
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

typedef struct dbfi_node * dbfi_parser_tree_t;

dbfi_parser_tree_t dbfi_parser_tree_init(void);
void dbfi_parser_tree_release(dbfi_parser_tree_t this);
void dbfi_parser_tree_add_command(dbfi_parser_tree_t this, dbfi_token_type_t command);
dbfi_parser_tree_t dbfi_parser_tree_add_scope(dbfi_parser_tree_t this);

#endif /* DBFI_PARSER_TREE */
