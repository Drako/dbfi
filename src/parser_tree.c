#include "parser_tree.h"

#include <stdio.h>
#include <stdlib.h>

dbfi_parser_tree_t dbfi_parser_tree_init(void)
{
    dbfi_parser_tree_t tree = malloc(sizeof(dbfi_node_t));
    tree->type_ = DBFI_NODE_NONE;
    tree->next_ = NULL;
    
    return tree;
}

void dbfi_parser_tree_release(dbfi_parser_tree_t _this)
{
    if (_this)
    {
        dbfi_parser_tree_release(_this->next_);
        
        if (_this->type_ == DBFI_NODE_SCOPE)
            dbfi_parser_tree_release(_this->scope_);
        
        free(_this);
    }
}

void dbfi_parser_tree_add_command(dbfi_parser_tree_t _this, dbfi_token_type_t command)
{
    if (_this)
    {
        while (_this->next_)
            _this = _this->next_;
        
        /* if the tree is not empty */
        if (_this->type_ != DBFI_NODE_NONE)
        {
            _this->next_ = malloc(sizeof(dbfi_node_t));
            _this = _this->next_;
            
            /* malloc failed */
            if (!_this)
            {
                fprintf(stderr, "Error: Failed to allocate space for new parser tree node.\n");
                abort();
            }
        }
        
        _this->type_ = DBFI_NODE_COMMAND;
        _this->next_ = NULL;
        _this->command_ = command;
    }
}

dbfi_parser_tree_t dbfi_parser_tree_add_scope(dbfi_parser_tree_t _this)
{
    if (_this)
    {
        while (_this->next_)
            _this = _this->next_;
        
        /* if the tree is not empty */
        if (_this->command_ != DBFI_NODE_NONE)
        {
            _this->next_ = malloc(sizeof(dbfi_node_t));
            _this = _this->next_;
            
            /* malloc failed */
            if (!_this)
            {
                fprintf(stderr, "Error: Failed to allocate space for new parser tree node.\n");
                abort();
            }
        }
        
        _this->type_ = DBFI_NODE_SCOPE;
        _this->next_ = NULL;
        _this->scope_ = dbfi_parser_tree_init();
        
        /* if the subtree could not be allocated also release the parent node */
        if (!(_this->scope_))
        {
            free(_this);
            return NULL;
        }
        
        return (_this->scope_);
    }
    
    return NULL;
}
