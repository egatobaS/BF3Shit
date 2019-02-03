#include "main.h"

bool ShouldSetIni = false;
bool RunThread = true;

void MainThread()
{
	if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
		printf("Could not create symbolic link!\n");
	}

	LoadINI();

	AddMenuOptions();

	while (RunThread)
	{
		if (ATG::g_pd3dDevice && !IsFontInit)
		{
			InitFont();
		}

		if (ShouldSetIni)
		{
			SetInit();
			ShouldSetIni = false;
		}
		Sleep(10);
	}

	printf("Thread Exited\n");
}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		ATG::g_pd3dDevice = NULL;

		RayCastingOriginal = (RayCasting_t)RayCastingDetour.HookFunction(0x83C44E30, (unsigned int)RayCastingHook);
		TransmitPacketOriginal = (TransmitPacketStub)TransmitPacketDetour.HookFunction(0x83CFFAA0, (DWORD)TransmitPacketHook);
		D3DDevice_PresentOriginal = (D3DDevice_Present_t)D3DDevice_PresentDetour.HookFunction(0x8315F850, (unsigned int)D3DDevice_PresentHook);
		XamInputGetStateDetour.HookFunction(GetAddr(0x82D80000, 0x191), (unsigned int)XamInputGetStateHook);
		AddMoveOriginal = (AddMoveStub)AddMoveHook.HookFunction(0x83D00B58, (DWORD)AddMove);

		CreateSystemThread(MainThread, NULL);


	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RunThread = false;

		TransmitPacketDetour.RestoreFunction();
		RayCastingDetour.RestoreFunction();
		XamInputGetStateDetour.RestoreFunction();
		D3DDevice_PresentDetour.RestoreFunction();
		AddMoveHook.RestoreFunction();

		Sleep(500);
	}
	return TRUE;
}

