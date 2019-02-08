#include "main.h"


GAME_ADDRESSES_BF3* Addresses;

Detour* (*GetDetour)();
void(*XNotify)(wchar_t*);
void*(*user_memcpy)(void*, void*, size_t);
char*(*user_strcpy)(char*, const char*);
void*(*user_memset)(void*, int, size_t);
int(*user_strcmp)(const char*, const char*);
void*(*xbOHookFunction)(Detour* a, void* b, void* c);

float(*GetDistance)(Vector3 c1, Vector3 c2);
float(*VectorLength2D)(Vector3* pV);
void(*CreateSystemThread)(void* Function, void* Param);
bool(*MmIsAddressValidPtr)(void * ptr);
int(*GetAsyncKeyState)(DWORD KEY);
bool(*CWriteFile)(const char* FilePath, const void* Data, unsigned int Size);
BOOL(*FileExists)(LPCSTR lpFileName);
int(*sendSpottingMessage)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type);
int(*GetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer*);
int(*AddDamageData)(ClientConnection*, ClientDamageStream::DamageData*);
int(*sub_835F4878)(unsigned char* r3, unsigned char* r4);
int(*sub_83D131D0)(unsigned char* r3, unsigned char* r4);
int(*GetAmmoPtr)(int x, int y, int z);
int(*CCMessage)(ClientConnection*, Message*);
int(*ReloadMessageFunction)(int r3, int r4, int r5);


__int64 __declspec(naked) HvxGetVersion(unsigned int key, __int64 type, __int64 SourceAddress, __int64 DestAddress, __int64 lenInBytes)
{
	__asm
	{
		li r0, 0x0
		sc
		blr
	}
}

unsigned int HVGetVersionsPeekDWORD(unsigned long long Address)
{
	unsigned int *data = (unsigned int *)XPhysicalAlloc(4, MAXULONG_PTR, 0, PAGE_READWRITE); ;

	__int64 dest = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned int*)data);

	HvxGetVersion(0x72627472, 5, Address, dest, 4);

	unsigned int retData = *(unsigned int*)data;

	XPhysicalFree(data);

	return retData;
}

unsigned int ReverseInt(unsigned int val)
{
	int RetVal = ((val << 24)) | (((val << 8) & 0x00ff0000)) | (((val >> 8) & 0x0000ff00)) | (((val >> 24) & 0x000000ff));

	return (RetVal + 0x90E00000);
}


#if defined(DEVKIT)

int Real_sub_835F4878(unsigned char* r3, unsigned char* r4)
{
	int(*sub_835F4878)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))Addresses->_0x835F4878;

	return sub_835F4878(r3, r4);
}


int Real_sub_83D131D0(unsigned char* r3, unsigned char* r4)
{
	int(*sub_83D131D0)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))Addresses->_0x83D131D0;

	return sub_83D131D0(r3, r4);
}

int Real_GetAmmoPtr(int x, int y, int z)
{
	int(*GetAmmoPtr)(int x, int y, int z) = (int(*)(int x, int y, int z))Addresses->_0x83266AC0;

	return GetAmmoPtr(x, y, z);
}

int Real_CCMessage(ClientConnection*a, Message*b)
{
	int(*CCMessage)(ClientConnection*, Message*) = (int(*)(ClientConnection*, Message*))Addresses->_0x831FAD00;

	return CCMessage(a, b);
}

int Real_ReloadMessageFunction(int r3, int r4, int r5)
{
	int(*ReloadMessageFunction)(int r3, int r4, int r5) = (int(*)(int r3, int r4, int r5))Addresses->_0x834CC888;

	return ReloadMessageFunction(r3, r4, r5);

}
int Real_AddDamageData(ClientConnection* a, ClientDamageStream::DamageData* b)
{
	int(*AddDamageData)(ClientConnection*, ClientDamageStream::DamageData*) = (int(*)(ClientConnection*, ClientDamageStream::DamageData*))Addresses->_0x831FB1D8;

	return AddDamageData(a, b);
}

int Real_GetPlayerScore(ClientPlayerScoreManager*a, ClientPlayer*b)
{
	int(*GetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer*) = (int(*)(ClientPlayerScoreManager*, ClientPlayer*))Addresses->_0x83212338;

	return GetPlayerScore(a, b);
}

