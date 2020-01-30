//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[menu_button_manager.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/09(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef MENU_BUTTON_MANAGER_H_
#define MENU_BUTTON_MANAGER_H_

#include "menu_button.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
enum MENU_MODE
{
	MENU_SELECT,
	MENU_POINT,
	MENU_MAX
};

//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������

//	�{�^���̏�Ԃ��Ǘ����A�Q�[���V�[���ɔ��f������
class Menu_Button_Manager {
private:
	static const int BUTTON_MAX = 5;
	static const int PLAY2_TEX_WIDTH = 512;
	static const int PLAY2_TEX_HEIGHT = 467;
	static const int PLAY2_WIDTH = 512;
	static const int PLAY2_HEIGHT = 467;
	static const int PLAY4_TEX_WIDTH = 512;
	static const int PLAY4_TEX_HEIGHT = 467;
	static const int PLAY4_WIDTH = 512;
	static const int PLAY4_HEIGHT = 467;

	Menu_Button* m_buttons[BUTTON_MAX];
	int m_te_tex_id;
	int m_play2_tex_id;
	int m_play4_tex_id;
	int m_hi_tex_id;
	int m_no_tex_id;
	MENU_MODE m_mode;
	float m_play2_x;
	float m_play2_y;
	float m_play4_x;
	float m_play4_y;
	bool m_is_nextscene;
	bool m_p24;
	bool m_right;
public:
	Menu_Button_Manager(void);
	~Menu_Button_Manager(void);
	void Update(void);
	void Draw(void);
	bool Is_Next_Scene(void);
};

//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
void Menu_Button_Manager_Init(void);
void Menu_Button_Manager_Uninit(void);
void Menu_Button_Manager_Update(void);
void Menu_Button_Manager_Draw(void);
bool Is_Next_Scene_Menu_Button_Manager(void);


#endif	// !MENU_BUTTON_MANAGER_H_
