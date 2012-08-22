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

#ifndef DBFI_APPLICATION_HXX
#define DBFI_APPLICATION_HXX

#include <tokens.hxx>

#include <boost/utility.hpp>

namespace dbfi
{
	class application
		: private boost::noncopyable
	{
	public:
		// constructor/destructor
		application();
		~application();
		
		// main entry point
		int main(int argc, char ** argv);

		// singleton access
		static application & instance();
		static application * instance_ptr();
	private:
		static application * instance_;

		program script_;
	};
}

#endif // DBFI_APPLICATION_HXX

