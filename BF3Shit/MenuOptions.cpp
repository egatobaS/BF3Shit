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

float damage = 100.0f;
float FlySpeed = 10.0f;
float fTeleHeight = 50.0f;
float fCompassSize = 120.0f;

int ESPType = 0;
int MainMenu = 0, MovementMenu = 0, AimbotMenu = 0, WeaponMenu = 0, ClassCustomizationMenu = 0, SendChatMenu = 0, ESPMenu = 0, EnemyESPMenu = 0, FriendlyESPMenu = 0, VehicleESPMenu = 0, EntityESPMenu = 0, CompassMenu = 0;
int Gun[] = { 0x7ECAA648, 0x74E2BFBA, 0x449E68FC, 0x7475B83D, 0x66ACC2FE, 0x270013D1, 0xDE801D07, 0xDFC9E5A, 0x231EBF24, 0xA9BEFA95 };
int Spoof[] = { 0xA6784811, 0x7ECAA648, 0x74E2BFBA, 0xADD2FC9A, 0x4BE5D515, 0x256F047E, 0x490A8A5F, 0xBF93FD19, 0x697AA0D0, 0xD1ABE5D3, 0xC25A2EB5, 0x6C6ACD2B };

const char* ESPArray[] = { "3D ESP", "2D ESP" };

const char* OptionArray[] = { "RAWR", "MKV", "MGL", "MGL[Infinite Ammo]", "M82A3 CQB", "M82A3 MED","M82A3", "AMR2 CQB", "AMR2 MED", "AMR2" };

const char* SpoofArray[] = { "Railgun", "RAWR", "MKV", "Hand Flare", "Cruise Missle", "Icicle", "AK-12", "Knife", "Ammo Bag", "Medic Bag", "Ballistic Shield", "Killed" };
const char* SnapLineArray[] = { "TOP", "MIDDLE", "BOTTOM" };


