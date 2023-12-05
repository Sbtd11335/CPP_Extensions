#include"Common.hpp"

namespace Extensions {
	bool IsDBCS(char TestChar) { if (TestChar < 0)return true; return false; }
	int64_t FindDBCS(const char* TestStr)
	{
		for (__int64 Count{}; Count < strlen(TestStr); Count += ET_SINGLEBYTE)
		{
			if (IsDBCS(TestStr[Count]))return Count;
		}
		return -1;
	}
	bool IsNum(char TestChar) { if (TestChar >= '0' && TestChar <= '9')return true; return false; }
	bool IsAllNum(const char* TestStr)
	{
		if (FindDBCS(TestStr) >= 0)return false;
		bool GetNum{};
		bool GetDot{};
		for (size_t Count{}; Count < strlen(TestStr); Count += ET_SINGLEBYTE)
		{
			if (IsNum(TestStr[Count]) == false)
			{
				if (TestStr[Count] == '+' || TestStr[Count] == '-') { if (GetNum)return false; }
				else if (TestStr[Count] == '.')
				{
					if (GetDot == false)
					{
						if (GetNum == false)return false;
						GetDot = true;
					}
					else return false;
				}
				else return false;
			}
			else {
				GetNum = true;
			}

		}

		if (GetNum == false)return false;
		return true;
	}
	int64_t StrFind(const char* Str1, const char* Str2)
	{
		std::string str1{ Str1 }, str2{ Str2 };
		size_t Count{};
		do {
			if (IsDBCS(str1[Count]) == false)
			{
				if (isupper(str1[Count]))
				{
					str1.erase(Count, ET_SINGLEBYTE);
					str1.insert(Count, std::string(1, tolower(Str1[Count])));
				}
				Count += ET_SINGLEBYTE;
			}
			else Count += ET_MULTIBYTE;
		} while (Count < str1.length());
		Count = 0;
		do {
			if (IsDBCS(str2[Count]) == false)
			{
				if (isupper(str2[Count]))
				{
					str2.erase(Count, ET_SINGLEBYTE);
					str2.insert(Count, std::string(1, tolower(Str2[Count])));
				}
				Count += ET_SINGLEBYTE;
			}
			else Count += ET_MULTIBYTE;
		} while (Count < str2.length());
		return str1.find(str2);
	}
	std::string EraceSpace(const char* Str)
	{
		std::string Return{};
		size_t Count{};
		do {
			if (IsDBCS(Str[Count]) == false)
			{
				if (std::string(Str).substr(Count, ET_SINGLEBYTE) != " ")Return.append(std::string(Str).substr(Count, ET_SINGLEBYTE));
				Count += ET_SINGLEBYTE;
			}
			else {
				if (std::string(Str).substr(Count, ET_MULTIBYTE) != "@")Return.append(std::string(Str).substr(Count, ET_MULTIBYTE));
				Count += ET_MULTIBYTE;
			}
		} while (Count < strlen(Str));
		return Return;
	}

	template<> std::string catos(const char* Str)
	{
		if (FindDBCS(EraceSpace(Str).c_str()) >= 0 || IsAllNum(EraceSpace(Str).c_str()) == false)return "0.0";

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
		return Return;
	}
	template<> float catos(const char* Str) { return atof(catos<std::string>(Str).c_str()); }
	template<> double catos(const char* Str) { return atof(catos<std::string>(Str).c_str()); }
	template<> int catos(const char* Str) { return atoi(catos<std::string>(Str).c_str()); }
	template<> long long catos(const char* Str) { return atoll(catos<std::string>(Str).c_str()); }
	//etc Common.hpp
}//Extensions