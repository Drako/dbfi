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

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct dbfi_parser
{
    dbfi_parser_tree_t current_scope_;
};

dbfi_parser_t dbfi_parser_init(void)
{
    dbfi_parser_t parser = malloc(sizeof(struct dbfi_parser));
    if (!parser)
        return NULL;
    
    parser->current_scope_ = NULL;
    return parser;
}

void dbfi_parser_release(dbfi_parser_t _this)
{
    free(_this);
}

dbfi_parser_tree_t dbfi_parser_generate_tree(dbfi_parser_t _this, dbfi_lexer_t lexer)
{
    dbfi_parser_tree_t result;
    dbfi_token_info_t * tok;
    int is_root = 0;
    
    assert(_this);
    assert(lexer);
    
    result = _this->current_scope_;
    if (!result)
    {
        is_root = 1;
        
        result = dbfi_parser_tree_init();
        if (!result)
            return NULL;
    }
    
    /* walk through tokens till end of file or end of scope */
    tok = dbfi_lexer_next_token(lexer);
    while (tok->type_ != DBFI_TOKEN_BRIGHT && tok->type_ != DBFI_TOKEN_EOF)
    {
        if (tok->type_ == DBFI_TOKEN_BLEFT)
        {
            dbfi_parser_tree_t subtree = dbfi_parser_tree_add_scope(result);
            assert(subtree);
            
            _this->current_scope_ = subtree;
            dbfi_parser_generate_tree(_this, lexer);
            _this->current_scope_ = result;
        }
        else
            dbfi_parser_tree_add_command(result, tok->type_);
        
        tok = dbfi_lexer_next_token(lexer);
    }
    
    if (is_root)
    {
        _this->current_scope_ = NULL;
        
        /* we are at root scope... the scope has ended... but not the file
         * thus there has to be an unexpected ] (right bracket) */
        if (tok->type_ != DBFI_TOKEN_EOF)
        {
            fprintf(stderr,
                "Error: Unexpected closing bracket.\n"
                "At:    %s - Line: %u - Column: %u.\n"
            , tok->filename_, (unsigned)(tok->row_ + 1), (unsigned)(tok->column_ + 1));
            exit(-1);
        }
    }
    
    return result;
}