int Real_sendSpottingMessage(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type)
{
	int(*sendSpottingMessage)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type) = (int(*)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type))Addresses->_0x8340E610;

	return sendSpottingMessage(thisClientSpottingComponent, MyClientPlayer, controllablesToSpot, type);
}

DWORD Real_ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HANDLE hModule; DWORD Address;
	XexGetModuleHandle(ModuleName, &hModule);
	XexGetProcedureAddress(hModule, Ordinal, &Address);
	return Address;
}

DWORD Real_XNotifyThread(wchar_t *Message)
{
	while (((int(*)(DWORD exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData))Real_ResolveFunction("xam.xex", 0x290))(34, 0xFF, 2, Message, 0) == ERROR_ACCESS_DENIED)
		Sleep(10);

	return 0;
}

int * Real_GetDetours()
{
	return (int*)new Detour();
}

VOID Real_XNotify(CONST PWCHAR NotifyText)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)Real_XNotifyThread, NotifyText, 0);
}

void* Real_HookFunction(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (unsigned int)c);
}


float Real_GetDistance(Vector3 c1, Vector3 c2)
{
	Vector3 Sub = c1 - c2;
	return (sqrt((float)((Sub.x * Sub.x) + (Sub.y * Sub.y) + (Sub.z * Sub.z))) / 55.0f);
}

float Real_VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

const DWORD MMIORangeTable[] =
{
	0x7FC80000,
	0x7FC9FFFF,
	0x7FD00000,
	0x7FDFFFFF,
	0x7FEA0000,
	0x7FEAFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x8FFF0000,
	0x8FFF0FFF,
	0x8FFF1000,
	0x8FFF1FFF,
	0x00000000,
	0x00000000,

};

BOOL Real_FIsMmIoAddress(PVOID addr)
{
	int i = 0;

	for (i = 0; MMIORangeTable[i]; i += 2) {
		if (((DWORD)addr > MMIORangeTable[i]) && ((DWORD)addr < MMIORangeTable[i + 1]))
			return TRUE;
	}

	return FALSE;
}

bool Real_MmIsAddressValidPtr(void* ptr)
{
	if (((int)ptr > 0x30000000))
		return (!Real_FIsMmIoAddress(ptr) && MmIsAddressValid(ptr));

	return false;
}

BOOL Real_FileExists(LPCSTR lpFileName)
{
	if (GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}
	return TRUE;
}

void Real_CreateSystemThread(void* Function, void* Param)
{
	HANDLE hThread1 = 0; DWORD threadId1 = 0;
	ExCreateThread(&hThread1, 0x10000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)Function, Param, 0x2);
	XSetThreadProcessor(hThread1, 4);
	ResumeThread(hThread1);
	CloseHandle(hThread1);
}

int Real_GetAsyncKeyState(DWORD KEY)
{
	XINPUT_STATE InputState;
	XInputGetState(0, &InputState);

	if (!KEY)
		return true;

	if (KEY == KEY_LT) {
		return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	}

	if (KEY == KEY_RT)
		return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return InputState.Gamepad.wButtons & KEY;
}

bool Real_CWriteFile(const char* FilePath, const void* Data, unsigned int Size)
{
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	DWORD writeSize = Size;
	if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE) {
		return FALSE;
	}
	CloseHandle(fHandle);
	return TRUE;
}

#endif




void LoadAddresses()
{
#if defined(DEVKIT)

	GetDetour = (Detour*(*)())Real_GetDetours;
	XNotify = (void(*)(wchar_t*))Real_XNotify;

	user_memcpy = (void*(*)(void*, void*, size_t))memcpy;
	user_strcpy = (char*(*)(char*, const char*))strcpy;
	user_memset = (void*(*)(void*, int, size_t))memset;
	user_strcmp = (int(*)(const char*, const char*))strcmp;
	xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))Real_HookFunction;

	GetDistance = (float(*)(Vector3 c1, Vector3 c2))Real_GetDistance;
	VectorLength2D = (float(*)(Vector3* pV))Real_VectorLength2D;
	CreateSystemThread = (void(*)(void* Function, void* Param))Real_CreateSystemThread;
	MmIsAddressValidPtr = (bool(*)(void * ptr))Real_MmIsAddressValidPtr;
	GetAsyncKeyState = (int(*)(DWORD KEY))Real_GetAsyncKeyState;
	CWriteFile = (bool(*)(const char* FilePath, const void* Data, unsigned int Size))Real_CWriteFile;
	FileExists = (BOOL(*)(LPCSTR lpFileName))Real_FileExists;

	sendSpottingMessage = (int(*)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type))Real_sendSpottingMessage;
	GetPlayerScore = (int(*)(ClientPlayerScoreManager*, ClientPlayer*))Real_GetPlayerScore;
	AddDamageData = (int(*)(ClientConnection*, ClientDamageStream::DamageData*))Real_AddDamageData;
	sub_835F4878 = (int(*)(unsigned char* r3, unsigned char* r4))Real_sub_835F4878;
	sub_83D131D0 = 
		(int(*)(unsigned char* r3, unsigned char* r4))Real_sub_83D131D0;
	GetAmmoPtr = (int(*)(int x, int y, int z))Real_GetAmmoPtr;
	CCMessage = (int(*)(ClientConnection*, Message*))Real_CCMessage;
	ReloadMessageFunction = (int(*)(int r3, int r4, int r5))Real_ReloadMessageFunction;

	Addresses = new GAME_ADDRESSES_BF3;
	Addresses->SetAddress();
