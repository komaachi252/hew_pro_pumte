//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	…ƒ^ƒCƒ‹ˆ—[water.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 11/13(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"
#include "water.h"
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


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

//static int VERTEX_MAX = sizeof(g_vertices) / sizeof(g_vertices[0]);

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Water::Water(void)
{
	//  D3DƒfƒoƒCƒX‚Ìæ“¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//  ’¸“_ƒoƒbƒtƒ@‚Ìì¬
	pDevice->CreateVertexBuffer(sizeof(WaterVertex) * 4, D3DUSAGE_WRITEONLY, FVF_WATER, D3DPOOL_MANAGED, &m_vertex_buffer_ptr, nullptr);
	pDevice->CreateVertexBuffer(sizeof(WaterVertex) * 4, D3DUSAGE_WRITEONLY, FVF_WATER, D3DPOOL_MANAGED, &m_vertex_buffer_ptr, nullptr);

	WaterVertex* vtx_ptr;
	m_vertex_buffer_ptr->Lock(0, 0, (void**)&vtx_ptr, D3DLOCK_DISCARD);

	vtx_ptr[0].position = D3DXVECTOR3(-5.0f, 0.0f, 5.0f);
	vtx_ptr[1].position = D3DXVECTOR3( 5.0f, 0.0f, 5.0f);
	vtx_ptr[2].position = D3DXVECTOR3(-5.0f, 0.0f,-5.0f);
	vtx_ptr[3].position = D3DXVECTOR3( 5.0f, 0.0f,-5.0f);

	vtx_ptr[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	vtx_ptr[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	vtx_ptr[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	vtx_ptr[3].uv = D3DXVECTOR2(1.0f, 1.0f);

	vtx_ptr[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	for (int i = 0; i < 4; i++) {
		vtx_ptr[i].color = D3DCOLOR_RGBA(255,255,255,255);
	}

	m_vertex_buffer_ptr->Unlock();

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Water::~Water(void)
{
	if (m_vertex_buffer_ptr) {
		m_vertex_buffer_ptr->Release();
		m_vertex_buffer_ptr = nullptr;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Water::Draw(int tex_id, const D3DXMATRIX& mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, &mtx);
	pDevice->SetFVF(FVF_WATER);
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(tex_id);

	//  ƒeƒNƒXƒ`ƒƒ”½•œƒ‚[ƒh
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetStreamSource(0,m_vertex_buffer_ptr,0,sizeof(WaterVertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
