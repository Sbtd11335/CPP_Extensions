#include "Common.hpp"

namespace Extensions
{
	bool IsDBCS(char TestChar)
	{
		if (TestChar < 0)return true;
		return false;
	}
	size_t FindDBCS(const char* TestStr)
	{
		for (size_t Count{}; Count < strlen(TestStr); Count += SINGLEBYTE)
		{
			if (IsDBCS(TestStr[Count]))return Count;
		}
		return Extensions::npos;
	}
	bool IsNum(char TestChar)
	{
		if (IsDBCS(TestChar))return false;
		char Get[2]{};
		Get[0] = TestChar;
		Get[1] = '\0';
		if (strspn(Get, "0123456789") < strlen(Get))return false;
		else return true;
	}
	bool IsValue(const char* Value)
	{
		if (Extensions::FindDBCS(Value) != Extensions::npos)return false;
		char Minus[2]{}, ExponentialMinus[2]{}, GetValue[Extensions::BufferSize]{}, GetExponentialValue[Extensions::BufferSize]{};
		bool GetSymbol{}, GetNum{}, GetDecimalPoint{}, GetExponential{}, GetExponentialSymbol{}, GetExponentialNum{};
		for (size_t Count{}; Count < strlen(Value); Count += SINGLEBYTE)
		{
			if (Value[Count] == '+')
			{
				if (GetExponential == false)
				{
					if (GetNum || GetDecimalPoint)return false;
					GetSymbol = true;
				}
				else {
					if (GetExponentialNum)return false;
					GetExponentialSymbol = true;
				}
			}
			else if (Value[Count] == '-') {
				if (GetExponential == false)
				{
					if (GetNum || GetDecimalPoint)return false;
#if defined(_WIN32) || defined(_WIN64)
					if (strlen(Minus) == 0)strcpy_s(Minus, sizeof(Minus), "-");
					else strcpy_s(Minus, sizeof(Minus), "");
#else
					if (strlen(Minus) == 0)strcpy(Minus, "-");
					else strcpy(Minus, "");
#endif
					GetSymbol = true;
				}
				else {
					if (GetExponentialNum)return false;
#if defined(_WIN32) || defined(_WIN64)
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
				else return false;
			}
			else if (Value[Count] == '.') {
				if (GetExponential == false)
				{
					if (GetDecimalPoint)return false;
					GetDecimalPoint = true;
					GetValue[strlen(GetValue)] = Value[Count];
				}
				else return false;
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
			else return false;
		}
		if (GetNum == false)return false;
		if (GetExponential && GetExponentialNum == false)return false;
		return true;
	}
	void StrClear(char* Src, size_t Size)
	{
		for (size_t Count{}; Count < Size - 1; Count++) { Src[Count] = '\0'; };
	}
	void EraseSpace(const char* Str1, char* Str2, size_t Size)
	{
		char Buffer[16]{};
		Extensions::StrClear(Str2, Size);
		for (size_t Count{}; Count < strlen(Str1);)
		{
			Extensions::StrClear(Buffer, sizeof(Buffer));
			if (Extensions::IsDBCS(Str1[Count]) == false)
			{
				for (size_t BCount{}; BCount < SINGLEBYTE; BCount++) { Buffer[BCount] = Str1[Count + BCount]; };
				Buffer[SINGLEBYTE] = '\0';
				Count += SINGLEBYTE;
			}
			else {
				for (size_t BCount{}; BCount < MULTIBYTE; BCount++) { Buffer[BCount] = Str1[Count + BCount]; };
				Buffer[MULTIBYTE] = '\0';
				Count += MULTIBYTE;
			}
			if (strcmp(Buffer, " ") != 0 && strcmp(Buffer, "@") != 0)
			{
#if defined(_WIN32) || defined(_WIN64)
				strcat_s(Str2, Size, Buffer);
#else
				strcat(Str2, Buffer);
#endif
				if (strlen(Str2) >= Size - 1)return;
			}
		}
	}
	size_t MBStrlen(const char* Str)
	{
		size_t Return{};
		for (size_t Count{}; Count < strlen(Str);)
		{
			if (Extensions::IsDBCS(Str[Count]) == false)Count += SINGLEBYTE;
			else Count += MULTIBYTE;
			Return++;
		}
		return Return;
	}
	void Substr(char* Buffer, size_t Size, const char* Str, size_t Start, size_t Num)
	{
		Extensions::StrClear(Buffer, Size);
		if (Start >= strlen(Str) || Num == 0 || Size <= 1)return;
		for (size_t Count{}; Count < Num; Count++)
		{
			if (Start + Count >= strlen(Str) || Count >= Size - 1)break;
			Buffer[Count] = Str[Start + Count];
		}
		Buffer[strlen(Buffer)] = '\0';
		return;
	}
	void MBSubstr(char* Buffer, size_t Size, const char* Str, size_t Start, size_t Num)
	{
		Extensions::StrClear(Buffer, Size);
		if (Start >= strlen(Str) || Num == 0 || Size <= 1)return;
		for (size_t Count{}, Count2{}, Count3{}; Count2 < Num; Count2++)
		{
			if (Extensions::IsDBCS(Str[Start + Count]) == false)
			{
				for (Count3 = 0; Count3 < SINGLEBYTE; Count3++)
				{
					if (Start + Count + Count3 >= strlen(Str) || Count + Count3 >= Size - 1)break;
					Buffer[Count + Count3] = Str[Start + Count + Count3];
				}
				Count += SINGLEBYTE;
			}
			else {
				for (Count3 = 0; Count3 < MULTIBYTE; Count3++)
				{
					if (Start + Count + Count3 >= strlen(Str) || Count + Count3 >= Size - 1)break;
					Buffer[Count + Count3] = Str[Start + Count + Count3];
				}
				Count += MULTIBYTE;
			}
		}
		Buffer[strlen(Buffer)] = '\0';
		return;
	}
	void ToUpper(char* Buffer, size_t Size)
	{
		for (size_t Count{}; Count < strlen(Buffer);)
		{
			if (Extensions::IsDBCS(Buffer[Count]) == false)
			{
				Buffer[Count] = toupper(Buffer[Count]);
				Count += SINGLEBYTE;
			}
			else Count += MULTIBYTE;
		}
		return;
	}
	void ToLower(char* Buffer, size_t Size)
	{
		for (size_t Count{}; Count < strlen(Buffer);)
		{
			if (Extensions::IsDBCS(Buffer[Count]) == false)
			{
				Buffer[Count] = tolower(Buffer[Count]);
				Count += SINGLEBYTE;
			}
			else Count += MULTIBYTE;
		}
		return;
	}
	void SwapCase(char* Buffer, size_t Size)
	{
		for (size_t Count{}; Count < strlen(Buffer);)
		{
			if (Extensions::IsDBCS(Buffer[Count]) == false)
			{
				if (isupper(Buffer[Count]))Buffer[Count] = tolower(Buffer[Count]);
				else Buffer[Count] = toupper(Buffer[Count]);
				Count += SINGLEBYTE;
			}
			else Count += MULTIBYTE;
		}
		return;
	}
	size_t StrFind(const char* Src, const char* Find)
	{
		char Buffer[Extensions::BufferSize]{};
		for (size_t Count{}; Count < strlen(Src);)
		{
			Extensions::StrClear(Buffer, sizeof(Buffer));
			if (Extensions::IsDBCS(Src[Count]) == false)
			{
				Extensions::MBSubstr(Buffer, sizeof(Buffer), Src, Count, Extensions::MBStrlen(Find));
				if (strcmp(Buffer, Find) == 0)return Count;
				Count += SINGLEBYTE;
			}
			else {
				Extensions::MBSubstr(Buffer, sizeof(Buffer), Src, Count, Extensions::MBStrlen(Find));
				if (strcmp(Buffer, Find) == 0)return Count;
				Count += MULTIBYTE;
			}
		}
		return Extensions::npos;
	}
	size_t StrCaseFind(const char* Src, const char* Find, size_t Find_Size)
	{
		char Buffer[Extensions::BufferSize]{};
		char LSrc[Extensions::BufferSize]{};
		char LFind[Extensions::BufferSize]{};
		strcpy_s(LSrc, sizeof(LSrc), Src);
		strcpy_s(LFind, sizeof(LFind), Find);
		ToLower(LSrc, sizeof(LSrc));
		ToLower(LFind, Find_Size);
		for (size_t Count{}; Count < strlen(LSrc);)
		{
			Extensions::StrClear(Buffer, sizeof(Buffer));
			if (Extensions::IsDBCS(LSrc[Count]) == false)
			{
				Extensions::MBSubstr(Buffer, sizeof(Buffer), LSrc, Count, Extensions::MBStrlen(LFind));
				if (strcmp(Buffer, LFind) == 0)return Count;
				Count += SINGLEBYTE;
			}
			else {
				Extensions::MBSubstr(Buffer, sizeof(Buffer), LSrc, Count, Extensions::MBStrlen(LFind));
				if (strcmp(Buffer, LFind) == 0)return Count;
				Count += MULTIBYTE;
			}
			
		}
		return Extensions::npos;
	}
}