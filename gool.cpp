#include"gool.h"
#include<math.h>
#include"input.h"
#include"direct3d.h"
#include"common.h"
#include<d3dx9.h>
#include<d3d9.h>
#include "model.h"

#define FVF_GOOL (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)

//頂点構造体宣言
typedef struct GoolVertex_tag
{
	//座標
	D3DXVECTOR3 position;
	//法線
	D3DXVECTOR3 normal;
	//カラー
	D3DCOLOR color;
}GoolVertex;

static const GoolVertex_tag g_Gool_vertices[] =
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



static LPDIRECT3DDEVICE9 g_GoolDevice;

//ワールド変換行列
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


	//スケーリング
	D3DXMatrixScaling(&mtxScal, g_gool.scale, g_gool.scale, g_gool.scale);

	//トランスレーション
	D3DXMatrixTranslation(&mtxTranslation, g_gool.pos.x, g_gool.pos.y, g_gool.pos.z);

	//ローテーション
	D3DXMatrixRotationY(&mtxRotationY, g_gool.angleY);
	D3DXMatrixRotationX(&mtxRotationX, g_gool.angleX);
	//スケーリング＊ローテーション＊トランスレーション
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

	//ワールド変換行列
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