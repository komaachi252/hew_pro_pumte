//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[menu_button_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/09(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "menu_button_manager.h"
#include "input.h"
#include "input2.h"
#include "texture.h"
#include "sprite.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Menu_Button_Manager* g_menu_button_mana = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Menu_Button_Manager_Init(void)
{
	g_menu_button_mana = new Menu_Button_Manager();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Menu_Button_Manager_Uninit(void)
{
	delete g_menu_button_mana;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Menu_Button_Manager_Update(void)
{
	g_menu_button_mana->Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Menu_Button_Manager_Draw(void)
{
	g_menu_button_mana->Draw();
}

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
Menu_Button_Manager::Menu_Button_Manager(void)
{
	m_play2_tex_id = Texture_SetLoadFile("Asset/Texture/s.png", PLAY2_TEX_WIDTH, PLAY2_TEX_HEIGHT);
	m_play4_tex_id = Texture_SetLoadFile("Asset/Texture/t.png", PLAY4_TEX_WIDTH, PLAY4_TEX_HEIGHT);
	m_cur_tex_id = Texture_SetLoadFile("Asset/Texture/cursur.png", PLAY4_TEX_WIDTH, PLAY4_TEX_HEIGHT);
	Texture_Load();
	m_play2_x = 100.0f;
	m_play2_y = 150.0f;
	m_play4_x = 680.0f;
	m_play4_y = 150.0f;

	m_buttons[0] = new Menu_Button(m_play2_tex_id, m_play2_x, m_play2_y, PLAY2_WIDTH, PLAY2_HEIGHT);
	m_buttons[1] = new Menu_Button(m_play4_tex_id, m_play4_x, m_play4_y, PLAY4_WIDTH, PLAY4_HEIGHT);

	m_c = false;
}

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
Menu_Button_Manager::~Menu_Button_Manager(void)
{
	Texture_Destroy(&m_play2_tex_id, 1);
	Texture_Destroy(&m_play4_tex_id, 1);
	
	for (int i = 0; i < BUTTON_MAX; i++) {
		delete m_buttons[i];
	}
}

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Menu_Button_Manager::Update(void)
{
	for (int i = 0; i < BUTTON_MAX; i++) {
		m_buttons[i]->Update();
	}
	if (Keyboard_IsTrigger(DIK_RIGHT) && !m_c){
		m_c = true;
	}
	if (Keyboard_IsTrigger(DIK_LEFT) && m_c) {
		m_c = false;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Menu_Button_Manager::Draw(void)
{
	for (int i = 0; i < BUTTON_MAX; i++) {
		m_buttons[i]->Draw();
	}
	if (m_c) {
		Sprite_Draw(m_cur_tex_id, m_play4_x, m_play4_y, PLAY2_TEX_WIDTH, PLAY2_TEX_HEIGHT);
	}
	else {
		Sprite_Draw(m_cur_tex_id, m_play2_x, m_play2_y, PLAY2_TEX_WIDTH, PLAY2_TEX_HEIGHT);
	}
}