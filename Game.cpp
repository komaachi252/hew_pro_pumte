//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	ゲーム処理[Game.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 11/06(水)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡

//  ここにゲーム用ヘッダをインクルード
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Game_Initialize(void)
{
	// --------------------------------
	//  ここにゲームの初期化関数を記述
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
	//	初期化でフェードイン
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Game_Update(void)
{
	// --------------------------------
	//  ここにゲームの更新関数を記述
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Game_Draw(void)
{
	// --------------------------------
	//  ここにゲームの描画関数を記述
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Game_Finalize(void)
{
	// --------------------------------
	//  ここにゲームの終了関数を記述
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
