//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�n�ʃ^�C������[ground.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/13(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"
#include <d3dx9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define FVF_GROUND (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TEX_WIDTH (2134)
#define TEX_HEIGHT (2134)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct GroundVertex_tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;

}GroundVertex;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static int g_tex = 0;
static D3DCOLOR GROUND_COLOR = D3DCOLOR_RGBA(120, 200, 20, 255);

static GroundVertex g_vertices[] = {
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), GROUND_COLOR, D3DXVECTOR2(0.0f,0.0f) },
	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  GROUND_COLOR, D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), GROUND_COLOR, D3DXVECTOR2(0.0f,1.0f) },
	//{ D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), GROUND_COLOR, D3DXVECTOR2(0.0f,1.0f) },
	//{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  GROUND_COLOR, D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  GROUND_COLOR, D3DXVECTOR2(1.0f,1.0f) },
};

static int VERTEX_MAX = sizeof(g_vertices) / sizeof(g_vertices[0]);
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = nullptr;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = nullptr;


//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Ground_Init(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//  ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(GroundVertex) * 4, D3DUSAGE_WRITEONLY, FVF_GROUND, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	GroundVertex* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, g_vertices, sizeof(g_vertices));

	g_pVertexBuffer->Unlock();

	//  �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 2;
	pIndex[4] = 1;
	pIndex[5] = 3;

	g_pIndexBuffer->Unlock();

}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Ground_Uninit(void)
{
	Texture_Destroy(&g_tex, 1);
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Ground_Update(void)
{
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Ground_Draw(const D3DXMATRIX* p_mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, p_mtx);
	pDevice->SetFVF(FVF_GROUND);

	pDevice->SetTexture(0, nullptr);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(GroundVertex));

	pDevice->SetIndices(g_pIndexBuffer);//�C���f�b�N�X�w��

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}