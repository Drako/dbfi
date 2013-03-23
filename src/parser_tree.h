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

#if !defined(DBFI_PARSER_TREE)
#define DBFI_PARSER_TREE

#include "token.h"

typedef enum dbfi_node_type
{
    DBFI_NODE_COMMAND = 0,
    DBFI_NODE_SCOPE,
    
    DBFI_NODE_NONE
} dbfi_node_type_t;

typedef enum dbfi_command
{
    DBFI_COMMAND_MODIFY_VALUE = 0,
    DBFI_COMMAND_MODIFY_PTR,
    DBFI_COMMAND_PRINT,
    DBFI_COMMAND_READ,

    DBFI_COMMAND_NONE
} dbfi_command_t;

typedef struct dbfi_node
{
    dbfi_node_type_t type_;
    struct dbfi_node * next_;
    
    union
    {
        /* type_ == DBFI_NODE_COMMAND */
        struct
        {
            dbfi_command_t command_;
            /* for DBFI_COMMAND_MODIFY_VALUE and DBFI_COMMAND_MODIFY_PTR */
            int parameter_;
        };
        
        /* type_ == DBFI_NODE_SCOPE */
        struct dbfi_node * scope_;
    };
} dbfi_node_t;

typedef struct dbfi_node * dbfi_parser_tree_t;

dbfi_parser_tree_t dbfi_parser_tree_init(void);
void dbfi_parser_tree_release(dbfi_parser_tree_t _this);
void dbfi_parser_tree_add_command(dbfi_parser_tree_t _this, dbfi_command_t command, int param);
dbfi_parser_tree_t dbfi_parser_tree_add_scope(dbfi_parser_tree_t _this);

#endif /* DBFI_PARSER_TREE */

