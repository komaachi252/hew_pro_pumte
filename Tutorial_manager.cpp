//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Tutorial_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 12/17(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "input.h"
#include "fade.h"
#include "scene.h"
#include "camera.h"
#include "UI.h"
#include "water.h"
#include "player.h"
#include <d3d9.h>
#include "texture.h"
#include <memory>
#include "sprite.h"
#include "tutorial_player.h"
#include "data.h"
#include "sound.h"

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

	int m_tutorial_tex_id;
	int m_water_tex_id;
	int m_L_tex_id;
	int m_R_tex_id;
	int m_L_arrow_tex;
	int m_R_arrow_tex;
	int m_frame_id;

	int* m_player_tex;
	int m_ready_tex;
	int m_ok_tex;
	bool* m_ok_list;
	float m_sin;
	int m_alpha;
	PLAY_MODE m_mode;
public:
	Tutorial_Manager();
	virtual ~Tutorial_Manager();
	void Update();
	void Draw();
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
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager_Draw(void)
{
	gp_manager->Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Tutorial_Manager::Tutorial_Manager(void):m_is_fade(false)
{
	m_water_tex_id = Texture_SetLoadFile("Asset/Texture/kawaline.png", 0, 0);
	m_L_tex_id = Texture_SetLoadFile("Asset/Texture/kawaleft.png", 0, 0);
	m_R_tex_id = Texture_SetLoadFile("Asset/Texture/kawaright.png", 0, 0);
	m_L_arrow_tex = Texture_SetLoadFile("Asset/Texture/arrow_L.png", 256, 256);
	m_R_arrow_tex = Texture_SetLoadFile("Asset/Texture/arrow_R.png", 256, 256);
	m_tutorial_tex_id = Texture_SetLoadFile("Asset/Texture/tuto.png", 512, 141);
	m_frame_id = Texture_SetLoadFile("Asset/Texture/frame.png", 265, 92);
	m_ready_tex = Texture_SetLoadFile("Asset/Texture/readyoff.png", 206, 50);
	m_ok_tex = Texture_SetLoadFile("Asset/Texture/readyon.png", 206, 50);
	Texture_Load();

	m_mode = Get_Mode();
	if (m_mode == MODE_2) {
		m_ok_list = new bool[2];
		for (int i = 0; i < 2; i++) {
			m_ok_list[i] = false;
		}
		m_player_tex = new int[2];
		m_player_tex[0] = Texture_SetLoadFile("Asset/Texture/p1.png", 86, 101);
		m_player_tex[1] = Texture_SetLoadFile("Asset/Texture/p2.png", 86, 90);
	}else {
		m_ok_list = new bool[4];
		for (int i = 0; i < 4; i++) {
			m_ok_list[i] = false;
		}
		m_player_tex = new int[4];
		m_player_tex[0] = Texture_SetLoadFile("Asset/Texture/p1.png", 86, 101);
		m_player_tex[1] = Texture_SetLoadFile("Asset/Texture/p2.png", 86, 90);
		m_player_tex[2] = Texture_SetLoadFile("Asset/Texture/p3.png", 86, 88);
		m_player_tex[3] = Texture_SetLoadFile("Asset/Texture/p4.png", 86, 86);
	}
	Texture_Load();
	m_sin = 0.0f;
	m_alpha = 255;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Tutorial_Manager::~Tutorial_Manager(void)
{
	Texture_Destroy(&m_L_arrow_tex, 1);
	Texture_Destroy(&m_R_arrow_tex, 1);
	Texture_Destroy(&m_L_tex_id, 1);
	Texture_Destroy(&m_R_tex_id, 1);
	Texture_Destroy(&m_water_tex_id, 1);
	Texture_Destroy(&m_tutorial_tex_id,1);
	Texture_Destroy(&m_frame_id,1);
	Texture_Destroy(&m_ok_tex,1);
	Texture_Destroy(&m_ready_tex,1);

	int player_num;
	if (m_mode == PLAY_MODE::MODE_2) {
		player_num = 2;
	}
	else {
		player_num = 4;
	}
	for (int i = 0; i < player_num; i++) {
		Texture_Destroy(&m_player_tex[i], 1);
	}
	delete[] m_ok_list;
	delete[] m_player_tex;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager::Update(void)
{
	m_sin += 0.1f;

	m_alpha = (sin(m_sin) + 1) * 127 + 1;

	bool is_next = true;
	if (m_mode == PLAY_MODE::MODE_2) {
		for (int i = 0; i < 2; i++) {
			if (!m_ok_list[i]) {
				is_next = false;
			}
		}
		if (Keyboard_IsTrigger(DIK_Q)) {
			PlaySound(SOUND_LABEL_SE_MENU);
			m_ok_list[0] = true;
		}
		if (Keyboard_IsTrigger(DIK_W)) {
			PlaySound(SOUND_LABEL_SE_MENU);
			m_ok_list[1] = true;
		}

	}
	else {
		for (int i = 0; i < 4; i++) {
			if (!m_ok_list[i]) {
				is_next = false;
			}
		}
	}

	if (is_next && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (Keyboard_IsTrigger(DIK_RETURN) && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_GAME);
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Tutorial_Manager::Draw(void)
{
	D3DXVECTOR3 p_pos(TutoPlayerGet()->mtxWorld._41, TutoPlayerGet()->mtxWorld._42, TutoPlayerGet()->mtxWorld._43);
	{
		// ì‚Ìƒ^ƒCƒ‹
		std::unique_ptr<Water> w(new Water());

		D3DXMATRIX mtx_world, mtx_trans, mtx_rot;

		D3DXMatrixIdentity(&mtx_world);
		w->Draw(m_water_tex_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 10.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 20.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 30.0f);
		w->Draw(m_R_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, 0.0f, 30.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 20.0f, 0.0f, 30.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 30.0f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
		mtx_world = mtx_rot * mtx_trans;
		w->Draw(m_L_tex_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 40.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 50.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 60.0f);
		w->Draw(m_L_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 20.0f, 0.0f, 60.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, 0.0f, 60.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 60.0f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
		mtx_world = mtx_rot * mtx_trans;
		w->Draw(m_R_tex_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 70.0f);
		w->Draw(m_water_tex_id, mtx_trans);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 80.0f);
		w->Draw(m_water_tex_id, mtx_trans);
	}
	Camera_2D();
	D3DXVECTOR3 arrow_right_pos(0.0f, 0.0f, 25.0f);
	if (20.0f > fabsf((arrow_right_pos.x - p_pos.x) * (arrow_right_pos.x - p_pos.x) + (arrow_right_pos.z - p_pos.z) * (arrow_right_pos.z - p_pos.z))) {
		Sprite_Draw(m_R_arrow_tex, 500, 0);
	}

	arrow_right_pos = D3DXVECTOR3(25.0f, 0.0f, 30.0f);

	if (20.0f > fabsf((arrow_right_pos.x - p_pos.x) * (arrow_right_pos.x - p_pos.x) + (arrow_right_pos.z - p_pos.z) * (arrow_right_pos.z - p_pos.z))) {
		Sprite_Draw(m_L_arrow_tex, 500, 0);
	}

	arrow_right_pos = D3DXVECTOR3(30.0f, 0.0f, 55.0f);

	if (20.0f > fabsf((arrow_right_pos.x - p_pos.x) * (arrow_right_pos.x - p_pos.x) + (arrow_right_pos.z - p_pos.z) * (arrow_right_pos.z - p_pos.z))) {
		Sprite_Draw(m_L_arrow_tex, 500, 0);
	}

	arrow_right_pos = D3DXVECTOR3(5.0f, 0.0f, 60.0f);

	if (20.0f > fabsf((arrow_right_pos.x - p_pos.x) * (arrow_right_pos.x - p_pos.x) + (arrow_right_pos.z - p_pos.z) * (arrow_right_pos.z - p_pos.z))) {
		Sprite_Draw(m_R_arrow_tex, 500, 0);
	}

	//	ƒ`ƒ…[ƒgƒŠƒAƒ‹
	Sprite_DrawAlpha(m_tutorial_tex_id, 700, 0, 512, 141, m_alpha);

	//	Ready
	int player_num;
	if (m_mode == PLAY_MODE::MODE_2) {
		player_num = 2;
	}else {
		player_num = 4;
	}
	for (int i = 0; i < player_num; i++) {
		Sprite_Draw(m_frame_id, 1000, 350 + i * 80);
		Sprite_Draw(m_player_tex[i], 930, 350 + i * 80);
		if (m_ok_list[i]) {
			Sprite_Draw(m_ok_tex, 1030, 370 + i * 80);
		}else {
			Sprite_Draw(m_ready_tex, 1030, 370 + i * 80);
		}
	}
	


}