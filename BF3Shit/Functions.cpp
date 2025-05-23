#include "main.h"

Vector3 pSilent;

unsigned int WaitTimSendSpot = 0;
unsigned int TimeCountSendSpot = 0;
int isClientWallable[24] = { 0 };
bool setBitFlag = false;
bool bShoot = false;
bool bTriggerBot = false;
int ShootCount = 0;

int NearestPlayer = -1;
int UACounterInt = 0;

WeaponSway::Deviation* pRecoil = 0;
WeaponSway::Deviation *pSpread = 0;

DWORD playerWeakPtrs[24];
eastl::fixed_vector<DWORD *, 8, 0> controllablesToSpot;
ClientPlayer* pTarget = NULL;

UnlockAssetBase(*GetWeaponID)(ClientWeapon*) = (UnlockAssetBase(*)(ClientWeapon*))0x836F4390;


void SendSpotWait(int time)
{
	TimeCountSendSpot = GetTickCount();
	WaitTimSendSpot = time;
}

Vector3 GetLocalViewOrigin()
{
	Vector3 vOrigin;

	GameRenderer* renderer = GameRenderer::Singleton();


	if (renderer == NULL)
		return vOrigin;

	if (renderer->m_viewParams.view.Update() == false)
		return vOrigin;

	return  Vector3(renderer->m_viewParams.firstPersonTransform.data[3][0], renderer->m_viewParams.firstPersonTransform.data[3][1], renderer->m_viewParams.firstPersonTransform.data[3][2]);
}

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

	if (!MmIsAddressValidPtr(pLocal))
		return false;

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

	WeaponFiringData *pFireData = pCW->m_pWeaponFiringData;
	if (!MmIsAddressValidPtr(pFireData))
		return false;


	BulletEntityData *pProjData = pFireData->m_pFiringFunctionData->m_pBulletEntityData;
	if (!MmIsAddressValidPtr(pProjData))
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

void setIsAuthoritativeMovementActive(EntryInputState *pEIS, BOOL active)
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

	MatrixD* Mat = (MatrixD*)(((int)renderer) + Addresses->_0xDB0);

	Vector3 vOrigin = GetLocalViewOrigin();//renderer->m_viewParams.firstPersonTransform.trans;
	Vector3 vForward = Mat->Forward();
	vForward.Normalize();
	Vector3 vRayEnd = vOrigin + (vForward * FlySpeed);
	Vector3 vDiff = vRayEnd - vOrigin;
	vDiff.Normalize();
	float factor = 50.0f / sqrt(vDiff.x*vDiff.x + vDiff.y * vDiff.y + vDiff.z * vDiff.z);


	if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN))
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


#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))

void HealthBarColour(float Health, float MaxHealth, LPDWORD Color) {
	BYTE NewColour[4] = { 0 };
	Health = max(0, min(Health, MaxHealth));
	Color[0] = (byte)min((510.f * (MaxHealth - Health)) / 100, 255);
	Color[1] = (byte)min((510.f * Health) / 100, 255);
	Color[2] = 0;
	Color[3] = 60;
	*Color = D3DCOLOR_RGBA(Color[0], Color[1], Color[2], Color[3]);
}

void DrawClientOnWorldHealthBar(float x, float y, float w, float health, float max)
{

	//D3DCOLOR col = (health >= (max / 2) ? D3DCOLOR_RGBA(0, 255, 0, 60) : D3DCOLOR_RGBA(255, 0, 0, 60));

	D3DCOLOR col = 0;
	HealthBarColour(health, max, &col);

	float step = (w / max);
	float draw = (step * health);

	//DrawBox(x, y, w, 4, D3DCOLOR_RGBA(0, 0, 0, 255));
	DrawBox(x, y, w, 4, D3DCOLOR_RGBA(0, 0, 0, 100));
	DrawBox(x, y, draw, 4, col);

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


bool DrawPlayerHealthBar(ClientVehicleEntity* pEnt, float size)
{
	Matrix* trans = new Matrix;
	Vector3 Pos;

	AxisAlignedBox* TransAABB = new AxisAlignedBox;

	if (!MmIsAddressValidPtr(pEnt))
		return false;

	pEnt->computeBoundingBox(TransAABB);

	pEnt->getTransform(trans);
	Pos = Vector3(trans->operator()(3, 0), trans->operator()(3, 1), trans->operator()(3, 2));

	Pos.y -= 0.1;

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

		Vector3 vPos;

		if (GetBone((ClientSoldierEntity*)pEnt, &vPos, UpdatePoseResultData::Head))
		{
			float w = abs(r - l);
			DrawClientOnWorldHealthBar(l, t, w, ((ClientSoldierEntity*)pEnt)->m_Health, ((ClientSoldierEntity*)pEnt)->m_MaxHealth);

		}
	}
	delete trans;
	delete TransAABB;

	return true;
}

