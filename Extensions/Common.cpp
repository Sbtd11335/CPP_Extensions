#include "Common.hpp"

namespace Extensions
{
	bool IsDBCS(char TestChar)
	{
		if (TestChar < 0)return true;
		return false;
	}
	size_t FindDBCS(const char* Src)
	{
		for (size_t Count{}; Count < strlen(Src); Count += SINGLEBYTE) { if (Extensions::IsDBCS(Src[Count]))return Count; }
		return Extensions::npos;
	}
	size_t mbstrlen(const char* Src)
	{
		size_t Return{};
		for (size_t Count{}; Count < strlen(Src);)
		{
			if (IsDBCS(Src[Count]) == false)
			{
				Return++;
				Count += SINGLEBYTE;
			}
			else {
				Return++;
				Count += MULTIBYTE;
			}
		}
		return Return;
		return Return;
	}
	const char* ToLowerString(const char* Str)
	{
		char Return[Extensions::BufferSize]{};
		for (size_t Count{}; Count < strlen(Str);)
		{
			if (IsDBCS(Str[Count]) == false)
			{
				Return[strlen(Return)] = tolower(Str[Count]);
				Count += SINGLEBYTE;
			}
			else {
				for (size_t Count2{}; Count2 < MULTIBYTE; Count2++)
				{
					Return[strlen(Return)] = Str[Count + Count2];
				}
				Count += MULTIBYTE;
			}

				
		}
		return Return;
	}
	const char* ToUpperString(const char* Str)
	{
		char Return[Extensions::BufferSize]{};
		for (size_t Count{}; Count < strlen(Str);)
		{
			if (IsDBCS(Str[Count]) == false)
			{
				Return[strlen(Return)] = toupper(Str[Count]);
				Count += SINGLEBYTE;
			}
			else {
				for (size_t Count2{}; Count2 < MULTIBYTE; Count2++)
				{
					Return[strlen(Return)] = Str[Count + Count2];
				}
				Count += MULTIBYTE;
			}


		}
		return Return;
	}
	const char* EraceSpace(const char* Src)
	{
		char Return[Extensions::BufferSize]{};
		char MultiByte_Base[10]{};
		for (size_t Count{}; Count < strlen(Src);)
		{
			if (IsDBCS(Src[Count]) == false)
			{
				if (Src[Count] != ' ')Return[strlen(Return)] = Src[Count];
				Count += SINGLEBYTE;
			}
			else {
				for (size_t MCount{}; MCount < MULTIBYTE; MCount++)
				{
					MultiByte_Base[MCount] = Src[Count + MCount];
				}
				MultiByte_Base[MULTIBYTE] = '\0';
				for (size_t MCount{}; strcmp(MultiByte_Base, "@") != 0 && MCount < MULTIBYTE; MCount++)
				{
					Return[strlen(Return)] = Src[Count + MCount];
				}
				strcpy_s(MultiByte_Base, "");
				Count += MULTIBYTE;
			}

		}
		Return[strlen(Return)] = '\0';
		return const_cast<const char*>(Return);
	}
	size_t strfind(const char* Src, const char* find)
	{
		if (strlen(Src) == 0 || strlen(find) == 0 || strlen(Src) < strlen(find))return Extensions::npos;
		for (size_t Count{}; Count < strlen(Src);)
		{
			size_t Count3{};
			char Base[Extensions::BufferSize]{};
			for (size_t Count2{}; Count2 < Extensions::mbstrlen(find); Count2++)
			{
				if (IsDBCS(Src[Count + Count3]) == false)
				{
					Base[strlen(Base)] = Src[Count + Count3];
					Count3 += SINGLEBYTE;
				}
				else {
					for (size_t Count4{}; Count4 < MULTIBYTE; Count4++)
					{
						Base[strlen(Base)] = Src[Count + Count3 + Count4];
					}
					Count3 += MULTIBYTE;
				}
			}
			Base[strlen(Base)] = '\0';
			if (Extensions::mbstrlen(Base) < Extensions::mbstrlen(find))break;
			if (strcmp(Base, find) == 0)return Count;
			if (IsDBCS(Src[Count]) == false)Count += SINGLEBYTE;
			else Count += MULTIBYTE;
		}
		return Extensions::npos;
	}
	size_t strcasefind(const char* Src, const char* find)
	{
		if (strlen(Extensions::ToLowerString(Src)) == 0 || strlen(Extensions::ToLowerString(find)) == 0 || strlen(Extensions::ToLowerString(Src)) < strlen(Extensions::ToLowerString(find)))return Extensions::npos;
		for (size_t Count{}; Count < strlen(Extensions::ToLowerString(Src));)
		{
			size_t Count3{};
			char Base[Extensions::BufferSize]{};
			for (size_t Count2{}; Count2 < Extensions::mbstrlen(Extensions::ToLowerString(find)); Count2++)
			{
				if (IsDBCS(Extensions::ToLowerString(Src)[Count + Count3]) == false)
				{
					Base[strlen(Base)] = Extensions::ToLowerString(Src)[Count + Count3];
					Count3 += SINGLEBYTE;
				}
				else {
					for (size_t Count4{}; Count4 < MULTIBYTE; Count4++)
					{
						Base[strlen(Base)] = Extensions::ToLowerString(Src)[Count + Count3 + Count4];
					}
					Count3 += MULTIBYTE;
				}
			}
			Base[strlen(Base)] = '\0';
			if (Extensions::mbstrlen(Base) < Extensions::mbstrlen(Extensions::ToLowerString(find)))break;
			if (strcmp(Base, Extensions::ToLowerString(find)) == 0)return Count;
			if (IsDBCS(Extensions::ToLowerString(Src)[Count]) == false)Count += SINGLEBYTE;
			else Count += MULTIBYTE;
		}
		return Extensions::npos;
	}
	bool IsNum(char TestChar)
	{
		char Get[2]{};
		Get[0] = TestChar;
		Get[1] = '\0';
		if (strspn(Get, "0123456789") < strlen(Get))return false;
		return true;
	}
	bool IsValue(const char* Src)
	{
		if (Extensions::FindDBCS(Src) != Extensions::npos || strlen(Src) == 0)return false;
		bool GetSymbol{}, GetDecimalPoint{}, GetNum{}, GetExponential{}, GetExponentialSymbol{}, GetExponentialNum{};
		for (size_t Count{}; Count < strlen(Src); Count += SINGLEBYTE)
		{
			if (IsNum(Src[Count]) == false)
			{
				if (Src[Count] == '.')
				{
					if (GetExponential == false)
					{
						if (GetDecimalPoint == false && GetNum)GetDecimalPoint = true;
						else return false;
					}
					else return false;
				}
				else if (Src[Count] == '-' || Src[Count] == '+')
				{
					if (GetExponential == false)
					{
						if (GetNum)return false;
						GetSymbol = true;
					}
					else {
						if (GetExponentialNum)return false;
						GetExponentialSymbol = true;
					}
				}
				else if (Src[Count] == 'e' || Src[Count] == 'E')
				{
					if (GetExponential || GetNum == false)return false;
					GetExponential = true;
				}
				else return false;
			}
			else {
				if (GetExponential == false)GetNum = true;
				else GetExponentialNum = true;
			}
		}
		if (GetExponential && GetExponentialNum == false)return false;
		return true;
	}
	//template <typename Type>Type Extensions::ToValue(const char* Value)
	template <>char* ToValue(const char* Value)
	{
		if (Extensions::IsValue(Value) == false)return (char*)"0.0";
		char Process[Extensions::BufferSize]{}, ExponentialProcess[Extensions::BufferSize]{}, Process2[Extensions::BufferSize]{};
		char Minus[2]{}, ExponentialMinus[2]{};
		bool GetExponential{};
		for (size_t Count{}; Count < strlen(Value); Count += SINGLEBYTE)
		{
			if (Value[Count] == '+')
			{

			}
			else if (Value[Count] == '-')
			{
				if (GetExponential == false)
				{
					if (strlen(Minus) == 0)strcpy_s(Minus, "-");
					else strcpy_s(Minus, "");
				}
				else {
					if (strlen(ExponentialMinus) == 0)strcpy_s(ExponentialMinus, "-");
					else strcpy_s(ExponentialMinus, "");
				}
			}
			else if (Value[Count] == 'e' || Value[Count] == 'E')GetExponential = true;
			else {
				if (GetExponential == false)Process[strlen(Process)] = Value[Count];
				else ExponentialProcess[strlen(ExponentialProcess)] = Value[Count];
			}
		}
		Process[strlen(Process)] = '\0';
		if (GetExponential == false)(void)sprintf_s(Process2, sizeof(Process2), "%s%s", Minus, Process);
		else (void)sprintf_s(Process2, sizeof(Process2), "%s%se%s%s", Minus, Process, ExponentialMinus, ExponentialProcess);
		return Process2;
	}
	template <>const char* ToValue(const char* Value) { return const_cast<const char*>(Extensions::ToValue<char*>(Value)); }

}//namespace Extensions