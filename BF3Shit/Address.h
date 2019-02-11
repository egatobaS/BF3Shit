#pragma once

#define DEVKIT 1
class Detour;

extern Detour* (*GetDetour)();
extern void(*XNotify)(wchar_t*);
extern void*(*user_memcpy)(void*, void*, size_t);
extern char*(*user_strcpy)(char*, const char*);
extern void*(*user_memset)(void*, int, size_t);
extern int(*user_strcmp)(const char*, const char*);
extern void*(*xbOHookFunction)(Detour* a, void* b, void* c);

extern float(*GetDistance)(Vector3 c1, Vector3 c2);
extern float(*VectorLength2D)(Vector3* pV);
extern void(*CreateSystemThread)(void* Function, void* Param);
extern bool(*MmIsAddressValidPtr)(void * ptr);
extern int(*GetAsyncKeyState)(DWORD KEY);
extern bool(*CWriteFile)(const char* FilePath, const void* Data, unsigned int Size);
extern BOOL(*FileExists)(LPCSTR lpFileName);
extern int(*sendSpottingMessage)(ClientSpottingComponent* thisClientSpottingComponent, ClientPlayer* MyClientPlayer, eastl::fixed_vector<DWORD *, 8, 0> *controllablesToSpot, int type);
extern int(*GetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer*);
extern int(*AddDamageData)(ClientConnection*, ClientDamageStream::DamageData*);
extern int(*sub_835F4878)(unsigned char* r3, unsigned char* r4);
extern int(*sub_83D131D0)(unsigned char* r3, unsigned char* r4);
extern int(*GetAmmoPtr)(int x, int y, int z);
extern int(*CCMessage)(ClientConnection*, Message*);
extern int(*ReloadMessageFunction)(int r3, int r4, int r5);

struct SYS_FUNCTION_ADDRESS
{
	void* HookFunction;
	void* XNotify;
	void* memcpy;
	void* memset;
	void* strcpy;
	void* memcmp;
	void* strcmp;
	void* Sleep;
	void* MmIsAddressValid;
	void* FIsMmIoAddress;
	void* GetDetours;
};


struct GAME_ADDRESSES_BF3
{
	int _0x834162D8;
	int _0x83CFF480;
	int _0x834F63C8;
	int _0x83C44E30;
	int _0x83CFFAA0;
	int _0x8315F850;
	int _0x82D80000;
	int _0x191;
	int _0x83D00B58;
	int _0x83266AC0;
	int _0x831FAD00;
	int _0x834CC888;
	int _0x831FB1D8;
	int _0x83212338;
	int _0xDB0;
	int _0x836F4390;
	int _0x841289FC;
	int _0x8420E38C;
	int _0x835F4878;
	int _0x83D131D0;
	int _0x836D01E4;
	int _0x836FDAC8;
	int _0x834FC41C;
	int _0x834FB424;
	int _0x834FB3D0;
	int _0x83504BBC;
	int _0x835054C0;
	int _0x83505268;
	int _0x835054FC;
	int _0x8350498C;
	int _0x83504990;
	int _0x83504994;
	int _0x836bbf98;
	int _0x38600001;
	int _0x39600001;
	int _0x42400020;
	int _0x60000000;
	int _0x4800003C;
	int _0x917F02A4;
	int _0x38600000;
	int _0x39600000;
	int _0x4240004C;
	int _0x419A0B38;
	int _0x409A0DA4;
	int _0x419A003C;
	int _0x89590035;
	int _0x2B0A0000;
	int _0x419A01AC;
	int _0x4E800421;
	int _0x840603E0;
	int _0x84122028;
	int _0x835F48BC;
	int _0x835F48C8;
	int _0x835F48D0;
	int _0x835F48D8;
	int _0x835F48B0;
	int _0x835F48B4;
	int _0x39000000;
	int _0x38E0FFFF;
	int _0x38C00004;
	int _0x38A00000;
	int _0x7FC4F378;
	int _0x8406041F;
	int _0x8340E610;

#if defined(DEVKIT)

