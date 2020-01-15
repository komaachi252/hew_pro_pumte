#include"flags.h"
#include<math.h>
#include"input.h"
#include"direct3d.h"
#include"common.h"
#include "model.h"

#define FVF_FLAG (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)

//���_�\���̐錾
typedef struct FlagVertex_tag
{
	//���W
	D3DXVECTOR3 position;
	//�@��
	D3DXVECTOR3 normal;
	//�J���[
	D3DCOLOR color;
}FlagVertex;

static const FlagVertex_tag g_flag_vertices[] =
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



static LPDIRECT3DDEVICE9 g_FlagDevice;

//���[���h�ϊ��s��
static 	D3DXMATRIX  mtxWorld, mtxRotationY, mtxRotationX, mtxTranslation, mtxScal;
 
static Flag g_flag[FLAG_NUM];
//�ʂ������̐�
static int g_flagCnt;

static int g_model_id = 0;

void FlagsInit(void)
{
	g_FlagDevice = GetDevice();

	for (int i = 0; i < FLAG_NUM; i++)
	{
		//g_flag[i].pos = D3DXVECTOR3(i * 2 - FLAG_NUM + 1, 0.5f, 5.0f);
		g_flag[i].pos = D3DXVECTOR3(((i*i)%6)-3, 0.5f, i * 24 +5);
		g_flag[i].scale = 10.0f;
		g_flag[i].angleX = 0.0f;
		g_flag[i].angleY = atan2(1, 0);
		g_flag[i].coli.now = false;
		g_flag[i].coli.past = false;
		g_flag[i].coliLenth = 0.5f;
		g_flag[i].isColi = true;
	}
	g_flagCnt = 0;

	g_model_id = Model_Load("pole.x");
}

void FlagsDraw(void)
{
	g_FlagDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_FlagDevice->SetFVF(FVF_FLAG);
	g_FlagDevice->SetTexture(0, NULL);

	for (int i = 0; i < FLAG_NUM; i++)
	{
		if (true)
		{
			//�X�P�[�����O
			D3DXMatrixScaling(&mtxScal, g_flag[i].scale, g_flag[i].scale, g_flag[i].scale);

			//�g�����X���[�V����
			D3DXMatrixTranslation(&mtxTranslation, g_flag[i].pos.x, g_flag[i].pos.y, g_flag[i].pos.z);

			//���[�e�[�V����
			D3DXMatrixRotationY(&mtxRotationY, g_flag[i].angleY);
			D3DXMatrixRotationX(&mtxRotationX, g_flag[i].angleX);
			//�X�P�[�����O�����[�e�[�V�������g�����X���[�V����
			mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

			//���[���h�ϊ��s��
			g_FlagDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
			//g_FlagDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_flag_vertices, sizeof(FlagVertex));
			Model_Draw(g_model_id);
		}
	}
	g_FlagDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void FlagsUninit(void)
{

}

void FlagsUpdate(void)
{

	for (int i = 0; i < FLAG_NUM; i++)
	{
		if (g_flag[i].isColi==true)
		{
			if (ColiTriger(&g_flag[i].coli)) // Release
			{
				FlagsAddScore();
				g_flag[i].isColi = false;
			}
		}
		g_flag[i].coli.past = g_flag[i].coli.now;
		g_flag[i].coli.now = false;
	}
}

Flag* FlagsGetFlag(int id)
{
	return &g_flag[id];
}
void FlagsSetColi(int id, bool set)
{

	g_flag[id].coli.now = set;
}
bool FlagsGetIsColi(int id)
{

	return g_flag[id].isColi;
}
void FlagsAddScore(void)
{

	g_flagCnt++;
}
int FlagsGetCnt(void)
{
	return g_flagCnt;
}