//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�Q�[������[Game.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/06(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c

//  �����ɃQ�[���p�w�b�_���C���N���[�h
#include "camera.h"
#include "Game_manager.h"
#include "light.h"
#include <d3dx9.h>
#include "water.h"
#include "grid.h"
#include "map.h"
#include "start_count.h"
#include "player.h"
#include "UI.h"
//#include "brocks.h"
#include "Judgement.h"
//#include "Flags.h"
//#include "gool.h"
#include "fade.h"
#include "rock.h"
//#include "player.h"
//#include "line.h"
#include "sky_dome.h"
#include "MapArea.h"
#include "collision_draw.h"
#include "sinko.h"
#include "uturn.h"
#include "input.h"
#include "flag.h"
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
void Game_Initialize(void)
{
	// --------------------------------
	//  �����ɃQ�[���̏������֐����L�q
	// --------------------------------

	Map_Init();
	RockInit();
	MapAreaInit();
	PlayerInit();
	FlagInit();
	CameraInit();
	JudgementInit();
	Game_Manager_Init();
	Light_Init();
	Set_Light();
	Grid_Init();
	Start_Count_Init();
	//GoolInit();
	UI_Init();
	//LineInit();
	Sky_Dome_Init();
	Sinko_Init();
	Colli_Draw_Init(GetDevice());
	Uturn_Init();
	StopSound(SOUND_LABEL_BGM_TUTORIAL);
	PlaySound(SOUND_LABEL_BGM_GAME);
	Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);
	//	�������Ńt�F�[�h�C��
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Game_Update(void)
{
	// --------------------------------
	//  �����ɃQ�[���̍X�V�֐����L�q
	// --------------------------------
	JudgementUpdate();
	Map_Update();
	PlayerUpdate();
	CameraUpdate();
	MapAreaUpdate();
	Game_Manager_Update();
	Grid_Update();
	Start_Count_Update();
	UI_Update();
	RockUpdate();
	FlagUpdate();
	Sky_Dome_Update();
	Sinko_Update();
	Uturn_Update();
	if (Keyboard_IsTrigger(DIK_Q)) {
		Uturn_Create();
	}
	//GoolUpdate();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Game_Draw(void)
{
	// --------------------------------
	//  �����ɃQ�[���̕`��֐����L�q
	// --------------------------------
	D3DXMATRIX mtxW;
	D3DXMatrixIdentity(&mtxW);
	Sky_Dome_Draw();
	Map_Draw();
	PlayerDraw();
	MapAreaDraw();

	//GoolDraw();
	RockDraw();
	FlagDraw();
	Uturn_Draw();
	Start_Count_Draw();
	UI_Draw();
	Sinko_Draw();
	
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Game_Finalize(void)
{
	// --------------------------------
	//  �����ɃQ�[���̏I���֐����L�q
	// --------------------------------
	PlayerUninit();
	RockUninit();
	FlagUninit();
	Grid_Uninit();
	Map_Uninit();
	Start_Count_Uninit();
	UI_Uninit();
	//GoolUninit();
	Game_Manager_Uninit();
	Sky_Dome_Uninit();
	MapAreaUninit();
	Colli_Draw_Uninit();
	Sinko_Uninit();
	Uturn_Uninit();
}
