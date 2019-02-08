#pragma once

extern Menu MenuBase;

extern float FlySpeed;
extern float fTeleHeight;
extern float fCompassSize;

extern int ArrayEnumarator;

extern int PrimaryArrayEnumarator;
extern int SecondaryArrayEnumarator;
extern int Gadget1ArrayEnumarator;
extern int Gadget2WeaponArrayEnumarator;
extern int GrenadeWeaponArrayEnumarator;
extern int SnapArrayEnumaratorE;
extern int SnapArrayEnumaratorF;
extern int SpoofArrayEnumarator;

extern int Spoof[];
extern int Gun[];

extern int ESPType;

extern int fPacketSpeed;
extern bool bPacketHack;

extern bool ServerCrash;
extern bool BoolOption;
extern bool bAimbot;
extern bool bVisibility;
extern bool bFOVCheck;
extern bool bTeleCrosshair;
extern bool bTeleAir;
extern bool bSilentAimbot;
extern bool bFlyHack;
extern bool bUnfairAimbot;
extern bool bUnlimitedAmmo;
extern bool bHealSelf;
extern bool bTeamHeal;
extern bool bAimingRequired;
extern bool bAntiParachute;
extern bool bNoSpreadFake;
extern bool bNoSpread;
extern bool bNoSway;
extern bool bNoBBobbing;
extern bool bESPEnemy;
extern bool bVehicleESP;
extern bool bESPFriendly;
extern bool bDrawSnapLinesE;
extern bool bDrawSnapLinesF;
extern bool bDrawBonesE;
extern bool bDrawBonesF;
extern bool bAutoShoot;
extern bool bDrawPickups;
extern bool bDrawSupply;
extern bool bDrawUnusedVehicles;
extern bool bHeadshots;
extern bool bDrawGrenade;
extern bool bDrawExplosive;
extern bool bVehicleChams;
extern bool bPlayerChamsE;
extern bool bPlayerChamsF;
extern bool bInvisible;
extern bool bSpoofKills;
extern bool bSpoofTarget;
extern bool bUAV;
extern bool bTargetInfo;
extern bool pAim;
extern bool bFriendName;
extern bool bEnemyName;
extern bool bDrawRadar;
extern bool bECompass;
extern bool bFCompass;
extern bool bAutoSpot;
extern bool bForceSquadSpawn;
extern bool bOHK;
extern bool bClientHealthBarF;
extern bool bClientHealthBarE;
extern bool bBlueTint;
extern bool SetIni;
extern bool GetIni;

void DoIniSet();
void DoIniLoad();

void AddMenuOptions();

void LoadINI();

void SetInit();