void SendChatMessage(wchar_t *Message)
{

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
	MenuBase.AddCall("Set Draw At Current Origin", "", SetDraw);

	MenuBase.AddSubMenuLink("Movement", "", &MovementMenu);
	MenuBase.AddSubMenuLink("Aimbot", "", &AimbotMenu);
	MenuBase.AddSubMenuLink("Weapon mods", "", &WeaponMenu);
	MenuBase.AddSubMenuLink("Customization", "", &ClassCustomizationMenu);
	MenuBase.AddSubMenuLink("Chat messages", "", &SendChatMenu);
	MenuBase.AddSubMenuLink("ESP", "", &ESPMenu);

	MovementMenu = MenuBase.CreateSubMenu("Movement");
	MenuBase.AddBool("Teleport To Crosshair [RB]", "Press RB to teleport to your crosshair.", &bTeleCrosshair);
	MenuBase.AddBool("Teleport in Air [RS & LS]", "Press the right thumb and left thumb button to teleport into the air.", &bTeleAir);
	MenuBase.AddFloat("Teleport Height", "Allows you to set how high you teleport.", &fTeleHeight, 20.0f, 0.0f, 2000.0f);

	AimbotMenu = MenuBase.CreateSubMenu("Aimbot");
	MenuBase.AddBool("Aimbot", "Enables aimbot.", &bAimbot);
	MenuBase.AddBool("Aiming Required", "The aimbot will only be activated when ADS.", &bAimingRequired);
	MenuBase.AddBool("Visibility Check", "The aimbot will only aim at visible players.", &bVisibility);
	MenuBase.AddBool("Spread Predicition", "The aimbot will automatically counter your recoil and spread.", &pAim);
	MenuBase.AddBool("Aiming in Parachute", "This will allow you to rotate 360 degrees while in a parachute.", &bAntiParachute);
	MenuBase.AddBool("Auto Shoot", "Shoots automatically when target is in sight.", &bAutoShoot);
	MenuBase.AddBool("Silent Aimbot", "Curved bullets", &bSilentAimbot);
	MenuBase.AddBool("Unfair Aimbot", "Allows the user to shoot through some walls.", &bUnfairAimbot);
	MenuBase.AddBool("Headshots", "Sets if your damage type is a headshot.", &bHeadshots);
	MenuBase.AddBool("Spoof WeaponID to Target", "Allows the user to spoof their kills to that of their target.", &bSpoofTarget);
	MenuBase.AddBool("Spoof Kills", "Allows the user to spoof kills.", &bSpoofKills);
	MenuBase.AddListBox("Spoof Weapon", "Sets your weapon to be spoofed.", &SpoofArrayEnumarator, SpoofArray, 12);

	WeaponMenu = MenuBase.CreateSubMenu("Weapon Mods");
	MenuBase.AddBool("Unlimited Ammo", "Gives your weapon unlimited ammo.", &bUnlimitedAmmo);
	MenuBase.AddBool("Self Healing Gun", "Health regens whilst shooting.", &bHealSelf);
	MenuBase.AddBool("Team Healing Gun", "Regens your friendlies health whilst shooting.", &bTeamHeal);
	MenuBase.AddBool("One hit kill", "Sets the bullet damage.", &bOHK);
	MenuBase.AddBool("Remove View bobbing", "Enable and see what it does", &bNoBBobbing);
	MenuBase.AddBool("Remove Visual Spread", "Enable and see what it does", &bNoSpreadFake);
	MenuBase.AddBool("Remove Sway", "Enable and see what it does", &bNoSway);


	ClassCustomizationMenu = MenuBase.CreateSubMenu("Customization");
	MenuBase.AddListBox("Set Primary", "Sets your weapon to the selected option.", &PrimaryArrayEnumarator, OptionArray, 10, SetPrimary);
	MenuBase.AddListBox("Set Secondary", "Sets your weapon to the selected option.", &SecondaryArrayEnumarator, OptionArray, 10, SetSecondary);
	MenuBase.AddListBox("Set Gadget 1", "Sets your weapon to the selected option.", &Gadget1ArrayEnumarator, OptionArray, 10, SetGadet1);
	MenuBase.AddListBox("Set Gadget 2", "Sets your weapon to the selected option.", &Gadget2WeaponArrayEnumarator, OptionArray, 10, SetGadget2);
	MenuBase.AddListBox("Set Grenade", "Sets your weapon to the selected option.", &GrenadeWeaponArrayEnumarator, OptionArray, 10, SetGrenade);
	MenuBase.AddCall("Invisibility", "Makes your player invisible to other clients. [YOU HAVE TO RESPAWN]", DoInvisible);

	SendChatMenu = MenuBase.CreateSubMenu("Chat Message");
	MenuBase.AddCall("Made by Trojan041 and Sabotage!", "Sends a chat message.", SendChatMessage, "s", 1, L"Made by Trojan041 and Sabotage!");
	MenuBase.AddCall("Trojan041#1337", "Sends a chat message.", SendChatMessage, "s", 1, L"Trojan041#1337");
	MenuBase.AddCall("Sabotage#1337", "Sends a chat message.", SendChatMessage, "s", 1, L"Sabotage#1337");
	MenuBase.AddCall("https://xbOnline.live/", "Sends a chat message.", SendChatMessage, "s", 1, L"https://xbOnline.live/");
	MenuBase.AddCall("Sabotage eats shoes", "Sends a chat message.", SendChatMessage, "s", 1, L"Sabotage eats shoes");
	MenuBase.AddCall("Fubc is dad", "Sends a chat message.", SendChatMessage, "s", 1, L"Fubc is dad");
	MenuBase.AddCall("I'm a nasty lil cheater", "Sends a chat message.", SendChatMessage, "s", 1, L"I'm a nasty lil cheater");
	MenuBase.AddCall("We always finish second.", "Sends a chat message.", SendChatMessage, "s", 1, L"We always finish second.");
	MenuBase.AddCall("Why do I have so many notification?", "Sends a chat message.", SendChatMessage, "s", 1, L"Why do I have so many notification?");
	MenuBase.AddCall("Shoutout windows defender", "Sends a chat message.", SendChatMessage, "s", 1, L"Shoutout windows defender");
	MenuBase.AddCall("El Carterino was here!", "Sends a chat message.", SendChatMessage, "s", 1, L"El Carterino was here!");

	ESPMenu = MenuBase.CreateSubMenu("ESP");
	MenuBase.AddListBox("ESP Type", "Choose the ESP Type.", &ESPType, ESPArray, 2);
	MenuBase.AddBool("Target Info", "Enable this to display information about your client.", &bTargetInfo);
	MenuBase.AddBool("UAV", "Shows all players on the minimap.", &bUAV);
	MenuBase.AddSubMenuLink("Compass", "", &CompassMenu);
	MenuBase.AddSubMenuLink("Enemies", "", &EnemyESPMenu);
	MenuBase.AddSubMenuLink("Friendly", "", &FriendlyESPMenu);
	MenuBase.AddSubMenuLink("Vehicles", "", &VehicleESPMenu);
	MenuBase.AddSubMenuLink("Entity", "", &EntityESPMenu);

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
	MenuBase.AddBool("Player Chams", "Enable for highlighted Players.", &bPlayerChamsE);

	FriendlyESPMenu = MenuBase.CreateSubMenu("Friendly");
	MenuBase.AddBool("Friendly ESP", "Enable ESP for friendlies.", &bESPFriendly);
	MenuBase.AddBool("Name ESP", "Enable Name ESP for friendlies.", &bFriendName);
	MenuBase.AddBool("Draw Snaplines", "Draws lines from the crosshair to players.", &bDrawSnapLinesF);
	MenuBase.AddListBox("Snapline position", "Positions snapline in the top/middle/bottom", &SnapArrayEnumaratorF, SnapLineArray, 3);
	MenuBase.AddBool("Draw Bones", "Draw player bones.", &bDrawBonesF);
	MenuBase.AddBool("Player Chams", "Enable for highlighted Players.", &bPlayerChamsF);

	VehicleESPMenu = MenuBase.CreateSubMenu("Vehicles");
	MenuBase.AddBool("Vehicle ESP", "Draws boxes around vehicles.", &bVehicleESP);
	MenuBase.AddBool("Vehicle Chams", "Enable for highlighted vehicles.", &bVehicleChams);
	MenuBase.AddBool("Draw Unused Vehicles", "Draws boxes around empty vehicles.", &bDrawUnusedVehicles);

	EntityESPMenu = MenuBase.CreateSubMenu("Entity");
	MenuBase.AddBool("Draw Pickups", "Draws any weapons that are on the ground.", &bDrawPickups);
	MenuBase.AddBool("Draw Supply Crates", "Draws medkits and ammoboxes.", &bDrawSupply);
	MenuBase.AddBool("Draw Explosives", "Draws claymores/c4/anti-tank.", &bDrawExplosive);
	MenuBase.AddBool("Draw Grenade", "Draws Grenades.", &bDrawGrenade);
}
