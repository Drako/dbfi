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

#include <interpreter.hxx>
#include <config.hxx>

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <cstdio>
#endif

namespace platform
{
#if defined(DBFI_UNIX)
	namespace detail
	{
		void init_termios(termios & old)
		{
			tcgetattr(0, &old);
			termios new_ = old;
			new_.c_lflag &= ~ICANON;
			new_.c_lflag &= ~ECHO;
			tcsetattr(0, TCSANOW, &new_);
		}

		void reset_termios(termios const & old)
		{
			tcsetattr(0, TCSANOW, &old);
		}

		char getch()
		{
			termios old;

			init_termios(old);
			char ch = std::getchar();
			reset_termios(old);

			return ch;
		}
	}
#endif

	char getch()
	{
#ifdef DBFI_WINDOWS
		return static_cast<char>(_getch());
#else
		return detail::getch();
#endif
	}
}

namespace dbfi
{
	interpreter::interpreter(int fieldsize)
		: field_(fieldsize)
		, index_(0)
	{
	}
	
	void interpreter::run(program const & scope)
	{
		for (auto const & cmd : scope.instructions_) {
			switch (cmd.type_) {
			case TOK_INCPTR:
				if (++index_ >= static_cast<int>(field_.size()))
					index_ = 0;
				break;
			case TOK_DECPTR:
				if (--index_ < 0)
					index_ = static_cast<int>(field_.size()) - 1;
				break;
			case TOK_INCVAL:
				++(field_[index_]);
				break;
			case TOK_DECVAL:
				--(field_[index_]);
				break;
			case TOK_PUTCHAR:
				std::cout << static_cast<char>(field_[index_]);
				break;
			case TOK_GETCHAR:
				field_[index_] = platform::getch();
				break;
			case TOK_PROGRAM:
				while (field_[index_])
					run(static_cast<program const &>(cmd));
				break;
			}
		}
	}
}
