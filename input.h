#ifndef INPUT_H_
#define INPUT_H_

#include<Windows.h>

//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by Joystick.rc
//

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

#endif