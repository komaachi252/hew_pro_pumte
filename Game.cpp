//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒQ[ƒ€ˆ—[Game.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 11/06(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc

//  ‚±‚±‚ÉƒQ[ƒ€—pƒwƒbƒ_‚ğƒCƒ“ƒNƒ‹[ƒh
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Initialize(void)
{
	// --------------------------------
	//  ‚±‚±‚ÉƒQ[ƒ€‚Ì‰Šú‰»ŠÖ”‚ğ‹Lq
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
	//	‰Šú‰»‚ÅƒtƒF[ƒhƒCƒ“
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Update(void)
{
	// --------------------------------
	//  ‚±‚±‚ÉƒQ[ƒ€‚ÌXVŠÖ”‚ğ‹Lq
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Draw(void)
{
	// --------------------------------
	//  ‚±‚±‚ÉƒQ[ƒ€‚Ì•`‰æŠÖ”‚ğ‹Lq
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Finalize(void)
{
	// --------------------------------
	//  ‚±‚±‚ÉƒQ[ƒ€‚ÌI—¹ŠÖ”‚ğ‹Lq
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
