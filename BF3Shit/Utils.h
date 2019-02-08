#define NAME_MOUNT "Nigel:\\"
#define NAME_HDD "\\Device\\Harddisk0\\Partition1"


enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

typedef struct _STRING
{
	short Length;
	short MaximumLength;
	char*  Buffer;
} STRING, *PSTRING;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;


typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InClosureOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID NtHeadersBase;
	PVOID ImageBase;
	DWORD SizeOfNtImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	DWORD Flags;
	DWORD SizeOfFullImage;
	PVOID EntryPoint;
	WORD LoadCount;
	WORD ModuleIndex;
	PVOID DllBaseOriginal;
	DWORD CheckSum;
	DWORD ModuleLoadFlags;
	DWORD TimeDateStamp;
	PVOID LoadedImports;
	PVOID XexHeaderBase;
	union {
		STRING LoadFileName;
		struct {
			PVOID ClosureRoot; // LDR_DATA_TABLE_ENTRY
			PVOID TraversalParent; // LDR_DATA_TABLE_ENTRY
		} asEntry;
	} inf;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

extern "C" {
	PVOID XexPcToFileHeader(PVOID address, PLDR_DATA_TABLE_ENTRY* ldatOut);

	PVOID RtlImageXexHeaderField(PVOID XexHeaderBase, DWORD ImageField);
}

typedef struct _DETOUR_XEX_IMPORT_DESCRIPTOR
{
	DWORD Size;
	DWORD NameTableSize;
	DWORD ModuleCount;
} DETOUR_XEX_IMPORT_DESCRIPTOR, *PDETOUR_XEX_IMPORT_DESCRIPTOR;


extern "C"
{
	VOID NTAPI RtlInitAnsiString(PSTRING DestinationString, LPCSTR SourceString);
	HRESULT ObCreateSymbolicLink(PSTRING SymbolicLinkName, PSTRING DeviceName);
	DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, LPDWORD lpThreadId, PVOID apiThreadStartup, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlagsMod);
	void XapiThreadStartup(void(*StartRoutine)(void *), void* StartContext, unsigned int dwExitCode);
}
DWORD GetAddr(DWORD dwModuleBaseAddr, int Ordinal);
HRESULT CreateSymbolicLink(PCHAR szDrive, PCHAR szDeviceName, BOOL System);
void CreateSystemThread(void* Function, void* Param);
bool MmIsAddressValidPtr(void * ptr);
BOOL FileExists(LPCSTR lpFileName);
int GetAsyncKeyState(DWORD KEY);
bool CWriteFile(const char* FilePath, const void* Data, unsigned int Size);
void Wait(int time);

extern unsigned int WaitTime;
extern unsigned int TimeCount;