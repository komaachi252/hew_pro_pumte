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


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
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

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Water_Init(void)
{
	g_tex = Texture_SetLoadFile("Asset/Texture/kawa.jpg", TEX_WIDTH, TEX_HEIGHT);
	Texture_Load();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Water_Uninit(void)
{
	Texture_Destroy(&g_tex, 1);
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Water_Update(void)
{
	for (int i = 0; i < VERTEX_MAX; i++) {
		g_vertices[i].uv.y -= V_SPEED;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
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