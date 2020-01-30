#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"player.h"
#include"common.h"
#include"camera.h"
#include"input.h"
#include"player.h"
#include"debug_font.h"
static camera g_camera;

static LPDIRECT3DDEVICE9 g_cameraDevice;
//画角
static float g_cameraAngleX;
static float g_cameraAngleY;
static float g_angleInCloss;
static float g_angleOutCloss;

void CameraInit()
{

	Player* player = PlayerGet();
	//カメラ座標
	g_camera.eye.x = 0.0f;
	g_camera.eye.y = 30;
	g_camera.eye.z = -5.0f;

	//見る場所
	g_camera.at.x = 0.0f;
	g_camera.at.y = 0.0f;
	g_camera.at.z = 0.0f;
	
	//上方向
	g_camera.up.x = 0.0f;
	g_camera.up.y = 1.0f;
	g_camera.up.z = 0.0;

	g_camera.vec_flont = player->vecFront;
	g_camera.vec_right = player->vecRight;
	g_camera.vec_up = player->vecUp;
	
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationAxis(&mtxRot, &g_camera.vec_right, D3DXToRadian(45));
	D3DXVec3TransformNormal(&g_camera.vec_flont, &g_camera.vec_flont, &mtxRot);
	D3DXVec3TransformNormal(&g_camera.vec_up, &g_camera.vec_up, &mtxRot);
	D3DXVec3Normalize(&g_camera.vec_flont, &g_camera.vec_flont);
	D3DXVec3Normalize(&g_camera.vec_up, &g_camera.vec_up);
	
	g_camera.rotTimer = 0;

	g_cameraAngleX = 0;
	g_cameraAngleY = 0;

	g_cameraDevice = GetDevice();

}

void CameraUninit()
{
}

void CameraUpdate()
{
	//カメラ
	D3DXMATRIX mtxCamera, mtxCameraRotX, mtxCameraRotY;


	Player* player = PlayerGet();
	
	D3DXVECTOR3 plVec3 = D3DXVECTOR3(player->vecFront.x, 0.0f, player->vecFront.z);
	D3DXVECTOR3 camVec3 = D3DXVECTOR3(g_camera.vec_flont.x, 0.0f, g_camera.vec_flont.z);
	D3DXVec3Normalize(&camVec3, &camVec3);
	D3DXVec3Normalize(&plVec3, &plVec3);
	D3DXVECTOR3 outCloss = D3DXVECTOR3
	(
		(camVec3.y*plVec3.z) - (camVec3.z*plVec3.y),
		(camVec3.z*plVec3.x) - (camVec3.x*plVec3.z),
		(camVec3.x*plVec3.y) - (camVec3.y*plVec3.x)
	);
	g_angleOutCloss = asinf(Vec3Lenth(outCloss));

	if (g_angleOutCloss > D3DXToRadian(1))
	{
		g_camera.rotTimer++;
	}
	else
	{
		g_camera.rotTimer = 0;
	}

	if (g_camera.rotTimer>3)
	{
	
		if (outCloss.y < 0)
		{
			g_cameraAngleY = D3DXToRadian(-0.5);
		}
		else if (outCloss.y>0)
		{
			g_cameraAngleY = D3DXToRadian(0.5);
		}
		else
		{
			g_cameraAngleY = 0;
		}


		D3DXMATRIX mtxRotX, mtxRotY;
		D3DXMatrixRotationY(&mtxRotY, g_cameraAngleY);
		D3DXMatrixRotationX(&mtxRotX, g_cameraAngleX);
		mtxRotX = mtxRotX * mtxRotY;

		D3DXVec3TransformNormal(&g_camera.vec_flont, &g_camera.vec_flont, &mtxRotX);
		D3DXVec3TransformNormal(&g_camera.vec_right, &g_camera.vec_right, &mtxRotX);
		D3DXVec3TransformNormal(&g_camera.vec_up, &g_camera.vec_up, &mtxRotX);
		D3DXVec3Normalize(&g_camera.vec_flont, &g_camera.vec_flont);
		D3DXVec3Normalize(&g_camera.vec_right, &g_camera.vec_right);
		D3DXVec3Normalize(&g_camera.vec_up, &g_camera.vec_up);
	}


	//カメラセット
	g_camera.at = player->pos + player->vecFront*2;
	//g_camera.at = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera.eye = player->pos - g_camera.vec_flont * 5;
	g_camera.up = player->vecUp;



	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.eye, &g_camera.at, &g_camera.up);
	g_cameraDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(60),//画角
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,//アスペクト比
		0.1f,//ニア
		200.0f//ファー
	);
	g_cameraDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
	//g_cameraAngleY *= 0.98f;
}
void CameraDraw(void)
{
	//デバッグライト
	//DebugFont_Draw(10, 10, "Angle=%f\n",D3DXToDegree( g_angleInCloss));
	DebugFont_Draw(10, 11, "x=%f::y=%f::z=%f\n", PlayerGet()->pos.x, PlayerGet()->pos.y, PlayerGet()->pos.z);

}
void CameraAddAngleX(float angle)
{
	g_cameraAngleX += angle;
}
void CameraAddAngleY(float angle)
{
	g_cameraAngleY += angle;
}
camera* CameraGet()
{
	return &g_camera;
}

void Camera_2D(void)
{
	D3DXMATRIX mtxView;
	D3DXMatrixLookAtLH(&mtxView, &D3DXVECTOR3(0.0, 0.0, 0.0), &D3DXVECTOR3(0.0, 0.0, 0.0), &D3DXVECTOR3(0.0, 1.0, 0.0));

	GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxProjection;

	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

D3DXVECTOR3* Get_Camera_Pos(void)
{
	return &g_camera.eye;
}

D3DXVECTOR3* Get_Camera_At(void)
{
	return &g_camera.at;
}

D3DXVECTOR3* Get_Camera_Up(void)
{
	return &g_camera.up;
}




