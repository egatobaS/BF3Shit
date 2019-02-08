#include "main.h"

Menu::Menu()
{
	CurrentSubMenu = 0;
	isMenuOpened = false;
	SubIndex = -1;
}

Menu::~Menu()
{
}

int Menu::CreateSubMenu(std::string SubName)
{
	LastSubMenu.push_back(SubIndex);

	SubIndex++;

	SubTitles.push_back(SubName);

	int SubCount = SubIndex + 1;

	OptionCount.resize(SubCount);
	MaxScroll.resize(SubCount);
	SubMenuText.resize(SubCount);
	SubMenuDescription.resize(SubCount);
	CurrentScroll.resize(SubCount);
	OptionKind.resize(SubCount);

	BoolValue.resize(SubCount);
	BoolCall.resize(SubCount);

	MaxFloat.resize(SubCount);
	MinFloat.resize(SubCount);
	fiAmount.resize(SubCount);
	floatValue.resize(SubCount);
	floatCall.resize(SubCount);

	MaxInt.resize(SubCount);
	MinInt.resize(SubCount);
	IiAmount.resize(SubCount);
	IntValue.resize(SubCount);
	IntCall.resize(SubCount);

	ListBoxPosition.resize(SubCount);
	ListBox.resize(SubCount);
	ListBoxSize.resize(SubCount);
	ListBoxCall.resize(SubCount);

	SubMenus.resize(SubCount);

	paramType.resize(SubCount);
	params.resize(SubCount);

	FunctionCall.resize(SubCount);

	OptionCount[SubIndex] = -1;

	return SubIndex;
}

void Menu::AddBool(std::string OptionText, std::string Description, bool* Option, void* Function, const char* fmt, int ArgCount, ...)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);
	OptionKind[SubIndex].resize(OptionPosition);
	BoolValue[SubIndex].resize(OptionPosition);

	OptionKind[SubIndex][OptionCount[SubIndex]] = (Function) ? TYPE_BOOL_CALL : TYPE_BOOL;

	BoolValue[SubIndex][OptionCount[SubIndex]] = Option;

	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;

	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	if (Function)
	{
		params[SubIndex].resize(OptionPosition);
		params[SubIndex][OptionCount[SubIndex]].resize(6);

		if (fmt || ArgCount)
		{
			va_list ArgumentList = { 0 };

			va_start(ArgumentList, ArgCount);

			OptionCall(fmt, ArgCount, ArgumentList);

			va_end(ArgumentList);
		}

		BoolCall[SubIndex].resize(OptionPosition);

		BoolCall[SubIndex][OptionCount[SubIndex]] = (void(*)(...))Function;
	}
}

void Menu::AddFloat(std::string OptionText, std::string Description, float* Value, float fAmmount, float Min, float Max, void* Function, const char* fmt, int ArgCount, ...)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);
	OptionKind[SubIndex].resize(OptionPosition);

	MaxFloat[SubIndex].resize(OptionPosition);
	MinFloat[SubIndex].resize(OptionPosition);
	fiAmount[SubIndex].resize(OptionPosition);
	floatValue[SubIndex].resize(OptionPosition);

	MaxFloat[SubIndex][OptionCount[SubIndex]] = Max;
	MinFloat[SubIndex][OptionCount[SubIndex]] = Min;
	fiAmount[SubIndex][OptionCount[SubIndex]] = fAmmount;
	floatValue[SubIndex][OptionCount[SubIndex]] = Value;

	OptionKind[SubIndex][OptionCount[SubIndex]] = (Function) ? TYPE_FLOAT_CALL : TYPE_FLOAT;
	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;
	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	if (Function)
	{
		params[SubIndex].resize(OptionPosition);
		params[SubIndex][OptionCount[SubIndex]].resize(6);

		if (fmt || ArgCount)
		{
			va_list ArgumentList = { 0 };

			va_start(ArgumentList, ArgCount);

			OptionCall(fmt, ArgCount, ArgumentList);

			va_end(ArgumentList);
		}

		floatCall[SubIndex].resize(OptionPosition);

		floatCall[SubIndex][OptionCount[SubIndex]] = (void(*)(...))Function;
	}
}

