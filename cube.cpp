//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[cube.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 10/18(‹à)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3dx9.h>
#include "Direct3d.h"
#include "common.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "texture.h"


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define FVF_CUBE (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) // ƒˆ‚È’¸“_‚Å‚·‚æ

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct CubeVertex_tag {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}CubeVertex;

enum maru1 {
	UP,
	DOWN,
	RIGHT,
	LEFT
};
enum maru2 {
	Big,
	Small
};

enum maru4{
	SOUL,
	WAIT,
	DELETE_A
};
struct Cube1 {
	maru1 mode;
	float speed;
	D3DXVECTOR3 positon;
};
struct Cube2 {
	maru2 mode;
	float speed;
	D3DXVECTOR3 positon;
	float scale;
};

struct Cube4 {
	maru4 mode;
	float speed;
	D3DXVECTOR3 position;
	float limit;
	bool use;
	int frame;
};

// ƒJƒƒ‰—p
typedef struct Camera_tag {
	D3DXVECTOR3 eye;
	D3DXVECTOR3 at;
	D3DXVECTOR3 up;
	float speed;
	float angle;
}Camera;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Cube1 cube1;
static Cube2 cube2;
static Cube4 cube4[5];
static int tex;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = nullptr;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = nullptr;

static const CubeVertex g_cube_vertices[] = {

	// ‘O–Ê
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3(0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.0f) },
	{D3DXVECTOR3(-0.5f, -0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.25f) },
	//{D3DXVECTOR3(-0.5f, -0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.25f) },
	//{D3DXVECTOR3(0.5f, 0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.0f) },
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },

	// ‰E–Ê
	{D3DXVECTOR3(0.5f,0.5f,-0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.0f) },
	{D3DXVECTOR3(0.5f,0.5f,0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.0f) },
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },
	//{D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },
	//{D3DXVECTOR3(0.5f,0.5f,0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.0f) },
	{D3DXVECTOR3(0.5f,-0.5f,0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.25f) },

	// ¶–Ê
	{D3DXVECTOR3(-0.5f,0.5f,0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.0f) },
	{D3DXVECTOR3(-0.5f,0.5f,-0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.0f) },
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.25f) },
	//{D3DXVECTOR3(-0.5f,-0.5f,0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.50f,0.25f) },
	//{D3DXVECTOR3(-0.5f,0.5f,-0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.0f) },
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.25f) },

	// ”w–Ê
	{D3DXVECTOR3(0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.0f) },
	{D3DXVECTOR3(-0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	{D3DXVECTOR3(0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.25f) },
	//{D3DXVECTOR3(0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.75f,0.25f) },
	//{D3DXVECTOR3(-0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	{D3DXVECTOR3(-0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.25f) },

	// ã–Ê
   {D3DXVECTOR3(-0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.25f) },
   {D3DXVECTOR3(0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },
   {D3DXVECTOR3(-0.5f,0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.5f) },
   //{D3DXVECTOR3(-0.5f,0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.5f) },
   //{D3DXVECTOR3(0.5f,0.5f,0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },
   {D3DXVECTOR3(0.5f,0.5f,-0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.5f) },

   // ‰º–Ê
   {D3DXVECTOR3(-0.5f,-0.5f,-0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.25f) },
   {D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.5f,0.25f) },
   {D3DXVECTOR3(-0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.5f) },
   //{D3DXVECTOR3(-0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.25f,0.5f) },
   //{D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.5f,0.25f) },
   {D3DXVECTOR3(0.5f,-0.5f,0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.5f,0.5f) },
   

};

static LPDIRECT3DDEVICE9 g_pDevice = NULL;

static float g_angle = 0.0f;
static float g_y = 0.0f;

static Camera* g_pCamera = NULL;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Cube_Init(void)
{
	g_pDevice = GetDevice();

	tex = Texture_SetLoadFile("Asset/Texture/spice_and_wolf.png", 1024, 1024);
	Texture_Load();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_angle = 0.0f;

	cube1.mode = LEFT;
	cube1.speed = 0.2f;
	cube1.positon.x = 4.5f;
	cube1.positon.y = 0.5f;
	cube1.positon.z = -4.5f;

	cube2.mode = Big;
	cube2.speed = 0.05f;
	cube2.positon.x = 4.5f;
	cube2.positon.y = 0.5f;
	cube2.positon.z = 4.5f;
	cube2.scale = 1.0f;

	for (int i = 0; i < 5; i++) {
		cube4[i].mode = SOUL;
		cube4[i].frame = 0;
		cube4[i].speed = 0.1f;
		cube4[i].position.x = -4.5f;
		cube4[i].position.y = 10.0f;
		cube4[i].position.z = 4.5f;
		cube4[i].limit = i + 0.5f;
		cube4[i].use = false;
	
	}
	cube4[0].use = true;

	//  ’¸“_ƒoƒbƒtƒ@‚Ìì¬
	g_pDevice->CreateVertexBuffer(sizeof(CubeVertex) * 24, D3DUSAGE_WRITEONLY, FVF_CUBE, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	g_pDevice->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	CubeVertex* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, g_cube_vertices, sizeof(g_cube_vertices));

	g_pVertexBuffer->Unlock();


	WORD *pIndex;

	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	/*
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 2;
	pIndex[4] = 1;
	pIndex[5] = 3;
	pIndex[6] = 4;
	pIndex[7] = 5;
	pIndex[8] = 6;
	pIndex[9] = 6;
	pIndex[10] = 5;
	pIndex[11] = 7;
	pIndex[12] = 8;
	pIndex[13] = 9;
	pIndex[14] = 10;
	pIndex[15] = 10;
	pIndex[16] = 9;
	pIndex[17] = 11;
	pIndex[18] = 12;
	pIndex[19] = 13;
	pIndex[20] = 14;
	pIndex[21] = 14;
	pIndex[22] = 13;
	pIndex[23] = 15;
	pIndex[24] = 16;
	pIndex[25] = 17;
	pIndex[26] = 18;
	pIndex[27] = 18;
	pIndex[28] = 17;
	pIndex[29] = 19;
	pIndex[30] = 20;
	pIndex[31] = 21;
	pIndex[32] = 22;
	pIndex[33] = 22;
	pIndex[34] = 21;
	pIndex[35] = 23;
	*/
	int val = 0;
	for (int i = 0; i < 6; i++) {
		pIndex[i * 6] = 0 + val;
		pIndex[i * 6 + 1] = 1 + val;
		pIndex[i * 6 + 2] = 2 + val;
		pIndex[i * 6 + 3] = 2 + val;
		pIndex[i * 6 + 4] = 1 + val;
		pIndex[i * 6 + 5] = 3 + val;
		val = val + 4;
	}

	g_pIndexBuffer->Unlock();

	//  ƒJƒƒ‰

	g_pCamera = new Camera;

	g_pCamera->eye = D3DXVECTOR3(0.0f, 3.0f, -10.0f);
	g_pCamera->at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pCamera->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_pCamera->speed = 0.1f;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Cube_Uninit(void)
{
	Texture_Destroy(&tex,1);
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (g_pIndexBuffer) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	delete g_pCamera;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Cube_Update(void)
{
	switch (cube1.mode) {
	case LEFT:
		cube1.positon.x -= cube1.speed;
		if (cube1.positon.x <= -4.5f) {
			cube1.mode = UP;
		}
		break;
	case UP:
		cube1.positon.z += cube1.speed;
		if (cube1.positon.z >= 4.5f) {
			cube1.mode = RIGHT;
		}
		break;
	case RIGHT:
		cube1.positon.x += cube1.speed;
		if (cube1.positon.x >= 4.5f) {
			cube1.mode = DOWN;
		}
		break;
	case DOWN:
		cube1.positon.z -= cube1.speed;
		if (cube1.positon.z <= -4.5f) {
			cube1.mode = LEFT;
		}
		break;
	}
	g_angle += 0.05f;

	switch (cube2.mode)
	{
	case Big:
		cube2.scale += cube2.speed;
		cube2.positon.y += cube2.speed * 0.5f;
		cube2.positon.x -= cube2.speed * 0.5f;
		cube2.positon.z -= cube2.speed * 0.5f;
		if (cube2.scale >= 3.0f) {
			cube2.mode = Small;
		}
		break;
	case Small:
		cube2.scale -= cube2.speed;
		cube2.positon.y -= cube2.speed * 0.5f;
		cube2.positon.x += cube2.speed * 0.5f;
		cube2.positon.z += cube2.speed * 0.5f;
		if (cube2.scale <= 1.0f) {
			cube2.mode = Big;
		}
		break;
	default:
		break;
	}


	for (int i = 0; i < 5; i++) {
		if (!cube4[i].use) {
			continue;
		}
		switch (cube4[i].mode){
		case SOUL:
			cube4[i].position.y -= cube4[i].speed;
			if (cube4[i].position.y <= cube4[i].limit) {
				cube4[i].mode = WAIT;
				if (i < 4) {
					cube4[i + 1].use = true;
				}
				
			}
			break;
		case WAIT:
			if (cube4[4].mode == WAIT) {
				for (int j = 0; j < 5; j++) {
					cube4[j].use = false;
					cube4[j].position.y = 10.0f;
					cube4[j].mode = SOUL;
				}
			}
			break;
		default:
			break;
		}
	}

	for (int i = 4; i >= 0; i--) {
		if (cube4[i].use) {
			break;
		}
		if (!cube4[0].use) {
			cube4[0].use = true;
		}
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Cube_Draw(void)
{

	// ƒ[ƒ‹ƒhÀ•W•ÏŠ·
	D3DXMATRIX mtxWorld, mtxRotation, mtxTransRation;  //  ƒ[ƒ‹ƒhs—ñ
	//D3DXMatrixIdentity(&mtxWorld);  //  ’PˆÊs—ñ‚ğì‚é

	D3DXMatrixRotationY(&mtxRotation, g_angle);

	D3DXMatrixTranslation(&mtxTransRation, 4.0f, -g_y, 0.0f);

	mtxWorld = mtxRotation * mtxTransRation;
	//  ˆê”ÔÅŒã
	g_pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	g_pDevice->SetFVF(FVF_CUBE);
	g_pDevice->SetTexture(0, nullptr);

	//g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_cube_vertices, sizeof(CubeVertex));

}

void Cube_Draw(const D3DMATRIX* pMatrix)
{
	g_pDevice->SetTransform(D3DTS_WORLD, pMatrix);

	g_pDevice->SetFVF(FVF_CUBE);

	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(tex);

	g_pDevice->SetTexture(0, pTexture);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex));

	g_pDevice->SetIndices(g_pIndexBuffer);//ƒCƒ“ƒfƒbƒNƒXw’è

	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_cube_vertices, sizeof(CubeVertex));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

void Cube_Set(void)
{
	//D3DXVECTOR3 eye, at, up;




	//Camera_Set(&eye, &at, &up);




	/*
	D3DXMATRIX mtxWorld, mtxRotation, mtxTransRation, mtxScale;  //  ƒ[ƒ‹ƒhs—ñ

	//D3DXMatrixIdentity(&mtxWorld);  //  ’PˆÊs—ñ‚ğì‚é

	D3DXMatrixTranslation(&mtxTransRation, 0.5f, 0.5f, -0.5f);

	mtxWorld = mtxTransRation;

	Cube_Draw(&mtxWorld);
	*/
	
	// ƒ[ƒ‹ƒhÀ•W•ÏŠ·
	D3DXMATRIX mtxWorld, mtxRotation, mtxTransRation,mtxScale;  //  ƒ[ƒ‹ƒhs—ñ

	//‡@

	D3DXMatrixTranslation(&mtxTransRation, cube1.positon.x, cube1.positon.y, cube1.positon.z);
	mtxWorld = mtxTransRation;

	Cube_Draw(&mtxWorld);

	//‡A
	//D3DXMatrixTranslation(&mtxTransRation, -(sin(g_angle) ) + 4.5f, (sinf(g_angle) + 1 % 2) + 0.5f, -(sin(g_angle) + 2) + 4.5f);

	D3DXMatrixTranslation(&mtxTransRation, cube2.positon.x, cube2.positon.y, cube2.positon.z);

	//D3DXMatrixScaling(&mtxScale, sin(g_angle) + 2, sin(g_angle) + 2, sin(g_angle) + 2);

	D3DXMatrixScaling(&mtxScale, cube2.scale, cube2.scale, cube2.scale);

	//D3DXMatrixScaling(&mtxScale, sin(g_angle) + 2, sin(g_angle) + 2, sin(g_angle) + 2);

	mtxWorld = mtxScale * mtxTransRation;
	//mtxWorld = mtxTransRation;

	Cube_Draw(&mtxWorld);

	//‡B

	D3DXMatrixTranslation(&mtxTransRation, -4.5f, 0.5f, -4.5f);

	D3DXMatrixRotationY(&mtxRotation, g_angle);
	
	mtxWorld = mtxRotation * mtxTransRation;

	Cube_Draw(&mtxWorld);

	//‡C

	// 0
	D3DXMatrixTranslation(&mtxTransRation, -4.5f, cube4[0].position.y, 4.5f);
	mtxWorld = mtxTransRation;

	if (cube4[0].use) {
		Cube_Draw(&mtxWorld);
	}
	// 1
	D3DXMatrixTranslation(&mtxTransRation, -4.5f, cube4[1].position.y, 4.5f);
	mtxWorld = mtxTransRation;

	if (cube4[1].use) {
		Cube_Draw(&mtxWorld);
	}
	// 2
	D3DXMatrixTranslation(&mtxTransRation, -4.5f, cube4[2].position.y, 4.5f);
	mtxWorld = mtxTransRation;

	if (cube4[2].use) {
		Cube_Draw(&mtxWorld);
	}

	// 3
	D3DXMatrixTranslation(&mtxTransRation, -4.5f, cube4[3].position.y, 4.5f);
	mtxWorld = mtxTransRation;

	if (cube4[3].use) {
		Cube_Draw(&mtxWorld);
	}

	// 4
	D3DXMatrixTranslation(&mtxTransRation, -4.5f, cube4[4].position.y, 4.5f);
	mtxWorld = mtxTransRation;

	if (cube4[4].use) {
		Cube_Draw(&mtxWorld);
	}



}