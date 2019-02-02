#include "main.h"

bool IsTextureInit = false;
bool IsFontInit = false;

ATG::Font m_Font;
D3DTexture* Primitive = NULL;

wstring widen(const string& str)
{
	wostringstream wstm;
	const ctype<wchar_t>& ctfacet =
		use_facet< ctype<wchar_t> >(wstm.getloc());
	for (size_t i = 0; i < str.size(); ++i)
		wstm << ctfacet.widen(str[i]);
	return wstm.str();
}


D3DRECT GetTitleSafeArea()
{
	D3DDISPLAYMODE mode;
	ATG::g_pd3dDevice->GetDisplayMode(0, &mode);

	D3DRECT rcSafeArea;
	rcSafeArea.x1 = (LONG)(mode.Width * 0.0f);
	rcSafeArea.y1 = (LONG)(mode.Height * 0.0f);
	rcSafeArea.x2 = (LONG)(mode.Width * 1.0f);
	rcSafeArea.y2 = (LONG)(mode.Height * 1.0f);
	return rcSafeArea;
}



bool InitFont()
{
	if (!ATG::g_pd3dDevice) return false;

	if (IsFontInit) return IsFontInit;

	if (m_Font.Create("Nigel:\\Media\\Fonts\\Arial_16.xpr") != ERROR_SUCCESS) {

		IsFontInit = false;

		printf("Font Creation Failed\n");

		return IsFontInit;
	}

	m_Font.SetWindow(GetTitleSafeArea());

	IsFontInit = true;

	printf("Font Creation Succesful\n");

	return IsFontInit;
}

bool InitTexture()
{
	if (!ATG::g_pd3dDevice) return false;

	if (IsTextureInit) return IsTextureInit;

	if (GenerateTexture(ATG::g_pd3dDevice, &Primitive, D3DCOLOR_RGBA(255, 255, 255, 255)) != ERROR_SUCCESS) {

		IsTextureInit = false;

		printf("Texture Creation Failed\n");

		return IsTextureInit;
	}

	IsTextureInit = true;

	printf("Texture Creation Succesful\n");

	return IsTextureInit;
}

HRESULT GenerateTexture(D3DDevice* Device, D3DTexture** Texture, DWORD Color)
{

	if (FAILED(Device->CreateTexture(4, 4, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, Texture, NULL)))
		return E_FAIL;

	WORD Color16 = ((WORD)((Color >> 28) & 0xF) << 12) | (WORD)(((Color >> 20) & 0xF) << 8) | (WORD)(((Color >> 12) & 0xF) << 4) | (WORD)(((Color >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*Texture)->LockRect(0, &d3dlr, 0, 0);

	WORD *Dst16 = (WORD*)d3dlr.pBits;

	for (INT xy = 0; xy < 8 * 8; xy++)
		*Dst16++ = Color16;

	(*Texture)->UnlockRect(0);

	return S_OK;
}

void D3DDevice_SetColor(D3DCOLOR color)
{
	FLOAT vColor[4];
	vColor[0] = ((color & 0x00ff0000) >> 16L) / 255.0F;
	vColor[1] = ((color & 0x0000ff00) >> 8L) / 255.0F;
	vColor[2] = ((color & 0x000000ff) >> 0L) / 255.0F;
	vColor[3] = ((color & 0xff000000) >> 24L) / 255.0F;
	ATG::g_pd3dDevice->SetVertexShaderConstantF(1, vColor, 1);
}

void DrawBox(float X, float Y, float W, float H, D3DCOLOR Color)
{

	MeshVertexPC Vertices[4];
	Vertices[0].Position = XMFLOAT3(X, Y + H, 0);
	Vertices[0].Color = Color;

	Vertices[1].Position = XMFLOAT3(X, Y, 0);
	Vertices[1].Color = Color;

	Vertices[2].Position = XMFLOAT3(X + W, Y + H, 0);
	Vertices[2].Color = Color;

	Vertices[3].Position = XMFLOAT3(X + W, Y, 0);
	Vertices[3].Color = Color;

	DWORD dwLineWidthSaved = 0;

	m_Font.Begin();
	D3DDevice_SetColor(Color);
	ATG::g_pd3dDevice->SetTexture(0, Primitive);
	ATG::g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertices, sizeof(MeshVertexPC));
	m_Font.End();
}

void DrawLine(float X, float Y, float X2, float Y2, float Width, D3DCOLOR Color)
{
	MeshVertexPC Vertices[2];
	Vertices[0].Position = XMFLOAT3(X, Y, 0);
	Vertices[0].Color = Color;
	Vertices[1].Position = XMFLOAT3(X2, Y2, 0);
	Vertices[1].Color = Color;

	m_Font.Begin();
	D3DDevice_SetColor(Color);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_LINEWIDTH, *((DWORD*)&Width));
	ATG::g_pd3dDevice->SetTexture(0, Primitive);
	ATG::g_pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, Vertices, sizeof(MeshVertexPC));
	m_Font.End();
}

wchar_t* charToWChar(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
}


void DrawText(const char *Text, float x, float y, float scale, D3DCOLOR Color, int Flags)
{
	if (x < 0 || y < 0) return;

	m_Font.Begin();
	wchar_t* wcstr = charToWChar(Text);

	m_Font.SetScaleFactors(scale, scale);
	m_Font.DrawText(x, y, Color, wcstr, Flags);

	delete wcstr;

	m_Font.End();
}

