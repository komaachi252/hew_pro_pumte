//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	カメラ処理[camera.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 10/24(木)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include <d3dx9.h>
#include "direct3d.h"
#include "common.h"
#include "input.h"
#include "player.h"


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

static D3DXVECTOR3 g_vecFront(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vecRight(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vecUp(0.0f, 0.0f, 0.0f);

static D3DXVECTOR3 g_vecAccelFront(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vecAccelRight(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vecAccelUp(0.0f, 0.0f, 0.0f);

static D3DXVECTOR3 g_oldVec(0.0f, 0.0f, 0.0f);
static float g_moveSpeed = 0.0f;
static float g_accleX = 0.0f;
static float g_accleY = 0.0f;
static float g_accleZ = 0.0f;
static float g_accele = 0.0f;

static float g_rotationSpeed = 0.0f;
static float g_roteacceleX = 0.0f;
static float g_roteacceleY = 0.0f;
static D3DXVECTOR3 g_Position(0.0f, 0.0f, 0.0f);
static float g_Fov = 0.0f;

static D3DXVECTOR3 g_a(0.0f,0.0f,0.0f);
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Init(void)
{
	g_pDevice = GetDevice();

	g_vecFront = D3DXVECTOR3(0.0f,-1.0f, 1.0f);
	g_vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVec3Normalize(&g_vecFront, &g_vecFront);

	D3DXVec3Cross(&g_vecUp, &g_vecFront, &g_vecRight);
	D3DXVec3Normalize(&g_vecUp, &g_vecUp);

	g_vecAccelFront = D3DXVECTOR3(0.0f,-1.0f, 1.0f);
	g_vecAccelRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVec3Normalize(&g_vecAccelFront, &g_vecAccelFront);

	D3DXVec3Cross(&g_vecAccelUp, &g_vecAccelFront, &g_vecAccelRight);
	D3DXVec3Normalize(&g_vecAccelUp, &g_vecAccelUp);

	g_oldVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_accele = 0.0f;

	g_moveSpeed = 0.05f;
	g_rotationSpeed = 0.01f;
	g_roteacceleX = 0.0f;
	g_roteacceleY = 0.0f;
	g_Fov = 1.0f; // 60度 ラジアン が画角は倍

	g_Position = D3DXVECTOR3(0.0f, 30.0f, -5.0f);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Uninit(void)
{


}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Update()
{

	D3DXVECTOR3 vecDirection(0.0f,0.0f,0.0f);
	//D3DXVECTOR3 vecDirection(g_accleX,g_accleY,g_accleZ);
	if (Keyboard_IsPress(DIK_W)) {
		vecDirection += g_vecFront;
		vecDirection.y = 0.0f; //  少し上向きでも真ん前に進む
		g_accele += 0.01f;
		g_oldVec += g_vecAccelFront * 0.1f;
		g_oldVec.y = 0.0f;
	}
	if (Keyboard_IsPress(DIK_A)) {
		vecDirection += -g_vecRight;
		g_accele -= 0.01f;
		g_oldVec -= g_vecAccelRight * 0.1f;
	}
	if (Keyboard_IsPress(DIK_D)) {
		vecDirection += g_vecRight;
		g_accele += 0.01f;
		g_oldVec += g_vecAccelRight * 0.1f;
	}
	if (Keyboard_IsPress(DIK_S)) {
		vecDirection += -g_vecFront;
		vecDirection.y = 0.0f; //  少し下向きでも真ん前に進む
		g_accele -= 0.01f;
		g_oldVec -= g_vecAccelFront * 0.1f;
		g_oldVec.y = 0.0f;
	}
	if (Keyboard_IsPress(DIK_Q)) {
		vecDirection += g_vecUp;
		g_accele += 0.01f;
		g_oldVec += g_vecAccelUp * 0.1f;
		g_oldVec.x = 0.0f;
	}
	if (Keyboard_IsPress(DIK_E)) {
		vecDirection += -g_vecUp;
		g_accele -= 0.01f;
		g_oldVec -= g_vecAccelUp * 0.1f;
		g_oldVec.x = 0.0f;
	}

	D3DXVec3Normalize(&vecDirection, &vecDirection);

	
	//g_accleX *= 0.96f;
	//g_accleY *= 0.96f;
	//g_accleZ *= 0.96f;
	g_oldVec *= 0.96f;

	//g_Position += (g_oldVec + vecDirection) * g_moveSpeed;
	g_Position += g_oldVec * g_moveSpeed;

	g_Position.z = Get_Player_Pos_Z() - 8.0f;


	//g_Position += vecDirection * g_moveSpeed;

	//D3DXVec3Normalize(&vecAccle, &vecAccle);
	//vecAccle *= g_accleX;

	//g_Position +=  vecAccle + vecDirection * g_moveSpeed ;
	
	//g_Position += vecDirection * g_moveSpeed;

	D3DXMATRIX mtxRotation;

	if (Keyboard_IsPress(DIK_RIGHT) && (Keyboard_IsPress(DIK_LSHIFT) || Keyboard_IsPress(DIK_RSHIFT))) {
		D3DXMatrixRotationY(&mtxRotation, g_rotationSpeed);

		g_a = g_Position + g_vecFront * 4.0f;

		D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);

		D3DXVec3TransformNormal(&g_vecAccelFront, &g_vecAccelFront, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecAccelRight, &g_vecAccelRight, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecAccelUp, &g_vecAccelUp, &mtxRotation);



		g_Position = g_a - g_vecFront * 4.0f;

	}
	else if (Keyboard_IsPress(DIK_LEFT) && (Keyboard_IsPress(DIK_LSHIFT) || Keyboard_IsPress(DIK_RSHIFT))) {
		D3DXMatrixRotationY(&mtxRotation, -g_rotationSpeed);

		g_a = g_Position + g_vecFront * 4.0f;

		D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);

		D3DXVec3TransformNormal(&g_vecAccelFront, &g_vecAccelFront, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecAccelRight, &g_vecAccelRight, &mtxRotation);
		D3DXVec3TransformNormal(&g_vecAccelUp, &g_vecAccelUp, &mtxRotation);

		g_Position = g_a - g_vecFront * 4.0f;

	}
	else if (Keyboard_IsPress(DIK_RIGHT)) {
		g_roteacceleX += 0.001f;
	}
	else if (Keyboard_IsPress(DIK_LEFT)) {
		g_roteacceleX -= 0.001f;
	}
	else if (Keyboard_IsPress(DIK_UP)) {
		g_roteacceleY -= 0.001f;
	}
	else if (Keyboard_IsPress(DIK_DOWN)) {
		g_roteacceleY += 0.001f;
	}

	g_roteacceleY *= 0.96f;
	g_roteacceleX *= 0.96f;

	D3DXMatrixRotationY(&mtxRotation, g_roteacceleX);
	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);

	D3DXVec3TransformNormal(&g_vecAccelFront, &g_vecAccelFront, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecAccelRight, &g_vecAccelRight, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecAccelUp, &g_vecAccelUp, &mtxRotation);

	D3DXMatrixIsIdentity(&mtxRotation);

	D3DXMatrixRotationAxis(&mtxRotation, &g_vecRight, g_roteacceleY);
	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);

	D3DXVec3TransformNormal(&g_vecAccelFront, &g_vecAccelFront, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecAccelRight, &g_vecAccelRight, &mtxRotation);
	D3DXVec3TransformNormal(&g_vecAccelUp, &g_vecAccelUp, &mtxRotation);

	D3DXVec3Normalize(&g_vecFront, &g_vecFront);
	D3DXVec3Normalize(&g_vecRight, &g_vecRight);
	D3DXVec3Normalize(&g_vecUp, &g_vecUp);
	D3DXVECTOR3 eye = g_Position;
	D3DXVECTOR3 at = g_Position + g_vecFront;
	D3DXVECTOR3 up = g_vecUp;
	D3DXMATRIX mtxView;
	D3DXMatrixLookAtLH(&mtxView, &eye, &at, &up);

	g_pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, g_Fov, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 300.0f);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	カメラ座標プロジェクション座標設定関数
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Set(D3DXVECTOR3* eye, D3DXVECTOR3* at, D3DXVECTOR3* up)
{
	D3DXMATRIX mtxView;
	D3DXMatrixLookAtLH(&mtxView, eye, at, up);

	g_pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	カメラ座標を2Dに変換
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_2D(void) 
{
	D3DXMATRIX mtxView;
	D3DXMatrixLookAtLH(&mtxView, &D3DXVECTOR3(0.0,0.0,0.0), &D3DXVECTOR3(0.0, 0.0, 0.0), &D3DXVECTOR3(0.0, 1.0, 0.0));

	g_pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}
/*
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	カメラ座標プロジェクション座標設定関数
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Set(void)
{
	D3DXMATRIX mtxView;

	D3DXVECTOR3 eye(0.0f, 3.0f, -10.0f);  //  カメラ座標
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);  //  注視点　見る場所
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);  //  上方向ベクトル

	D3DXMatrixLookAtLH(&mtxView, &eye, &at, &up);

	g_pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}*/
