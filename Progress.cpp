//進捗バーの表示
//制作者　安保圭一郎
//
//デフォルトでは、仮の画像を元に作られており、画面の中央の上側に表示している
//赤い三角形が、進捗を示すアイコン

#include <d3d9.h>
#include<d3dx9.h>
#include<d3d.h>
#include "sprite.h"
#include "texture.h"
#include "common.h"

#define PROGRESS_FRAME_WIDTH (520)											//進捗バーの枠の横サイズ			　
#define PROGRESS_FRAME_HIGHT (40)											//進捗バーの枠の縦サイズ												
#define FRAMESPASE_SIZE (4)													//進捗バーの枠の太さ
#define PROGRESS_BAR_WIDTH (PROGRESS_FRAME_WIDTH - FRAMESPASE_SIZE * 2)     //進捗バーのバー自体の横サイズ
#define PROGRESSFRAME_POSITION_Y (24)										//進捗バーを表示するY座標
#define PROGRESS_ICON_SIZE (32)												//進捗バーのアイコンサイズ

enum PROGRESS_TEXTYPE
{
	PROGRESS_FRAME,
	PROGRESS_ICON,
	PROGRESS_TYPEMAX
};

static int g_progressTex[PROGRESS_TYPEMAX] = {};							//進捗バー本体とアイコンのテクスチャを保存する変数
static float g_progress = 0;												//進捗度を保持する変数　0.0f～1.0fまで

void Progress_Init()
{
	g_progressTex[PROGRESS_FRAME] = Texture_SetLoadFile("Asset/Texture/progress.png", PROGRESS_FRAME_WIDTH, PROGRESS_FRAME_HIGHT);	//テクスチャのロード　パス変更必須
	g_progressTex[PROGRESS_ICON]=Texture_SetLoadFile("Asset/Texture/icon.png",PROGRESS_ICON_SIZE , PROGRESS_ICON_SIZE);				//パス変更必須
	g_progress = 0.0f;																												//進捗度の初期化
}
void Progress_Uninit(void)
{
	Texture_Destroy(&g_progressTex[PROGRESS_FRAME], 1);																												//テクスチャ解放
	Texture_Destroy(&g_progressTex[PROGRESS_ICON], 1);																												//テクスチャ解放
}
void Progress_Update(void)
{
	//g_progress = GetProgress();																									//本命の進捗取得
	g_progress += 0.001f;																											//テスト用のインクリメント
	if (g_progress >= 1.0f)																											//アイコンがバーの外に出ないようにする
	{
		g_progress = 1.0f;
	}
}
void Progress_Draw(void)
{
	Texture_Load();																													//テクスチャロード
	Sprite_Draw(g_progressTex[PROGRESS_FRAME], (SCREEN_WIDTH - PROGRESS_FRAME_WIDTH) / 2, PROGRESSFRAME_POSITION_Y);
	Sprite_Draw(g_progressTex[PROGRESS_ICON],((SCREEN_WIDTH - PROGRESS_FRAME_WIDTH) / 2 + FRAMESPASE_SIZE) + PROGRESS_BAR_WIDTH * g_progress,PROGRESSFRAME_POSITION_Y+PROGRESS_FRAME_HIGHT/2);
}

