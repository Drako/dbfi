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

#ifndef DBFI_PARSER_HXX
#define DBFI_PARSER_HXX

#include <tokens.hxx>

#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#include <boost/spirit/include/qi.hpp>

namespace dbfi
{
	class parser
		: private boost::noncopyable
	{
	public:
		parser(program & scope);

		void incptr();
		void decptr();
		void incval();
		void decval();
		void putchar();
		void getchar();
		void openloop();
		void closeloop(bool & go_on);

		bool is_complete();
		
	private:
		void push_scope();
		bool pop_scope();
		void add_to_scope(token_type tok);
		
		program * current_scope_;
	};
	
	template <typename Iterator>
	void parse_program(Iterator & begin, Iterator end, program & scope)
	{
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		parser state(scope);

		// parser definition
		qi::phrase_parse(begin, end, *(
			qi::char_('>')[boost::bind(&parser::incptr, &state)] |
			qi::char_('<')[boost::bind(&parser::decptr, &state)] |
			qi::char_('+')[boost::bind(&parser::incval, &state)] |
			qi::char_('-')[boost::bind(&parser::decval, &state)] |
			qi::char_('.')[boost::bind(&parser::putchar, &state)] |
			qi::char_(',')[boost::bind(&parser::getchar, &state)] |
			qi::char_('[')[boost::bind(&parser::openloop, &state)] |
			qi::char_(']')[boost::bind(&parser::closeloop, &state, ::_3)] |
			(~qi::char_("<>+-.,[]")) // everything else is a comment
			), ascii::space
		);

		if (begin != end)
			throw std::runtime_error("Unexpected end of loop \']\'.");

		if (!(state.is_complete()))
			throw std::runtime_error("Unexpected end of file. Missing \']\'.");
	}
}

#endif // DBFI_PARSER_HXX

