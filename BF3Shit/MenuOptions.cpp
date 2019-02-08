#include "main.h"

Menu MenuBase;

float Menu_X = 0.5f;
float Menu_Y = 0.4f;

int IntOption = 1;

int ArrayEnumarator = 0;

int PrimaryArrayEnumarator = 0;
int SecondaryArrayEnumarator = 0;
int Gadget1ArrayEnumarator = 0;
int Gadget2WeaponArrayEnumarator = 0;
int GrenadeWeaponArrayEnumarator = 0;
int SnapArrayEnumaratorE = 0;
int SnapArrayEnumaratorF = 0;
int SpoofArrayEnumarator = 0;

bool bPacketHack = false;
bool ServerCrash = false;
bool BoolOption = false;
bool bAimbot = false;
bool bVisibility = false;
bool bFOVCheck = false;
bool bSilentAimbot = false;
bool bFlyHack = false;
bool bTeleCrosshair = false;
bool bTeleAir = false;
bool bUnfairAimbot = false;
bool bUnlimitedAmmo = false;
bool bHealSelf = false;
bool bTeamHeal = false;
bool bAimingRequired = false;
bool bAntiParachute = false;
bool bNoSpreadFake = false;
bool bNoSpread = false;
bool bNoSway = false;
bool bNoBBobbing = false;
bool bESPEnemy = false;
bool bVehicleESP = false;
bool bESPFriendly = false;
bool bDrawSnapLinesE = false;
bool bDrawSnapLinesF = false;
bool bDrawBonesE = false;
bool bDrawBonesF = false;
bool bAutoShoot = false;
bool bDrawPickups = false;
bool bDrawSupply = false;
bool bDrawUnusedVehicles = false;
bool bHeadshots = false;
bool bDrawGrenade = false;
bool bDrawExplosive = false;
bool bVehicleChams = false;
bool bPlayerChamsE = false;
bool bPlayerChamsF = false;
bool bInvisible = false;
bool bSpoofKills = false;
bool bSpoofTarget = false;
bool bUAV = false;
bool bOHK = false;
bool bTargetInfo = false;
bool pAim = false;
bool bFriendName = false;
bool bEnemyName = false;
bool bDrawRadar = false;
bool bECompass = false;
bool bFCompass = false;
bool bAutoSpot = false;
bool bForceSquadSpawn = false;
bool bBlueTint = false;
bool bClientHealthBarF = false;
bool bClientHealthBarE = false;

int fPacketSpeed = 100;
float damage = 100.0f;
float FlySpeed = 10.0f;
float fTeleHeight = 50.0f;
float fCompassSize = 120.0f;

int ESPType = 0;
int MainMenu = 0, MiscMenu = 0, AimbotMenu = 0, WeaponMenu = 0, ClassCustomizationMenu = 0, SendChatMenu = 0, ESPMenu = 0, EnemyESPMenu = 0, FriendlyESPMenu = 0, VehicleESPMenu = 0, EntityESPMenu = 0, CompassMenu = 0;
int Gun[] = { 0x7ECAA648, 0x74E2BFBA, 0x449E68FC, 0x7475B83D, 0x66ACC2FE, 0x270013D1, 0xDE801D07, 0xDFC9E5A, 0x231EBF24, 0xA9BEFA95 };
int Spoof[] = { 0xA6784811, 0x7ECAA648, 0x74E2BFBA, 0xADD2FC9A, 0x4BE5D515, 0x256F047E, 0x490A8A5F, 0xBF93FD19, 0x697AA0D0, 0xD1ABE5D3, 0xC25A2EB5, 0x6C6ACD2B };

const char* ESPArray[] = { "3D ESP", "2D ESP" };

const char* OptionArray[] = { "RAWR", "MKV", "MGL", "MGL[Infinite Ammo]", "M82A3 CQB", "M82A3 MED","M82A3", "AMR2 CQB", "AMR2 MED", "AMR2" };

const char* SpoofArray[] = { "Railgun", "RAWR", "MKV", "Hand Flare", "Cruise Missle", "Icicle", "AK-12", "Knife", "Ammo Bag", "Medic Bag", "Ballistic Shield", "Killed" };
const char* SnapLineArray[] = { "TOP", "MIDDLE", "BOTTOM" };


