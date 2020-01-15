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
//#include "Flags.h"
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

static int g_UI_tex = 0;																//UIのテクスチャを保持する変数
static int g_period_tex = 0;														    //ピリオドのテクスチャを保持する変数
static int g_goal_tex = 0;														    //ピリオドのテクスチャを保持する変数
static double g_time = 0.0f;															//タイムを保持する変数
static int g_gate_count = 0;															//通過したゲート数を保持する変数

void UI_Init(void)
{
	Number_Init();																		//ナンバーのイニット
	g_UI_tex = Texture_SetLoadFile("Asset/Texture/UI.png", SCREEN_WIDTH, TEX_HIGHT);	//UIテクスチャ読み込み
	g_period_tex = Texture_SetLoadFile("Asset/Texture/period.png", 30, 28);	//UIテクスチャ読み込み
	g_goal_tex = Texture_SetLoadFile("Asset/Texture/goal_logo.png", 294, 294);	//UIテクスチャ読み込み
	Texture_Load();  //テクスチャセット
	g_time = 0.0f;																		//タイムの初期化
	g_gate_count = 0;																	//通過ゲート数の初期化
}
	
void UI_Uninit(void)
{
	Texture_Destroy();																	//テクスチャ解放
}
void UI_Update(void)
{
	if (!Is_Start_Count_End()) {
		return;
	}
	/*
	if (GoolGetCrear()) {
		return;
	}
	*/
	g_time += COUNTUP_TIME;															   //タイムのカウントアップ


}
void UI_Draw()
{
	//g_gate_count = FlagsGetCnt();
	Camera_2D();
	Sprite_Draw(g_UI_tex, 0, 0);														//UIの文字部分の表示
	//Number_Draw(FLAG_NUM/10,234,128);													//全てのゲート数の表示　10の位
	//Number_Draw(FLAG_NUM % 10, 262, 128);												//全てのゲート数の表示　1の位
	//Number_Draw(g_gate_count/10, 152, 128);												//通過ゲート数の表示　10の位
	//Number_Draw(g_gate_count%10, 180, 128);												//通過ゲート数の表示　1の位

	int num;																			//ループで算出される各桁の数字を保持する変数
	int time = g_time * DECIMAL_POINT;													//桁を減らしながらタイムを保持する変数　最初にタイムを自然数で保持
	for (int i = 0; i < TIME_DIGIT; i++)												//表示桁数分だけループ　
	{
		num = time % 10;																//1の位の数字を算出
		Number_Draw(num,264-i*NUM_SPACE,55);													//算出した数字を表示
		time = time / 10;																//次の桁の数字を算出するために、桁を減らす
		if (i == 2) {
			Sprite_Draw(g_period_tex, 274 - i * NUM_SPACE, 66);
		}
	}
	/*
	if (GoolGetCrear()) {
		Sprite_Draw(g_goal_tex, 500, 100);
	}
	*/
}



