#include "main.h"

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

		Drawing.DrawText("xbOffline Menu", 0.70, &MenuTitleCoords, &Blue);
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


