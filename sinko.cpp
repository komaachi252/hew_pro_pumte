//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[sinko.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 1/25(“y)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "texture.h"
#include "sprite.h"
#include "map.h"
#include "uturn.h"
#include <d3dx9.h>
#include "player.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int DIST = 495 / WATER_MAX;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int frame_tex = 0;
static int bar_tex = 0;
static int icon_tex = 0;
static float icon_y;
static float angle;
static bool right;
static int old_index;
static int max_index;
static D3DXVECTOR3 old_vec;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sinko_Init(void)
{
	frame_tex = Texture_SetLoadFile("Asset/Texture/shinko_frame.png", 68, 525);
	bar_tex = Texture_SetLoadFile("Asset/Texture/shinko_bar.png", 35, 503);
	icon_tex = Texture_SetLoadFile("Asset/Texture/shinko_icon.png", 120, 104);
	Texture_Load();

	icon_y = 0.0f;

	right = true;

	old_index = 0;
	max_index = 0;

	old_vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sinko_Uninit(void)
{
	Texture_Destroy(&frame_tex, 1);
	Texture_Destroy(&bar_tex, 1);
	Texture_Destroy(&icon_tex, 1);
	angle = 0.0f;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sinko_Update(void)
{


	if (right) {
		angle += 0.025f;
		if (angle >= 0.6f) {
			right = false;
		}
	}
	if (!right) {
		angle -= 0.025f;
		if (angle <= -0.6f) {
			right = true;
		}
	}


	int index = Get_Map_Index();



	D3DXVECTOR3 vec = *Get_Player_Front();

	float angle = acosf(D3DXVec3Dot(&old_vec, &vec));

	if (max_index - 1 > index) {
		Uturn_Create();
	}

	if (Uturn_Is_Used()) {
		max_index = index;
	}

	icon_y = 590 - index * DIST;

	old_index = index;

	if (index < old_index) {
		old_vec = *Get_Player_Front();
	}

	if (index > max_index) {
		max_index = index;
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Sinko_Draw(void)
{
	Sprite_Draw(frame_tex, 1180.0f, 150.0f);
	Sprite_Draw(bar_tex, 1197.0f, 162.0f);
	Sprite_Draw(icon_tex, 1155.0f, icon_y,0,0,120,104,angle,1155 + 60,icon_y + 52,1);

}