void SendChatMessage(wchar_t *Message)
{
	*(int*)(0x835F48BC) = 0x39000000;//force server id
	*(int*)(0x835F48C8) = 0x38E0FFFF;//force all mask
	*(int*)(0x835F48D0) = 0x38C00004;//for all chatchannel
	*(int*)(0x835F48D8) = 0x38A00000;//Set is dead byte to 0
	*(int*)(0x835F48B0) = 0x7FC4F378;//mr %r4, %r30
	*(int*)(0x835F48B4) = 0x60000000;//nop next

	lstrcpyW((LPWSTR)0x8406041F, Message);
	*(unsigned char*)0x840603E0 = 1;
}

void SetPrimary()
{

}
void SetSecondary()
{

}
void SetGadet1()
{

}
void SetGadget2()
{

}
void SetGrenade()
{

}
void DoInvisible()
{

}

void AddMenuOptions()
{
	MainMenu = MenuBase.CreateSubMenu("Main Menu");
	MenuBase.AddSubMenuLink("Misc", "", &MiscMenu);
	MenuBase.AddSubMenuLink("Aimbot", "", &AimbotMenu);
	MenuBase.AddSubMenuLink("Weapon mods", "", &WeaponMenu);
	//MenuBase.AddSubMenuLink("Customization", "", &ClassCustomizationMenu);
	MenuBase.AddSubMenuLink("Chat messages", "", &SendChatMenu);
	MenuBase.AddSubMenuLink("ESP", "", &ESPMenu);
	//MenuBase.AddCall("Test Option Set", "", GetXuid, "s", 1, "haloskinner");
	//MenuBase.AddCall("Test Option Reset", "", GetXuid, "s", 1, "x goes over pi");

	MiscMenu = MenuBase.CreateSubMenu("Misc");
	//MenuBase.AddBool("Teleport To Crosshair [RB]", "Press RB to teleport to your crosshair.", &bTeleCrosshair);
	//MenuBase.AddBool("Teleport in Air [RS & LS]", "Press the right thumb and left thumb button to teleport into the air.", &bTeleAir);
	//MenuBase.AddFloat("Teleport Height", "Allows you to set how high you teleport.", &fTeleHeight, 20.0f, 0.0f, 2000.0f);
	MenuBase.AddBool("Speed Hack", "Allows you to move fasts.", &bPacketHack);
	MenuBase.AddInt("Speed Hack Interval", "Which speed you move.", &fPacketSpeed, 50, 100, 400);
	MenuBase.AddBool("Flyhack", "Enables no-clip.", &bFlyHack);
	MenuBase.AddFloat("Fly speed", "Player Flying Speed", &FlySpeed, 10.f, 0.0f, 550.0f);
	MenuBase.AddBool("Auto Spot", "Automatically Spots Players.", &bAutoSpot);
	MenuBase.AddBool("Force Squad Spawn", "Allows you to spawn on any squad member.", &bForceSquadSpawn);
	MenuBase.AddBool("Blue Tint", "Removes the BF3 Blue tint over the screen", &bBlueTint);

	AimbotMenu = MenuBase.CreateSubMenu("Aimbot");
	MenuBase.AddBool("Aimbot", "Enables aimbot.", &bAimbot);
	MenuBase.AddBool("Aiming Required", "The aimbot will only be activated when ADS.", &bAimingRequired);
	MenuBase.AddBool("Visibility Check", "The aimbot will only aim at visible players.", &bVisibility);  //todo
	//MenuBase.AddBool("Spread Predicition", "The aimbot will automatically counter your recoil and spread.", &pAim); //todo
	//MenuBase.AddBool("Aiming in Parachute", "This will allow you to rotate 360 degrees while in a parachute.", &bAntiParachute); //todo
	MenuBase.AddBool("Auto Shoot", "Shoots automatically when target is in sight.", &bAutoShoot); //todo
	MenuBase.AddBool("Silent Aimbot", "Curved bullets", &bSilentAimbot);//todo
	MenuBase.AddBool("Unfair Aimbot", "Allows the user to shoot through some walls.", &bUnfairAimbot); //fix
	MenuBase.AddBool("Headshots", "Sets if your damage type is a headshot.", &bHeadshots); //fix
	MenuBase.AddBool("Spoof WeaponID to Target", "Allows the user to spoof their kills to that of their target.", &bSpoofTarget); //todo
	//MenuBase.AddBool("Spoof Kills", "Allows the user to spoof kills.", &bSpoofKills);//todo
	//MenuBase.AddListBox("Spoof Weapon", "Sets your weapon to be spoofed.", &SpoofArrayEnumarator, SpoofArray, 12);//todo

	WeaponMenu = MenuBase.CreateSubMenu("Weapon Mods");
	MenuBase.AddBool("Unlimited Ammo", "Gives your weapon unlimited ammo.", &bUnlimitedAmmo);
	MenuBase.AddBool("Self Healing Gun", "Health regens whilst shooting.", &bHealSelf); //fix
	MenuBase.AddBool("Team Healing Gun", "Regens your friendlies health whilst shooting.", &bTeamHeal); //fix
	//MenuBase.AddBool("One hit kill", "Sets the bullet damage.", &bOHK); //todo
	MenuBase.AddBool("Remove View bobbing", "Enable and see what it does", &bNoBBobbing); //todo
	MenuBase.AddBool("No Spread", "Enable and see what it does", &bNoSpreadFake); //todo

	//ClassCustomizationMenu = MenuBase.CreateSubMenu("Customization");
	//MenuBase.AddListBox("Set Primary", "Sets your weapon to the selected option.", &PrimaryArrayEnumarator, OptionArray, 10, SetPrimary);			  //todo
	//MenuBase.AddListBox("Set Secondary", "Sets your weapon to the selected option.", &SecondaryArrayEnumarator, OptionArray, 10, SetSecondary);		  //todo
	//MenuBase.AddListBox("Set Gadget 1", "Sets your weapon to the selected option.", &Gadget1ArrayEnumarator, OptionArray, 10, SetGadet1);			  //todo
	//MenuBase.AddListBox("Set Gadget 2", "Sets your weapon to the selected option.", &Gadget2WeaponArrayEnumarator, OptionArray, 10, SetGadget2);	  //todo
	//MenuBase.AddListBox("Set Grenade", "Sets your weapon to the selected option.", &GrenadeWeaponArrayEnumarator, OptionArray, 10, SetGrenade);		  //todo
	//MenuBase.AddCall("Invisibility", "Makes your player invisible to other clients. [YOU HAVE TO RESPAWN]", DoInvisible);							  //todo

	SendChatMenu = MenuBase.CreateSubMenu("Chat Message");
	MenuBase.AddCall("Made by Trojan041 and Sabotage!", "Sends a chat message.", SendChatMessage, "s", 1, L"Made by Trojan041 and Sabotage!");				//todo
	MenuBase.AddCall("Trojan041#1337", "Sends a chat message.", SendChatMessage, "s", 1, L"Trojan041#1337");												//todo
	MenuBase.AddCall("Sabotage#1337", "Sends a chat message.", SendChatMessage, "s", 1, L"Sabotage#1337");													//todo
	MenuBase.AddCall("https://xbOnline.live/", "Sends a chat message.", SendChatMessage, "s", 1, L"https://xbOnline.live/");								//todo
	MenuBase.AddCall("Sabotage eats shoes", "Sends a chat message.", SendChatMessage, "s", 1, L"Sabotage eats shoes");										//todo
	MenuBase.AddCall("Fubc is dad", "Sends a chat message.", SendChatMessage, "s", 1, L"Fubc is dad");														//todo
	MenuBase.AddCall("I'm a nasty lil cheater", "Sends a chat message.", SendChatMessage, "s", 1, L"I'm a nasty lil cheater");								//todo
	MenuBase.AddCall("We always finish second.", "Sends a chat message.", SendChatMessage, "s", 1, L"We always finish second.");							//todo
	MenuBase.AddCall("Why do I have so many notification?", "Sends a chat message.", SendChatMessage, "s", 1, L"Why do I have so many notification?");		//todo
	MenuBase.AddCall("Shoutout windows defender", "Sends a chat message.", SendChatMessage, "s", 1, L"Shoutout windows defender");							//todo
	MenuBase.AddCall("El Carterino was here!", "Sends a chat message.", SendChatMessage, "s", 1, L"El Carterino was here!");								//todo

	ESPMenu = MenuBase.CreateSubMenu("ESP");
	MenuBase.AddListBox("ESP Type", "Choose the ESP Type.", &ESPType, ESPArray, 2);
	MenuBase.AddBool("Target Info", "Enable this to display information about your client.", &bTargetInfo);
	MenuBase.AddBool("UAV", "Shows all players on the minimap.", &bUAV);
	MenuBase.AddSubMenuLink("Compass", "", &CompassMenu);
	MenuBase.AddSubMenuLink("Enemies", "", &EnemyESPMenu);
	MenuBase.AddSubMenuLink("Friendly", "", &FriendlyESPMenu);
	MenuBase.AddSubMenuLink("Vehicles", "", &VehicleESPMenu);//todo
	//MenuBase.AddSubMenuLink("Entity", "", &EntityESPMenu);//todo

	CompassMenu = MenuBase.CreateSubMenu("Compass");
	MenuBase.AddFloat("Compass Size", "Defines the size of the compass.", &fCompassSize, 5.0f, 120.0f, 320.0f);
	MenuBase.AddBool("Draw Enemies", "Draws all your enemies on the compass.", &bECompass);
	MenuBase.AddBool("Draw Friendlies", "Draws all your friendlies on the compass.", &bFCompass);

	EnemyESPMenu = MenuBase.CreateSubMenu("Enemy");
	MenuBase.AddBool("Enemy ESP", "Enable ESP for enemies.", &bESPEnemy);
	MenuBase.AddBool("Name ESP", "Enable Name ESP for enemies.", &bEnemyName);
	MenuBase.AddBool("Draw Snaplines", "Draws lines from the crosshair to players.", &bDrawSnapLinesE);
	MenuBase.AddListBox("Snapline position", "Positions snapline in the top/middle/bottom", &SnapArrayEnumaratorE, SnapLineArray, 3);
	MenuBase.AddBool("Draw Bones", "Draw player bones.", &bDrawBonesE);
	MenuBase.AddBool("Draw Health Bar", "Draws players health.", &bClientHealthBarE);
	/*MenuBase.AddBool("Player Chams", "Enable for highlighted Players.", &bPlayerChamsE);*/

	FriendlyESPMenu = MenuBase.CreateSubMenu("Friendly");
	MenuBase.AddBool("Friendly ESP", "Enable ESP for friendlies.", &bESPFriendly);
	MenuBase.AddBool("Name ESP", "Enable Name ESP for friendlies.", &bFriendName);
	MenuBase.AddBool("Draw Snaplines", "Draws lines from the crosshair to players.", &bDrawSnapLinesF);
	MenuBase.AddListBox("Snapline position", "Positions snapline in the top/middle/bottom", &SnapArrayEnumaratorF, SnapLineArray, 3);
	MenuBase.AddBool("Draw Bones", "Draw player bones.", &bDrawBonesF);
	MenuBase.AddBool("Draw Health Bar", "Draws players health.", &bClientHealthBarF);
	/*MenuBase.AddBool("Player Chams", "Enable for highlighted Players.", &bPlayerChamsF);*/

	VehicleESPMenu = MenuBase.CreateSubMenu("Vehicles");
	MenuBase.AddBool("Vehicle ESP", "Draws boxes around vehicles.", &bVehicleESP);
	/*MenuBase.AddBool("Vehicle Chams", "Enable for highlighted vehicles.", &bVehicleChams);*/
	/*MenuBase.AddBool("Draw Unused Vehicles", "Draws boxes around empty vehicles.", &bDrawUnusedVehicles);*/

	//EntityESPMenu = MenuBase.CreateSubMenu("Entity");
	//MenuBase.AddBool("Draw Pickups", "Draws any weapons that are on the ground.", &bDrawPickups);
	//MenuBase.AddBool("Draw Supply Crates", "Draws medkits and ammoboxes.", &bDrawSupply);
	//MenuBase.AddBool("Draw Explosives", "Draws claymores/c4/anti-tank.", &bDrawExplosive);
	//MenuBase.AddBool("Draw Grenade", "Draws Grenades.", &bDrawGrenade);
}


