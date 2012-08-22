/************************************************************************
 * Copyright (C) 2010, Felix Bytow <drako123@gmx.de>                    *
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

#ifndef DBFI_TOKENS_HXX
#define DBFI_TOKENS_HXX

#include <boost/ptr_container/ptr_list.hpp>

namespace dbfi
{
	enum token_type
	{
		TOK_PROGRAM = 0, // Special token used for the root node
		TOK_INCPTR, // >
		TOK_DECPTR, // <
		TOK_INCVAL, // +
		TOK_DECVAL, // -
		TOK_PUTCHAR, // .
		TOK_GETCHAR, // ,
		TOK_OPENLOOP, // [
		TOK_CLOSELOOP // ]
	};

	struct token_tree
	{
		token_type type_;
	};

	struct program
		: token_tree
	{
		program * parent_scope_;
		boost::ptr_list<token_tree> instructions_;
	};
}

#endif // DBFI_TOKENS_HXX

