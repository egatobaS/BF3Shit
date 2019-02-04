#include "main.h"

Vector3 pSilent;

bool isClientWallable[24] = { 0 };
bool setBitFlag = false;
bool bShoot = false;
bool bTriggerBot = false;
int ShootCount = 0;

int NearestPlayer = -1;
int UACounterInt = 0;

WeaponSway::Deviation* pRecoil = 0;
WeaponSway::Deviation *pSpread = 0;

int(*GetAmmoPtr)(int x, int y, int z) = (int(*)(int x, int y, int z))0x83266AC0;
int(*CCMessage)(ClientConnection*, Message*) = (int(*)(ClientConnection*, Message*))0x831FAD00;
int(*ReloadMessageFunction)(int r3, int r4, int r5) = (int(*)(int r3, int r4, int r5))0x834CC888;
int(*AddDamageData)(ClientConnection*, ClientDamageStream::DamageData*) = (int(*)(ClientConnection*, ClientDamageStream::DamageData*))0x831FB1D8;
int(*GetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer*) = (int(*)(ClientPlayerScoreManager*, ClientPlayer*))0x83212338;
UnlockAssetBase(*GetWeaponID)(ClientWeapon*) = (UnlockAssetBase(*)(ClientWeapon*))0x836F4390;

bool WorldToScreen(Vector3 WorldPos, Vector3* ScreenPos)
{
	GameRenderer* renderer = GameRenderer::Singleton();

	if (renderer == NULL)
		return false;

	if (renderer->m_viewParams.view.Update() == false)
		return false;

	LinearTransform ScreenTransform = renderer->m_viewParams.view.m_viewProjectionMatrix;

	float mX = 1280.0f * 0.5f;
	float mY = 720.0f * 0.5f;

	float w =

		ScreenTransform(0, 3) * WorldPos.x +
		ScreenTransform(1, 3) * WorldPos.y +
		ScreenTransform(2, 3) * WorldPos.z +
		ScreenTransform(3, 3);


	if (w < 0.65f)
	{
		return false;
	}

	float x =
		ScreenTransform(0, 0) * WorldPos.x +
		ScreenTransform(1, 0) * WorldPos.y +
		ScreenTransform(2, 0) * WorldPos.z +
		ScreenTransform(3, 0);

	float y =
		ScreenTransform(0, 1) * WorldPos.x +
		ScreenTransform(1, 1) * WorldPos.y +
		ScreenTransform(2, 1) * WorldPos.z +
		ScreenTransform(3, 1);

	ScreenPos->x = (mX + mX * x / w);
	ScreenPos->y = (mY - mY * y / w);
	ScreenPos->z = w;

	if (ScreenPos->x < -3000.0f || ScreenPos->x > 6000.0f) return false;

	return true;
}

ClientPlayer* GetLocalPlayer()
{
	ClientGameContext* pCGC = ClientGameContext::GetInstance();
	if (!MmIsAddressValidPtr(pCGC))
		return NULL;

	ClientPlayerManager* pCPM = pCGC->m_pClientPlayerManager;
	if (!MmIsAddressValidPtr(pCPM))
		return NULL;

	if (!MmIsAddressValidPtr(pCPM->m_pLocalPlayer))
		return NULL;

	return pCPM->m_pLocalPlayer;
}

ClientPlayer* GetPlayerById(unsigned int id)
{
	ClientGameContext* pCGC = ClientGameContext::GetInstance();
	if (!MmIsAddressValidPtr(pCGC))
		return NULL;

	ClientPlayerManager* pCPM = pCGC->m_pClientPlayerManager;
	if (!MmIsAddressValidPtr(pCPM))
		return NULL;

	if (!MmIsAddressValidPtr(pCPM->m_ppPlayers[id]))
		return NULL;

	return pCPM->m_ppPlayers[id];
}

bool IsLocalClientAlive()
{
	ClientPlayer* pLocal = GetLocalPlayer();
	ClientSoldierEntity* pCSE = pLocal->GetClientSoldier();
	if (!MmIsAddressValidPtr(pCSE))
		return false;

	ClientSoldierReplication* pCSR = pCSE->m_pClientSoldierReplication;
	if (!MmIsAddressValidPtr(pCSR))
		return false;

	if (pCSE->m_Health < 0.1f)
		return false;

	ClientBoneCollisionComponent* pCBCC = pCSE->m_pClientBoneCollisionComponent;
	if (!MmIsAddressValidPtr(pCBCC))
		return false;

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValidPtr(pCSWC))
		return false;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValidPtr(pCSW))
		return false;

	ClientWeapon* pCW = pCSW->m_pWeapon;
	if (!MmIsAddressValidPtr(pCW))
		return false;

	WeaponFiring* pWF = pCSW->m_pPrimaryFiring;
	if (!MmIsAddressValidPtr(pWF))
		return false;

	ClientSoldierAimingSimulation* pCSAS = pCSW->m_pClientSoldierAimingSimulation;
	if (!MmIsAddressValidPtr(pCSAS))
		return false;

	WeaponFiringData *pFireData = pCSWC->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData;
	if (pFireData == 0)
		return false;

	BulletEntityData *pProjData = pFireData->m_pFiringFunctionData->m_pBulletEntityData;
	if (pProjData == 0)
		return false;

	return true;
}

