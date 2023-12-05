#if __has_include(<python.h>)
#	define PY_SSIZE_T_CLEAN
#	include<Python.h>
#else
#	error "Python.h" file not found
#endif

#include <string>

#ifndef EXTENSIONS_PYTHON_HPP_INCLUDED
#	define EXTENSIONS_PYTHON_HPP_INCLUDED

namespace Extensions {
	namespace Python {
		class Python {
		private:
			PyObject* Main{};
		public:
			Python();
			Python(int I);
			~Python();
			void Import(const char* Name);
			void Run(const char* Code);
			template <typename Type>Type Get(const char* Variable);
		};
		void pipinstall(const char* Name);
		void Version();
	}
}//Extensions


#endif