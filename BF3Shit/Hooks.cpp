#include "main.h"

UIRender Drawing;

RayCasting_t RayCastingOriginal;
D3DDevice_Present_t D3DDevice_PresentOriginal;
AddMoveStub AddMoveOriginal;
sub_834F63C8_t sub_834F63C8Original;
TransmitPacketStub TransmitPacketOriginal;

Detour XamInputGetStateDetour, D3DDevice_PresentDetour, RayCastingDetour, AddMoveHook, sub_834F63C8Detour, XamUserGetXUIDDetour, XamUserGetSigninInfoDetour, XamUserGetNameDetour, TransmitPacketDetour;

unsigned int WaitTimeV2 = 0;
unsigned int TimeCountV2 = 0;

void WaitV2(int time)
{
	TimeCountV2 = GetTickCount();
	WaitTimeV2 = time;
}

int TransmitPacketHook(StreamManagerMoveClient* lol, int r4, int r5)
{
	__try
	{
		if (GetAsyncKeyState(XINPUT_GAMEPAD_LEFT_THUMB) && bPacketHack)
			*(int*)((int)lol + 0x40) += fPacketSpeed;
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

void FixMovement(EntryInputState* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove)
{
	float deltaView = CurAngle - OldAngle;

	if (CurAngle < OldAngle)
		deltaView = abs(CurAngle - OldAngle);
	else
		deltaView = 6.28319f - abs(OldAngle - CurAngle);

	if (CurAngle > XM_PI)
		deltaView = XM_2PI - deltaView;

	pCmd->m_analogInput[0] = cosf(deltaView)*fOldForward + cosf((deltaView)+XM_PIDIV2)*fOldSidemove;
	pCmd->m_analogInput[1] = sinf(deltaView)*fOldForward + sinf((deltaView)+XM_PIDIV2)*fOldSidemove;

}

int AddMove(StreamManagerMoveClient* r3, IMoveObject* pMove)
{
	if (setBitFlag) {
		pMove->m_EntryInput.m_CustomBitFlags ^= (pMove->m_EntryInput.m_CustomBitFlags ^ -true) & 2;
	}

	if (IsLocalClientAlive() && bSilentAimbot)
	{

		ClientPlayer* LocalPlayer = GetLocalPlayer();

		if (MmIsAddressValidPtr(LocalPlayer))
		{

			ClientSoldierEntity* pCSE = LocalPlayer->GetClientSoldier();

			if (MmIsAddressValidPtr(pCSE))
			{

				if (custom_isnan(pSilent.x) || custom_isnan(pSilent.y))
					return AddMoveOriginal(r3, pMove);

				if (!pCSE->m_sprinting && NearestPlayer != -1)
				{

					float OldAngle = pMove->m_EntryInput.m_WeaponAngles.x;

					pMove->m_EntryInput.m_WeaponAngles.x = (pSilent.x);
					pMove->m_EntryInput.m_WeaponAngles.y = (pSilent.y);

					FixMovement(&pMove->m_EntryInput, pMove->m_EntryInput.m_WeaponAngles.x, OldAngle, pMove->m_EntryInput.m_analogInput[0], pMove->m_EntryInput.m_analogInput[1]);
				}
			}
		}
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

			*(int*)(0x836D01E4) = bNoBBobbing ? 0x39600000 : 0x39600001;//no bobbing
			*(int*)(0x836FDAC8) = bNoSpreadFake ? 0x60000000 : 0x4E800421;//zero out recoil/spread
			*(int*)(0x836bbf98) = 0x60000000;  //Force Bones to update

			setBitFlag = bFlyHack;

			if (bFlyHack)
				MovementHack();

			ClientPlayer* LocalClientPlayer = GetLocalPlayer();

			if (MmIsAddressValidPtr(LocalClientPlayer))
			{
				ClientSoldierEntity* LocalClientSoldierEntity = LocalClientPlayer->GetClientSoldier();

				if (MmIsAddressValidPtr(LocalClientSoldierEntity))
				{
					if (bHealSelf && LocalClientSoldierEntity->m_Health < 100.0f && GetAsyncKeyState(KEY_RT))
						HealSelf(LocalClientPlayer);
				}
			}

			if (bTeamHeal)
				HealTeam(GetLocalPlayer());

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

	if (bAutoShoot)
	{
		if (IsLocalClientAlive())
		{
			if (bTriggerBot)
				pState->Gamepad.bRightTrigger = (bShoot ? 255 : 0);

			if (MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()))
			{
				if (MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon))
				{
					if (MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData))
					{
						if (MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData->m_pFiringFunctionData))
						{
							if ((GetTickCount() - ShootCount) > GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData->m_pFiringFunctionData->m_RateOfFire / 60)
							{
								ShootCount = GetTickCount();
								bShoot = !bShoot;
							}
						}
					}
				}
			}
		}
	}

	if (bAimbot && (NearestPlayer != -1 && !bSilentAimbot) && ((bAimingRequired && GetAsyncKeyState(0x5555)) || !bAimingRequired))
	{
		pState->Gamepad.sThumbRX = 0;
		pState->Gamepad.sThumbRY = 0;
	}

	return dwResult;
}

int(*sub_835F4878)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))0x835F4878;
int(*sub_83D131D0)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))0x83D131D0;

void SendMessage()
{
	int r4 = *(unsigned char*)0x840603E0;

	if (r4 != 1)
		return;

	int r15 = 0;

	*(unsigned char*)0x840603E0 = 0;

	unsigned char _0x50[0x200] = { 0 };

	r4 = sub_835F4878(_0x50, (unsigned char*)0x8406041F);


	int r3 = *(int*)(0x84122028);

	if (r3 == 0)
		return;

	r3 = *(int*)(r3 + 0x34);

	if (r3 == 0)
		return;

	r3 = *(int*)(r3 + 0x18);

	if (r3 == 0)
		return;

	r3 = *(int*)(r3 + 0x2E2C);

	if (r3 == 0)
		return;

	sub_83D131D0((unsigned char*)r3, (unsigned char*)r4);
}

int sub_834F63C8Hook(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3)
{
	SendMessage();

	return sub_834F63C8Original(r3, r4, r5, r6, r7, r8, r9, r10, f1, f2, f3);
}

DWORD XamUserGetXUIDHook(DWORD dwUserIndex, LPSTR pUserName, PXUID onlineOut)
{
	*onlineOut = *(INT64*)0x81E70200;
	return ERROR_SUCCESS;
}

DWORD XamUserGetSigninInfoHook(DWORD userIndex, DWORD flags, PXUSER_SIGNIN_INFO pSigninInfo) {

	DWORD result = XUserGetSigninInfo(userIndex, flags, pSigninInfo);

	pSigninInfo->xuid = *(INT64*)0x81E70200;
	strcpy(pSigninInfo->szUserName, (char*)0x81E70220);

	return result;
}

DWORD XamUserGetNameHook(DWORD dwUserIndex, LPSTR pUserName, DWORD cchUserName) {

	DWORD result = XamUserGetName(dwUserIndex, pUserName, cchUserName);

	strcpy(pUserName, (char*)0x81E70220);

	return result;
}


