#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	テクスチャ処理[texture.h]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#include <d3d9.h>


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	プロトタイプ宣言
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_SetLoadFile(const char* pFilename, int width, int height);//読み込むテクスチャの予約　(ファイル名, テクスチャ幅,　高さ)戻り値 予約番号(id) -1が返ったら空きがないよ
int Texture_Load(void);                       //ファイルの読み込み 戻り値　読み込めなかった数
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//テクスチャインタフェースを取得する関数　(予約番号) 不正番号でNULLが返る
void Texture_Destroy(int ids[], int count);   //テクスチャ解放処理　部分解放　(解放したいidが入った配列の先頭アドレス, このアドレスから何個分？)    int id; (&id,1)でおっけ　
void Texture_Destroy(void);                   //テクスチャ解放処理　全部解放
int Texture_GetWidth(int id);                 //テクスチャの幅を取得
int Texture_GetHeight(int id);                //テクスチャの高さを取得

#endif