void Menu::AddInt(std::string OptionText, std::string Description, int* Value, int IAmmount, int Min, int Max, void* Function, const char* fmt, int ArgCount, ...)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	OptionKind[SubIndex].resize(OptionPosition);
	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);

	MaxInt[SubIndex].resize(OptionPosition);
	MinInt[SubIndex].resize(OptionPosition);
	IiAmount[SubIndex].resize(OptionPosition);
	IntValue[SubIndex].resize(OptionPosition);

	MaxInt[SubIndex][OptionCount[SubIndex]] = Max;
	MinInt[SubIndex][OptionCount[SubIndex]] = Min;
	IiAmount[SubIndex][OptionCount[SubIndex]] = IAmmount;
	IntValue[SubIndex][OptionCount[SubIndex]] = Value;

	OptionKind[SubIndex][OptionCount[SubIndex]] = (Function) ? TYPE_INT_CALL : TYPE_INT;
	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;
	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	if (Function)
	{
		params[SubIndex].resize(OptionPosition);
		params[SubIndex][OptionCount[SubIndex]].resize(6);

		if (fmt || ArgCount)
		{
			va_list ArgumentList = { 0 };

			va_start(ArgumentList, ArgCount);

			OptionCall(fmt, ArgCount, ArgumentList);

			va_end(ArgumentList);
		}

		IntCall[SubIndex].resize(OptionPosition);

		IntCall[SubIndex][OptionCount[SubIndex]] = (void(*)(...))Function;
	}
}

void Menu::AddListBox(std::string OptionText, std::string Description, int* ArrayPosition, const char** Array, int ArraySize, void* Function, const char* fmt, int ArgCount, ...)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	OptionKind[SubIndex].resize(OptionPosition);
	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);

	ListBoxPosition[SubIndex].resize(OptionPosition);
	ListBox[SubIndex].resize(OptionPosition);
	ListBoxSize[SubIndex].resize(OptionPosition);

	ListBoxPosition[SubIndex][OptionCount[SubIndex]] = ArrayPosition;

	for (int i = 0; i < ArraySize; i++)
		ListBox[SubIndex][OptionCount[SubIndex]].push_back(Array[i]);

	ListBoxSize[SubIndex][OptionCount[SubIndex]] = ArraySize - 1;

	OptionKind[SubIndex][OptionCount[SubIndex]] = (Function) ? TYPE_LISTBOX_CALL : TYPE_LISTBOX;
	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;
	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	if (Function)
	{
		params[SubIndex].resize(OptionPosition);
		params[SubIndex][OptionCount[SubIndex]].resize(6);

		if (fmt || ArgCount)
		{
			va_list ArgumentList = { 0 };

			va_start(ArgumentList, ArgCount);

			OptionCall(fmt, ArgCount, ArgumentList);

			va_end(ArgumentList);
		}

		ListBoxCall[SubIndex].resize(OptionPosition);
		ListBoxCall[SubIndex][OptionCount[SubIndex]] = (void(*)(...))Function;
	}
}

void Menu::AddCall(std::string OptionText, std::string Description, void* Function, const char* fmt, int ArgCount, ...)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);
	OptionKind[SubIndex].resize(OptionPosition);

	OptionKind[SubIndex][OptionCount[SubIndex]] = TYPE_FUNCTION;
	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;
	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	if (Function)
	{
		params[SubIndex].resize(OptionPosition);
		params[SubIndex][OptionCount[SubIndex]].resize(6);

		if (fmt || ArgCount)
		{
			va_list ArgumentList = { 0 };

			va_start(ArgumentList, ArgCount);

			OptionCall(fmt, ArgCount, ArgumentList);

			va_end(ArgumentList);
		}

		FunctionCall[SubIndex].resize(OptionPosition);
		FunctionCall[SubIndex][OptionCount[SubIndex]] = (void(*)(...))Function;
	}
}

void Menu::AddSubMenuLink(std::string OptionText, std::string Description, int* SubMenu)
{
	OptionCount[SubIndex]++;

	MaxScroll[SubIndex]++;

	int OptionPosition = OptionCount[SubIndex] + 1;

	OptionKind[SubIndex].resize(OptionPosition);
	SubMenuText[SubIndex].resize(OptionPosition);
	SubMenuDescription[SubIndex].resize(OptionPosition);

	SubMenus[SubIndex].resize(OptionPosition);

	OptionKind[SubIndex][OptionCount[SubIndex]] = TYPE_SUBMENU;
	SubMenuText[SubIndex][OptionCount[SubIndex]] = OptionText;
	SubMenuDescription[SubIndex][OptionCount[SubIndex]] = Description;

	SubMenus[SubIndex][OptionCount[SubIndex]] = SubMenu;
}

void Menu::ScrollDown()
{
	CurrentScroll[CurrentSubMenu]++;
	if (CurrentScroll[CurrentSubMenu] > (MaxScroll[CurrentSubMenu] - 1))
		CurrentScroll[CurrentSubMenu] = 0;
}