bool IsClientAlive(ClientPlayer* pTarget)
{
	if (!MmIsAddressValidPtr(pTarget))
		return false;

	if (pTarget->isInVehicle())
		return false;

	ClientSoldierEntity* pCSE = pTarget->GetClientSoldier();
	if (!MmIsAddressValidPtr(pCSE))
		return false;

	ClientSoldierPrediction* pCSP = pCSE->m_pClientSoldierPrediction;
	if (!MmIsAddressValidPtr(pCSP))
		return false;

	ClientSoldierReplication* pCSR = pCSE->m_pClientSoldierReplication;
	if (!MmIsAddressValidPtr(pCSR))
		return false;

	if (pCSE->m_Health < 0.1f)
		return false;

	ClientBoneCollisionComponent* pCBCC = pCSE->m_pClientBoneCollisionComponent;
	if (!MmIsAddressValidPtr(pCBCC))
		return false;

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValidPtr(pCSWC))
		return false;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValidPtr(pCSW))
		return false;

	ClientWeapon* pCW = pCSW->m_pWeapon;
	if (!MmIsAddressValidPtr(pCW))
		return false;

	//WeaponModifier* pWM = pCW->m_pWeaponModifier;
	//if (!MmIsAddressValidPtr(pWM))
	//	return false;
	//
	//UnlockAssetBase* pUAB = pWM->m_pWeaponUnlockAsset;
	//if (!MmIsAddressValidPtr(pUAB))
	//	return false;

	return true;
}

void setIsAuthoritativeMovementActive(EntryInputState *pEIS, bool active)
{
	pEIS->m_CustomBitFlags ^= (pEIS->m_CustomBitFlags ^ -active) & 2;
}

void MovementHack()
{
	bool bStay = 0;

	GameRenderer* renderer = GameRenderer::Singleton();

	if (renderer == NULL)
		return;

	if (renderer->m_viewParams.view.Update() == false)
		return;

	MatrixD* Mat = (MatrixD*)(((int)renderer) + 0xDB0);

	Vector3 vOrigin = renderer->m_viewParams.firstPersonTransform.trans;
	Vector3 vForward = Mat->Forward();
	vForward.Normalize();
	Vector3 vRayEnd = vOrigin + (vForward * FlySpeed);
	Vector3 vDiff = vRayEnd - vOrigin;
	vDiff.Normalize();
	float factor = 50.0f / sqrt(vDiff.x*vDiff.x + vDiff.y * vDiff.y + vDiff.z * vDiff.z);


	if (GetAsyncKeyState(0x0100))
	{

		setBitFlag = true;
		memcpy(&GetLocalPlayer()->m_pExternalInputState->m_authoritativeMovementVelocity, &vDiff, 0xC);
		setIsAuthoritativeMovementActive(GetLocalPlayer()->m_pExternalInputState, true);

	}
	else
	{
		setBitFlag = true;
		GetLocalPlayer()->m_pExternalInputState->m_authoritativeMovementVelocity = Vector4(0, 0, 0, 0);
		setIsAuthoritativeMovementActive(GetLocalPlayer()->m_pExternalInputState, false);
	}
}

void DrawCompass(Vector3 ClientPosition, D3DCOLOR Color, float CompassSize)
{
	__try
	{
		Vector2 cCenter = Vector2(1280.0f / 2.0f, 720.0f / 2.0f);

		float RadarX = ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position.x - ClientPosition.x;
		float RadarY = ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position.z - ClientPosition.z;

		float Angle = (ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer->m_pControlledControllable->m_ViewAngles.x * (360.0f / 6.4f)) / 180.0f * 3.14159f;

		Vector2 ViewAngles = ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer->m_pControlledControllable->m_ViewAngles;

		float RotateX = RadarY * cos(Angle) - RadarX * sin(Angle);
		float RotateY = RadarX * cos(Angle) + RadarY * sin(Angle);

		float FinalY = cCenter.y - RotateY;

		float angle = atan(RotateX / RotateY) * (180.0f / 3.14159f);
		float FinalA = FinalY > cCenter.y ? -angle - 180.0f : -angle;

		if (FinalA < 0)
			FinalA += 360.0f;

		float radians = (3.14159f / 180.f) * (FinalA + 183.5f);
		float radians1 = (3.14159f / 180.f) * (FinalA + 183.5f + 2.f);
		float radians2 = (3.14159f / 180.f) * (FinalA + 183.5f - 2.f);

		Vector2 CircleOut = Vector2(cCenter.x - (cos(radians) * (fCompassSize + (fCompassSize / 30.f))), cCenter.y + (sin(radians) * (fCompassSize + (fCompassSize / 30.f))));
		Vector2 CircleOut1 = Vector2(cCenter.x - (cos(radians1) * (fCompassSize - (fCompassSize / 15.f))), cCenter.y + (sin(radians1) * (fCompassSize - (fCompassSize / 15.f))));
		Vector2 CircleOut2 = Vector2(cCenter.x - (cos(radians2) * (fCompassSize - (fCompassSize / 15.f))), cCenter.y + (sin(radians2) * (fCompassSize - (fCompassSize / 15.f))));

		DrawLine(CircleOut.x, CircleOut.y, CircleOut1.x, CircleOut1.y, 1, Color);
		DrawLine(CircleOut.x, CircleOut.y, CircleOut2.x, CircleOut2.y, 1, Color);
		DrawLine(CircleOut1.x, CircleOut1.y, CircleOut2.x, CircleOut2.y, 1, Color);
	}
	__except (1)
	{

	}
}

