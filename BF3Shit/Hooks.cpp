#include "main.h"

UIRender Drawing;

GetDispersionStub GetDispersionOriginal;
onPostPhysicsUpdateSync_t onPostPhysicsUpdateSyncOriginal;
sub_83CFF480_t sub_83CFF480Original;
RayCasting_t RayCastingOriginal;
D3DDevice_Present_t D3DDevice_PresentOriginal;
AddMoveStub AddMoveOriginal;
sub_834F63C8_t sub_834F63C8Original;
TransmitPacketStub TransmitPacketOriginal;
ClientConnection_SendMessage_t ClientConnection_SendMessageOriginal;
createScoringMessageStub createScoringMessageOriginal;

Detour* XamInputGetStateDetour, *D3DDevice_PresentDetour, *RayCastingDetour, *AddMoveHook, *sub_834F63C8Detour,
*XamUserGetXUIDDetour, *XamUserGetSigninInfoDetour, *XamUserGetNameDetour, *TransmitPacketDetour, *sub_83CFF480Detour,
*ClientConnection_SendMessageDetour, *onPostPhysicsUpdateSyncDetour, *GetDispersionDetour, *createScoringMessageDetour;

unsigned int WaitTimeV2 = 0;
unsigned int TimeCountV2 = 0;

void WaitV2(int time)
{
	TimeCountV2 = GetTickCount();
	WaitTimeV2 = time;
}

int createScoringMessagehk(int r3, int messageData, UINetworkHudScoringMessage *message)
{
	if (MmIsAddressValid(message))
	{
		if (!strcmp("ID_SCORE_HEADSHOT", message->m_descriptionSid))
		{
			strcpy(SoundPath, "Nigel:\\headshot.wav");
			runSoundsNow = true;
		}
		else if (!strcmp("ID_SCORE_DOUBLE_KILL", message->m_descriptionSid))
		{
			strcpy(SoundPath, "Nigel:\\doublekill.wav");
			runSoundsNow = true;
		}
		else if (!strcmp("ID_SCORE_TRIPE_KILL", message->m_descriptionSid))
		{
			strcpy(SoundPath, "Nigel:\\triplekill.wav");
			runSoundsNow = true;
		}
		else if (!strcmp("ID_SCORE_SQUAD_WIPE", message->m_descriptionSid))
		{
			strcpy(SoundPath, "Nigel:\\multikill.wav");
			runSoundsNow = true;
		}
	}

	return createScoringMessageOriginal(r3, messageData, message);
}

int GetDispersionHook(WeaponSway* r3, LinearTransform* swayTransform, bool scaletransform)
{
	ClientPlayer* pCP = GetLocalPlayer();
	if (!MmIsAddressValid(pCP))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	ClientSoldierEntity* pCSE = pCP->m_pControlledControllable;
	if (!MmIsAddressValid(pCSE))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValid(pCSWC))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValid(pCSW))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	ClientSoldierAimingSimulation* pCSAS = pCSW->m_pClientSoldierAimingSimulation;
	if (!MmIsAddressValid(pCSAS))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	AimAssist* pAA = pCSAS->m_fpsAimer;
	if (!MmIsAddressValid(pAA))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	WeaponFiring* pWF = pCSW->m_pPrimaryFiring;
	if (!MmIsAddressValid(pWF))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	WeaponSway* pWS = pWF->m_pSway;
	if (!MmIsAddressValid(pWS))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	SoldierWeaponData* pSWD = pCSW->m_pSoldierWeaponData;
	if (!MmIsAddressValid(pSWD))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	WeaponFiringData* pWFD = pSWD->m_pWeaponFiringData;
	if (!MmIsAddressValid(pWFD))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	FiringFunctionData* pFFD = pWFD->m_pFiringFunctionData;
	if (!MmIsAddressValid(pFFD))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	BulletEntityData* pBED = pFFD->m_pBulletEntityData;
	if (!MmIsAddressValid(pBED))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	if (!MmIsAddressValid(pTarget))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	ClientSoldierEntity* pCSET = pTarget->m_pControlledControllable;
	if (!MmIsAddressValid(pCSET))
		return GetDispersionOriginal(r3, swayTransform, scaletransform);

	if (r3->m_currentDispersionDeviation.m_Yaw > 0 || r3->m_currentDispersionDeviation.m_Yaw < 0)
	{
		DamagePlayer(pTarget, GetLocalPlayer(), bUnfairAimbot ? 100.0f : pBED->m_DamageMax, bSpoofTarget ? getUA(pTarget) : getUA(GetLocalPlayer()), bHeadshots ? HRT_Head : (HitReactionType)0);
		pTarget = NULL;
	}

	return GetDispersionOriginal(r3, swayTransform, scaletransform);
}