void LoadINI()
{
	CSimpleIniA ini;

	if (!FileExists("Nigel:\\xbOnline"))
		CreateDirectory("Nigel:\\xbOnline", NULL);

	if (!ini.LoadFile("Nigel:\\xbOnline\\BF3.cfg"))
	{
		if (!strcmp(ini.GetValue("Game", "ESPType"), "3D ESP"))
			ESPType = 0;
		else
			ESPType = 1;


		bAimbot = ini.GetBoolValue("Game", "bAimbot");
		bVisibility = ini.GetBoolValue("Game", "bVisibility");
		bFOVCheck = ini.GetBoolValue("Game", "bFOVCheck");
		bSilentAimbot = ini.GetBoolValue("Game", "bSilentAimbot");
		bFlyHack = ini.GetBoolValue("Game", "bFlyHack");
		bTeleCrosshair = ini.GetBoolValue("Game", "bTeleCrosshair");
		bTeleAir = ini.GetBoolValue("Game", "bTeleAir");
		bUnfairAimbot = ini.GetBoolValue("Game", "bUnfairAimbot");
		bUnlimitedAmmo = ini.GetBoolValue("Game", "bUnlimitedAmmo");
		bHealSelf = ini.GetBoolValue("Game", "bHealSelf");
		bTeamHeal = ini.GetBoolValue("Game", "bTeamHeal");
		bAimingRequired = ini.GetBoolValue("Game", "bAimingRequired");
		bAntiParachute = ini.GetBoolValue("Game", "bAntiParachute");
		bNoSpreadFake = ini.GetBoolValue("Game", "bNoSpreadFake");
		bNoSpread = ini.GetBoolValue("Game", "bNoSpread");
		bNoSway = ini.GetBoolValue("Game", "bNoSway");
		bNoBBobbing = ini.GetBoolValue("Game", "bNoBBobbing");
		bESPEnemy = ini.GetBoolValue("Game", "bESPEnemy");
		bVehicleESP = ini.GetBoolValue("Game", "bVehicleESP");
		bESPFriendly = ini.GetBoolValue("Game", "bESPFriendly");
		bDrawSnapLinesE = ini.GetBoolValue("Game", "bDrawSnapLinesE");
		bDrawSnapLinesF = ini.GetBoolValue("Game", "bDrawSnapLinesF");
		bDrawBonesE = ini.GetBoolValue("Game", "bDrawBonesE");
		bDrawBonesF = ini.GetBoolValue("Game", "bDrawBonesF");
		bAutoShoot = ini.GetBoolValue("Game", "bAutoShoot");
		bDrawPickups = ini.GetBoolValue("Game", "bDrawPickups");
		bDrawSupply = ini.GetBoolValue("Game", "bDrawSupply");
		bDrawUnusedVehicles = ini.GetBoolValue("Game", "bDrawUnusedVehicles");
		bHeadshots = ini.GetBoolValue("Game", "bHeadshots");
		bDrawGrenade = ini.GetBoolValue("Game", "bDrawGrenade");
		bDrawExplosive = ini.GetBoolValue("Game", "bDrawExplosive");
		bVehicleChams = ini.GetBoolValue("Game", "bVehicleChams");
		bPlayerChamsE = ini.GetBoolValue("Game", "bPlayerChamsE");
		bPlayerChamsF = ini.GetBoolValue("Game", "bPlayerChamsF");
		bInvisible = ini.GetBoolValue("Game", "bInvisible");
		bSpoofKills = ini.GetBoolValue("Game", "bSpoofKills");
		bSpoofTarget = ini.GetBoolValue("Game", "bSpoofTarget");
		bUAV = ini.GetBoolValue("Game", "bUAV");
		bOHK = ini.GetBoolValue("Game", "bOHK");
		bTargetInfo = ini.GetBoolValue("Game", "bTargetInfo");
		pAim = ini.GetBoolValue("Game", "pAim");
		bFriendName = ini.GetBoolValue("Game", "bFriendName");
		bEnemyName = ini.GetBoolValue("Game", "bEnemyName");
		bDrawRadar = ini.GetBoolValue("Game", "bDrawRadar");
		bPacketHack = ini.GetBoolValue("Game", "bPacketHack");
		bAutoSpot = ini.GetBoolValue("Game", "bAutoSpot");
		bForceSquadSpawn = ini.GetBoolValue("Game", "bForceSquadSpawn");
		bClientHealthBarF = ini.GetBoolValue("Game", "bClientHealthBarF");
		bClientHealthBarE = ini.GetBoolValue("Game", "bClientHealthBarE");
		bBlueTint = ini.GetBoolValue("Game", "bBlueTint");
	}
	else
	{
		ini.SetValue("Game", "ESPType", "3D ESP");
		ini.SetValue("Game", "bAimbot", "false");
		ini.SetValue("Game", "bVisibility", "false");
		ini.SetValue("Game", "bFOVCheck", "false");
		ini.SetValue("Game", "bSilentAimbot", "false");
		ini.SetValue("Game", "bFlyHack", "false");
		ini.SetValue("Game", "bTeleCrosshair", "false");
		ini.SetValue("Game", "bTeleAir", "false");
		ini.SetValue("Game", "bUnfairAimbot", "false");
		ini.SetValue("Game", "bUnlimitedAmmo", "false");
		ini.SetValue("Game", "bHealSelf", "false");
		ini.SetValue("Game", "bTeamHeal", "false");
		ini.SetValue("Game", "bAimingRequired", "false");
		ini.SetValue("Game", "bAntiParachute", "false");
		ini.SetValue("Game", "bNoSpreadFake", "false");
		ini.SetValue("Game", "bNoSpread", "false");
		ini.SetValue("Game", "bNoSway", "false");
		ini.SetValue("Game", "bNoBBobbing", "false");
		ini.SetValue("Game", "bESPEnemy", "false");
		ini.SetValue("Game", "bVehicleESP", "false");
		ini.SetValue("Game", "bESPFriendly", "false");
		ini.SetValue("Game", "bDrawSnapLinesE", "false");
		ini.SetValue("Game", "bDrawSnapLinesF", "false");
		ini.SetValue("Game", "bDrawBonesE", "false");
		ini.SetValue("Game", "bDrawBonesF", "false");
		ini.SetValue("Game", "bAutoShoot", "false");
		ini.SetValue("Game", "bDrawPickups", "false");
		ini.SetValue("Game", "bDrawSupply", "false");
		ini.SetValue("Game", "bDrawUnusedVehicles", "false");
		ini.SetValue("Game", "bHeadshots", "false");
		ini.SetValue("Game", "bDrawGrenade", "false");
		ini.SetValue("Game", "bDrawExplosive", "false");
		ini.SetValue("Game", "bVehicleChams", "false");
		ini.SetValue("Game", "bPlayerChamsE", "false");
		ini.SetValue("Game", "bPlayerChamsF", "false");
		ini.SetValue("Game", "bInvisible", "false");
		ini.SetValue("Game", "bSpoofKills", "false");
		ini.SetValue("Game", "bSpoofTarget", "false");
		ini.SetValue("Game", "bUAV", "false");
		ini.SetValue("Game", "bOHK", "false");
		ini.SetValue("Game", "bTargetInfo", "false");
		ini.SetValue("Game", "pAim", "false");
		ini.SetValue("Game", "bFriendName", "false");
		ini.SetValue("Game", "bEnemyName", "false");
		ini.SetValue("Game", "bPacketHack", "false");
		ini.SetValue("Game", "bAutoSpot", "false");
		ini.SetValue("Game", "bForceSquadSpawn", "false");
		ini.SetValue("Game", "bClientHealthBarF", "false");
		ini.SetValue("Game", "bClientHealthBarE", "false");
		ini.SetValue("Game", "bBlueTint", "false");
		ini.SaveFile("Nigel:\\xbOnline\\BF3.cfg");
	}
}

