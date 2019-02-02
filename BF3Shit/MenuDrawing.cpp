#include "main.h"


//bool worldToScreenCalculated(Vector3 vWorldLocationVec3, Vector3* vOut)
//{
//	int height = 720;
//	int width = 1280;
//	float aspect = (float)width / (float)height;
//
//
//	GameRenderer* renderer = GameRenderer::Singleton();
//
//	if (renderer == NULL)
//		return false;
//
//	
//
//	D3DXVECTOR3 vOrigin = D3DXVECTOR3(renderer->m_viewParams.firstPersonTransform.data[3][0], renderer->m_viewParams.firstPersonTransform.data[3][1], renderer->m_viewParams.firstPersonTransform.data[3][2]);
//	D3DXVECTOR3  vLeft = D3DXVECTOR3(renderer->m_viewParams.firstPersonTransform.data[0][0], renderer->m_viewParams.firstPersonTransform.data[0][1], renderer->m_viewParams.firstPersonTransform.data[0][2]);
//	D3DXVECTOR3 vUp = D3DXVECTOR3(renderer->m_viewParams.firstPersonTransform.data[1][0], renderer->m_viewParams.firstPersonTransform.data[1][1], renderer->m_viewParams.firstPersonTransform.data[1][2]);
//	D3DXVECTOR3 vForward = D3DXVECTOR3(renderer->m_viewParams.firstPersonTransform.data[2][0], renderer->m_viewParams.firstPersonTransform.data[2][1], renderer->m_viewParams.firstPersonTransform.data[2][2]);
//
//	D3DXMATRIX viewMatrix;
//	D3DXMatrixIdentity(&viewMatrix);
//	viewMatrix._11 = vLeft.x; viewMatrix._12 = vUp.x; viewMatrix._13 = vForward.x;
//	viewMatrix._21 = vLeft.y; viewMatrix._22 = vUp.y; viewMatrix._23 = vForward.y;
//	viewMatrix._31 = vLeft.z; viewMatrix._32 = vUp.z; viewMatrix._33 = vForward.z;
//
//	viewMatrix._41 = -D3DXVec3Dot(&vOrigin, &vLeft);
//	viewMatrix._42 = -D3DXVec3Dot(&vOrigin, &vUp);
//	viewMatrix._43 = -D3DXVec3Dot(&vOrigin, &vForward);
//
//	D3DXMATRIXA16 Proj;
//	D3DXMatrixPerspectiveFovRH(&Proj, renderer->m_viewParams.view.m_desc.fovY, aspect, 0.1f, 10000.0f);
//	D3DXMATRIXA16 viewProjectionMatrix = viewMatrix * Proj;
//
//	float mX = width * 0.5f;
//	float mY = height * 0.5f;
//
//	float w =
//		viewProjectionMatrix(0, 3) * vWorldLocationVec3.x +
//		viewProjectionMatrix(1, 3) * vWorldLocationVec3.y +
//		viewProjectionMatrix(2, 3) * vWorldLocationVec3.z +
//		viewProjectionMatrix(3, 3);
//
//	if (w < 0.65f)
//	{
//		vOut->z = w;
//
//		return false;
//	}
//
//	float x =
//		viewProjectionMatrix(0, 0) * vWorldLocationVec3.x +
//		viewProjectionMatrix(1, 0) * vWorldLocationVec3.y +
//		viewProjectionMatrix(2, 0) * vWorldLocationVec3.z +
//		viewProjectionMatrix(3, 0);
//
//	float y =
//		viewProjectionMatrix(0, 1) * vWorldLocationVec3.x +
//		viewProjectionMatrix(1, 1) * vWorldLocationVec3.y +
//		viewProjectionMatrix(2, 1) * vWorldLocationVec3.z +
//		viewProjectionMatrix(3, 1);
//
//	vOut->x = mX + mX * x / w;
//	vOut->y = mY - mY * y / w;
//	vOut->z = w;
//
//
//
//	return true;
//}

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#define POINTERCHK( pointer ) ( pointer  && pointer !=0  && HIWORD( pointer ) )

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

Vector4 White = Vector4(1, 1, 1, 1);
Vector4 Red = Vector4(1, 0, 0, 1);
Vector4 MenuColor = Vector4(0, 0.94901960784, 1, 1);
Vector4 Blue = Vector4(0, 0.94901960784, 1, 1);

Vector4 MenuToggleOptionCoords = Vector4(90 + 250, 0, 340, 140.0f + 55 - 10);
Vector4 MenuOptionCoords = Vector4(90, 0, 505, 140.0f + 55 - 10);
Vector4 TitleCoords = Vector4(90, 0, 505, 140.0f + 25);
Vector4 MenuTitleCoords = Vector4(90, 0, 505, 140.0f);
Vector4 MenuInstructions = Vector4(50, 680, 505, 700);
Vector4 InstructionsWhiteLines = Vector4(1, 1, 1, 0.6);
Vector4 InstructionsBackGround = Vector4(0, 0, 0, 0.4);

int(*g_snprintf)(char* _Dest, size_t Count, const char* _Format, ...) = (int(*)(char* _Dest, size_t Count, const char* _Format, ...))0x835376B8;

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

Vector3 Origin = Vector3(13.977393, 92.163528, 533.447266);
//

void SetDraw()
{
	GameRenderer* renderer = GameRenderer::Singleton();

	if (renderer == NULL)
		return;

	D3DXVECTOR3 vOrigin = D3DXVECTOR3(renderer->m_viewParams.firstPersonTransform.data[3][0], renderer->m_viewParams.firstPersonTransform.data[3][1], renderer->m_viewParams.firstPersonTransform.data[3][2]);

	GameRenderer::Singleton()->m_viewParams.view.Update();
	Vector3 vecMySoldierPosition = GameRenderer::Singleton()->m_viewParams.view.m_viewMatrixInverse.trans;

	Origin = Vector3(vOrigin.x, vOrigin.y, vOrigin.z);
}

