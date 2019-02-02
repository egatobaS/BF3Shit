#include "main.h"

bool ShouldSetIni = false;
bool RunThread = true;

void MainThread()
{
	if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
		printf("Could not create symbolic link!\n");
	}

	LoadINI();

	AddMenuOptions();

	while (RunThread)
	{
		if (ATG::g_pd3dDevice && !IsFontInit)
		{
			InitFont();
		}

		if (ShouldSetIni)
		{
			SetInit();
			ShouldSetIni = false;
		}
		Sleep(10);
	}

	printf("Thread Exited\n");
}


//void WriteUInt32(int Address, int Data)
//{
//	*(int*)(Address) = Data;
//
//}
//
//void WriteByte(int Address, int Data)
//{
//	*(unsigned char*)(Address) = Data;
//}
//
//void Nit()
//{
//	WriteByte(0x8406041F, 0x0);//store byte before txt for proper formatting
//	WriteUInt32(0x835F48BC, 0x39000000);//force server id
//	WriteUInt32(0x835F48C8, 0x38E0FFFF);//force all mask
//	WriteUInt32(0x835F48D0, 0x38C00004);//for all chatchannel
//	WriteUInt32(0x835F48D8, 0x38A00000);//Set is dead byte to 0
//											 //Jtag.WriteUInt32(0x835F48B4, 0x7CC43378);//fix string into r4
//											 //Jtag.WriteUInt32(0x835F488C, 0x7CDE3378 );//move string ptr to correct register (r6 to r30)
//	WriteUInt32(0x835F48B0, 0x7FC4F378);//mr %r4, %r30
//	WriteUInt32(0x835F48B4, 0x60000000);//nop next
//
//	byte[] zeroabyte = new byte[200];
//	WriteByte(0x84060420, zeroabyte);
//
//	//Save registers
//	WriteUInt32(0x840602D0, 0x7D8802A6);//mflr r12
//	WriteUInt32(0x840602D4, 0x60000000);//nop
//	WriteUInt32(0x840602D8, 0x9421FE50);//stwu %r1, -0x1B0(%r1)
//	WriteUInt32(0x840602DC, 0x60000000);//nop
//	WriteUInt32(0x840602E0, 0x60000000);//nop
//	WriteUInt32(0x840602E4, 0x60000000);//nop
//	WriteUInt32(0x840602E8, 0x60000000);//nop
//	WriteUInt32(0x840602EC, 0x60000000);//nop
//	WriteUInt32(0x840602F0, 0x60000000);//nop
//	WriteUInt32(0x840602F4, 0x60000000);//nop
//	WriteUInt32(0x840602F8, 0xD0210000);// stfs %r1, 0x00(%r1)
//	WriteUInt32(0x840602FC, 0x90610004);// stw %r3, 0x04(%r1)
//	WriteUInt32(0x84060300, 0x90810008);// stw %r4, 0x08(%r1)
//	WriteUInt32(0x84060304, 0x90A1000C);// stw %r5, 0x0C(%r1) 
//	WriteUInt32(0x84060308, 0x90C10010);// stw %r6, 0x10(%r1)
//	WriteUInt32(0x8406030C, 0x90E10014);// stw %r7, 0x14(%r1)
//	WriteUInt32(0x84060310, 0x91010018);// stw %r8, 0x18(%r1) 
//	WriteUInt32(0x84060314, 0x9121001C);// stw %r9, 0x1C(%r1)
//	WriteUInt32(0x84060318, 0x91410020);// stw %r10, 0x20(%r1)
//	WriteUInt32(0x8406031C, 0x91810024);//stw %r12, 0x24(%r1)
//										 ///////////////////////////////////////////////////////////////////
//
//										 //First Section
//	WriteUInt32(0x84060320, 0x3C808406);//lis r27 8406 (send chat byte!)
//	WriteUInt32(0x84060324, 0x608403E0);//ori r27 03E0
//	WriteUInt32(0x84060328, 0x88840000);//load chat byte into r4
//	WriteUInt32(0x8406032C, 0x2B040001);//cmp r4 to 1
//	WriteUInt32(0x84060330, 0x409A0068);//bne to end
//	WriteUInt32(0x84060334, 0x39E00000);//li r15 0x00
//	WriteUInt32(0x84060338, 0x3C808406);//lis r4 8406  0x840603E0 is chatbyte
//	WriteUInt32(0x8406033C, 0x608403E0);//ori r4 03E0
//	WriteUInt32(0x84060340, 0x99E40000);// stb r15 r4(r4 is send chat byte)//Clear chat byte
//	WriteUInt32(0x84060344, 0x3C808406);//lis %r4, 0x8406
//	WriteUInt32(0x84060348, 0x6084041F);//ori %r4, %r4, 0x0420(R4 = String PTR)
//	WriteUInt32(0x8406034C, 0x38610050);//addi %r3,%r1, 0x50
//	WriteUInt32(0x84060350, 0x4B594529);//branch to first chat func--0x835F4878
//	WriteUInt32(0x84060354, 0x7C641B78);//mov r3(Stack) to r4 for next call
//
//										 //Second Section
//	WriteUInt32(0x84060358, 0x3C608412);// lis %r3, 0x8412
//	WriteUInt32(0x8406035C, 0x80632028);// lwz %r3  0x2028(Context)
//	WriteUInt32(0x84060360, 0x2B030000);//cmp chatmanager ptr to 0x00000000
//	WriteUInt32(0x84060364, 0x419A0034);//beq
//	WriteUInt32(0x84060368, 0x80630034);//lwz %r3, 0x34(%r3)
//	WriteUInt32(0x8406036C, 0x2B030000);//cmp chatmanager ptr to 0x00000000
//	WriteUInt32(0x84060370, 0x419A0028);//beq
//	WriteUInt32(0x84060374, 0x80630018);//lwz %r3, 0x18(%r3)
//	WriteUInt32(0x84060378, 0x2B030000);//cmp chatmanager ptr to 0x00000000
//	WriteUInt32(0x8406037C, 0x419A001C);//beq
//	WriteUInt32(0x84060380, 0x80632E2C);//lwz %r3, 0x2E2C(%r3)
//	WriteUInt32(0x84060384, 0x2B030000);//cmp chatmanager ptr to 0x00000000
//	WriteUInt32(0x84060388, 0x419A0010);//beq
//	WriteUInt32(0x8406038C, 0x3BC30010);//addi  %r30, %r3, 0x10
//	WriteUInt32(0x84060390, 0x7C7F1B78);//mr %r31,  %r3
//	WriteUInt32(0x84060394, 0x4BCB2E3D);//bl  to second chat func--83D131D0
//
//	WriteUInt32(0x84060398, 0x60000000);//nop
//	WriteUInt32(0x8406039C, 0xC0210000);//lfs %r1, 0x00(%r1)
//	WriteUInt32(0x840603A0, 0x80610004);//lwz %r3, 0x04(%r1)
//	WriteUInt32(0x840603A4, 0x80810008);//lwz %r4, 0x08(%r1)
//	WriteUInt32(0x840603A8, 0x80A1000C);//lwz %r5, 0x0C(%r1)
//	WriteUInt32(0x840603AC, 0x80C10010);//lwz %r6, 0x10(%r1)
//	WriteUInt32(0x840603B0, 0x80E10014);//lwz %r7, 0x14(%r1)
//	WriteUInt32(0x840603B4, 0x81010018);//lwz %r8, 0x18(%r1)
//	WriteUInt32(0x840603B8, 0x8121001C);//lwz %r9, 0x1C(%r1)
//	WriteUInt32(0x840603BC, 0x81410020);//lwz %r10,0x20(%r1)
//	WriteUInt32(0x840603C0, 0x81810024);//lwz %r12,0x24(%r1)
//	WriteUInt32(0x840603C4, 0x382101B0);//addi  %r1, %r1, 0x1B0
//	WriteUInt32(0x840603C8, 0x7D8803A6);//nop
//	WriteUInt32(0x840603CC, 0x3D408414);//do orig  r10, ((dword_84139420+0x10000)@h)
//	WriteUInt32(0x840603D0, 0x4E800020);//blr
//
//	Jtag.WriteUInt32(0x834F63E0, 0x48B69EF1);//initial branch
//}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		ATG::g_pd3dDevice = NULL;

		RayCastingOriginal = (RayCasting_t)RayCastingDetour.HookFunction(0x83116A38, (unsigned int)RayCastingHook);
		TransmitPacketOriginal = (TransmitPacketStub)TransmitPacketDetour.HookFunction(0x83CFFAA0, (DWORD)TransmitPacketHook);
		D3DDevice_PresentOriginal = (D3DDevice_Present_t)D3DDevice_PresentDetour.HookFunction(0x8315F850, (unsigned int)D3DDevice_PresentHook);
		XamInputGetStateDetour.HookFunction(GetAddr(0x82D80000, 0x191), (unsigned int)XamInputGetStateHook);
		AddMoveOriginal = (AddMoveStub)AddMoveHook.HookFunction(0x83D00B58, (DWORD)AddMove);

		CreateSystemThread(MainThread, NULL);


	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RunThread = false;

		TransmitPacketDetour.RestoreFunction();
		RayCastingDetour.RestoreFunction();
		XamInputGetStateDetour.RestoreFunction();
		D3DDevice_PresentDetour.RestoreFunction();
		AddMoveHook.RestoreFunction();

		Sleep(500);
	}
	return TRUE;
}

