#include "main.h"

UIRender Drawing;
RayCasting_t RayCastingOriginal;

Detour XamInputGetStateDetour, D3DDevice_PresentDetour, RayCastingDetour;
D3DDevice_Present_t D3DDevice_PresentOriginal;

Detour AddMoveHook;
AddMoveStub AddMoveOriginal;

int Count = 0;

unsigned int WaitTimeV2 = 0;
unsigned int TimeCountV2 = 0;

void WaitV2(int time)
{
	TimeCountV2 = GetTickCount();
	WaitTimeV2 = time;
}

TransmitPacketStub TransmitPacketOriginal;
Detour TransmitPacketDetour;

int TransmitPacketHook(StreamManagerMoveClient* lol, int r4, int r5)
{
	__try
	{
		if (GetAsyncKeyState(XINPUT_GAMEPAD_LEFT_THUMB))
			*(int*)((int)lol + 0x40) += 100;
	}
	__except (1)
	{

	}

	return TransmitPacketOriginal((int)lol, (int)r4, (int)r5);
}

int RayCastingHook(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3)
{
	if ((GetTickCount() - TimeCountV2) > WaitTimeV2)
	{
		if (IsLocalClientAlive())
		{
			if (bAimbot)
				Aimbot(GetLocalPlayer());

		}

		WaitV2(5);
	}

	return RayCastingOriginal(r3, r4, r5, r6, r7, r8, r9, r10, f1, f2, f3);
}

int AddMove(StreamManagerMoveClient* r3, IMoveObject* pMove)
{
	if (setBitFlag)
	{
		pMove->m_EntryInput.m_CustomBitFlags ^= (pMove->m_EntryInput.m_CustomBitFlags ^ -true) & 2;
	}
	return AddMoveOriginal(r3, pMove);
}

int D3DDevice_PresentHook(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7) 
{

	ATG::g_pd3dDevice = (D3DDevice*)*(int*)((((int)pDevice) + 0x18));

	InitTexture();

	if (IsFontInit && IsTextureInit)
	{
		DrawMenu();

		if (IsLocalClientAlive())
		{
			DrawESP();

			DrawHealthBar(GetLocalPlayer()->GetClientSoldier()->m_Health, GetLocalPlayer()->GetClientSoldier()->m_MaxHealth);

			if (bHealSelf)
				if (GetLocalPlayer()->GetClientSoldier()->m_Health < 100.0f)
					if (GetAsyncKeyState(KEY_RT))
						HealSelf(GetLocalPlayer());

			*(int*)(0x836D01E4) = 0x39600000;//no bobbing
			*(int*)(0x836FDAC8) = 0x60000000;//zero out recoil/spread
			*(int*)(0x836bbf98) = 0x60000000;  //Force Bones to update

			setBitFlag = bFlyHack;

			if (bFlyHack)
				MovementHack();

			if (bUnlimitedAmmo)
				DoAmmo();
		}
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

	if (bAimbot &&  NearestPlayer != -1 && (( bAimingRequired && GetAsyncKeyState(0x5555)) || !bAimingRequired))
	{
		pState->Gamepad.sThumbRX = 0;
		pState->Gamepad.sThumbRY = 0;
	}

	return dwResult;
}
