#pragma once

extern UIRender Drawing;

typedef int(*TransmitPacketStub)(int lol, int r4, int r5);
extern TransmitPacketStub TransmitPacketOriginal;

typedef int(*ClientConnection_SendMessage_t)(ClientConnection* Connection, _NetworkableMessage* Message);
extern ClientConnection_SendMessage_t ClientConnection_SendMessageOriginal;

typedef int(*ClientConnection_SendMessage_t)(ClientConnection* Connection, _NetworkableMessage* Message);
extern ClientConnection_SendMessage_t ClientConnection_SendMessageOriginal;

typedef int(*createScoringMessageStub)(int r3, int messageData, UINetworkHudScoringMessage *message);
extern createScoringMessageStub createScoringMessageOriginal;

typedef int(*TransmitPacketStub)(int lol, int r4, int r5);
extern TransmitPacketStub TransmitPacketOriginal;

typedef int(*sub_83CFF480_t)(unsigned long long r3, unsigned long long r4);
extern sub_83CFF480_t sub_83CFF480Original;

typedef int(*onPostPhysicsUpdateSync_t)(ClientSpottingComponent* Component, ClientPlayer* LocalClientPlayer);
extern onPostPhysicsUpdateSync_t onPostPhysicsUpdateSyncOriginal;

typedef int(*RayCasting_t)(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
extern RayCasting_t RayCastingOriginal;

typedef int(*D3DDevice_Present_t)(D3DDevice *pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);
extern D3DDevice_Present_t D3DDevice_PresentOriginal;

typedef int(*AddMoveStub)(StreamManagerMoveClient* r3, IMoveObject* r4);
extern AddMoveStub AddMoveOriginal;

typedef int(*sub_834F63C8_t)(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
extern sub_834F63C8_t sub_834F63C8Original;

typedef int(*GetDispersionStub)(WeaponSway* r3, LinearTransform* swayTransform, bool scaletransform);
extern GetDispersionStub GetDispersionOriginal;

extern Detour* XamInputGetStateDetour, *D3DDevice_PresentDetour, *RayCastingDetour, *AddMoveHook, *sub_834F63C8Detour,
*XamUserGetXUIDDetour, *XamUserGetSigninInfoDetour, *XamUserGetNameDetour, *TransmitPacketDetour, *sub_83CFF480Detour, *ClientConnection_SendMessageDetour, *onPostPhysicsUpdateSyncDetour, *GetDispersionDetour, *createScoringMessageDetour;

DWORD XamUserGetXUIDHook(DWORD dwUserIndex, LPSTR pUserName, PXUID onlineOut);
DWORD XamUserGetSigninInfoHook(DWORD userIndex, DWORD flags, PXUSER_SIGNIN_INFO pSigninInfo);
DWORD XamUserGetNameHook(DWORD dwUserIndex, LPSTR pUserName, DWORD cchUserName);

int sub_83CFF480Hook(unsigned long long r3, unsigned long long r4);
int ClientConnection_SendMessageHook(ClientConnection * Connection, _NetworkableMessage * Message);
void onPostPhysicsUpdateSyncHook(ClientSpottingComponent * Component, ClientPlayer * LocalClientPlayer);
int sub_834F63C8Hook(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
int RayCastingHook(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6, UINT64 r7, UINT64 r8, UINT64 r9, UINT64 r10, float f1, float f2, float f3);
int AddMove(StreamManagerMoveClient * r3, IMoveObject * pMove);
int createScoringMessagehk(int r3, int messageData, UINetworkHudScoringMessage * message);
int GetDispersionHook(WeaponSway * r3, LinearTransform * swayTransform, bool scaletransform);
int TransmitPacketHook(StreamManagerMoveClient* lol, int r4, int r5);
int D3DDevice_PresentHook(D3DDevice* pDevice, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7);