bool DrawNameESP(ClientPlayer* Enemy, float fFontSize, ClientVehicleEntity* pEnt, float size)
{
	Matrix* trans = new Matrix;
	Vector3 Pos;

	AxisAlignedBox* TransAABB = new AxisAlignedBox;

	if (!MmIsAddressValidPtr(pEnt))
		return false;

	pEnt->computeBoundingBox(TransAABB);

	pEnt->getTransform(trans);
	Pos = Vector3(trans->operator()(3, 0), trans->operator()(3, 1), trans->operator()(3, 2));

	Pos.y += 0.5f * size;

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

		float w = abs(r - l);

		DrawText(Enemy->m_Name, l + (w / 2), b, fFontSize, D3DCOLOR_RGBA(255, 255, 255, 255), ATGFONT_CENTER_X | ATGFONT_CENTER_Y);
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
	DrawBoneLine(Client, UpdatePoseResultData::LeftElbowRoll, UpdatePoseResultData::LeftHand, boneESPCol);

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

Vector3 OverAllScreenCoords;


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

		ClientSoldierEntity* TargetClientSoldierEntity = Target->GetClientSoldier();

		if (!MmIsAddressValidPtr(TargetClientSoldierEntity))
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
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						Draw2DBox(Target->GetClientVehicleEntity(), D3DCOLOR_RGBA(231, 0, 245, 255), 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						TransformDrawAABB(Target->GetClientVehicleEntity(), D3DCOLOR_RGBA(231, 0, 245, 255), 0.8);
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


		if ((bClientHealthBarE && Target->m_teamId != GetLocalPlayer()->m_teamId) || (bClientHealthBarF && Target->m_teamId == GetLocalPlayer()->m_teamId))
		{
			DrawPlayerHealthBar((ClientVehicleEntity*)pCSE, 0.8);
		}

		if ((bEnemyName && Target->m_teamId != GetLocalPlayer()->m_teamId) || (bFriendName && Target->m_teamId == GetLocalPlayer()->m_teamId))
		{
			float fFontSize = (0.70f - (GetDistance(LocalPosition, ClientPosition) / 10.f));

			if (fFontSize < 0.f)
				fFontSize = 0.1f;

			DrawNameESP(Target, fFontSize, (ClientVehicleEntity*)TargetClientSoldierEntity, 0.8f);
		}

		if (Target->m_teamId == GetLocalPlayer()->m_teamId)
		{
			if (bDrawSnapLinesF)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
				{
					switch (SnapArrayEnumaratorF)
					{
					case 0:
						DrawLine(1280.f / 2.f, 0.f, ClientPosition.x, (ClientPosition.y), 1, D3DCOLOR_RGBA(0, 255, 0, 255));
						break;

					case 1:
						DrawLine(1280 / 2.f, 720.f / 2.f, ClientPosition.x, (ClientPosition.y), 1, D3DCOLOR_RGBA(0, 255, 0, 255));
						break;

					case 2:
						DrawLine(1280.f / 2.f, 720.f, ClientPosition.x, (ClientPosition.y), 1, D3DCOLOR_RGBA(0, 255, 0, 255));
						break;
					}
				}
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
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						Draw2DBox((ClientVehicleEntity*)TargetClientSoldierEntity, D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						TransformDrawAABB((ClientVehicleEntity*)TargetClientSoldierEntity, D3DCOLOR_RGBA(0, 255, 0, 255), 0.8);
					break;
				}
				}
			}
		}
		else
		{
			D3DCOLOR ESPColor = isClientWallable[i] == 0 ? D3DCOLOR_RGBA(255, 0, 0, 255) : D3DCOLOR_RGBA(255, 255, 0, 255);

			ESPColor = (isClientWallable[i] == AutoWall) ? D3DCOLOR_RGBA(255, 69, 0, 255) : ESPColor;

			if (bDrawSnapLinesE)
			{
				if (WorldToScreen(ClientPosition, &ClientPosition))
				{
					switch (SnapArrayEnumaratorE)
					{
					case 0:
						DrawLine(1280 / 2, 0, ClientPosition.x, (ClientPosition.y), 1, ESPColor);
						break;

					case 1:
						DrawLine(1280 / 2, 720 / 2, ClientPosition.x, (ClientPosition.y), 1, ESPColor);
						break;

					case 2:
						DrawLine(1280 / 2, 720, ClientPosition.x, (ClientPosition.y), 1, ESPColor);
						break;
					}
				}
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
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						Draw2DBox((ClientVehicleEntity*)TargetClientSoldierEntity, ESPColor, 0.8);
					break;
				}
				case 0:
				{
					if (MmIsAddressValidPtr(TargetClientSoldierEntity))
						TransformDrawAABB((ClientVehicleEntity*)TargetClientSoldierEntity, ESPColor, 0.8);
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

void AimCorrection(Vector3 * inVec, Vector3 enemyVelo, Vector3 myVelo, float Distance, float BulletSpeed, float Gravity)
{
	if (!IsLocalClientAlive())
		return;

	ClientSoldierEntity* pCSE = GetLocalPlayer()->GetClientSoldier();
	if (!MmIsAddressValidPtr(pCSE))
		return;

	ClientSoldierPrediction* pCSP = pCSE->m_pClientSoldierPrediction;
	if (!MmIsAddressValidPtr(pCSP))
		return;

	ClientBoneCollisionComponent* pCBCC = pCSE->m_pClientBoneCollisionComponent;
	if (!MmIsAddressValidPtr(pCBCC))
		return;

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValidPtr(pCSWC))
		return;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValidPtr(pCSW))
		return;

	ClientWeapon* pWeapon = pCSW->m_pWeapon;
	if (!MmIsAddressValidPtr(pWeapon))
		return;

	WeaponFiringData *pFireData = pWeapon->m_pWeaponFiringData;
	if (!MmIsAddressValidPtr(pFireData))
		return;

	BulletEntityData *pProjData = pFireData->m_pFiringFunctionData->m_pBulletEntityData;
	if (!MmIsAddressValidPtr(pProjData))
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

	ClientPlayer*  LocalClientPlayer = GetLocalPlayer();

	if (!MmIsAddressValidPtr(LocalClientPlayer))
		return;

	ClientSoldierEntity* LocalClientSoldierEntity = LocalClientPlayer->m_pControlledControllable;

	if (!MmIsAddressValidPtr(LocalClientSoldierEntity))
		return;

	ClientSoldierWeaponsComponent* pWeapComp = LocalClientSoldierEntity->m_pClientSoldierWeaponsComponent;

	if (!MmIsAddressValidPtr(pWeapComp))
		return;

	ClientSoldierWeapon* ActiveWeapon = pWeapComp->GetActiveSoldierWeapon();

	if (!MmIsAddressValidPtr(ActiveWeapon))
		return;

	ClientWeapon* ClientWeapon = ActiveWeapon->m_pWeapon;

	if (!MmIsAddressValidPtr(ClientWeapon))
		return;

	WeaponFiringData *pFireData = ClientWeapon->m_pWeaponFiringData;

	if (!MmIsAddressValidPtr(pFireData))
		return;

	FiringFunctionData* FiringData = pFireData->m_pFiringFunctionData;

	if (!MmIsAddressValidPtr(FiringData))
		return;

	BulletEntityData *pProjData = FiringData->m_pBulletEntityData;

	if (!MmIsAddressValidPtr(pProjData))
		return;

	float Gravity = pProjData->m_gravity;

	float Bulletspeed = FiringData->m_initialSpeed.z;

	AimCorrection(&enemyVec, enemySoldier->m_pClientSoldierPrediction->m_Velocity, mySoldier->m_pClientSoldierPrediction->m_Velocity, mySoldier->m_pClientSoldierPrediction->m_Position.Distance(enemySoldier->m_pClientSoldierPrediction->m_Position), Bulletspeed, Gravity);
}

