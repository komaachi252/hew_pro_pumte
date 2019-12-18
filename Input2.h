#ifndef INPUT2_H_
#define INPUT2_H_

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


HRESULT InitDirectInput(HWND hWnd);
HRESULT UpdateInput(HWND hWnd);
void UninitDirectInput();

#endif