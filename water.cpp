//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	���^�C������[water.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/13(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"
#include "water.h"
#include <d3dx9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define FVF_WATER (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TEX_WIDTH (2134)
#define TEX_HEIGHT (2134)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct WaterVertex_tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;

}WaterVertex;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������

//static int VERTEX_MAX = sizeof(g_vertices) / sizeof(g_vertices[0]);

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
Water::Water(void)
{
	//  D3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//  ���_�o�b�t�@�̍쐬
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

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
Water::~Water(void)
{
	if (m_vertex_buffer_ptr) {
		m_vertex_buffer_ptr->Release();
		m_vertex_buffer_ptr = nullptr;
	}
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Water::Draw(int tex_id, const D3DXMATRIX& mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, &mtx);
	pDevice->SetFVF(FVF_WATER);
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(tex_id);

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetStreamSource(0,m_vertex_buffer_ptr,0,sizeof(WaterVertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
