//UIの表示
//制作者　安保圭一郎
//
//デフォルトでは、仮の画像を元に作られており、左上に表示している　本画像が来た場合調整必須
//ナンバー表示のポジションのマジックナンバーはご容赦ください　（defineするにも何だかなぁ）
//タイム表示の部分は小数点はないが、デフォルトの下2桁は小数となっている
//例：ゲーム画面で「Time:11451」の場合　「114.51秒」となる

#include "texture.h"
#include "sprite.h"
#include "number.h"
#include "common.h"
#include "camera.h"
#include "start_count.h"
#include "direct3d.h"
#include "flag.h"
#include "sound.h"

//#include "gool.h"

#define TEX_HIGHT (196)																	//テクスチャの高さ
#define COUNTUP_TIME (0.017)															//タイムのインクリメント数　120秒で2.4秒の誤差アリ
#define GATE_NUM (10)																	//全てのゲート数　テスト用で16を入れている
#define DECIMAL_POINT (100)																//小数点以下2桁を表示するために100倍する用の数値
#define NUM_SPACE (28)																	//数字と数字の間
#define TIME_DIGIT (5)																	//タイムの桁数　下2桁が小数

/*																						UIの画像が複数枚になった時用の番号付け
enum UI_TYPE
{
UI_TIME,
UI_GATE,
UI_TYPE_MAX
};

*/

static int g_ui_timer_tex = 0;																//UIのテクスチャを保持する変数
static int g_ui_flag_tex = 0;																//UIのテクスチャを保持する変数
static int g_period_tex = 0;														    //ピリオドのテクスチャを保持する変数
static int g_goal_tex = 0;														    //ピリオドのテクスチャを保持する変数
static int g_new_tex = 0;														    //ピリオドのテクスチャを保持する変数
static double g_time = 0.0f;															//タイムを保持する変数
static int g_gate_count = 0;															//通過したゲート数を保持する変数
static int g_old_count = 0;															//通過したゲート数を保持する変数
static bool g_goal_sound;															//通過したゲート数を保持する変数

void UI_Init(void)
{
	Number_Init();																		//ナンバーのイニット
	g_ui_timer_tex = Texture_SetLoadFile("Asset/Texture/ui_timer.png", 303, 107);	//UIテクスチャ読み込み
	g_ui_flag_tex = Texture_SetLoadFile("Asset/Texture/newflag.png", 303, 107);	//UIテクスチャ読み込み
	g_period_tex = Texture_SetLoadFile("Asset/Texture/period.png", 30, 28);	//UIテクスチャ読み込み
	g_goal_tex = Texture_SetLoadFile("Asset/Texture/goal_logo.png", 294, 294);	//UIテクスチャ読み込み
	g_new_tex = Texture_SetLoadFile("Asset/Texture/flagcount.png", 256, 43);	//UIテクスチャ読み込み
	Texture_Load();  //テクスチャセット
	g_time = 0.0f;																		//タイムの初期化
	g_gate_count = 0;																	//通過ゲート数の初期化
	g_old_count = 0;//通過ゲート数の初期化
	g_goal_sound = false;
}
	
void UI_Uninit(void)
{
	Texture_Destroy(&g_ui_flag_tex, 1);																//テクスチャ解放
	Texture_Destroy(&g_ui_timer_tex, 1);																//テクスチャ解放
	Texture_Destroy(&g_period_tex, 1);																//テクスチャ解放
	Texture_Destroy(&g_goal_tex, 1);																//テクスチャ解放
	
}
void UI_Update(void)
{
	if (!Is_Start_Count_End()) {
		return;
	}
	/*
	if(GoolGetCrear() && !g_goal_sound){
		PlaySound(SOUND_LABEL_WHI);
	}
	if (GoolGetCrear()) {
		return;
	}
	*/
	g_time += COUNTUP_TIME;															   //タイムのカウントアップ


}
void UI_Draw()
{
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_gate_count = FlagGetColiNum();
	if (g_old_count < g_gate_count) {
		PlaySound(SOUND_LABEL_SE_GATE);
		g_old_count = g_gate_count;
	}
	Camera_2D();
	Sprite_Draw(g_ui_timer_tex, 0, 0);														//UIの文字部分の表示
	Sprite_Draw(g_ui_flag_tex, 0, 107);	//UIの文字部分の表示
	//Sprite_Draw(g_new_tex, 75, 136, g_gate_count * 19.69f ,43);
	Sprite_Draw(g_new_tex, 75, 139, 0, 0, g_gate_count * 21.3333f, 43);
	//Number_Draw(FLAG_NUM/10,234,128);													//全てのゲート数の表示　10の位
	//Number_Draw(FLAG_NUM % 10, 262, 128);												//全てのゲート数の表示　1の位
	//Number_Draw(g_gate_count/10, 152, 128);												//通過ゲート数の表示　10の位
	//Number_Draw(g_gate_count%10, 180, 128);												//通過ゲート数の表示　1の位

	int num;																			//ループで算出される各桁の数字を保持する変数
	int time = g_time * DECIMAL_POINT;													//桁を減らしながらタイムを保持する変数　最初にタイムを自然数で保持
	for (int i = 0; i < TIME_DIGIT; i++)												//表示桁数分だけループ　
	{
		num = time % 10;																//1の位の数字を算出
		Number_Draw(num,234-i*NUM_SPACE,55);													//算出した数字を表示
		time = time / 10;																//次の桁の数字を算出するために、桁を減らす
		if (i == 2) {
			Sprite_Draw(g_period_tex, 244 - i * NUM_SPACE, 66);
		}
	}
	/*

	(67.0f, -64.0f, 441.0f);

	if (GoolGetCrear()) {
		Sprite_Draw(g_goal_tex, 500, 100);
	}
	*/
}

double Get_Time(void) 
{
	return g_time;
}



