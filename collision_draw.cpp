//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[collision_draw.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 1/16(–Ø)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"
#include "direct3d.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define DEBUG_SPHERE_VERTEX_NUM (8)
#define DEBUG_SPHERE_MAX (256)
#define FVF_DEBUG_SPHERE_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
LPDIRECT3DVERTEXBUFFER9 m_sphere_vertex;
LPDIRECT3DINDEXBUFFER9 m_sphere_index;
int m_sphere_count = 0;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
struct Sphere_vertex {
	D3DXVECTOR3 pos;
	D3DCOLOR color;
};

class Sphere_Draw
{
private:

public:
	void Draw(D3DXVECTOR3 pos, float radius);
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
HRESULT Colli_Draw_Init(LPDIRECT3DDEVICE9 device)
{
	//device->CreateVertexBuffer(DEBUG_SPHERE_VERTEX_NUM * DEBUG_SPHERE_MAX * sizeof(Sphere_vertex),
	//					   D3DUSAGE_WRITEONLY, FVF_DEBUG_SPHERE_VERTEX, D3DPOOL_MANAGED, &m_sphere_vertex,nullptr);
	//device->CreateIndexBuffer((DEBUG_SPHERE_VERTEX_NUM * 2) * DEBUG_SPHERE_MAX * sizeof(WORD),
	//				   D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_sphere_index, nullptr);
	device->CreateVertexBuffer(16 * sizeof(Sphere_vertex), D3DUSAGE_WRITEONLY, FVF_DEBUG_SPHERE_VERTEX, D3DPOOL_MANAGED, &m_sphere_vertex, nullptr);
	device->CreateIndexBuffer(32 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_sphere_index, nullptr);
	return D3D_OK;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Colli_Draw_Uninit(void)
{
	if (m_sphere_vertex) {
		m_sphere_vertex->Release();
		m_sphere_vertex = nullptr;
	}
	if (m_sphere_index) {
		m_sphere_index->Release();
		m_sphere_index = nullptr;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Colli_Draw_Begin(void)
{
	m_sphere_count = 0;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sphere_Draw(D3DXVECTOR3 pos, float radius, D3DCOLOR color)
{
	if (m_sphere_count >= DEBUG_SPHERE_MAX) {
		return;
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sphere_Draw(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 pos, float radius, D3DCOLOR color)
{
	D3DXMATRIX mtx_world;
	D3DXMatrixTranslation(&mtx_world, pos.x, pos.y, pos.z);

	device->SetTransform(D3DTS_WORLD, &mtx_world);

	Sphere_vertex* pV;
	m_sphere_vertex->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	float divide = D3DX_PI * 2.0f / 8;
	for (int i = 0; i < 8; i++) {
		pV[i].pos = D3DXVECTOR3(sinf(divide * i) * radius, cosf(divide * i) * radius, 0.0f);
		pV[i].color = color;
	}
	for (int i = 8; i < 16; i++) {
		pV[i].pos = D3DXVECTOR3(0.0f, cosf(divide * i) * radius, sinf(divide * i) * radius);
		pV[i].color = color;
	}
	m_sphere_vertex->Unlock();

	WORD* pI;
	m_sphere_index->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
	for (int i = 0; i < 8; i++) {
		if (i == 7) {
			pI[i * 2] = 7;
			pI[i * 2 + 1] = 0;
		}else {
			pI[i * 2] = i;
			pI[i * 2 + 1] = i + 1;

		}
	}

	for (int i = 8; i < 16; i++) {
		if (i == 15) {
			pI[i * 2] = 15;
			pI[i * 2 + 1] = 8;
		}else {
			pI[i * 2] = i;
			pI[i * 2 + 1] = i + 1;
		}
	}
	m_sphere_index->Unlock();

	device->SetStreamSource(0, m_sphere_vertex, 0, sizeof(Sphere_vertex));
	device->SetIndices(m_sphere_index);
	device->SetFVF(FVF_DEBUG_SPHERE_VERTEX);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetTexture(0, nullptr);
	device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 16, 0, 16);
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	/*
	Sphere_vertex v[16];
	float divide = D3DX_PI * 2.0f / 8;
	for (int i = 0; i < 8; i++) {
		v[i].pos = D3DXVECTOR3(sinf(divide * i) * radius, cosf(divide * i) * radius,0.0f);
		v[i].color = color;
	}
	for (int i = 8; i < 16; i++) {
		v[i].pos = D3DXVECTOR3(pos.x, cosf(divide * i) * radius + pos.y, sinf(divide * i) * radius + pos.z);
		v[i].color = color;
	}

	device->SetFVF(FVF_DEBUG_SPHERE_VERTEX);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->DrawPrimitiveUP(D3DPT_LINELIST, 8, v, sizeof(Sphere_vertex));
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	*/
}