void SetInit()
{
	CSimpleIniA ini;

	if (!ini.LoadFile("Nigel:\\xbOnline\\BF3.cfg"))
	{
		switch (ESPType)
		{
		case 0:
			ini.SetValue("Game", "ESPType", "3D ESP");
			break;
		case 1:
			ini.SetValue("Game", "ESPType", "2D ESP");
			break;
		default:
			break;
		}

		ini.SetValue("Game", "bAimbot", bAimbot ? "true" : "false");
		ini.SetValue("Game", "bVisibility", bVisibility ? "true" : "false");
		ini.SetValue("Game", "bFOVCheck", bFOVCheck ? "true" : "false");
		ini.SetValue("Game", "bSilentAimbot", bSilentAimbot ? "true" : "false");
		ini.SetValue("Game", "bFlyHack", bFlyHack ? "true" : "false");
		ini.SetValue("Game", "bTeleCrosshair", bTeleCrosshair ? "true" : "false");
		ini.SetValue("Game", "bTeleAir", bTeleAir ? "true" : "false");
		ini.SetValue("Game", "bUnfairAimbot", bUnfairAimbot ? "true" : "false");
		ini.SetValue("Game", "bUnlimitedAmmo", bUnlimitedAmmo ? "true" : "false");
		ini.SetValue("Game", "bHealSelf", bHealSelf ? "true" : "false");
		ini.SetValue("Game", "bTeamHeal", bTeamHeal ? "true" : "false");
		ini.SetValue("Game", "bAimingRequired", bAimingRequired ? "true" : "false");
		ini.SetValue("Game", "bAntiParachute", bAntiParachute ? "true" : "false");
		ini.SetValue("Game", "bNoSpreadFake", bNoSpreadFake ? "true" : "false");
		ini.SetValue("Game", "bNoSpread", bNoSpread ? "true" : "false");
		ini.SetValue("Game", "bNoSway", bNoSway ? "true" : "false");
		ini.SetValue("Game", "bNoBBobbing", bNoBBobbing ? "true" : "false");
		ini.SetValue("Game", "bESPEnemy", bESPEnemy ? "true" : "false");
		ini.SetValue("Game", "bVehicleESP", bVehicleESP ? "true" : "false");
		ini.SetValue("Game", "bESPFriendly", bESPFriendly ? "true" : "false");
		ini.SetValue("Game", "bDrawSnapLinesE", bDrawSnapLinesE ? "true" : "false");
		ini.SetValue("Game", "bDrawSnapLinesF", bDrawSnapLinesF ? "true" : "false");
		ini.SetValue("Game", "bDrawBonesE", bDrawBonesE ? "true" : "false");
		ini.SetValue("Game", "bDrawBonesF", bDrawBonesF ? "true" : "false");
		ini.SetValue("Game", "bAutoShoot", bAutoShoot ? "true" : "false");
		ini.SetValue("Game", "bDrawPickups", bDrawPickups ? "true" : "false");
		ini.SetValue("Game", "bDrawSupply", bDrawSupply ? "true" : "false");
		ini.SetValue("Game", "bDrawUnusedVehicles", bDrawUnusedVehicles ? "true" : "false");
		ini.SetValue("Game", "bHeadshots", bHeadshots ? "true" : "false");
		ini.SetValue("Game", "bDrawGrenade", bDrawGrenade ? "true" : "false");
		ini.SetValue("Game", "bDrawExplosive", bDrawExplosive ? "true" : "false");
		ini.SetValue("Game", "bVehicleChams", bVehicleChams ? "true" : "false");
		ini.SetValue("Game", "bPlayerChamsE", bPlayerChamsE ? "true" : "false");
		ini.SetValue("Game", "bPlayerChamsF", bPlayerChamsF ? "true" : "false");
		ini.SetValue("Game", "bInvisible", bInvisible ? "true" : "false");
		ini.SetValue("Game", "bSpoofKills", bSpoofKills ? "true" : "false");
		ini.SetValue("Game", "bSpoofTarget", bSpoofTarget ? "true" : "false");
		ini.SetValue("Game", "bUAV", bUAV ? "true" : "false");
		ini.SetValue("Game", "bOHK", bOHK ? "true" : "false");
		ini.SetValue("Game", "bTargetInfo", bTargetInfo ? "true" : "false");
		ini.SetValue("Game", "pAim", pAim ? "true" : "false");
		ini.SetValue("Game", "bFriendName", bFriendName ? "true" : "false");
		ini.SetValue("Game", "bEnemyName", bEnemyName ? "true" : "false");
		ini.SetValue("Game", "bDrawRadar", bDrawRadar ? "true" : "false");
		ini.SetValue("Game", "bPacketHack", bPacketHack ? "true" : "false");
		ini.SetValue("Game", "bAutoSpot", bAutoSpot ? "true" : "false");
		ini.SetValue("Game", "bForceSquadSpawn", bForceSquadSpawn ? "true" : "false");
		ini.SetValue("Game", "bClientHealthBarF", bClientHealthBarF ? "true" : "false");
		ini.SetValue("Game", "bClientHealthBarE", bClientHealthBarE ? "true" : "false");
		ini.SetValue("Game", "bBlueTint", bBlueTint ? "true" : "false");
		ini.SaveFile("Nigel:\\xbOnline\\BF3.cfg");
	}
}

