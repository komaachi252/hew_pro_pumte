#include"gool.h"
#include<math.h>
#include"input.h"
#include"direct3d.h"
#include"common.h"
#include<d3dx9.h>
#include<d3d9.h>
#include "model.h"

#define FVF_GOOL (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)

//���_�\���̐錾
typedef struct GoolVertex_tag
{
	//���W
	D3DXVECTOR3 position;
	//�@��
	D3DXVECTOR3 normal;
	//�J���[
	D3DCOLOR color;
}GoolVertex;

static const GoolVertex_tag g_Gool_vertices[] =
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



static LPDIRECT3DDEVICE9 g_GoolDevice;

//���[���h�ϊ��s��
static 	D3DXMATRIX  mtxWorld, mtxRotationY, mtxRotationX, mtxTranslation, mtxScal;


static Gool g_gool;

static bool g_crear;

static int g_model_id = 0;

void GoolInit(void)
{
	g_GoolDevice = GetDevice();
	
	g_gool.pos = D3DXVECTOR3(0.0f, 0.5f, 350.0f);
	g_gool.scale = 2.3f;
	g_gool.angleX = 0.0f;
	g_gool.angleY = atan2(1, 0);
	g_gool.coli.now = false;
	g_gool.coli.past = false;
	g_gool.coliLenth = 0.5f;
	g_gool.isColi = true;
	g_crear = false;
	
	g_model_id = Model_Load("goal.x");
}

void GoolDraw(void)
{
	g_GoolDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//g_GoolDevice->SetFVF(FVF_GOOL);
	g_GoolDevice->SetTexture(0, NULL);


	//�X�P�[�����O
	D3DXMatrixScaling(&mtxScal, g_gool.scale, g_gool.scale, g_gool.scale);

	//�g�����X���[�V����
	D3DXMatrixTranslation(&mtxTranslation, g_gool.pos.x, g_gool.pos.y, g_gool.pos.z);

	//���[�e�[�V����
	D3DXMatrixRotationY(&mtxRotationY, g_gool.angleY);
	D3DXMatrixRotationX(&mtxRotationX, g_gool.angleX);
	//�X�P�[�����O�����[�e�[�V�������g�����X���[�V����
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

	//���[���h�ϊ��s��
	g_GoolDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	//g_GoolDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, g_Gool_vertices, sizeof(GoolVertex));
	Model_Draw(g_model_id);

	g_GoolDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void GoolUninit(void)
{

}

void GoolUpdate(void)
{

	
	if (ColiTriger(&g_gool.coli))
	{
		g_crear = true;
		g_gool.isColi = false;
		g_gool.coli.past = g_gool.coli.now;
		g_gool.coli.now = false;
	}
}

Gool* GoolGetGool(void)
{
	return &g_gool;
}
void GoolSetColi(bool set)
{

	g_gool.coli.now = set;
}
bool GoolGetIsColi(void)
{
	return g_gool.isColi;
}
bool GoolGetCrear(void)
{
	return g_crear;
}