#include "main.h"

HANDLE g_hModule;

bool RunThread = true;

char SoundPath[0x255] = { 0 };
bool runSoundsNow = false;

void SoundThread()
{
	while (RunThread)
	{

		if (runSoundsNow) {

			PlayThreadedWav(SoundPath);
			runSoundsNow = false;
		}
		Sleep(10);
	}
}

void MainThread()
{
	XNotify(L"[1.0.6] xbOnline BF3 Cheats Loaded!");

	if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
	}

	CreateSystemThread(SoundThread, NULL);

	LoadINI();

	AddMenuOptions();

	while (RunThread)
	{
		if (ATG::g_pd3dDevice && !IsFontInit)
		{
			InitFont();
		}

		if (SetIni)
		{
			SetInit();
			SetIni = false;
		}

		if (GetIni)
		{
			LoadINI();
			GetIni = false;
		}

		Sleep(10);
	}
}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		ATG::g_pd3dDevice = NULL;

		g_hModule = ModuleHandle;

		LoadAddresses();

		onPostPhysicsUpdateSyncDetour = GetDetour();
		ClientConnection_SendMessageDetour = GetDetour();
		sub_83CFF480Detour = GetDetour();
		sub_834F63C8Detour = GetDetour();
		TransmitPacketDetour = GetDetour();
		RayCastingDetour = GetDetour();
		XamInputGetStateDetour = GetDetour();
		D3DDevice_PresentDetour = GetDetour();
		AddMoveHook = GetDetour();
		GetDispersionDetour = GetDetour();
		createScoringMessageDetour = GetDetour();

#if defined(DEVKIT)
		//XamUserGetSigninInfoDetour = GetDetour();
		//XamUserGetNameDetour = GetDetour();
		//XamUserGetXUIDDetour = GetDetour();
		//
		//xbOHookFunction(XamUserGetSigninInfoDetour, (void*)0x83F275EC, (void*)XamUserGetSigninInfoHook);
		//xbOHookFunction(XamUserGetNameDetour, (void*)0x83F2775C, (void*)XamUserGetNameHook);
		//xbOHookFunction(XamUserGetXUIDDetour, (void*)0x83F2732C, (void*)XamUserGetXUIDHook);
#endif 

		createScoringMessageOriginal = (createScoringMessageStub)xbOHookFunction(createScoringMessageDetour, (void*)0x834D3758, (void*)createScoringMessagehk);

		GetDispersionOriginal = (GetDispersionStub)xbOHookFunction(GetDispersionDetour, (void*)0x8334FA80, (void*)GetDispersionHook);
		onPostPhysicsUpdateSyncOriginal = (onPostPhysicsUpdateSync_t)xbOHookFunction(onPostPhysicsUpdateSyncDetour, (void*)Addresses->_0x834162D8, (void*)onPostPhysicsUpdateSyncHook);
		ClientConnection_SendMessageOriginal = (ClientConnection_SendMessage_t)xbOHookFunction(ClientConnection_SendMessageDetour, (void*)Addresses->_0x831FAD00, (void*)ClientConnection_SendMessageHook);
		sub_83CFF480Original = (sub_83CFF480_t)xbOHookFunction(sub_83CFF480Detour, (void*)Addresses->_0x83CFF480, (void*)sub_83CFF480Hook);
		sub_834F63C8Original = (sub_834F63C8_t)xbOHookFunction(sub_834F63C8Detour, (void*)Addresses->_0x834F63C8, (void*)sub_834F63C8Hook);
		RayCastingOriginal = (RayCasting_t)xbOHookFunction(RayCastingDetour, (void*)Addresses->_0x83C44E30, (void*)RayCastingHook);
		TransmitPacketOriginal = (TransmitPacketStub)xbOHookFunction(TransmitPacketDetour, (void*)Addresses->_0x83CFFAA0, (void*)TransmitPacketHook);
		D3DDevice_PresentOriginal = (D3DDevice_Present_t)xbOHookFunction(D3DDevice_PresentDetour, (void*)Addresses->_0x8315F850, (void*)D3DDevice_PresentHook);
		xbOHookFunction(XamInputGetStateDetour, (void*)GetAddr(Addresses->_0x82D80000, 0x191), (void*)XamInputGetStateHook);
		AddMoveOriginal = (AddMoveStub)xbOHookFunction(AddMoveHook, (void*)Addresses->_0x83D00B58, (void*)AddMove);

		CreateSystemThread(MainThread, NULL);


	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RunThread = false;

#if defined(DEVKIT)
		//XamUserGetSigninInfoDetour->RestoreFunction();
		//XamUserGetNameDetour->RestoreFunction();
		//XamUserGetXUIDDetour->RestoreFunction();
#endif // DEVKIT

		createScoringMessageDetour->RestoreFunction();
		GetDispersionDetour->RestoreFunction();
		onPostPhysicsUpdateSyncDetour->RestoreFunction();
		ClientConnection_SendMessageDetour->RestoreFunction();
		sub_83CFF480Detour->RestoreFunction();
		sub_834F63C8Detour->RestoreFunction();
		TransmitPacketDetour->RestoreFunction();
		RayCastingDetour->RestoreFunction();
		XamInputGetStateDetour->RestoreFunction();
		D3DDevice_PresentDetour->RestoreFunction();
		AddMoveHook->RestoreFunction();

		Sleep(500);
	}
	return TRUE;
}