Vector3 Multiply(Vector3 vec, Matrix* mat)
{
	return Vector3(mat->operator()(0, 0) * vec.x + mat->operator()(1, 0)* vec.y + mat->operator()(2, 0)* vec.z,
		mat->operator()(0, 1)* vec.x + mat->operator()(1, 1)* vec.y + mat->operator()(2, 1)* vec.z,
		mat->operator()(0, 2)* vec.x + mat->operator()(1, 2)* vec.y + mat->operator()(2, 2)* vec.z);
}

bool Draw2DBox(ClientVehicleEntity* pEnt, D3DCOLOR color, float size)
{
	Matrix* trans = new Matrix;
	Vector3 Pos;

	AxisAlignedBox* TransAABB = new AxisAlignedBox;

	if (!MmIsAddressValidPtr(pEnt))
		return false;

	pEnt->computeBoundingBox(TransAABB);

	pEnt->getTransform(trans);
	Pos = Vector3(trans->operator()(3, 0), trans->operator()(3, 1), trans->operator()(3, 2));

	Vector3 aabbMin = Vector3(TransAABB->min.x, TransAABB->min.y, TransAABB->min.z);
	Vector3 aabbMax = Vector3(TransAABB->max.x, TransAABB->max.y, TransAABB->max.z);
	Vector3 min = aabbMin * size;
	Vector3 max = aabbMax * size;
	Vector3 crnr2 = Pos + Multiply(Vector3(max.x, min.y, min.z), trans);
	Vector3 crnr3 = Pos + Multiply(Vector3(max.x, min.y, max.z), trans);
	Vector3 crnr4 = Pos + Multiply(Vector3(min.x, min.y, max.z), trans);
	Vector3 crnr5 = Pos + Multiply(Vector3(min.x, max.y, max.z), trans);
	Vector3 crnr6 = Pos + Multiply(Vector3(min.x, max.y, min.z), trans);
	Vector3 crnr7 = Pos + Multiply(Vector3(max.x, max.y, min.z), trans);

	min = Pos + Multiply(min, trans);
	max = Pos + Multiply(max, trans);

	if (WorldToScreen(min, &min) && WorldToScreen(max, &max) && WorldToScreen(crnr2, &crnr2) && WorldToScreen(crnr3, &crnr3) && WorldToScreen(crnr4, &crnr4) && WorldToScreen(crnr5, &crnr5) && WorldToScreen(crnr6, &crnr6) && WorldToScreen(crnr7, &crnr7))
	{
		Vector3 arr[] = { min, max, crnr2, crnr3, crnr4, crnr5, crnr6, crnr7 };

		float l = min.x;
		float t = min.y;
		float r = min.x;
		float b = min.y;

		for (int i = 0; i < 8; i++)
		{
			if (l > arr[i].x) l = arr[i].x;
			if (t < arr[i].y) t = arr[i].y;
			if (r < arr[i].x) r = arr[i].x;
			if (b > arr[i].y) b = arr[i].y;
		}

		DrawLine(l, b, l, t, 1, color);
		DrawLine(l, t, r, t, 1, color);
		DrawLine(r, t, r, b, 1, color);
		DrawLine(r, b, l, b, 1, color);

	}

	delete trans;
	delete TransAABB;

	return true;
}

bool TransformDrawAABB(ClientVehicleEntity* pEnt, D3DCOLOR color, float size)
{
	Matrix* trans = new Matrix;
	Vector3 Pos;

	AxisAlignedBox* TransAABB = new AxisAlignedBox;

	if (!MmIsAddressValidPtr(pEnt))
		return false;

	pEnt->computeBoundingBox(TransAABB);

	pEnt->getTransform(trans);
	Pos = Vector3(trans->operator()(3, 0), trans->operator()(3, 1), trans->operator()(3, 2));

	Vector3 aabbMin = Vector3(TransAABB->min.x, TransAABB->min.y, TransAABB->min.z);
	Vector3 aabbMax = Vector3(TransAABB->max.x, TransAABB->max.y, TransAABB->max.z);
	Vector3 min = aabbMin * size;
	Vector3 max = aabbMax * size;
	Vector3 crnr2 = Pos + Multiply(Vector3(max.x, min.y, min.z), trans);
	Vector3 crnr3 = Pos + Multiply(Vector3(max.x, min.y, max.z), trans);
	Vector3 crnr4 = Pos + Multiply(Vector3(min.x, min.y, max.z), trans);
	Vector3 crnr5 = Pos + Multiply(Vector3(min.x, max.y, max.z), trans);
	Vector3 crnr6 = Pos + Multiply(Vector3(min.x, max.y, min.z), trans);
	Vector3 crnr7 = Pos + Multiply(Vector3(max.x, max.y, min.z), trans);

	min = Pos + Multiply(min, trans);
	max = Pos + Multiply(max, trans);

	if (WorldToScreen(min, &min) && WorldToScreen(max, &max) && WorldToScreen(crnr2, &crnr2) && WorldToScreen(crnr3, &crnr3) && WorldToScreen(crnr4, &crnr4) && WorldToScreen(crnr5, &crnr5) && WorldToScreen(crnr6, &crnr6) && WorldToScreen(crnr7, &crnr7))
	{
		//From min to 2, 4 and 6
		DrawLine(min.x, min.y, crnr2.x, crnr2.y, 1, color);
		DrawLine(min.x, min.y, crnr4.x, crnr4.y, 1, color);
		DrawLine(min.x, min.y, crnr6.x, crnr6.y, 1, color);

		//From max to 5, 7 and 3
		DrawLine(max.x, max.y, crnr5.x, crnr5.y, 1, color);
		DrawLine(max.x, max.y, crnr7.x, crnr7.y, 1, color);
		DrawLine(max.x, max.y, crnr3.x, crnr3.y, 1, color);

		//From 2 to 7 and 3
		DrawLine(crnr2.x, crnr2.y, crnr7.x, crnr7.y, 1, color);
		DrawLine(crnr2.x, crnr2.y, crnr3.x, crnr3.y, 1, color);

		//From 4 to 5 and 3
		DrawLine(crnr4.x, crnr4.y, crnr5.x, crnr5.y, 1, color);
		DrawLine(crnr4.x, crnr4.y, crnr3.x, crnr3.y, 1, color);

		//From 6 to 5 and 7
		DrawLine(crnr6.x, crnr6.y, crnr5.x, crnr5.y, 1, color);
		DrawLine(crnr6.x, crnr6.y, crnr7.x, crnr7.y, 1, color);
	}

	delete trans;
	delete TransAABB;

	return true;
}

