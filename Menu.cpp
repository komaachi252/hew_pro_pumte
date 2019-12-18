//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒƒjƒ…[ˆ—[Menu.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 11/06(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc

//  ‚±‚±‚Éƒwƒbƒ_‚ðƒCƒ“ƒNƒ‹[ƒh
#include "Menu_manager.h"
#include "Menu_Logo.h"
#include "fade.h"
#include "camera.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Initialize(void)
{
	// --------------------------------
	//  ‰Šú‰»ŠÖ”‚ð‹Lq
	// --------------------------------
	//  JKimouto_Initialize();
	//  Mama_Initialize();

	Menu_Manager_Init();
	Menu_Logo_Init();
	Camera_2D();
	Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Update(void)
{
	// --------------------------------
	//  XVŠÖ”‚ð‹Lq
	// --------------------------------
	Menu_Manager_Update();
	Menu_Logo_Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Draw(void)
{
	// --------------------------------
	//  •`‰æŠÖ”‚ð‹Lq
	// --------------------------------
	Menu_Logo_Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Finalize(void)
{
	// --------------------------------
	//  I—¹ŠÖ”‚ð‹Lq
	// --------------------------------
	Menu_Logo_Uninit();
	Menu_Manager_Uninit();
}
