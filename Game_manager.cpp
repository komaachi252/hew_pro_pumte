//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Game_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 12/17(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "input.h"
#include "fade.h"
#include "scene.h"

#include <d3d9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
class Game_Manager
{
private:
	//	’è”’è‹`
	static const int FADE_FRAME = 60;
	static const D3DCOLOR FADE_COLOR;
	//	•Ï”’è‹`
	bool m_is_fade;
public:
	Game_Manager();
	virtual ~Game_Manager();
	void Update();
};

const D3DCOLOR Game_Manager::FADE_COLOR = D3DCOLOR_RGBA(0,0,0,0);
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Game_Manager* gp_manager = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Manager_Init(void)
{
	gp_manager = new Game_Manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Manager_Uninit(void)
{
	delete gp_manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Manager_Update(void)
{
	gp_manager->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Game_Manager::Game_Manager(void):m_is_fade(false)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Game_Manager::~Game_Manager(void)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Manager::Update(void)
{
	if (Keyboard_IsTrigger(DIK_X) && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_RESULT);
	}
}