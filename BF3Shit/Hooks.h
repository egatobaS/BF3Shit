#pragma once

extern UIRender Drawing;


extern Detour XamInputGetStateDetour, D3DDevice_PresentDetour;

typedef int(*D3DDevice_Present_t)(D3DDevice *pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);

extern D3DDevice_Present_t D3DDevice_PresentOriginal;

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
int D3DDevice_PresentHook(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);