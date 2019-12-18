//�i���o�[�̕\��
//����ҁ@���ی\��Y
//
//�f�t�H���g�ł́A���̉摜�����ɍ���Ă���A��ʂ̒����̏㑤�ɕ\�����Ă���
//�Ԃ��O�p�`���A�i���������A�C�R��

#include <d3d9.h>
#include<d3dx9.h>
#include<d3d.h>
#include "sprite.h"
#include "texture.h"
#include "common.h"

#define PROGRESS_FRAME_WIDTH (520)											//�i���o�[�̘g�̉��T�C�Y			�@
#define PROGRESS_FRAME_HIGHT (40)											//�i���o�[�̘g�̏c�T�C�Y												
#define FRAMESPASE_SIZE (4)													//�i���o�[�̘g�̑���
#define PROGRESS_BAR_WIDTH (PROGRESS_FRAME_WIDTH - FRAMESPASE_SIZE * 2)     //�i���o�[�̃o�[���̂̉��T�C�Y
#define PROGRESSFRAME_POSITION_Y (24)										//�i���o�[��\������Y���W
#define PROGRESS_ICON_SIZE (32)												//�i���o�[�̃A�C�R���T�C�Y

enum PROGRESS_TEXTYPE
{
	PROGRESS_FRAME,
	PROGRESS_ICON,
	PROGRESS_TYPEMAX
};

static int g_progressTex[PROGRESS_TYPEMAX] = {};							//�i���o�[�{�̂ƃA�C�R���̃e�N�X�`����ۑ�����ϐ�
static float g_progress = 0;												//�i���x��ێ�����ϐ��@0.0f�`1.0f�܂�

void Progress_Init()
{
	g_progressTex[PROGRESS_FRAME] = Texture_SetLoadFile("Asset/Texture/progress.png", PROGRESS_FRAME_WIDTH, PROGRESS_FRAME_HIGHT);	//�e�N�X�`���̃��[�h�@�p�X�ύX�K�{
	g_progressTex[PROGRESS_ICON]=Texture_SetLoadFile("Asset/Texture/icon.png",PROGRESS_ICON_SIZE , PROGRESS_ICON_SIZE);				//�p�X�ύX�K�{
	g_progress = 0.0f;																												//�i���x�̏�����
}
void Progress_Uninit(void)
{
	Texture_Destroy();																												//�e�N�X�`�����
}
void Progress_Update(void)
{
	//g_progress = GetProgress();																									//�{���̐i���擾
	g_progress += 0.001f;																											//�e�X�g�p�̃C���N�������g
	if (g_progress >= 1.0f)																											//�A�C�R�����o�[�̊O�ɏo�Ȃ��悤�ɂ���
	{
		g_progress = 1.0f;
	}
}
void Progress_Draw(void)
{
	Texture_Load();																													//�e�N�X�`�����[�h
	Sprite_Draw(g_progressTex[PROGRESS_FRAME], (SCREEN_WIDTH - PROGRESS_FRAME_WIDTH) / 2, PROGRESSFRAME_POSITION_Y);
	Sprite_Draw(g_progressTex[PROGRESS_ICON],((SCREEN_WIDTH - PROGRESS_FRAME_WIDTH) / 2 + FRAMESPASE_SIZE) + PROGRESS_BAR_WIDTH * g_progress,PROGRESSFRAME_POSITION_Y+PROGRESS_FRAME_HIGHT/2);
}