bool GetAimPos(int ClientNumber, ClientPlayer* _EnemyPlayer, Vector2* Angles, Vector3* LocalOrigin, Vector3* Origin)
{
	Vector3 Space;

	if (_EnemyPlayer->m_pControlledControllable != 0)
	{
		*LocalOrigin = GetLocalViewOrigin();

		if (isClientWallable[ClientNumber] == Bone_Head)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::Head)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == Bone_Hips)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::Hips)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == Left_Knee)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::LeftKneeRoll)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == Right_Knee)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::RightKneeRoll)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == Right_Foot)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::RightFoot)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else  if (isClientWallable[ClientNumber] == Left_Foot)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::LeftFoot)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == Bone_Origin)
		{
			*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
		}
		else if (isClientWallable[ClientNumber] == Bone_None || !bVisibility)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::Neck)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
		}
		else if (isClientWallable[ClientNumber] == AutoWall && bUnfairAimbot)
		{
			if (!GetBone(_EnemyPlayer->m_pControlledControllable, Origin, UpdatePoseResultData::Neck)) {

				*Origin = _EnemyPlayer->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
				Origin->y += 1.8f;
			}
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


bool IsVisible(Vector3* vFrom, Vector3* vTo, Vector3* PositionHit)
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

	Vector4 Mine = Vector4(vFrom->x, vFrom->y, vFrom->z, 0), Theires = Vector4(vTo->x, vTo->y, vTo->z, 0);

	bool visible = !rayCaster->physicsRayQuery("OnGroundState::update", &Mine, &Theires, &ray, IPhysicsRayCaster::AimbotFlags, NULL);

	Vector3 WorldCoords = Vector3(ray.m_position.x, ray.m_position.y, ray.m_position.z);

	if (PositionHit)
		*PositionHit = WorldCoords;

	return visible;
}



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

		if (Target->m_teamId == LocalPlayer->m_teamId)
			continue;

		Vector3 Position, PositionL;

		if (!GetBone(LocalPlayer->m_pControlledControllable, &PositionL, UpdatePoseResultData::Head))
		{
			PositionL = GetLocalPlayer()->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;

			PositionL.y += 1.8f;
		}

		ClientBones BonesStatus;


		BonesStatus.Origin = Target->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
		BonesStatus.GotOrigin = true;

		BonesStatus.GotHead = GetBone(Target->m_pControlledControllable, &BonesStatus.Head, UpdatePoseResultData::Head);
		if (!BonesStatus.GotHead) {
			BonesStatus.Head = Target->m_pControlledControllable->m_pClientSoldierPrediction->m_Position;
			BonesStatus.Head.y += 1.8f;
			BonesStatus.GotHead = true;
		}
		BonesStatus.GotHips = GetBone(Target->m_pControlledControllable, &BonesStatus.Hips, UpdatePoseResultData::Hips);
		BonesStatus.GotLeftFoot = GetBone(Target->m_pControlledControllable, &BonesStatus.LeftFoot, UpdatePoseResultData::LeftFoot);
		BonesStatus.GotRightFoot = GetBone(Target->m_pControlledControllable, &BonesStatus.RightFoot, UpdatePoseResultData::RightFoot);
		BonesStatus.GotLeftKnee = GetBone(Target->m_pControlledControllable, &BonesStatus.LeftKnee, UpdatePoseResultData::LeftKneeRoll);
		BonesStatus.GotRightKnee = GetBone(Target->m_pControlledControllable, &BonesStatus.RightKnee, UpdatePoseResultData::RightKneeRoll);

		Vector3 ImpactSystem;

		if (bAutoBone)
		{
			if (BonesStatus.GotHead && IsVisible(&PositionL, &BonesStatus.Head, &ImpactSystem))
				isClientWallable[i] = Bone_Head;
			else if (BonesStatus.GotHips && IsVisible(&PositionL, &BonesStatus.Hips, &ImpactSystem))
				isClientWallable[i] = Bone_Hips;
			else if (BonesStatus.GotLeftKnee && IsVisible(&PositionL, &BonesStatus.LeftKnee, &ImpactSystem))
				isClientWallable[i] = Left_Knee;
			else if (BonesStatus.GotRightKnee && IsVisible(&PositionL, &BonesStatus.RightKnee, &ImpactSystem))
				isClientWallable[i] = Right_Knee;
			else if (BonesStatus.GotRightFoot && IsVisible(&PositionL, &BonesStatus.RightFoot, &ImpactSystem))
				isClientWallable[i] = Right_Foot;
			else if (BonesStatus.GotLeftFoot && IsVisible(&PositionL, &BonesStatus.LeftFoot, &ImpactSystem))
				isClientWallable[i] = Left_Foot;
			else if (BonesStatus.GotOrigin && IsVisible(&PositionL, &BonesStatus.Origin, &ImpactSystem))
				isClientWallable[i] = Bone_Origin;
			else isClientWallable[i] = Bone_None;
		}
		else
		{
			if (BonesStatus.GotHead && IsVisible(&PositionL, &BonesStatus.Head, &ImpactSystem))
				isClientWallable[i] = Bone_Head;
			else if (BonesStatus.GotOrigin && IsVisible(&PositionL, &BonesStatus.Origin, &ImpactSystem))
				isClientWallable[i] = Bone_Origin;
			else isClientWallable[i] = Bone_None;
		}

		if (isClientWallable[i] == Bone_None && bUnfairAimbot) {

			if (ImpactSystem.Distance(BonesStatus.Origin) <= 11.0f)
				isClientWallable[i] = AutoWall;
		}

		Position = BonesStatus.Head;

		float distance = Position.Distance(PositionL);

		if (isClientWallable[i] == Bone_None && bVisibility)
			continue;

		if ((distance < nearestDistance))
		{
			nearestDistance = distance;
			Nearest = i;
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
	DamagePlayer(LocalPlayer, LocalPlayer, -200.0f, NULL, HRT_Body);
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
	int(*GetWeaponID)(ClientWeapon*) = (int(*)(ClientWeapon*))Addresses->_0x836F4390;

	ClientSoldierEntity* ClientSoldier = localp->GetClientSoldier();

	if (!MmIsAddressValidPtr(ClientSoldier))
		return NULL;

	if (!MmIsAddressValidPtr(ClientSoldier->m_pClientSoldierWeaponsComponent))
		return NULL;

	ClientSoldierWeaponsComponent* ClientSoldierWeaponsComponent = ClientSoldier->m_pClientSoldierWeaponsComponent;

	if (!MmIsAddressValidPtr(ClientSoldierWeaponsComponent))
		return NULL;

	ClientSoldierWeapon* ActiveSoldier = ClientSoldierWeaponsComponent->GetActiveSoldierWeapon();

	if (!MmIsAddressValidPtr(ActiveSoldier))
		return NULL;

	ClientWeapon* pWeapon = ActiveSoldier->m_pWeapon;

	if (!MmIsAddressValidPtr(pWeapon))
		return NULL;

	if (!GetWeaponID(pWeapon))
		return NULL;

	return (UnlockAssetBase*)GetWeaponID(pWeapon);

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

		if (wepfPrimary->m_Ammo != 0x0 && UACounterInt != 0x0 && GetAsyncKeyState(XINPUT_GAMEPAD_X) != 1)
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

			int r3 = *(int*)(Addresses->_0x841289FC);
			int r4 = (int)(Addresses->_0x8420E38C);
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
			DamagePlayer(pTarget, LocalPlayer, -200.0f, NULL, HRT_Head);
	}
}