void DrawMenu()
{
	Vector4 BackGround = Vector4(0, 0, 0, 0.5);

	if (MenuBase.isMenuOpened)
	{





		Vector3 Coords;

		if (WorldToScreen(Origin, &Coords))
		{

			printf("%f %f\n", Coords.x, Coords.y);

			DrawText("My previous Origin", Coords.x, Coords.y, 1, 0xffffffff, 0);

			DrawLine(1280 / 2, 720 / 2, Coords.x, Coords.y, 1, 0xffffffff);

		}

		Drawing.DrawRect(70.0f, 120.0f, 280.0f, 100.0f + (MenuBase.OptionCount[MenuBase.CurrentSubMenu] * 17.65f), &BackGround);
		Drawing.DrawBorderBox(69.0f, 119.0f, 281.0f, 101.0f + (MenuBase.OptionCount[MenuBase.CurrentSubMenu] * 17.65f), 1, &Blue);

		Drawing.DrawText("xbOnline Menu", 0.70, &MenuTitleCoords, &Blue);
		Drawing.DrawText(MenuBase.SubTitles[MenuBase.CurrentSubMenu].c_str(), 0.60, &TitleCoords, &White);

		for (int i = 0; i < MenuBase.MaxScroll[MenuBase.CurrentSubMenu]; i++)
		{
			char OptionText[255] = { 0 };

			bool isSelected = i == MenuBase.CurrentScroll[MenuBase.CurrentSubMenu];

			float yOffset = (((i + 1.0f) * 15.0f));

			Vector4 cToggle = MenuToggleOptionCoords;
			cToggle.a = cToggle.a + yOffset;

			Vector4 Coords = MenuOptionCoords;
			Coords.a = Coords.a + yOffset;

			g_snprintf(OptionText, 255, (isSelected ? " %s" : "%s"), MenuBase.SubMenuText[MenuBase.CurrentSubMenu][i].c_str());

			Drawing.DrawText(OptionText, 0.60, &Coords, isSelected ? &MenuColor : &White, 0, 0, 0, 2);

			switch (MenuBase.OptionKind[MenuBase.CurrentSubMenu][i])
			{
			case TYPE_FLOAT:
			case TYPE_FLOAT_CALL:
				g_snprintf(OptionText, 255, (isSelected ? "< %.2f >" : "%.2f"), *MenuBase.floatValue[MenuBase.CurrentSubMenu][i]);
				Drawing.DrawText(OptionText, 0.60, &cToggle, isSelected ? &MenuColor : &White, 0, 0, 1, 2);
				break;
			case TYPE_INT:
			case TYPE_INT_CALL:
				g_snprintf(OptionText, 255, (isSelected ? "< %i >" : "%i"), *MenuBase.IntValue[MenuBase.CurrentSubMenu][i]);
				Drawing.DrawText(OptionText, 0.60, &cToggle, isSelected ? &MenuColor : &White, 0, 0, 1, 2);
				break;
			case TYPE_BOOL:
			case TYPE_BOOL_CALL:
				Drawing.DrawText(*MenuBase.BoolValue[MenuBase.CurrentSubMenu][i] ? (isSelected ? "< On >" : "On") : (isSelected ? "< Off >" : "Off"), 0.60, &cToggle, isSelected ? &MenuColor : &White, 0, 0, 1, 2);
				break;
			case TYPE_LISTBOX_CALL:
			case TYPE_LISTBOX:
				g_snprintf(OptionText, 255, (isSelected ? "< %s >" : "%s"), MenuBase.ListBox[MenuBase.CurrentSubMenu][i][*MenuBase.ListBoxPosition[MenuBase.CurrentSubMenu][i]]);
				Drawing.DrawText(OptionText, 0.60, &cToggle, isSelected ? &MenuColor : &White, 0, 0, 1, 2);
				break;
			case TYPE_FUNCTION:
				break;
			case TYPE_SUBMENU:
				Drawing.DrawText(isSelected ? "<" : "", 0.60, &cToggle, isSelected ? &MenuColor : &White, 0, 0, 1, 2);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		Drawing.DrawText("Press RS and DPAD Left to open", 0.70, &Vector4(20, 0, 505, 90), &Blue);
	}

	if (GetAsyncKeyState(XINPUT_GAMEPAD_START) || GetAsyncKeyState(XINPUT_GAMEPAD_BACK))
	{
		MenuBase.isMenuOpened = false;
	}

	if ((GetTickCount() - TimeCount) > WaitTime)
	{
		if (!MenuBase.isMenuOpened)
		{
			if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT) && GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_THUMB))
			{
				MenuBase.OpenMenu();

				Wait(200);
			}
		}
		else
		{
			if (GetAsyncKeyState(XINPUT_GAMEPAD_A))
			{
				MenuBase.SelectOption();

				Wait(140);
			}
			else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP))
			{
				MenuBase.ScrollUp();

				Wait(140);
			}
			else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN))
			{
				MenuBase.ScrollDown();

				Wait(140);
			}
			else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT))
			{
				MenuBase.ScrollLeft();

				Wait(140);
			}
			else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_RIGHT))
			{
				MenuBase.ScrollRight();

				Wait(140);
			}
			else if (GetAsyncKeyState(XINPUT_GAMEPAD_B))
			{
				MenuBase.GoBack();

				Wait(190);
			}
		}
	}
}


