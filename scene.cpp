//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒV[ƒ“ˆ—[scene.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 11/06(…)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "scene.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Menu.h"
#include "Tutorial.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static SCENE g_scene = SCENE_NONE;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒV[ƒ“İ’èˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Set_Scene(SCENE scene)
{
	if (scene == g_scene){return;}  //  “¯‚¶ê‡‚ÍÈ‚¢‚½‚Ù‚¤‚ª‚¢‚¢H
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