int TransmitPacketHook(StreamManagerMoveClient* lol, int r4, int r5)
{
	if (MmIsAddressValidPtr(lol))
	{
		if (GetAsyncKeyState(XINPUT_GAMEPAD_LEFT_THUMB) && bPacketHack)
			*(int*)((int)lol + 0x40) += fPacketSpeed;
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
	if (setBitFlag) {
		pMove->m_EntryInput.m_CustomBitFlags ^= (pMove->m_EntryInput.m_CustomBitFlags ^ -1) & 2;
	}

	if (IsLocalClientAlive() && bSilentAimbot || bNoSpread)
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

					if (bNoSpread)
						DoTheSpreadHack_Silent();

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
		if (IsLocalClientAlive())
		{

			ClientGameContext* pCGC = ClientGameContext::GetInstance();
			if (!MmIsAddressValidPtr(pCGC))
				return NULL;

			pCGC->m_pLevel->m_worldRenderModule->m_worldRenderer->m_worldRenderSettings->m_lightBrightMap = bBlueTint;

			DrawESP();

			*(int*)(Addresses->_0x836bbf98) = Addresses->_0x60000000;  //Force Bones to update

			*(int*)(Addresses->_0x836D01E4) = bNoBBobbing ? Addresses->_0x39600000 : Addresses->_0x39600001;//no bobbing
			*(int*)(Addresses->_0x834FC41C) = bUAV ? Addresses->_0x38600001 : Addresses->_0x38600000;
			*(int*)(Addresses->_0x834FB424) = bUAV ? Addresses->_0x39600001 : Addresses->_0x39600000;
			*(int*)(Addresses->_0x834FB3D0) = bUAV ? Addresses->_0x39600001 : Addresses->_0x39600000;
			*(int*)(Addresses->_0x83504BBC) = bUAV ? Addresses->_0x42400020 : Addresses->_0x4240004C;
			*(int*)(Addresses->_0x835054C0) = bUAV ? Addresses->_0x60000000 : Addresses->_0x419A0B38;
			*(int*)(Addresses->_0x83505268) = bUAV ? Addresses->_0x60000000 : Addresses->_0x409A0DA4;
			*(int*)(Addresses->_0x835054FC) = bUAV ? Addresses->_0x4800003C : Addresses->_0x419A003C;
			*(int*)(Addresses->_0x8350498C) = bUAV ? Addresses->_0x39600001 : Addresses->_0x89590035;
			*(int*)(Addresses->_0x83504990) = bUAV ? Addresses->_0x917F02A4 : Addresses->_0x2B0A0000;
			*(int*)(Addresses->_0x83504994) = bUAV ? Addresses->_0x60000000 : Addresses->_0x419A01AC;

			setBitFlag = bFlyHack;

			if (bHealSelf)
				SelfHeal();

			if (bFlyHack)
				MovementHack();

			if (bTeamHeal)
				HealTeam(GetLocalPlayer());

			if (bUnlimitedAmmo)
				DoAmmo();
		}

		if (bForceSquadSpawn)
			ForceSquadSpawn();

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

	if (bAimbot && (NearestPlayer != -1 && !bSilentAimbot) && ((bAimingRequired && GetAsyncKeyState(0x5555)) || !bAimingRequired))
	{
		pState->Gamepad.sThumbRX = 0;
		pState->Gamepad.sThumbRY = 0;
	}

	if (bAutoShoot)
	{
		if (IsLocalClientAlive())
		{
			if (bTriggerBot)
				pState->Gamepad.bRightTrigger = (bShoot ? 255 : 0);

			ClientSoldierEntity* pCSE = GetLocalPlayer()->GetClientSoldier();
			if (!MmIsAddressValidPtr(pCSE))
				return dwResult;

			ClientSoldierPrediction* pCSP = pCSE->m_pClientSoldierPrediction;
			if (!MmIsAddressValidPtr(pCSP))
				return dwResult;

			ClientBoneCollisionComponent* pCBCC = pCSE->m_pClientBoneCollisionComponent;
			if (!MmIsAddressValidPtr(pCBCC))
				return dwResult;

			ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
			if (!MmIsAddressValidPtr(pCSWC))
				return dwResult;

			ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
			if (!MmIsAddressValidPtr(pCSW))
				return dwResult;

			ClientWeapon* pWeapon = pCSW->m_pWeapon;
			if (!MmIsAddressValidPtr(pWeapon))
				return dwResult;

			WeaponFiringData *pFireData = pWeapon->m_pWeaponFiringData;
			if (!MmIsAddressValidPtr(pFireData))
				return dwResult;

			FiringFunctionData * FiringFunctionData = pFireData->m_pFiringFunctionData;
			if (!MmIsAddressValidPtr(FiringFunctionData))
				return dwResult;


			if ((GetTickCount() - ShootCount) > FiringFunctionData->m_RateOfFire / 60)
			{
				ShootCount = GetTickCount();
				bShoot = !bShoot;
			}
		}
	}

	return dwResult;
}

void SendMessage()
{
	int r4 = *(unsigned char*)Addresses->_0x840603E0;

	if (r4 != 1)
		return;

	int r15 = 0;

	*(unsigned char*)Addresses->_0x840603E0 = 0;

	unsigned char _0x50[0x200] = { 0 };

	r4 = sub_835F4878(_0x50, (unsigned char*)Addresses->_0x8406041F);


	int r3 = *(int*)(Addresses->_0x84122028);

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

int sub_83CFF480Hook(unsigned long long r3, unsigned long long r4)
{
	if (!MmIsAddressValidPtr((void*)r4) || !MmIsAddressValidPtr((void*)r3))
		return 0;
	int a = 0;

	__try {
		a = sub_83CFF480Original(r3, r4);
	}
	__except (0)
	{

	}

	return a;
}

int ClientConnection_SendMessageHook(ClientConnection* Connection, _NetworkableMessage* Message)
{
	return ClientConnection_SendMessageOriginal(Connection, Message);
}

void onPostPhysicsUpdateSyncHook(ClientSpottingComponent* Component, ClientPlayer* LocalClientPlayer)
{
	if (bAutoSpot)
		SendSpot(Component, LocalClientPlayer);

	onPostPhysicsUpdateSyncOriginal(Component, LocalClientPlayer);
}