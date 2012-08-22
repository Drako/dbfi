#ifndef DBFI_APPLICATION_HXX
#define DBFI_APPLICATION_HXX

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
	};
}

#endif // DBFI_APPLICATION_HXX

