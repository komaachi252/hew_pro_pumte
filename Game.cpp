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
#include "brocks.h"
#include "Judgement.h"
#include "Flags.h"
#include "gool.h"
#include "fade.h"
//#include "player.h"
//#include "line.h"

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
	// Enemy_Initialize();
	// Player_Initialize();
	Game_Manager_Init();
	Light_Init();
	Set_Light();
	Grid_Init();
	Map_Init();
	Start_Count_Init();
	Player_Init();
	BrocksInit();
	FlagsInit();
	GoolInit();
	UI_Init();
	//LineInit();
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
	Game_Manager_Update();
	Camera_Update();
	Grid_Update();
	Water_Update();
	Start_Count_Update();
	UI_Update();
	Player_Update();
	BrocksUpdate();
	FlagsUpdate();
	GoolUpdate();
	JudgementUpdate();
	//LineUpdate();
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
	Grid_Draw();
	Map_Draw();
	Player_Draw();
	BrocksDraw();
	FlagsDraw();
	GoolDraw();
	//LineDraw();
	Start_Count_Draw();
	UI_Draw();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Game_Finalize(void)
{
	// --------------------------------
	//  �����ɃQ�[���̏I���֐����L�q
	// --------------------------------
	Player_Uninit();
	Grid_Uninit();
	Map_Uninit();
	Start_Count_Uninit();
	UI_Uninit();
	GoolUninit();
	BrocksUninit();
	FlagsUninit();
	Game_Manager_Uninit();
	//PlayerUninit();
	//LineUninit();
}