bool GetBone(ClientSoldierEntity* pEnt, Vector3 *vOut, int iBone)
{
	if (iBone == -1)
		return false;

	if (!MmIsAddressValidPtr(pEnt))
		return false;

	if (!iBone)
		return false;

	if (!MmIsAddressValidPtr(vOut))
		return false;

	ClientAntAnimatableComponent* pAnt = pEnt->m_pAntAnimatable2;
	if (!MmIsAddressValidPtr(pAnt))
		return false;

	pAnt->m_handler.m_hadVisualUpdate = true;

	ClientRagDollComponent * pCRC = pEnt->m_pClientRagdollComponent;

	if (!MmIsAddressValidPtr(pCRC))
		return false;

	if (pCRC->m_UpdatePoseResultData.m_ValidTransforms)
	{

		QuatTransform* pQuat = pCRC->m_UpdatePoseResultData.m_ActiveWorldTransforms;

		if (!MmIsAddressValidPtr(pQuat))
			return false;

		Vector4 vTmp = pQuat[iBone].m_TransAndScale;

		vOut->x = vTmp.x;
		vOut->y = vTmp.y;
		vOut->z = vTmp.z;

		return true;
	}

	return false;
}

void DrawBoneLine(ClientPlayer* entity, int tagname1, int tagname2, D3DCOLOR col)
{
	Vector3 Origin1, Origin2;

	if (GetBone(entity->m_pControlledControllable, &Origin1, tagname1) && GetBone(entity->m_pControlledControllable, &Origin2, tagname2))
	{
		Vector3 Loc1, Loc2;
		if (WorldToScreen(Origin1, &Loc1) && WorldToScreen(Origin2, &Loc2))
			DrawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, 1.0f, col);
	}
}

void DoAllBones(ClientPlayer* Client, D3DCOLOR boneESPCol)
{
	//neck
	DrawBoneLine(Client, UpdatePoseResultData::Head, UpdatePoseResultData::Neck, boneESPCol);

	//left arm
	DrawBoneLine(Client, UpdatePoseResultData::Neck, UpdatePoseResultData::LeftShoulder, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::LeftShoulder, UpdatePoseResultData::LeftElbowRoll, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::LeftElbowRoll, UpdatePoseResultData::RightHand, boneESPCol);

	//right arm
	DrawBoneLine(Client, UpdatePoseResultData::Neck, UpdatePoseResultData::RightShoulder, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::RightShoulder, UpdatePoseResultData::RightElbowRoll, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::RightElbowRoll, UpdatePoseResultData::RightHand, boneESPCol);

	//spine
	DrawBoneLine(Client, UpdatePoseResultData::Neck, UpdatePoseResultData::Spine, boneESPCol);

	//left leg
	DrawBoneLine(Client, UpdatePoseResultData::Spine, UpdatePoseResultData::LeftKneeRoll, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::LeftKneeRoll, UpdatePoseResultData::LeftFoot, boneESPCol);

	//right leg
	DrawBoneLine(Client, UpdatePoseResultData::Spine, UpdatePoseResultData::RightKneeRoll, boneESPCol);
	DrawBoneLine(Client, UpdatePoseResultData::RightKneeRoll, UpdatePoseResultData::RightFoot, boneESPCol);
}

float GetDistance(Vector3 c1, Vector3 c2)
{
	Vector3 Sub = c1 - c2;
	return (sqrt((float)((Sub.x * Sub.x) + (Sub.y * Sub.y) + (Sub.z * Sub.z))) / 55.0f);
}

