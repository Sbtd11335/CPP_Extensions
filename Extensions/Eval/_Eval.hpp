#include "../Eval.hpp"

//Extensions::EasyEval
template<typename Type>Type Extensions::EasyEval(const char* Formula)
{
	if (Extensions::FindDBCS(Formula) != Extensions::npos)return Type(0.0);
	char _Formula[Extensions::BufferSize]{}, _Value[Extensions::BufferSize]{};
	bool GetNum{}, GetExponential{}, GetExponentialNum{};
	std::vector<Type>GetValue;
	std::vector<short>GetSymbol;
	std::vector<bool>MinusCheck;
	std::vector<size_t>MinusCount;
#if defined(_MSC_VER)
	strcpy_s(_Formula, sizeof(_Formula), Formula);
#else
	strcpy(_Formula, Formula);
#endif
	Extensions::EraseSpace(_Formula, sizeof(_Formula));
	if (strlen(_Formula) == 0)return Type(0.0);
	for (size_t Count{}, Count2{}; Count < strlen(_Formula); Count++)
	{
		if (_Formula[Count] == '+' || _Formula[Count] == '-' || _Formula[Count] == '*' || _Formula[Count] == '/' || _Formula[Count] == '%' || _Formula[Count] == '^')
		{
			if (GetNum == false)
			{
				_Value[Count2] = _Formula[Count];
				Count2++;
			}
			else {
				if (GetExponential == false)
				{
					//Save
					if (_Value[strlen(_Value) - 1] == '\\')
					{
						Extensions::EraseChar(_Value, sizeof(_Value), "\\");
						MinusCheck.push_back(true);
					}
					else MinusCheck.push_back(false);
					if (GetValue.size() == 0)
					{
						GetValue.push_back(Extensions::ToValue<Type>(_Value));
						MinusCount.push_back(Extensions::CharCount(_Value, '-'));
						GetSymbol.push_back(-1);
					}
					else {
						GetValue.push_back(Extensions::ToValue<Type>(&_Value[1]));
						MinusCount.push_back(Extensions::CharCount(&_Value[1], '-'));
						if (_Value[0] == '+')GetSymbol.push_back(0);
						else if (_Value[0] == '-')GetSymbol.push_back(1);
						else if (_Value[0] == '*')GetSymbol.push_back(2);
						else if (_Value[0] == '/')GetSymbol.push_back(3);
						else if (_Value[0] == '%')GetSymbol.push_back(4);
						else if (_Value[0] == '^')GetSymbol.push_back(5);
					}

					Count2 = 0;
					GetNum = false;
					GetExponential = false;
					GetExponentialNum = false;
					Extensions::StrClear(_Value, sizeof(_Value));
					_Value[Count2] = _Formula[Count];
					Count2++;
				}
				else {
					if (GetExponentialNum == false)
					{
						_Value[Count2] = _Formula[Count];
						Count2++;
					}
					else {
						//Save
						if (_Value[strlen(_Value) - 1] == '\\')
						{
							Extensions::EraseChar(_Value, sizeof(_Value), "\\");
							MinusCheck.push_back(true);
						}
						else MinusCheck.push_back(false);
						if (GetValue.size() == 0)
						{
							GetValue.push_back(Extensions::ToValue<Type>(_Value));
							MinusCount.push_back(Extensions::CharCount(_Value, '-'));
							GetSymbol.push_back(-1);
						}
						else {
							GetValue.push_back(Extensions::ToValue<Type>(&_Value[1]));
							MinusCount.push_back(Extensions::CharCount(&_Value[1], '-'));
							if (_Value[0] == '+')GetSymbol.push_back(0);
							else if (_Value[0] == '-')GetSymbol.push_back(1);
							else if (_Value[0] == '*')GetSymbol.push_back(2);
							else if (_Value[0] == '/')GetSymbol.push_back(3);
							else if (_Value[0] == '%')GetSymbol.push_back(4);
							else if (_Value[0] == '^')GetSymbol.push_back(5);
						}
						Count2 = 0;
						GetNum = false;
						GetExponential = false;
						GetExponentialNum = false;
						Extensions::StrClear(_Value, sizeof(_Value));
						_Value[Count2] = _Formula[Count];
						Count2++;
					}
				}
			}
		}
		else if (Extensions::IsNum(_Formula[Count]))
		{
			if (GetExponential == false)
			{
				_Value[Count2] = _Formula[Count];
				Count2++;
				GetNum = true;
			}
			else {
				_Value[Count2] = _Formula[Count];
				Count2++;
				GetExponentialNum = true;
			}
		}
		else if (_Formula[Count] == 'e' || _Formula[Count] == 'E')
		{
			_Value[Count2] = _Formula[Count];
			Count2++;
			GetExponential = true;
		}
		else
		{
			_Value[Count2] = _Formula[Count];
			Count2++;
		}
	}
	if (strlen(_Value) > 0)
	{
		//Save
		if (_Value[strlen(_Value) - 1] == '\\')
		{
			Extensions::EraseChar(_Value, sizeof(_Value), "\\");
			MinusCheck.push_back(true);
		}
		else MinusCheck.push_back(false);
		if (GetValue.size() == 0)
		{
			GetValue.push_back(Extensions::ToValue<Type>(_Value));
			MinusCount.push_back(Extensions::CharCount(_Value, '-'));
			GetSymbol.push_back(-1);
		}
		else {
			GetValue.push_back(Extensions::ToValue<Type>(&_Value[1]));
			MinusCount.push_back(Extensions::CharCount(&_Value[1], '-'));
			if (_Value[0] == '+')GetSymbol.push_back(0);
			else if (_Value[0] == '-')GetSymbol.push_back(1);
			else if (_Value[0] == '*')GetSymbol.push_back(2);
			else if (_Value[0] == '/')GetSymbol.push_back(3);
			else if (_Value[0] == '%')GetSymbol.push_back(4);
			else if (_Value[0] == '^')GetSymbol.push_back(5);
		}
	}
	//Calculation
	for (size_t Count = GetValue.size() - 1; Count >= 1; Count--)
	{
		if (Count == Extensions::npos)break;

		if (GetSymbol[Count] == 5)
		{
			if (MinusCheck[Count - 1] == false)
			{
				if (GetValue[Count - 1] >= 0)GetValue[Count - 1] = pow(abs(GetValue[Count - 1]), GetValue[Count]);
				else GetValue[Count - 1] = -pow(abs(GetValue[Count - 1]), GetValue[Count]);
			}
			else {
				if (MinusCount[Count - 1] % 2 == 0)GetValue[Count - 1] = -pow(-abs(GetValue[Count - 1]), GetValue[Count]);
				else GetValue[Count - 1] = pow(-abs(GetValue[Count - 1]), GetValue[Count]);
			}

			GetValue.erase(GetValue.begin() + Count);
			GetSymbol.erase(GetSymbol.begin() + Count);
			MinusCheck.erase(MinusCheck.begin() + Count);
			MinusCount.erase(MinusCount.begin() + Count);
			Count = GetValue.size();
		}
	}
	for (size_t Count = 0; Count < GetValue.size(); Count++)
	{
		if (GetSymbol[Count] >= 2 && GetSymbol[Count] <= 4)
		{
			if (GetSymbol[Count] == 2)GetValue[Count - 1] = GetValue[Count - 1] * GetValue[Count];
			if (GetSymbol[Count] == 3)GetValue[Count - 1] = GetValue[Count - 1] / GetValue[Count];
			if (GetSymbol[Count] == 4)GetValue[Count - 1] = (long long)GetValue[Count - 1] % (long long)GetValue[Count];

			GetValue.erase(GetValue.begin() + Count);
			GetSymbol.erase(GetSymbol.begin() + Count);
			MinusCheck.erase(MinusCheck.begin() + Count);
			MinusCount.erase(MinusCount.begin() + Count);
			Count = 0;
			continue;
		}
	}
	for (size_t Count = 0; Count < GetValue.size(); Count++)
	{
		if (GetSymbol[Count] == 0 || GetSymbol[Count] == 1)
		{
			if (GetSymbol[Count] == 0)GetValue[Count - 1] = GetValue[Count - 1] + GetValue[Count];
			if (GetSymbol[Count] == 1)GetValue[Count - 1] = GetValue[Count - 1] - GetValue[Count];
			GetValue.erase(GetValue.begin() + Count);
			GetSymbol.erase(GetSymbol.begin() + Count);
			MinusCheck.erase(MinusCheck.begin() + Count);
			MinusCount.erase(MinusCount.begin() + Count);
			Count = 0;
			continue;
		}
	}
	if (GetValue.size() > 0)return GetValue[0];
	return Type(0.0);
}