void DoTheSpreadHack_Silent()
{
	ClientPlayer* pCP = GetLocalPlayer();
	if (!MmIsAddressValid(pCP))
		return;

	ClientSoldierEntity* pCSE = pCP->m_pControlledControllable;
	if (!MmIsAddressValid(pCSE))
		return;

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValid(pCSWC))
		return;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValid(pCSW))
		return;

	ClientSoldierAimingSimulation* pCSAS = pCSW->m_pClientSoldierAimingSimulation;
	if (!MmIsAddressValid(pCSAS))
		return;

	AimAssist* pAA = pCSAS->m_fpsAimer;
	if (!MmIsAddressValid(pAA))
		return;

	WeaponFiring* pWF = pCSW->m_pPrimaryFiring;
	if (!MmIsAddressValid(pWF))
		return;

	WeaponSway* pWS = pWF->m_pSway;
	if (!MmIsAddressValid(pWS))
		return;

	if (!MmIsAddressValid(&pWS->m_currentRecoilDeviation))
		return;

	if (pCSWC->m_activeSlot == ClientSoldierWeaponsComponent::M_GRENADE || pCSWC->m_activeSlot == ClientSoldierWeaponsComponent::M_KNIFE)
		return;

	float flYaw = pSilent.x;
	float flPitch = pSilent.y;

	flYaw -= (-asin(pWS->m_currentRecoilDeviation.m_Yaw));
	flPitch -= (-asin(pWS->m_currentRecoilDeviation.m_Pitch));

	WeaponSway::WeaponFiringUpdateContext* pWFUC = new WeaponSway::WeaponFiringUpdateContext();
	pWFUC->ticks = ClientGameContext::GetInstance()->m_pGameTime->m_ticks;

	pWS->primaryFireShotSpawnedCallback(0.f, true, pWFUC);

	flYaw += pWS->m_currentDispersionDeviation.m_Yaw;
	flPitch += pWS->m_currentDispersionDeviation.m_Pitch;

	pSilent.x = flYaw;
	pSilent.y = flPitch;

	delete pWFUC;
}

