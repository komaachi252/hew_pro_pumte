#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"line.h"
#define FVF_LINE (  D3DFVF_XYZ  | D3DFVF_DIFFUSE  )


//頂点構造体宣言
typedef struct LineVertex_tag
{
	//座標
	D3DXVECTOR3 position;
	//カラー
	D3DCOLOR color;

}LineVertex;
struct LineDate
{
	LineVertex line[2];
	bool use;
};
static LineDate g_line[LINE_MAX];
//static LineVertex g_line[LINE_MAX*2];

static LPDIRECT3DDEVICE9 g_lineDevice;

static 	D3DXMATRIX mtxWorld, mtxRotation, mtxTranslation;


void LineInit()
{


	for (int i = 0; i < LINE_MAX; i++)
	{
		g_line[i].line[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_line[i].line[0].color = D3DCOLOR_RGBA(128, 0, 250, 255);
		g_line[i].line[1].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_line[i].line[1].color = D3DCOLOR_RGBA(128, 0, 250, 255);
		g_line[i].use = false;
	}

	g_lineDevice = GetDevice();

}

void LineUninit()
{

}

void LineDraw()
{
	int drawNum = 0;
	LineVertex drawLine[LINE_MAX*2];

	for (int i = 0; i < LINE_MAX; i++)
	{
		if (g_line[i].use==true)
		{
			drawLine[drawNum*2] = g_line[i].line[0];
			drawLine[drawNum*2+1] = g_line[i].line[1];
			drawNum++;
		}
	}
	//ライト使わない
	g_lineDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールド変換行列
	//単位行列
	D3DXMatrixIdentity(&mtxWorld);
	g_lineDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	g_lineDevice->SetFVF(FVF_LINE);
	g_lineDevice->SetTexture(0, NULL);
	g_lineDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_lineDevice->DrawPrimitiveUP(D3DPT_LINELIST, drawNum, drawLine, sizeof(LineVertex));

	//ライト戻す
	g_lineDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
void LineUpdate()
{
	
	for (int i = 0; i < LINE_MAX; i++)
	{
		g_line[i].line[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_line[i].line[0].color = D3DCOLOR_RGBA(256, 128, 128, 255);
		g_line[i].line[1].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_line[i].line[1].color = D3DCOLOR_RGBA(256, 128, 128, 255);
		g_line[i].use = false;
	}
	
}

void LineSet(D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd)
{
	
	for (int i = 0; i < LINE_MAX; i++)
	{
		if (g_line[i].use == false)
		{
			g_line[i].line[0].position = posStart;
			g_line[i].line[0].color = D3DCOLOR_RGBA(256, 128, 128, 255);
			g_line[i].line[1].position = posEnd;
			g_line[i].line[1].color = D3DCOLOR_RGBA(256, 128, 128, 255);
			g_line[i].use = true;
			break;

		}
		
	}
	
}
