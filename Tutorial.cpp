//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒƒjƒ…[ˆ—[Tutorial.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 11/06(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc

//  ‚±‚±‚Éƒwƒbƒ_‚ðƒCƒ“ƒNƒ‹[ƒh
#include "Tutorial_manager.h"
#include "Tutorial_Logo.h"
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
void Tutorial_Initialize(void)
{
	// --------------------------------
	//  ‰Šú‰»ŠÖ”‚ð‹Lq
	// --------------------------------
	//  JKimouto_Initialize();
	//  Mama_Initialize();

	Tutorial_Manager_Init();
	Tutorial_Logo_Init();
	Camera_2D();
	Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Update(void)
{
	// --------------------------------
	//  XVŠÖ”‚ð‹Lq
	// --------------------------------
	Tutorial_Manager_Update();
	Tutorial_Logo_Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Draw(void)
{
	// --------------------------------
	//  •`‰æŠÖ”‚ð‹Lq
	// --------------------------------
	Tutorial_Logo_Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Finalize(void)
{
	// --------------------------------
	//  I—¹ŠÖ”‚ð‹Lq
	// --------------------------------
	Tutorial_Logo_Uninit();
	Tutorial_Manager_Uninit();
}
