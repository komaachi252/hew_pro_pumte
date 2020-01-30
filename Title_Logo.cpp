//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[Title_Logo.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/11(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "common.h"
#include "sprite.h"
#include "texture.h"
#include "d3dx9.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
static const int TITLE_LOGO_WIDTH = 1280;
static const int TITLE_LOGO_HEIGHT = 720;


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
class Title_Logo {
private:
	D3DXVECTOR2 m_pos;
	int m_tex;
	int m_press_tex;
	int m_logo_tex;
	int m_alpha;
	float m_sin;
public:
	Title_Logo(void);
	~Title_Logo(void);
	void Update(void);
	void Draw(void);
};

//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Title_Logo* gp_title_logo = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Title_Logo_Init(void)
{
	gp_title_logo = new Title_Logo;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Title_Logo_Uninit(void)
{
	delete gp_title_logo;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Title_Logo_Update(void)
{
	gp_title_logo->Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Title_Logo_Draw(void)
{
	gp_title_logo->Draw();
}

//��������������������������������������������������������������������������������
//	Title_Logo �R���X�g���N�^
//��������������������������������������������������������������������������������
Title_Logo::Title_Logo(void)
{
	m_tex = Texture_SetLoadFile("Asset/Texture/�^�C�g��.png", TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
	m_logo_tex = Texture_SetLoadFile("Asset/Texture/TRS.png", TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
	m_press_tex = Texture_SetLoadFile("Asset/Texture/PAK.png", TITLE_LOGO_WIDTH * 0.5f, TITLE_LOGO_HEIGHT * 0.5f);
	Texture_Load();

	//  ���S���W
	m_pos = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_alpha = 255;
	m_sin = 0.0f;
}





//��������������������������������������������������������������������������������
//	Title_Logo �f�X�g���N�^
//��������������������������������������������������������������������������������
Title_Logo::~Title_Logo(void)
{
	Texture_Destroy(&m_tex, 1);
	Texture_Destroy(&m_logo_tex, 1);
	Texture_Destroy(&m_press_tex, 1);
}

//��������������������������������������������������������������������������������
//	Title_Logo�X�V����
//��������������������������������������������������������������������������������
void Title_Logo::Update(void)
{
	//  ���W�ς���̂��ȁ[
	m_sin += 0.1f;

	m_alpha = (sin(m_sin) + 1) * 127 + 1;
}

//��������������������������������������������������������������������������������
//	Title_Logo�`�揈��
//��������������������������������������������������������������������������������
void Title_Logo::Draw(void)
{
	//  ���S���W��������W
	float tx, ty;
	tx = m_pos.x - (TITLE_LOGO_WIDTH * 0.5f);
	ty = m_pos.y - (TITLE_LOGO_HEIGHT * 0.5f);
	Sprite_Draw(m_tex, 0, 0);


	Sprite_Draw(m_logo_tex, 0, 0);
	Sprite_DrawAlpha(m_press_tex, 320, 400, TITLE_LOGO_WIDTH * 0.5f, TITLE_LOGO_HEIGHT * 0.5f, m_alpha);


}
