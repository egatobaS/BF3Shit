#include "main.h"

int(*GetAmmoPtr)(int x, int y, int z) = (int(*)(int x, int y, int z))0x83266AC0;
int(*CCMessage)(ClientConnection*, Message*) = (int(*)(ClientConnection*, Message*))0x831FAD00;
int(*ReloadMessageFunction)(int r3, int r4, int r5) = (int(*)(int r3, int r4, int r5))0x834CC888;
int(*AddDamageData)(ClientConnection*, ClientDamageStream*) = (int(*)(ClientConnection*, ClientDamageStream*))0x831FB1D8;
int(*GetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer*) = (int(*)(ClientPlayerScoreManager*, ClientPlayer*))0x83212338;

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

	BFClientSoldierHealthComponent* pBFCSHC = pCSE->m_healthModule;
	if (!MmIsAddressValidPtr(pBFCSHC))
		return false;

	if (pBFCSHC->m_Health < 0.1f)
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

	ClientSoldierReplication* pCSR = pCSE->m_pClientSoldierReplication;
	if (!MmIsAddressValidPtr(pCSR))
		return false;

	BFClientSoldierHealthComponent* pBFCSHC = pCSE->m_healthModule;
	if (!MmIsAddressValidPtr(pBFCSHC))
		return false;

	if (pBFCSHC->m_Health < 0.1f)
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

	return true;
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

bool DrawESP() //TODO: BoneESP and a Visibility Check
{
	for (int i = 0; i < 24; i++)
	{
		if (!IsClientAlive(GetPlayerById(i)))
			continue;

		Vector3 ClientPosition = GetPlayerById(i)->GetClientSoldier()->m_pClientSoldierPrediction->m_Position;

		if (GetPlayerById(i)->m_teamId == GetLocalPlayer()->m_teamId)
		{
			if (bDrawSnapLinesF)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
					DrawLine(1280 / 2, 720 / 2, ClientPosition.x, ClientPosition.y, 1, D3DCOLOR_RGBA(0, 255, 0, 255));
			}

			if (bFCompass)
				DrawCompass(ClientPosition, D3DCOLOR_RGBA(0, 255, 0, 255), 120.0f);

			if (bESPFriendly)
			{
				switch (ESPType)
				{
				case 1:
				{
					Draw2DBox((ClientVehicleEntity*)GetPlayerById(i)->GetClientSoldier(), D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				case 0:
				{
					TransformDrawAABB((ClientVehicleEntity*)GetPlayerById(i)->GetClientSoldier(), D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				}
			}
		}
		else
		{
			if (bDrawSnapLinesE)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
					DrawLine(1280 / 2, 720 / 2, ClientPosition.x, ClientPosition.y, 1, D3DCOLOR_RGBA(255, 0, 0, 255));
			}

			if (bECompass)
				DrawCompass(ClientPosition, D3DCOLOR_RGBA(255, 0, 0, 255), 120.0f);

			if (bESPEnemy)
			{
				switch (ESPType)
				{
				case 1:
				{
					Draw2DBox((ClientVehicleEntity*)GetPlayerById(i)->GetClientSoldier(), D3DCOLOR_RGBA(255, 0, 0, 255), 0.8);
					break;
				}
				case 0:
				{
					TransformDrawAABB((ClientVehicleEntity*)GetPlayerById(i)->GetClientSoldier(), D3DCOLOR_RGBA(255, 0, 0, 255), 0.8);
					break;
				}
				}
			}
		}
	}

	return 0;
}