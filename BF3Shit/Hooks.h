#pragma once

extern UIRender Drawing;

typedef int(*TransmitPacketStub)(int lol, int r4, int r5);
extern TransmitPacketStub TransmitPacketOriginal;

typedef int(*RayCasting_t)(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
extern RayCasting_t RayCastingOriginal;

typedef int(*D3DDevice_Present_t)(D3DDevice *pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);
extern D3DDevice_Present_t D3DDevice_PresentOriginal;

typedef int(*AddMoveStub)(StreamManagerMoveClient* r3, IMoveObject* r4);
extern AddMoveStub AddMoveOriginal;

extern Detour XamInputGetStateDetour, D3DDevice_PresentDetour, RayCastingDetour, TransmitPacketDetour, AddMoveHook;

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
int RayCastingHook(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
int AddMove(StreamManagerMoveClient * r3, IMoveObject * pMove);
int TransmitPacketHook(StreamManagerMoveClient* lol, int r4, int r5);
int D3DDevice_PresentHook(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);