void DoTheSpreadHack_Visible()
{
	ClientPlayer* pCP = GetLocalPlayer();
	if (!MmIsAddressValid(pCP))
		return;

	ClientSoldierEntity* pCSE = pCP->m_pControlledControllable;
	if (!MmIsAddressValid(pCSE))
		return;

	ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
	if (!MmIsAddressValid(pCSWC))
		return;

	ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
	if (!MmIsAddressValid(pCSW))
		return;

	ClientSoldierAimingSimulation* pCSAS = pCSW->m_pClientSoldierAimingSimulation;
	if (!MmIsAddressValid(pCSAS))
		return;

	AimAssist* pAA = pCSAS->m_fpsAimer;
	if (!MmIsAddressValid(pAA))
		return;

	WeaponFiring* pWF = pCSW->m_pPrimaryFiring;
	if (!MmIsAddressValid(pWF))
		return;

	WeaponSway* pWS = pWF->m_pSway;
	if (!MmIsAddressValid(pWS))
		return;

	if (!MmIsAddressValid(&pWS->m_currentRecoilDeviation))
		return;

	if (pCSWC->m_activeSlot == ClientSoldierWeaponsComponent::M_GRENADE || pCSWC->m_activeSlot == ClientSoldierWeaponsComponent::M_KNIFE)
		return;

	float flYaw = pAA->m_yaw;
	float flPitch = pAA->m_pitch;

	flYaw -= (-asin(pWS->m_currentRecoilDeviation.m_Yaw));
	flPitch -= (-asin(pWS->m_currentRecoilDeviation.m_Pitch));

	WeaponSway::WeaponFiringUpdateContext* pWFUC = new WeaponSway::WeaponFiringUpdateContext();
	pWFUC->ticks = ClientGameContext::GetInstance()->m_pGameTime->m_ticks;

	pWS->primaryFireShotSpawnedCallback(0.f, true, pWFUC);

	flYaw += pWS->m_currentDispersionDeviation.m_Yaw;
	flPitch += pWS->m_currentDispersionDeviation.m_Pitch;

	pAA->m_yaw = flYaw;
	pAA->m_pitch = flPitch;

	delete pWFUC;
}

