#pragma once

#define MAX_HUDS 50

enum OptionType
{
	TYPE_FLOAT,
	TYPE_INT,
	TYPE_BOOL,
	TYPE_LISTBOX,
	TYPE_LISTBOX_CALL,
	TYPE_BOOL_CALL,
	TYPE_FLOAT_CALL,
	TYPE_INT_CALL,
	TYPE_FUNCTION,
	TYPE_SUBMENU
};

union Param
{
	int intValue;
	char *strValue;
	bool boolValue;
	float floatValue;
	float *vectorValue;
	class SubMenu *Sub;
};

class Menu
{
public:
	Menu();
	~Menu();

	void ScrollRight();
	void ScrollLeft();
	void SelectOption();
	void GoBack();
	void OpenMenu();

	int CreateSubMenu(std::string SubName);

	void AddCall(std::string OptionText, std::string Description, void* Function = 0, const char* fmt = 0, int ArgCount = 0, ...);
	void AddBool(std::string OptionText, std::string Description, bool* Option, void*Function = 0, const char* fmt = 0, int ArgCount = 0, ...);
	void AddFloat(std::string OptionText, std::string Description, float* Value, float fAmmount, float Min, float Max, void*Function = 0, const char* fmt = 0, int ArgCount = 0, ...);
	void AddInt(std::string OptionText, std::string Description, int* Value, int IAmmount, int Min, int Max, void*Function = 0, const char* fmt = 0, int ArgCount = 0, ...);
	void AddListBox(std::string OptionText, std::string Description, int* ArrayPosition, const char** Array, int ArraySize, void*Function = 0, const char* fmt = 0, int ArgCount = 0, ...);
	void AddSubMenuLink(std::string OptionText, std::string Description, int* SubMenu);
	void OptionCall(const char* fmt, int n_args, va_list vaList);

	void ScrollDown();
	void ScrollUp();

	bool isMenuOpened;
	int SubIndex;
	int CurrentSubMenu;

	std::vector<std::vector<std::vector<Param>>>  params;
	std::vector<std::vector<std::string>> paramType;

	std::vector<std::vector<std::vector<const char*>>> ListBox;
	std::vector<std::vector<int*>> ListBoxPosition;
	std::vector<std::vector<int>> ListBoxSize;
	std::vector<std::vector<void(*)(...)>> ListBoxCall;

	std::vector<std::vector<float>> MaxFloat;
	std::vector<std::vector<float>> MinFloat;
	std::vector<std::vector<float*>> floatValue;
	std::vector<std::vector<float>> fiAmount;
	std::vector<std::vector<void(*)(...)>> floatCall;

	std::vector<std::vector<int>> MaxInt;
	std::vector<std::vector<int>> MinInt;
	std::vector<std::vector<int*>> IntValue;
	std::vector<std::vector<int>> IiAmount;
	std::vector<std::vector<void(*)(...)>> IntCall;

	std::vector<std::vector<bool*>> BoolValue;
	std::vector<std::vector<void(*)(...)>> BoolCall;

	std::vector<std::vector<void(*)(...)>> FunctionCall;

	std::vector<std::vector<int*>> SubMenus;
	std::vector<std::vector<OptionType>> OptionKind;
	std::vector<int> MaxScroll;
	std::vector<int> OptionCount;
	std::vector<int> LastSubMenu;
	std::vector<int> CurrentScroll;
	std::vector<std::string> SubTitles;
	std::vector<std::vector<std::string>> SubMenuText;
	std::vector<std::vector<std::string>> SubMenuDescription;

private:
};
