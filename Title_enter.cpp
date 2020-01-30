//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	タイトルエンター処理[Title_Enter.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 1/4(土)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include "Title_Enter.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "input.h"
#include "input.h"
#include "xinput.h"
#include "sound.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define NEXT_FRAME (100)

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	コンストラクタ
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
Title_Enter::Title_Enter(void)
{

}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
HRESULT Title_Enter::Init(void)
{
	//	テクスチャ予約番号
	m_tex = Texture_SetLoadFile("Asset/Texture/press_enter.png", LOGO_TEX_WIDTH, LOGO_TEX_HEIGHT);
	Texture_Load();
	//  中心座標
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f);

	m_alpha = 255;

	m_is_next_scene = false;

	m_frame = NEXT_FRAME;

	m_sin = 0.0f;
	return S_OK;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Title_Enter::Draw(void)
{
	//  中心座標→左上座標
	float tx, ty;
	tx = m_pos.x - (LOGO_WIDTH * 0.5f);
	ty = m_pos.y - (LOGO_HEIGHT * 0.5f);

	Sprite_DrawAlpha(m_tex, tx, ty, LOGO_WIDTH, LOGO_HEIGHT,m_alpha);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	デストラクタ
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
Title_Enter::~Title_Enter(void)
{
	Texture_Destroy(&m_tex, 1);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	次シーン切り替え可能判定処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Title_Enter::Next_Scene(void)
{
	return m_frame <= 0 ? true : false;
}