//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�V�[������[scene.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/06(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "scene.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Menu.h"
#include "Tutorial.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static SCENE g_scene = SCENE_NONE;

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Scene_Update(void)
{
	switch (g_scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		Title_Update();
		break;
	case SCENE_MENU:
		Menu_Update();
		break;
	case SCENE_TUTORIAL:
		Tutorial_Update();
		break;
	case SCENE_GAME:
		Game_Update();
		break;
	case SCENE_RESULT:
		Result_Update();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//�`�揈��
//��������������������������������������������������������������������������������
void Scene_Draw(void)
{
	switch (g_scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		Title_Draw();
		break;
	case SCENE_MENU:
		Menu_Draw();
		break;
	case SCENE_TUTORIAL:
		Tutorial_Draw();
		break;
	case SCENE_GAME:
		Game_Draw();
		break;
	case SCENE_RESULT:
		Result_Draw();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//	�V�[���ݒ菈��
//��������������������������������������������������������������������������������
void Set_Scene(SCENE scene)
{
	if (scene == g_scene){return;}  //  �����ꍇ�͏Ȃ����ق��������H
	switch (g_scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		Title_Finalize();
		break;
	case SCENE_MENU:
		Menu_Finalize();
		break;
	case SCENE_TUTORIAL:
		Tutorial_Finalize();
		break;
	case SCENE_GAME:
		Game_Finalize();
		break;
	case SCENE_RESULT:
		Result_Finalize();
		break;
	default:
		break;
	}

	switch (scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		Title_Initialize();
		break;
	case SCENE_MENU:
		Menu_Initialize();
		break;
	case SCENE_TUTORIAL:
		Tutorial_Initialize();
		break;
	case SCENE_GAME:
		Game_Initialize();
		break;
	case SCENE_RESULT:
		Result_Initialize();
		break;
	default:
		break;
	}
	g_scene = scene;
}
