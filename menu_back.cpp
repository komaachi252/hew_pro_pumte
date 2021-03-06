//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[menu_back.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/15(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
class Menu_Back
{
private:
	float m_x;
	float m_y;
	int m_tex;
	float m_uv;
public:
	Menu_Back(float x, float y) :m_x(x), m_y(y), m_tex(Texture_SetLoadFile("Asset/Texture/menu_back.png", 512, 512)), m_uv(0.0f) { Texture_Load(); }
	~Menu_Back(void) { Texture_Destroy(&m_tex, 1); }
	void Update(void);
	void Draw(void);
};

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Menu_Back* g_menu_back = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Menu_Back_Init(void)
{
	g_menu_back = new Menu_Back(200,200);
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Menu_Back_Uninit(void)
{
	delete g_menu_back;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Menu_Back_Update(void)
{
	g_menu_back->Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Menu_Back_Draw(void)
{
	g_menu_back->Draw();
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Menu_Back::Update(void)
{
	m_uv += 0.01f;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Menu_Back::Draw(void)
{
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	Sprite_DrawScroll(m_tex, 0, 0, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 256, 0, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 512, 0, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 768, 0, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 1024, 0, 256, 256, m_uv, -m_uv);

	Sprite_DrawScroll(m_tex, 0, 256, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 256, 256, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 512, 256, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 768, 256, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 1024, 256, 256, 256, m_uv, -m_uv);
	
	Sprite_DrawScroll(m_tex, 0, 512, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 256, 512, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 512, 512, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 768, 512, 256, 256, m_uv, -m_uv);
	Sprite_DrawScroll(m_tex, 1024, 512, 256, 256, m_uv, -m_uv);
	

}
