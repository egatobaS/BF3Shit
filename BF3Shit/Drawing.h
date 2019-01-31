#pragma once

extern ATG::Font m_Font;     // Font for drawing text
extern D3DTexture* Primitive;

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

struct MeshVertexPC
{
public:
	XMFLOAT3 Position;
	D3DCOLOR Color;
	static size_t Size()
	{
		return sizeof(MeshVertexPC);
	}
};


bool InitTexture();
bool InitFont();

extern bool IsTextureInit;
extern bool IsFontInit;
void DrawText(const char *Text, float x, float y, float scale, D3DCOLOR Color);
void DrawBox(int x, int y, int w, int h, D3DCOLOR color);
void DrawLine(float X, float Y, float X2, float Y2, float Width, D3DCOLOR Color);
HRESULT GenerateTexture(D3DDevice* Device, D3DTexture** Texture, DWORD Color);