bool DrawESP() //TODO: BoneESP and a Visibility Check
{
	ClientPlayer* LocalPlayer = GetLocalPlayer();

	if (MmIsAddressValidPtr(LocalPlayer))
	{
		ClientSoldierEntity* pCSE = LocalPlayer->GetClientSoldier();

		if (MmIsAddressValidPtr(pCSE))
		{
			DrawHealthBar(pCSE->m_Health, pCSE->m_MaxHealth);
		}
	}

	for (int i = 0; i < 24; i++)
	{
		ClientPlayer* Target = GetPlayerById(i);

		if (!MmIsAddressValidPtr(Target))
			continue;

		if (Target->isInVehicle())
		{
			if (!MmIsAddressValidPtr(Target->GetClientVehicleEntity()))
				continue;

			if (bVehicleESP)
			{
				switch (ESPType)
				{
				case 1:
				{
					if (MmIsAddressValidPtr(Target->GetClientSoldier()))
						Draw2DBox(Target->GetClientVehicleEntity(), D3DCOLOR_RGBA(255, 255, 0, 255), 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(Target->GetClientSoldier()))
						TransformDrawAABB(Target->GetClientVehicleEntity(), D3DCOLOR_RGBA(255, 255, 0, 255), 0.8);
					break;
				}
				}
			}
		}

		if (!IsClientAlive(Target))
			continue;

		if (Target == GetLocalPlayer())
			continue;

		ClientSoldierEntity* pCSE = Target->GetClientSoldier();
		if (!MmIsAddressValidPtr(pCSE))
			continue;

		ClientSoldierPrediction* pCSP = pCSE->m_pClientSoldierPrediction;
		if (!MmIsAddressValidPtr(pCSP))
			continue;

		Vector3 ClientPosition = pCSP->m_Position;

		ClientSoldierEntity* LocalpCSE = GetLocalPlayer()->GetClientSoldier();
		if (!MmIsAddressValidPtr(LocalpCSE))
			continue;

		ClientSoldierPrediction* LocalpCSP = LocalpCSE->m_pClientSoldierPrediction;
		if (!MmIsAddressValidPtr(LocalpCSP))
			continue;

		Vector3 LocalPosition = LocalpCSP->m_Position;

		if ((bEnemyName && Target->m_teamId != GetLocalPlayer()->m_teamId) || (bESPFriendly && Target->m_teamId == GetLocalPlayer()->m_teamId))
		{
			float fFontSize = (0.5 - (GetDistance(LocalPosition, ClientPosition) / 50));
			if (fFontSize < 0.3)
				fFontSize = 0.3;

			Vector3 PlayerHead;

			if (GetBone(Target->GetClientSoldier(), &PlayerHead, UpdatePoseResultData::Head))
			{
				float fHeight = PlayerHead.y - ClientPosition.y;

				Vector3 ScreenCoords;
				if (WorldToScreen(PlayerHead, &ScreenCoords))
				{
					float y = ((ScreenCoords.y) - (fHeight + ((m_Font.GetFontHeight() * fFontSize) * 2)) + (m_Font.GetFontHeight() * fFontSize));
					DrawTextCentered(Target->m_Name, ScreenCoords.x, y, fFontSize, D3DCOLOR_RGBA(255, 255, 255, 255), 0);
				}
			}
		}

		if (Target->m_teamId == GetLocalPlayer()->m_teamId)
		{
			if (bDrawSnapLinesF)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
					DrawLine(1280 / 2, 720 / 2, ClientPosition.x, ClientPosition.y, 1, D3DCOLOR_RGBA(0, 255, 0, 255));
			}

			if (bFCompass)
				DrawCompass(ClientPosition, D3DCOLOR_RGBA(0, 255, 0, 255), 120.0f);

			if (bDrawBonesF)
				DoAllBones(Target, D3DCOLOR_RGBA(0, 120, 230, 255));

			if (bESPFriendly)
			{
				switch (ESPType)
				{
				case 1:
				{
					if (MmIsAddressValidPtr(Target->GetClientSoldier()))
						Draw2DBox((ClientVehicleEntity*)Target->GetClientSoldier(), D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(Target->GetClientSoldier()))
						TransformDrawAABB((ClientVehicleEntity*)Target->GetClientSoldier(), D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				}
			}
		}
		else
		{
			D3DCOLOR ESPColor = isClientWallable[i] == 0 ? D3DCOLOR_RGBA(255, 0, 0, 255) : D3DCOLOR_RGBA(255, 255, 0, 255);

			if (bDrawSnapLinesE)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
					DrawLine(1280 / 2, 720 / 2, ClientPosition.x, ClientPosition.y, 1, ESPColor);
			}

			if (bECompass)
				DrawCompass(ClientPosition, ESPColor, 120.0f);

			if (bDrawBonesE)
				DoAllBones(Target, D3DCOLOR_RGBA(0, 120, 230, 255));

			if (bESPEnemy)
			{
				switch (ESPType)
				{
				case 1:
				{
					if (MmIsAddressValidPtr(Target->GetClientSoldier()))
						Draw2DBox((ClientVehicleEntity*)Target->GetClientSoldier(), ESPColor, 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(GetPlayerById(i)->GetClientSoldier()))
						TransformDrawAABB((ClientVehicleEntity*)Target->GetClientSoldier(), ESPColor, 0.8);
					break;
				}
				}
			}
		}
	}

	return 0;
}

