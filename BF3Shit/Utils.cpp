#include "main.h"

unsigned int WaitTime = 0;
unsigned int TimeCount = 0;

BOOL FileExists(LPCSTR lpFileName)
{
	if (GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}
	return TRUE;
}

void CreateSystemThread(void* Function, void* Param)
{
	HANDLE hThread1 = 0; DWORD threadId1 = 0;
	ExCreateThread(&hThread1, 0x10000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)Function, Param, 0x2);
	XSetThreadProcessor(hThread1, 4);
	ResumeThread(hThread1);
	CloseHandle(hThread1);
}


HRESULT CreateSymbolicLink(PCHAR szDrive, PCHAR szDeviceName, BOOL System)
{
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);
	if (FileExists(szDrive)) return S_OK;
	long status = ObCreateSymbolicLink(&linkname, &devicename);
	return (status >= 0) ? S_OK : S_FALSE;
}



DWORD GetModuleImport(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal)
{
	PDETOUR_XEX_IMPORT_DESCRIPTOR importTable;
	DWORD dwModuleCountIndex = 0;
	DWORD dwModuleIndex = 0;
	CHAR szModuleName[0x100];
	CHAR szHImportedModule[0x100];

	DWORD dwImportAddress = (DWORD)GetProcAddress((HMODULE)HImportedModule, (LPCSTR)Ordinal);

	if (dwImportAddress == NULL || HModule == NULL)
		return 0;

	importTable = (PDETOUR_XEX_IMPORT_DESCRIPTOR)
		RtlImageXexHeaderField((void*)*(DWORD *)((DWORD)HModule + 0x58), 0x000103FF);

	if (importTable == NULL)
		return 0;

	WideCharToMultiByte(CP_UTF8, NULL, (wchar_t*)*(DWORD*)((DWORD)HImportedModule + 0x30), -1, szHImportedModule, 0x100, NULL, NULL);

	for (DWORD dwModuleCount = 0; dwModuleCount < importTable->ModuleCount; dwModuleCount++)
	{
		DWORD i = dwModuleCountIndex;

		DWORD dwPointer = (DWORD)importTable + 0x0C + importTable->NameTableSize + dwModuleIndex;

		DWORD dwModuleSectionSize = *(DWORD *)dwPointer;

		dwPointer += 0x24 + 4;

		dwModuleIndex += dwModuleSectionSize;

		dwModuleSectionSize -= 0x24 + 4;

		dwModuleCountIndex += strlen((char*)((DWORD)importTable + 0x0C + i));

		strcpy(szModuleName, (char*)((DWORD)importTable + 0x0C + i));

		if (!strcmp(szModuleName, szHImportedModule))
		{
			for (DWORD dwSize = 0; dwSize < dwModuleSectionSize; dwSize += 8)
			{
				DWORD dwTempAddr = *(DWORD *)*(DWORD *)(dwPointer + dwSize);
				if (dwTempAddr == dwImportAddress)
					return *(DWORD *)(dwPointer + dwSize + 4);
			}
		}
	}
	return 0;
}

DWORD GetAddr(DWORD dwModuleBaseAddr, int Ordinal)
{
	HANDLE hModule;
	XexPcToFileHeader((PVOID)dwModuleBaseAddr, (PLDR_DATA_TABLE_ENTRY*)&hModule);
	HANDLE hImportedModule = (HANDLE)GetModuleHandle("xam.xex");
	return GetModuleImport(hModule, hImportedModule, Ordinal);
}


int GetAsyncKeyState(DWORD KEY)
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

void Wait(int time)
{
	TimeCount = GetTickCount();
	WaitTime = time;
}