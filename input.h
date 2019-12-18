<<<<<<< HEAD
/*==============================================================================

   キーボード入力処理 [input.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/09/05
--------------------------------------------------------------------------------
   キーボードモジュールの初期化内でCOMインターフェースや
   DirectInputデバイスの初期化をしているので、マウス入力やパッド入力を
   追加する場合は、切り離さないといけない
   ※パッド対応はxinputの利用を推奨
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.hをインクルードする前にこれを入れないと警告が出るので注意
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// キーボード入力モジュールの初期化
//
// 戻り値：初期化出来なかった場合false
//
// 引数：hinstance ... インスタンスハンドル（WinMainの引数などで取得）
//       hWnd      ... ウィンドウハンドル
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);

// キーボードモジュールの終了処理
void Keyboard_Finalize(void);

// キーボードモジュールの更新
// ※キーボード全体のキー状態の取得
//
void Keyboard_Update(void);

// キーボードのキー状態の取得
//
// Keyboard_Update()で取得したキーの状態を確認する関数群
//
// 戻り値：指定のキーが
//     Press   ... 押されている
//     Trigger ... 押した瞬間
//     Release ... 離した瞬間
// であった場合trueを返す
//
// 引数：nKey ... キー指定（DIK_～というキー列挙）
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);//押した瞬間
bool Keyboard_IsRelease(int nKey);//離した瞬間
=======
#ifndef INPUT_H_
#define INPUT_H_

#include<Windows.h>

//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by Joystick.rc
//

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        104
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1025
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif


HRESULT InitDirectInput(HWND hWnd);
HRESULT UpdateInput(HWND hWnd);
void UninitDirectInput();


/*
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
plus・・・マイナスをプラスにする
*/
float GetAxisX(int JoyConNumber, bool plus);

/*
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
plus・・・マイナスをプラスにする
*/
float GetAxisY(int JoyConNumber, bool plus);

/*
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
plus・・・マイナスをプラスにする
*/
float GetAxisZ(int JoyConNumber, bool plus);

/*
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
*/
float GetlX(int JoyConNumber);

/*
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
*/
float GetlY(int JoyConNumber);

/*
JoyConのボタン設定
JoyConNumber・・・0から始まるJoyConの番号
　　　　　　　 　 接続した順番で決まる
		  　　　　　　
BotonNumber ・・・
よこもちR[L]
0:右[上]
1:左[右]
2:上[左]
3:下[下]
4:R[L]
5:L[R]
6:(左下)L[(右下)L]
7:(左下)ZL[(右下)ZL]
8:マイナス
9:[プラス]
10[スティック押し込み]
11:スティック押し込み
12:[丸]
13:四角
*/
float GetBotton(int JoyConNumber, int BotonNumber);
>>>>>>> 3b73f20ab355e091174d7e2d0657ef0d01b278b8

#endif