//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒwƒbƒ_[menu_button_manager.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 1/09(–Ø)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef MENU_BUTTON_MANAGER_H_
#define MENU_BUTTON_MANAGER_H_

#include "menu_button.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

//	ƒ{ƒ^ƒ“‚Ìó‘Ô‚ğŠÇ—‚µAƒQ[ƒ€ƒV[ƒ“‚É”½‰f‚³‚¹‚é
class Menu_Button_Manager {
private:
	static const int BUTTON_MAX = 2;
	static const int PLAY2_TEX_WIDTH = 512;
	static const int PLAY2_TEX_HEIGHT = 467;
	static const int PLAY2_WIDTH = 512;
	static const int PLAY2_HEIGHT = 467;
	static const int PLAY4_TEX_WIDTH = 512;
	static const int PLAY4_TEX_HEIGHT = 467;
	static const int PLAY4_WIDTH = 512;
	static const int PLAY4_HEIGHT = 467;

	Menu_Button* m_buttons[BUTTON_MAX];
	int m_cur_tex_id;
	int m_play2_tex_id;
	int m_play4_tex_id;

	float m_play2_x;
	float m_play2_y;
	float m_play4_x;
	float m_play4_y;
	bool m_c;
public:
	Menu_Button_Manager(void);
	~Menu_Button_Manager(void);
	void Update(void);
	void Draw(void);
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager_Init(void);
void Menu_Button_Manager_Uninit(void);
void Menu_Button_Manager_Update(void);
void Menu_Button_Manager_Draw(void);


#endif	// !MENU_BUTTON_MANAGER_H_
