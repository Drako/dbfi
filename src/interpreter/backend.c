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

#include "backend.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if defined(_WIN32)
#include <conio.h>

int dbfi_getch(void)
{
    return _getch();
}
#elif defined(__linux__)
#include <termios.h>

int dbfi_getch(void)
{
    struct termios old, cur;
    int result;
    
    tcgetattr(0, &old);
    cur = old;
    cur.c_lflag &= ~ICANON;
    cur.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &cur);
    
    result = getchar();
    
    tcsetattr(0, TCSANOW, &old);
    
    return result;
}
#endif

struct dbfi_interpreter_backend
{
    dbfi_backend_type_t type_;
    
    /* the brainfuck memory */
    int memory_[65536];
    uint16_t memptr_;
};

dbfi_backend_t dbfi_interpreter_backend_init(void)
{
    struct dbfi_interpreter_backend * backend = malloc(sizeof(struct dbfi_interpreter_backend));
    if (!backend)
        return NULL;
    
    backend->type_ = DBFI_BACKEND_INTERPRETER;
    memset(backend->memory_, 0, sizeof(backend->memory_));
    backend->memptr_ = 0;
    
    return backend;
}

void dbfi_interpreter_backend_process_parser_tree(dbfi_backend_t _this, dbfi_parser_tree_t pt)
{
    dbfi_node_t * node = pt;
    struct dbfi_interpreter_backend * THIS = _this;
    
    assert(_this);
    
    while (node)
    {
        switch (node->type_)
        {
        default: /* do nothing */ break;
        case DBFI_NODE_SCOPE:
            {
                while (THIS->memory_[THIS->memptr_])
                    dbfi_interpreter_backend_process_parser_tree(_this, node->scope_);
            } break;
        case DBFI_NODE_COMMAND:
            {
                dbfi_interpreter_backend_handle_command(_this, node->command_, node->parameter_);
            } break;
        }
        
        node = node->next_;
    }
}

void dbfi_interpreter_backend_handle_command(dbfi_backend_t _this, dbfi_command_t command, int param)
{
    struct dbfi_interpreter_backend * THIS = _this;
    
    assert(_this);
    
    switch (command)
    {
    default: /* other tokens than those below may not appear hear */ break;
    case DBFI_COMMAND_MODIFY_VALUE:
        {
            (THIS->memory_[THIS->memptr_]) += param;
        } break;
    case DBFI_COMMAND_MODIFY_PTR:
        {
            (THIS->memptr_) += param;
        } break;
    case DBFI_COMMAND_PRINT:
        {
            putchar((char)(THIS->memory_[THIS->memptr_]));
        } break;
    case DBFI_COMMAND_READ:
        {
            THIS->memory_[THIS->memptr_] = dbfi_getch();
        } break;
    }
}

