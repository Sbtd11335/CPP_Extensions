#include "Common.hpp"
#include <math.h>
#include <iostream>
#include <vector>
#include <iomanip>

#ifndef EXTENSIONS_EVAL_HPP_INCLUDED
#	define EXTENSIONS_EVAL_HPP_INCLUDED

#	define EVAL_DEBUG


namespace Extensions {
	namespace Eval{
		template<typename Type>Type SimpleEval(const char* Formula);
	}//Eval
}//Extensions


//Extensions::Eval::SimpleEval
template<typename Type>Type Extensions::Eval::SimpleEval(const char* Formula)
{
	Type Result{};
	if (FindDBCS(EraceSpace(Formula).c_str()) >= 0 || strlen(EraceSpace(Formula).c_str()) == 0)return Result;
	if (IsAllNum(EraceSpace(Formula).c_str()))return catos<Type>(EraceSpace(Formula).c_str());
	std::string FORMULA{ EraceSpace(Formula).c_str() }, BSave{}, VSave{};
	std::vector<Type>Value;
	std::vector<int>Rule;
	uint8_t Rule_Save{};

	size_t BCount{}, BCount_Save{};
	bool GetNum{};

	FORMULA.insert(0, "("); FORMULA.append(")");
#ifdef EVAL_DEBUG
	std::cout << "Formula:" << FORMULA << std::endl;
#endif

	while (true)
	{
		//Get
		BCount = 0;
		BSave.clear();
		for (int64_t Count = FORMULA.length() - ET_SINGLEBYTE; Count >= 0; Count -= ET_SINGLEBYTE) {

			if (FORMULA[Count] == ')')
			{
				BSave.clear();
				BCount++;
			}
			else if (FORMULA[Count] == '(')
			{
				//calculation processing: BSave
				VSave.clear();
				GetNum = false;
				for (size_t Count2{}; Count2 < BSave.length(); Count2 += ET_SINGLEBYTE)
				{
					if (IsNum(BSave[Count2]) == false)
					{
						if (GetNum == false)
						{
							VSave.append(std::string(1, BSave[Count2]));
						}
						else {
							if (BSave[Count2] == '.')VSave.append(std::string(1, BSave[Count2]));
							else {
								if (VSave[0] == '+' || VSave[0] == '-')Rule_Save = 0;
								else if (VSave[0] == '*')Rule_Save = 1;
								else if (VSave[0] == '/')Rule_Save = 2;
								else if (VSave[0] == '%')Rule_Save = 3;
								else if (VSave[0] == '^')Rule_Save = 4;
								else Rule_Save = 0;
								//Save
								if (Value.size() == 0)Value.push_back(catos<Type>(VSave.c_str()));
								else {
									if (Rule_Save == 0)Value.push_back(catos<Type>(VSave.c_str()));
									else Value.push_back(catos<Type>(VSave.substr(ET_SINGLEBYTE, VSave.length() - ET_SINGLEBYTE).c_str()));
								}
								if (Rule.size() == 0)Rule.push_back(0);
								else Rule.push_back(Rule_Save);
								GetNum = false;
								VSave = std::string(1, BSave[Count2]);
							}
						}
					}
					else {
						VSave.append(std::string(1, BSave[Count2]));
						GetNum = true;
					}
				}
				if (VSave.length() > 0)
				{
					if (VSave[0] == '+' || VSave[0] == '-')Rule_Save = 0;
					else if (VSave[0] == '*')Rule_Save = 1;
					else if (VSave[0] == '/')Rule_Save = 2;
					else if (VSave[0] == '%')Rule_Save = 3;
					else if (VSave[0] == '^')Rule_Save = 4;
					else Rule_Save = 0;
					//Save
					if (Value.size() == 0)Value.push_back(catos<Type>(VSave.c_str()));
					else {
						if (Rule_Save == 0)Value.push_back(catos<Type>(VSave.c_str()));
						else Value.push_back(catos<Type>(VSave.substr(ET_SINGLEBYTE, VSave.length() - ET_SINGLEBYTE).c_str()));
					}
					Rule.push_back(Rule_Save);
					GetNum = false;
				}

				std::cout << "ŒŸo‚³‚ê‚½Ž®‚ÆŒvŽZ•û–@:" << std::endl;
				for (int Count2 = 0; Count2 < Value.size(); Count2++)
				{
					std::cout << Value[Count2] << "(" << Rule[Count2]<< ")" << std::endl;
				}
				//calculation
				//Rule:4
				for (int64_t Count2 = Value.size() - 1; Count2 >= 0; Count2--)
				{
					if (Rule[Count2] == 4)
					{
						Value[Count2 - 1] = pow(Value[Count2 - 1], Value[Count2]);
						Value.erase(Value.begin() + Count2);
						Rule.erase(Rule.begin() + Count2);
						Count2 = Value.size();
					}
				}
				//Rule:1,2,3
				for (int64_t Count2{}; Count2 < Value.size(); Count2++)
				{
					switch (Rule[Count2])
					{
					case 1:// *
						Value[Count2 - 1] = Value[Count2 - 1] * Value[Count2];
						Value.erase(Value.begin() + Count2);
						Rule.erase(Rule.begin() + Count2);

						Count2 = 0;
						break;
					case 2:// /
						Value[Count2 - 1] = Value[Count2 - 1] / Value[Count2];
						Value.erase(Value.begin() + Count2);
						Rule.erase(Rule.begin() + Count2);
						Count2 = 0;
						break;
					case 3:// /
						Value[Count2 - 1] = static_cast<int64_t>(Value[Count2 - 1]) % static_cast<int64_t>(Value[Count2]);
						Value.erase(Value.begin() + Count2);
						Rule.erase(Rule.begin() + Count2);
						Count2 = 0;
						break;
					}
				}
				//Rule:0
				for (int64_t Count2{1}; Count2 < Value.size(); Count2++)
				{
					if (Rule[Count2] == 0)
					{
						Value[Count2 - 1] = Value[Count2 - 1] + Value[Count2];
						Value.erase(Value.begin() + Count2);
						Rule.erase(Rule.begin() + Count2);
						Count2 = 1;
					}
				}

				std::cout << std::fixed  << "A." << Value[0] << std::endl;

				Value.clear(); Value.shrink_to_fit();
				Rule.clear(); Rule.shrink_to_fit();
			}
			else BSave.insert(0, std::string(1, FORMULA[Count]));
		}

		if (BCount <= 1)break;
	}
	return Result;
}



#endif