void Aimbot(ClientPlayer* LocalEntity)
{
	ClientPlayer*  LocalClientPlayer = GetLocalPlayer();

	if (!MmIsAddressValidPtr(LocalClientPlayer))
		return;

	ClientSoldierEntity* LocalClientSoldierEntity = LocalClientPlayer->m_pControlledControllable;

	if (!MmIsAddressValidPtr(LocalClientSoldierEntity))
		return;

	ClientSoldierWeaponsComponent* pWeapComp = LocalClientSoldierEntity->m_pClientSoldierWeaponsComponent;

	if (!MmIsAddressValidPtr(pWeapComp))
		return;

	ClientSoldierWeapon* ActiveWeapon = pWeapComp->GetActiveSoldierWeapon();

	if (!MmIsAddressValidPtr(ActiveWeapon))
		return;

	ClientWeapon* ClientWeapon = ActiveWeapon->m_pWeapon;

	if (!MmIsAddressValidPtr(ClientWeapon))
		return;

	WeaponFiringData *pFireData = ClientWeapon->m_pWeaponFiringData;

	if (!MmIsAddressValidPtr(pFireData))
		return;

	FiringFunctionData* FiringData = pFireData->m_pFiringFunctionData;
	if (!MmIsAddressValidPtr(FiringData))
		return;

	WeaponFiring* WeaponPrimaryFriring = ActiveWeapon->m_pPrimaryFiring;
	if (!MmIsAddressValidPtr(WeaponPrimaryFriring))
		return;

	ClientSoldierAimingSimulation* ClientSoldierAimingSimulation = ActiveWeapon->m_pClientSoldierAimingSimulation;
	if (!MmIsAddressValidPtr(ClientSoldierAimingSimulation))
		return;

	Vector2 Angles = Vector2(0, 0);
	Vector2 TempAng = Vector2(0, 0);

	NearestPlayer = ClosestClient(LocalEntity);

	if (NearestPlayer == -1)
	{
		bTriggerBot = false;
		pTarget = NULL;
		return;
	}

	ClientPlayer* AimTarget = GetPlayerById(NearestPlayer);
	int ClientCount = NearestPlayer;

	Vector3 LocalOrigin, Origin;

	if (!GetAimPos(NearestPlayer, AimTarget, &Angles, &LocalOrigin, &Origin))
		return;

	if (pWeapComp->m_activeSlot == ClientSoldierWeaponsComponent::M_GRENADE || pWeapComp->m_activeSlot == ClientSoldierWeaponsComponent::M_KNIFE)
		return;

	if (ActiveWeapon->m_pCorrectedFiring->m_weaponState == 11)
		return;

	if (ActiveWeapon->m_pSoldierWeaponData->isRocket())
		return;

	Angles.x -= ClientSoldierAimingSimulation->m_sway.x;
	Angles.y -= ClientSoldierAimingSimulation->m_sway.y;

	TempAng = Angles;

	if (custom_isnan(Angles.x) || custom_isnan(Angles.y))
		return;

	pTarget = AimTarget;

	pSilent.x = Angles.x;
	pSilent.y = Angles.y;

	if (bAimingRequired)
	{
		if (GetAsyncKeyState(0x5555))
		{
			bTriggerBot = true;

			if (!bSilentAimbot)
			{
				ClientSoldierAimingSimulation->m_fpsAimer->m_pitch = Angles.y;
				ClientSoldierAimingSimulation->m_fpsAimer->m_yaw = Angles.x;

				if (bNoSpread)
					DoTheSpreadHack_Visible();
			}
		}
		else
			bTriggerBot = false;
	}
	else
	{
		bTriggerBot = true;

		if (!bSilentAimbot)
		{
			ClientSoldierAimingSimulation->m_fpsAimer->m_pitch = Angles.y;
			ClientSoldierAimingSimulation->m_fpsAimer->m_yaw = Angles.x;

			if (bNoSpread)
				DoTheSpreadHack_Visible();
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

void SendSpot(ClientSpottingComponent* Component, ClientPlayer* LocalClientPlayer)
{
	if ((GetTickCount() - TimeCountSendSpot) > WaitTimSendSpot)
	{
		for (int i = 0; i < 24; i++) {

			ClientPlayer* Target = GetPlayerById(i);

			if (!IsLocalClientAlive())
				continue;

			if (!MmIsAddressValidPtr(Target))
				continue;

			if (!IsClientAlive(Target))
				continue;

			if (GetLocalPlayer() == Target)
				continue;

			if (!MmIsAddressValidPtr(Target->m_pControlledControllable))
				continue;

			if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_pClientSoldierPrediction))
				continue;

			if (!MmIsAddressValidPtr(GetLocalPlayer()->m_pControlledControllable))
				continue;

			if (!MmIsAddressValidPtr(Component))
				continue;

			if (!MmIsAddressValidPtr(LocalClientPlayer))
				continue;

			ClientSpottingComponent* LocalClientSpottingComponent = GetLocalPlayer()->m_pControlledControllable->m_pClientSpottingComponent;

			if (!MmIsAddressValidPtr(LocalClientSpottingComponent))
				continue;

			ClientSoldierEntity* controllable = Target->m_pControlledControllable;

			if (Target->m_teamId != GetLocalPlayer()->m_teamId)
			{
				playerWeakPtrs[i] = (DWORD)controllable + 4;
				DWORD *pointerToDword = &playerWeakPtrs[i];
				controllablesToSpot.push_back(pointerToDword);
			}

			//if (controllablesToSpot.size() == 2)
			{
				sendSpottingMessage(Component, LocalClientPlayer, &controllablesToSpot, 1);

				controllablesToSpot.clear();
			}
		}

		SendSpotWait(100);
	}
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

void SelfHeal()
{
	ClientPlayer* LocalClientPlayer = GetLocalPlayer();

	if (MmIsAddressValidPtr(LocalClientPlayer))
	{
		ClientSoldierEntity* LocalClientSoldierEntity = LocalClientPlayer->GetClientSoldier();

		if (MmIsAddressValidPtr(LocalClientSoldierEntity))
		{
			ClientSoldierEntity* pCSE = LocalClientPlayer->GetClientSoldier();
			if (!MmIsAddressValidPtr(pCSE))
				return;

			ClientSoldierReplication* pCSR = pCSE->m_pClientSoldierReplication;
			if (!MmIsAddressValidPtr(pCSR))
				return;

			ClientSoldierWeaponsComponent* pCSWC = pCSE->m_pClientSoldierWeaponsComponent;
			if (!MmIsAddressValidPtr(pCSWC))
				return;

			ClientSoldierWeapon* pCSW = pCSWC->GetActiveSoldierWeapon();
			if (!MmIsAddressValidPtr(pCSW))
				return;

			ClientWeapon* pCW = pCSW->m_pWeapon;
			if (!MmIsAddressValidPtr(pCW))
				return;

			WeaponFiring* pWF = pCSW->m_pPrimaryFiring;
			if (!MmIsAddressValidPtr(pWF))
				return;

			if (LocalClientSoldierEntity->m_Health < 100.0f && pWF->m_weaponState == 9)
				HealSelf(LocalClientPlayer);
		}
	}
}

void ForceSquadSpawn()
{
	for (int i = 0; i < 24; i++) {

		ClientPlayer* Target = GetPlayerById(i);

		if (!MmIsAddressValidPtr(Target))
			continue;

		if (!IsClientAlive(Target))
			continue;

		if (GetLocalPlayer() == Target)
			continue;

		if (!MmIsAddressValidPtr(Target->m_pControlledControllable))
			continue;

		if (!MmIsAddressValidPtr(Target->m_pControlledControllable->m_pClientSoldierPrediction))
			continue;

		Target->m_isAllowedToSpawnOn = true;

	}
}


