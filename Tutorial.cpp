//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	チュートリアル処理[Tutorial.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 11/06(水)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡

//  ここにヘッダをインクルード
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Tutorial_Initialize(void)
{
	// --------------------------------
	//  初期化関数を記述
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Tutorial_Update(void)
{
	// --------------------------------
	//  更新関数を記述
	// --------------------------------
	TutoJudgementUpdate();

	Tutorial_Logo_Update();
	TutoPlayerUpdate();
	TutoCameraUpdate();
	TutoRockUpdate();
	TutoFlagUpdate();

	Tutorial_Manager_Update();
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Tutorial_Draw(void)
{
	// --------------------------------
	//  描画関数を記述
	// --------------------------------

	TutoPlayerDraw();
	TutoRockDraw();
	TutoFlagDraw();
	Tutorial_Manager_Draw();
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Tutorial_Finalize(void)
{
	// --------------------------------
	//  終了関数を記述
	// --------------------------------

	Tutorial_Logo_Uninit();
	Tutorial_Manager_Uninit();
	TutoPlayerUninit();
	TutoCameraUninit();
	TutoMapAreaUninit();
	TutoRockUninit();
	TutoFlagUninit();
}
