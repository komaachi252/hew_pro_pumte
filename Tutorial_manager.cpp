//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Tutorial_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
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
class Tutorial_Manager
{
private:
	//	’è”’è‹`
	static const int FADE_FRAME = 60;
	static const D3DCOLOR FADE_COLOR;
	//	•Ï”’è‹`
	bool m_is_fade;
public:
	Tutorial_Manager();
	virtual ~Tutorial_Manager();
	void Update();
};

const D3DCOLOR Tutorial_Manager::FADE_COLOR = D3DCOLOR_RGBA(0,0,0,0);
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Tutorial_Manager* gp_manager = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager_Init(void)
{
	gp_manager = new Tutorial_Manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager_Uninit(void)
{
	delete gp_manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager_Update(void)
{
	gp_manager->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Tutorial_Manager::Tutorial_Manager(void):m_is_fade(false)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Tutorial_Manager::~Tutorial_Manager(void)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager::Update(void)
{
	if (Keyboard_IsTrigger(DIK_SPACE) && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_GAME);
	}
}