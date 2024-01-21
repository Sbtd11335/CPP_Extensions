#ifndef EXTENSIONS_EVAL_HPP
#	define	EXTENSIONS_EVAL_HPP

#	include	"Common.hpp"
#	include <iostream>
#	include <math.h>
#	include <string>
#	include <sstream>
#	include <iomanip>

namespace Extensions
{
	template<typename Type>Type EasyEval(const char* Formula);
	template<typename Type>Type SimpleEval(const char* Formula, size_t SetPrecision = 6);
#ifdef EXTENSIONS_THREAD_INCLUDED
	//template<typename Type>Type ThreadSimpleEval(const char* Formula);
#endif
}//namespace Extensions

#include "Eval/_Eval.hpp"
#endif