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
				if (GetValue[Count - 1] >= 0)
				{
					GetValue[Count - 1] = -pow(abs(GetValue[Count - 1]), GetValue[Count]);
				}
				else {
					GetValue[Count - 1] = pow(abs(GetValue[Count - 1]), GetValue[Count]);
				}
			}

			GetValue.erase(GetValue.begin() + Count);
			GetSymbol.erase(GetSymbol.begin() + Count);
			MinusCheck.erase(MinusCheck.begin() + Count);
			MinusCount.erase(MinusCount.begin() + Count);
			Count = GetValue.size() - 1;
			continue;
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

//Extensions::SimpleEval
template<typename Type>Type Extensions::SimpleEval(const char* Formula, size_t SetPrecision)
{
	if (Extensions::FindDBCS(Formula) != Extensions::npos)return Type(0.0);
	char _Formula[Extensions::BufferSize]{}, Process[Extensions::BufferSize]{}, Process2[Extensions::BufferSize]{}, Str[Extensions::BufferSize]{}, Func[Extensions::BufferSize]{}, Content[Extensions::BufferSize]{};
	size_t BCount{}, CNum{};
	Type Result{}, ContentResult[Extensions::BufferSize]{};
	bool BCheck{};
	bool BoostCheck{};
	//boost
#ifdef EXTENSIONS_BOOST_INCLUDED
	if (Extensions::StrCaseFind(typeid(Result).name(), "Boost", sizeof("Boost")))BoostCheck = true;
#endif
#if defined(_MSC_VER)
	strcpy_s(_Formula, sizeof(_Formula), Formula);
#else
	strcpy(_Formula, Formula);
#endif
	Extensions::EraseSpace(_Formula, sizeof(_Formula));
	if (strlen(_Formula) == 0)return Type(0.0);
	Extensions::StrInsert(_Formula, sizeof(_Formula), "(", 0);
	Extensions::StrInsert(_Formula, sizeof(_Formula), ")", strlen(_Formula));

	while(true)
	{
		Extensions::StrClear(Process, sizeof(Process));
		Extensions::StrClear(Str, sizeof(Str));
		BCount = 0;
		for (size_t Count{}, Count2{}; Count < strlen(_Formula); Count++)
		{
			if (_Formula[Count] == '(')
			{

#if defined(_MSC_VER)
				strcpy_s(Str, sizeof(Str), Process);
#else
				strcpy(Str, Process);
#endif
				Extensions::StrClear(Process, sizeof(Process));
				BCount++;
				Count2 = 0;
			}
			else if (_Formula[Count] == ')') {
				//printf("Debug:F:%s\t%zd, %zd\t", _Formula, Count - strlen(Process) - 1, strlen(Process) + 2);
				//Calc
				Extensions::StrClear(Func, sizeof(Func));
				for (size_t SCount = strlen(Str) - 1; SCount >= 0 && SCount != Extensions::npos; SCount--)
				{
					if (SCount == Extensions::npos || Str[SCount] == '+' || Str[SCount] == '-' || Str[SCount] == '*' || Str[SCount] == '/' || Str[SCount] == '%' || Str[SCount] == '^' || Str[SCount] == '.' || Str[SCount] == ',' || Str[SCount] == '\\')break;
					Extensions::StrInsert(Func, sizeof(Func), Str[SCount], 0);
				}
				Extensions::StrErase(_Formula, sizeof(_Formula), Count - strlen(Process) - 1 - strlen(Func), strlen(Process) + 2 + strlen(Func));
				//printf("(%s)\tStr:%s\n", Process, Func);
				Result = 0;
				//Func
				if (Extensions::StrCaseCmp(Func, "abs") == 0)Result = abs(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "avg") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					for (size_t CCount{}; CCount < CNum; CCount++)
					{
						if (CCount > 0)(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', CCount);
						Result += Extensions::SimpleEval<Type>(Content);
					}
					if (CNum == 0)Result = Type(0.0);
					else Result /= CNum;
				}
				else if (Extensions::StrCaseCmp(Func, "ceil") == 0)Result = ceil(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "exp") == 0)Result = exp(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "floor") == 0)Result = floor(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "hypot") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					if (CNum < 2)Result = Type(0.0);
					else {
						ContentResult[0] = Extensions::EasyEval<Type>(Content);
						(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', 1);
						Result = hypot(ContentResult[0], Extensions::EasyEval<Type>(Content));
					}
				}
				else if (Extensions::StrCaseCmp(Func, "ln") == 0)Result = log(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "log") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					if (CNum == 0)Result = Type(0.0);
					else if (CNum == 1)Result = log(Extensions::EasyEval<Type>(Process));
					else {
						ContentResult[0] = Extensions::EasyEval<Type>(Content);
						(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', 1);
						Result = log(Extensions::EasyEval<Type>(Content)) / log(ContentResult[0]);
					}
				}
				else if (Extensions::StrCaseCmp(Func, "log10") == 0)Result = log10(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "pow") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					if (CNum < 2)Result = Type(0.0);
					else {
						ContentResult[0] = Extensions::EasyEval<Type>(Content);
						(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', 1);
						Result = pow(ContentResult[0], Extensions::EasyEval<Type>(Content));
					}
				}
				else if (Extensions::StrCaseCmp(Func, "sqrt") == 0)Result = sqrt(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "sum") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					for (size_t CCount{}; CCount < CNum; CCount++)
					{
						if (CCount > 0)(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', CCount);
						Result += Extensions::SimpleEval<Type>(Content);
					}
					if (CNum == 0)Result = Type(0.0);
				}
				else if (Extensions::StrCaseCmp(Func, "acos") == 0)Result = acos(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "asin") == 0)Result = asin(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "atan") == 0)Result = atan(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "atan2") == 0)
				{
					CNum = Extensions::StrSplit(Content, sizeof(Content), Process, ',', 0);
					if (CNum < 2)Result = Type(0.0);
					else {
						ContentResult[0] = Extensions::EasyEval<Type>(Content);
						(void)Extensions::StrSplit(Content, sizeof(Content), Process, ',', 1);
						Result = atan2(ContentResult[0], Extensions::EasyEval<Type>(Content));
					}
				}
				else if (Extensions::StrCaseCmp(Func, "cos") == 0)Result = cos(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "cosh") == 0)Result = cosh(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "sin") == 0)Result = sin(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "sinh") == 0)Result = sinh(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "tan") == 0)Result = tan(Extensions::EasyEval<Type>(Process));
				else if (Extensions::StrCaseCmp(Func, "tanh") == 0)Result = tanh(Extensions::EasyEval<Type>(Process));
				else Result = Extensions::EasyEval<Type>(Process);
				std::stringstream sResult{};
				sResult << std::setprecision(SetPrecision) << Result;
				//printf("Debug:%s\n", sResult.str().c_str());
				if (Result >= 0)Extensions::StrInsert(_Formula, sizeof(_Formula), sResult.str().c_str(), Count - strlen(Process) - 1 - strlen(Func));
				else {
#if defined(_MSC_VER)
					sprintf_s(Content, sizeof(Content), "%s\\", sResult.str().c_str());
#else
					sprintf(Content, "%s\\", sResult.str().c_str());
#endif
					Extensions::StrInsert(_Formula, sizeof(_Formula), Content, Count - strlen(Process) - 1 - strlen(Func));
				}

				Extensions::StrClear(Process, sizeof(Process));
				Extensions::StrClear(Str, sizeof(Str));
				Count = 0;
				Count2 = 0;
				break;
			}
			else {
				Process[Count2] = _Formula[Count];
				Count2++;
			}
		}
		if (BCount <= 1)break;
	}
	return Type(Result);
}