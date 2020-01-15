#ifndef INPUT2_H_
#define INPUT2_H_

#include<Windows.h>

//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by Joystick.rc
//

#define JOYCON_MAX     (2)

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }

#define IDI_MAIN                        102
#define IDD_JOYST_IMM                   103
#define IDR_ACCELERATOR1                103
#define IDC_CLOSE                       1001
#define IDC_X_AXIS                      1010
#define IDC_Y_AXIS                      1011
#define IDC_Z_AXIS                      1012
#define IDC_X_AXIS_TEXT                 1013
#define IDC_Y_AXIS_TEXT                 1014
#define IDC_Z_AXIS_TEXT                 1015
#define IDC_X_ROT_TEXT                  1016
#define IDC_Y_ROT_TEXT                  1017
#define IDC_Z_ROT_TEXT                  1018
#define IDC_SLIDER0_TEXT                1019
#define IDC_X_ROT                       1020
#define IDC_Y_ROT                       1021
#define IDC_Z_ROT                       1022
#define IDC_SLIDER1_TEXT                1023
#define IDC_POV0_TEXT                   1024
#define IDC_POV1_TEXT                   1025
#define IDC_POV2_TEXT                   1026
#define IDC_POV3_TEXT                   1027
#define IDC_SLIDER0                     1030
#define IDC_SLIDER1                     1031
#define IDC_POV                         1040
#define IDC_POV0                        1040
#define IDC_BUTTONS                     1041
#define IDC_POV1                        1042
#define IDC_POV2                        1043
#define IDC_POV3                        1044

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        104
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1025
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif


HRESULT InitDirectInput(HWND hWnd);
HRESULT UpdateInput(HWND hWnd);
void UninitDirectInput();


/*
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
plus�E�E�E�}�C�i�X���v���X�ɂ���
*/
float GetAxisX(int JoyConNumber, bool plus);

/*
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
plus�E�E�E�}�C�i�X���v���X�ɂ���
*/
float GetAxisY(int JoyConNumber, bool plus);

/*
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
plus�E�E�E�}�C�i�X���v���X�ɂ���
*/
float GetAxisZ(int JoyConNumber, bool plus);

float GetLastAxisZ(int JoyConNumber, bool plus);

/*
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
*/
float GetlX(int JoyConNumber);

/*
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
*/
float GetlY(int JoyConNumber);

/*
JoyCon�̃{�^���ݒ�
JoyConNumber�E�E�E0����n�܂�JoyCon�̔ԍ�
�@�@�@�@�@�@�@ �@ �ڑ��������ԂŌ��܂�
		  �@�@�@�@�@�@
BotonNumber �E�E�E
�悱����R[L]
0:�E[��]
1:��[�E]
2:��[��]
3:��[��]
4:R[L]
5:L[R]
6:(����)L[(�E��)L]
7:(����)ZL[(�E��)ZL]
8:�}�C�i�X
9:[�v���X]
10[�X�e�B�b�N��������]
11:�X�e�B�b�N��������
12:[��]
13:�l�p
*/
float GetBotton(int JoyConNumber, int BotonNumber);

float GetRotY(int joyConNumber);
float GetRotZ(int joyConNumber);
float GetAxis(int JoyConNumber, bool plus);

#endif