#ifndef CAMERA_H_
#define CAMERA_H_
#include<d3dx9.h>
#include<d3d9.h>



struct camera
{

	//ビュー変換行列
	D3DXMATRIX mtxView;
	D3DXVECTOR3 eye;//カメラ座標
	D3DXVECTOR3 at;//見る場所
	D3DXVECTOR3 up;//上方向

	D3DXVECTOR3 vec_flont;//カメラ座標
	D3DXVECTOR3 vec_right;//見る場所
	D3DXVECTOR3 vec_up;//上方向

	int rotTimer;//回転時間
	//プロジェクション変換行列
	D3DXMATRIX mtxProjection;
};


void CameraInit();
void CameraUninit();
void CameraUpdate();
void CameraDraw(void);

void CameraAddAngleX(float angle);
void CameraAddAngleY(float angle);
camera* CameraGet();
void Camera_2D(void);
D3DXVECTOR3* Get_Camera_Pos(void);
D3DXVECTOR3* Get_Camera_At(void);
D3DXVECTOR3* Get_Camera_Up(void);
#endif // !CAMERA_H_
