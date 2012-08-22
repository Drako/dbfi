#include <application.hxx>

#include <cassert>

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

