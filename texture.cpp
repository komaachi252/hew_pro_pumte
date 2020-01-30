/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	テクスチャ処理[texture.cpp]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#define _CRT_SECURE_NO_WARNINGS
#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	マクロ定義
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define FILENAME_MAX    (128)
#define TEXTUREDATA_MAX  (128)



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	構造体宣言
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct Texture_tag
{
	char fliename[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureData;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	グローバル変数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static TextureData g_TextureData[TEXTUREDATA_MAX] = {};



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	読み込むテクスチャの予約処理
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_SetLoadFile(const char* pFilename, int width, int height)//　幅　高さを間違えると危険
{
	//同じファイル名を探す
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (strcmp(g_TextureData[i].fliename, pFilename) == 0) {//同じファイルを見つけた
			return i;//予約番号を返す
		}
	}
	//新規登録
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		//使用されていない場所を探す
		if (g_TextureData[i].fliename[0] != 0) {//配列最初が\0
			continue;//前のfor文に戻る
		}
		//登録
		strcpy(g_TextureData[i].fliename, pFilename);
		g_TextureData[i].width  = width;
		g_TextureData[i].height = height;
		return i;
	}
	return -1;//空きがないよ
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	テクスチャ読み込み処理
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9  g_pDevice = GetDevice();
	int error_count = 0;
	
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {

		if (g_TextureData[i].fliename[0] == 0) {
			continue;
		}
		if (g_TextureData[i].pTexture != NULL) {
			continue;
		}
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(g_pDevice, g_TextureData[i].fliename, &g_TextureData[i].pTexture);

	}
	return error_count;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id)
{
	return g_TextureData[id].pTexture;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	指定テクスチャ破壊関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Texture_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (g_TextureData[ids[i]].pTexture != NULL) {
			g_TextureData[ids[i]].pTexture->Release();
			g_TextureData[ids[i]].pTexture = NULL;
			g_TextureData[ids[i]].fliename[0] = 0;
			g_TextureData[ids[i]].width  = 0;
			g_TextureData[ids[i]].height = 0;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	全テクスチャ破壊関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Texture_Destroy(void)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureData[i].pTexture != NULL) {
			g_TextureData[i].pTexture->Release();
			g_TextureData[i].pTexture = NULL;
			g_TextureData[i].fliename[0] = 0;
			g_TextureData[i].width  = 0;
			g_TextureData[i].height = 0;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	テクスチャ幅取得関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_GetWidth(int id)
{
	return g_TextureData[id].width;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	テクスチャ高さ取得関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_GetHeight(int id)
{
	return g_TextureData[id].height;
}



