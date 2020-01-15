//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[grid.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 10/24(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3dx9.h>
#include "direct3d.h"
#include "common.h"
#include "camera.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define FVF_GRID (D3DFVF_XYZ | D3DFVF_DIFFUSE) // �����Ȓ��_�ł���
#define GRID_VERTEX_MAX (444)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct GridVertex_tag {
	D3DXVECTOR3 position;
	D3DCOLOR color;
}GridVertex;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static GridVertex g_grid_vertices[GRID_VERTEX_MAX] = {};

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = nullptr;

static LPDIRECT3DDEVICE9 g_pDevice = NULL;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Grid_Init(void)
{
	g_pDevice = GetDevice();
	float x = -5.0f;
	float z = 5.0f;
	int vstart = 0;
	int vend = 22;
	
	for (int i = vstart; i < vend; i++) {
		g_grid_vertices[i].position.x = x;
		g_grid_vertices[i].position.z = z;
		g_grid_vertices[i].position.y = 0;
		g_grid_vertices[i].color = D3DCOLOR_RGBA(128, 255, 0, 255);
		x *= -1.0f;
		if (i % 2 == 1) {
			z -= 1.0f;
		}
	}
	x = -5.0f;
	z = 5.0f;
	vstart = vend;
	vend = 44;
	for (int i = vstart; i < vend; i++) {
		g_grid_vertices[i].position.x = x;
		g_grid_vertices[i].position.z = z;
		g_grid_vertices[i].position.y = 0;
		g_grid_vertices[i].color = D3DCOLOR_RGBA(128, 255, 0, 255);
		z *= -1.0f;
		if (i % 2 == 1) {
			x += 1.0f;
		}
	}
	g_grid_vertices[10].color = D3DCOLOR_RGBA(255,0,0,255);
	g_grid_vertices[11].color = D3DCOLOR_RGBA(255,0,0,255);
	g_grid_vertices[32].color = D3DCOLOR_RGBA(0,0,255,255);
	g_grid_vertices[33].color = D3DCOLOR_RGBA(0,0,255,255);

	//  ���_�o�b�t�@�̍쐬
	g_pDevice->CreateVertexBuffer(sizeof(GridVertex) * GRID_VERTEX_MAX, D3DUSAGE_WRITEONLY, FVF_GRID, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	GridVertex* pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, g_grid_vertices, sizeof(g_grid_vertices));

	g_pVertexBuffer->Unlock();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Grid_Uninit(void)
{
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Grid_Update(void)
{

}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Grid_Draw(void)
{
	D3DXMATRIX mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);
	g_pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	g_pDevice->SetFVF(FVF_GRID);
	g_pDevice->SetTexture(0, nullptr);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 22, &g_grid_vertices, sizeof(GridVertex));

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(GridVertex));

	g_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, GRID_VERTEX_MAX / 2);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
