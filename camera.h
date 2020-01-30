#ifndef CAMERA_H_
#define CAMERA_H_
#include<d3dx9.h>
#include<d3d9.h>



struct camera
{

	//�r���[�ϊ��s��
	D3DXMATRIX mtxView;
	D3DXVECTOR3 eye;//�J�������W
	D3DXVECTOR3 at;//����ꏊ
	D3DXVECTOR3 up;//�����

	D3DXVECTOR3 vec_flont;//�J�������W
	D3DXVECTOR3 vec_right;//����ꏊ
	D3DXVECTOR3 vec_up;//�����

	int rotTimer;//��]����
	//�v���W�F�N�V�����ϊ��s��
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
