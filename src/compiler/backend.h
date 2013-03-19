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

#if !defined(DBFI_COMPILER_BACKEND_H)
#define DBFI_COMPILER_BACKEND_H

#include "../backend.h"

dbfi_backend_t dbfi_compiler_backend_init(void);
void dbfi_compiler_backend_release(dbfi_backend_t _this);
void dbfi_compiler_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt);
void dbfi_compiler_backend_handle_command(dbfi_backend_t _this, dbfi_token_type_t command);
void dbfi_compiler_backend_finalize(dbfi_backend_t _this, char const * filename);

#endif /* DBFI_COMPILER_BACKEND_H */