template<typename Type>Type Extensions::SimpleEval(const char* Formula, size_t SetPrecision)
{
	if (Extensions::FindDBCS(Formula) != Extensions::npos || Extensions::CharCount(Formula, '(') != Extensions::CharCount(Formula, ')'))return Type(0.0);
	if (Extensions::IsValue(Formula))return Extensions::ToValue<Type>(Formula);
	char _Formula[Extensions::BufferSize]{}, GetFormula[Extensions::BufferSize]{}, GetFunc[Extensions::BufferSize]{}, Func[Extensions::BufferSize]{};
	Type Result{};
	std::vector<std::string>Formulas, Functions;
	std::vector<size_t>Position;
	size_t BCount{}, BPosition{};
	int Position_Plus{};

#if defined(_MSC_VER)
	strcpy_s(_Formula, sizeof(_Formula), Formula);
#else
	strcpy(_Formula, Formula);
#endif
	Extensions::EraseSpace(_Formula, sizeof(_Formula));
	if (strlen(_Formula) == 0)return Type(0.0);
	if (Extensions::IsValue(_Formula))return Extensions::ToValue<Type>(_Formula);
	Type* FuncResult = new Type[Extensions::BufferSize]{};

	while (true)
	{
		BCount = 0;
		BPosition = Extensions::npos;
		Extensions::StrClear(GetFormula, sizeof(GetFormula));
		Extensions::StrClear(GetFunc, sizeof(GetFunc));
		Extensions::StrClear(Func, sizeof(Func));
		for (size_t Count{}, FCount{}, SCount{}; Count < strlen(_Formula); Count++)
		{
			if (_Formula[Count] == '(')
			{
#if defined(_MSC_VER)
				strcpy_s(Func, sizeof(Func), GetFunc);
#else
				strcpy(Func, GetFunc);
#endif
				Extensions::StrClear(GetFunc, sizeof(GetFunc));
				Extensions::StrClear(GetFormula, sizeof(GetFormula));
				SCount = 0;
				FCount = 0;
				BPosition = Count;
				BCount++;
				continue;
			}
			else if (_Formula[Count] == ')')
			{
				if (BPosition != Extensions::npos)
				{
					//Save
					Formulas.push_back(std::string(GetFormula));
					Functions.push_back(std::string(Func));
					Position.push_back(BPosition - strlen(Func));
					BPosition = Extensions::npos;
				}
				Extensions::StrClear(GetFormula, sizeof(GetFormula));
				Extensions::StrClear(GetFunc, sizeof(GetFunc));
				Extensions::StrClear(Func, sizeof(Func));
				SCount = 0;
				FCount = 0;
				continue;
			}
			else {
				GetFunc[FCount++] = _Formula[Count];
				GetFormula[SCount++] = _Formula[Count];
			}

			if (_Formula[Count] == '+' || _Formula[Count] == '-' || _Formula[Count] == '*' || _Formula[Count] == '/' || _Formula[Count] == '%' || _Formula[Count] == '^' || _Formula[Count] == '.' || _Formula[Count] == ',' || _Formula[Count] == '\\')
			{
				Extensions::StrClear(GetFunc, sizeof(GetFunc));
				FCount = 0;
			}
		}
		//Calculation
		if (Formulas.size() > 0)
		{
			Position_Plus = 0;
			for (size_t Count{}; Count < Formulas.size(); Count++)
			{
				if (Functions[Count].length() > 0)
				{
					Extensions::StrErase(_Formula, sizeof(_Formula), Position[Count] + Position_Plus, Functions[Count].length() + Formulas[Count].length() + 2);
					//Function
					if (Extensions::StrCaseCmp(Functions[Count].c_str(), "abs") == 0)Result = abs(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "avg") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						for (size_t CCount{}; CCount < BPosition; CCount++)
						{
							if (CCount > 0)(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', CCount);
							Result += Extensions::SimpleEval<Type>(Func);
						}
						if (BPosition == 0)Result = Type(0.0);
						else Result /= BPosition;
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "ceil") == 0)Result = ceil(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "exp") == 0)Result = exp(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "floor") == 0)Result = floor(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "hypot") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						if (BPosition < 2)Result = Type(0.0);
						else {
							FuncResult[0] = Extensions::EasyEval<Type>(Func);
							(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 1);
							Result = hypot(FuncResult[0], Extensions::EasyEval<Type>(Func));
						}
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "ln") == 0)Result = log(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "log") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						if (BPosition == 0)Result = Type(0.0);
						else if (BPosition == 1)Result = log(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
						else {
							FuncResult[0] = Extensions::EasyEval<Type>(Func);
							(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 1);
							Result = log(Extensions::EasyEval<Type>(Func)) / log(FuncResult[0]);
						}
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "log10") == 0)Result = log10(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "pow") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						if (BPosition < 2)Result = Type(0.0);
						else {
							FuncResult[0] = Extensions::EasyEval<Type>(Func);
							(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 1);
							Result = pow(FuncResult[0], Extensions::EasyEval<Type>(Func));
						}
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "sqrt") == 0)Result = sqrt(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "sum") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						for (size_t CCount{}; CCount < BPosition; CCount++)
						{
							if (CCount > 0)(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', CCount);
							Result += Extensions::SimpleEval<Type>(Func);
						}
						if (BPosition == 0)Result = Type(0.0);
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "acos") == 0)Result = acos(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "asin") == 0)Result = asin(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "atan") == 0)Result = atan(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "atan2") == 0)
					{
						BPosition = Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 0);
						Result = 0;
						if (BPosition < 2)Result = Type(0.0);
						else {
							FuncResult[0] = Extensions::EasyEval<Type>(Func);
							(void)Extensions::StrSplit(Func, sizeof(Func), Formulas[Count].c_str(), ',', 1);
							Result = atan2(FuncResult[0], Extensions::EasyEval<Type>(Func));
						}
					}
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "cos") == 0)Result = cos(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "cosh") == 0)Result = cosh(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "sin") == 0)Result = sin(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "sinh") == 0)Result = sinh(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "tan") == 0)Result = tan(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else if (Extensions::StrCaseCmp(Functions[Count].c_str(), "tanh") == 0)Result = tanh(Extensions::EasyEval<Type>(Formulas[Count].c_str()));
					else Result = Extensions::EasyEval<Type>(Formulas[Count].c_str());
				}
				else {
					Extensions::StrErase(_Formula, sizeof(_Formula), Position[Count] + Position_Plus, Formulas[Count].length() + 2);
					Result = Extensions::EasyEval<Type>(Formulas[Count].c_str());
				}
				std::stringstream sResult{};
				sResult << std::setprecision(SetPrecision) << Result;
				
				if (Result >= 0)
				{
					Extensions::StrInsert(_Formula, sizeof(_Formula), sResult.str().c_str(), Position[Count] + Position_Plus);
					if (Functions[Count].length() == 0)Position_Plus += sResult.str().length() - Formulas[Count].length() - 2;
					else Position_Plus += sResult.str().length() - Functions[Count].length() - Formulas[Count].length() - 2;

				}
				else {
#if defined(_MSC_VER)
					sprintf_s(GetFunc, sizeof(GetFunc), "%s\\", sResult.str().c_str());
#else
					sprintf(GetFunc, "%s\\", sResult.str().c_str());
#endif
					Extensions::StrInsert(_Formula, sizeof(_Formula), GetFunc, Position[Count] + Position_Plus);
					if (Functions[Count].length() == 0)Position_Plus += sResult.str().length() - Formulas[Count].length() - 1;
					else Position_Plus += sResult.str().length() - Functions[Count].length() - Formulas[Count].length() + 1;
				}
			}
			BCount -= Formulas.size();
			if (BCount > 0)
			{
				Formulas.clear(); Formulas.shrink_to_fit();
				Functions.clear(); Functions.shrink_to_fit();
				Position.clear(); Position.shrink_to_fit();
			}
		}
		
		if (BCount <= 0)break;
	}
	delete[]FuncResult;

	return Extensions::EasyEval<Type>(_Formula);
}

