#include"brocks.h"
#include<math.h>
#include"input.h"
#include"direct3d.h"
#include"common.h"
#include "model.h"
#include <time.h>
#define FVF_BROCK (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)

//���_�\���̐錾
typedef struct BrockVertex_tag
{
	//���W
	D3DXVECTOR3 position;
	//�@��
	D3DXVECTOR3 normal;
	//�J���[
	D3DCOLOR color;
}BrockVertex;

static const BrockVertex_tag g_brock_vertices[] =
{

	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//����
	{D3DXVECTOR3(0.5f, 0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//�E��
	{D3DXVECTOR3(0.5f, -0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//�E��

	{D3DXVECTOR3(0.5f, -0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//�E��
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//����
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//����
	///////////////////////////////////
	{D3DXVECTOR3(0.5f,0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//����
	{D3DXVECTOR3(-0.5f, 0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//�E��
	{D3DXVECTOR3(-0.5f, -0.5f,0.5f),	D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//�E��

	{D3DXVECTOR3(-0.5f, -0.5f,0.5f),	D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//�E��
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//����
	{D3DXVECTOR3(0.5f,0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//����
	/////////////////////////////////
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//�O��
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),		D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//����
	{D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//����

	{D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//����
	{D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//�O��
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//�O��
	//////////////////////////////////
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//����
	{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//�O��
	{D3DXVECTOR3(-0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//�O��

	{D3DXVECTOR3(-0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//�O��
	{D3DXVECTOR3(-0.5f, -0.5f,  0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//����
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//����
	//////////////////////////////////��
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//����
	{D3DXVECTOR3(0.5f, 0.5f,  0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//
	{D3DXVECTOR3(0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//�O

	{D3DXVECTOR3(0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//�O
	{D3DXVECTOR3(-0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//����
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//����
	//////////////////////////////////��
	{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//���O
	{D3DXVECTOR3(0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//�E�O
	{D3DXVECTOR3(0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//�E��

	{D3DXVECTOR3(0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//�E��
	{D3DXVECTOR3(-0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//����
	{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//���O
};



static LPDIRECT3DDEVICE9 g_BrockDevice;

//���[���h�ϊ��s��
static 	D3DXMATRIX  mtxWorld, mtxRotationY, mtxRotationX, mtxTranslation, mtxScal;
static Brock g_brock[BROCK_NUM];

static int g_model_id = 0;

void BrocksInit(void)
{
	srand((unsigned int)time(0));//���Ԏ擾
	rand(); rand(); rand(); rand(); rand();//rand()��ł��Ő��x�㏸

	g_BrockDevice = GetDevice();

	for (int i = 0; i < BROCK_NUM; i++)
	{

		g_brock[i].pos = D3DXVECTOR3(rand() % 5, 1.5f, i * 27);
		g_brock[i].scale = 1.0;
		g_brock[i].angleX = 0.0f;
		g_brock[i].angleY = atan2(1, 0);
		g_brock[i].coli.now = false;
		g_brock[i].coli.past = false;
		g_brock[i].coliLenth = 0.5f;
		g_brock[i].draw = false;
	}

	//g_model_id = Model_Load("rock.x");
}



void BrocksDraw(void)
{

	g_BrockDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_BrockDevice->SetFVF(FVF_BROCK);
	g_BrockDevice->SetTexture(0, NULL);


	for (int i = 0; i < BROCK_NUM; i++)
	{
			//�X�P�[�����O
			D3DXMatrixScaling(&mtxScal, g_brock[i].scale, g_brock[i].scale, g_brock[i].scale);

			//�g�����X���[�V����
			D3DXMatrixTranslation(&mtxTranslation, g_brock[i].pos.x, g_brock[i].pos.y, g_brock[i].pos.z);

			//���[�e�[�V����
			D3DXMatrixRotationY(&mtxRotationY, g_brock[i].angleY);
			D3DXMatrixRotationX(&mtxRotationX, g_brock[i].angleX);
			//�X�P�[�����O�����[�e�[�V�������g�����X���[�V����
			mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

			//���[���h�ϊ��s��
			g_BrockDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			//g_BrockDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_brock_vertices, sizeof(BrockVertex));		
			Model_Draw(g_model_id);
	}
	g_BrockDevice->SetRenderState(D3DRS_LIGHTING, FALSE);



}

void BrocksUninit(void)
{
}

void BrocksUpdate(void)
{
	for (int i = 0; i < BROCK_NUM; i++)
	{
		g_brock[i].draw = g_brock[i].coli.now;
		g_brock[i].coli.past = g_brock[i].coli.now;
		g_brock[i].coli.now = false;
	}
}
Brock* BrocksGetBrock(int id)
{
	return &g_brock[id];
}
void BrocksSetColiFlag(int id,bool set)
{
	g_brock[id].coli.now = set;
}