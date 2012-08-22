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
#include <config.hxx>
#include <parser.hxx>

#include <iostream>
#include <string>

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

		std::string filename;

		///////////////////////////
		// command line handling //
		///////////////////////////
		
		po::options_description desc("Available Options");
		desc.add_options()
			("help,?", "produce help message")
			("version,v", "show version information")
			("input,i", po::value<std::string>(&filename), "input file")
		;

		po::positional_options_description p;
		p.add("input", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 0;
		}

		if (vm.count("version")) {
			std::cout << "Dragon Brainfuck Interpreter\n";
			std::cout << "Version " << DBFI_VERSION << "-r" << DBFI_GIT_HASH << " " << DBFI_BUILD_TYPE << " " << DBFI_ARCH << "\n";
			std::cout << "Copyright (C) 2012, Felix Bytow <felix.bytow@googlemail.com>" << std::endl;
			return 0;
		}

		if (!(vm.count("input"))) {
			std::cerr << "Error: Missing input file name!\n";
			std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
			return 1;
		}

		///////////////////
		// input parsing //
		///////////////////

		// TODO: implement

		////////////////////
		// interpretation //
		////////////////////

		// TODO: implement

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

