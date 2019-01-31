#include "main.h"

typedef int(*D3DDevice_Present_t)(D3DDevice *pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);
D3DDevice_Present_t pD3DDevice_Present;
Detour dD3DDevice_Present;

bool RunThread = true;

void MainThread()
{
	if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
		printf("Could not create symbolic link!\n");
	}

	while (RunThread)
	{
		if (ATG::g_pd3dDevice && !IsFontInit)
			InitFont();

		Sleep(1);
	}

	printf("Thread Exited\n");
}

int D3DDevice_PresentHk(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7) {

	ATG::g_pd3dDevice = (ATG::D3DDevice*)*(int*)((((int)pDevice) + 0x18));

	InitTexture();

	if (IsFontInit && IsTextureInit)
	{
		DrawBox(100, 100, 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255));

		DrawText("Hello World", 1280 / 2, 720 / 2, 0.5, D3DCOLOR_RGBA(255, 255, 255, 255));

		DrawLine(1280 / 2, 720 / 2, 100, 100, 1, D3DCOLOR_RGBA(255, 0, 0, 255));
	}

	return pD3DDevice_Present(pDevice, r4, r5, r6, r7);;
}


BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		ATG::g_pd3dDevice = NULL;

		pD3DDevice_Present = (D3DDevice_Present_t)dD3DDevice_Present.HookFunction(0x8315F850, (unsigned int)D3DDevice_PresentHk);

		CreateSystemThread(MainThread, NULL);


	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RunThread = false;

		dD3DDevice_Present.RestoreFunction();

		Sleep(500);
	}
	return TRUE;
}

