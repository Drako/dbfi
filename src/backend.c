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

#include "config.h"
#include "backend.h"
#if defined(LIBTCC_FOUND)
#include "compiler/backend.h"
#endif
#include "interpreter/backend.h"

#include <stdlib.h>
#include <assert.h>

struct dbfi_basic_backend
{
    dbfi_backend_type_t type_;
};

dbfi_backend_t dbfi_backend_init(dbfi_backend_type_t type)
{
    static struct dbfi_basic_backend dummy = { DBFI_BACKEND_DUMMY };
    
    switch (type)
    {
    default:                       return &dummy;                          break;
#if defined(LIBTCC_FOUND)
    case DBFI_BACKEND_COMPILER:    return dbfi_compiler_backend_init();    break;
#endif /* LIBTCC_FOUND */
    case DBFI_BACKEND_INTERPRETER: return dbfi_interpreter_backend_init(); break;
    };
}

void dbfi_backend_release(dbfi_backend_t _this)
{
    struct dbfi_basic_backend * THIS = _this;
    
    switch (THIS->type_)
    {
    default: /* do nothing */ break;
#if defined(LIBTCC_FOUND)
    case DBFI_BACKEND_COMPILER:
        dbfi_compiler_backend_release(_this);
#endif /* LIBTCC_FOUND */
        /* fall through */
    case DBFI_BACKEND_INTERPRETER:
        free(_this);
    }
}

void dbfi_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt)
{
    struct dbfi_basic_backend * THIS = _this;
    
    assert(_this);
    
    switch (THIS->type_)
    {
    default:                       /* the dummy does nothing */                                    break;
#if defined(LIBTCC_FOUND)
    case DBFI_BACKEND_COMPILER:    dbfi_compiler_backend_process_parser_tree(_this, pt);    break;
#endif /* LIBTCC_FOUND */
    case DBFI_BACKEND_INTERPRETER: dbfi_interpreter_backend_process_parser_tree(_this, pt); break;
    }
}

void dbfi_backend_finalize(dbfi_backend_t _this, char const * filename)
{
    struct dbfi_basic_backend * THIS = _this;
    
    assert(_this);
    
#if defined(LIBTCC_FOUND)
    if (THIS->type_ == DBFI_BACKEND_COMPILER)
        dbfi_compiler_backend_finalize(_this, filename);
#endif /* LIBTCC_FOUND */
}

