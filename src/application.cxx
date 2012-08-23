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
#include <interpreter.hxx>

#include <iostream>
#include <string>
#include <fstream>

#include <cassert>

#include <boost/program_options.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

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
		namespace spirit = boost::spirit;

		std::string filename;
		unsigned fieldsize;

		///////////////////////////
		// command line handling //
		///////////////////////////
		
		po::options_description desc("Available Options");
		desc.add_options()
			("help,?", "produce help message")
			("version,v", "show version information")
			("input,i", po::value<std::string>(&filename), "input file")
			("fieldsize,s", po::value<unsigned>(&fieldsize)->default_value(2048), "brainfuck field size")
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

		std::ifstream source(filename);
		if (!source) {
			std::cerr << "Error: Could not open \"" << filename << "\"." << std::endl;
			return 2;
		}

		typedef std::istreambuf_iterator<char> base_iterator_type;
		typedef spirit::multi_pass<base_iterator_type> forward_iterator_type;
		typedef spirit::classic::position_iterator<forward_iterator_type> pos_iterator_type;

		base_iterator_type in_begin(source);
		forward_iterator_type fwd_begin = spirit::make_default_multi_pass(in_begin);
		forward_iterator_type fwd_end;
		pos_iterator_type pos_begin(fwd_begin, fwd_end, filename);
		pos_iterator_type pos_end;

		try {
			parse_program(pos_begin, pos_end, script_);
		} catch(std::runtime_error const & e) {
			auto const & pos = pos_begin.get_position();
			std::cerr << pos.file << ":" << pos.line << ":" << pos.column << ": " << e.what() << std::endl;
			return 3;
		}

		////////////////////
		// interpretation //
		////////////////////

		interpreter i(fieldsize);
		i.run(script_);

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

