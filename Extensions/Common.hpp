#ifndef EXTENSIONS_COMMON_HPP
#	define	EXTENSIONS_COMMON_HPP
#if defined(BOOST_MP_CPP_INT_HPP) || defined(BOOST_MP_CPP_DEC_FLOAT_HPP) || defined(BOOST_MP_CPP_COMPLEX_HPP)
#	define	EXTENSIONS_BOOST_INCLUDED
#endif
#if __has_include(<thread>)
#	define	EXTENSIONS_THREAD_INCLUDED
#	include	<future>
#	include <mutex>
#endif

#	ifndef MULTIBYTE_SPACE
#		define	MULTIBYTE_SPACE "Å@"
#	endif
#	define	SINGLEBYTE	1
#	define	MULTIBYTE	strlen(MULTIBYTE_SPACE)

#	include <string.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <ctype.h>
#	include <numeric>

#	ifndef INFINITY
#		define INFINITY ((float)(1e+300 * 1e+300))
#	endif

namespace Extensions
{
	constexpr size_t npos = -1;
	constexpr size_t BufferSize = 1024;

	bool IsDBCS(char TestChar);
	size_t FindDBCS(const char* TestStr);
	bool IsNum(char TestChar);
	bool IsValue(const char* Value);
	void StrClear(char* Src, size_t Size);
	void EraseSpace(char* Str, size_t Size);
	void EraseChar(char* Str, size_t Size, const char* EraceStr);
	size_t MBStrlen(const char* Str);
	void Substr(char* Buffer, size_t Size, const char* Str, size_t Start, size_t Num);
	void MBSubstr(char* Buffer, size_t Size, const char* Str, size_t Start, size_t Num);
	void StrInsert(char* Buffer, size_t Size, const char* Str, size_t Position);
	void StrInsert(char* Buffer, size_t Size, char Str, size_t Position);
	void StrErase(char* Buffer, size_t Size, size_t Start, size_t Num);
	void ToUpper(char* Buffer, size_t Size);
	void ToLower(char* Buffer, size_t Size);
	int StrCaseCmp(const char* Str1, const char* Str2);
	void SwapCase(char* Buffer, size_t Size);
	size_t StrFind(const char* Src, const char* Find);
	size_t StrCaseFind(const char* Src, const char* Find, size_t Find_Size);
	size_t CharCount(const char* Str, char CountChar);
	size_t StrSplit(char* Buffer, size_t Size, const char* Src, char Del, size_t Position);
	template <typename Type>Type ToValue(const char* Value);
}//namespace Extensions

#	include "_Common.hpp"
#endif