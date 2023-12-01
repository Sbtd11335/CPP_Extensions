#include "Common.h"

namespace Extensions {
	bool IsDBCS(char TestChar) { if (TestChar < 0)return true; return false; }
	int64_t FindDBCS(const char* TestStr)
	{
		for (size_t Count = 0; Count < strlen(TestStr); Count += ET_SINGLEBYTE) { if (IsDBCS(TestStr[Count]))return Count; }
		return -1;
	}
	bool IsNum(char TestChar) { if (TestChar >= '0' && TestChar < '9')return true; return false; }
	bool IsAllNum(const char* TestStr)
	{
		if (FindDBCS(TestStr) >= 0)return false;
		for (size_t Count = 0; Count < strlen(TestStr); Count++) { if (IsNum(TestStr[Count]))return true; }
		return false;
	}

	std::string ssubstr(std::string src, size_t _Off, size_t _Count, int8_t Mode)
	{
		switch (Mode)
		{
		default: case ET_SUBSTRMODE_DEFAULT: return src.substr(_Off, _Count); break;
		case ET_SUBSTRMODE_DB:
		{
			std::string Return{};
			size_t SCount{ _Off }, SCountT{ _Off };
			do {
				if (SCount >= src.length())break;
				if (IsDBCS(src[SCount]) == false)
				{
					Return.append(std::string(1, src[SCount]));
					SCount += ET_SINGLEBYTE;
				}
				else {
					Return.append(src.substr(SCount, ET_DOUBLEBYTE));
					SCount += ET_DOUBLEBYTE;
				}
				SCountT++;
			} while (SCountT - _Off < _Count);
			return Return;
		}
			break;
		}
	}
	std::string ssplit(std::string src, char del, size_t item)
	{
		std::string Return{};
		size_t Count{};
		do {

			Count++;
		} while (Count < src.length());


		return "";
	}
}//Extensions