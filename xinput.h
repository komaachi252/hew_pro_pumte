//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	xinputƒwƒbƒ_[xinput.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 12/21(“y)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef XINPUT_H_
#define XINPUT_H_


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#include <d3d9.h>
#include <XInput.h>
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
bool Xinput_Init(HWND hWnd);	//‰Šú‰»ŠÖ”
void Xinput_Uninit(void);	//I—¹ˆ—ŠÖ”
void Xinput_Update(void);	//XVˆ—
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
