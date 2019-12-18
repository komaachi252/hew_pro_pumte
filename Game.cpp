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
#include "brocks.h"
#include "Judgement.h"
#include "Flags.h"
#include "gool.h"
#include "fade.h"
//#include "player.h"
//#include "line.h"

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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Game_Finalize(void)
{
	// --------------------------------
	//  ここにゲームの終了関数を記述
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
