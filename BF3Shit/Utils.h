#define NAME_MOUNT "Nigel:\\"
#define NAME_HDD "\\Device\\Harddisk0\\Partition1"

typedef struct _STRING
{
	short Length;
	short MaximumLength;
	char*  Buffer;
} STRING, *PSTRING;

extern "C"
{
	VOID NTAPI RtlInitAnsiString(PSTRING DestinationString, LPCSTR SourceString);
	HRESULT ObCreateSymbolicLink(PSTRING SymbolicLinkName, PSTRING DeviceName);
	DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, LPDWORD lpThreadId, PVOID apiThreadStartup, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlagsMod);
	void XapiThreadStartup(void(*StartRoutine)(void *), void* StartContext, unsigned int dwExitCode);
}

HRESULT CreateSymbolicLink(PCHAR szDrive, PCHAR szDeviceName, BOOL System);
void CreateSystemThread(void* Function, void* Param);
BOOL FileExists(LPCSTR lpFileName);