#else
	GAME_ADDRESS_TRANSFER_BF3* Game_Functions = (GAME_ADDRESS_TRANSFER_BF3*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED0));
	int AddressLength = ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED4));
	SYS_FUNCTION_ADDRESS* Sys_Functions = (SYS_FUNCTION_ADDRESS*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED8));


	if (Sys_Functions)
	{

		GetDetour = (Detour*(*)())Sys_Functions->GetDetours;
		XNotify = (void(*)(wchar_t*))Sys_Functions->XNotify;
		user_memcpy = (void*(*)(void*, void*, size_t))Sys_Functions->memcpy;
		user_strcpy = (char*(*)(char*, const char*))Sys_Functions->strcpy;
		user_memset = (void*(*)(void*, int, size_t))Sys_Functions->memset;
		user_strcmp = (int(*)(const char*, const char*))Sys_Functions->strcmp;
		xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))Sys_Functions->HookFunction;
	}


	if (Game_Functions)
	{
		Addresses = Game_Functions->Addresses;

		GetDistance = (float(*)(Vector3 c1, Vector3 c2))(void*)ReverseInt((int)Game_Functions->GetDistance);
		VectorLength2D = (float(*)(Vector3* pV))(void*)ReverseInt((int)Game_Functions->VectorLength2D);
		CreateSystemThread = (void(*)(void* Function, void* Param))(void*)ReverseInt((int)Game_Functions->CreateSystemThread);
		MmIsAddressValidPtr = (bool(*)(void * ptr))(void*)ReverseInt((int)Game_Functions->MmIsAddressValidPtr);
		GetAsyncKeyState = (int(*)(DWORD KEY))(void*)ReverseInt((int)Game_Functions->GetAsyncKeyState);
		CWriteFile = (bool(*)(const char* FilePath, const void* Data, unsigned int Size))(void*)ReverseInt((int)Game_Functions->CWriteFile);
		FileExists = (BOOL(*)(LPCSTR lpFileName))(void*)ReverseInt((int)Game_Functions->FileExists);

		sendSpottingMessage = (int(*)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type))(void*)ReverseInt((int)Game_Functions->sendSpottingMessage);
		GetPlayerScore = (int(*)(ClientPlayerScoreManager*, ClientPlayer*))(void*)ReverseInt((int)Game_Functions->GetPlayerScore);
		AddDamageData = (int(*)(ClientConnection*, ClientDamageStream::DamageData*))(void*)ReverseInt((int)Game_Functions->AddDamageData);
		sub_835F4878 = (int(*)(unsigned char* r3, unsigned char* r4))(void*)ReverseInt((int)Game_Functions->sub_835F4878);
		sub_83D131D0 = (int(*)(unsigned char* r3, unsigned char* r4))(void*)ReverseInt((int)Game_Functions->sub_83D131D0);
		GetAmmoPtr = (int(*)(int x, int y, int z))(void*)ReverseInt((int)Game_Functions->GetAmmoPtr);
		CCMessage = (int(*)(ClientConnection*, Message*))(void*)ReverseInt((int)Game_Functions->CCMessage);
		ReloadMessageFunction = (int(*)(int r3, int r4, int r5))(void*)ReverseInt((int)Game_Functions->ReloadMessageFunction);

	}

#endif
}
