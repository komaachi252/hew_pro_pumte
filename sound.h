//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_GAME = 0,			// BGM�@�Q�[�����
	SOUND_LABEL_BGM_TITLE,				// BGM�@�^�C�g�����
	SOUND_LABEL_BGM_MENU,				// BGM�@���j���[���
	SOUND_LABEL_BGM_RANKIN,				// BGM�@�����L���O���
	SOUND_LABEL_SE_CANCEL,				// SE   �L�����Z����
	SOUND_LABEL_SE_HIT1,				// SE�@ �Փˉ��@����1
	SOUND_LABEL_SE_HIT2,				// SE �@�Փˉ��@����2
	SOUND_LABEL_SE_MENU,				// SE �@���j���[��ʂł̌��艹
	SOUND_LABEL_SE_RANKIN,				// SE �@�����N�C����
	SOUND_LABEL_SE_RANKING,				// SE �@�����L���O��
	SOUND_LABEL_SE_SPLASH,				// SE   �����Ԃ���
	SOUND_LABEL_SE_SWITCH,				// SE	���j���[��ʂł̃J�[�\���؂�ւ���
	SOUND_LABEL_SE_TITLE,				// SE�@ �^�C�g����ʂł̌��艹
	SOUND_LABEL_SE_GATE,				// SE�@ �Q�[�g�ʉ߉�
	SOUND_LABEL_MAX,					// BGM&SE�̐�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
