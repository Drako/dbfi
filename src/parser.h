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

#if !defined(DBFI_PARSER_H)
#define DBFI_PARSER_H

#include "lexer.h"
#include "parser_tree.h"

struct dbfi_parser;
typedef struct dbfi_parser * dbfi_parser_t;

dbfi_parser_t dbfi_parser_init(void);
void dbfi_parser_release(dbfi_parser_t _this);

dbfi_parser_tree_t dbfi_parser_generate_tree(dbfi_parser_t _this, dbfi_lexer_t lexer);

#endif /* DBFI_PARSER_H */

