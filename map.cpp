//ÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúc
//
//
//	èàóù[map.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               çÏê¨é“ ñÓêÅàÍèr
//                                                               çÏê¨ì˙ 11/18(åé)
//ÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúc
#include "water.h"
#include "ground.h"
#include "texture.h"
#include "player.h"
#include <float.h>
#include "debug_font.h"
#include "model.h"
#include "direct3d.h"
#include "map.h"

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	íËêîíËã`
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô

enum WATER_TYPE
{
	WATER_LINE,
	WATER_L,
	WATER_R,
	WATER_TYPE_MAX
};

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ÉNÉâÉXêÈåæ
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
struct Water_Matrix //	çsóÒÇ∆éÌóﬁ
{
	D3DXMATRIX mtx;
	WATER_TYPE type;
};

class Map {
public:
	virtual void Draw(void) = 0;
	virtual void Update(void) = 0;
	virtual float Player_Y(void) = 0;
	virtual bool Search_Y(void) = 0;
	virtual float Player_Angle(void) = 0;
	virtual void Draw_Obj(void) = 0;
	virtual int Get_Index(void) = 0;
};

class Map_Sprint : public Map {
private:
	int m_water_tex_id;
	int m_L_tex_id;
	int m_R_tex_id;
	int m_kusa_id;
	int m_nanakusa_id;
	int m_marukusa_id;
	int m_komachi_id;
	float m_player_y;
	Water* m_water;
	float m_player_angle;
	Water_Matrix m_water_mtx[WATER_MAX];
	int m_index;
public:
	Map_Sprint(void);
	~Map_Sprint(void);
	void Draw(void);
	void Update(void);
	float Player_Y(void);
	float Player_Angle(void);
	bool Search_Y(void);
	void Draw_Obj(void);
	int Get_Index(void);
};

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ÉvÉçÉgÉ^ÉCÉvêÈåæ
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô


//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ÉOÉçÅ[ÉoÉãïœêîêÈåæ
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô

static Map* gp_map = nullptr;

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	èâä˙âªèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Init(void)
{
	gp_map = new Map_Sprint;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	èIóπèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Uninit(void)
{
	delete gp_map;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	çXêVèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Update(void)
{
	gp_map->Update();
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Draw(void)
{
	gp_map->Draw();
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
float Player_Y(void)
{
	if (gp_map == nullptr) {
		return 0.0f;
	}
	return gp_map->Player_Y();
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
float Map_Player_Angle(void)
{
	return gp_map->Player_Angle();
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	ï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
int Get_Map_Index(void)
{
	return gp_map->Get_Index();
}

int Map_Sprint::Get_Index(void)
{
	return m_index;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_Sprint ÉRÉìÉXÉgÉâÉNÉ^
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
Map_Sprint::Map_Sprint(void)
{
	m_water_tex_id = Texture_SetLoadFile("Asset/Texture/kawaline.png", 0, 0);
	m_L_tex_id = Texture_SetLoadFile("Asset/Texture/kawaleft.png", 0, 0);
	m_R_tex_id = Texture_SetLoadFile("Asset/Texture/kawaright.png", 0, 0);
	m_kusa_id = Model_Load("kusa.x");
	m_nanakusa_id = Model_Load("nanakusa.x");
	m_marukusa_id = Model_Load("marukusa.x");
	m_komachi_id = Model_Load("komachi.x");
	Texture_Load();
	
	m_water = new Water(); //	é¿ëÃÇÕÇPå¬Ç≈Ç¢Ç¢

	//	êÖÉ^ÉCÉãï™ÇÃçsóÒÇ™ïKóv
	//	çsóÒÇ∆ÉeÉNÉXÉ`ÉÉéÌóﬁÇê›íË
	D3DXMATRIX mtx_world, mtx_rot, mtx_rot_x, mtx_trans;

	float radius = 5.0f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	m_player_y = 0.0f;

	//	ÇPñáñ⁄

	D3DXMatrixIdentity(&mtx_world);
	
	m_water_mtx[0].mtx = mtx_world;
	m_water_mtx[0].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 10.0f);
	mtx_world = mtx_trans;
	m_water_mtx[1].mtx = mtx_world;
	m_water_mtx[1].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 20.0f);
	mtx_world = mtx_trans;
	m_water_mtx[2].mtx = mtx_world;
	m_water_mtx[2].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 30.0f);
	mtx_world = mtx_trans;
	m_water_mtx[3].mtx = mtx_world;
	m_water_mtx[3].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 40.0f);
	mtx_world = mtx_trans;
	m_water_mtx[4].mtx = mtx_world;
	m_water_mtx[4].type = WATER_R;

	D3DXMatrixTranslation(&mtx_trans, 10.0f, 0.0f, 40.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[5].mtx = mtx_world;
	m_water_mtx[5].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, 0.0f, 40.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[6].mtx = mtx_world;
	m_water_mtx[6].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 40.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[7].mtx = mtx_world;
	m_water_mtx[7].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 40.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[8].mtx = mtx_world;
	m_water_mtx[8].type = WATER_L;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 50.0f);
	mtx_world = mtx_trans;
	m_water_mtx[9].mtx = mtx_world;
	m_water_mtx[9].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 60.0f);
	mtx_world = mtx_trans;
	m_water_mtx[10].mtx = mtx_world;
	m_water_mtx[10].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 70.0f);
	mtx_world = mtx_trans;
	m_water_mtx[11].mtx = mtx_world;
	m_water_mtx[11].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 80.0f);
	mtx_world = mtx_trans;
	m_water_mtx[12].mtx = mtx_world;
	m_water_mtx[12].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, 0.0f, 90.0f);
	mtx_world = mtx_trans;
	m_water_mtx[13].mtx = mtx_world;
	m_water_mtx[13].type = WATER_L;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, 0.0f, 90.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[14].mtx = mtx_world;
	m_water_mtx[14].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, 0.0f, 90.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[15].mtx = mtx_world;
	m_water_mtx[15].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 10.0f, 0.0f, 90.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[16].mtx = mtx_world;
	m_water_mtx[16].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, 0.0f, 90.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[17].mtx = mtx_world;
	m_water_mtx[17].type = WATER_R;

	//	ÇQñáñ⁄
	z = cosf(D3DXToRadian(30)) * radius + radius + 90.0f;
	y = sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[18].mtx = mtx_world;
	m_water_mtx[18].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius + z;
	y = sinf(D3DXToRadian(30)) * radius + sinf(D3DXToRadian(30)) * radius + y;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[19].mtx = mtx_world;
	m_water_mtx[19].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius + z;
	y = sinf(D3DXToRadian(30)) * radius + sinf(D3DXToRadian(30)) * radius + y;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[20].mtx = mtx_world;
	m_water_mtx[20].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + radius + z;
	y = y + sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 0.0f, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[21].mtx = mtx_world;
	m_water_mtx[21].type = WATER_R;


	D3DXMatrixTranslation(&mtx_trans, 10.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[22].mtx = mtx_world;
	m_water_mtx[22].type = WATER_R;

	z = z  - cosf(D3DXToRadian(45)) * radius - radius;
	y = y - sinf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 10.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-45));
	mtx_world = mtx_rot * mtx_rot_x * mtx_trans;
	m_water_mtx[23].mtx = mtx_world;
	m_water_mtx[23].type = WATER_LINE;

	z = z - cosf(D3DXToRadian(45)) * radius - radius;
	y = y - sinf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 10.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[24].mtx = mtx_world;
	m_water_mtx[24].type = WATER_L;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[25].mtx = mtx_world;
	m_water_mtx[25].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[26].mtx = mtx_world;
	m_water_mtx[26].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[27].mtx = mtx_world;
	m_water_mtx[27].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[28].mtx = mtx_world;
	m_water_mtx[28].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 50.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[29].mtx = mtx_world;
	m_water_mtx[29].type = WATER_L;

	z = cosf(D3DXToRadian(30)) * radius + radius + z;
	y = y - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 50.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(30));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[30].mtx = mtx_world;
	m_water_mtx[30].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius + z;
	y = y - sinf(D3DXToRadian(30)) * radius - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 50.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(30));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[31].mtx = mtx_world;
	m_water_mtx[31].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + z + radius;
	y = y - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 50.0f, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[32].mtx = mtx_world;
	m_water_mtx[32].type = WATER_L;

	D3DXMatrixTranslation(&mtx_trans, 40.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[33].mtx = mtx_world;
	m_water_mtx[33].type = WATER_LINE;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[34].mtx = mtx_world;
	m_water_mtx[34].type = WATER_L;

	z = z - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, 30.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[35].mtx = mtx_world;
	m_water_mtx[35].type = WATER_R;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[36].mtx = mtx_world;
	m_water_mtx[36].type = WATER_R;

	z = cosf(D3DXToRadian(30)) * radius + z + radius;
	y = y - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[37].mtx = mtx_world;
	m_water_mtx[37].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius + z;
	y = y - sinf(D3DXToRadian(30)) * radius - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[38].mtx = mtx_world;
	m_water_mtx[38].type = WATER_LINE;

	z = cosf(D3DXToRadian(30)) * radius + radius + z;
	y = y - sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, 20.0f, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[39].mtx = mtx_world;
	m_water_mtx[39].type = WATER_R;

	y = y - sinf(D3DXToRadian(30)) * radius;

	x = 20.0f;
	x = x + radius + cosf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot_x * mtx_rot * mtx_trans;
	m_water_mtx[40].mtx = mtx_world;
	m_water_mtx[40].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(30)) * radius * 2;
	x = x + cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot_x * mtx_rot * mtx_trans;
	m_water_mtx[41].mtx = mtx_world;
	m_water_mtx[41].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(30)) * radius;
	x = x + radius + cosf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[42].mtx = mtx_world;
	m_water_mtx[42].type = WATER_L;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[43].mtx = mtx_world;
	m_water_mtx[43].type = WATER_LINE;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[44].mtx = mtx_world;
	m_water_mtx[44].type = WATER_LINE;

	//	ÇRñáñ⁄

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[45].mtx = mtx_world;
	m_water_mtx[45].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[46].mtx = mtx_world;
	m_water_mtx[46].type = WATER_L;

	y = y + sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-20));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[47].mtx = mtx_world;
	m_water_mtx[47].type = WATER_LINE;

	y = y + sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[48].mtx = mtx_world;
	m_water_mtx[48].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[49].mtx = mtx_world;
	m_water_mtx[49].type = WATER_L;

	y = y - sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(20));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[50].mtx = mtx_world;
	m_water_mtx[50].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[51].mtx = mtx_world;
	m_water_mtx[51].type = WATER_L;

	x = x - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[52].mtx = mtx_world;
	m_water_mtx[52].type = WATER_R;

	y = y - sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(20));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[53].mtx = mtx_world;
	m_water_mtx[53].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(20)) * radius;
	z = z + cosf(D3DXToRadian(20)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[54].mtx = mtx_world;
	m_water_mtx[54].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[55].mtx = mtx_world;
	m_water_mtx[55].type = WATER_L;

	z = z + cosf(D3DXToRadian(30)) * radius + radius;
	y = y + sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[56].mtx = mtx_world;
	m_water_mtx[56].type = WATER_LINE;

	z = z + cosf(D3DXToRadian(30)) * radius + cosf(D3DXToRadian(30)) * radius;
	y = y + sinf(D3DXToRadian(30)) * radius + sinf(D3DXToRadian(30)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(-30));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[57].mtx = mtx_world;
	m_water_mtx[57].type = WATER_LINE;

	//	ÇSñáñ⁄

	y = y + sinf(D3DXToRadian(30)) * radius;
	z = z + cosf(D3DXToRadian(30)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[58].mtx = mtx_world;
	m_water_mtx[58].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[59].mtx = mtx_world;
	m_water_mtx[59].type = WATER_L;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[60].mtx = mtx_world;
	m_water_mtx[60].type = WATER_L;

	x = x - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[61].mtx = mtx_world;
	m_water_mtx[61].type = WATER_R;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[62].mtx = mtx_world;
	m_water_mtx[62].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[63].mtx = mtx_world;
	m_water_mtx[63].type = WATER_L;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[64].mtx = mtx_world;
	m_water_mtx[64].type = WATER_L;

	x = x - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[65].mtx = mtx_world;
	m_water_mtx[65].type = WATER_R;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[66].mtx = mtx_world;
	m_water_mtx[66].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[67].mtx = mtx_world;
	m_water_mtx[67].type = WATER_L;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[68].mtx = mtx_world;
	m_water_mtx[68].type = WATER_L;

	x = x - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[69].mtx = mtx_world;
	m_water_mtx[69].type = WATER_R;


	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[70].mtx = mtx_world;
	m_water_mtx[70].type = WATER_R;

	x = x + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[71].mtx = mtx_world;
	m_water_mtx[71].type = WATER_L;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[72].mtx = mtx_world;
	m_water_mtx[72].type = WATER_L;

	x = x - radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-90));
	mtx_world = mtx_rot * mtx_trans;
	m_water_mtx[73].mtx = mtx_world;
	m_water_mtx[73].type = WATER_R;

	y = y - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[74].mtx = mtx_world;
	m_water_mtx[74].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[75].mtx = mtx_world;
	m_water_mtx[75].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[76].mtx = mtx_world;
	m_water_mtx[76].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[77].mtx = mtx_world;
	m_water_mtx[77].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[78].mtx = mtx_world;
	m_water_mtx[78].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[79].mtx = mtx_world;
	m_water_mtx[79].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + cosf(D3DXToRadian(45)) * radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(45));
	mtx_world = mtx_rot_x * mtx_trans;
	m_water_mtx[80].mtx = mtx_world;
	m_water_mtx[80].type = WATER_LINE;

	y = y - sinf(D3DXToRadian(45)) * radius;
	z = z + cosf(D3DXToRadian(45)) * radius + radius;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[81].mtx = mtx_world;
	m_water_mtx[81].type = WATER_LINE;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[82].mtx = mtx_world;
	m_water_mtx[82].type = WATER_LINE;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[83].mtx = mtx_world;
	m_water_mtx[83].type = WATER_LINE;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[84].mtx = mtx_world;
	m_water_mtx[84].type = WATER_LINE;

	z = z + radius * 2;

	D3DXMatrixTranslation(&mtx_trans, x, y, z);
	mtx_world = mtx_trans;
	m_water_mtx[85].mtx = mtx_world;
	m_water_mtx[85].type = WATER_LINE;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_Sprint ÉfÉXÉgÉâÉNÉ^
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
Map_Sprint::~Map_Sprint(void)
{
	Texture_Destroy(&m_water_tex_id, 1);
	Texture_Destroy(&m_L_tex_id, 1);
	Texture_Destroy(&m_R_tex_id, 1);
	Model_Destroy(&m_kusa_id, 1);
	Model_Destroy(&m_nanakusa_id, 1);
	Model_Destroy(&m_marukusa_id, 1);
	Model_Destroy(&m_komachi_id, 1);
	
	delete m_water;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_SprintçXêVèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Sprint::Update(void)
{
	Search_Y();
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_SprintçXêVèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
float Map_Sprint::Player_Y(void)
{
	return m_player_y;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_SprintçXêVèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
float Map_Sprint::Player_Angle(void)
{
	return m_player_angle;
}



//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_SprintçXêVèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
bool Map_Sprint::Search_Y(void)
{
	// ÉvÉåÉCÉÑÅ[ÇÃç¿ïWÇ©ÇÁëŒè€ÇÃÉÅÉbÉVÉÖÇíTç∏
	D3DXVECTOR3 p_pos(PlayerGet()->mtxWorld._41, PlayerGet()->mtxWorld._42, PlayerGet()->mtxWorld._43);

	float min_dist = FLT_MAX;
	int min_index = WATER_MAX;
	for (int i = 0; i < WATER_MAX; i++) {
		if (min_dist > fabsf((m_water_mtx[i].mtx._41 - p_pos.x) * (m_water_mtx[i].mtx._41 - p_pos.x) + (m_water_mtx[i].mtx._43 - p_pos.z) * (m_water_mtx[i].mtx._43 - p_pos.z))) {
			min_dist = fabsf((m_water_mtx[i].mtx._41 - p_pos.x) * (m_water_mtx[i].mtx._41 - p_pos.x) + (m_water_mtx[i].mtx._43 - p_pos.z) * (m_water_mtx[i].mtx._43 - p_pos.z));
			min_index = i;
		}
	}
	if (min_index == WATER_MAX) {
		return false;
	}

	// ëŒè€ÉÅÉbÉVÉÖÇÃçsóÒÇ≈í∏ì_Çïœä∑
	WaterVertex* vtx_ptr;
	m_water->m_vertex_buffer_ptr->Lock(0, 0, (void**)&vtx_ptr, D3DLOCK_DISCARD);

	D3DXVECTOR3 vertex_pos[4];

	for (int i = 0; i < 4; i++) {
		vertex_pos[i] = vtx_ptr[i].position;
		D3DXVec3TransformNormal(&vertex_pos[i], &vertex_pos[i], &m_water_mtx[min_index].mtx);
		vertex_pos[i] += D3DXVECTOR3(m_water_mtx[min_index].mtx._41, m_water_mtx[min_index].mtx._42, m_water_mtx[min_index].mtx._43);
	}

	m_water->m_vertex_buffer_ptr->Unlock();

	//Å@ñ@ê¸ÇçÏÇÈ
	D3DXVECTOR3 AB_vec(vertex_pos[1].x - vertex_pos[0].x, vertex_pos[1].y - vertex_pos[0].y, vertex_pos[1].z - vertex_pos[0].z);

	D3DXVECTOR3 BC_vec(vertex_pos[2].x - vertex_pos[0].x, vertex_pos[2].y - vertex_pos[0].y, vertex_pos[2].z - vertex_pos[0].z);
	D3DXVec3Normalize(&AB_vec, &AB_vec);
	D3DXVec3Normalize(&BC_vec, &BC_vec);

	D3DXVECTOR3 normal;
	D3DXVec3Cross(&normal, &AB_vec, &BC_vec);

	if (normal.y < 0.0f) {
		normal.x *= -1.0f;
		normal.y *= -1.0f;
		normal.z *= -1.0f;
	}
	D3DXVec3Normalize(&normal, &normal);
	//	í∏ì_AÇäÓèÄÇ…ì_Çn(ÉvÉåÉCÉÑÅ[ç¿ïW)ÇÃyç¿ïWÇéZèo

	//	divideÇ™0Ç»ÇÁÇŒí∏ì_ÇÃÇxç¿ïWÇ…çáÇÌÇπÇÈ
	float divide = normal.y * ((normal.x * (p_pos.x - vertex_pos[1].x)) + (normal.z * (p_pos.z - vertex_pos[1].z)));
	if (divide == 0.0f) {
		m_player_y = vertex_pos[1].y;
		m_index = min_index;
	}
	if (divide != 0.0f) {
		m_player_y = vertex_pos[1].y - (1.0f / normal.y * ((normal.x * (p_pos.x - vertex_pos[1].x)) + (normal.z * (p_pos.z - vertex_pos[1].z))));
		m_index = min_index;
	}

	//	ÉvÉåÉCÉÑÅ[ÇÃñ@ê¸Ç∆êÖÇÃñ@ê¸ÇÃÇ»Ç∑äpÇåüèo
	D3DXVECTOR3 p_up_vec = PlayerGet()->vecUp;

	//p_up_vec = D3DXVECTOR3(0, 1, 0);

	float angle = acosf(D3DXVec3Dot(&normal, &p_up_vec));

	//	1ìxñ¢ñûÇÃäpìxÇÕë„ì¸ÇµÇ»Ç¢
	if (fabs(angle) < D3DXToRadian(1)) {
		m_player_angle = 0.0f;
		return true;
	}

	if (fabs(angle) < D3DXToRadian(5)) {
		m_player_angle = angle;
		return true;
	}
	
	D3DXVECTOR3 cross;

	D3DXVec3Cross(&cross, &normal, &p_up_vec);

	if (cross.y > 0.0f) {
		m_player_angle = D3DXToRadian(5);
	}
	else {
		m_player_angle = -D3DXToRadian(5);
	}

	return true;
}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_Sprintï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Sprint::Draw(void)
{
	//GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	Draw_Obj();
	
	//GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	for (int i = 0; i < WATER_MAX; i++) {
		switch (m_water_mtx[i].type)
		{
		case WATER_LINE:
			m_water->Draw(m_water_tex_id, m_water_mtx[i].mtx);
			break;
		case WATER_L:
			m_water->Draw(m_L_tex_id, m_water_mtx[i].mtx);
			break;
		case WATER_R:
			m_water->Draw(m_R_tex_id, m_water_mtx[i].mtx);
			break;
		default:
			break;
		}
	}
	//GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	DebugFont_Draw(10, 500, "%3.3f", m_player_y);
	DebugFont_Draw(10, 550, "%d", m_index);
	DebugFont_Draw(10, 600, "%3.3f", m_player_angle);

}

//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
//	Map_Sprintï`âÊèàóù
//ÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅôÅô
void Map_Sprint::Draw_Obj(void)
{
	D3DXMATRIX mtx_trans, mtx_rot, mtx_scale, mtx_world;

	{//å„ÇÎ
		D3DXMatrixTranslation(&mtx_trans, 15.0f, -0.001f, -25.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -15.0f, -0.001f, -25.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);
	}

	D3DXMatrixTranslation(&mtx_trans, 25.0f, -0.001f, 15.0f);
	D3DXMatrixRotationY(&mtx_rot, 0.0f);
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 50.0f, -0.005f, 16.0f);
	D3DXMatrixRotationY(&mtx_rot, 0.0f);
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 50.0f, -0.005f, 17.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(30));
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_rot * mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 64.0f, -0.1f, 48.0f);
	D3DXMatrixRotationY(&mtx_rot, 0.0f);
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 64.0f, -0.1f, 88.0f);
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 74.0f, -2.0f, 118.0f);
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	mtx_world = mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);

	D3DXMatrixTranslation(&mtx_trans, 49.0f, -0.25f, 98.0f);
	D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(30));
	D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.0f);
	mtx_world = mtx_rot * mtx_scale * mtx_trans;

	Model_Draw(m_kusa_id, mtx_world);




	{
		D3DXMatrixTranslation(&mtx_trans, 54.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 53.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 52.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 49.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 46.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 43.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 40.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 37.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 34.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 31.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 28.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 25.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 22.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 19.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 16.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 15.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 2.65f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 13.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 105.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.5f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 105.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 106.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 104.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 105.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 106.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 5.0f, -0.1f, 106.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 6.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.65f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	
		D3DXMatrixTranslation(&mtx_trans, 5.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 5.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 5.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	
		D3DXMatrixTranslation(&mtx_trans, 4.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 4.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 4.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 4.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 3.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 3.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 3.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 9.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 9.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 9.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 9.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 11.0f, -0.1f, 107.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.3f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 11.0f, -0.1f, 108.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 11.0f, -0.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 11.0f, -0.1f, 110.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 13.0f, -0.1f, 111.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 13.0f, -0.1f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 13.0f, -0.1f, 113.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.4f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


	}


	{
		D3DXMatrixTranslation(&mtx_trans, -25.0f, -0.001f, 15.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -25.0f, -0.001f, 45.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -5.0f, -1.2f, 60.0f);
		D3DXMatrixScaling(&mtx_scale, 3.0f, 1.0f, 3.0f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(-30));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 5.0f, -0.001f, 65.0f);
		D3DXMatrixScaling(&mtx_scale, 3.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -10.0f, -0.5f, 85.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(30));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -25.0f, -0.001f, 85.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;

		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -25.0f, -0.001f, 115.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 5.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -15.0f, -0.001f, 135.0f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 5.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	}
	
	{
		D3DXMatrixTranslation(&mtx_trans, -7.5f, -0.001f, 98.0f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 3.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -7.2f, -0.001f, 103.0f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 4.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -6.5f, -0.001f, 112.0f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 5.0f, 1.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -6.2f, -0.001f, 124.0f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 6.0f, 1.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -6.0f, -0.001f, 127.0f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 7.0f, 1.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -5.0f, -0.001f, 130.0f);
		D3DXMatrixScaling(&mtx_scale, 1.2f, 7.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -2.0f, -0.001f, 131.0f);
		D3DXMatrixScaling(&mtx_scale, 1.2f, 7.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 0.0f, -0.001f, 131.2f);
		D3DXMatrixScaling(&mtx_scale, 1.2f, 7.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 7.3f, 14.5f, 131.2f);
		D3DXMatrixScaling(&mtx_scale, 0.1f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.9f, 14.5f, 131.2f);
		D3DXMatrixScaling(&mtx_scale, 0.1f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 12.0f, 14.5f, 130.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 15.0f, 14.5f, 129.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 16.0f, 14.5f, 128.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 17.0f, 14.5f, 127.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 18.0f, 14.5f, 126.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 1.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 19.0f, 14.5f, 125.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 1.0f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 20.0f, 14.5f, 124.2f);
		D3DXMatrixScaling(&mtx_scale, 0.6f, 1.0f, 0.35f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 20.0f, 11.0f, 117.5f);
		D3DXMatrixScaling(&mtx_scale, 0.6f, 1.0f, 0.42f);
		D3DXMatrixRotationX(&mtx_rot, -D3DXToRadian(20));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


	}




	{
		D3DXMatrixTranslation(&mtx_trans, 52.0f, -65.3f, 460.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 86.0f, -65.3f, 460.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 92.0f, -65.0f, 435.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 92.0f, -65.0f, 405.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 92.0f, -58.3f, 386.6f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 92.0f, -43.3f, 371.8f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 92.0f, -31.8f, 360.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.3f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_scale * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 42.5f, -58.3f, 386.6f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 42.5f, -43.3f, 371.8f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 42.5f, -31.8f, 360.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.3f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(45));
		mtx_world = mtx_scale * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 42.5f, -65.3f, 435.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 42.5f, -65.3f, 405.0f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


	}

	{
		D3DXMatrixTranslation(&mtx_trans, 75.0f, -15.6f, 304.0f);
		D3DXMatrixScaling(&mtx_scale, 4.0f, 0.01f, 4.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	}

	{
		D3DXMatrixTranslation(&mtx_trans, 82.0f, -20.5f, 255.3f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.01f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(-30));
		mtx_world = mtx_scale * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 52.5f, -20.5f, 255.3f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.01f);
		D3DXMatrixRotationX(&mtx_rot, D3DXToRadian(-30));
		mtx_world = mtx_scale * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

	}

	{
		D3DXMatrixTranslation(&mtx_trans, 92.0f, -25.3f, 239.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 64.0f, -25.6f, 225.2f);
		D3DXMatrixScaling(&mtx_scale, 4.0f, 0.05f, 2.2f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 64.0f, -25.6f, 200.2f);
		D3DXMatrixScaling(&mtx_scale, 4.0f, 0.4f, 4.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);



		D3DXMatrixTranslation(&mtx_trans, 65.0f, -25.3f, 203.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 57.0f, -25.3f, 200.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 58.0f, -25.6f, 218.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 1.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 47.0f, -25.3f, 154.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 1.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 80.0f, -25.3f, 154.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 1.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 47.0f, -25.3f, 184.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 1.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

	}

	D3DXMATRIX mtx_rot_x;
	{
		D3DXMatrixTranslation(&mtx_trans, 37.0f, -20.3f, 164.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
		mtx_world = mtx_rot_x * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 37.0f, -20.3f, 144.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 8.0f, 1.6f);
		D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
		mtx_world = mtx_scale * mtx_rot_x * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
		
		D3DXMatrixTranslation(&mtx_trans, 32.0f, -16.3f, 162.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 2.0f, 0.8f);
		D3DXMatrixRotationX(&mtx_rot_x, D3DXToRadian(30));
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
		mtx_world = mtx_scale * mtx_rot_x * mtx_rot * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
		
		D3DXMatrixTranslation(&mtx_trans, 20.5f, -12.5f, 162.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 1.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 16.5f, -12.5f, 160.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 1.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 14.5f, -12.5f, 158.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 1.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);




		D3DXMatrixTranslation(&mtx_trans, 23.0f, -20.3f, 140.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 3.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 23.0f, -20.3f, 130.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 5.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);



		D3DXMatrixTranslation(&mtx_trans, 21.0f, -15.3f, 168.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 3.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 15.0f, -15.3f, 168.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 3.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 12.0f, -15.3f, 160.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 3.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 10.0f, -15.3f, 139.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 4.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -15.3f, 148.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 4.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -15.3f, 130.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 8.0f, -15.3f, 120.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
		
		D3DXMatrixTranslation(&mtx_trans, 8.0f, -15.3f, 110.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 6.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
		
		D3DXMatrixTranslation(&mtx_trans, 32.0f, -15.3f, 143.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 40.0f, -15.3f, 143.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 45.0f, -15.3f, 143.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 48.0f, -15.3f, 143.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 52.0f, -15.3f, 143.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 55.0f, -15.3f, 140.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 20.0f, -15.3f, 118.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 6.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 24.0f, -15.3f, 113.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 6.0f, 1.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 29.0f, -15.3f, 110.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 6.0f, 1.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 32.0f, -15.3f, 114.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 6.0f, 1.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 36.0f, -15.3f, 118.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 1.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 20.0f, -15.3f, 115.2f);
		D3DXMatrixScaling(&mtx_scale, 4.0f, 9.0f, 0.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);


		D3DXMatrixTranslation(&mtx_trans, 38.0f, -15.3f, 119.2f);
		D3DXMatrixScaling(&mtx_scale, 1.0f, 9.0f, 2.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 43.0f, -15.3f, 119.2f);
		D3DXMatrixScaling(&mtx_scale, 0.5f, 9.0f, 2.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, -5.2f, -15.3f, 125.2f);
		D3DXMatrixScaling(&mtx_scale, 2.0f, 1.0f, 2.0f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	}


	{
		D3DXMatrixTranslation(&mtx_trans, 29.0f, -20.4f, 141.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 10.0f, 0.4f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 27.0f, -20.4f, 140.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 10.0f, 0.4f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 26.0f, -20.4f, 137.2f);
		D3DXMatrixScaling(&mtx_scale, 0.4f, 10.0f, 0.4f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 25.0f, -20.4f, 135.2f);
		D3DXMatrixScaling(&mtx_scale, 0.1f, 10.0f, 0.6f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);
	}

	{
		D3DXMatrixTranslation(&mtx_trans, -0.5f, -0.001f, 114.5f);
		D3DXMatrixScaling(&mtx_scale, 5.8f, 7.5f, 6.5f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_nanakusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 30.0f, 7.15f, 114.2f);
		D3DXMatrixScaling(&mtx_scale, 1.6f, 2.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 50.0f, -2.1f, 118.2f);
		D3DXMatrixScaling(&mtx_scale, 5.8f, 5.0f, 4.3f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_nanakusa_id, mtx_world);
	}

	{
		D3DXMatrixTranslation(&mtx_trans, 30.0f, 7.15f, 114.2f);
		D3DXMatrixScaling(&mtx_scale, 1.6f, 2.0f, 0.1f);
		mtx_world = mtx_scale * mtx_trans;
		//Model_Draw(m_kusa_id, mtx_world);
	}


	//	ä≈î¬
	{
		D3DXMatrixTranslation(&mtx_trans, 10.0f, -0.5f, 45.2f);
		D3DXMatrixScaling(&mtx_scale, 1.8f, 1.8f, 1.8f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(90));
		mtx_world = mtx_scale * mtx_rot * mtx_trans;
		Model_Draw(m_komachi_id, mtx_world);
	}

	{
		D3DXMatrixTranslation(&mtx_trans, 19.0f, -12.1f, 135.0f);
		D3DXMatrixScaling(&mtx_scale, 5.8f, 5.0f, 4.3f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
		mtx_world = mtx_rot * mtx_scale * mtx_trans;
		Model_Draw(m_nanakusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 12.0f, -12.1f, 109.0f);
		D3DXMatrixScaling(&mtx_scale, 1.2f, 5.0f, 1.2f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_marukusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 13.0f, -2.2f, 127.9f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 15.0f, -2.2f, 124.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		D3DXMatrixRotationY(&mtx_rot, D3DXToRadian(180));
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 16.0f, -2.2f, 121.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 14.0f, -2.2f, 119.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 17.0f, -2.2f, 117.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);



		D3DXMatrixTranslation(&mtx_trans, 25.0f, -2.2f, 117.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 27.0f, -2.2f, 118.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 29.0f, -2.2f, 118.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

		D3DXMatrixTranslation(&mtx_trans, 31.0f, -2.2f, 119.5f);
		D3DXMatrixScaling(&mtx_scale, 0.3f, 0.5f, 0.3f);
		mtx_world = mtx_scale * mtx_trans;
		Model_Draw(m_kusa_id, mtx_world);

	}

}
