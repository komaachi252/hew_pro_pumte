//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�`���[�g���A������[Tutorial.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/06(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c

//  �����Ƀw�b�_���C���N���[�h
#include "Tutorial_manager.h"
#include "Tutorial_Logo.h"
#include "fade.h"
#include "camera.h"
#include "player.h"
#include "sky_dome.h"
#include "TutoJudgement.h"
#include "MapArea.h"
#include "Tuto_rock.h"
#include "tutorial_player.h"
#include "tutocamera.h"
#include "TutoMapArea.h"
#include "light.h"
#include "TutoFlag.h"
#include "Tutorial.h"
#include "sound.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Tutorial_Initialize(void)
{
	// --------------------------------
	//  �������֐����L�q
	// --------------------------------
	Light_Init();
	TutoRockInit();
	TutoMapAreaInit();

	TutoPlayerInit();
	TutoFlagInit();
	TutoCameraInit();
	Tutorial_Manager_Init();
	Tutorial_Logo_Init();
	TutoJudgementInit();
	StopSound(SOUND_LABEL_BGM_MENU);
	PlaySound(SOUND_LABEL_BGM_TUTORIAL);
	Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Tutorial_Update(void)
{
	// --------------------------------
	//  �X�V�֐����L�q
	// --------------------------------
	TutoJudgementUpdate();

	Tutorial_Logo_Update();
	TutoPlayerUpdate();
	TutoCameraUpdate();
	TutoRockUpdate();
	TutoFlagUpdate();

	Tutorial_Manager_Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Tutorial_Draw(void)
{
	// --------------------------------
	//  �`��֐����L�q
	// --------------------------------

	TutoPlayerDraw();
	TutoRockDraw();
	TutoFlagDraw();
	Tutorial_Manager_Draw();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Tutorial_Finalize(void)
{
	// --------------------------------
	//  �I���֐����L�q
	// --------------------------------

	Tutorial_Logo_Uninit();
	Tutorial_Manager_Uninit();
	TutoPlayerUninit();
	TutoCameraUninit();
	TutoMapAreaUninit();
	TutoRockUninit();
	TutoFlagUninit();
}
