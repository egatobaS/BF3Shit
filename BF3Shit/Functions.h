#pragma once

extern Vector3 pSilent;
extern bool setBitFlag;
extern bool bShoot;
extern bool bTriggerBot;
extern int ShootCount;


extern WeaponSway::Deviation* pRecoil;
extern WeaponSway::Deviation *pSpread;

bool WorldToScreen(Vector3 WorldPos, Vector3 * ScreenPos);

ClientPlayer * GetLocalPlayer();

ClientPlayer * GetPlayerById(unsigned int id);

bool IsLocalClientAlive();

bool IsClientAlive(ClientPlayer * pTarget);

void setIsAuthoritativeMovementActive(EntryInputState * pEIS, BOOL active);

void MovementHack();

void DrawCompass(Vector3 ClientPosition, D3DCOLOR Color, float CompassSize);

Vector3 Multiply(Vector3 vec, Matrix * mat);

bool Draw2DBox(ClientVehicleEntity * pEnt, D3DCOLOR color, float size);

bool TransformDrawAABB(ClientVehicleEntity * pEnt, D3DCOLOR color, float size);

bool GetBonePos(ClientSoldierEntity * pEnt, int iBone, Vector3 * vOut);

void DrawBoneLine(ClientPlayer * entity, int tagname1, int tagname2, D3DCOLOR col);

void DoAllBones(ClientPlayer * Client, D3DCOLOR boneESPCol);

bool DrawESP();

float solveQuadratic(float a, float b, float c);

bool custom_isnan(double var);

void AimCorrection(Vector3 * inVec, Vector3 enemyVelo, Vector3 myVelo, float Distance, float BulletSpeed, float Gravity);

int ClosestClient(ClientPlayer * LocalPlayer);

void DamagePlayer(ClientPlayer * Target, ClientPlayer * LocalPlayer, float damage, UnlockAssetBase * Weapon, HitReactionType HitType);

void HealSelf(ClientPlayer * LocalPlayer);

int getKitID();

UnlockAssetBase * getUA(ClientPlayer * localp);

ClientPlayerScore * GetScorePTR();

void DoAmmo();

void HealTeam(ClientPlayer * LocalPlayer);

void Aimbot(ClientPlayer * LocalEntity);

extern int NearestPlayer;

extern bool isClientWallable[24];

unsigned long long GetXuid(char* Name);

void SendSpot(ClientSpottingComponent * Component, ClientPlayer * LocalClientPlayer);

void FixMovement(EntryInputState * pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove);

void SelfHeal();

void ForceSquadSpawn();
