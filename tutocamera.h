#ifndef TUTOCAMERA_H_
#define TUTOCAMERA_H_
#include<d3dx9.h>
#include<d3d9.h>
#include "camera.h"

void TutoCameraInit();
void TutoCameraUninit();
void TutoCameraUpdate();
void TutoCameraDraw(void);

void TutoCameraAddAngleX(float angle);
void TutoCameraAddAngleY(float angle);
camera* TutoCameraGet();
D3DXVECTOR3* TutoGet_Camera_Pos(void);
D3DXVECTOR3* TutoGet_Camera_At(void);
D3DXVECTOR3* TutoGet_Camera_Up(void);
#endif // !CAMERA_H_
