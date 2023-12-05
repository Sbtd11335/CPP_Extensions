#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>


#ifndef EXTENSIONS_COMMON_HPP_INCLUDED
#	define EXTENSIONS_COMMON_HPP_INCLUDED

#ifdef BOOST_MP_CPP_INT_HPP || BOOST_MP_CPP_DEC_FLOAT_HPP || BOOST_MP_CPP_COMPLEX_HPP
#	define ET_BOOST_IUNCLUDED
#	include "Boost.hpp"
#endif

#	define ET_SINGLEBYTE	strlen("0")
#	define ET_MULTIBYTE		strlen("‚O")

namespace Extensions {
	bool IsDBCS(char TestChar);
	int64_t FindDBCS(const char* TestStr);
	bool IsNum(char TestChar);
	bool IsAllNum(const char* TestStr);
	int64_t StrFind(const char* Str1, const char* Str2);
	std::string EraceSpace(const char* Str);
	template <typename Type>Type catos(const char* Str);
	template<> std::string catos(const char* Str);
	template<> float catos(const char* Str);
	template<> double catos(const char* Str);
	template<> int catos(const char* Str);
	template<> long long catos(const char* Str);
}//Extensions

//Extensions::catos
template <typename Type>inline Type Extensions::catos(const char* Str)
{
	//Boost
	bool Boost_cast{};
	if (StrFind(typeid(Type).name(), "boost") >= 0)Boost_cast = true;
	if (FindDBCS(EraceSpace(Str).c_str()) >= 0 || IsAllNum(EraceSpace(Str).c_str()) == false)
	{
		if (Boost_cast == false)return static_cast<Type>(atof("0.0"));
		else return Type("0.0");
	}
	std::string Return{ "" };
	std::string Minus{ "" };
	for (size_t Count{}; Count < strlen(EraceSpace(Str).c_str()); Count += ET_SINGLEBYTE)
	{
		if (EraceSpace(Str).c_str()[Count] == '+')continue;
		else if (EraceSpace(Str).c_str()[Count] == '-')
		{
			if (Minus.length() == 0)Minus = "-";
			else Minus.clear();
		}
		else Minus.append(std::string(1, EraceSpace(Str).c_str()[Count]));
	}
	Return.insert(0, Minus);
	if (Boost_cast == false)return static_cast<Type>(atof(Return.c_str()));
	else return Type(Return.c_str());
}

#endif