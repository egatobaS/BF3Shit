#pragma once

/*
TL-------------------TR
|					  |
|					  |
|					  |
BL-------------------BR
*/

struct MatrixCoords
{
	/*
	float TL_X;	//0x70
	float TL_Y;	//0x74
	float TL_Z;	//0x78
	*/
	Vector3 TL;

	/*
	float TR_X;	//0x7C
	float TR_Y;	//0x80
	float TR_Z;	//0x84
	*/
	Vector3 TR;

	/*
	float BR_X;	//0x88
	float BR_Y;	//0x8C
	float BR_Z;	//0x90
	*/
	Vector3 BR;

	/*
	float BL_X; //0x94
	float BL_Y; //0x98
	float BL_Z;	//0x9C
	*/
	Vector3 BL;
};

typedef struct
{
	char padding00[0x3C];

	float Scale;

	float Color_R;
	float Color_G;
	float Color_B;

	float unk3;

	float Color_A;

	char padding01[0xC];

	float m_LetterSpacing;
	float m_RowSpacing;

	char padding02[0x20];

	float x;
	float y;

	float Glow_R;
	float Glow_G;
	float Glow_B;

	float unk1;

	float Glow_A;

	char padding03[0xc];

	float glow_Intensity;
}SolidTextStyle;

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
}MovingTextStyle;

class UIRender
{
public:

	UIRender();

	void DrawRect(float x, float y, float width, float height, Vector4* color);
	void DrawText(const char* Text, float FontScale, Vector4* Coords, Vector4* Color, Vector4* GlowColor = 0, float GlowScale = 0, int Halign = 0, int Valign = 2);

	void SetSolidTextStyle(int Data);
	void SetMovingTextStyle(int Data);

	void SetColor(Vector4* color);
	void SetScale(float Scale);
	void SetGlow(Vector4* color, float Intensity);
	void DrawBorderBox(float x, float y, float width, float height, float thickness, Vector4* color);

private:
	int StackData;
	bool isDrawigSolid;
	SolidTextStyle * SelectedSolidStyle;
	MovingTextStyle * SelectedMovingStyle;
};