//class Eval
template<typename Type>Extensions::Eval<Type>::Eval()
{
	Extensions::Eval<Type>::AppendConstant("\\PI", "3.141592653589793238462643");
	Extensions::Eval<Type>::AppendConstant("e", "2.718281828459045235360287");
	return;
}
template<typename Type>size_t Extensions::Eval<Type>::FindConstantByName(const char* Name)
{
	for (size_t Count{}; Count < ConstantNames.size(); Count++)
	{
		if (ConstantNames[Count][0] == '\\')
		{
			if (Extensions::StrCaseCmp(Name, &ConstantNames[Count][1]) == 0)return Count;
		}
		else {
			if (strcmp(Name, ConstantNames[Count]) == 0)return Count;
		}
	}
	return Extensions::npos;
}
template<typename Type>size_t Extensions::Eval<Type>::FindVariableByName(const char* Name)
{
	for (size_t Count{}; Count < VariableNames.size(); Count++)
	{
		if (VariableNames[Count][0] == '\\')
		{
			if (Extensions::StrCaseCmp(Name, &VariableNames[Count][1]) == 0)return Count;
		}
		else {
			if (strcmp(Name, VariableNames[Count]) == 0)return Count;
		}
	}
	return Extensions::npos;
}
template<typename Type>Type Extensions::Eval<Type>::GetConstantValueByName(const char* Name)
{
	for (size_t Count{}; Count < ConstantNames.size(); Count++)
	{
		if (ConstantNames[Count][0] == '\\')
		{
			if (Extensions::StrCaseCmp(Name, &ConstantNames[Count][1]) == 0)return ConstantValues[Count];
		}
		else {
			if (strcmp(Name, ConstantNames[Count]) == 0)return ConstantValues[Count];
		}
	}
	return Extensions::npos;
}
template<typename Type>Type Extensions::Eval<Type>::GetVariableValueByName(const char* Name)
{
	for (size_t Count{}; Count < VariableNames.size(); Count++)
	{
		if (VariableNames[Count][0] == '\\')
		{
			if (Extensions::StrCaseCmp(Name, &VariableNames[Count][1]) == 0)return VariableValues[Count];
		}
		else {
			if (strcmp(Name, VariableNames[Count]) == 0)return VariableValues[Count];
		}
	}
	return Extensions::npos;
}

template<typename Type>size_t Extensions::Eval<Type>::AppendConstant(const char* Name, Type Value)
{
	if (FindConstantByName(Name) != Extensions::npos || FindVariableByName(Name) != Extensions::npos)return Extensions::npos;
	ConstantNames.push_back(Name);
	ConstantValues.push_back(Value);
	return ConstantNames.size() - 1;
}
template<typename Type>size_t Extensions::Eval<Type>::AppendConstant(const char* Name, char* Value)
{

	return ConstantNames.size() - 1;
}