#ifndef EXTENSIONS_EVAL_HPP
#	define	EXTENSIONS_EVAL_HPP

#	include	"Common.hpp"
#	include <iostream>
#	include <math.h>
#	include <string>
#	include <sstream>
#	include <iomanip>
#include <cmath>

#include <iostream>
#include <limits>

namespace Extensions
{
	template<typename Type>Type EasyEval(const char* Formula);
	template<typename Type>Type SimpleEval(const char* Formula, size_t SetPrecision = 6);

	template<typename Type>class Eval {
	private:
		std::vector<const char*>ConstantNames;
		std::vector<Type>ConstantValues;

		std::vector<const char*>VariableNames;
		std::vector<char*>VariableValues;
		std::vector<bool>VariableValues_Indeterminate;
	public:
		Eval();

		size_t FindConstantByName(const char* Name);
		size_t FindVariableByName(const char* Name);
		Type GetConstantValueByName(const char* Name);
		Type GetVariableValueByName(const char* Name);

		size_t AppendConstant(const char* Name, Type Value);
		size_t AppendConstant(const char* Name, char* Value);
		size_t AppendConstant(const char* Name, const char* Value);
		size_t AppendVariable(const char* Name, Type Value);
		size_t AppendVariable(const char* Name, char* Value);
		size_t AppendVariable(const char* Name, const char* Value);
		size_t ChangeVariable(const char* Name, Type Value);
		size_t ChangeVariable(const char* Name, char* Value);
		size_t ChangeVariable(const char* Name, const char* Value);


		Type Calculation(const char* Formula, size_t SetPrecision = 6);
	};

}//namespace Extensions

#include "Eval/_Eval.hpp"
#endif