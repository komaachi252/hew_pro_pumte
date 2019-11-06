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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Init(void)
{
	g_pDevice = GetDevice();
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
//	カメラ座標プロジェクション座標設定関数
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Camera_Set(void)
{
	D3DXMATRIX mtxView;

	D3DXVECTOR3 eye(-4.0f, 1.1f, -6.0f);  //  カメラ座標
	D3DXVECTOR3 at(-4.0f, 0.0f, 0.0f);  //  注視点　見る場所
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);  //  上方向ベクトル

	D3DXMatrixLookAtLH(&mtxView, &eye, &at, &up);

	g_pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}