float solveQuadratic(float a, float b, float c)
{
	return (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
}

bool custom_isnan(double var)
{
	volatile double d = var;
	return d != d;
}

void CorrectRecoil(Vector2* pAngles, WeaponSway::Deviation* pRecoil)
{
	WeaponFiring* pFiring = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pPrimaryFiring;
	if (MmIsAddressValidPtr(pFiring) && MmIsAddressValidPtr(pRecoil))
	{
		if (custom_isnan(asin(pRecoil->m_Yaw)) || custom_isnan(asin(pRecoil->m_Pitch)))
			return;

		pAngles->x += asin(pRecoil->m_Yaw);
		pAngles->y += asin(pRecoil->m_Pitch);
	}
}

void CorrectSpread(Vector2* pAngles, WeaponSway::Deviation* pSpread)
{
	WeaponFiring* pFiring = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pPrimaryFiring;
	if (MmIsAddressValidPtr(pFiring) && MmIsAddressValidPtr(pSpread))
	{
		if (custom_isnan(asin(pSpread->m_Yaw)) || custom_isnan(asin(pSpread->m_Pitch)))
			return;

		pAngles->x += pSpread->m_Yaw;
		pAngles->y += pSpread->m_Pitch;
	}
}

float VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

void AimCorrection(Vector3 * inVec, Vector3 enemyVelo, Vector3 myVelo, float Distance, float BulletSpeed, float Gravity)
{
	if (!IsLocalClientAlive())
		return;

	ClientSoldierWeaponsComponent *pWeapComp = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent;
	if (pWeapComp == 0)
		return;

	WeaponFiringData *pFireData = pWeapComp->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData;
	if (pFireData == 0)
		return;

	BulletEntityData *pProjData = pFireData->m_pFiringFunctionData->m_pBulletEntityData;
	if (pProjData == 0)
		return;

	inVec->y -= atan2(pFireData->m_pFiringFunctionData->m_initialSpeed.y, pFireData->m_pFiringFunctionData->m_initialSpeed.z);

	float m_time = Distance / fabsf(BulletSpeed);
	float m_grav = fabsf(Gravity);
	*inVec = *inVec + (enemyVelo * m_time);
	inVec->y += 0.2f * m_grav * m_time * m_time;

	float holdover = solveQuadratic(Gravity / (2 * (BulletSpeed*BulletSpeed)), 1 + (Gravity*inVec->y) / (BulletSpeed*BulletSpeed), (Distance)*Gravity / (2 * (BulletSpeed*BulletSpeed)));
	inVec->y += holdover;
}

void DoAimCorrection(ClientSoldierEntity * mySoldier, ClientSoldierEntity * enemySoldier, Vector3 & enemyVec)
{
	if (!IsLocalClientAlive())
		return;

	ClientSoldierWeaponsComponent *pWeapComp = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierWeaponsComponent;
	if (pWeapComp == 0)
		return;

	WeaponFiringData *pFireData = pWeapComp->GetActiveSoldierWeapon()->m_pWeapon->m_pWeaponFiringData;
	if (pFireData == 0)
		return;

	BulletEntityData *pProjData = pFireData->m_pFiringFunctionData->m_pBulletEntityData;
	if (pProjData == 0)
		return;

	float Gravity = pProjData->m_gravity;
	float Bulletspeed = pFireData->m_pFiringFunctionData->m_initialSpeed.z;

	AimCorrection(&enemyVec, enemySoldier->m_pClientSoldierPrediction->m_Velocity, mySoldier->m_pClientSoldierPrediction->m_Velocity, mySoldier->m_pClientSoldierPrediction->m_Position.Distance(enemySoldier->m_pClientSoldierPrediction->m_Position), Bulletspeed, Gravity);
}

bool GetAimPos(ClientPlayer* _EnemyPlayer, Vector2* Angles, Vector3* LocalOrigin, Vector3* Origin)
{
	Vector3 Space;

	if (_EnemyPlayer->m_pControlledControllable != 0)
	{

		if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::Neck) || !GetBone(GetLocalPlayer()->m_pControlledControllable, LocalOrigin, UpdatePoseResultData::Head)) {
			*LocalOrigin = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;

			*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
		}

		DoAimCorrection(GetLocalPlayer()->m_pControlledControllable, _EnemyPlayer->m_pControlledControllable, *Origin);

		Space.x = Origin->x - LocalOrigin->x;
		Space.y = Origin->y - LocalOrigin->y;
		Space.z = Origin->z - LocalOrigin->z;

		Angles->x = -atan2(Space.x, Space.z);
		Angles->y = atan2(Space.y, VectorLength2D(&Space));

		return true;
	}
	return false;
}

enum RayCastFlags
{
	CheckDetailMesh = 0x1,
	IsAsyncRaycast = 0x2,
	DontCheckWater = 0x4,
	DontCheckTerrain = 0x8,
	DontCheckRagdoll = 0x10,
	DontCheckCharacter = 0x20,
	DontCheckGroup = 0x40,
	DontCheckPhantoms = 0x80,
};

bool IsVisible(Vector4* vFrom, Vector4* vTo)
{
	ClientGameContext* g_pGameContext = ClientGameContext::GetInstance();


	if (!MmIsAddressValidPtr(g_pGameContext))
		return false;

	Level* Level = g_pGameContext->m_pLevel;

	if (!MmIsAddressValidPtr(Level))
		return false;


	HavokPhysicsManager* pPhysicsManager = Level->m_pHavokPhysicsManager;

	if (!MmIsAddressValidPtr(pPhysicsManager))
		return false;
	IPhysicsRayCaster* rayCaster = pPhysicsManager->m_pRayCaster;

	if (!MmIsAddressValidPtr(rayCaster))
		return false;


	RayCastHit ray;

	bool visible = !rayCaster->physicsRayQuery("OnGroundState::update", vFrom, vTo, &ray, 0x4 | 0x10 | 0x20 | 0x80, NULL);

	return visible;
}
//ClientPlayer* 

int ClosestClient(ClientPlayer* LocalPlayer)
{

	int Nearest = -1;

	float nearestDistance = 99999;

	for (int i = 0; i < 24; i++)
	{
		ClientPlayer* Target = GetPlayerById(i);

		if (!MmIsAddressValidPtr(Target))
			continue;

		if (!IsClientAlive(Target))
			continue;

		if (LocalPlayer == Target)
			continue;

		if (!MmIsAddressValidPtr(Target->m_pControlledControllable))
			continue;

		if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_pClientSoldierPrediction))
			continue;

		Vector3 Position, PositionL;

		if (!GetBone(Target->m_pControlledControllable, &Position, UpdatePoseResultData::Neck) || !GetBone(LocalPlayer->m_pControlledControllable, &PositionL, UpdatePoseResultData::Head)) {
			PositionL = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;

			PositionL.y += 1.8f;

			Position = Target->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;

			Position.y += 1.8f;
		}

		float distance = Position.Distance(PositionL);

		Vector4 Mine = Vector4(PositionL.x, PositionL.y, PositionL.z, 0), Theires = Vector4(Position.x, Position.y, Position.z, 0);


		isClientWallable[i] = IsVisible(&Mine, &Theires);


		if (Target->m_teamId != LocalPlayer->m_teamId)
		{
			if ((isClientWallable[i] && bVisibility) || !bVisibility)
			{
				if ((distance < nearestDistance))
				{
					nearestDistance = distance;
					Nearest = i;
				}
			}
		}
	}
	return Nearest;
}

