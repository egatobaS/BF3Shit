#include "main.h"

HANDLE g_hModule;

bool ShouldSetIni = false;
bool RunThread = true;

unsigned int WaitConfig = 0;
unsigned int TimeConfig = 0;

void ConfigWait(int time)
{
	TimeConfig = GetTickCount();
	WaitConfig = time;
}


void MainThread()
{
	if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
	}

	LoadINI();

	AddMenuOptions();

	while (RunThread)
	{
		if (ATG::g_pd3dDevice && !IsFontInit)
		{
			InitFont();
		}

		if ((GetTickCount() - TimeConfig) > WaitConfig)
		{
			if (ShouldSetIni)
			{
				SetInit();

				ShouldSetIni = false;
			}
			ConfigWait(1000);
		}

		Sleep(10);
	}
}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		ATG::g_pd3dDevice = NULL;

		g_hModule = ModuleHandle;

		onPostPhysicsUpdateSyncOriginal = (onPostPhysicsUpdateSync_t)onPostPhysicsUpdateSyncDetour.HookFunction(0x834162D8, (unsigned int)onPostPhysicsUpdateSyncHook);
		ClientConnection_SendMessageOriginal = (ClientConnection_SendMessage_t)ClientConnection_SendMessageDetour.HookFunction(0x831FAD00, (unsigned int)ClientConnection_SendMessageHook);
		sub_83CFF480Original = (sub_83CFF480_t)sub_83CFF480Detour.HookFunction(0x83CFF480, (unsigned int)sub_83CFF480Hook);
		sub_834F63C8Original = (sub_834F63C8_t)sub_834F63C8Detour.HookFunction(0x834F63C8, (unsigned int)sub_834F63C8Hook);
		RayCastingOriginal = (RayCasting_t)RayCastingDetour.HookFunction(0x83C44E30, (unsigned int)RayCastingHook);
		TransmitPacketOriginal = (TransmitPacketStub)TransmitPacketDetour.HookFunction(0x83CFFAA0, (DWORD)TransmitPacketHook);
		D3DDevice_PresentOriginal = (D3DDevice_Present_t)D3DDevice_PresentDetour.HookFunction(0x8315F850, (unsigned int)D3DDevice_PresentHook);
		XamInputGetStateDetour.HookFunction(GetAddr(0x82D80000, 0x191), (unsigned int)XamInputGetStateHook);
		AddMoveOriginal = (AddMoveStub)AddMoveHook.HookFunction(0x83D00B58, (DWORD)AddMove);

		CreateSystemThread(MainThread, NULL);


	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RunThread = false;
		onPostPhysicsUpdateSyncDetour.RestoreFunction();
		ClientConnection_SendMessageDetour.RestoreFunction();
		sub_83CFF480Detour.RestoreFunction();
		sub_834F63C8Detour.RestoreFunction();
		TransmitPacketDetour.RestoreFunction();
		RayCastingDetour.RestoreFunction();
		XamInputGetStateDetour.RestoreFunction();
		D3DDevice_PresentDetour.RestoreFunction();
		AddMoveHook.RestoreFunction();

		Sleep(500);
	}
	return TRUE;
}

