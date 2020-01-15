//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[map.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 11/18(Œ)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "water.h"
#include "ground.h"
#include "texture.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define WATER_MAX (86) //	…ƒ^ƒCƒ‹‚Ì”

enum WATER_TYPE
{
	WATER_LINE,
	WATER_L,
	WATER_R,
	WATER_TYPE_MAX
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
struct Water_Matrix //	s—ñ‚Æí—Ş
{
	D3DXMATRIX mtx;
	WATER_TYPE type;
};

class Map {
public:
	virtual void Draw(void) = 0;
	virtual void Update(void) = 0;
};

class Map_Sprint : public Map {
private:
	int m_water_tex_id;
	int m_L_tex_id;
	int m_R_tex_id;
	Water* m_water;
	Water_Matrix m_water_mtx[WATER_MAX];
public:
	Map_Sprint(void);
	~Map_Sprint(void);
	void Draw(void);
	void Update(void);
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

static Map* gp_map = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Init(void)
{
	gp_map = new Map_Sprint;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Uninit(void)
{
	delete gp_map;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Update(void)
{
	gp_map->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Draw(void)
{
	gp_map->Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Map_Sprint ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Map_Sprint::Map_Sprint(void)
{
	m_water_tex_id = Texture_SetLoadFile("Asset/Texture/kawa.png", 0, 0);
	m_L_tex_id = Texture_SetLoadFile("Asset/Texture/l_kawa.png", 0, 0);
	m_R_tex_id = Texture_SetLoadFile("Asset/Texture/r_kawa.png", 0, 0);
	Texture_Load();
	
	m_water = new Water(); //	À‘Ì‚Í‚PŒÂ‚Å‚¢‚¢

	//	…ƒ^ƒCƒ‹•ª‚Ìs—ñ‚ª•K—v
	//	s—ñ‚ÆƒeƒNƒXƒ`ƒƒí—Ş‚ğİ’è
	D3DXMATRIX mtx_world, mtx_rot, mtx_rot_x, mtx_trans;

	float radius = 5.0f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//	‚P–‡–Ú

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

	//	‚Q–‡–Ú
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

	//	‚R–‡–Ú

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

	//	‚S–‡–Ú

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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Map_Sprint ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Map_Sprint::~Map_Sprint(void)
{
	delete m_water;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Map_SprintXVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Sprint::Update(void)
{

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Map_Sprint•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Map_Sprint::Draw(void)
{
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
}