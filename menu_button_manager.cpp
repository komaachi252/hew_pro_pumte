//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[menu_button_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 1/09(–Ø)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "menu_button_manager.h"
#include "input.h"
#include "input2.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "tutorial_player.h"
#include "data.h"
#include "sound.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Menu_Button_Manager* g_menu_button_mana = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager_Init(void)
{
	g_menu_button_mana = new Menu_Button_Manager();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager_Uninit(void)
{
	delete g_menu_button_mana;
	g_menu_button_mana = nullptr;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager_Update(void)
{
	if (g_menu_button_mana == nullptr) {
		return;
	}
	g_menu_button_mana->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager_Draw(void)
{
	if (g_menu_button_mana == nullptr) {
		return;
	}
	g_menu_button_mana->Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ŸƒV[ƒ“ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
bool Is_Next_Scene_Menu_Button_Manager(void)
{
	if (g_menu_button_mana == nullptr) {
		return false;
	}
	return g_menu_button_mana->Is_Next_Scene();
}


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Menu_Button_Manager::Menu_Button_Manager(void)
{
	m_play2_tex_id = Texture_SetLoadFile("Asset/Texture/s.png", PLAY2_TEX_WIDTH, PLAY2_TEX_HEIGHT);
	m_play4_tex_id = Texture_SetLoadFile("Asset/Texture/t.png", PLAY4_TEX_WIDTH, PLAY4_TEX_HEIGHT);
	m_te_tex_id = Texture_SetLoadFile("Asset/Texture/te.png", 768, 384);
	m_hi_tex_id = Texture_SetLoadFile("Asset/Texture/hi.png", 384, 192);
	m_no_tex_id = Texture_SetLoadFile("Asset/Texture/no.png", 384, 192);
	Texture_Load();
	m_play2_x = 100.0f;
	m_play2_y = 130.0f;
	m_play4_x = 680.0f;
	m_play4_y = 130.0f;

	m_buttons[0] = new Menu_Button(m_play2_tex_id, m_play2_x, m_play2_y, PLAY2_WIDTH, PLAY2_HEIGHT);
	m_buttons[1] = new Menu_Button(m_play4_tex_id, m_play4_x, m_play4_y, PLAY4_WIDTH, PLAY4_HEIGHT);
	m_buttons[2] = new Menu_Button(m_te_tex_id, 270, 100, 768, 384);

	m_buttons[3] = new Menu_Button(m_hi_tex_id, 260, 400, 384, 192);
	m_buttons[4] = new Menu_Button(m_no_tex_id, 660, 400, 384, 192);

	m_buttons[0]->Set_Scale_Mode(true);
	m_buttons[4]->Set_Scale_Mode(true);

	m_is_nextscene = false;

	m_mode = MENU_SELECT;

	m_right = true;

	m_p24 = true;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Menu_Button_Manager::~Menu_Button_Manager(void)
{
	Texture_Destroy(&m_play2_tex_id, 1);
	Texture_Destroy(&m_play4_tex_id, 1);
	Texture_Destroy(&m_hi_tex_id, 1);
	Texture_Destroy(&m_no_tex_id, 1);
	Texture_Destroy(&m_te_tex_id, 1);
	
	for (int i = 0; i < BUTTON_MAX; i++) {
		delete m_buttons[i];
		m_buttons[i] = nullptr;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager::Update(void)
{
	if (m_buttons[0] != nullptr) {
		m_buttons[0]->Update();
	}
	if (m_buttons[1] != nullptr) {
		m_buttons[1]->Update();
	}
	if (m_buttons[2] != nullptr && m_mode == MENU_POINT) {
		m_buttons[2]->Update();
	}
	if (m_buttons[3] != nullptr && m_mode == MENU_POINT) {
		m_buttons[3]->Update();
	}
	if (m_buttons[4] != nullptr && m_mode == MENU_POINT) {
		m_buttons[4]->Update();
	}



	if (Keyboard_IsTrigger(DIK_LEFT) && m_mode == MENU_SELECT){
		PlaySound(SOUND_LABEL_SE_SWITCH);
		m_buttons[0]->Set_Scale_Mode(true);
		m_buttons[1]->Set_Scale_Mode(false);
		m_p24 = true;
	}
	if (Keyboard_IsTrigger(DIK_RIGHT) && m_mode == MENU_SELECT) {
		PlaySound(SOUND_LABEL_SE_SWITCH);
		m_buttons[0]->Set_Scale_Mode(false);
		m_buttons[1]->Set_Scale_Mode(true);
		m_p24 = false;
	}

	if (Keyboard_IsTrigger(DIK_LEFT) && m_mode == MENU_POINT){
		PlaySound(SOUND_LABEL_SE_SWITCH);
		m_buttons[3]->Set_Scale_Mode(true);
		m_buttons[4]->Set_Scale_Mode(false);
		m_right = false;
	}
	if (Keyboard_IsTrigger(DIK_RIGHT) && m_mode == MENU_POINT) {
		PlaySound(SOUND_LABEL_SE_SWITCH);
		m_buttons[3]->Set_Scale_Mode(false);
		m_buttons[4]->Set_Scale_Mode(true);
		m_right = true;
	}

	if (Keyboard_IsTrigger(DIK_RETURN) && m_mode == MENU_SELECT) {
		PlaySound(SOUND_LABEL_SE_MENU);
		m_mode = MENU_POINT;
	}else  if (Keyboard_IsTrigger(DIK_RETURN) && m_mode == MENU_POINT && m_right) {
		PlaySound(SOUND_LABEL_SE_CANCEL);
		m_mode = MENU_SELECT;
	}
	else if (Keyboard_IsTrigger(DIK_RETURN) && m_mode == MENU_POINT && !m_right) {
		PlaySound(SOUND_LABEL_SE_MENU);
		m_is_nextscene = true;
		if (m_p24) {
			Set_Mode(MODE_2);
			//	‚±‚±ƒ‰ƒ“ƒLƒ“ƒO
		}
		else{
			Set_Mode(MODE_4);
			//	‚±‚±ƒ‰ƒ“ƒLƒ“ƒO
		}
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Menu_Button_Manager::Draw(void)
{
	if (m_buttons[0] != nullptr) {
		m_buttons[0]->Draw();
	}
	if (m_buttons[1] != nullptr) {
		m_buttons[1]->Draw();
	}
	if (m_buttons[2] != nullptr && m_mode == MENU_POINT) {
		m_buttons[2]->Draw();
	}
	if (m_buttons[3] != nullptr && m_mode == MENU_POINT) {
		m_buttons[3]->Draw();
	}
	if (m_buttons[4] != nullptr && m_mode == MENU_POINT) {
		m_buttons[4]->Draw();
	}


}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ŸƒV[ƒ“ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
bool Menu_Button_Manager::Is_Next_Scene(void)
{
	return m_is_nextscene;
}