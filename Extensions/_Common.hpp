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
	char Minus[2]{}, ExponentialMinus[2]{}, GetValue[Extensions::BufferSize]{}, GetExponentialValue[Extensions::BufferSize]{}, ReturnValue[Extensions::BufferSize]{}, Str[Extensions::BufferSize]{};
	bool GetSymbol{}, GetNum{}, GetDecimalPoint{}, GetExponential{}, GetExponentialSymbol{}, GetExponentialNum{}, GetStr{};
	for (size_t Count{}; Count < strlen(Value); Count += SINGLEBYTE)
	{
		if (GetStr == false)
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
				if (GetNum == false)
				{
					GetStr = true;
					Str[strlen(Str)] = Value[Count];
				}
				else {
					if (GetExponential == false)GetExponential = true;
					else return Return;
				}
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
			else {
				if (GetNum || GetDecimalPoint)return Return;
				GetStr = true;
				Str[strlen(Str)] = Value[Count];
			}
		}
		else {
			if (GetStr == false && Value[Count] == '+' || Value[Count] == '-')return Return;
			Str[strlen(Str)] = Value[Count];
		}
	}

	if (GetStr == false)
	{
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
	}
	else {
		//Str
		if (Extensions::StrCaseCmp(Str, "inf") == 0 || Extensions::StrCaseCmp(Str, "infinity") == 0)
		{
			if (strlen(Minus) == 0)return std::numeric_limits<Type>::infinity();
			else return -std::numeric_limits<Type>::infinity();
		}
	}

	return Return;
}