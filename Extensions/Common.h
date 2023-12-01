#include <string.h>
#include <string>
#include <vector>

#ifndef EXTENSIONS_COMMON_H_INCLUDED
#	define EXTENSIONS_COMMON_H_INCLUDED

#define ET_SINGLEBYTE			strlen("0")
#define ET_DOUBLEBYTE			strlen("‚O")

#define ET_SUBSTRMODE_DEFAULT	0x00
#define ET_SUBSTRMODE_DB		0x01

namespace Extensions {
	bool IsDBCS(char TestChar);
	int64_t FindDBCS(const char* TestStr);
	bool IsNum(char TestChar);
	bool IsAllNum(const char* TestStr);
	std::string ssubstr(std::string src, size_t _Off, size_t _Count, int8_t Mode = ET_SUBSTRMODE_DEFAULT);
	std::string ssplit(std::string src, char del, size_t item = 0);
}//Extensions

#endif