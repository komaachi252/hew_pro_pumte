<<<<<<< HEAD
/*==============================================================================

   �L�[�{�[�h���͏��� [input.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/09/05
--------------------------------------------------------------------------------
   �L�[�{�[�h���W���[���̏���������COM�C���^�[�t�F�[�X��
   DirectInput�f�o�C�X�̏����������Ă���̂ŁA�}�E�X���͂�p�b�h���͂�
   �ǉ�����ꍇ�́A�؂藣���Ȃ��Ƃ����Ȃ�
   ���p�b�h�Ή���xinput�̗��p�𐄏�
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.h���C���N���[�h����O�ɂ�������Ȃ��ƌx�����o��̂Œ���
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �L�[�{�[�h���̓��W���[���̏�����
//
// �߂�l�F�������o���Ȃ������ꍇfalse
//
// �����Fhinstance ... �C���X�^���X�n���h���iWinMain�̈����ȂǂŎ擾�j
//       hWnd      ... �E�B���h�E�n���h��
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);

// �L�[�{�[�h���W���[���̏I������
void Keyboard_Finalize(void);

// �L�[�{�[�h���W���[���̍X�V
// ���L�[�{�[�h�S�̂̃L�[��Ԃ̎擾
//
void Keyboard_Update(void);

// �L�[�{�[�h�̃L�[��Ԃ̎擾
//
// Keyboard_Update()�Ŏ擾�����L�[�̏�Ԃ��m�F����֐��Q
//
// �߂�l�F�w��̃L�[��
//     Press   ... ������Ă���
//     Trigger ... �������u��
//     Release ... �������u��
// �ł������ꍇtrue��Ԃ�
//
// �����FnKey ... �L�[�w��iDIK_�`�Ƃ����L�[�񋓁j
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);//�������u��
bool Keyboard_IsRelease(int nKey);//�������u��
=======
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
>>>>>>> 3b73f20ab355e091174d7e2d0657ef0d01b278b8

#endif