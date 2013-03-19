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
 
#if !defined(DBFI_LEXER_H)
#define DBFI_LEXER_H

#include "token.h"

struct dbfi_lexer;
typedef struct dbfi_lexer * dbfi_lexer_t;

dbfi_lexer_t dbfi_lexer_init(char const * filename);
void dbfi_lexer_release(dbfi_lexer_t _this);

dbfi_token_info_t * dbfi_lexer_next_token(dbfi_lexer_t _this);

#endif /* DBFI_LEXER_H */

