/************************************************************************
 * Copyright (C) 2013, Felix Bytow <felix.bytow@googlemail.com>         *
 *                                                                      *
 * This file is part of dbfi.                                           *
 *                                                                      *
 * dbfi is free software: you can redistribute it and/or modify         *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * dbfi is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with dbfi.  If not, see <http://www.gnu.org/licenses/>.        *
 ************************************************************************/

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

void dbfi_parser_tree_add_command(dbfi_parser_tree_t _this, dbfi_command_t command, int param)
{
    /* do not add commands that have no effect at all */
    if (command == DBFI_COMMAND_NONE ||
        ((command == DBFI_COMMAND_MODIFY_VALUE || command == DBFI_COMMAND_MODIFY_PTR) && param == 0)
    )
        return;

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
        _this->parameter_ = param;
    }
}

dbfi_parser_tree_t dbfi_parser_tree_add_scope(dbfi_parser_tree_t _this)
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