void DamagePlayer(ClientPlayer* Target, ClientPlayer* LocalPlayer, float damage, UnlockAssetBase* Weapon, HitReactionType HitType)
{

	if (!MmIsAddressValidPtr(Target) || (!MmIsAddressValidPtr(LocalPlayer)))
		return;
	ClientGameContext* pGC = ClientGameContext::GetInstance();
	if (!MmIsAddressValidPtr(pGC))
		return;
	OnlineManager* pOM = pGC->m_pOnlineManager;
	if (!MmIsAddressValidPtr(pOM))
		return;
	ClientConnection* pCCC = pOM->m_pClientConnection;
	if (!MmIsAddressValidPtr(pCCC))
		return;
	ClientDamageStream* pDamageStream = pCCC->m_pDamageStream;
	if (!MmIsAddressValidPtr(pDamageStream))
		return;
	ClientDamageStream::DamageData* pDMG = pDamageStream->m_pDamageData;
	if (!MmIsAddressValidPtr(pDMG))
		return;

	pDMG->victimPlayerId = Target->getId();
	pDMG->victimInstanceId = 0;
	pDMG->inflictorPlayerId = LocalPlayer->getId();
	pDMG->hitType = HitType;
	pDMG->weaponUnlockAsset = Weapon;
	pDMG->damage = damage;
	pDMG->clientAiKilled = 0;

	AddDamageData(pCCC, pDMG);
}

void HealSelf(ClientPlayer* LocalPlayer)
{
	DamagePlayer(LocalPlayer, LocalPlayer, -200.0f, NULL, HitReactionType::HRT_Body);
}

int getKitID()
{
	ClientPlayer* localP = ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer;
	if (!MmIsAddressValidPtr(localP))
		return 0xFF;

	VeniceSoldierCustomizationAsset* veniceFind = localP->m_pSelectedCustomizationAsset;
	if (!MmIsAddressValidPtr(veniceFind))
		return 0xFF;

	const char* assaultString = "ID_M_ASSAULT";
	const char* EngineerString = "ID_M_ENGINEER";
	const char* SUPPORTString = "ID_M_SUPPORT";
	const char* ReconString = "ID_M_RECON";
	int kitID = 0;

	if (strcmp(assaultString, veniceFind->m_ID_Name) == 0)
		return 0;

	if (strcmp(EngineerString, veniceFind->m_ID_Name) == 0)
		return 1;

	if (strcmp(SUPPORTString, veniceFind->m_ID_Name) == 0)
		return 2;

	if (strcmp(ReconString, veniceFind->m_ID_Name) == 0)
		return 3;

	return 0xFF;
}

UnlockAssetBase* getUA(ClientPlayer* localp)
{
	int(*GetWeaponID)(ClientWeapon*) = (int(*)(ClientWeapon*))0x836F4390;

	if (!GetWeaponID(localp->GetClientSoldier()->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon))
		return NULL;

	return (UnlockAssetBase*)GetWeaponID(localp->GetClientSoldier()->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pWeapon);

	return NULL;
}

ClientPlayerScore* GetScorePTR()
{
	ClientPlayerScoreManager* pscore = ClientGameContext::GetInstance()->m_pClientScoreManager;
	if (!MmIsAddressValidPtr(pscore))
		return NULL;

	ClientPlayer* localp = GetLocalPlayer();
	if (!MmIsAddressValidPtr(localp))
		return NULL;

	int pScore = GetPlayerScore(pscore, localp);

	ClientPlayerScore* pscoreReal = (ClientPlayerScore*)pScore;
	if (!MmIsAddressValidPtr(pscoreReal))
		return NULL;
	return pscoreReal;
}

void DoAmmo()
{
	if (IsLocalClientAlive())
	{
		ClientPlayer* localP = ClientGameContext::GetInstance()->m_pClientPlayerManager->m_pLocalPlayer;
		if (!MmIsAddressValidPtr(localP))
			return;

		ClientSoldierEntity* cse = localP->m_pControlledControllable;
		if (!MmIsAddressValidPtr(cse))
			return;

		ClientSoldierWeaponsComponent* cwc = cse->m_pClientSoldierWeaponsComponent;
		if (!MmIsAddressValidPtr(cwc))
			return;

		ClientSoldierWeaponsComponent::ClientActiveWeaponHandler* act12 = cwc->m_pActiveHandler;
		if (!MmIsAddressValidPtr(act12))
			return;

		ClientSoldierWeapon* act1 = act12->m_pActiveWeapon;
		if (!MmIsAddressValidPtr(act1))
			return;

		WeaponFiring* wepfPrimary = act1->m_pPrimaryFiring;
		if (!MmIsAddressValidPtr(wepfPrimary))
			return;

		WeaponFiring* wepfCorrected = act1->m_pCorrectedFiring;
		if (!MmIsAddressValidPtr(wepfCorrected))
			return;

		VeniceSoldierCustomizationAsset* veniceFind = localP->m_pSelectedCustomizationAsset;
		if (!MmIsAddressValidPtr(veniceFind))
			return;

		if (wepfPrimary->m_Ammo != 0x0 && UACounterInt != 0x0 && GetAsyncKeyState(XINPUT_GAMEPAD_X) != true)
		{
			UACounterInt = 0;
			return;
		}

		if (GetAsyncKeyState(XINPUT_GAMEPAD_X) && UACounterInt == 0x0 && MmIsAddressValidPtr(act1) || (wepfPrimary->m_Ammo == 0 && UACounterInt == 0x0 && MmIsAddressValidPtr(act1)))
		{
			UACounterInt = 1;

			int kitID = getKitID();
			if (kitID == 0xFF)
				return;

			int r3 = *(int*)(0x841289FC);
			int r4 = (int)(0x8420E38C);
			int checkPtr = GetAmmoPtr(r3, r4, 0x1);
			ReloadMessageFunction(checkPtr, kitID, 0x1);
		}
	}
}

