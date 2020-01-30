//cccccccccccccccccccc
//
//
//	xinputwb_[xinput.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ์ฌา ๎๊r
//                                                               ์ฌ๚ 12/21(y)
//cccccccccccccccccccc
#pragma once
#ifndef XINPUT_H_
#define XINPUT_H_


//
//	่่`
//
#include <d3d9.h>
#include <XInput.h>
//
//	NX้พ
//



//
//	vg^Cv้พ
//
bool Xinput_Init(HWND hWnd);	//๚ปึ
void Xinput_Uninit(void);	//Iนึ
void Xinput_Update(void);	//XV
bool Xinput_IsPress(int key);
bool Xinput_IsTrigger(int key);
bool Xinput_IsExit(int key);
float Xinput_IsAxisLX(void);
float Xinput_IsAxisRX(void);
float Xinput_IsAxisLY(void);
float Xinput_IsAxisRY(void);
bool Xinput_IsTriggerL2(void);
bool Xinput_IsTriggerR2(void);
void Xinput_Vibration(int frame, WORD left_speed, WORD right_speed);
#endif
