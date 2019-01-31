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

float ang = 0.000000f;

typedef float vec2_t[2];

void rotationalLine(vec2_t center, float x, float y, float x2, float y2, float angle, D3DCOLOR Color) {
	//Don't tell sab that I stole this from him

	vec2_t Line1 = { 0 };
	vec2_t Line2 = { 0 };

	Line1[0] = center[0] + (x - center[0])*cos(-angle) + (y - center[1])*sin(-angle);
	Line1[1] = center[1] - (x - center[0])*sin(-angle) + (y - center[1])*cos(-angle);

	Line2[0] = center[0] + (x2 - center[0])*cos(-angle) + (y2 - center[1])*sin(-angle);
	Line2[1] = center[1] - (x2 - center[0])*sin(-angle) + (y2 - center[1])*cos(-angle);


}


void DrawSwastika(vec2_t point, vec2_t mid, float scale, float angle) {

	rotationalLine(point, mid[0], mid[1] - scale, mid[0], mid[1] + scale, ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //Vertical
	rotationalLine(point, mid[0], mid[1] - scale, mid[0] + scale, mid[1] - scale, ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //top
	rotationalLine(point, mid[0], mid[1] + scale, mid[0] - scale, mid[1] + scale, ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //bottom

	rotationalLine(point, mid[0] - scale, mid[1], mid[0] + scale, mid[1], ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //Horiztonal
	rotationalLine(point, mid[0] - scale, mid[1], mid[0] - scale, mid[1] - scale, ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //left
	rotationalLine(point, mid[0] + scale, mid[1], mid[0] + scale, mid[1] + scale, ang, D3DCOLOR_RGBA(0, 100, 255, 50)); //right
	ang += 0.051f / 4;
}



vec2_t point = { 1280 / 2, 720 / 2 };
vec2_t mid = { (1280 / 2), (720 / 2) };


int D3DDevice_PresentHk(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7) {

	ATG::g_pd3dDevice = (ATG::D3DDevice*)*(int*)((((int)pDevice) + 0x18));

	InitTexture();

	if (IsFontInit && IsTextureInit)
	{

		DrawBox(100, 100, 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255));

		DrawText("xbOnline Menu e e Menu", 1280 / 2, 720 / 2, 1, D3DCOLOR_RGBA(0, 255, 255, 50));

		DrawLine(1280 / 2, 720 / 2, 1280 / 2, (720 / 2) + 100, 5.4f, D3DCOLOR_RGBA(0, 255, 255, 50));

		DrawSwastika(point, mid, 30, 0);


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

