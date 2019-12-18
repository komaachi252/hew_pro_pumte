//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_GAME = 0,			// BGM　ゲーム画面
	SOUND_LABEL_BGM_TITLE,				// BGM　タイトル画面
	SOUND_LABEL_BGM_MENU,				// BGM　メニュー画面
	SOUND_LABEL_BGM_RANKIN,				// BGM　ランキング画面
	SOUND_LABEL_SE_CANCEL,				// SE   キャンセル音
	SOUND_LABEL_SE_HIT1,				// SE　 衝突音　その1
	SOUND_LABEL_SE_HIT2,				// SE 　衝突音　その2
	SOUND_LABEL_SE_MENU,				// SE 　メニュー画面での決定音
	SOUND_LABEL_SE_RANKIN,				// SE 　ランクイン音
	SOUND_LABEL_SE_RANKING,				// SE 　ランキング音
	SOUND_LABEL_SE_SPLASH,				// SE   水しぶき音
	SOUND_LABEL_SE_SWITCH,				// SE	メニュー画面でのカーソル切り替え音
	SOUND_LABEL_SE_TITLE,				// SE　 タイトル画面での決定音
	SOUND_LABEL_SE_GATE,				// SE　 ゲート通過音
	SOUND_LABEL_MAX,					// BGM&SEの数
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