void Menu::ScrollUp()
{
	CurrentScroll[CurrentSubMenu]--;
	if (CurrentScroll[CurrentSubMenu] < 0)
		CurrentScroll[CurrentSubMenu] = (MaxScroll[CurrentSubMenu] - 1);
}

void Menu::OpenMenu()
{
	isMenuOpened = true;
	SubIndex = 0;
}

void Menu::GoBack()
{
	if (LastSubMenu[CurrentSubMenu] == -1)
		isMenuOpened = false;
	else
		CurrentSubMenu = LastSubMenu[CurrentSubMenu];
}

void Menu::SelectOption()
{
	switch (OptionKind[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
	{
	case TYPE_FUNCTION:
		if (FunctionCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			FunctionCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]](params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][0], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][1],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][2], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][3], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][4],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][5]);
		break;
	case TYPE_BOOL:
		*BoolValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = !*BoolValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		break;
	case TYPE_LISTBOX_CALL:

		if (ListBoxCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			ListBoxCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]](params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][0], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][1],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][2], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][3], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][4],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][5]);
		break;
	case TYPE_BOOL_CALL:

		*BoolValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = !*BoolValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];

		if (BoolCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			BoolCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]](params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][0], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][1],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][2], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][3], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][4],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][5]);

		break;
	case TYPE_FLOAT_CALL:

		if (floatCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			floatCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]](params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][0], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][1],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][2], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][3], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][4],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][5]);
		break;
	case TYPE_INT_CALL:

		if (IntCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			IntCall[CurrentSubMenu][CurrentScroll[CurrentSubMenu]](params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][0], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][1],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][2], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][3], params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][4],
				params[CurrentSubMenu][CurrentScroll[CurrentSubMenu]][5]);
		break;

	case TYPE_SUBMENU:
	{
		int SubMenuBackUp = CurrentSubMenu;

		CurrentSubMenu = *SubMenus[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		CurrentScroll[CurrentSubMenu] = 0;

		LastSubMenu[CurrentSubMenu] = SubMenuBackUp;

		break;
	}
	default:
		break;
	}
}

void Menu::ScrollLeft()
{
	switch (OptionKind[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
	{
	case TYPE_FLOAT:
	case TYPE_FLOAT_CALL:
		*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] -= fiAmount[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		if (*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] < MinFloat[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = MaxFloat[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		break;
	case TYPE_INT:
	case TYPE_INT_CALL:
		*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] -= IiAmount[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		if (*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] < MinInt[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = MaxInt[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];

		break;
	case TYPE_LISTBOX:
	case TYPE_LISTBOX_CALL:
		*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] -= 1;
		if (*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] < 0)
			*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = ListBoxSize[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		break;

	default:
		break;
	}
}

void Menu::ScrollRight()
{
	switch (OptionKind[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
	{
	case TYPE_FLOAT:
	case TYPE_FLOAT_CALL:
		*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] += fiAmount[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		if (*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] > MaxFloat[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			*floatValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = MinFloat[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		break;
	case TYPE_INT:
	case TYPE_INT_CALL:
		*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] += IiAmount[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		if (*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] > MaxInt[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			*IntValue[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = MinInt[CurrentSubMenu][CurrentScroll[CurrentSubMenu]];
		break;

	case TYPE_LISTBOX:
	case TYPE_LISTBOX_CALL:
		*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] += 1;
		if (*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] > ListBoxSize[CurrentSubMenu][CurrentScroll[CurrentSubMenu]])
			*ListBoxPosition[CurrentSubMenu][CurrentScroll[CurrentSubMenu]] = 0;

		break;
	default:
		break;
	}
}

void Menu::OptionCall(const char* fmt, int n_args, va_list vaList)
{
	int OptionPosition = OptionCount[SubIndex] + 1;

	paramType[SubIndex].resize(OptionPosition);
	paramType[SubIndex][OptionCount[SubIndex]] = fmt;

	for (int i = 0; i < n_args; i++)
	{
		switch (paramType[SubIndex][OptionCount[SubIndex]].c_str()[i])
		{
		case 'i':
			params[SubIndex][OptionCount[SubIndex]][i].intValue = va_arg(vaList, int);
			break;
		case 's':
			params[SubIndex][OptionCount[SubIndex]][i].strValue = va_arg(vaList, char*);
			break;
		case 'b':
			params[SubIndex][OptionCount[SubIndex]][i].boolValue = va_arg(vaList, bool);
			break;
		case 'f':
			params[SubIndex][OptionCount[SubIndex]][i].floatValue = va_arg(vaList, float);
			break;
		case 'v':
			params[SubIndex][OptionCount[SubIndex]][i].vectorValue = va_arg(vaList, float*);
			break;
		default:
			break;
		}
	}
}