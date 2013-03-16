#include "parser_tree.h"

#include <stdio.h>
#include <stdlib.h>

dbfi_parser_tree_t dbfi_parser_tree_init(void)
{
    dbfi_parser_tree_t tree = malloc(sizeof(dbfi_node_t));
    tree->type_ = DBFI_NODE_NONE;
    tree->next_ = NULL;
}

void dbfi_parser_tree_release(dbfi_parser_tree_t this)
{
    if (this)
    {
        dbfi_parser_tree_release(this->next_);
        
        if (this->type_ == DBFI_NODE_SCOPE)
            dbfi_parser_tree_release(this->scope_);
        
        free(this);
    }
}

void dbfi_parser_tree_add_command(dbfi_parser_tree_t this, dbfi_token_type_t command)
{
    if (this)
    {
        while (this->next_)
            this = this->next_;
        
        /* if the tree is not empty */
        if (this->command_ != DBFI_NODE_NONE)
        {
            this->next_ = malloc(sizeof(dbfi_node_t));
            this = this->next_;
            
            /* malloc failed */
            if (!this)
            {
                fprintf(stderr, "Error: Failed to allocate space for new parser tree node.\n");
                abort();
            }
        }
        
        this->type_ = DBFI_NODE_COMMAND;
        this->next_ = NULL;
        this->command_ = command;
    }
}

dbfi_parser_tree_t dbfi_parser_tree_add_scope(dbfi_parser_tree_t this)
{
    if (this)
    {
        while (this->next_)
            this = this->next_;
        
        /* if the tree is not empty */
        if (this->command_ != DBFI_NODE_NONE)
        {
            this->next_ = malloc(sizeof(dbfi_node_t));
            this = this->next_;
            
            /* malloc failed */
            if (!this)
            {
                fprintf(stderr, "Error: Failed to allocate space for new parser tree node.\n");
                abort();
            }
        }
        
        this->type_ = DBFI_NODE_SCOPE;
        this->next_ = NULL;
        this->scope_ = dbfi_parser_tree_init();
        
        /* if the subtree could not be allocated also release the parent node */
        if (!(this->scope_))
        {
            free(this);
            return NULL;
        }
        
        return (this->scope_);
    }
    
    return NULL;
}
