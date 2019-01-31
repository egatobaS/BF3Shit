#include "main.h"

void UIRender::DrawBorderBox(float x, float y, float width, float height, float thickness, Vector4* color)
{
	D3DCOLOR Color = D3DCOLOR_RGBA((int)(color->x * 255), (int)(color->y * 255), (int)(color->z * 255), (int)(color->a * 255));

	DrawBox(x, y, width, thickness, Color);
	DrawBox(x, y, thickness, height, Color);
	DrawBox((x + width), y, thickness, height, Color);
	DrawBox(x, (y + height), width + thickness, thickness, Color);
}

UIRender::UIRender()
{

}

void UIRender::SetSolidTextStyle(int Data)
{

}

void UIRender::SetMovingTextStyle(int Data)
{

}

void UIRender::SetColor(Vector4* color)
{

}

void UIRender::SetGlow(Vector4* color, float Intensity)
{

}

void UIRender::SetScale(float Scale)
{

}

void UIRender::DrawText(const char* Text, float FontScale, Vector4* Coords, Vector4* Color, Vector4* GlowColor, float GlowScale, int Halign, int Valign)
{
	D3DCOLOR LColor = D3DCOLOR_RGBA((int)(Color->x * 255), (int)(Color->y * 255), (int)(Color->z * 255), (int)(Color->a * 255));

	::DrawText(Text, Coords->x, Coords->a, FontScale, LColor, Halign);
}

void UIRender::DrawRect(float x, float y, float width, float height, Vector4* color)
{
	D3DCOLOR Color = D3DCOLOR_RGBA((int)(color->x * 255), (int)(color->y * 255), (int)(color->z * 255), (int)(color->a * 255));

	DrawBox(x, y, width, height, Color);
}