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

#if !defined(DBFI_BACKEND_H)
#define DBFI_BACKEND_H

#include "parser_tree.h"

typedef void * dbfi_backend_t;

typedef enum dbfi_backend_type
{
    DBFI_BACKEND_INTERPRETER = 0,
    DBFI_BACKEND_COMPILER,
    
    DBFI_BACKEND_DUMMY /* does nothing */
} dbfi_backend_type_t;

dbfi_backend_t dbfi_backend_init(dbfi_backend_type_t type);
void dbfi_backend_release(dbfi_backend_t _this);

void dbfi_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt);
void dbfi_backend_finalize(dbfi_backend_t _this, char const * filename);

#endif /* DBFI_BACKEND_H */

