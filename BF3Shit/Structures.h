#pragma once

typedef struct Vector2
{
	float x, y;
	Vector2() : x(0), y(0) { }
	Vector2(float X, float Y) : x(X), y(Y) { }

}Vector2, *PVector2;



typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator* (const float mul)
	{
		return Vector3(this->x *= mul, this->y *= mul, this->z *= mul);
	}

	const bool operator != (Vector3 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	float Distance(Vector3 const &Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z); }

	inline Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	const Vector3 &RoundHalfUpF()
	{
		return Vector3((float)floor(this->x + 0.5), (float)floor(this->y + 0.5), (float)floor(this->z + 0.5));
	}\
		const Vector3 &RoundHalfDown()
	{
		return Vector3((float)floor(this->x + 0.5), (float)floor(this->y + 0.5), (float)floor(this->z + 0.5));
	}
} Vector3, *PVector3;

typedef struct Vector4
{
	float x, y, z, a;
	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

} Vector4, *PVector4;

struct MatrixCoords
{
	/*
	float TL_X; //0x70
	float TL_Y; //0x74
	float TL_Z; //0x78
	*/
	Vector3 TL;

	/*
	float TR_X; //0x7C
	float TR_Y; //0x80
	float TR_Z; //0x84
	*/
	Vector3 TR;

	/*
	float BR_X; //0x88
	float BR_Y; //0x8C
	float BR_Z; //0x90
	*/
	Vector3 BR;

	/*
	float BL_X; //0x94
	float BL_Y; //0x98
	float BL_Z; //0x9C
	*/
	Vector3 BL;
};

typedef struct
{
	float r, g, b, a;
} Color;

typedef struct
{
	float height, width, intensity;
} Dimensions;

typedef struct
{
	char padding00[0x38];
	float unk0;

	float blur;

	float Glow_R;
	float Glow_G;
	float Glow_B;

	float unk1;

	float Glow_A;

	char padding01[0x38];

	float Scale; // 0x8C

	float Color_R;
	float Color_G;
	float Color_B;

	float unk3;

	float Color_A;
}_TextStyle;


typedef struct
{
	char padding00[0x3C];

	float Scale;

	float Color_R;
	float Color_G;
	float Color_B;

	float unk3;

	float Color_A;

	char pad_0x54[0xc];

	float m_LetterSpacing;
	float m_RowSpacing;

	char pad_0x064[0x20];

	float x;
	float y;

	float Glow_R;
	float Glow_G;
	float Glow_B;

	float unk1;

	float Glow_A;

	char pad_0xa8[0xc];

	float glow_Intensity;
}TextStyle;

