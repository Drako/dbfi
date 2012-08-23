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

#include <parser.hxx>

#include <stdexcept>

namespace dbfi
{
	parser::parser(program & scope)
		: current_scope_(&scope)
	{
		// initial cleanup
		scope.type_ = TOK_PROGRAM;
		scope.parent_scope_ = nullptr;
		scope.instructions_.clear();
	}

	void parser::incptr()
	{
		add_to_scope(TOK_INCPTR);
	}

	void parser::decptr()
	{
		add_to_scope(TOK_DECPTR);
	}

	void parser::incval()
	{
		add_to_scope(TOK_INCVAL);
	}

	void parser::decval()
	{
		add_to_scope(TOK_DECVAL);
	}

	void parser::putchar()
	{
		add_to_scope(TOK_PUTCHAR);
	}

	void parser::getchar()
	{
		add_to_scope(TOK_GETCHAR);
	}

	void parser::openloop()
	{
		push_scope();
	}

	void parser::closeloop(bool & go_on)
	{
		go_on = pop_scope();
	}

	bool parser::is_complete()
	{
		return (current_scope_->parent_scope_ == nullptr);
	}

	void parser::add_to_scope(token_type tok)
	{
		token_tree * p = new token_tree;
		p->type_ = tok;
		current_scope_->instructions_.push_back(p);
	}

	void parser::push_scope()
	{
		program * p = new program;
		p->type_ = TOK_PROGRAM;
		p->parent_scope_ = current_scope_;
		current_scope_->instructions_.push_back(p);
		current_scope_ = p;
	}

	bool parser::pop_scope()
	{
		if (current_scope_->parent_scope_ == nullptr)
			return false;
		current_scope_ = current_scope_->parent_scope_;
		return true;
	}
}
