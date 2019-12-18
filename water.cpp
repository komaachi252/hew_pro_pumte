//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	…ƒ^ƒCƒ‹ˆ—[water.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 11/13(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"
#include <d3dx9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define FVF_WATER (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TEX_WIDTH (2134)
#define TEX_HEIGHT (2134)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct WaterVertex_tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;

}WaterVertex;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const float V_SPEED = 0.01f;
static int g_tex = 0;

static WaterVertex g_vertices[] = {
{ D3DXVECTOR3(-4.0f, 0.5f, 4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },
{ D3DXVECTOR3(4.0f, 0.5f, 4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
{ D3DXVECTOR3(-4.0f, 0.5f,-4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,1.0f) },
{ D3DXVECTOR3(-4.0f, 0.5f,-4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,1.0f) },
{ D3DXVECTOR3(4.0f, 0.5f, 4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(1.0f,0.0f) },
{ D3DXVECTOR3(4.0f, 0.5f,-4.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,1.0f) },
};
/*
static WaterVertex g_vertices[] = {
{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },
{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
{ D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,1.0f) },
{ D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,1.0f) },
{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(1.0f,0.0f) },
{ D3DXVECTOR3(0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,1.0f) },
};
*/


static int VERTEX_MAX = sizeof(g_vertices) / sizeof(g_vertices[0]);

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Water_Init(void)
{
	g_tex = Texture_SetLoadFile("Asset/Texture/kawa.jpg", TEX_WIDTH, TEX_HEIGHT);
	Texture_Load();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Water_Uninit(void)
{
	Texture_Destroy(&g_tex, 1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Water_Update(void)
{
	for (int i = 0; i < VERTEX_MAX; i++) {
		g_vertices[i].uv.y -= V_SPEED;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Water_Draw(const D3DXMATRIX* p_mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, p_mtx);
	pDevice->SetFVF(FVF_WATER);

	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(g_tex);

	pDevice->SetTexture(0, pTexture);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_vertices, sizeof(WaterVertex));
}