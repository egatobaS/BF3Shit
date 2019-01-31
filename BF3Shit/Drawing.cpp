#include "main.h"

bool IsTextureInit = false;
bool IsFontInit = false;

ATG::Font m_Font;  
D3DTexture* Primitive = NULL;

bool InitFont() 
{
	if (!ATG::g_pd3dDevice) return false;

	if (IsFontInit) return IsFontInit;

	if (m_Font.Create("Nigel:\\Media\\Fonts\\Arial_16.xpr") != ERROR_SUCCESS)  {

		IsFontInit = false;

		printf("Font Creation Failed\n");

		return IsFontInit;
	}

	m_Font.SetWindow(ATG::GetTitleSafeArea());

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

	m_Font.SetWindow(ATG::GetTitleSafeArea());

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

void DrawBox(int x, int y, int w, int h, D3DCOLOR color) 
{
	D3DRECT rec = { x, y, x + w, y + h };
	ATG::g_pd3dDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
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

void DrawLine(float X, float Y, float X2, float Y2, float Width, D3DCOLOR Color)
{
	MeshVertexPC Vertices[2];
	Vertices[0].Position = XMFLOAT3(X, Y, 0);
	Vertices[0].Color = Color;
	Vertices[1].Position = XMFLOAT3(X2, Y2, 0);
	Vertices[1].Color = Color;

	DWORD dwLineWidthSaved = 0;

	DWORD m_dwSavedState[SAVEDSTATE_COUNT] = { 0 };
	ATG::g_pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_dwSavedState[SAVEDSTATE_D3DRS_ALPHABLENDENABLE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &m_dwSavedState[SAVEDSTATE_D3DRS_SRCBLEND]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &m_dwSavedState[SAVEDSTATE_D3DRS_DESTBLEND]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_BLENDOP, &m_dwSavedState[SAVEDSTATE_D3DRS_BLENDOP]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &m_dwSavedState[SAVEDSTATE_D3DRS_ALPHATESTENABLE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_ALPHAREF, &m_dwSavedState[SAVEDSTATE_D3DRS_ALPHAREF]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_ALPHAFUNC, &m_dwSavedState[SAVEDSTATE_D3DRS_ALPHAFUNC]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_FILLMODE, &m_dwSavedState[SAVEDSTATE_D3DRS_FILLMODE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_CULLMODE, &m_dwSavedState[SAVEDSTATE_D3DRS_CULLMODE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_ZENABLE, &m_dwSavedState[SAVEDSTATE_D3DRS_ZENABLE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_STENCILENABLE, &m_dwSavedState[SAVEDSTATE_D3DRS_STENCILENABLE]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_VIEWPORTENABLE, &m_dwSavedState[SAVEDSTATE_D3DRS_VIEWPORTENABLE]);
	ATG::g_pd3dDevice->GetSamplerState(0, D3DSAMP_MINFILTER, &m_dwSavedState[SAVEDSTATE_D3DSAMP_MINFILTER]);
	ATG::g_pd3dDevice->GetSamplerState(0, D3DSAMP_MAGFILTER, &m_dwSavedState[SAVEDSTATE_D3DSAMP_MAGFILTER]);
	ATG::g_pd3dDevice->GetSamplerState(0, D3DSAMP_ADDRESSU, &m_dwSavedState[SAVEDSTATE_D3DSAMP_ADDRESSU]);
	ATG::g_pd3dDevice->GetSamplerState(0, D3DSAMP_ADDRESSV, &m_dwSavedState[SAVEDSTATE_D3DSAMP_ADDRESSV]);
	ATG::g_pd3dDevice->GetRenderState(D3DRS_LINEWIDTH, &dwLineWidthSaved);

	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_VIEWPORTENABLE, FALSE);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	D3DDevice_SetColor(Color);

	ATG::g_pd3dDevice->SetRenderState(D3DRS_LINEWIDTH, *((DWORD*)&Width));
	ATG::g_pd3dDevice->SetTexture(0, Primitive);
	ATG::g_pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, Vertices, sizeof(MeshVertexPC));

	ATG::g_pd3dDevice->SetTexture(0, NULL);
	ATG::g_pd3dDevice->SetVertexDeclaration(NULL);
	ATG::g_pd3dDevice->SetVertexShader(NULL);
	ATG::g_pd3dDevice->SetPixelShader(NULL);

	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, m_dwSavedState[SAVEDSTATE_D3DRS_ALPHABLENDENABLE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, m_dwSavedState[SAVEDSTATE_D3DRS_SRCBLEND]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, m_dwSavedState[SAVEDSTATE_D3DRS_DESTBLEND]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, m_dwSavedState[SAVEDSTATE_D3DRS_BLENDOP]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, m_dwSavedState[SAVEDSTATE_D3DRS_ALPHATESTENABLE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, m_dwSavedState[SAVEDSTATE_D3DRS_ALPHAREF]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, m_dwSavedState[SAVEDSTATE_D3DRS_ALPHAFUNC]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, m_dwSavedState[SAVEDSTATE_D3DRS_FILLMODE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, m_dwSavedState[SAVEDSTATE_D3DRS_CULLMODE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, m_dwSavedState[SAVEDSTATE_D3DRS_ZENABLE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, m_dwSavedState[SAVEDSTATE_D3DRS_STENCILENABLE]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_VIEWPORTENABLE, m_dwSavedState[SAVEDSTATE_D3DRS_VIEWPORTENABLE]);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, m_dwSavedState[SAVEDSTATE_D3DSAMP_MINFILTER]);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, m_dwSavedState[SAVEDSTATE_D3DSAMP_MAGFILTER]);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, m_dwSavedState[SAVEDSTATE_D3DSAMP_ADDRESSU]);
	ATG::g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, m_dwSavedState[SAVEDSTATE_D3DSAMP_ADDRESSV]);
	ATG::g_pd3dDevice->SetRenderState(D3DRS_LINEWIDTH, dwLineWidthSaved);
}
wstring widen(const string& str)
{
	wostringstream wstm;
	const ctype<wchar_t>& ctfacet =
		use_facet< ctype<wchar_t> >(wstm.getloc());
	for (size_t i = 0; i < str.size(); ++i)
		wstm << ctfacet.widen(str[i]);
	return wstm.str();
}

void DrawText(const char *Text, float x, float y, float scale, D3DCOLOR Color) 
{
	m_Font.Begin();
	const wchar_t* wcstr = widen(Text).c_str();

	m_Font.SetScaleFactors(scale, scale);
	m_Font.DrawText(x, y, Color, wcstr);
	m_Font.End();

}