void HealTeam(ClientPlayer* LocalPlayer)
{
	for (int i = 0; i < 24; i++)
	{
		ClientPlayer* pTarget = GetPlayerById(i);
		if (!MmIsAddressValidPtr(pTarget))
			continue;

		if (pTarget->m_teamId != LocalPlayer->m_teamId)
			continue;

		if (!IsClientAlive(pTarget))
			continue;

		if (GetAsyncKeyState(KEY_RT))
			DamagePlayer(pTarget, LocalPlayer, -200.0f, NULL, HitReactionType::HRT_Head);
	}
}

void Aimbot(ClientPlayer* LocalEntity)
{
	Vector2 Angles = Vector2(0, 0);
	Vector2 TempAng = Vector2(0, 0);

	NearestPlayer = ClosestClient(LocalEntity);

	if (NearestPlayer == -1)
	{
		bTriggerBot = false;
		return;
	}

	ClientPlayer* AimTarget = GetPlayerById(NearestPlayer);
	int ClientCount = NearestPlayer;

	Vector3 LocalOrigin, Origin;

	if (!GetAimPos(AimTarget, &Angles, &LocalOrigin, &Origin))
		return;

	ClientSoldierWeaponsComponent* pCSWC = LocalEntity->m_pControlledControllable->m_pClientSoldierWeaponsComponent;

	if (!MmIsAddressValidPtr(pCSWC))
		return;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();

	if (!MmIsAddressValidPtr(pCSW))
		return;

	if (pCSW->m_pCorrectedFiring->m_weaponState == 11)
		return;

	if (pCSW->m_pSoldierWeaponData->isRocket())
		return;

	Angles.x -= pCSW->m_pClientSoldierAimingSimulation->m_sway.x;
	Angles.y -= pCSW->m_pClientSoldierAimingSimulation->m_sway.y;

	TempAng = Angles;

	if (custom_isnan(Angles.x) || custom_isnan(Angles.y))
		return;

	pSilent.x = Angles.x;
	pSilent.y = Angles.y;

	if (bAimingRequired)
	{
		if (GetAsyncKeyState(0x5555))
		{
			bTriggerBot = true;

			if (GetAsyncKeyState(KEY_RT) || GetLocalPlayer()->GetClientSoldier()->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pPrimaryFiring->m_weaponState == 9 && bUnfairAimbot)
				DamagePlayer(AimTarget, GetLocalPlayer(), 100.0f, bSpoofTarget ? getUA(AimTarget) : getUA(GetLocalPlayer()), bHeadshots ? HitReactionType::HRT_Head : (HitReactionType)0);

			Matrix* m = new Matrix;
			bool l = false;

			GetLocalPlayer()->GetClientSoldier()->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pPrimaryFiring->m_pSway->getDispersion(*m, true);

			delete m;

			if (!bSilentAimbot)
			{
				pCSW->m_pClientSoldierAimingSimulation->m_fpsAimer->m_pitch = Angles.y;
				pCSW->m_pClientSoldierAimingSimulation->m_fpsAimer->m_yaw = Angles.x;
			}
		}
		else
			bTriggerBot = false;
	}
	else
	{
		bTriggerBot = true;

		if (GetAsyncKeyState(KEY_RT) || GetLocalPlayer()->GetClientSoldier()->m_pClientSoldierWeaponsComponent->GetActiveSoldierWeapon()->m_pPrimaryFiring->m_weaponState == 9 && bUnfairAimbot)
			DamagePlayer(AimTarget, GetLocalPlayer(), 100.0f, bSpoofTarget ? getUA(AimTarget) : getUA(GetLocalPlayer()), bHeadshots ? HitReactionType::HRT_Head : (HitReactionType)0);

		if (!bSilentAimbot)
		{
			pCSW->m_pClientSoldierAimingSimulation->m_fpsAimer->m_pitch = Angles.y;
			pCSW->m_pClientSoldierAimingSimulation->m_fpsAimer->m_yaw = Angles.x;
		}
	}
}

unsigned long long GetXuid(char* Name)
{
	int(*GetXUID)(unsigned long long xuid, unsigned long long r4, char* gt, int size, unsigned long long* xuidout, int unk) =
		(int(*)(unsigned long long xuid, unsigned long long r4, char* gt, int size, unsigned long long* xuidout, int unk))0x819D09D0;

	strcpy((char*)0x81E70220, Name);

	GetXUID(0x9000006f93463, 0, Name, 0x18, (unsigned long long*)0x81E70200, 0);

	return *(unsigned long long*)(0x81E70200);
}