	void SetAddress()
	{
		_0x834162D8 = 0x834162D8;
		_0x83CFF480 = 0x83CFF480;
		_0x834F63C8 = 0x834F63C8;
		_0x83C44E30 = 0x83C44E30;
		_0x83CFFAA0 = 0x83CFFAA0;
		_0x8315F850 = 0x8315F850;
		_0x82D80000 = 0x82D80000;
		_0x191 = 0x191; ;
		_0x83D00B58 = 0x83D00B58;
		_0x83266AC0 = 0x83266AC0;
		_0x831FAD00 = 0x831FAD00;
		_0x834CC888 = 0x834CC888;
		_0x831FB1D8 = 0x831FB1D8;
		_0x83212338 = 0x83212338;
		_0xDB0 = 0xDB0; ;
		_0x836F4390 = 0x836F4390;
		_0x841289FC = 0x841289FC;
		_0x8420E38C = 0x8420E38C;
		_0x835F4878 = 0x835F4878;
		_0x83D131D0 = 0x83D131D0;
		_0x836D01E4 = 0x836D01E4;
		_0x836FDAC8 = 0x836FDAC8;
		_0x834FC41C = 0x834FC41C;
		_0x834FB424 = 0x834FB424;
		_0x834FB3D0 = 0x834FB3D0;
		_0x83504BBC = 0x83504BBC;
		_0x835054C0 = 0x835054C0;
		_0x83505268 = 0x83505268;
		_0x835054FC = 0x835054FC;
		_0x8350498C = 0x8350498C;
		_0x83504990 = 0x83504990;
		_0x83504994 = 0x83504994;
		_0x836bbf98 = 0x836bbf98;
		_0x38600001 = 0x38600001;
		_0x39600001 = 0x39600001;
		_0x42400020 = 0x42400020;
		_0x60000000 = 0x60000000;
		_0x4800003C = 0x4800003C;
		_0x917F02A4 = 0x917F02A4;
		_0x38600000 = 0x38600000;
		_0x39600000 = 0x39600000;
		_0x4240004C = 0x4240004C;
		_0x419A0B38 = 0x419A0B38;
		_0x409A0DA4 = 0x409A0DA4;
		_0x419A003C = 0x419A003C;
		_0x89590035 = 0x89590035;
		_0x2B0A0000 = 0x2B0A0000;
		_0x419A01AC = 0x419A01AC;
		_0x4E800421 = 0x4E800421;
		_0x840603E0 = 0x840603E0;
		_0x84122028 = 0x84122028;
		_0x835F48BC = 0x835F48BC;
		_0x835F48C8 = 0x835F48C8;
		_0x835F48D0 = 0x835F48D0;
		_0x835F48D8 = 0x835F48D8;
		_0x835F48B0 = 0x835F48B0;
		_0x835F48B4 = 0x835F48B4;
		_0x39000000 = 0x39000000;
		_0x38E0FFFF = 0x38E0FFFF;
		_0x38C00004 = 0x38C00004;
		_0x38A00000 = 0x38A00000;
		_0x7FC4F378 = 0x7FC4F378;
		_0x8406041F = 0x8406041F;
		_0x8340E610 = 0x8340E610;
	}

#endif
};

extern GAME_ADDRESSES_BF3* Addresses;

struct GAME_ADDRESS_TRANSFER_BF3
{
	GAME_ADDRESSES_BF3* Addresses;

	void* GetDistance;
	void* VectorLength2D;
	void* CreateSystemThread;
	void* MmIsAddressValidPtr;
	void* GetAsyncKeyState;
	void* CWriteFile;
	void* FileExists;

	void* sendSpottingMessage;
	void* GetPlayerScore;
	void* AddDamageData;
	void* sub_835F4878;
	void* sub_83D131D0;
	void* GetAmmoPtr;
	void* CCMessage;
	void* ReloadMessageFunction;

};

void LoadAddresses();