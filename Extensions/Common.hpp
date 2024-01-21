#ifndef EXTENSIONS_COMMON_HPP
#	define	EXTENSIONS_COMMON_HPP
#if defined(BOOST_MP_CPP_INT_HPP) || defined(BOOST_MP_CPP_DEC_FLOAT_HPP) || defined(BOOST_MP_CPP_COMPLEX_HPP)
#	define	EXTENSIONS_BOOST_INCLUDED
#endif
#if __has_include(<thread>)
#	define	EXTENSIONS_THREAD_INCLUDED
#	include	<future>
#endif

#	define	SINGLEBYTE	strlen("0")
#	define	MULTIBYTE	strlen("‚O")

#if defined(_MSC_VER)
#	define	STRICMP		_stricmp
#else
#	define	STRICMP		stricmp
#endif

#	include <string.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <ctype.h>

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
	void SwapCase(char* Buffer, size_t Size);
	size_t StrFind(const char* Src, const char* Find);
	size_t StrCaseFind(const char* Src, const char* Find, size_t Find_Size);
	size_t StrSplit(char* Buffer, size_t Size, const char* Src, char Del, size_t Position);
	template <typename Type>Type ToValue(const char* Value);
}//namespace Extensions

//Extensions::ToValue
template <typename Type>Type Extensions::ToValue(const char* Value)
{
	Type Return{};
	bool BoostCheck{};
	//boost
#ifdef EXTENSIONS_BOOST_INCLUDED
	if (Extensions::StrCaseFind(typeid(Return).name(), "Boost", sizeof("Boost")))BoostCheck = true;
#endif
	if (Extensions::FindDBCS(Value) != Extensions::npos)return Return;
	char Minus[2]{}, ExponentialMinus[2]{}, GetValue[Extensions::BufferSize]{}, GetExponentialValue[Extensions::BufferSize]{}, ReturnValue[Extensions::BufferSize]{};
	bool GetSymbol{}, GetNum{}, GetDecimalPoint{}, GetExponential{}, GetExponentialSymbol{}, GetExponentialNum{};
	for (size_t Count{}; Count < strlen(Value); Count += SINGLEBYTE)
	{
		if (Value[Count] == '+')
		{
			if (GetExponential == false)
			{
				if (GetNum || GetDecimalPoint)return Return;
				GetSymbol = true;
			}
			else {
				if (GetExponentialNum)return Return;
				GetExponentialSymbol = true;
			}
		}
		else if (Value[Count] == '-') {
			if (GetExponential == false)
			{
				if (GetNum || GetDecimalPoint)return Return;
#if	defined(_MSC_VER)
				if (strlen(Minus) == 0)strcpy_s(Minus, sizeof(Minus), "-");
				else strcpy_s(Minus, sizeof(Minus), "");
#else
				if (strlen(Minus) == 0)strcpy(Minus, "-");
				else strcpy(Minus, "");
#endif
				GetSymbol = true;
			}
			else {
				if (GetExponentialNum)return Return;
#if defined(_MSC_VER)
				if (strlen(ExponentialMinus) == 0)strcpy_s(ExponentialMinus, sizeof(ExponentialMinus), "-");
				else strcpy_s(ExponentialMinus, sizeof(ExponentialMinus), "");
#else
				if (strlen(ExponentialMinus) == 0)strcpy(ExponentialMinus, "-");
				else strcpy(ExponentialMinus, "");
#endif
				GetExponentialSymbol = true;
			}
		}
		else if (Value[Count] == 'e' || Value[Count] == 'E') {
			if (GetExponential == false)GetExponential = true;
			else return Return;
		}
		else if (Value[Count] == '.') {
			if (GetExponential == false)
			{
				if (GetDecimalPoint)return Return;
				GetDecimalPoint = true;
				GetValue[strlen(GetValue)] = Value[Count];
			}
			else return Return;
		}
		else if (IsNum(Value[Count])) {
			if (GetExponential == false)
			{
				GetNum = true;
				GetValue[strlen(GetValue)] = Value[Count];
			}
			else {
				GetExponentialNum = true;
				GetExponentialValue[strlen(GetExponentialValue)] = Value[Count];
			}
		}
		else return Return;
	}
	if (GetNum == false)return Return;
	if (GetExponential && GetExponentialNum == false)return Return;
#if defined(_MSC_VER)
	if (GetExponential == false)sprintf_s(ReturnValue, sizeof(ReturnValue), "%s%s", Minus, GetValue);
	else sprintf_s(ReturnValue, sizeof(ReturnValue), "%s%se%s%s", Minus, GetValue, ExponentialMinus, GetExponentialValue);
#else
	if (GetExponential == false)sprintf(ReturnValue, "%s%s", Minus, GetValue);
	else sprintf(ReturnValue, "%s%se%s%s", Minus, GetValue, ExponentialMinus, GetExponentialValue);
#endif
#ifndef EXTENSIONS_BOOST_INCLUDED
	Return = atof(ReturnValue);
#else
	if (BoostCheck == false)Return = Type(atof(ReturnValue));
	else Return = boost::lexical_cast<Type>(ReturnValue);
#endif
	return Return;
}
#endif