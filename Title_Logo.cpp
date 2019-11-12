//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Title_Logo.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 11/11(ŒŽ)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "common.h"
#include "sprite.h"
#include "texture.h"
#include "d3dx9.h"


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TITLE_LOGO_WIDTH = 483;
static const int TITLE_LOGO_HEIGHT = 246;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
class Title_Logo {
private:
	D3DXVECTOR2 pos;
	int tex;
public:
	Title_Logo(void);
	~Title_Logo(void);
	void Update(void);
	void Draw(void);
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static Title_Logo* gp_title_logo = nullptr;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo_Init(void)
{
	gp_title_logo = new Title_Logo;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo_Uninit(void)
{
	delete gp_title_logo;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo_Update(void)
{
	gp_title_logo->Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo_Draw(void)
{
	gp_title_logo->Draw();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Title_Logo ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Title_Logo::Title_Logo(void)
{
	tex = Texture_SetLoadFile("Asset/Texture/Title_Logo.png", TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
	Texture_Load();

	//  ’†SÀ•W
	gp_title_logo->pos = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Title_Logo ƒfƒXƒgƒ‰ƒNƒ^
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
Title_Logo::~Title_Logo(void)
{
	Texture_Destroy(&tex, 1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Title_LogoXVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo::Update(void)
{
	//  À•W•Ï‚¦‚é‚Ì‚©‚È[
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Title_Logo•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Title_Logo::Draw(void)
{
	//  ’†SÀ•W¨¶ãÀ•W
	float tx, ty;
	tx = gp_title_logo->pos.x - (TITLE_LOGO_WIDTH * 0.5f);
	ty = gp_title_logo->pos.y - (TITLE_LOGO_HEIGHT * 0.5f);
	Sprite_Draw(tex, tx, ty);
}




