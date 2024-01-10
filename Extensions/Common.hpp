#ifndef EXTENSIONS_COMMON_HPP
#	define EXTENSIONS_COMMON_HPP
//Boost
#	ifdef BOOST_MP_CPP_INT_HPP || BOOST_MP_CPP_DEC_FLOAT_HPP || BOOST_MP_CPP_COMPLEX_HPP
#	define EXTENSIONS_BOOST
#	ifndef BOOST_LEXICAL_CAST_INCLUDED
#		include<boost/lexical_cast.hpp>
#	endif
#	endif
#	include <string.h>
#	include <stdlib.h>
#	include <stdio.h>
#	include <ctype.h>

#	define	SINGLEBYTE	strlen("0")
#	define	MULTIBYTE	strlen("‚O")

namespace Extensions
{
	constexpr size_t npos = -1;
	constexpr size_t BufferSize = 2048;

	bool IsDBCS(char TestChar);
	size_t FindDBCS(const char* Src);
	size_t mbstrlen(const char* Src);
	const char* ToLowerString(const char* Str);
	const char* ToUpperString(const char* Str);
	const char* EraceSpace(const char* Src);
	size_t strfind(const char* Src, const char* find);
	size_t strcasefind(const char* Src, const char* find);
	bool IsNum(char TestChar);
	bool IsValue(const char* Src);
	template <typename Type>Type ToValue(const char* Value);
	template <>char* ToValue(const char* Value);
	template <>const char* ToValue(const char* Value);

}//namespace Extensions

template <typename Type>Type Extensions::ToValue(const char* Value)
{
	Type Return{};
#ifndef EXTENSIONS_BOOST
	Return = Type(atof(Extensions::ToValue<const char*>(Value)));
#else
	Return = boost::lexical_cast<Type>(Extensions::ToValue<const char*>(Value));
#endif
	return Return;
}

#endif