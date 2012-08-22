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

#include <application.hxx>

#include <iostream>

#include <cassert>

#include <boost/program_options.hpp>

namespace dbfi
{
	application * application::instance_ = nullptr;

	application::application()
	{
		assert(instance_ == nullptr);
		instance_ = this;
	}

	application::~application()
	{
		assert(instance_ != nullptr);
		instance_ = nullptr;
	}

	int application::main(int argc, char ** argv)
	{
		namespace po = boost::program_options;

		po::options_description desc;
		desc.add_options()
			("help,?", "produce help message")
			("version,v", "show version information")
		;

		return 0;
	}

	application & application::instance()
	{
		assert(instance_ != nullptr);
		return (*instance_);
	}

	application * application::instance_ptr()
	{
		return instance_;
	}
}

