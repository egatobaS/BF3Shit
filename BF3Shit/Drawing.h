#pragma once

enum SavedStates
{
	SAVEDSTATE_D3DRS_ALPHABLENDENABLE,
	SAVEDSTATE_D3DRS_SRCBLEND,
	SAVEDSTATE_D3DRS_DESTBLEND,
	SAVEDSTATE_D3DRS_BLENDOP,
	SAVEDSTATE_D3DRS_ALPHATESTENABLE,
	SAVEDSTATE_D3DRS_ALPHAREF,
	SAVEDSTATE_D3DRS_ALPHAFUNC,
	SAVEDSTATE_D3DRS_FILLMODE,
	SAVEDSTATE_D3DRS_CULLMODE,
	SAVEDSTATE_D3DRS_ZENABLE,
	SAVEDSTATE_D3DRS_STENCILENABLE,
	SAVEDSTATE_D3DRS_VIEWPORTENABLE,
	SAVEDSTATE_D3DSAMP_MINFILTER,
	SAVEDSTATE_D3DSAMP_MAGFILTER,
	SAVEDSTATE_D3DSAMP_ADDRESSU,
	SAVEDSTATE_D3DSAMP_ADDRESSV,

	SAVEDSTATE_COUNT
};

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