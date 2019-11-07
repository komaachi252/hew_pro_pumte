#include "texture.h"
#include "sprite.h"
#include "UI.h"
#include "number.h"
#include "common.h"

#define TEX_HIGHT (196)
#define COUNTUP_TIME (0.017)
#define GATE_NUM (16)
#define DECIMAL_POINT (100)
#define NUM_SPACE (16)
#define TIME_DIGIT (5)

static int g_UI_tex = 0;
static double g_time = 0.0f;
static int g_gate_count = 0;

void UI_Init(void)
{
	Number_Init();
	g_UI_tex = Texture_SetLoadFile("Asset/Texture/UI2.png", SCREEN_WIDTH, TEX_HIGHT);
	g_time = 0.0f;
	g_gate_count = 0;
}
	
void UI_Uninit(void)
{
	Texture_Destroy();
}
void UI_Update(void)
{
	g_time += COUNTUP_TIME;															   //タイムのカウントアップ
	//g_gate_count = Get_GateNum();                                                    //ゲート通過数の取得

}
void UI_Draw()
{
	Texture_Load();
	Sprite_Draw(g_UI_tex, 0, 0);
	Number_Draw(GATE_NUM/10,224,128);
	Number_Draw(GATE_NUM % 10, 242, 128);
	Number_Draw(g_gate_count/10, 152, 128);
	Number_Draw(g_gate_count%10, 170, 128);

	int num;
	int time = g_time * DECIMAL_POINT;
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		num = time % 10;
		Number_Draw(num,224-i*18,64);
		time = time / 10;
	}
}



