#include "main.h"

UIRender Drawing;

Detour XamInputGetStateDetour, D3DDevice_PresentDetour;
D3DDevice_Present_t D3DDevice_PresentOriginal;

int D3DDevice_PresentHook(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7) {

	ATG::g_pd3dDevice = (D3DDevice*)*(int*)((((int)pDevice) + 0x18));

	InitTexture();

	if (IsFontInit && IsTextureInit)
	{
		DrawMenu();
	}

	return D3DDevice_PresentOriginal(pDevice, r4, r5, r6, r7);;
}


DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	DWORD dwResult = XInputGetState(dwUserIndex, pState);

	if (dwUserIndex != 0 || dwResult != 0)
		return dwResult;

	if (MenuBase.isMenuOpened) {
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
	}

	return dwResult;
}
