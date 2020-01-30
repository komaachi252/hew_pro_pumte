//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�^�C�g���G���^�[����[Title_Enter.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/4(�y)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "Title_Enter.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "input.h"
#include "input.h"
#include "xinput.h"
#include "sound.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define NEXT_FRAME (100)

//��������������������������������������������������������������������������������
//	�R���X�g���N�^
//��������������������������������������������������������������������������������
Title_Enter::Title_Enter(void)
{

}

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
HRESULT Title_Enter::Init(void)
{
	//	�e�N�X�`���\��ԍ�
	m_tex = Texture_SetLoadFile("Asset/Texture/press_enter.png", LOGO_TEX_WIDTH, LOGO_TEX_HEIGHT);
	Texture_Load();
	//  ���S���W
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f);

	m_alpha = 255;

	m_is_next_scene = false;

	m_frame = NEXT_FRAME;

	m_sin = 0.0f;
	return S_OK;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Title_Enter::Update(void)
{
	m_sin += 0.1f;
	if ( !m_is_next_scene && (Keyboard_IsTrigger(DIK_RETURN) || Xinput_IsTrigger(XINPUT_GAMEPAD_START))) {
		StopSound(SOUND_LABEL_BGM_TITLE);
		PlaySound(SOUND_LABEL_SE_START);
		m_is_next_scene = true;
	}
	if (m_is_next_scene) {
		m_frame--;
		if (m_alpha > 0) {
			m_alpha--;
		}
	}else {
		m_alpha = (sin(m_sin) + 1) * 127 + 1;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Title_Enter::Draw(void)
{
	//  ���S���W��������W
	float tx, ty;
	tx = m_pos.x - (LOGO_WIDTH * 0.5f);
	ty = m_pos.y - (LOGO_HEIGHT * 0.5f);

	Sprite_DrawAlpha(m_tex, tx, ty, LOGO_WIDTH, LOGO_HEIGHT,m_alpha);
}

//��������������������������������������������������������������������������������
//	�f�X�g���N�^
//��������������������������������������������������������������������������������
Title_Enter::~Title_Enter(void)
{
	Texture_Destroy(&m_tex, 1);
}

//��������������������������������������������������������������������������������
//	���V�[���؂�ւ��\���菈��
//��������������������������������������������������������������������������������
bool Title_Enter::Next_Scene(void)
{
	return m_frame <= 0 ? true : false;
}