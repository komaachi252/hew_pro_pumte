//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Result_manager.cpp]
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
class Result_Manager
{
private:
	//	’è”’è‹`
	static const int FADE_FRAME = 60;
	static const D3DCOLOR FADE_COLOR;
	//	•Ï”’è‹`
	bool m_is_fade;
public:
	Result_Manager();
	virtual ~Result_Manager();
	void Update();
};

const D3DCOLOR Result_Manager::FADE_COLOR = D3DCOLOR_RGBA(0,0,0,0);
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Result_Manager* gp_manager = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Manager_Init(void)
{
	gp_manager = new Result_Manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Manager_Uninit(void)
{
	delete gp_manager;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Manager_Update(void)
{
	gp_manager->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Result_Manager::Result_Manager(void):m_is_fade(false)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Result_Manager::~Result_Manager(void)
{
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Manager::Update(void)
{
	if (Keyboard_IsTrigger(DIK_SPACE) && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_TITLE);
	}
}