struct MatrixD : public XMFLOAT4X4
{
	MatrixD() : XMFLOAT4X4(1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f) {}
	MatrixD(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) : XMFLOAT4X4(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33) {}
	explicit MatrixD(const Vector3& r0, const Vector3& r1, const Vector3& r2) : XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
		r1.x, r1.y, r1.z, 0,
		r2.x, r2.y, r2.z, 0,
		0, 0, 0, 1.f) {}
	explicit MatrixD(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3) : XMFLOAT4X4(r0.x, r0.y, r0.z, r0.a,
		r1.x, r1.y, r1.z, r1.a,
		r2.x, r2.y, r2.z, r2.a,
		r3.x, r3.y, r3.z, r3.a) {}
	MatrixD(const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
	MatrixD(const XMFLOAT3X3& M);
	MatrixD(const XMFLOAT4X3& M);


	operator XMMATRIX() const { return XMLoadFloat4x4(this); }

	// Comparison operators
	bool operator == (const MatrixD& M) const;
	bool operator != (const MatrixD& M) const;

	// Assignment operators
	MatrixD& operator= (const MatrixD& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(float) * 16); return *this; }
	MatrixD& operator= (const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); return *this; }
	MatrixD& operator= (const XMFLOAT3X3& M);
	MatrixD& operator= (const XMFLOAT4X3& M);
	MatrixD& operator+= (const MatrixD& M);
	MatrixD& operator-= (const MatrixD& M);
	MatrixD& operator*= (const MatrixD& M);
	MatrixD& operator*= (float S);
	MatrixD& operator/= (float S);

	MatrixD& operator/= (const MatrixD& M);
	// Element-wise divide

	// Unary operators
	MatrixD operator+ () const { return *this; }
	MatrixD operator- () const;

	// Properties
	Vector3 Up() const { return Vector3(_21, _22, _23); }
	void Up(const Vector3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

	Vector3 Down() const { return Vector3(-_21, -_22, -_23); }
	void Down(const Vector3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

	Vector3 Right() const { return Vector3(_11, _12, _13); }
	void Right(const Vector3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

	Vector3 Left() const { return Vector3(-_11, -_12, -_13); }
	void Left(const Vector3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

	Vector3 Forward() const { return Vector3(-_31, -_32, -_33); }
	void Forward(const Vector3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

	Vector3 Backward() const { return Vector3(_31, _32, _33); }
	void Backward(const Vector3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

	Vector3 Translation() const { return Vector3(_41, _42, _43); }
	void Translation(const Vector3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }

};

class Matrix
{
public:
	float m[4][4];

	Matrix()
	{
		m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
	}

	float operator() (const int r, const int c)
	{
		return m[r][c];
	}
};

typedef enum
{
	ENTITY_CLIENT_WEAPON = 0x0E6,
	ENTITY_CLIENT_BULLET = 0x0FC,
	ENTITY_CLIENT_MISSILE = 0x0F5,
	ENTITY_CLIENT_EXPLOSIVE = 0x0F8,
	ENTITY_CLIENT_VEHICLE = 0x104,
	ENTITY_CLIENT_SOLDIER = 0x106,
	ENTITY_CLIENT_SUPPLYBOX = 0x0F9,
	ENTITY_CLIENT_PICKUP = 0x10D,


	ENTITY_CLIENT_GRENADE = 246

} EntityID;

template< class T > class WeakPtr
{
public:
	T * * m_ptr;

public:
	T * GetData()
	{
		if (!m_ptr)
			return NULL;

		if (!*m_ptr)
			return NULL;

		T* ptr = *m_ptr;

		return (T*)((intptr_t)ptr - sizeof(intptr_t));
	}
};

namespace fb
{
	template <class T>
	class RelocArray
	{
	private:
		int m_count; //0x0
#pragma pack(push,4)
		T* m_data; //0x4
#pragma pack(pop)

	public:
		int Size() { return m_count; }
		T At(INT index) { return *(T*)((intptr_t)m_data + (index * sizeof(T))); }
		T operator[](INT index) { return At(index); }
	};

	template <typename T> class Array
	{
	private:
		T * m_firstElement;

	public:
		T At(INT nIndex)
		{
			if (m_firstElement == NULL)
				return NULL;

			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}

		__int32 size()
		{
			intptr_t p = ((intptr_t)m_firstElement - sizeof(intptr_t));
			return *(__int32*)((intptr_t)p + 0x4);
		}

		T operator [](INT index)
		{
			return At(index);
		}
	};
}
class ClientSpottingComponent;
class ClientScoreManager;
class FixWeaponModifier;
class IMoveObject;
class EntryInputState;
class EntryInputStateNetworkMove;
class Color32;
class UIHud;
class ClientMovementComponent;
class ClientActiveWeaponHandler;
class OnlineManager;
class WeaponZeroingEntry;
class ZeroingModifier;
class QuatTransform;
class DynamicPhysicsEntity;
class ShotConfigData;
class WeaponFiring;
class UpdatePoseResultData;
class VaultComponentData;
class LevelData;
class ClientVaultComponent;
class Keyboard;
class KeyboardDevice;
class Mouse;
class MouseDevice;
class DifficultyData;
class ClientPlayerScore;
class DifficultyDatas;
class GameSettings;
class VersionData;
class ClientAnimatedSoldierWeaponHandler;
class ClientAntAnimatableComponent;
class ClientSoldierEntity;
class SomeScoreManagerClass;
class ClientPlayerScoreManager;
class ClientSoldierPrediction;
class TypeInfo;
class TypeInfoObject;
class ClientSoldierWeaponsComponent;
class ClientRagDollComponent;
class WeaponModifier;
class ClientControllableEntity;
class SoldierAimingSimulation;
class ArrayTypeInfo;
class AntRef;
class JumpingClass;
class UnlockAssetBase;
class GameObject;
class ClientPeer;
class wf48;
class MaterialGridManager;
class SprintInputHandler;
class SkeletonCollisionData;
class ClientPlayerManager;
class MemberInfoData;
class ClientCharacterEntity;
class BoneCollisionComponent;
class BoneCollisionComponentData;
class SkeletonAsset;
struct BoneCollisionData;
struct PitchModifier;
class SoldierAimingSimulationData;
class BluePrintName;
class SomePickUpClass;
class ClientPickupEntity;
class TypeInfoObject;
class TypeInfo;
class MemberInfoData;
class WeaponInfo;
class MemberInfoFlags;
class ClientConnection;
class ClientDamageStream;
class DamageData;
class PickupEntityData;
class ClientSpottingTargetComponent;
class WeaponSway;
class BorderInputNode;
class ClientPlayer;
class ShotStats;
class VehicleEntityData;
class Components;
class Temp;
class GameTime;
class LinearTransform;
class BulletHitInfo;
class MeshAsset;
class WeaponComponentData;
class EntityData;
class WeaponEntityData;
class ClientSoldierWeapon;
class EntryComponent;
class ClientPlayerView;
class FiringFunctionData;
class FireLogicData;
class ExtendableWideStringBuilder;
class Entity;
class EntityCreator;
class EntityCollectionSegment;
class ITypedObject;
class DataContainer;
class Asset;
class PropertyConnection;
class LinkConnection;
class SubLevel;
class ResourceManager;
class ExplosiveData;
class LinearTransform;
class Compartment;
template <typename T> class Array;
class DefibrillatorWeaponData;
class ClientParachuteComponent;
class SoldierEntityData;
class IPhysicsRayCaster;
class ClientWeaponComponent;
class TypeInfo;
class ClientExplosionPackEntity;
class Level;
class ClientGameWorld;
class PickupData;
class HavokPhysicsManager;
class GameWorld;
class IMouse;
class MouseInputBuffer;
class PhysicsEntityTransform;
class AxisAlignedBox;
struct TransformAABBStruct;
class HavokPhysicsData;
class LoadedData;
class PlayerEntryComponentData;
class ClientPlayerEntryComponent;
class NetworkableMessage;
class Message;
class Unknown01;
class GFxDrawText;
class GColor;
class GFxDrawTextManager;
class GFxDrawTextManagerImpl;
class ChatMessage;
class StreamManagerChat;

class Unknown01
{
public:
	char pad_0000[0x3C]; //0x0000
	bool  cullBool; //0x3C
};

class timer_s {
	int interval;
	int end_time;
	bool repeat;
	bool finished;
public:
	timer_s(int interval, bool repeat);
	bool done();
};

class TypeInfoObject
{
public:
	virtual TypeInfo* GetType();
};

enum InputConceptIdentifiers
{
	ConceptMoveFB, //0x0000
	ConceptMoveLR, //0x0001
	ConceptMoveForward, //0x0002
	ConceptMoveBackward, //0x0003
	ConceptMoveLeft, //0x0004
	ConceptMoveRight, //0x0005
	ConceptYaw, //0x0006
	ConceptPitch, //0x0007
	ConceptRoll, //0x0008
	ConceptRecenterCamera, //0x0009
	ConceptFire, //0x000A
	ConceptAltFire, //0x000B
	ConceptFireCountermeasure, //0x000C
	ConceptReload, //0x000D
	ConceptZoom, //0x000E
	ConceptToggleCamera, //0x000F
	ConceptSprint, //0x0010
	ConceptCrawl, //0x0011
	ConceptToggleWeaponLight, //0x0012
	ConceptSelectPartyMember0, //0x0013
	ConceptSelectPartyMember1, //0x0014
	ConceptSelectPartyMember2, //0x0015
	ConceptSelectPartyMember3, //0x0016
	ConceptLockTarget, //0x0017
	ConceptCrosshairMoveX, //0x0018
	ConceptCrosshairMoveY, //0x0019
	ConceptTacticalMenu, //0x001A
	ConceptConversationSelect, //0x001B
	ConceptConversationSkip, //0x001C
	ConceptConversationChangeSelection, //0x001D
	ConceptJump, //0x001E
	ConceptCrouch, //0x001F
	ConceptCrouchOnHold, //0x0020
	ConceptProne, //0x0021
	ConceptInteract, //0x0022
	ConceptPickUp, //0x0023
	ConceptDrop, //0x0024
	ConceptBreathControl, //0x0025
	ConceptParachute, //0x0026
	ConceptSwitchInventoryItem, //0x0027
	ConceptSelectInventoryItem1, //0x0028
	ConceptSelectInventoryItem2, //0x0029
	ConceptSelectInventoryItem3, //0x002A
	ConceptSelectInventoryItem4, //0x002B
	ConceptSelectInventoryItem5, //0x002C
	ConceptSelectInventoryItem6, //0x002D
	ConceptSelectInventoryItem7, //0x002E
	ConceptSelectInventoryItem8, //0x002F
	ConceptSelectInventoryItem9, //0x0030
	ConceptSwitchToPrimaryWeapon, //0x0031
	ConceptSwitchToGrenadeLauncher, //0x0032
	ConceptSwitchToStaticGadget, //0x0033
	ConceptSwitchToDynamicGadget1, //0x0034
	ConceptSwitchToDynamicGadget2, //0x0035
	ConceptMeleeAttack, //0x0036
	ConceptThrowGrenade, //0x0037
	ConceptCycleFireMode, //0x0038
	ConceptChangeVehicle, //0x0039
	ConceptBrake, //0x003A
	ConceptHandBrake, //0x003B
	ConceptClutch, //0x003C
	ConceptGearUp, //0x003D
	ConceptGearDown, //0x003E
	ConceptGearSwitch, //0x003F
	ConceptNextPosition, //0x0040
	ConceptSelectPosition1, //0x0041
	ConceptSelectPosition2, //0x0042
	ConceptSelectPosition3, //0x0043
	ConceptSelectPosition4, //0x0044
	ConceptSelectPosition5, //0x0045
	ConceptSelectPosition6, //0x0046
	ConceptSelectPosition7, //0x0047
	ConceptSelectPosition8, //0x0048
	ConceptCameraPitch, //0x0049
	ConceptCameraYaw, //0x004A
	ConceptMapZoom, //0x004B
	ConceptMapInnerZoom, //0x004C
	ConceptMapSize, //0x004D
	ConceptMapThreeDimensional, //0x004E
	ConceptScoreboard, //0x004F
	ConceptScoreboardAndMenuCombo, //0x0050
	ConceptMenu, //0x0051
	ConceptSpawnMenu, //0x0052
	ConceptCancel, //0x0053
	ConceptCommMenu1, //0x0054
	ConceptCommMenu2, //0x0055
	ConceptCommMenu3, //0x0056
	ConceptAccept, //0x0057
	ConceptDecline, //0x0058
	ConceptSelect, //0x0059
	ConceptBack, //0x005A
	ConceptActivate, //0x005B
	ConceptDeactivate, //0x005C
	ConceptEdit, //0x005D
	ConceptView, //0x005E
	ConceptParentNavigateLeft, //0x005F
	ConceptParentNavigateRight, //0x0060
	ConceptMenuZoomIn, //0x0061
	ConceptMenuZoomOut, //0x0062
	ConceptPanX, //0x0063
	ConceptPanY, //0x0064
	ConceptBattledashToggle, //0x0065
	ConceptVoiceFunction1, //0x0066
	ConceptSquadVoice, //0x0067
	ConceptSayAllChat, //0x0068
	ConceptTeamChat, //0x0069
	ConceptSquadChat, //0x006A
	ConceptSquadLeaderChat, //0x006B
	ConceptToggleChat, //0x006C
	ConceptQuicktimeInteractDrag, //0x006D
	ConceptQuicktimeFire, //0x006E
	ConceptQuicktimeBlock, //0x006F
	ConceptQuicktimeFastMelee, //0x0070
	ConceptQuicktimeJumpClimb, //0x0071
	ConceptQuicktimeCrouchDuck, //0x0072
	ConceptFreeCameraMoveUp, //0x0073
	ConceptFreeCameraMoveDown, //0x0074
	ConceptFreeCameraMoveLR, //0x0075
	ConceptFreeCameraMoveFB, //0x0076
	ConceptFreeCameraMoveUD, //0x0077
	ConceptFreeCameraRotateX, //0x0078
	ConceptFreeCameraRotateY, //0x0079
	ConceptFreeCameraRotateZ, //0x007A
	ConceptFreeCameraIncreaseSpeed, //0x007B
	ConceptFreeCameraDecreaseSpeed, //0x007C
	ConceptFreeCameraFOVModifier, //0x007D
	ConceptFreeCameraChangeFOV, //0x007E
	ConceptFreeCameraSwitchSpeed, //0x007F
	ConceptFreeCameraTurboSpeed, //0x0080
	ConceptFreeCameraActivator1, //0x0081
	ConceptFreeCameraActivator2, //0x0082
	ConceptFreeCameraActivator3, //0x0083
	ConceptFreeCameraMayaInputActivator, //0x0084
	ConceptTargetedCameraDistance, //0x0085
	ConceptTargetedCameraRotateX, //0x0086
	ConceptTargetedCameraRotateY, //0x0087
	ConceptTargetedCameraChangeSpeed, //0x0088
	ConceptLThumb, //0x0089
	ConceptRThumb, //0x008A
	ConceptLeftStickX, //0x008B
	ConceptLeftStickY, //0x008C
	ConceptRightStickX, //0x008D
	ConceptRightStickY, //0x008E
	ConceptButtonDPadLeft, //0x008F
	ConceptButtonDPadRight, //0x0090
	ConceptButtonDPadUp, //0x0091
	ConceptButtonDPadDown, //0x0092
	ConceptButtonA, //0x0093
	ConceptButtonB, //0x0094
	ConceptButtonX, //0x0095
	ConceptButtonY, //0x0096
	ConceptButtonSelect, //0x0097
	ConceptButtonStart, //0x0098
	ConceptButtonL1, //0x0099
	ConceptButtonL2, //0x009A
	ConceptButtonR1, //0x009B
	ConceptButtonR2, //0x009C
	ConceptButtonLeftThumb, //0x009D
	ConceptButtonRightThumb, //0x009E
	ConceptToggleMinimapType, //0x009F
	ConceptDeployZoom, //0x00A0
	ConceptMenuDigitalUp, //0x00A1
	ConceptMenuDigitalDown, //0x00A2
	ConceptMenuDigitalLeft, //0x00A3
	ConceptMenuDigitalRight, //0x00A4
	ConceptRightStickUp, //0x00A5
	ConceptRightStickDown, //0x00A6
	ConceptRightStickLeft, //0x00A7
	ConceptRightStickRight, //0x00A8
	ConceptMultipleSelect, //0x00A9
	ConceptSelectAll, //0x00AA
	ConceptMinimize, //0x00AB
	ConceptMoveCameraUp, //0x00AC
	ConceptMoveCameraDown, //0x00AD
	ConceptMoveCameraLeft, //0x00AE
	ConceptMoveCameraRight, //0x00AF
	ConceptSelectSquad1, //0x00B0
	ConceptSelectSquad2, //0x00B1
	ConceptSelectSquad3, //0x00B2
	ConceptSelectSquad4, //0x00B3
	ConceptSelectSquad5, //0x00B4
	ConceptSelectSquad6, //0x00B5
	ConceptSelectSquad7, //0x00B6
	ConceptSelectSquad8, //0x00B7
	ConceptSelectSquad9, //0x00B8
	ConceptSpectatorViewPrev, //0x00B9
	ConceptSpectatorViewNext, //0x00BA
	ConceptSpectatorTargetPrev, //0x00BB
	ConceptSpectatorTargetNext, //0x00BC
	ConceptSpectatorViewTableTop, //0x00BD
	ConceptSpectatorViewFirstPerson, //0x00BE
	ConceptSpectatorViewThirdPerson, //0x00BF
	ConceptSpectatorViewFreeCam, //0x00C0
	ConceptSpectatorViewPlayer1, //0x00C1
	ConceptSpectatorViewPlayer2, //0x00C2
	ConceptSpectatorViewPlayer3, //0x00C3
	ConceptSpectatorViewPlayer4, //0x00C4
	ConceptSpectatorViewPlayer5, //0x00C5
	ConceptSpectatorViewPlayer6, //0x00C6
	ConceptSpectatorViewPlayer7, //0x00C7
	ConceptSpectatorViewPlayer8, //0x00C8
	ConceptSpectatorViewPlayer9, //0x00C9
	ConceptSpectatorViewPlayer10, //0x00CA
	ConceptSpectatorViewPlayer11, //0x00CB
	ConceptSpectatorViewPlayer12, //0x00CC
	ConceptSpectatorViewPlayer13, //0x00CD
	ConceptSpectatorViewPlayer14, //0x00CE
	ConceptSpectatorViewPlayer15, //0x00CF
	ConceptSpectatorViewPlayer16, //0x00D0
	ConceptSpectatorViewOptions, //0x00D1
	ConceptSpectatorHudVisibility, //0x00D2
	ConceptAnalogZoom, //0x00D3
	ConceptSpectatorTargetPrevInSquad, //0x00D4
	ConceptSpectatorTargetNextInSquad, //0x00D5
	ConceptSpectatorTargetPrevOnTeam, //0x00D6
	ConceptSpectatorTargetNextOnTeam, //0x00D7
	ConceptSpectatorFreeCameraIncreaseSpeed, //0x00D8
	ConceptSpectatorFreeCameraDecreaseSpeed, //0x00D9
	ConceptSpectatorFreeCameraSwitchSpeed, //0x00DA
	ConceptSpectatorFreeCameraMoveLR, //0x00DB
	ConceptSpectatorFreeCameraMoveUD, //0x00DC
	ConceptSpectatorFreeCameraMoveFB, //0x00DD
	ConceptSpectatorFreeCameraRotateX, //0x00DE
	ConceptSpectatorFreeCameraRotateY, //0x00DF
	ConceptSpectatorFreeCameraRotateZ, //0x00E0
	ConceptSpectatorFreeCameraTurboSpeed, //0x00E1
	ConceptSpectatorFreeCameraFOVModifier, //0x00E2
	ConceptSpectatorFreeCameraChangeFOV, //0x00E3
	ConceptSpectatorSquadLeft, //0x00E4
	ConceptSpectatorSquadRight, //0x00E5
	ConceptSpectatorSquadUp, //0x00E6
	ConceptSpectatorSquadDown, //0x00E7
	ConceptSpectatorSquadActivate, //0x00E8
	ConceptUndefined, //0x00E9
	ConceptSize //0x00EA
};
enum InputDeviceMouseButtons
{
	IDB_Button_0 = 0,
	IDB_Button_1 = 1,
	IDB_Button_2 = 2,
	IDB_Button_3 = 3,
	IDB_Button_4 = 4,
	IDB_Button_5 = 5,
	IDB_Button_6 = 6,
	IDB_Button_7 = 7,
	IDB_Button_Undefined = 8
};

enum InputDeviceKeys
{
	IDK_None = 0,
	IDK_Escape = 1,
	IDK_1 = 2,
	IDK_2 = 3,
	IDK_3 = 4,
	IDK_4 = 5,
	IDK_5 = 6,
	IDK_6 = 7,
	IDK_7 = 8,
	IDK_8 = 9,
	IDK_9 = 10,
	IDK_0 = 11,
	IDK_Minus = 12,
	IDK_Equals = 13,
	IDK_Backspace = 14,
	IDK_Tab = 15,
	IDK_Q = 16,
	IDK_W = 17,
	IDK_E = 18,
	IDK_R = 19,
	IDK_T = 20,
	IDK_Y = 21,
	IDK_U = 22,
	IDK_I = 23,
	IDK_O = 24,
	IDK_P = 25,
	IDK_LeftBracket = 26,
	IDK_RightBracket = 27,
	IDK_Enter = 28,
	IDK_LeftCtrl = 29,
	IDK_A = 30,
	IDK_S = 31,
	IDK_D = 32,
	IDK_F = 33,
	IDK_G = 34,
	IDK_H = 35,
	IDK_J = 36,
	IDK_K = 37,
	IDK_L = 38,
	IDK_Semicolon = 39,
	IDK_Apostrophe = 40,
	IDK_Grave = 41,
	IDK_LeftShift = 42,
	IDK_Backslash = 43,
	IDK_Z = 44,
	IDK_X = 45,
	IDK_C = 46,
	IDK_V = 47,
	IDK_B = 48,
	IDK_N = 49,
	IDK_M = 50,
	IDK_Comma = 51,
	IDK_Period = 52,
	IDK_Slash = 53,
	IDK_RightShift = 54,
	IDK_Multiply = 55,
	IDK_LeftAlt = 56,
	IDK_Space = 57,
	IDK_Capital = 58,
	IDK_F1 = 59,
	IDK_F2 = 60,
	IDK_F3 = 61,
	IDK_F4 = 62,
	IDK_F5 = 63,
	IDK_F6 = 64,
	IDK_F7 = 65,
	IDK_F8 = 66,
	IDK_F9 = 67,
	IDK_F10 = 68,
	IDK_Numlock = 69,
	IDK_ScrollLock = 70,
	IDK_Numpad7 = 71,
	IDK_Numpad8 = 72,
	IDK_Numpad9 = 73,
	IDK_Subtract = 74,
	IDK_Numpad4 = 75,
	IDK_Numpad5 = 76,
	IDK_Numpad6 = 77,
	IDK_Add = 78,
	IDK_Numpad1 = 79,
	IDK_Numpad2 = 80,
	IDK_Numpad3 = 81,
	IDK_Numpad0 = 82,
	IDK_Decimal = 83,
	IDK_OEM_102 = 86,
	IDK_F11 = 87,
	IDK_F12 = 88,
	IDK_F13 = 100,
	IDK_F14 = 101,
	IDK_F15 = 102,
	IDK_Kana = 112,
	IDK_PTBRSlash = 115,
	IDK_Convert = 121,
	IDK_NoConvert = 123,
	IDK_Yen = 125,
	IDK_PTBRNUMPADPOINT = 126,
	IDK_NumpadEquals = 141,
	IDK_PrevTrack = 144,
	IDK_At = 145,
	IDK_Colon = 146,
	IDK_Underline = 147,
	IDK_Kanji = 148,
	IDK_Stop = 149,
	IDK_Ax = 150,
	IDK_Unlabeled = 151,
	IDK_NextTrack = 153,
	IDK_NumpadEnter = 156,
	IDK_RightCtrl = 157,
	IDK_Mute = 160,
	IDK_Calculator = 161,
	IDK_PlayPause = 162,
	IDK_MediaStop = 164,
	IDK_VolumeDown = 174,
	IDK_VolumeUp = 176,
	IDK_WebHome = 178,
	IDK_NumpadComma = 179,
	IDK_Divide = 181,
	IDK_PrintScreen = 183,
	IDK_RightAlt = 184,
	IDK_Home = 199,
	IDK_ArrowUp = 200,
	IDK_PageUp = 201,
	IDK_ArrowLeft = 203,
	IDK_ArrowRight = 205,
	IDK_End = 207,
	IDK_ArrowDown = 208,
	IDK_PageDown = 209,
	IDK_Insert = 210,
	IDK_Delete = 211,
	IDK_LeftWin = 219,
	IDK_RightWin = 220,
	IDK_AppMenu = 221,
	IDK_Power = 222,
	IDK_Sleep = 223,
	IDK_Wake = 227,
	IDK_WebSearch = 229,
	IDK_WebFavorites = 230,
	IDK_WebRefresh = 231,
	IDK_WebStop = 232,
	IDK_WebForward = 233,
	IDK_WebBack = 234,
	IDK_MyComputer = 235,
	IDK_Mail = 236,
	IDK_MediaSelect = 237,
	IDK_Pause = 197,
	IDK_Undefined = 255
};

enum OrderType
{
	OrderType_None,
	OrderType_RequestHeal,
	OrderType_LetMeHeal,
	OrderType_RequestAmmo,
	OrderType_LetMeGiveAmmo,
	OrderType_LetMeRepair,
	OrderType_RequestRepair,
	OrderType_RequestRide,
	OrderType_GoGoGo,
	OrderType_FollowMe,
	OrderType_Negative,
	OrderType_Sorry,
	OrderType_ThankYou,
	OrderType_RogerThat,
	OrderType_NeedBackup,
	OrderType_GetIn,
	OrderType_GetOut,
	OrderType_Attack,
	OrderType_RequestSquadOrder,//18
	OrderType_RequestCommanderOrder,
	OrderType_RequestSupply,
	OrderType_RequestVehicle,
	OrderType_RequestScan,
	OrderType_AcceptOrder,
	OrderType_DenyOrder,
	OrderType_RequestComm,
	OrderType_Count,
};

class LinearTransform
{
public:
	union
	{
		struct
		{
			Vector3 left;
			Vector3 up;
			Vector3 forward;
			Vector3 trans;
		};
		struct
		{
			Vector3 m_rows[4];
		};
		FLOAT data[4][4];
	};
	//new from me to calculate matrix
	LinearTransform & operator = (LinearTransform & From)
	{
		this->m_rows[0] = From.m_rows[0];
		this->m_rows[1] = From.m_rows[1];
		this->m_rows[2] = From.m_rows[2];
		this->m_rows[3] = From.m_rows[3];

		return (*this);
	};

	float operator() (const int r, const int c)
	{
		return data[r][c];
	}

	Vector3 one() { return m_rows[0]; }
	Vector3 two() { return m_rows[1]; }
	Vector3 three() { return m_rows[2]; }
	Vector3 four() { return m_rows[3]; }

	//new from me get origin from matrix/lineartransform
	BOOL GetOrigin(Vector3* vOrigin)
	{
		if (vOrigin)
		{
			memcpy_s(vOrigin, sizeof(Vector3), &(this->trans), sizeof(Vector3));
			return TRUE;
		}
		return FALSE;
	};

};

class RenderViewDesc
{
public:
	LinearTransform transform;				// 0x00
	INT type;								// 0x40
	PAD(0x4);								// 0x44
	FLOAT fovY;								// 0x48
	FLOAT defaultFovY;						// 0x4C
	FLOAT nearPlane;						// 0x50
	FLOAT farPlane;							// 0x54
	FLOAT aspect;							// 0x58
	FLOAT orthoWidth;						// 0x5C
	FLOAT orthoHeight;						// 0x60
	FLOAT stereoSeparation;					// 0x64
	FLOAT stereoConvergence;				// 0x68
	Vector2 viewportOffset;					// 0x6C
	Vector2 viewportScale;						// 0x74

};

class RenderView
{
public:
	RenderViewDesc m_desc;							// 0x00
	PAD(0x4);										// 0x7C
	INT m_dirtyFlags;								// 0x80
	PAD(0x16C);										// 0x84
	FLOAT m_fovX;									// 0x1F0
	FLOAT m_depthToWidthRatio;						// 0x1F4
	FLOAT m_fovScale;								// 0x1F8
	FLOAT m_fovScaleSqr;							// 0x1FC
	LinearTransform m_viewMatrix;					// 0x200
	LinearTransform m_viewMatrixTranspose;			// 0x240
	LinearTransform m_viewMatrixInverse;			// 0x280
													//D3DXMATRIX m_viewMatrixInverse;				// 0x280
	LinearTransform m_projectionMatrix;				// 0x2C0
	LinearTransform m_viewMatrixAtOrigin;			// 0x300
	LinearTransform m_projectionMatrixTranspose;	// 0x340
	LinearTransform m_projectionMatrixInverse;		// 0x380
	LinearTransform m_viewProjectionMatrix;			// 0x3C0
	LinearTransform m_viewProjectionMatrixTranspose;// 0x400
	LinearTransform m_viewProjectionMatrixInverse;	// 0x440

public:
	BOOL Update()
	{
		FLOAT screenX = static_cast<FLOAT>(1280);
		FLOAT screenY = static_cast<FLOAT>(720);
		this->m_desc.aspect = screenX / screenY;

		int(*UpdateMatrices)(RenderView*, LPVOID) = (int(*)(RenderView*, LPVOID))0x8316CEE0;
		UpdateMatrices(this, NULL);
		return TRUE;
	}
	BOOL GetOriginFromMatrix(Vector3* vOrigin)
	{
		if (vOrigin)
		{
			memcpy_s(vOrigin, sizeof(Vector3), &(this->m_viewMatrixInverse), sizeof(Vector3));
			return TRUE;
		}
		return FALSE;
	}

};

class GameRenderViewParams
{
public:
	RenderView view;						// 0x00
	RenderView prevView;					// 0x480
	RenderView secondaryStreamingView;		// 0x900
	INT secondaryStreamingViewEnable;		// 0xD80
	PAD(0xC);								// 0xD84
	LinearTransform firstPersonTransform;		// 0xD90
};

class GameRenderer
{
public:
	PAD(0x20);							// 0x08
	GameRenderViewParams m_viewParams;	// 0x50
public:
	static GameRenderer* Singleton()
	{
		DWORD GAMERENDERER = 0x84125D80;
		return *(GameRenderer**)(GAMERENDERER);
	}
};

class AxisAlignedBox
{
public:
	Vector4  min;
	Vector4  max;

	Vector3 GetCenter() const {
		return Vector3(
			(max.x + min.x) * 0.5f,
			(max.y + min.y) * 0.5f,
			(max.z + min.z) * 0.5f);
	}
};

class TeamEntityData
{
public:
	char pad_0000[96]; //0x0000
	class TeamData* m_TeamData; //0x0060
	int m_id; //0x0064
	char pad_0068[28]; //0x0068
}; //Size: 0x0084

class EntryInputState
{
public:
	struct CharacterMeleeIdentifier
	{
		WeakPtr<void*> entity;//fb::Entity
		void *clientGhost;//fb::network::ClientGhost
	};
	struct CharacterCollisionPos
	{
		WeakPtr<void*> entity;//fb::Entity
		void* clientGhost;//fb::network::ClientGhost
		Vector4 pos;
	};

	LPVOID vftable;									// 0x00
	PAD(0xC);										// 0x04
	FLOAT m_analogInput[10];						// 0x10
	FLOAT m_downTimes[100];							// 0x38
	PAD(0x18);										// 0x1C8
	long long m_DigitalBitFlags; //0x01E0
	int m_CustomBitFlags; //0x01E8
	float m_DeltaTime; //0x01EC
	float m_TimeBehind; //0x01F0
	Vector2 m_WeaponAngles; //0x01F4
	float m_AuthoritiveMovementPenalty; //0x01FC
	Vector4 m_authoritativeCameraPosition;
	Vector4 m_authoritativeMovementPosition;
	Vector4 m_authoritativeMovementVelocity;
	char pad22[0xA8];
	unsigned int m_zoomLevel;
	unsigned int m_ticks;
	unsigned int m_controllableId;
	unsigned int m_entryId;
	unsigned int m_networkSequenceNumber;
	int m_rawDigital[18];
	Vector2 m_rawLeftStick;
	Vector2 m_rawRightStick;
	float m_rawLeftTrigger;
	float m_rawRightTrigger;
	unsigned int m_clientCameraOrientation;
	unsigned __int32 m_isLastTickInFrame : 1;
	unsigned __int32 m_hasClientCameraOrientation : 1;
	unsigned __int32 m_previousAuthoritativeMovementActive : 1;


};

class WorldRenderSettings
{
public:


	static WorldRenderSettings* GetInstance()
	{
		//return *(WorldRenderSettings**)OFFSET_WORLDRENDERSETTINGS;
	}

public:
	char _0x0000[16];
	float m_dynamicEnvmapDefaultPosition_0; //0x0010 
	float m_dynamicEnvmapDefaultPosition_1; //0x0014 
	float m_dynamicEnvmapDefaultPosition_2; //0x0018 
	float m_dynamicEnvmapDefaultPosition_3; //0x001C 
	float m_subSurfaceColor_0; //0x0020 
	float m_subSurfaceColor_1; //0x0024 
	float m_subSurfaceColor_2; //0x0028 
	float m_subSurfaceColor_3; //0x002C 
	float m_viewportScale; //0x0030 
	float m_shadowMinScreenArea; //0x0034 
	float m_shadowViewportScale; //0x0038 
	DWORD m_fxaaQuality; //0x003C 
	float m_cullScreenAreaScale; //0x0040 
	float m_planarReflectionCullFOV; //0x0044 
	DWORD m_planarReflectionWidth; //0x0048 
	float m_shadowmapSizeZScale; //0x004C 
	DWORD m_shadowmapResolution; //0x0050 
	DWORD m_shadowmapQuality; //0x0054 
	char _0x0058[8];
	float m_shadowmapSliceSchemeWeight; //0x0060 
	float m_shadowmapFirstSliceScale; //0x0064 
	float m_shadowViewDistance; //0x0068 
	char _0x006C[68];
	float m_motionBlurScale; //0x00B0 
	float m_motionBlurMax; //0x00B4 
	float m_motionBlurNoiseScale; //0x00B8 
	DWORD m_motionBlurQuality; //0x00BC 
	DWORD m_dynamicEnvmapResolution; //0x00C0 
	DWORD m_maxDecalVolumeCount; //0x00C4 
	DWORD m_motionBlurMaxSampleCount; //0x00C8 
	DWORD m_motionBlurFrameAverageCount; //0x00CC 
	float m_motionBlurMaxFrameTime; //0x00D0 
	float m_forceMotionBlurDepthCutoff; //0x00D4 
	float m_forceMotionBlurCutoffGradientScale; //0x00D8 
	DWORD m_multisampleCount; //0x00DC 
	float m_multisampleThreshold; //0x00E0 
	DWORD m_maxSpotLightShadowCount; //0x00E4 
	DWORD m_reflectionEnvmapSize; //0x00E8 
	float m_spotLightNearPlane; //0x00EC 
	float m_subSurfaceRolloff; //0x00F0 
	char _0x00F4[4];
	DWORD m_maxSpotLightCount; //0x00F8 
	DWORD m_spotLightShadowmapResolution; //0x00FC 
	DWORD m_spotLightShadowmapQuality; //0x0100 
	char _0x0104[150];
	bool m_drawFirstPersonModel; //0x019A 
	char _0x019B[6];
	bool m_enlightenGlass; //0x01A1 
	bool m_drawDebugSkyEnvmap; //0x01A2 
	bool m_debugDrawEmitters; //0x01A3 
	char _0x01A4[1];
	bool m_depthOfField; //0x01A5 
	char _0x01A6[7];
	bool m_debugDrawDepth; //0x01AD 
	char _0x01AE[1];
	bool m_lightBrightMap; //0x01AF 
	char _0x01B0[1];
	bool m_debugDrawSkyboxAndMask; //0x01B1 
	char _0x01B2[4];
	bool m_debugDrawSkyviewBoxes; //0x01B6 
	bool m_skyEnable; //0x01B7 
	char _0x01B8[6];
	bool m_sunEnabled; //0x01BE 
	char _0x01BF[7];
	bool m_fluorescentBloom; //0x01C6 
	char _0x01C7[6];
	bool m_drawFoliage; //0x01CD 
	char _0x01CE[4];
	bool m_drawLight; //0x01D2 
	bool m_unlitEnable; //0x01D3 
	char _0x01D4[1];
	bool m_spotLightEnable_0; //0x01D5 
	char _0x01D6[3];
	bool m_spotLightEnable_1; //0x01D9 
	char _0x01DA[3];
	bool m_lightShadows; //0x01DD 
	char _0x01DE[17];
	bool m_clearBuffer; //0x01EF 
	char _0x01F0[10];
	bool m_softenSmoke; //0x01FA 
	char _0x01FB[1];
	bool m_somethingLighting; //0x01FC 
	bool m_drawReflection; //0x01FD 
	bool m_fadeDecals; //0x01FE 
	char _0x01FF[5];
	bool m_debugDrawMovementOrSomething; //0x0204 
	bool m_debugChristmasAcidTrip; //0x0205 
	char _0x0206[1];
	bool m_debugMultiView; //0x0207 Has color map, fullbright, shadow, everything!
	char _0x0208[8];
	bool m_lightEnabledAgain; //0x0210 
	bool m_drawShadows; //0x0211 
	char _0x0212[3];
	bool m_drawNothingButGround; //0x0215 
	char _0x0216[10];
	bool m_debugDrawShadowBoxes; //0x0220 
	char _0x0221[2];
	bool m_moreShadows; //0x0223 
	bool DONTFUCKINGCHANGEME; //0x0224 
	char _0x0225[5];
	bool m_smokeShadows; //0x022A 
	char _0x022B[7];
	bool m_comeBackToMe2; //0x0232 
	bool m_softenLighting; //0x0233
};


class IMoveObject
{
public:
	char pad[0x10];
	EntryInputState m_EntryInput;
}; // fb::network::IMoveObject

class WorldRenderer
{
public:
	class RootView
	{
	public:
		DWORD    index;
		/*WorldDrawViewInfo*   */void* viewInfo;
	};
	void*    m_vtable;
	char _0x0004[32];
	DWORD m_viewWidth; //0x0024 
	DWORD m_viewHeight; //0x0028 
	PAD(0x4524);
	WorldRenderSettings* m_worldRenderSettings; //0x8988 
};

class WorldRenderModule
{
public:
	/*unsigned char pad[0x18];				//0000
	//		IWorldRenderer* m_worldRenderer;       // 0x18
	bool m_fmvPlaying;                     // 0x1C
	bool m_worldEnable;                     // 0x1D*/
	char _0x0000[24]; // Inheritance 
	WorldRenderer* m_worldRenderer;
	bool m_fmvPlaying;
	bool m_worldEnable;


}; // fb::WorldRenderModule
class Level
{
public:
	char pad_0000[36]; //0x0000
	class LevelData* m_pLevelData; //0x0024
	char pad_0028[4]; //0x0028
	class N00001C33* N00000084; //0x002C
	char pad_0030[52]; //0x0030
	class TeamEntityData** m_ppTeamEntityData; //0x0064
	char* m_LevelName; //0x0068
	char pad_006C[76]; //0x006C
	WorldRenderModule* m_worldRenderModule;
	class HavokPhysicsManager* m_pHavokPhysicsManager; //0x00BC
	class GameWorld* m_pGameWorld; //0x00C0

}; //Size: 0x0084

class Temp
{
public:
	virtual TypeInfo* GetType();
};
class ClientGameView
{
public:
	virtual void* GetType(); //
	virtual void GetTransform(Matrix &, Vector2 &); //
	virtual void GetLocalTransform(Matrix &); //
	virtual void GetCurrentCameraTransform(Matrix &); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void setActiveCamera(int id); //

};//Size=0x00F0


class Components
{
public:
	char pad_0000[28]; //0x0000
	class Temp** m_ppComponents; //0x001C
	void Dump()
	{
		for (int i = 0; i < 282; i++)
		{
			if (m_ppComponents[i])
			{

			}
		}
	}
};
class LevelData
{
public:
	char pad_0000[8]; //0x0000
	char* m_LevelName; //0x0008
	char pad_000C[72]; //0x000C
	char* m_ID_Name; //0x0054
	char pad_0058[236]; //0x0058
}; //Size: 0x0144
class HavokPhysicsManager
{
public:
	char pad_0000[60]; //0x0000
	intptr_t m_pHavokManager; //0x003C
	class IPhysicsRayCaster* m_pRayCaster; //0x0040
	char pad_0044[28]; //0x0044
	float m_MaxVehicleHeight; //0x0060
	char pad_0064[8]; //0x0064
	class TerrainPhysicsEntity* m_pTerrainPhysicsEntity; //0x006C
	char pad_0070[132]; //0x0070
	intptr_t m_pPhysics; //0x00F4
	char pad_00F8[4]; //0x00F8
	intptr_t* m_pPhysicsSettings; //0x00FC
	intptr_t* m_pPhysicsRenderSettings; //0x0100

};

class WeaponSway
{
public:
	struct Random
	{
		unsigned int m_value;
		unsigned int m_tableIndex;
		float m_nextNormal;
		bool m_nextNormalIsValid;
	};
	class GunSwayLagData
	{
	public:
		float m_MoveStrafeModifier; //+0x0
		float m_MoveForwardModifier; //+0x4
		float m_RotateYawModifier; //+0x8
		float m_RotatePitchModifier; //+0xC
		float m_ReleaseModifier;//+0x10
	};
	class GunSwayRecoilData
	{
	public:
		float m_RecoilAmplitudeMax;//+0x0
		float m_RecoilAmplitudeIncPerShot; //+0x4
		float m_HorizontalRecoilAmplitudeIncPerShotMin; //+0x8
		float m_HorizontalRecoilAmplitudeIncPerShotMax; //+0xC
		float m_HorizontalRecoilAmplitudeMax;//+0x10
		float m_RecoilAmplitudeDecreaseFactor; //+0x14
	};
	class CameraRecoilData
	{
	public:
		char pad[0x8];
		float m_SpringConstant; //+0x10
		float m_SpringDamping;//+0x14
		float m_SpringMinThresholdAngle; //+0x18
	};
	class GunSwayDispersionData
	{
	public:
		float m_MinAngle; //+0x0
		float m_MaxAngle; //+0x4
		float m_IncreasePerShot;//+0x8
		float m_DecreasePerSecond;//+0xC
		float m_NoFireDecreasePerSecond;//+0x10
		float m_NoFireTimeThreshold; //+0x14
	};
	class GunSwayBaseMoveJumpData
	{
	public:
		GunSwayDispersionData m_BaseValue; //+0x0
		GunSwayDispersionData m_Moving; //+0x18
		GunSwayDispersionData m_Jumping; //+0x30
		GunSwayDispersionData m_Sprinting; //+0x48
		GunSwayDispersionData m_VaultingSmallObject; //+0x60
		GunSwayDispersionData m_VaultingMediumObject; //+0x78
		GunSwayRecoilData m_Recoil; //+0x90
		GunSwayLagData m_GunSwayLag; //+0xA8
	};

	class GunSwayStandData
	{
	public:
		GunSwayBaseMoveJumpData m_NoZoom; //+0x0
		GunSwayBaseMoveJumpData m_Zoom; //+0xBC
	};
	class GunSwayBaseMoveData
	{
	public:
		GunSwayDispersionData m_BaseValue; //+0x0
		GunSwayDispersionData m_Moving; //+0x18
		GunSwayRecoilData m_Recoil;//+0x30
		GunSwayLagData m_GunSwayLag; //+0x48
	};
	class GunSwayCrouchProneData
	{
	public:
		GunSwayBaseMoveData m_NoZoom;//+0x0
		GunSwayBaseMoveData m_Zoom; //+0x5C
	};
	class GunSwayStanceTransition
	{
	public:
		GunSwayDispersionData m_MaxPenaltyValue; //+0x0
		float m_CoolDown; //+0x18
	};
	class GunSwayDispersionModData
	{
	public:
		float m_MinAngleModifier; //+0x0
		float m_MaxAngleModifier; //+0x4
		float m_IncreasePerShotModifier; //+0x8
		float m_DecreasePerSecondModifier; //+0xC
	};

	class GunSwayStanceZoomModifierData
	{
	public:
		GunSwayDispersionModData m_DispersionMod; //+0x0
		GunSwayDispersionModData m_MovingDispersionMod; //+0x10
		GunSwayDispersionModData m_SprintingDispersionMod; //+0x20
		float m_RecoilMagnitudeMod;//+0x30
		float m_RecoilAngleMod; //+0x34
		float m_FirstShotRecoilMod;//+0x38
		float m_LagYawMod; //+0x3C
		float m_LagPitchMod; //+0x40
	};

	class GunSwayData
	{
	public:
		char pad[0x8];
		GunSwayStandData m_Stand; //+0x10
		GunSwayCrouchProneData m_Crouch; //+
		GunSwayCrouchProneData m_Prone; //+
		GunSwayStanceTransition m_ProneToCrouch; //+
		GunSwayStanceTransition m_ProneToStand; //+
		GunSwayStanceTransition m_CrouchToProne; //+
		GunSwayStanceTransition m_CrouchToStand; //+
		GunSwayStanceTransition m_StandToProne; //+
		GunSwayStanceTransition m_StandToCrouch; //+
		GunSwayStanceZoomModifierData m_SuppressionModifierUnzoomed;//+
		GunSwayStanceZoomModifierData m_SuppressionModifierZoomed; //+
		void* m_ModifierUnlocks; //+

		float m_DeviationScaleFactorZoom; //+
		float m_GameplayDeviationScaleFactorZoom; //+
		float m_DeviationScaleFactorNoZoom;//+
		float m_GameplayDeviationScaleFactorNoZoom;//+

		float m_ShootingRecoilDecreaseScale; //+
		float m_FirstShotRecoilMultiplier; //+0x438 
		CameraRecoilData m_CameraRecoil;//+
	};
	class Deviation
	{
	public:
		float m_Pitch; //0x0000
		float m_Yaw; //0x0004
		float m_Roll; //0x0008
		float m_TransY; //0x000C
	};//Size=0x0010
	class GunSwayModifierData
	{
	public:
		char pad[0x10];
		GunSwayStanceZoomModifierData m_StandZoomModifier; //+0x18
		GunSwayStanceZoomModifierData m_StandNoZoomModifier;//+0x5C
		GunSwayStanceZoomModifierData m_CrouchZoomModifier; //+0xA0
		GunSwayStanceZoomModifierData m_CrouchNoZoomModifier; //+0xE4
		GunSwayStanceZoomModifierData m_ProneZoomModifier; //+0x128
		GunSwayStanceZoomModifierData m_ProneNoZoomModifier; //+0x16C
		bool m_OnlyInSupportedShooting;//+0x1B0
		bool m_OnlyOnWeaponLightEnabled;//+0x1B1
	};
	struct WeaponFiringUpdateContext
	{
		union Flags
		{
			struct
			{
				unsigned primaryFireTrigger : 1;
				unsigned orderTrigger : 1;
				unsigned reloadTrigger : 1;
			};

			unsigned int data;
		};

		Vector4 targetPos; //0x0000
		WeakPtr<ClientSoldierEntity> target; //0x0010
		WeaponSway* weaponSway; //0x0014
		float deltaTime; //0x0018
		float reloadTimeMultiplier; //0x001C
		float damageMultiplier; //0x0020
		float explosiveMultiplier; // 0x0024
		float overheatMultiplier; // 0x0028
		void* characterMelee; //0x002C
		unsigned int ticks; //0x0030
							// unfinished //
	};
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void primaryFireShotSpawnedCallback(float powerModifier, bool trace, WeaponFiringUpdateContext *context); //
	virtual void function6(); //empty
	virtual void function7(); //
	virtual void function8(); //empty
	virtual void function9(); //empty
	virtual void function10(); //empty
	virtual void function11(); //empty
	virtual void function12(); //empty
	virtual void function13(); //empty
	virtual void function14(); //empty
	virtual void function15(); //empty
	virtual void function16(); //empty
	virtual void function17(); //empty
	virtual void function18(); //empty
	virtual void function19(); //empty
	virtual void function20(); //empty
	virtual void function21(); //empty
	virtual void unlockModifiers(const WeaponModifier * wm); //22            // V: 0x60
	virtual void update(float f, void* scb);//23;      // V: 0x64
	virtual void getDispersion(Matrix &, bool);   // V: 0x68
	virtual void getRecoil(Matrix &, bool);             // V: 0x6C
	virtual void getCameraRecoil(Matrix &);        // V: 0x70
	virtual void getLag(Matrix &, bool);  // V: 0x74
	virtual float getDispersionFactor();           // V: 0x7C
	virtual float getDispersionAngle();            // V: 0x80
	virtual float getMinDispersionAngle();    // V: 0x84
	virtual float getSuppresionMinDispersionAngleFactor();                // V: 0x88
	virtual float getRecoilPitch();       // V: 0x8C
	virtual float getRecoilYaw();        // V: 0x90

	char pad_0000[4]; //0x0000
	class GunSwayData* m_data; //0x0004
	char pad_0008[180]; //0x0008
	float m_TimeSinceLastShot; //0x00BC
	int m_cameraRecoilDeviation; //0x00C0
	char pad_00C4[148]; //0x00C4
	int m_seed; //0x0158
	float m_randomAngle; //0x015C
	float m_randomRadius; //0x0160
	int m_fireShot; //0x0164
	char pad_0165[3]; //0x0165
	int m_initialFireShot; //0x0168
	int m_IsFiring; //0x016C
};//Size=0x0C44

class BulletEntityData
{
public:
	char pad_0000[80]; //0x0000
	char* m_PrjectileName; //0x0050
	char pad_0054[36]; //0x0054
	float m_distributeDamageOverTime; //0x0078
	char pad_007C[24]; //0x007C
	char* m_PrjectileName2; //0x0094
	char pad_0098[52]; //0x0098
	float m_gravity; //0x00CC
	float m_impactImpulse; //0x00D0
	float m_detonationTimeVariation; //0x00D4
	float m_vehicleDetonationRadius; //0x00D8
	float m_vehicleDetonationActivationDelay; //0x00DC
	float m_flyBySoundRadius; //0x00E0
	float m_flyBySoundSpeed; //0x00E4
	float m_firstFraneTravelDistance; //0x00E8
	char pad_00EC[4]; //0x00EC
	float m_DamageMax; //0x00F0
	float m_DamageMin; //0x00F4
	float m_DamageFallOff; //0x00F8
	float m_DamageFallOffEndDistance; //0x00FC
	float m_TimeToArmExplosion; //0x0100
	int m_bHasVehicleDetination; //0x0104
	int m_bInstantHit; //0x0105
	int m_bStopTrail; //0x0106
	int m_bUnk; //0x0107
	char pad_0108[828]; //0x0108
}; //Size: 0x0444

class FiringFunctionData
{
public:
	char pad_0000[96]; //0x0000
	Vector4 m_PositionOffset; //0x0060
	Vector4 m_Direction; //0x0070
	Vector4 m_initialSpeed; //0x0080
	char pad_0090[8]; //0x0090
	class BulletEntityData* m_pBulletEntityData; //0x0098
	char pad_009C[20]; //0x009C
	int m_numberOfBulletsPerShell; //0x00B0
	int m_numberOfBulletsPerShot; //0x00B4
	int m_numberOfBulletsPerBurst; //0x00B8
	int m_relativeTargetAiming; //0x00BC
	int m_forceSpawnToCamera; //0x00BD
	int m_activeForceSpawnToCamera; //0x00BE
	int m_SpawnVisualAtBone; //0x00BF
	char pad_00C0[92]; //0x00C0
	float m_TriggerPullWeight; //0x011C
	float m_RateOfFire; //0x0120
	float m_RateOfFireForBurst; //0x0124
	float m_ClientFireRateMultiplier; //0x0128
	char pad_012C[8]; //0x012C
	float m_ReloadTreshold; //0x0134
	char pad_0138[4]; //0x0138
	float m_ReloadTime; //0x013C
	float m_ReloadTimeBulletsLeft; //0x0140

}; //Size: 0x0860

class WeaponFiringData
{
public:
	char pad_0000[8]; //0x0000
	class FiringFunctionData* m_pFiringFunctionData; //0x0008
	char pad_000C[568]; //0x000C
}; //Size: 0x0244


class SoldierAimingSimulation
{
public:
	char pad_0000[20]; //0x0000
	class SoldierAimingSimulationData* m_pSoldierAimingSimulationData; //0x0014

};//Size=0x0040

class SoldierAimingSimulationData
{
public:
	char pad_0000[8]; //0x0000
	class ZoomLevelData** m_ZoomLevels; //0x0008
	char pad_000C[4]; //0x000C
	int m_AimAssist; //0x0010
	float m_StandPose; //0x0014
	char pad_0018[20]; //0x0018
	float m_CrouchPose; //0x002C
	char pad_0030[20]; //0x0030
	float m_PronePose; //0x0044
	char pad_0048[24]; //0x0048
	float m_ZoomTransitionTime; //0x0060
	char pad_0064[8]; //0x0064
	float m_AimingRange; //0x006C

}; //Size: 0x0144
class WeaponFiring
{
public:
	char pad_0000[60]; //0x0000
	class WeaponSway* m_pSway; //0x003C
	char pad_0040[84]; //0x0040
	class WeaponFiringData* m_pPrimaryFire; //0x0094
	char pad_0098[4]; //0x0098
	class SoldierWeaponData* m_pSoldierWeaponData; //0x009C
	char pad_00A0[4]; //0x00A0
	int m_weaponState; //0x00A4
	int m_lastWeaponState; //0x00A8
	int m_nextWeaponState; //0x00AC
	char pad_00B0[8]; //0x00B0
	float m_timeToWait; //0x00B8
	float m_reloadTimer; //0x00BC
	float m_holdReleaseMinDelay; //0x00C0
	float m_recoilTimer; //0x00C4
	float m_recoilAngleX; //0x00C8
	float m_recoilAngleY; //0x00CC
	float m_recoilAngleZ; //0x00D0
	float m_recoilFovAngle; //0x00D4
	float m_recoilTimeMultiplier; //0x00D8
	float m_overheatDropMultiplier; //0x00DC
	char pad_00E0[16]; //0x00E0
	int m_externalPrimaryMagazineCapacity; //0x00F0
	int m_Ammo; //0x00F4
	int m_ExtraAmmo; //0x00F8
	char pad_00FC[4]; //0x00FC
	int m_hasStoppedFiring; //0x0100
	int m_primaryFireTriggeredLastFrame; //0x0101
	int m_isOverheated; //0x0102
	char pad_0103[9]; //0x0103
	int m_Ticks; //0x010C
	char pad_0110[52]; //0x0110
}; //Size: 0x0144

class CharacterPhysicsData
{
public:
	class CharacterSprintData
	{
	public:
		char pad_0000[8]; //0x0000
		float m_SprintPowerDecreasePerSecond; //0x0008
		float m_SprintPowerIncreasePerSecond; //0x000C
		float m_SprintMinimumPower; //0x0010
		int m_AllowContinousSprinting; //0x0014
	};
	//char pad_0000[8]; //0x0000
	//char* m_Name; //0x0008
	//intptr_t m_States; //0x000C
	//intptr_t m_DefaultState; //0x0010
	//char pad_0014[4]; //0x0014
	//class CharacterSprintData* m_pSprint; //0x0018
	//int m_MaterialPair; //0x001C
	//int m_PushableObjectWeight; //0x0020
	//float m_Mass; //0x0024
	//float m_MaxAscendAngle; //0x0028
	//float m_PhysicalRadius; //0x002C
	//float m_EnterSwimStateDepth; //0x0030
	//float m_ExitSwimStateDepth; //0x0034
	//float m_InputAcceleration; //0x0038
	//float m_LadderAcceptAngle; //0x003C
	//float m_LadderAcceptAnglePitch; //0x0040
	//float m_JumpPenaltyTime; //0x0044
	//float m_JumpPenaltyFactor; //0x0048
	//float m_RadiusToPredictCollisionOnCharacters; //0x004C
	//int m_AllowPoseChangeDuringTransition; //0x0050
	//int m_AutoPushAwayFromWallsInProne; //0x0051
};

class FixWeaponModifier
{
public:
	char pad_0000[0xC]; //0x0000
	class UnlockAssetBase* m_pFirstWeaponUnlockAsset; //0x0C
};

class WeaponModifier
{
public:
	//char pad_0000[68]; //0x0000
	char pad_0000[0x8]; //0x0000
	class FixWeaponModifier* _mpFixit;//0xC
	char pad_0001[0x38]; //0x0000
	class UnlockAssetBase* m_pWeaponUnlockAsset; //0x0034
	char pad_0038[112]; //0x0048
	int m_EnableBreathControl; //0x00B8
	int m_CanBeInSupportedShooting; //0x00B9
	int m_UnZoomOnBoltAction; //0x00BA
	int m_HoldBoltActionUntilZoomRelease; //0x00BB
	int m_IsSilenced; //0x00BC

}; //Size: 0x0184

class ClientDefibrillatorWeapon
{
public:
	char pad_0x0000[0x4]; //0x0000
	DefibrillatorWeaponData* m_pDefibrillatorWeaponData; //0x0004

	char pad_0x0010[0x4]; //
	void* m_pWeaponFiringData; // 
	char pad_0x0020[0x10]; //
	Matrix m_ShootSpace; // 
};//Size=0x0440

class ClientWeapon
{
public:
	char pad_0000[4]; //0x0000
	class WeaponData* m_pWeaponData; //0x0004
	char pad_0008[4]; //0x0008
	class WeaponFiringData* m_pWeaponFiringData; //0x000C
	class WeaponModifier* m_pWeaponModifier; //0x0010
	char pad_0014[28]; //0x0014
	Vector4 m_MoveSpeed; //0x0030
	Matrix m_ShootSpace; //0x0040
	Matrix m_ShootSpaceIdentity; //0x0080
	char pad_00C0[264]; //0x00C0
	float m_CameraFOV; //0x01C8
	float m_WeaponFOV; //0x01CC
	float m_FOVScaleFactor; //0x01D0
	char pad_01D4[4]; //0x01D4
	int m_ZoomLevel; //0x01D8
	char pad_01DC[1012]; //0x01DC
	Vector4 m_lastRayBegin; //0x05D0
	Vector4 m_lastRayEnd; //0x05E0
	char pad_05F0[96]; //0x05F0
	WeakPtr<ClientControllableEntity> m_ControllableInAim; //0x0650

}; //Size: 0x0920

class AimAssist
{
public:
	char pad_0000[12]; //0x0000
	float m_yaw; //0x000C
	char pad_0010[8]; //0x0010
	float m_pitch; //0x0018

}; //Size: 0x0148

class ClientSoldierAimingEnvironment
{
public:
	class ClientSoldierEntity* m_soldier; //0x0
};//Size=0x0010

class ClientSoldierAimingSimulation
{
public:
	class SoldierAimingSimulationData* m_pSoldierAimingSimulationData; //0x0000
	class ClientSoldierAimingEnvironment* m_environment; //0x0004
	class AimAssist* m_fpsAimer; //0x0008
	Vector2 m_Angles; //0x000C
	float m_aimYawTimer; //0x0014
	float m_aimPitchTimer; //0x0018
	Vector2 m_sway; //0x001C
	char pad_0024[40]; //0x0024
	float m_zoomLevel; //0x004C
	char pad_0050[64]; //0x0050
	Vector3 N00002D9E; //0x0090
	char pad_009C[1264]; //0x009C
}; //Size: 0x058C

class ClientWeaponFiringReplication
{
public:
	char pad_0000[140]; //0x0000
	class WeaponFiringData* m_pWeaponFiringData; //0x008C
	char pad_0090[136]; //0x0090
	class WeaponSway* m_pWeaponSway; //0x0118
};

enum WeaponClassEnum
{
	wc12gauge,
	wc338Magnum,// = 1
	wc357Magnum,// = 2
	wc44Magnum,//= 3
	wc45cal,// = 4
	wc46x30mm,// = 5
	wc50cal,// = 6
	wc545x45mmWP,//= 7
	wc556x45mmNATO,//= 8
	wc57x28mm,// = 9
	wc58x42mm,//= 10
	wc762x39mmWP,// = 11
	wc762x51mmNATO,//= 12
	wc762x54mmR,//= 13
	wc9x19mm,//= 14
	wc9x39mm,// = 15
	wcAssault,// = 16
	wcShotgun,//= 17
	wcSmg,//= 18
	wcLmg,// = 19
	wcSniper,// = 20
	wcUgl,//= 21
	wcHgr,// = 22
	wcAt,//= 23
	wcATMine,// = 24
	wcC4,//= 25
	wcBallisticShield,//= 26
	wcAutoInjector,//= 27
	wcKnife,//= 28
	wcLaserDesignator,//= 29
	wcLaserPainter,// = 30
	wcMedKit,//= 31
	wcMortarStrike,//= 32
	wcPowerTool,//= 33
	wcTracerDart,// = 34
	wcRadioBeacon,//= 35
	wcEodBot,// = 36
	wcReconMav,// = 37
	wcUGS,//= 38
	wcUnarmed,//= 39
	wcCount,//= 40
	wcNone// = 41
};

class SoldierWeaponData
{
public:
	char pad_0000[100]; //0x0000
	int m_weaponClass; //0x0064
	char pad_0068[4]; //0x0068
	class WeaponFiringData* m_pWeaponFiringData; //0x006C
	char pad_0070[112]; //0x0070
	char* m_WeaponName; //0x00E0

	bool isRocket()
	{
		if (this->m_weaponClass == wcAt)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

class ClientSoldierWeapon
{
public:
	char pad_0000[20]; //0x0000
	class SoldierWeaponData* m_pSoldierWeaponData; //0x0014
	char pad_0018[300]; //0x0018
	class ClientSoldierAimingSimulation* m_pClientSoldierAimingSimulation; //0x0144
	char pad_0148[12]; //0x0148
	class ClientWeapon* m_pWeapon; //0x0154
	class ClientWeaponFiringReplication* m_pReplicatedFiring; //0x0158
	char pad_015C[4]; //0x015C
	class WeaponFiring* m_pPrimaryFiring; //0x0160
	class WeaponFiring* m_pCorrectedFiring; //0x0164

}; //Size: 0x0444

class ClientSoldierWeaponsComponent
{
public:
	class ClientActiveWeaponHandler
	{
	public:
		char pad_0000[8]; //0x0000
		float m_WeaponUsageTime; //0x0008
		char pad_000C[8]; //0x000C
		class ClientSoldierWeapon* m_pActiveWeapon; //0x0014
	};

	class ClientAnimatedSoldierWeaponHandler
	{
	public:
		ClientSoldierWeapon * m_WeaponList[10]; //0x0000 
	};

	enum WeaponSlot
	{
		M_PRIMARY = 0,
		M_SECONDARY = 1,
		M_GADGET1 = 2,
		M_GADGET2 = 5,
		M_GRENADE = 6,
		M_KNIFE = 7
	};

	char pad_0000[112]; //0x0000
	Matrix m_weaponTransform; //0x0070
	char pad_00B0[8]; //0x00B0
	class ClientSoldierEntity* m_pSoldier; //0x00B8
	class ClientAnimatedSoldierWeaponHandler* m_pHandler; //0x00BC
	char pad_00C0[12]; //0x00C0
	class ClientActiveWeaponHandler* m_pActiveHandler; //0x00CC
	char pad_00D0[100]; //0x00D0
	class SoldierAimingSimulation* m_pSoldierAimingSimulation; //0x0134
	char pad_0138[28]; //0x0138
	int m_currentZoomLevel; //0x0154
	float m_timeSinceLastShot; //0x0158
	char pad_015C[8]; //0x015C
	int m_activeSlot; //0x0164
	int m_lastActiveSlot; //0x0168
	int m_lastActiveWeaponSlot; //0x016C
	char pad_0170[24]; //0x0170
	int m_currentZoomLevel1; //0x0188

	ClientSoldierWeapon* GetActiveSoldierWeapon()
	{
		if (!MmIsAddressValidPtr(m_pActiveHandler))
			return NULL;

		if (!MmIsAddressValidPtr(m_pActiveHandler->m_pActiveWeapon))
			return NULL;

		return m_pActiveHandler->m_pActiveWeapon;
	};
};


#pragma warning( disable : 4200 )
class ResourceManager
{
public:

	class Compartment
	{
	public:
		char pad_0000[0x150]; //0x0000 128 ?


							  //4+16+ sizeof(stringmap) 
							  //MemArena 8
							  //	 sizeof(CRITICAL_SECTION)//0x18
							  //0x4
							  //0x130
		//vector<TypeInfoObject*> m_objects; //0x0014C //16C ?
	}; //Size: 0x0028

public:
	volatile int m_bundleLoadInProgress; //0x0000
	Compartment* m_compartments[]; //0x0004

	static ResourceManager* GetInstance()
	{
		//return *(ResourceManager**)(OFFSET_RESOURCEMANAGER);
	}
};

class SoldierWeaponBlueprint
{
public:
	char pad_0004[4]; //0x0004
	char* m_Name; //0x0008
	char pad_000C[20]; //0x000C
	class SoldierWeaponData* m_pSoldierWeaponData; //0x0020
	char pad_0024[96]; //0x0024

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0084

class UnlockAssetBase
{
public:
	char pad_0004[4]; //0x0004
	char* m_name; //0x0008
	int m_unlockUserData; //0x000C
	char pad_0010[4]; //0x0010
	char* m_debugUnlockId; //0x0014
	char pad_0018[16]; //0x0018
	class SoldierWeaponBlueprint* m_pBlueprint; //0x0028

	virtual  TypeInfo* GetType();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();

};//Size=0x04C0

class QuatTransform
{
public:
	Vector4 m_TransAndScale; // 0x0000
	Vector4 m_Rotation;  // 0x0010
}; // Size 0x0020

class UpdatePoseResultData
{
public:

	enum PlayerBones
	{
		Reference, //0
		AITrajectory, //1
		Trajectory, //2
		TrajectoryEnd, //3
		Hips, //4
		Spine, //5
		Spine1, //6
		Spine2, //7
		LeftShoulder, //8
		LeftArm, //9
		LeftArmRoll, //10
		LeftForeArm, //11
		LeftForeArmRoll, //12
		LeftForeArmRoll1, //13
		LeftHand, //14
		LeftHandMiddle0, //15
		LeftHandMiddle1, //16
		LeftHandMiddle2, //17
		LeftHandMiddle3, //18
		LeftHandMiddle4, //19
		LeftHandRing0, //20
		LeftHandRing1, //21
		LeftHandRing2, //22
		LeftHandRing3, //23
		LeftHandRing4, //24
		LeftHandPinky0, //25
		LeftHandPinky1, //26
		LeftHandPinky2, //27
		LeftHandPinky3, //28
		LeftHandPinky4, //29
		LeftHandIndex0, //30
		LeftHandIndex1, //31
		LeftHandIndex2, //32
		LeftHandIndex3, //33
		LeftHandIndex4, //34
		LeftHandThumb1, //35
		LeftHandThumb2, //36
		LeftHandThumb3, //37
		LeftHandThumb4, //38
		LeftForeArmCloth, //39
		LeftElbowRoll, //40
		LeftArmCloth, //41
		LeftShoulderPhys1, //42
		Neck, //43
		Neck1, //44
		Head, //45
		HeadEnd, //46
		Face, //47
		Offset_Jaw, //48
		Jaw, //49
		Offset_LeftLowerLip, //50
		LeftLowerLip, //51
		Offset_LowerLip, //52
		LowerLip, //53
		Offset_RightLowerLip, //54
		RightLowerLip, //55
		Offset_Tongue, //56
		Tongue, //57
		Offset_TongueTip, //58
		TongueTip, //59
		Offset_Chin, //60
		Chin, //61
		Offset_LeftEye, //62
		LeftEye, //63
		Offset_RightEye, //64
		RightEye, //65
		Offset_LeftUpCheek, //66
		LeftUpCheek, //67
		Offset_LeftUpInnerCheek, //68
		LeftUpInnerCheek, //69
		Offset_RightUpInnerCheek, //70
		RightUpInnerCheek, //71
		Offset_RightUpCheek, //72
		RightUpCheek, //73
		Offset_LeftCheek, //74
		LeftCheek, //75
		Offset_RightCheek, //76
		RightCheek, //77
		Offset_LeftMouth, //78
		LeftMouth, //79
		Offset_LeftUpperLip, //80
		LeftUpperLip, //81
		Offset_UpperLip, //82
		UpperLip, //83
		Offset_RightUpperLip, //84
		RightUpperLip, //85
		Offset_RightMouth, //86
		RightMouth, //87
		Offset_LeftUpEyelid, //88
		LeftUpEyelid, //89
		Offset_RightUpEyelid, //90
		RightUpEyelid, //91
		Offset_LeftLowEyelid, //92
		LeftLowEyelid, //93
		Offset_RightLowEyelid, //94
		RightLowEyelid, //95
		Offset_LeftInnerEyebrow, //96
		LeftInnerEyebrow, //97
		Offset_LeftOuterEyebrow, //98
		LeftOuterEyebrow, //99
		Offset_RightInnerEyebrow, //100
		RightInnerEyebrow, //101
		Offset_RightOuterEyebrow, //102
		RightOuterEyebrow, //103
		Offset_LeftNose, //104
		LeftNose, //105
		Offset_RightNose, //106
		RightNose, //107
		Offset_LeftCrease, //108
		LeftCrease, //109
		Offset_RightCrease, //110
		RightCrease, //111
		Offset_LeftMiddleEyebrow, //112
		LeftMiddleEyebrow, //113
		Offset_RightMiddleEyebrow, //114
		RightMiddleEyebrow, //115
		HeadCloth, //116
		Throat, //117
		Spine2Phys1, //118
		Spine2Cloth, //119
		RightShoulder, //120
		RightArm, //121
		RightArmRoll, //122
		RightForeArm, //123
		RightForeArmRoll, //124
		RightForeArmRoll1, //125
		RightHand, //126
		RightHandMiddle0, //127
		RightHandMiddle1, //128
		RightHandMiddle2, //129
		RightHandMiddle3, //130
		RightHandMiddle4, //131
		RightHandRing0, //132
		RightHandRing1, //133
		RightHandRing2, //134
		RightHandRing3, //135
		RightHandRing4, //136
		RightHandPinky0, //137
		RightHandPinky1, //138
		RightHandPinky2, //139
		RightHandPinky3, //140
		RightHandPinky4, //141
		RightHandIndex0, //142
		RightHandIndex1, //143
		RightHandIndex2, //144
		RightHandIndex3, //145
		RightHandIndex4, //146
		RightHandThumb1, //147
		RightHandThumb2, //148
		RightHandThumb3, //149
		RightHandThumb4, //150
		RightForeArmCloth, //151
		RightElbowRoll, //152
		RightArmCloth, //153
		RightShoulderPhys1, //154
		Wep_Root, //155
		Wep_Extra1, //156
		Wep_Trigger, //157
		Wep_Slide, //158
		Wep_Grenade1, //159
		Wep_Grenade2, //160
		Wep_Mag, //161
		Wep_Mag_Ammo, //162
		Wep_Physic1, //163
		Wep_Physic2, //164
		Wep_Physic3, //165
		Wep_Belt1, //166
		Wep_Belt2, //167
		Wep_Belt3, //168
		Wep_Belt4, //169
		Wep_Belt5, //170
		Wep_Bipod1, //171
		Wep_Bipod2, //172
		Wep_Bipod3, //173
		IK_Joint_LeftHand, //174
		IK_Joint_RightHand, //175
		Wep_Extra2, //176
		Wep_Extra3, //177
		Wep_Aim, //178
		LeftSpine1Phys1, //179
		RightSpine1Phys1, //180
		LeftUpLeg, //181
		LeftUpLegRoll, //182
		LeftLeg, //183
		LeftFoot, //184
		LeftToeBase, //185
		LeftToe, //186
		LeftLegCloth, //187
		LeftKneeRoll, //188
		LeftHipsRoll, //189
		LeftUpLegCloth, //190
		HipsCenterPhys, //191
		HipsCloth, //192
		LeftHipsFrontPhys, //193
		LeftHipsBackPhys, //194
		LeftHipsSidePhys, //195
		RightUpLeg, //196
		RightUpLegRoll, //197
		RightLeg, //198
		RightFoot, //199
		RightToeBase, //200
		RightToe, //201
		RightLegCloth, //202
		RightKneeRoll, //203
		RightHipsRoll, //204
		RightUpLegCloth, //205
		RightHipsFrontPhys, //206
		RightHipsBackPhys, //207
		RightHipsSidePhys, //208
		CameraBase, //209
		CameraJoint, //210
		Connect, //211
		ConnectEnd, //212
		totalBones
	};

	class QuatTransform* m_LocalTransform; //0x004C UpdatePoseResultData  Instance
	class QuatTransform* m_WorldTransform; //0x0050
	class QuatTransform* N00003AA7; //0x0054
	class QuatTransform* N00003AA8; //0x0058
	class QuatTransform* N00003AA9; //0x005C
	class QuatTransform* m_ActiveWorldTransforms; //0x0060
	class QuatTransform* m_ActiveLocalTransforms; //0x0064
	int m_Slot; //0x0068
	int m_ReaderIndex; //0x006C
	int m_ValidTransforms; //0x0070
	int m_PoseUpdateEnabled; //0x0071
	int m_PoseNeeded; //0x0072
};

class GameAnimatable
{
public:
	char pad_001[0xD0];
	bool m_hadVisualUpdate;  // this+0xD0
};

class ClientAntAnimatableComponent
{
public:
	char pad_001[0x20];
	GameAnimatable m_handler;
};

class ClientRagDollComponent
{
public:
	char pad_0000[4]; //0x0000
	class RagdollComponentData* m_pRagdollComponentData; //0x0004
	char pad_0008[52]; //0x0008
	UpdatePoseResultData m_UpdatePoseResultData; //0x003C
}; //Size: 0x04D4

class BoneCollisionComponent
{
public:

	class BoneTransformInfo
	{
	public:
		Matrix transform;    // 0x00
		Vector4 position;    // 0x40
	};

	char pad_0000[4]; //0x0000
	class BoneCollisionComponentData* m_pBoneCollisionComponentData; //0x0004
	char pad_0008[12]; //0x0008
	class BoneTransformInfo* m_boneCollisionTransforms; //0x0014
	char pad_0018[124]; //0x0018
	int m_collisionBoneCount; //0x0094
	int m_collisionEnabled; //0x0098
	int m_collisionUpdated; //0x0099

};//Size=0x0840

class RotateToHitData
{
public:
	float m_RotationSpeedFactor; //+0x0
};

class PoseConstraintsData
{
public:
	bool m_StandPose; //+0x0
	bool m_CrouchPose; //+0x1
	bool m_PronePose; //+0x2
};

class BFClientSoldierHealthComponent//BFClientSoldierHealthComponent
{
public:
	char pad_0000[16]; //0x0000
	float m_Health; //0x0010
	float m_MaxHealth; //0x0014
	char pad_0018[8]; //0x0018
	float m_vehicleHealth; //0x0020

};//Size=0x0440

class MeshAsset
{
public:
	int Pad000[0x8];
	char* m_name;
};

class ExplosiveData
{
public:
	char pad_0x0000[0x60]; //0x0000
	char* m_name; //0x00C0 

};//Size=0x0440

class RigidMeshAsset
{
public:
	char pad_0000[8]; //0x0000
	char* m_name; //0x0008
};

class SupplySphereEntityData
{
public:
	char pad_0000[0xB4]; //0x0000
	class RigidMeshAsset* m_pRigidMeshAsset; //0x00B4

}; //Size: 0x0144

class ClientSupplySphereEntityData
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void computeBoundingBoxWorldTransform(Matrix *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	char pad_0004[16]; //0x0004
	class SupplySphereEntityData* m_pData; //0x0014
	char pad_0018[88]; //0x0018
	Vector3 m_Position; //0x0070

}; //Size: 0x0448

class StaticModelEntityData
{
public:
	char pad_0000[132]; //0x0000
	class MeshAsset* m_pMeshAsset; //0x0084
}; //Size: 0x0454

class ClientStaticModelEntity
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void func21();
	virtual void computeBoundingBoxWorldTransform(LinearTransform *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	char pad_0004[20]; //0x0004
	class StaticModelEntityData* m_Data; //0x0018

};

class ObjectBlueprint
{
public:
	char pad_0000[8]; //0x0000
	char* m_Name; //0x0008

}; //Size: 0x0044

class KitPickupEntityData
{
public:
	char pad_0000[120]; //0x0000
	class ObjectBlueprint* m_pObjectBlueprint; //0x0078

}; //Size: 0x054C

class PositionData
{
public:
	Matrix m_Transform; //0x0000

}; //Size: 0x0080

class ClientPickupEntity
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void computeBoundingBoxWorldTransform(LinearTransform *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	char pad_0004[16]; //0x0004
	class KitPickupEntityData* m_pData; //0x0014
	char pad_0018[4]; //0x0018
	class PositionData* m_pPositionData; //0x001C
	char pad_0020[80]; //0x0020
	Vector3 m_Position; //0x0070
};

class ExplosivesName
{
public:
	char pad_0x0000[0x8]; //0x0000
	char* m_AssetName; //0x0010 
	char pad_0x0018[0x4]; //0x0018
	char* m_Name; //0x0020 

};//Size=0x0040

enum AntEntryIdEnum
{
	AntEntryIdEnum_Humvee_Driver = 0,
	AntEntryIdEnum_Humvee_Gunner = 1,
	AntEntryIdEnum_Humvee_PassengerRearLeft = 2,
	AntEntryIdEnum_Humvee_PassengerRearRight = 3,
	AntEntryIdEnum_F16_Pilot = 4,
	AntEntryIdEnum_SU37_Pilot = 5,
	AntEntryIdEnum_AH6_Pilot = 6,
	AntEntryIdEnum_AH64_Pilot = 7,
	AntEntryIdEnum_AH64_Gunner = 8,
	AntEntryIdEnum_Vodnik_Driver = 9,
	AntEntryIdEnum_Vodnik_Gunner = 10,
	AntEntryIdEnum_Humvee_PassengerFrontRight = 11,
	AntEntryIdEnum_Vodnik_PassengerFrontRight = 12,
	AntEntryIdEnum_Vodnik_PassengerRearRight = 13,
	AntEntryIdEnum_Vodnik_PassengerRearLeft = 14,
	AntEntryIdEnum_VadsGunner = 15,
	AntEntryIdEnum_F18F_Pilot = 16,
	AntEntryIdEnum_F18F_Navigator = 17,
	AntEntryIdEnum_M1A2_Gunner = 18,
	AntEntryIdEnum_M1A2_Driver = 19
};

class PlayerEntryComponentData
{
public:
	class AntEnumeration
	{
	public:
		char _0x000[12];
		int m_Value; //+12
	};
	char aEntryComponentData[120]; //+0x00 Inherited
	Vector3  m_AnimationAccelerationMultiplier; //+0xF0
	char* m_AntEntryIDStr; //+0x100
	AntEntryIdEnum m_AntEntryId; //+0x108
	AntEnumeration m_AntEntryEnumeration; //+0x110
};

class ClientPlayerEntryComponent
{
public:
	char pad_0000[4]; //0x0000
	intptr_t m_pSomeComponentList; //0x0004
	class PlayerEntryComponentData* m_pPlayerEntryComponentData; //0x0008
	char pad_000C[324]; //0x000C
	class ClientPlayer* m_pClientPlayer; //0x0150
};//0x640

class ClientControllableEntity
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void computeBoundingBoxWorldTransform(Matrix *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	char pad_0004[12]; //0x0004
	class Components* m_pComponents; //0x0010

};//Size=0x0148

class EntryComponent {
public:
	class WeaponInfo {
	public:
		virtual void WorldTransfrom(Matrix&);
		virtual void GetState(int&);
		virtual void AddWeaponFiringCallbacks(void*);
		virtual void RemoveWeaponFiringCallbacks(void*);
		virtual WeaponFiring* GetWeaponFiring();
		virtual ClientWeapon* GetWeapon();
		virtual bool ActiveInStance(int);
		virtual void* GetWeaponComponent();

		ClientWeaponComponent* m_pWeaponComponent; //0x0008
	};

	class FiringCallbacks
	{
	public:
		virtual void Function0();
		char __0x0004[0x4];
		WeaponInfo* weapon_info;
	};

	virtual int GetActiveStance();
	virtual bool isCharacterControlEntry();
	virtual void animTree();
	virtual void onPrimaryStartedFiring(WeaponInfo *);
	virtual void onPrimaryFire(WeaponInfo *);
	virtual void onPrimaryFireRelease(WeaponInfo *);
	virtual void onPrimaryFireShotSpawned(WeaponInfo *, float);
	virtual void onPrimaryFireAutomaticBegin(WeaponInfo *);
	virtual void onPrimaryFireAutomaticEnd(WeaponInfo *);
	virtual void onPrimaryStoppedFiring(WeaponInfo *);
	virtual void onReload(WeaponInfo *);
	virtual DWORD_PTR entryData();
	virtual void onSwitchStance();
	virtual bool isStanceAvailable(int);
	//vector<FiringCallbacks*> weapons;
};

class ClientWeaponComponent
{
public:
	char _0x0000[0x4];
	WeaponFiring* m_pWeaponFiring;
	WeaponComponentData* m_pComponentData; //0x0010
	char _0x0018[0x4];
	ClientPlayerEntryComponent* m_pPlayerEntry; //0x0020
	char _0x0028[0x14];
	DynamicPhysicsEntity* m_physicsEntity; //0x0050 Start of WeaponComponent
	char _0x0008[0x18];
	void* m_interpolationObject; //0x0088
	ClientWeapon* m_pWeapon; //0x0090
	void* m_pController; //0x0098 ClientWeaponComponentSimulation
	void* m_pReplicatedWeapon; //0x00A0 ClientWeaponComponentReplication
	void* m_pPredictedWeapon; //0x00A8 ClientWeaponComponentPrediction
	void* m_pLockingController; //0x00B0 ClientLockingController null
	void* m_pSecondaryLockingController; //0x00B8 ClientLockingController null
	ClientPlayer* m_pPlayer; //0x00C0 //148 in swbf
	WeaponInfo* m_pWeaponInfo; //0x00C8
	EntryComponent::FiringCallbacks* m_pWeaponFiringCallback; //0x00D0
	void* m_pWeaponMeshModel; //0x00D8 MeshModel null
	ClientPlayerEntryComponent* m_pFiringEntry; //0x00E0 ClientPlayerEntryComponent
}; //0x00B0

class WeaponComponentData
{
public:
	char _0x0000[0x38];
	Vector4  m_ProjectileSpawnOffset; //0x0070
	Vector4  m_TargetPositionOverride; //0x0080
	void* m_WeaponMesh; //0x0090
	void* m_WeaponFiring; //0x0098
	char* m_pDamageGiverName; //0x00A0
	void* m_AIData; //0x00A8
	void* m_CustomWeaponType; //0x00B0
	float m_ImpulseStrength; //0x00B8
	DWORD m_Classification; //0x00BC
	float m_ReloadTimeMultiplier; //0x00C0
	float m_DamageMultiplier; //0x00C4
	float m_ExplosionDamageMultiplier; //0x00C8
	float m_OverheatDropPerSecondMultiplier; //0x00CC
	float m_LockTimeMultiplier; //0x00D0
	float m_LockingAcceptanceAngleMultiplier; //0x00D4
	DWORD m_WeaponItemHash; //0x00D8
	bool m_SequentialFiring; //0x00DC
	char _0x00DD[0x3];
}; //0x00E0

class SoldierEntity
{
public:

	virtual BoneCollisionComponent* boneCollisionComponent(); // not tested
	virtual Matrix& soldierTransform();
	virtual bool SoldierEntity_funct2();
	virtual bool SoldierEntity_funct3();
	virtual bool isFiring();
	virtual bool isReloading();
	virtual bool SoldierEntity_funct6();
	virtual WeaponSway* getWeaponSway();
	virtual WeaponFiring* getCurrentWeaponFiring();
	virtual void* getCurrentWeaponFiringData();     // PrimaryFire* m_pPrimaryFire == WeaponFiringData* ;
	virtual bool SoldierEntity_funct10();
	virtual float moveSpeedMultiplier();

	SoldierEntityData* m_SoldierEntityData2;
};

class SoldierEntityData
{
public:
	class SoldierSprintSettingsData
	{
	public:
		char pad_0x00[0x8]; //+0x00
		float m_Fov; //+0x10
		float m_FovInDelay; //+0x14
		float m_FovInTime; //+0x18
		float m_FovOutDelay; //+0x1C
		float m_FovOutTime; //+0x20
		float m_RecoverTime; //+0x24
		float m_SprintToProneRecoverTime; //+0x28
		float m_InterruptingActions; //+0x30
	};

	enum PersonViewMode
	{
		PersonViewMode_FirstPerson = 0,
		PersonViewMode_ThirdPerson = 1
	};

	enum PlayerSpawnType
	{
		PlayerSpawnType_HumanPlayer = 0,
		PlayerSpawnType_AiPlayer = 1,
		PlayerSpawnType_Actor = 2,
		PlayerSpawnType_BrainAI = 3,
		PlayerSpawnType_Ai2Player = 300
	};

	char pad_0000[128]; //0x0000
	int m_DefaultTeam; //0x0080
	float m_LowHealthThreshold; //0x0084
	int m_MaterialPair; //0x0088
	int m_UsePrediction; //0x008C
	int m_ResetTeamOnLastPlayerExits; //0x008D
	int m_Immortal; //0x008E
	int m_FakeImmortal; //0x008F
	int m_ForceForegroundRendering; //0x0090
	char pad_0091[15]; //0x0091
	float m_MaxHealth; //0x00A0
	PersonViewMode m_DefaultViewMode; //0x00A4
	PlayerSpawnType PlayerSpawnType; //0x00A8
	intptr_t* m_pVoiceOverInfo; //0x00AC
	intptr_t* m_pSoldierSoundData; //0x00B0
	int m_CharacterLightingEnable; //0x00B4
	char pad_00B5[43]; //0x00B5
	class SoldierAimingConstraintsData* m_pSoldierAimingConstraintsData; //0x00E0
	char pad_00E4[4]; //0x00E4
	class CharacterPhysicsData* m_pCharacterPhysics; //0x00E8
	char pad_00EC[24]; //0x00EC
	class CollisionData* m_pCollisionInfo; //0x0104
	float m_FLIRValue; //0x0108
	float m_ExplosionDamageModifier; //0x010C
	float m_RegenerationDelayModifier; //0x0110
	float m_FallDamageThreshold; //0x0114
	int m_UseSpineXRotation; //0x0118
	int m_ShowWeaponWhenDead; //0x0119
	int m_EnableGroundmapLighting; //0x011A
	int m_LowerGunOnOwnTeam; //0x011B
	int m_ProximityCheck; //0x011C
	int m_FreeSpaceCheck; //0x011D
	int m_CollisionEnabled; //0x011E
	int m_PhysicsControlled; //0x011F
	int m_IsPushable; //0x0120
	int m_HumanPlayerControlled; //0x0121
	int m_InteractiveManDownAllowed; //0x0122
	int m_ShowNametag; //0x0123

};//Size=0x0440

class ClientSoldierPrediction
{
public:
	char pad_0000[32]; //0x0000
	Vector3 m_Position; //0x0020
	float m_Unk1;
	char pad_0030[16]; //0x0030
	Vector3 m_Velocity; //0x0040
	float m_Unk2;
	char pad_0050[28]; //0x0050
	int m_Pose; //0x006C
	int m_ChangingToPose; //0x0070
};//Size=0x00A0

class ClientSpottingTargetComponent
{
public:

	enum SpotType
	{
		SpotType_None,
		SpotType_Active,
		SpotType_Passive,
		SpotType_Radar,
		SpotType_Unspottable
		//....
	};

	class SpottingTargetComponentData
	{
	public:
		char pad_0000[36]; //0x0000
		float m_ActiveSpottedTime; //0x0024
		float m_PassiveSpottedTime; //0x0028
		float m_ActiveSpottedTimeMultiplier; //0x002C
		float m_PassiveSpottedTimeMultiplier; //0x0030
		float m_SpotOnFireMultiplier; //0x0034
		float m_RadarSpottedSpeedThresholdOverride; //0x0038
		int m_TargetBoundingBoxCenter; //0x003C
		int m_CalculateAngleOutsideBoundingSphere; //0x003D
	};

	char pad_0000[4]; //0x0000
	class SpottingTargetComponentData* m_pSpottingTargetComponentData; //0x0004
	char pad_0008[16]; //0x0008
	int m_spotType; //0x0018
	class ClientPlayer* m_spotterPlayer; //0x001C
	class ClientPlayer* m_playerThatOrders; //0x0020
	float m_lastOrderTime; //0x0024

};

class SprintInputHandler
{
public:
	int m_currentState; //0x0000
	float m_doubleTapTimer; //0x0004
	float m_sprintReleaseTimer; //0x0008
	int m_waitForSprintRelease; //0x000C

};

struct BoneCollisionData
{
	struct PitchModifier
	{
		Vector4 m_Offset; //0x0000
		float m_PitchVal; //0x0010
		float m_PitchAngle; //0x0014
	}; //0x0020

	Vector4 m_DebugDrawColor; //0x0000 
	Vector4 m_CapsuleOffset; //0x0010 
	PitchModifier m_MaxPitch; //0x0020 
	PitchModifier N0000087F; //0x0038 
	char pad_0x0050[0x8]; //0x0050
	char* m_pBoneName; //0x0060 
	int m_AnimationHitReactionType; //0x0068 
	DWORD m_MaterialPair; //0x006C 
	int m_BoneAxis; //0x0070 
	float m_CapsuleLength; //0x0074 
	float m_CapsuleRadius; //0x0078 
	int m_pAimAssistTarget; //0x0080 
	unsigned char m_ValidInHiLod; //0x0088 
	unsigned char m_ValidInLowLod; //0x0089 
	unsigned char m_DeactivateIfBehindWall; //0x008A 
	unsigned char m_UsePhysicsRotation; //0x008B 
}; //0x0090

class SkeletonCollisionData
{
public:
	char pad_0000[8]; //0x0000
	class SkeletonAsset* m_pSkeletonAsset; //0x0008
	//vector<BoneCollisionData> m_BoneCollisionData; //0x000C
}; //Size: 0x0444

class BoneCollisionComponentData
{
public:
	char pad_0000[96]; //0x0000
	class SkeletonCollisionData* m_pSkeletonCollisionData; //0x0060

}; //0x0080

class MovementComponentData
{
public:
	char pad[0xD4];
	int m_ClientSidePhysicsControlled;
};

class ClientMovementComponent
{
public:
	//void __thiscall EntryInputState::setIsAuthoritativeMovementActive(EntryInputState *this, bool active)
	//{
	//	this->m_customBitFlags ^= (this->m_customBitFlags ^ -active) & 2;
	//}
	// return (this->m_customBitFlags & 2 | -(this->m_customBitFlags & 2)) >> 31;
	char pad_0000[8]; //0x0000
	class MovementComponentData* m_pMovementComponentData; //0x0008
	char pad_000C[28]; //0x000C
	class ClientSoldierEntity* m_pSoldier; //0x0028
	int m_State; //0x002C
	char pad_002D[7]; //0x002D
	int m_Move; //0x0034
	char pad_0035[11]; //0x0035
	Vector3 m_LastPos; //0x0040
	char pad_004C[40]; //0x004C
	class ClientAntAnimatableComponent* m_pClientAntAnimatableComponent; //0x0074
	char pad_0078[8]; //0x0078
	Vector3 m_LastPos2; //0x0080
	char pad_008C[4]; //0x008C
	Vector4 m_Velocity; //0x0090
};//Size=0x0440

class BreathControlData
{
public:
	char pad_0000[8]; //0x0000
	float m_breathControlTime; //0x0008
	float m_breathControlReleaseTime; //0x000C
	float m_breathControlPenaltyMultiplier; //0x0010
	float m_breathControlPenaltyTimeout; //0x0014
	char pad_0018[44]; //0x0018
}; //Size: 0x0044

class ClientSoldierBreathControlComponent
{
public:
	class BreathControlData* m_pBreathControlData; //0x0000
	float m_breathControlTimer; //0x0004
	float m_breathControlMultiplier; //0x0008
	float m_breathControlPenaltyTimer; //0x000C
	float m_breathControlPenaltyMultiplier; //0x0010
	int m_State; //0x0014 0 - no breath, 3 - breath hold, 2 - penalty
}; //Size: 0x0084

class ClientSoldierReplication
{
public:
	char pad_0000[16]; //0x0000
	Vector4 m_Position; //0x0010
	char pad_0020[584]; //0x0020
}; //Size: 0x0268

class ClientBoneCollisionComponent
{
public:
	char pad_0000[4]; //0x0000
	class BoneCollisionComponentData* m_pBoneCollisionComponentData; //0x0004
	char pad_0008[12]; //0x0008
	class BoneTransformInfo* m_boneCollisionTransforms; //0x0014
	char pad_0018[124]; //0x0018
	int m_collisionBoneCount; //0x0094
	int m_collisionEnabled; //0x0098
	int m_collisionUpdated; //0x0099
	char pad_009A[546]; //0x009A
}; //Size: 0x02BC

class ClientSoldierEntity//ClientMovementComponent 0xD50
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void computeBoundingBoxWorldTransform(Matrix *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	char pad_0004[12]; //0x0004
	class Components* m_pComponents; //0x0010
	class SoldierEntityData* m_pSoldierEntityData; //0x0014
	char pad_0018[132]; //0x0018
	float m_Health; //0x009C
	char pad_00A0[24]; //0x00A0
	class ClientPlayer* m_pPlayer; //0x00B8
	class ClientAntAnimatableComponent* m_pAntAnimatable1; //0x00BC
	class ClientAntAnimatableComponent* m_pAntAnimatable2; //0x00C0
	char pad_00C4[156]; //0x00C4
	float m_MaxHealth; //0x0160
	class CharacterPhysicsEntity* m_pCharacterPhysicsEntity; //0x0164
	char pad_0168[8]; //0x0168
	float yaw; //0x0170
	char pad_0174[4]; //0x0174
	float pitch; //0x0178
	char pad_017C[44]; //0x017C
	Vector2 m_ViewAngles; //0x01A8
	char pad_01B0[152]; //0x01B0
	class SoldierBlueprint* m_pSoldierBlueprint; //0x0248
	class ClientSoldierPrediction* m_pClientSoldierPrediction; //0x024C
	class ClientSoldierReplication* m_pClientSoldierReplication; //0x0250
	char pad_0254[24]; //0x0254
	class VeniceClientSoldierCameraComponent* m_pVeniceClientSoldierCameraComponent; //0x026C
	char pad_0270[68]; //0x0270
	float m_cachedPitch; //0x02B4
	char pad_02B8[8]; //0x02B8
	Matrix m_Transform; //0x02C0
	char pad_0300[4]; //0x0300
	int m_PoseType; //0x0304
	char m_pUnktry;
	char pad_0308[59]; //0x0308
	class N00004B4B* N00001E09; //0x0344
	char pad_0348[12]; //0x0348
	class BFClientSoldierHealthComponent* m_healthModule; //0x0354
	float m_deathTimer; //0x0358
	class ClientSoldierWeaponsComponent* m_pClientSoldierWeaponsComponent; //0x035C
	int ClientSoldierBodyComponent; //0x0360
	class ClientBoneCollisionComponent* m_pClientBoneCollisionComponent; //0x0364
	class ClientRagDollComponent* m_pClientRagdollComponent; //0x0368
	char pad_036C[4]; //0x036C
	class ClientSoldierBreathControlComponent* m_pBreathControlHandler; //0x0370
	class SprintInputHandler* m_pSprintInputHandler; //0x0374
	int m_sprintInterruptAction; //0x0378
	float m_timeSinceLastSprinted; //0x037C
	bool m_sprinting; //0x0380
	bool m_occluded; //0x0381
	char pad_0382[6]; //0x0382
	float m_criticalHealthThreshold; //0x0388
	char pad_038C[180]; //0x038C
	class ClientSpottingComponent* m_pClientSpottingComponent; //0x0440
	char pad_0444[12]; //0x0444
	class ClientSpottingTargetComponent* m_pClientSpottingTargetComponent; //0x0450
	char pad_0454[28]; //0x0454
	class ClientSoldierSuppressionComponent* m_pClientSoldierSuppressionComponent; //0x0470
	char pad_0474[28]; //0x0474
	class ClientDropWeaponComponent* m_pClientDropWeaponComponent; //0x0490
	char pad_0494[92]; //0x0494
	class ClientMovementComponent* m_pClientMovementComponent; //0x04F0

	bool Visible()
	{
		return !m_occluded;
	}
};

class ClientParachuteComponent
{
public:

	class AimingConstraints
	{
	public:
		float m_MinYaw; //0x0000 
		float m_MaxYaw; //0x0004 
		float m_MinPitch; //0x0008 
		float m_MaxPitch; //0x000C 
		float m_PitchOffset; //0x0010 
		float m_YawOffset; //0x0014 
		float m_MinYawDefault; //0x0018 
		float m_MaxYawDefault; //0x001C 
	};

	class ParachuteComponentData
	{
	public:
		char pad_0000[212]; //0x0000
		float m_UndeployTime; //0x00D4
		float m_AutoDeployInitialDelay; //0x00D8
		float m_AutoDeployGroundDistance; //0x00DC
		float m_AutoDeployMinGroundDistance; //0x00E0
		int m_AutoDeployEnabled; //0x00E4
		int m_AutoDeployOnceOnSpawnOnly; //0x00E5

	};

	char pad_0000[8]; //0x0000
	class ParachuteComponentData* m_pData; //0x0008
	char pad_000C[4]; //0x000C
	class ClientPlayerEntryComponent* m_pEntry; //0x0010
	char pad_0014[152]; //0x0014
	class ClientAntAnimatableComponent* m_pAnimatable; //0x00AC
	class CharacterPhysicsEntity* m_pPhysicsEntity; //0x00B0
	class AimingConstraints* m_pAimingContraints; //0x00B4
	char pad_00B8[72]; //0x00B8
	int m_State; //0x0100
	Vector2 m_View; //0x0104
	Vector2 m_DeltaView; //0x010C
	Vector2 m_AuthoratativeView; //0x0114
	int m_SoldierInParachute; //0x011C

	void Tweak()
	{
		if ((this->m_pAimingContraints))
		{
			this->m_pAimingContraints->m_MinYaw = -180.f;
			this->m_pAimingContraints->m_MaxYaw = 180.f;
			this->m_pAimingContraints->m_MinPitch = -180.f;
			this->m_pAimingContraints->m_MaxPitch = 180.f;
			this->m_pAimingContraints->m_MinYawDefault = -180.f;
			this->m_pAimingContraints->m_MaxYawDefault = 180.f;
		}

		if ((this->m_pData))
			this->m_pData->m_UndeployTime = 0.f;
	}

}; //Size = 0x0150  

class DynamicPhysicsEntity
{
public:
	char pad_0000[96]; //0x0000
	AxisAlignedBox m_rbAabb; //0x0060
	int bitSetMask; //0x0080
	int bitCount; //0x0084
	class Matrix* m_pGameWorldTransformBase; //0x0088
	class ClientPartComponent** m_pTransformNodes; //0x008C
	char pad_0090[8]; //0x0090
	class PhysicsEntityData* m_pPhysicsEntityData; //0x0098
	class HavokPhysicsData* m_pHavokPhysicsData; //0x009C

};//

enum VehicleBone
{
	VEH_Type99_Center = 8,
	VEH_T90_Center = 4,
	VEH_M1_Center = 4,
	VEH_Venom_Center = 9,
	VEH_AH1Z_Center = 3,
	VEH_Z10w_Center = 3,
	VEH_Z11w_Center = 8,
	VEH_KLR650_Center = 12,
	VEH_PGZ_Center = 12,
	VEH_RHIB_Center = 11,
	VEH_DV15_Center = 3,
	VEH_Z9_Center = 10,
	VEH_Thunder_Center = 13,
	VEH_Growler_Center = 4,
	VEH_Growler_Pilot = 7,
	VEH_LAV25_Center = 3,
	VEH_F35_Center = 14,
	VEH_F35_Pilot = 3,
	VEH_AH6_Pilot = 6,
	VEH_Fantan_Center = 14,
	VEH_LYT_Center = 14,
	VEH_LYT_Pilot = 7,
	VEH_ZBD_Center = 14,
	VEH_HIMARS_Center = 14,
	VEH_Buggy_Center = 4,
	VEH_MI28_Center = 4,
	VEH_FA_Pilot = 7,
	VEH_FA_Center = 13,
	VEH_9K22_Center = 13,
	VEH_Kasatka_Center = 4,
	VEH_SU25_Center = 1,
	VEH_PWC_Center = 4,
	VEH_KKC617_Pilot = 9,
	VEH_BTR_Center = 13,
	VEH_Hover_Center = 4,
	VEH_Hover_Pilot = 6,
	VEH_7A1_Center = 4,
	VEH_MRAP_Center = 4,
	VEH_Quad_Center = 8,
	VEH_Quad_Pilot = 12,
	VEH_TOW2_Center = 10,
	VEH_GunShield_Center = 12,
	VEH_DPV_Center = 12,
	VEH_DPV_Pilot = 13,
};

class VehicleEntityData
{
public:
	char pad_0000[96]; //0x0000
	class PhysicsEntityData* m_pPhysicsEntityData; //0x0060
	char pad_0064[112]; //0x0064
	char* m_VehicleName; //0x00D4
	char pad_00D8[200]; //0x00D8
	char* m_VehicleUnlockAssetName; //0x01A0
}; //Size: 0x0144

class VehicleHealthZoneData
{
public:
	float m_maxHealth; //0x0000
	float m_maxShieldHealth; //0x0004
	float m_damageAngleMultiplier; //0x0008
	float m_minDamageAngle; //0x000C
	int m_useDamageAngleCalculation; //0x0010
	char pad_0014[48]; //0x0014
}; //Size: 0x0044

class VehicleEntityHealthZone // //vector<VehicleEntityHealthZone>
{
public:
	class VehicleHealthZoneData* m_pVehicleHealthZoneData; //0x0000
	float health; //0x0004
	float shieldHealth; //0x0008
	int useProtectedShields; //0x000C
	char pad_000D[2]; //0x000D
	int N00001B88; //0x000F
	char pad_0010[52]; //0x0010
}; //Size: 0x0044

class ClientVehicleHealthComponent
{
public:
	char pad_0000[20]; //0x0000
	class VehicleEntityHealthZone* m_healthZones; //0x0014
	char pad_0018[1324]; //0x0018
}; //Size: 0x0544

class ClientChassisComponent
{
public:
	char pad_0000[4]; //0x0000
	class ChassisComponentData* m_pChassisComponentData; //0x0004
	char pad_0008[8]; //0x0008
	class DynamicPhysicsEntity* m_pDynamicPhysicsEntity; //0x0010
	char pad_0014[204]; //0x0014
	AxisAlignedBox m_cachedBox; //0x00E0
	Vector4 m_linearVelocity; //0x0100
	Vector4 m_angularVelocity; //0x0110
	Vector4 m_prevLinearVelocity; //0x0120
	char pad_0130[20]; //0x0130
	Vector4 position; //0x0144
	char pad_0154[316]; //0x0154
	float m_gForce; //0x0290
	char pad_0294[496]; //0x0294
}; //Size: 0x0484

class PhysicsEntity
{
public:
	virtual ~PhysicsEntity();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1 // V: 0x0
	virtual void listenToParentChanges(void);//2 // V: 0x4
	virtual bool isPropertyChangedAllowed(void);//3 // V: 0x8
	virtual void _event(/*EntityEvent const *)*/);//4 // V: 0x0c
	virtual void editEvent(/*DataUpdateEvent const **/);//5 // V: 0x10
	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6 // V: 0x14
	virtual void getPeerBus(void);//7  // V: 0x18
	virtual void getPeerData(void);//8  V: 0x1c
	virtual void computeWorldTransform(LinearTransform &);//9 0x24
	virtual void getPeerSubBus(void);//10 0x28
	virtual void getRecordingData(/*EntityRecordingData **/);//11  0x2c
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//12 0x30
	virtual void onDestroy(void);//13 0x34
	virtual void Function14(); //14  0x38
	virtual void onSaveCreate(/*SaveOutStream &*/); //15 0x3c
	virtual void onInit(/*EntityInitInfo &*/); //16 0x40
	virtual void onSaveInit(/*SaveOutStream &*/);  //17  0x44
	virtual void onDeinit(/*EntityDeinitInfo &*/); //18 0x48
	virtual void getTransform(Matrix *);//19 - 0x54
	virtual void setTransform(Matrix *);//20 - 58 
	virtual void computeBoundingBoxWorldTransform(Matrix *); // 21V: 0x5c
	virtual void computeBoundingBox(AxisAlignedBox *); // V: 0x60 22
	virtual void Dummy(); // 23V: 0x5c
	virtual void Dummy1(); // V: 0x60 24

	virtual void visualCullScreenArea(void); // V: 0x68 25
	virtual void onHiddenToggled(bool); // V: 0x6C 26
	virtual void spawn(LinearTransform const *, void *, bool);//27- 0x70 
	virtual void needPrePhysicsUpdate(void); // V: 0x74 28
	virtual void prePhysicsUpdate(void*); // V: 0x78 29
	virtual void prePhysicsQuery(void*); // V: 0x7c 30
	virtual void needPostPhysicsUpdate(void); // V: 0x80 31
	virtual void postPhysicsUpdate(void*); // V: 0x84  32
	virtual void postPhysicsQuery(void*); // V: 0x88  33
	virtual void needPostFrameUpdate(void); // V: 0x8c  34
	virtual void postFrameUpdate(void*); // V: 0x90  35
	virtual void postFrameQuery(void*); // V: 0x94  36
	virtual void needFrameInterpolationUpdate(void); // V: 0x98  37
	virtual void frameInterpolationUpdate(void*); // V: 0x9c  38
	virtual void frameInterpolationQuery(void*); // V: 0x100  39
	virtual void onSpawn(LPVOID);//(GameEntity::SpawnInfo const &);  40
	virtual void onUnSpawn(LPVOID);//(GameEntity::UnSpawnInfo const &);  41 
	virtual void onDeinit1(LPVOID);//(GameEntity::GameEntityDeinitInfo &); 42
	virtual void worldTransformChanged(LinearTransform const &, bool); //43
																		   //virtual void onComponentWorldTransformDirty(void); //44
																		   //virtual void onComponentUpdateRequiredChanged(void); //45
																		   //virtual void onComponentLocalBoundingBoxDirty(void); //46
	virtual void createUpdater(LPVOID);//(UpdatePass); //44
	virtual void getUpdaters(void); //45
	virtual void meshModel(void); //46
	virtual void visualUpdate(float deltaTime);//fn 47 - 0xCC 
	virtual void Function48(); //
	virtual void fb__SoldierToComponentsInitializedMessage(); //

	virtual float mass(); //
	virtual void Function51(); //
	virtual float invMass(); //
	virtual const Vector3 &linearVelocity();//virtual void Function54(); // velocity
	virtual DWORD Function55(); //
	virtual DWORD Function56(); //
	virtual DWORD Function57(); //
	virtual DWORD onCollision(); //
	virtual DWORD Function59(); //
	virtual DWORD Function60(); //
	virtual DWORD Function61(); //
	virtual DWORD Function62(); //
	virtual DWORD Function63(); //
	virtual DWORD Function64(); //
	virtual DWORD Function65(); //
	virtual DWORD flgetHealth(); //
	virtual DWORD flgetMaxHealth(); //
	virtual DWORD entryInputstate(); //
	virtual DWORD Function69(); //
	virtual DWORD Function70(); //
	virtual DWORD fb__ClientSoldierEntity__postPhysicsUpdateEntry(); //
	virtual DWORD Function72(); //
	virtual ClientControllableEntity *onPlayerEntersControllable(); //
	virtual void UnlockComponentData(void);// ClientControllableEntity *onPlayerExitssControllable(); //
	virtual DWORD Function75(); //
	virtual DWORD Function76(); //
	virtual DWORD Function77(); //
	virtual DWORD Function78(); //
	virtual DWORD Function79(); //
	virtual DWORD Function80(); //
	virtual DWORD Function81(); //
	virtual DWORD Function82(); //
	virtual DWORD Function83(); //
	virtual DWORD ClientPlayer__applyCustomization(); //
	virtual void Function84(); //
	virtual void ClientPlayerKilledMessage();
	virtual void nullsub_6444(); //
	virtual void Function88(); //
	virtual void Function89(); //
	virtual void Function90(); //
	virtual void Function91(); //
	virtual DWORD InputState__getIsDown(); //
	virtual void Function93(); //
	virtual void Function94(); //
	virtual bool somebool(); //
	virtual void SoldierHealthModuleGS__writeGS(); //
	virtual void Function95(); //
	virtual DWORD Clientgamecontexplus16(); //
	virtual int Function98(); //
	virtual int Function99();

};

class ClientVehicleEntity
{
public:
	virtual TypeInfo* getType();
	virtual void propertyChanged(/*PropertyModificationListener::PropertyModification const &*/);//1
	virtual void listenToParentChanges(void);//2
	virtual bool isPropertyChangedAllowed(void);//3
	virtual void _event(/*EntityEvent const *)*/);//4
	virtual void editEvent(/*DataUpdateEvent const **/);//5
															//	virtual void getDebugName(/*StringBuilderBase &,bool*/);//6
	virtual void getPeerBus(void);//7
	virtual void getPeerData(void);//8
								   //	virtual void func9();//
	virtual void computeWorldTransform(LinearTransform &);//10
	virtual void getPeerSubBus(void);//11
	virtual void getRecordingData(/*EntityRecordingData **/);//12
	virtual void onCreate(/*EntityBusPeerCreationInfo &*/);//13
	virtual void onDestroy(void);//14
	virtual void Function15();
	virtual void onSaveCreate(/*SaveOutStream &*/);
	virtual void onInit(/*EntityInitInfo &*/);
	virtual void onSaveInit(/*SaveOutStream &*/);
	virtual void onDeinit(/*EntityDeinitInfo &*/);
	virtual void onDeinitNotAllowed(/*EntityDeinitInfo &*/);
	virtual void onInitOwnedEntity(/*EntityInitInfo &,Entity **/);
	virtual void getTransform(Matrix*);//22 - 0x58
	virtual void setTransform(Matrix *);//23 - 5C
	virtual void computeBoundingBoxWorldTransform(LinearTransform *);
	virtual AxisAlignedBox* computeBoundingBox(AxisAlignedBox *);
	virtual void visualCullScreenArea(void);
	virtual void onHiddenToggled(bool);
	virtual void spawn(LinearTransform const *, void *, bool);//28 - 0x70
	virtual void needPrePhysicsUpdate(void);
	virtual void prePhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void prePhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostPhysicsUpdate(void);
	virtual void postPhysicsUpdate(/*EntityUpdateInfo const &*/);
	virtual void postPhysicsQuery(/*EntityUpdateInfo const &*/);
	virtual void needPostFrameUpdate(void);
	virtual void postFrameUpdate(/*EntityUpdateInfo const &*/);
	virtual void postFrameQuery(/*EntityUpdateInfo const &*/);
	virtual void needFrameInterpolationUpdate(void);
	virtual void frameInterpolationUpdate(/*EntityUpdateInfo const &*/);
	virtual void frameInterpolationQuery(/*EntityUpdateInfo const &*/);
	virtual void onSpawn(/*GameEntity::SpawnInfo const &*/);
	virtual void onUnSpawn(/*GameEntity::UnSpawnInfo const &*/);
	virtual void onDeinit1(/*GameEntity::GameEntityDeinitInfo &*/);
	virtual void worldTransformChanged(LinearTransform const &, bool);
	virtual void onComponentWorldTransformDirty(void);
	virtual void onComponentUpdateRequiredChanged(void);
	virtual void onComponentLocalBoundingBoxDirty(void);
	virtual void createUpdater(/*UpdatePass*/);
	virtual void getUpdaters(void);
	virtual void meshModel(void);
	virtual void visualUpdate(float deltaTime);//fn 51 - 0xCC

	PhysicsEntity * m_pPhysicsEntity;
	char pad_0004[8]; //0x0004
	class Components* m_pComponents; //0x0010
	class VehicleEntityData* m_pVehicleEntityData; //0x0014
	char pad_0018[224]; //0x0018
	class DynamicPhysicsEntity* m_pDynamicPhysicsEntity; //0x00F8
	float m_waterLevel; //0x00FC
	float m_terrainLevel; //0x0100
	float m_waterLevelUpdateTimer; //0x0104
	float m_terrainLevelUpdateTime; //0x0108
	char pad_010C[4]; //0x010C
	AxisAlignedBox N00001131; //0x0110
	char pad_0130[16]; //0x0130
	Vector4 m_vehicleSpeed; //0x0140
	Vector4 m_prevVelocity; //0x0150
	float m_prevDeltaTime; //0x0160
	char pad_0164[152]; //0x0164
	class ClientChassisComponent* m_pClientChassisComponent; //0x01FC
	class ClientVehicleHealthComponent* m_vehicleHealth; //0x0200
	WeakPtr<ClientPlayer> m_GadgetOwner; //0x0204

};

class ClientPlayerView
{
public:
	char pad_0000[172]; //0x0000
	class ClientPlayer* m_Owner; //0x00AC
	char pad_00B0[64]; //0x00B0
	Vector3 m_Position; //0x00F0
	char pad_00FC[20]; //0x00FC
	Vector3 m_HitPosition; //0x0110
	char pad_011C[4]; //0x011C
	float m_Damage; //0x0120
	char pad_0124[40]; //0x0124
	float m_HealthLeft; //0x014C
	char pad_0150[80]; //0x0150

};//Size=

class ClientPlayer
{
public:
	virtual ~ClientPlayer();
	virtual SoldierEntity* getSoldier();// 
	virtual EntryComponent * getEntry(ClientPlayer*);  //
	virtual bool isInVehicle(); //
	virtual unsigned int getId(); //
	virtual bool isUnlocked(const class UnlockAssetBase *);  //

	char pad_0004[4]; //0x0004
	class PlayerData* m_pPlayerData; //0x0008
	char pad_000C[4]; //0x000C
	char* m_Name; //0x0010
	char pad_0014[20]; //0x0014
	char szName[20]; //0x0028
	char pad_003C[84]; //0x003C
	class VeniceSoldierCustomizationAsset* m_pSelectedCustomizationAsset; //0x0090
	char pad_0094[48]; //0x0094
	class UnlockAssetBase* m_pSpecialization; //0x00C4
	char pad_00C8[596]; //0x00C8
	int m_teamId; //0x031C
	char pad_0320[164]; //0x0320
	WeakPtr<ClientSoldierEntity> m_Corpse; //0x0EDC
	WeakPtr<ClientSoldierEntity> m_Soldier; //0x03C8
	WeakPtr<ClientPlayer> m_Player; //0x03CC
	class ClientVehicleEntity* m_pAttachedControllable; //0x03D0
	int m_AttachedEntryId; //0x03D4
	class ClientSoldierEntity* m_pControlledControllable; //0x03D8
	int m_ControlledEntryId; //0x03DC
	class EntryInputState* m_pInputState; //0x03E0
	class EntryInputState* m_pExternalInputState; //0x03E4
	char pad_03E8[28]; //0x03E8
	class ClientPlayerManager* m_pClientPlayerManager; //0x0404
	class ClientPlayerView* m_pOwnPlayerView; //0x0408
	class ClientPlayerView* m_pPlayerView; //0x040C
	char pad_0410[95]; //0x0410
	bool m_SquadId; //0x046F
	bool m_IsSquadLeader; //0x0470
	bool m_SquadClosed; //0x0471
	bool m_isAllowedToSpawnOn; //0x0472
	bool m_reviveAllowed; //0x0473
	char pad_0474[28]; //0x0474
	char m_FakeName[20]; //0x0490

	ClientSoldierEntity* GetClientSoldier()
	{
		__try
		{

			ClientSoldierEntity* Return = m_pControlledControllable;

			if (!MmIsAddressValidPtr(Return))
				return NULL;

			return	Return;
		}
		__except (1)
		{
			return nullptr;
		}
	}

	ClientVehicleEntity* GetClientVehicleEntity()
	{
		if (this->isInVehicle())
			return (ClientVehicleEntity*)m_pAttachedControllable;

		return NULL;
	}

};//Size=0x2440

class ClientPlayerScore
{
public:
	char pad_0x0000[0x148]; //0x0000
	int m_Rank; //0x0x148
	int m_Kills; //0x014C 
	int m_Deaths; //0x0150 
	int m_ScoreMultiplier; //0x0154 
	int m_Score; //0x0158
	int m_GlobalScoreOriginal; //0x015C 
	int m_GlobalScoreUpdated; //0x0160 
	float m_Time; //0x0164

};//Size=0x0440

class ClientVenicePersistenceManager
{
public:
	char pad_0000[12]; //0x0000
	class ClientPlayerScoreManager* m_pScoreManager; //0x000C

	static ClientVenicePersistenceManager* GetInstance()
	{
		//return *(ClientVenicePersistenceManager**)OFFSET_ClientVenicePersistenceManager;
	}
};//Size=0x0440

class ClientPlayerScoreManager
{
public:
	ClientPlayerScore * getScore(ClientPlayer *player)
	{
		typedef ClientPlayerScore* (__thiscall *tgetPlayerScore)(ClientPlayerScoreManager*, ClientPlayer *player);
		//tgetPlayerScore getPlayerScore = (tgetPlayerScore)OFFSET_GETPLAYERSCORE;
		//return getPlayerScore(this, player);
	}

};//Size=0x0080

class ClientPlayerManager
{
public:
	virtual ~ClientPlayerManager();
	//virtual //vector<ClientPlayer*>* getPlayers();//D0
	//virtual //vector<ClientPlayer*>* getSpectators();

	class PlayerData* m_pPlayerData; //0x0004
	int m_MaxPlayersCount; //0x0008
	char pad_000C[176]; //0x000C
	class ClientPlayer* m_pLocalPlayer; //0x00BC
	class ClientPlayer** m_ppPlayers; //0x00C0
};

class TypeInfoData
{
public:
	const char *name; //0x0
	unsigned short flags; //0x4
	unsigned short totalSize; //0x6
	void *module; //0x8
	unsigned char alignment; //0xC
	unsigned char fieldCount; //0xD
	unsigned char pad[2]; //0xE
};

enum ChatChannelType
{
	CctSayAll,                     // constant 0x0
	CctTeam,                     // constant 0x1
	CctSquad,                     // constant 0x2
	CctSquadLeader,                     // constant 0x3
	CctAdmin,                     // constant 0x4
	CctGame,                     // constant 0x5
}; // ChatChannelType

class TypeInfo
{
public:

	TypeInfoData * m_infoData;
	TypeInfo *m_pNext; //0x4
	unsigned short m_runtimeId; //0x8
	unsigned short m_flags; //0xA

	TypeInfoData *getTypeInfoData() {
		return (TypeInfoData *)m_infoData;
	}
};

class Material
{
public:
	enum MaterialFlag
	{
		MFSeeThrough = 0x1,
		MFClientDestructable = 0x40000000,
		MFPenetrable = 0x8
	};
	int m_flagsAndIndex;
	__forceinline bool isPenetrable()
	{
		return (m_flagsAndIndex & MFPenetrable);
	};
	__forceinline bool isSeeThrough()
	{
		return (m_flagsAndIndex & MFSeeThrough);
	};
};
class RayCastHit
{
public:
	Vector4  m_position; //0x0000
	Vector4 m_normal;    //0x0010
	void*  m_RigidBody; // 0x20
	Material m_Material;  // 0x28
	DWORD  m_Part;   // 0x30
	FLOAT  m_Lambda;  // 0x34
};

class IPhysicsRayCaster
{
public:
	enum RayCastFlags
	{
		NoCheck = 0x0,
		CheckDetailMesh = 0x1,
		IsAsyncRaycast = 0x2,
		DontCheckWater = 0x4,
		DontCheckTerrain = 0x8,
		DontCheckRagdoll = 0x10,
		DontCheckCharacter = 0x20,
		DontCheckGroup = 0x40,
		DontCheckPhantoms = 0x80,
		FORCE32BIT = 0x7FFFFFFF,
		AimbotFlags = (0x4 | 0x10 | 0x20 | 0x80)
	};
	virtual bool physicsRayQuery(char* text, Vector4 *from, Vector4 *to, RayCastHit *hit, int flag, void* PhysicsEntityList);
	virtual struct SafeQueryResult* asyncPhysicsRayQuery(const char *ident, Vector4 *from, Vector4 *to, unsigned int flags, void* excluded);

};
class EntityIterator;
class EntityCollection;
class RemovedEntityInfo;
class SpatialSize;

enum Realm
{
	Realm_Client,
	Realm_Server,
	Realm_ClientAndServer,
	Realm_None,
	Realm_Pipeline,
};



class EntityCreator
{
public:
	enum RayCastTest
	{
		RCTDetailed = 0,
		RCTCollision
	};
	LPVOID vftable;						// 0x00
	EntityCreator* m_previousCreator;	// 0x04
	EntityCreator* m_nextCreator;		// 0x08
	Realm m_realm;						// 0x0C
	INT m_linked;						// 0x10
}; // 0x14

class ITypedObject
{
public:
	virtual TypeInfo * getType(); //v-00
}; // 0x04


class PropertyModificationListener
	: public ITypedObject			// 0x00
{
	//new crashes when parsing through propmodlistener put back later i
	/*	class PropertyModification
	{
	int name;                     // 0x0
	void * value;                     // 0x4
	}; // PropertyModification
	*/
}; // 0x04


class EntityBusPeer
	: public PropertyModificationListener		// 0x00
{		//new
		//			virtual class fb::EntityBus * getPeerBus();	// V: 0x1C
		//			virtual const class fb::GameObjectData * getPeerData();	// V: 0x20
		//			virtual void * __vecDelDtor(unsigned int);	// V: 0x24

}; // 0x04

class SupportsWeakPtr // Inherited class at offset 0x4
{
}; // fb::SupportsWeakPtr

class ClientExplosionPackEntity;
class ClientGameEntity;
class GameEntity;
class SpatialEntity;
class Entity : public EntityBusPeer, SupportsWeakPtr			// 0x00
{
public:
	DWORD m_weakTokenHolder;		// 0x04
	DWORD m_flags;					// 0x08
}; // 0x0C

class DataContainer
	: public ITypedObject		// 0x00
{
public:
	WORD m_refCnt;				// 0x04
	WORD m_flags;				// 0x06
}; // 0x08


class GameDataContainer
	: public DataContainer			// 0x00
{
}; // 0x08

class GameObjectData
	: public GameDataContainer				// 0x00
{
public:
	WORD m_indexInBlueprint;				// 0x08
	BYTE m_isEventConnectionTarget;			// 0x0A
	BYTE m_isPropertyConnectionTarget;		// 0x0B
											//String m_name;  
}; // 0x0C


class EntityData
	: public GameObjectData					// 0x00
{
}; // 0xC

class SpatialEntityData
	: public EntityData				// 0x00
{
public:
	PAD(0x4);						// 0x0C
	LinearTransform m_transform;	// 0x10
}; // 0x50/ 0x08

class GameEntityData
	: public SpatialEntityData				// 0x00
{
public:
	char* m_name;//	RefArray<GameObjectData> m_components;	// 0x50
	BYTE m_enabled;							// 0x54
	BYTE m_runtimeComponentCount;			// 0x55
	PAD(0xA);								// 0x56

											//unsigned char m_runtimeComponentCount;               // 0x75	
											//class fb::Array<fb::WeaponStateData> m_weaponStates; // 0x80
											//enum fb::WeaponClassEnum m_weaponClass;              // 0x84

}; // 0x60


class SpatialEntity
	: public Entity				// 0x00
{
public:
	virtual ~SpatialEntity();
	virtual void propertyChanged(/*fb::PropertyModificationListener::PropertyModification const &*/);//1 // V: 0x0
	virtual void listenToParentChanges(void);//2 // V: 0x4
	virtual bool isPropertyChangedAllowed(void);//3 // V: 0x8
	virtual void _event(/*fb::EntityEvent const *)*/);//4 // V: 0x0c
	virtual void editEvent(/*fb::DataUpdateEvent const **/);//5 // V: 0x10
	virtual void getDebugName(/*fb::StringBuilderBase &,bool*/);//6 // V: 0x14
	virtual void getPeerBus(void);//7  // V: 0x18
	virtual void getPeerData(void);//8  V: 0x1c
	virtual void computeWorldTransform(LinearTransform &);//9 0x24
	virtual void getPeerSubBus(void);//10 0x28
	virtual void getRecordingData(/*fb::EntityRecordingData **/);//11  0x2c
	virtual void onCreate(/*fb::EntityBusPeerCreationInfo &*/);//12 0x30
	virtual void onDestroy(void);//13 0x34
	virtual void Function14(); //14  0x38
	virtual void onSaveCreate(/*fb::SaveOutStream &*/); //15 0x3c
	virtual void onInit(/*fb::EntityInitInfo &*/); //16 0x40
	virtual void onSaveInit(/*fb::SaveOutStream &*/);  //17  0x44
	virtual void onDeinit(/*fb::EntityDeinitInfo &*/); //18 0x48
	virtual void getTransform(LinearTransform &);//19 - 0x54
	virtual void setTransform(LinearTransform const &);//20 - 58 
	virtual void computeBoundingBoxWorldTransform(); // 21V: 0x5c
	virtual void computeBoundingBox(); // V: 0x60 22
	virtual void Dummy(); // 23V: 0x5c
	virtual void Dummy1(); // V: 0x60 24

	virtual void visualCullScreenArea(void); // V: 0x68 25
	virtual void onHiddenToggled(bool); // V: 0x6C 26
	virtual void spawn();//27- 0x70 
	virtual void needPrePhysicsUpdate(void); // V: 0x74 28
	virtual void prePhysicsUpdate(); // V: 0x78 29
	virtual void prePhysicsQuery(); // V: 0x7c 30
	virtual void needPostPhysicsUpdate(void); // V: 0x80 31
	virtual void postPhysicsUpdate(); // V: 0x84  32
	virtual void postPhysicsQuery(); // V: 0x88  33
	virtual void needPostFrameUpdate(void); // V: 0x8c  34
	virtual void postFrameUpdate(); // V: 0x90  35
	virtual void postFrameQuery(); // V: 0x94  36
	virtual void needFrameInterpolationUpdate(void); // V: 0x98  37
	virtual void frameInterpolationUpdate(); // V: 0x9c  38
	virtual void frameInterpolationQuery(); // V: 0x100  39
	virtual void onSpawn(LPVOID);//(fb::GameEntity::SpawnInfo const &);  40
	virtual void onUnSpawn(LPVOID);//(fb::GameEntity::UnSpawnInfo const &);  41 
	virtual void onDeinit1(LPVOID);//(fb::GameEntity::GameEntityDeinitInfo &); 42
	virtual void worldTransformChanged(); //43
	//virtual void onComponentWorldTransformDirty(void); //44
	//virtual void onComponentUpdateRequiredChanged(void); //45
	//virtual void onComponentLocalBoundingBoxDirty(void); //46
	virtual void createUpdater(LPVOID);//(fb::UpdatePass); //44
	virtual void getUpdaters(void); //45
	virtual void meshModel(void); //46
	virtual void visualUpdate(float deltaTime);//fn 47 - 0xCC 
	virtual void Function48(); //
	virtual void fb__SoldierToComponentsInitializedMessage(); //

	virtual float mass(); //
	virtual void Function51(); //
	virtual float invMass(); //
	virtual const Vector3 &linearVelocity();//virtual void Function54(); // velocity
	virtual DWORD Function55(); //
	virtual DWORD Function56(); //
	virtual DWORD Function57(); //
	virtual DWORD onCollision(); //
	virtual DWORD Function59(); //
	virtual DWORD Function60(); //
	virtual DWORD Function61(); //
	virtual DWORD Function62(); //
	virtual DWORD Function63(); //
	virtual DWORD Function64(); //
	virtual DWORD Function65(); //
	virtual DWORD flgetHealth(); //
	virtual DWORD flgetMaxHealth(); //
	virtual DWORD entryInputstate(); //
	virtual DWORD Function69(); //
	virtual DWORD Function70(); //
	virtual DWORD fb__ClientSoldierEntity__postPhysicsUpdateEntry(); //
	virtual DWORD Function72(); //
	virtual ClientControllableEntity *onPlayerEntersControllable(); //
	virtual void UnlockComponentData(void);// ClientControllableEntity *onPlayerExitssControllable(); //
	virtual DWORD Function75(); //
	virtual DWORD Function76(); //
	virtual DWORD Function77(); //
	virtual DWORD Function78(); //
	virtual DWORD Function79(); //
	virtual DWORD Function80(); //
	virtual DWORD Function81(); //
	virtual DWORD Function82(); //
	virtual DWORD Function83(); //
	virtual DWORD ClientPlayer__applyCustomization(); //
	virtual void Function84(); //
	virtual void ClientPlayerKilledMessage();
	virtual void nullsub_6444(); //
	virtual void Function88(); //
	virtual void Function89(); //
	virtual void Function90(); //
	virtual void Function91(); //
	virtual DWORD InputState__getIsDown(); //
	virtual void Function93(); //
	virtual void Function94(); //
	virtual bool somebool(); //
	virtual void SoldierHealthModuleGS__writeGS(); //
	virtual void Function95(); //
	virtual DWORD Clientgamecontexplus16(); //
	virtual int Function98(); //
	virtual int Function99();


	DWORD m_cullGridId;                    // 0x0C

}; // 0x10

class EntityBus
{
public:
	LPVOID vftable;							// 0x00
	void* m_subLevel;					// 0x04
	EntityBus* m_parentBus;					// 0x08
	INT m_dataId;							// 0x0C
	INT m_refCount;							// 0x10
	INT m_networkId;						// 0x14
	SHORT m_realm;							// 0x18
	CHAR m_parentPropertiesCanChange;		// 0x1A
											//	PAD(0x1);								// 0x1B
}; // 0x1C



template <class T>
class SpatialEntityWithBusAndData
	: public SpatialEntity				// 0x00
{
public:
	EntityBus * m_entityBus;				// 0x10
	T* m_data;							// 0x14

}; // 0x18


class GameEntity
	: public SpatialEntityWithBusAndData<GameEntityData>	// 0x00
{
public:
	DWORD m_updateInterval;									// 0x18
	int* m_collection;						// 0x1C


	//LinearTransform * m_worldTransform;                     // 0x1C
}; // 0x20

class ClientGameEntity
	: public GameEntity		// 0x00
{
public:
	bool visulUpdate(float deltatime)
	{
		typedef bool(__thiscall* R_visualUpdate)(ClientGameEntity *pThis, float deltatime);
		R_visualUpdate m_visualUpdate = (R_visualUpdate)0x01100610;

		return m_visualUpdate(this, deltatime);
	}
}; // 0x20

class ClientExplosionPackEntity
	: public ClientGameEntity
{
public:
	PAD(0x290);
	// 	ClientExplosionPackState m_state; // this+0x288
	//	float m_spottedTime;              // this+0x28C
	int m_teamId;                     // this+0x290
	int m_damageGiverPlayerId;        // this+0x294
	bool m_isSpotted;                 // this+0x298
};

class ClientSupplySphereEntity
	:public ClientExplosionPackEntity
{
public:
};


class EntityWorld
{
public:
	class SpatialSize
	{
	public:
		FLOAT halfSizeXZ;	// 0x00
		FLOAT minY;			// 0x04
	}; // 0x08

	class RemovedEntityInfo
	{
	public:
		Entity * entity;				// 0x00
		LPVOID func;				// 0x04
		EntityCreator* creator;		// 0x08
		LPVOID userData;			// 0x0C
	}; // 0x10

	class EntityCollection
	{
	public:
		EntityCollectionSegment * firstSegment;	// 0x00
		EntityCreator* creator;					// 0x04
	}; // 0x08

	class EntityIterator
	{
	public:
		eastl::vector<EntityWorld::EntityCollection>* m_collections;    //offset = 0x0, length = 0x4
		EntityCollectionSegment* m_currentSegment;    //offset = 0x4, length = 0x4
		unsigned int m_collectionIndexIt;    //offset = 0x8, length = 0x4
		unsigned int m_collectionIndexEnd;    //offset = 0xC, length = 0x4
		unsigned int m_entityIndexIt;    //offset = 0x10, length = 0x4
		unsigned int m_entityIndexEnd;    //offset = 0x14, length = 0x4
		byte m_onlyIncludeIterable;    //offset = 0x18, length = 0x1
		char pad_19[3];
	};

	void kindOfQuery(int* typeId, EntityWorld::EntityIterator* result, bool onlyIncludeIterable = true)
	{
		typedef void(__thiscall* kindOfQuery_t)(EntityWorld*, int*, EntityWorld::EntityIterator*, bool);

		kindOfQuery_t m_kindOfQuery = (kindOfQuery_t)0x551790;//0x551790;

		m_kindOfQuery(this, typeId, result, onlyIncludeIterable);
	}

	virtual void addSpatialEntity(int *);	// V: 0x0
	virtual void removeSpatialEntity(int *);	// V: 0x4
	virtual void updateSpatialEntity(int *);	// V: 0x8

														//LPVOID vftable;														// 0x00
	SpatialSize m_spatialSize;											// 0x04
	eastl::fixed_vector<RemovedEntityInfo, 128, 2> m_removedEntities;	// 0x0C
	eastl::vector<EntityCollection> m_collections;						// 0x820
	SubLevel* m_rootLevel;												// 0x830
	WORD m_entityRuntimeId;												// 0x834
	PAD(0x2);															// 0x836
	CHAR m_isDeletingAllEntities;										// 0x838
	CHAR m_isLoadingSaveGame;											// 0x839
	PAD(0x2);															// 0x83A
}; // 0x840

class GameWorld : public EntityWorld, public IPhysicsRayCaster
{
public:
	int m_spatialQueryManager;	// 0x844 SpatialQueryManager*
	void* m_physicsManager;// 0x848 IPhysicsManager*
	int m_terrainHeightFunc;		// 0x84C
	int m_hasTerrainFunc;		// 0x850
	int m_terrainMaterial;		// 0x854
	int m_getSoldierFunc;		// 0x858
};

class ExplosionEntityData
{
public:
	void* m_DetonationEffect; //+0x60 EffectBlueprint
	void* m_DetonationEffectForFriendlies; //+0x68 EffectBlueprint
	void* m_MaskVolume; //+0x70 MaskVolumeEntityData
	void* m_DestructionMaskVolume; //+0x78 DestructionMaskVolumeEntityData
	int m_MaterialPair; //+0x80
	int m_SecondaryMaterialPair; //+0x84
	int m_DamageIndicationType; //+0x88
	float m_EmpTime; //+0x8C
	float m_MaxOcclusionRaycastRadius; //+0x90
	float m_InnerBlastRadius; //+0x94
	float m_BlastDamage; //+0x98
	float m_BlastRadius; //+0x9C
	float m_BlastImpulse; //+0xA0
	float m_ShockwaveDamage; //+0xA4
	float m_ShockwaveRadius; //+0xA8
	float m_ShockwaveImpulse; //+0xAC
	float m_ShockwaveTime; //+0xB0
	float m_CameraShockwaveRadius; //+0xB4
	float m_SpawnDelay; //+0xB8
	bool m_NoFriendliesEffectOnEnabledFriendlyFire; //+0xBC
	bool m_UseEntityTransformForDetonationEffect; //+0xBD
	bool m_SecondaryMaterialsActive; //+0xBE
	bool m_HasStunEffect; //+0xBF
	bool m_DisableOcclusion; //+0xC0
	bool m_DisableStaticEntityOcclusion; //+0xC1
	bool m_TriggerImpairedHearing; //+0xC2
	bool m_Enabled; //+0xC3
};


enum HitReactionType
{
	HRT_Body,
	HRT_Head,
	HRT_RightArm,
	HRT_LeftArm,
	HRT_RightLeg,
	HRT_LeftLeg,
	HRT_Count,
};

class ClientDamageStream
{
public:

	class DamageData
	{
	public:
		int victimPlayerId; //0x0000
		int victimInstanceId; //0x0004 Health+0x168
		int inflictorPlayerId; //0x0008
		int hitType; //0x000C
		class UnlockAssetBase* weaponUnlockAsset; //0x0010
		char pad_0014[12]; //0x0014
		Vector4 direction; //0x0020
		float damage; //0x0030
		int clientAiKilled; //0x0034
		char pad_0035[3]; //0x0035
		int dw38; //0x0038
		int dw3c; //0x003C
		int id; //0x0040
	};//Size=0x0440

	virtual bool OnWriteDamageEvents(PVOID lpBitStreamWrite);    // V: 0x0 
	virtual bool OnReadDamageEvents(PVOID lpBitStreamRead); // V: 0x8 return true stub 
	virtual void OnProcessDamageEvents();    // V: 0x10 return false stub 
	virtual bool OnEventsToSend();    // V: 0x18 

	class DamageData* m_pDamageData; //0x0004


}; //Size = 0x0100

class TransmissionRecord
{
public:
	class ITransmissionRecord // Inherited class at offset 0x0
	{
	public:

	}; // network::ITransmissionRecord

	unsigned int sequenceNumber;                     // this+0x0

}; // TransmissionRecord

class EntryInputStateNetworkMove
{
public:
	char pad[0x8];
	EntryInputState m_EntryInput;
}; // EntryInputStateNetworkMove

class StreamManagerMoveClient
{
public:
	intptr_t vtable; //0x0000
	char pad_0004[12]; //0x0004
	int m_moves; //0x0010

}; // network::StreamManagerMoveClient



class ClientPeer
{
public:
	char pad_0000[0x2FE4]; //0x0000
	int* m_ChatManager; //0x2FE4
}; //Size: 0x3844

class OnlineManager
{
public:

	char pad_0000[0x14]; //0x0000
	class ClientPeer* m_pClientPeer; //0x0014
	class ClientConnection* m_pClientConnection; //0x0018

};



class MaterialContainerPair
	//	: public DataContainer			// 0x00
{
public:
	DWORD m_flagsAndIndex;			// 0x08
	int m_physicsPropertyIndex;	// 0x0C
	int m_physicsMaterialIndex;	// 0x0D
									//	PAD(0x2);						// 0x0E
}; // 0x10



class EntityCollectionSegment
{
public:
	eastl::vector<Entity *> m_Collection;
	void * m_subLevel; // 0x10
	EntityCollectionSegment * m_prev; // 0x14
	EntityCollectionSegment * m_next; // 0x18
	DWORD m_iterableSize; // 0x1C
	DWORD m_collectionIndex; // 0x20
};



class Asset
	: public DataContainer	// 0x00
{
public:
	const char* m_name;			// 0x08
}; // 0x0C


class PropertyConnection
{
public:
	DataContainer * m_source;		// 0x00
	DataContainer* m_target;		// 0x04
	INT m_sourceFieldId;			// 0x08
	INT m_targetFieldId;			// 0x0C
}; // 0x10

class LinkConnection
	: public PropertyConnection		// 0x00
{
}; // 0x10




class SubLevel
{
public:
	LPVOID vftable;											// 0x00
	eastl::vector<EntityCollectionSegment*> m_segments;		// 0x04
	eastl::vector<UINT> m_deletedEntities;					// 0x14
	DWORD* m_subLevelData;								// 0x24
	SubLevel* m_parent;										// 0x28
	SubLevel* m_child;										// 0x2C
	SubLevel* m_sibling;									// 0x30
	DWORD* m_arena;									// 0x34
	DWORD m_compartment;						// 0x38
	Realm m_realm;											// 0x3C
	INT m_refCount;											// 0x40
	BYTE m_isDestroyed;										// 0x44
	PAD(3);									// 0x45
}; // 0x48



class ClientGameContext
{
public:
	int m_MessageManager; //0x0000
	char pad_0004[0x8]; //0x0004
	class GameTime* m_pGameTime; //0x000C
	class Level* m_pLevel; //0x0010
	char pad_0014[0x14]; //0x0014
	class N00000D31* N0000001D; //0x0028
	char pad_002C[0x4]; //0x002C
	class ClientPlayerManager* m_pClientPlayerManager; //0x0030
	class OnlineManager* m_pOnlineManager; //0x0034
	class ClientGameView* m_pGameView; //0x0038
	char pad_003C[0x4]; //0x003C
	class ClientPlayerScoreManager* m_pClientScoreManager; //0x0040


	static ClientGameContext* GetInstance()
	{
		return *(ClientGameContext**)(0x84122028);
	}
};

class SyncedBFSettings
{
public:

	bool m_unk0; //0x0 
	bool m_unk1; //0x01 
	bool m_unk2; //0x02
	bool m_unk3; //0x03  
	bool m_unk4; //0x04 
	bool m_unk5; //0x05 
	bool m_unk6; //0x06  
	bool m_unk7; //0x07 
	bool m_unk8; //0x08 
	bool m_unk9; //0x09  
	bool m_unkA; //0x0A 
	bool m_unkB; //0x0B
	bool m_unkC; //0x0C
	bool m_unkD; //0x0D  
	bool m_unkE; //0x0E
	bool m_unkF; //0x0F 
	bool m_noMinimapSpottingActual; //0x10 
	bool m_unk11; //0x11  
	bool m_noHud; //0x12 
	bool m_noMinimapSpotting; //0x13 
	bool m_no3dSpotting; //0x14  
	bool m_noNameTag; //0x15
	bool m_onlySquadLeaderSpawn; //0x16
	bool m_TeamSwitchAllowed; //0x17
	bool m_unk18; //0x18 
	bool m_unk19; //0x19  
	bool m_unk20; //0x20 




	static SyncedBFSettings* GetInstance()
	{
		return *(SyncedBFSettings**)(0x8412FAA0);
	}
};

class GameTime
{
public:
	int m_ticks; //0x0000
	int m_tickFrequency; //0x0004
	int m_tickIndexInFrame; //0x0008
	int m_lastTickIndexInFrame; //0x000C
	int m_tickCountInFrame; //0x0010
	float m_deltaTime; //0x0014
	char pad_0018[36]; //0x0018
	float m_passedDeltaTimeInFrame; //0x003C
	char pad_0040[8]; //0x0040
}; //Size: 0x0048


class Client
{
public:
	char pad[12];
	ClientGameContext* m_gameContext; //0x000C  
	void* m_gameSettings; //0x0010  
	void* m_clientSettings; //0x0014  
	char pad1[4];
	ClientPlayerManager* m_playerManager; //0x001C  
	void* m_destructionManager; //0x0020 WeakPtr<ClientDestructionManager>
								//  ScopedPtr<ClientGameView> m_gameView;
	WeakPtr<ClientGameView>* m_gameView; //0x0024 ClientGameView 
	void* m_fileSystem; //0x0028 VirtualFileSystem 
	GameTime* m_gameTime; //0x002C  
	BorderInputNode* m_inputNode; //0x0030 //Shown as InputNode but holds BorderInputNode
	void* m_rumble; //0x0034 Rumble 
					//class SmartRef<ClientLevel> m_level; 
	Level* m_level; //0x0038  
	void * m_ui; //0x003C IUISystem 
	void* m_uiSystem; //0x0040 enum UISystemType 
	void * m_socketManagerFactory; //0x0044 ISocketManagerFactory 
	void* m_interpolationManager; //0x0048 network::InterpolationManager 
	WeakPtr<void*> m_inputTimer; //0x004C Timer2 
	WeakPtr<void*> m_timeDemo; //0x0050 TimeDemoBase 
	char pad2[252];
	int m_state; //0x0150 enum ClientState 
	char pad3[132];
	int m_gameType; //0x01D8  
	int m_quit; //0x01DC  
	int m_wantsToQuit; //0x01DD  
	int m_pauseOnStartup; //0x01DE  
	int m_keepResources; //0x01DF  
	int m_shouldConnectToServer; //0x01E0  
	int m_startServerLocal; //0x01E1  
	int m_startServerInCoop; //0x01E2  
	int m_consoleClient; //0x01E3  
	int m_threadedWinProc; //0x01E4  
	int m_inSimulationUpdate; //0x01E5  
	int m_mayPerformStateChange; //0x01E6  
	int _unused; //0x01E7  
	void * m_clientCallbacks;  //0x01E8 
	char pad4[132];
	float m_visualFrameUpdateTime; //0x01F0  
	char pad5[12];

	int m_readyForAutoSpawn; //0x0200  
	int m_debugAutoSpawnWaitForControllable; //0x0201  
	char pad6[2];
	__int32 m_autoSpawnFailCount; //0x0204  
	void* m_debugFramePrmiitive; //0x0208 SmartRef<IDebugRenderPrimitive> 
	void* m_clientNetSwitboard; //0x020C ClientNetSwitchboard 
	DWORD m_pendingBundleOp; //0x0210 AsyncResultHandle 

};

class Main
{
public:
	char pad001[0xA0];
	bool m_isDedicatedServer;
	bool m_isDedicatedServerData;
	bool m_isPaused;
	int _Main_unused_1;
	void* m_fileLogHandler;
	void* m_debugRendererLogHandler;
	void* m_demoControl;
	void* m_server;
	Client* m_client; // this+0xD4
	char pad002[0x7C];
	unsigned int m_buildId;                     // this+0x154
	const char * m_buildTime;                     // this+0x158
	char pad003[0xC];
	void* m_juiceScreenshotModule; // 0x168
	bool m_createdOk;
	bool m_playerHasEntered;
	int m_quitHelper;
	int m_settingsManagerService;

	static Main* GetInstance()
	{
		//return *(Main**)(OFFSET_MAIN);
	}
};
class BulletHitInfo
{
public:
	Vector3 m_Direction; //0x0000 
	char pad_0x000C[0x4]; //0x000C
	Vector3 m_SpawnPosition; //0x0010 
	char pad_0x001C[0x4]; //0x001C
	Vector3 m_HitPosition; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	UnlockAssetBase* m_WeaponUnlockAsset; //0x0030 
	__int32 m_WeaponType; //0x0038 
	__int32 m_BoneType; //0x003C 
	__int32 m_ShooterPlayerId; //0x0040 
	unsigned char m_ShooterIsAIPlayer; //0x0044 

};//Size=0x0080

struct TransformAABBStruct
{
	Matrix Transform;
	AxisAlignedBox AABB;

	TransformAABBStruct()
	{}
};

struct ScreenshotStatus
{
	bool enable;
	bool firstFrame;
	bool autoRenderEnable;
	bool multiRes;
	Vector2 viewportOffset;
};

class ScreenshotCroppingParams
{
public:
	int width; //0x0000  
	int height; //0x0004  
	int left; //0x0008  
	int top; //0x000C  
	int right; //0x0010  
	int bottom; //0x0014  
};//Size=0x0018(24)

class ScreenshotParams
{
public:
	int source; //0x0000 enum ScreenshotSource 
	const char* explicitFilename; //0x0004  
	char _ScreenshotParams_string_data[12]; //0x0008  
	ScreenshotCroppingParams croppingParams; //0x0014  
	int resolutionMultiplier; //0x002C  
	int antialiasMultiplier; //0x0030  
	int format; //0x0034 enum ScreenshotFormat 
	bool alphaEnable; //0x0038  
	bool orthoEnable; //0x0039  
	char _ScreenshotParams_skipped_0[2]; //0x003A  
	void* callbacks; //0x003C IScreenshotCallback 
};//Size=0x0040(64)
class ScreenshotModule
{
public:
	char _ScreenshotModule_skip_0[8];		//0x0000  
	int m_delayFrame;						//0x0008 
	int m_resolutionFrameIndex;			//0x000C  
	int m_antialiasFrameIndex;			//0x0010  
	int m_lineCount;					//0x0014  
	const char* m_tempPath;					//0x0018  
	const char* m_outputPath;				//0x001C  
	char _ScreenshotModule_skipped_1[12];	//0x0024  
	int m_counter;						//0x002C
	ScreenshotParams m_params;			//0x0030  
	void* m_stagingTexture;					//0x0070 DxTexture 
	char _ScreenshotModule_skipped_2[160];	//0x0074  
	ScreenshotStatus m_status;			//0x0114  

	static ScreenshotModule* Singleton()
	{
		//return *(ScreenshotModule**)OFFSET_SSMODULE;
	}
};


class InputCache
{
public:
	char pad_0x0000[4];
	float flInputBuffer[123];
	float m_juiceConceptCache[123];                     // 0x1F0
	float m_prevJuiceConceptCache[123];                     // 0x3DC
	void* m_recordData;                     // 0x5C8
	void* m_replayData;                     // 0x5CC
};

class VeniceSoldierCustomizationAsset
{
public:
	char pad_0000[8]; //0x0000
	char* m_name; //0x0008
	char* m_ID_Name; //0x000C
	char pad_0010[8]; //0x0010
	class CustomizationTable* m_pUnlocksTable1; //0x0018
	class CustomizationTable* m_pUnlocksTable2; //0x001C
	class CustomizationTable* m_pUnlocksTable3; //0x0020

};//Size=0x0040
class WeaponCustomization
{
public:
	UnlockAssetBase * m_Optics; //0x0000 []
	UnlockAssetBase* m_Rail; //0x0008 []
	UnlockAssetBase* m_Barrel; //0x0010 []
	UnlockAssetBase* m_Grip; //0x0018 []
	UnlockAssetBase* m_Camo; //0x0020 []
};//Size=0x0440

class ClientCharacterSpawnEntity
{
public:

};

class KeyboardDevice
{
public:
	virtual void Function0(); // 0x0000 
	virtual void Read(float SampleTime, bool VisualFrame); //0x0008  
	virtual const char* Name(unsigned int); //0x0010  
	virtual const char* Name(void); // 0x0018  
	virtual unsigned int ControlCount(); // 0x0020  
	virtual bool IsConnected(); // 0x0028 
	virtual bool IsAnalogue(unsigned int); // 0x0030 
	virtual float GetValue(unsigned int);    // 0x0038 

	char pad_0004[88]; //0x0004
	int m_HWND; //0x005C
	void* m_pWindowProcedure; //0x0060
	int m_Current; //0x0064
}; //Size: 0x0444

class Keyboard
{
public:
	char pad_0000[4]; //0x0000
	class KeyboardDevice* m_pDevice; //0x0004
	char pad_0008[1084]; //0x0008
}; //Size: 0x0444

class MouseState
{
public:
	int X; //0x0000
	int Y; //0x0004
	int Z; //0x0008
	char m_Buttons[8]; //0x000C
}; //Size: 0x0016

class MouseDevice
{
public:
	virtual void Function0(); // 0x0000 
	virtual void Read(float SampleTime, bool VisualFrame); //0x0008  
	virtual const char* Name(void); //0x0010  
	virtual const char* Name(unsigned int); // 0x0018  
	virtual unsigned int ControlCount(); // 0x0020  
	virtual bool IsConnected(); // 0x0028 
	virtual bool IsAnalogue(unsigned int); // 0x0030 
	virtual float GetValue(unsigned int);    // 0x0038 

	char pad_0004[88]; //0x0004
	int m_HWND; //0x005C
	void* m_pWindowProcedure; //0x0060
	char pad_0064[20]; //0x0064
	int m_CursorMode; //0x0078
	int m_UIOwnsInput; //0x0079
	int m_ShowCursor; //0x007A
	int m_CursorConfined; //0x007B
	int m_HasOverflowed; //0x007C
	int m_UseRawMouseInput; //0x007D
	int m_WindowActive; //0x007E
	char pad_007F[25]; //0x007F
	MouseState m_Current; //0x0098
	MouseState m_Buffer; //0x00AE

}; //Size: 0x0468

class Mouse
{
public:
	virtual void init();	// V: 0x0
	virtual void release();	// V: 0x4
	virtual void preFrameUpdate(float);	// V: 0x8
	virtual void update(float);	// V: 0xC
	virtual void updateBetweenFrames(float);	// V: 0x10
	virtual bool isDown(void*, bool);	// V: 0x14
	virtual bool wentDown(void*);	// V: 0x18
	virtual bool wentUp(void*);	// V: 0x1C
	virtual float getLevel(void*, bool);	// V: 0x20
	virtual float getLevel(void*);	// V: 0x24
	virtual bool getBufferedAction(void*);	// V: 0x28
	virtual void enableCursorMode(bool, int);	// V: 0x2C
	virtual void setCursorPosition(int, int);	// V: 0x30
	virtual void setCursorRect(bool, unsigned int, unsigned int, unsigned int, unsigned int);	// V: 0x34
	virtual void setMouseSensitivity(float);	// V: 0x38
	virtual void setUIOwnsInput(bool);	// V: 0x3C

	char pad_0000[4]; //0x0000
	class MouseDevice* m_pDevice; //0x0008
	char pad_000C[56]; //0x000C
}; //Size: 0x0044

class BorderInputNode
{
public:
	virtual void init();
	virtual void exit();
	virtual void clear();
	virtual void suppressButtons(); // V: 0x10
	virtual float getLevel(InputConceptIdentifiers, bool);        // V: 0x14
	virtual float getLevel2(void  *, bool); // V: 0x18 class InputActions
	virtual bool isDown(enum InputConceptIdentifiers, bool);   // V: 0x1C
	virtual bool isDown2(void*, bool);    // V: 0x20
	virtual bool wentDown(enum InputConceptIdentifiers);       // V: 0x24
	virtual bool wentDown2(void *);        // V: 0x28
	virtual bool wentUp(InputConceptIdentifiers); // V: 0x2C
	virtual bool wentUp2(void *);  // V: 0x30
	virtual bool isMouseActive();   // V: 0x34
	virtual void * getPad();      // V: 0x38
	virtual class MotionController *getMotionController();    // V: 0x3C
	virtual class Mouse * getMouse(); // V: 0x40
	virtual Keyboard * getKeyboard();   // V: 0x44
	virtual void setUIInputTyping(bool);    // V: 0x48
	virtual void setUIInputClicking(bool, int);     // V: 0x4C
	virtual void setUICursorPosition(int, int);     // V: 0x50
	virtual void setUICursorRect(bool, unsigned int, unsigned int, unsigned int, unsigned int);     // V: 0x54
	virtual void updateBetweenFrames(float);        // V: 0x58
	virtual /*class InputActionData **/void* getTriggeredInputAction(); // V: 0x5C
	virtual bool getTriggeredInputAction(/*class InputActionData &*/void*);     // V: 0x60
	virtual void update(float);     // V: 0x64
	virtual int preFrameUpdate(float fDeltaTime);
	//virtual void postFrameUpdate(float);	
	virtual void postFrameUpdate(float);	// V: 0x6C

	char unknown0[4];
	InputCache* m_inputCache;
	//new
	bool m_forceReadCache;                     // 0x8
	char pad[0x3];
	void * m_pad;								 // 0xC
	MotionController * m_motionController;      // 0x10
	Keyboard *m_keyboard;                     // 0x14
	Mouse * m_mouse;                     // 0x18
	int m_disableInput;                     // 0x1C
	int m_mouseActive;                     // 0x1D
	char pad2[0x2];
	void * m_defaultInputConceptDefinition;  // 0x20
	int m_ps3EnterOnCircle;                     // 0x24

	static BorderInputNode* GetInstance()
	{
		//return *(BorderInputNode**)(OFFSET_BORDERINPUTNODE);
	}
};





class CustomizationUnlockParts
{
public:
	char pad_0004[4]; //0x0004
	char* m_UICategorySid; //0x0008
	class UnlockAssetBase** m_SelectableUnlocks; //0x000C
	char pad_0010[16]; //0x0010

	virtual TypeInfo* GetType();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0020

class TeamData
{
public:
	char pad_0000[8]; //0x0000
	char* m_TeamName; //0x0008
	class SoldierBlueprint* m_pSoldierBlueprint; //0x000C
	char pad_0010[52]; //0x0010
}; //Size: 0x0044

class Message
{
public:

	intptr_t m_pVtable;//0
	DWORD m_Category;//4
	DWORD m_Type;//8
};

class NetworkableMessage : public Message
{
public:
	char _0x000c[0x34 - sizeof(Message)];
};

class Color32
{
public:
	union
	{
		struct
		{
			int R;
			int G;
			int B;
			int A;
		};
		DWORD dwColor;
	};

public:
	Color32(const DWORD _Color)
	{
		dwColor = _Color;
	}
	Color32()
	{
		A = 0, R = 0, G = 0, B = 0;
	}

	static Color32 White()
	{
		return Color32(255, 255, 255, 255);
	}

	static Color32 Black()
	{
		return Color32(0, 0, 0, 255);
	}

	static Color32 Red()
	{
		return Color32(255, 0, 0, 255);
	}

	static Color32 Green()
	{
		return Color32(0, 255, 0, 255);
	}

	static Color32 Blue()
	{
		return Color32(0, 0, 255, 255);
	}

	static Color32 Orange()
	{
		return Color32(255, 255, 0, 255);
	}


	static Color32 Gray()
	{
		return Color32(119, 136, 153, 255);
	}

	Color32(const int Red, const int Green, const int Blue, const int Alpha)
	{
		A = Alpha;
		R = Red;
		G = Green;
		B = Blue;
	}
	//operator Color() const { return Color(A, R, G, B);	}
};

class GColor
{
public:
	enum StandardColors
	{
		Black = 0x0,
		White = 0xFFFFFF,
		VeryLightGray = 0xE0E0E0,
		LightGray = 0xC0C0C0,
		Gray = 0x808080,
		DarkGray = 0x404040,
		VeryDarkGray = 0x202020,
		Red = 0xFF0000,
		LightRed = 0xFF8080,
		DarkRed = 0x800000,
		VeryDarkRed = 0x400000,
		Green = 0xFF00,
		LightGreen = 0x80FF80,
		DarkGreen = 0x8000,
		VeryDarkGreen = 0x4000,
		Blue = 0xFF,
		LightBlue = 0x8080FF,
		DarkBlue = 0x80,
		VeryDarkBlue = 0x40,
		Cyan = 0xFFFF,
		LightCyan = 0x80FFFF,
		DarkCyan = 0x8080,
		Magenta = 0xFF00FF,
		LightMagenta = 0xFF80FF,
		DarkMagenta = 0x800080,
		Yellow = 0xFFFF00,
		LightYellow = 0xFFFF80,
		DarkYellow = 0x808000,
		Purple = 0xFF00FF,
		DarkPurple = 0x800080,
		Pink = 0xFFC0C0,
		DarkPink = 0xC08080,
		Beige = 0xFFC080,
		LightBeige = 0xFFE0C0,
		DarkBeige = 0xC08040,
		Orange = 0xFF8000,
		Brown = 0x804000,
		LightBrown = 0xC06000,
		DarkBrown = 0x402000
	};
	enum StandardAlphas
	{
		Alpha0 = 0x0,
		Alpha25 = 0x40000000,
		Alpha50 = 0x7F000000,
		Alpha75 = 0xFFFFFFFFBF000000,
		Alpha100 = 0xFFFFFFFFFF000000
	};

	struct Rgb24
	{
		unsigned char Blue; // Offset = this + 0x0 Length = 0x1
		unsigned char Green; // Offset = this + 0x1 Length = 0x1
		unsigned char Red; // Offset = this + 0x2 Length = 0x1
	};
	struct Rgb32
	{
		unsigned char Blue; // Offset = this + 0x0 Length = 0x1
		unsigned char Green; // Offset = this + 0x1 Length = 0x1
		unsigned char Red; // Offset = this + 0x2 Length = 0x1
		unsigned char Alpha; // Offset = this + 0x3 Length = 0x1
	};


	GColor::Rgb32  Channels; // Offset = this + 0x0 Length = 0x4
	unsigned long Raw; // Offset = this + 0x0 Length = 0x4
};

class ChatMessage
{
public:

	wchar_t  m_string; // Offset = this + 0x0 Length = 0x10C
	unsigned int m_playerId; // Offset = this + 0x10C Length = 0x4
	double m_recipientMask; // Offset = this + 0x110 Length = 0x8
	unsigned int m_channelId; // Offset = this + 0x118 Length = 0x4
	bool m_senderIsDead; // Offset = this + 0x11C Length = 0x1
};


typedef struct
{
	char pad0000[0xC];
	wchar_t  m_string[128]; // Offset = this + 0x0 Length = 0x10C
	unsigned int m_playerId; // Offset = this + 0x10C Length = 0x4
	double m_recipientMask; // Offset = this + 0x110 Length = 0x8
	unsigned int m_channelId; // Offset = this + 0x118 Length = 0x4
	bool m_senderIsDead; // Offset = this + 0x11C Length = 0x1


}chatmessage_t;


class UIHud
{
public:
	char pad001[0x24];
	class Color32  m_currentTextColor; // Offset = this + 0x24 Length = 0x10
	char pad002[0x5];
	bool m_bCreateNewText; // Offset = this + 0x39 Length = 0x1
	char pad003[0x70];
	int m_text; // Offset = this + 0xB0
};

class ClientConnection//+0x68f8 - EntryInputState
{
public:
	char pad_0000[0x2E2C]; //0x2E2C
	class StreamManagerChat* m_pChatManager; //0x2E2C
	char pad_0001[0x10];
	class ClientDamageStream* m_pDamageStream; //0x2E40

};


class GString
{
public:
	enum FlagConstants
	{
		Flag_LengthIsSizeShift = 0x1F
	};
	enum HeapType
	{
		HT_Global = 0x0,
		HT_Local = 0x1,
		HT_Dynamic = 0x2,
		HT_Mask = 0x3
	};

	struct DataDesc
	{

		unsigned int Size; // Offset = this + 0x0 Length = 0x4
		long RefCount; // Offset = this + 0x4 Length = 0x4
	};
	union DataDescUnion
	{
		GString::DataDesc* pData; // Offset = this + 0x0 Length = 0x4
		unsigned int HeapTypeBits; // Offset = this + 0x0 Length = 0x4
	};
	struct NoConstructor
	{
	};
	struct InitStruct
	{
		virtual void dtor();
		virtual void InitString();	//TODO: Pure Function, update params from non-abstract derived class!

	};
	struct NoCaseKey
	{

		GString* pStr; // Offset = this + 0x0 Length = 0x4
	};
	struct HashFunctor
	{

	};
	struct NoCaseHashFunctor
	{

	};


	GString::DataDesc* pData; // Offset = this + 0x0 Length = 0x4
	unsigned int HeapTypeBits; // Offset = this + 0x0 Length = 0x4
};
class GFxDrawText
{
public:
	enum FontStyle
	{
		Normal = 0x0,
		Bold = 0x1,
		Italic = 0x2,
		BoldItalic = 0x3,
		ItalicBold = 0x3
	};
	enum Alignment
	{
		Align_Left = 0x0,
		Align_Default = 0x0,
		Align_Right = 0x1,
		Align_Center = 0x2,
		Align_Justify = 0x3
	};
	enum VAlignment
	{
		VAlign_Top = 0x0,
		VAlign_Default = 0x0,
		VAlign_Center = 0x1,
		VAlign_Bottom = 0x2
	};
	enum AAMode
	{
		AA_Animation = 0x0,
		AA_Readability = 0x1
	};
	enum FilterType
	{
		Filter_Unknown = 0x0,
		Filter_DropShadow = 0x1,
		Filter_Blur = 0x2,
		Filter_Glow = 0x3
	};
	enum FilterFlagsType
	{
		FilterFlag_KnockOut = 0x20,
		FilterFlag_HideObject = 0x40,
		FilterFlag_FineBlur = 0x80
	};


};

class GFxDrawTextManager
{
public:
	struct TextParams
	{

		int  TextColor; // Offset = this + 0x0 Length = 0x4
		int  HAlignment; // Offset = this + 0x4 Length = 0x4
		int   VAlignment; // Offset = this + 0x8 Length = 0x4
		int  FontStyle; // Offset = this + 0xC Length = 0x4
		float FontSize; // Offset = this + 0x10 Length = 0x4
		int  FontName; // Offset = this + 0x14 Length = 0x4
		bool Underline; // Offset = this + 0x18 Length = 0x1
		bool Multiline; // Offset = this + 0x19 Length = 0x1
		bool WordWrap; // Offset = this + 0x1A Length = 0x1
		int Leading; // Offset = this + 0x1C Length = 0x4
		int Indent; // Offset = this + 0x20 Length = 0x4
		unsigned int LeftMargin; // Offset = this + 0x24 Length = 0x4
		unsigned int RightMargin; // Offset = this + 0x28 Length = 0x4
	};

	char pad001[0xC];
	GFxDrawTextManagerImpl* GFxDrawTextManagerImplImpl; // Offset = this + 0xC Length = 0x4

};


class GFxDrawTextManagerImpl
{
public:
	enum
	{
		RTFlags_BeginDisplayInvoked = 0x1
	};
	char pad001[0x1C0];
	GFxDrawTextManager::TextParams  DefaultTextParams; // Offset = this + 0x1C0 Length = 0x2C

};



class _NetworkableMessage
{
public:
	virtual TypeInfo* GetType();
};