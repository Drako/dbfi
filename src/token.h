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

#if !defined(DBFI_TOKEN_H)
#define DBFI_TOKEN_H

#include <stdint.h>

typedef enum dbfi_token_type
{
    DBFI_TOKEN_PLUS = 0, /* + */
    DBFI_TOKEN_MINUS,    /* - */
    DBFI_TOKEN_GT,       /* > */
    DBFI_TOKEN_LT,       /* < */
    DBFI_TOKEN_BLEFT,    /* [ */
    DBFI_TOKEN_BRIGHT,   /* ] */
    DBFI_TOKEN_DOT,      /* . */
    DBFI_TOKEN_COMMA,    /* , */
    
    DBFI_TOKEN_EOF
} dbfi_token_type_t;

typedef struct dbfi_token_info
{
    dbfi_token_type_t type_;
    uint32_t row_;
    uint32_t column_;
    char const * filename_;
} dbfi_token_info_t;

#endif /* DBFI_TOKEN_H */

