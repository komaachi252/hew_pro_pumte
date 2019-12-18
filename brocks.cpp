#include"brocks.h"
#include<math.h>
#include"input.h"
#include"direct3d.h"
#include"common.h"
#include "model.h"
#include <time.h>
#define FVF_BROCK (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)

//頂点構造体宣言
typedef struct BrockVertex_tag
{
	//座標
	D3DXVECTOR3 position;
	//法線
	D3DXVECTOR3 normal;
	//カラー
	D3DCOLOR color;
}BrockVertex;

static const BrockVertex_tag g_brock_vertices[] =
{

	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//左上
	{D3DXVECTOR3(0.5f, 0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//右上
	{D3DXVECTOR3(0.5f, -0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//右下

	{D3DXVECTOR3(0.5f, -0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//右下
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),	D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//左下
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f),		D3DXVECTOR3(0.0f,0.0f,-1.0f),	D3DCOLOR_RGBA(255,255,255,255)},//左上
	///////////////////////////////////
	{D3DXVECTOR3(0.5f,0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//左上
	{D3DXVECTOR3(-0.5f, 0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//右上
	{D3DXVECTOR3(-0.5f, -0.5f,0.5f),	D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//右下

	{D3DXVECTOR3(-0.5f, -0.5f,0.5f),	D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//右下
	{D3DXVECTOR3(0.5f,-0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//左下
	{D3DXVECTOR3(0.5f,0.5f,0.5f),		D3DXVECTOR3(0.0f,0.0f,1.0f),	D3DCOLOR_RGBA(128,255,255,255)},//左上
	/////////////////////////////////
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//前上
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),		D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//奥上
	{D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//奥下

	{D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//奥下
	{D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//前下
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,255,255)},//前上
	//////////////////////////////////
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//奥上
	{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//前上
	{D3DXVECTOR3(-0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//前下

	{D3DXVECTOR3(-0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//前下
	{D3DXVECTOR3(-0.5f, -0.5f,  0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//奥下
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f,0.0f,0.0f),	D3DCOLOR_RGBA(255,128,128,255)},//奥上
	//////////////////////////////////上
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//左奥
	{D3DXVECTOR3(0.5f, 0.5f,  0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//
	{D3DXVECTOR3(0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//前

	{D3DXVECTOR3(0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//前
	{D3DXVECTOR3(-0.5f, 0.5f,  -0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//左奥
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f,1.0f,0.0f),	D3DCOLOR_RGBA(0,128,128,255)},//左奥
	//////////////////////////////////下
	{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//左前
	{D3DXVECTOR3(0.5f, -0.5f,  -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//右前
	{D3DXVECTOR3(0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//右奥

	{D3DXVECTOR3(0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//右奥
	{D3DXVECTOR3(-0.5f, -0.5f,  0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//左奥
	{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f,-1.0f,0.0f),	D3DCOLOR_RGBA(255,0,128,255)},//左前
};



static LPDIRECT3DDEVICE9 g_BrockDevice;

//ワールド変換行列
static 	D3DXMATRIX  mtxWorld, mtxRotationY, mtxRotationX, mtxTranslation, mtxScal;
static Brock g_brock[BROCK_NUM];

static int g_model_id = 0;

void BrocksInit(void)
{
	srand((unsigned int)time(0));//時間取得
	rand(); rand(); rand(); rand(); rand();//rand()空打ちで精度上昇

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

	g_model_id = Model_Load("rock.x");
}



void BrocksDraw(void)
{

	g_BrockDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_BrockDevice->SetFVF(FVF_BROCK);
	g_BrockDevice->SetTexture(0, NULL);


	for (int i = 0; i < BROCK_NUM; i++)
	{
			//スケーリング
			D3DXMatrixScaling(&mtxScal, g_brock[i].scale, g_brock[i].scale, g_brock[i].scale);

			//トランスレーション
			D3DXMatrixTranslation(&mtxTranslation, g_brock[i].pos.x, g_brock[i].pos.y, g_brock[i].pos.z);

			//ローテーション
			D3DXMatrixRotationY(&mtxRotationY, g_brock[i].angleY);
			D3DXMatrixRotationX(&mtxRotationX, g_brock[i].angleX);
			//スケーリング＊ローテーション＊トランスレーション
			mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

			//ワールド変換行列
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