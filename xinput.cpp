//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	Xinput処理[xinput.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 12/22(日)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include "xinput.h"
#include <windows.h>
#include <map>
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define XINPUT_GAMEPAD_L2 (0x0001)
#define XINPUT_GAMEPAD_R2 (0x0008)
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
enum INPUT_STATE {
	NONE,
	PUSH,
	ENTER,
	EXIT
};

typedef struct VIBRATION_tag{
	XINPUT_VIBRATION vib;
	int frame;
	bool is_used;
}Vibration;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static std::map<int, WORD> map_key;
static std::map<WORD, INPUT_STATE> key_state;

static XINPUT_STATE g_state;
static  DWORD XINPUT_MAX_CONTROLLERS = 4;
static Vibration g_vibration;

static bool L2_key;
static bool L2_old;
static bool R2_key;
static bool R2_old;

static WORD key_info[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_L2,
	XINPUT_GAMEPAD_R2
};
static int KEY_MAX = sizeof(key_info) / sizeof(key_info[0]);

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_Init(HWND hWnd)
{
	g_vibration.is_used = false;
	g_vibration.vib.wLeftMotorSpeed = 0;
	g_vibration.vib.wRightMotorSpeed = 0;
	ZeroMemory(&g_vibration.vib, sizeof(XINPUT_VIBRATION));
	
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &g_state);

	map_key[XINPUT_GAMEPAD_A] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_B] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_X] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_Y] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_START] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_LEFT_THUMB] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_RIGHT_THUMB] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_LEFT_SHOULDER] = g_state.Gamepad.wButtons;
	map_key[XINPUT_GAMEPAD_RIGHT_SHOULDER] = g_state.Gamepad.wButtons;

	key_state[XINPUT_GAMEPAD_A] = NONE;
	key_state[XINPUT_GAMEPAD_B] = NONE;
	key_state[XINPUT_GAMEPAD_X] = NONE;
	key_state[XINPUT_GAMEPAD_Y] = NONE;
	key_state[XINPUT_GAMEPAD_START] = NONE;
	key_state[XINPUT_GAMEPAD_LEFT_THUMB] = NONE;
	key_state[XINPUT_GAMEPAD_RIGHT_THUMB] = NONE;
	key_state[XINPUT_GAMEPAD_LEFT_SHOULDER] = NONE;
	key_state[XINPUT_GAMEPAD_RIGHT_SHOULDER] = NONE;

	L2_key = false;
	L2_old = false;
	R2_key = false;
	R2_old = false;

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		return true;
	}
	else
	{
		// Controller is not connected
		//MessageBox(hWnd, "Xinputオブジェクトがないです", "警告！", MB_ICONWARNING);
		return false;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Xinput_Uninit(void)
{


}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Xinput_Update(void)
{
	XInputGetState(0, &g_state);
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}
	if ((g_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbRX = 0;
		g_state.Gamepad.sThumbRY = 0;
	}
	
	for (int i = 0; i < KEY_MAX; i++) {
		if (g_state.Gamepad.wButtons & key_info[i]) {
			if (key_state[key_info[i]] == NONE || key_state[key_info[i]] == EXIT) {
				key_state[key_info[i]] = ENTER;
			}
			else {
				key_state[key_info[i]] = PUSH;
			}
		}
		else {
			if (key_state[key_info[i]] == PUSH || key_state[key_info[i]] == PUSH) {
				key_state[key_info[i]] = EXIT;
			}
			else {
				key_state[key_info[i]] = NONE;
			}
		}
	}
	if (!g_vibration.is_used) { return; }
	g_vibration.frame--;
	if (g_vibration.frame <= 0) {
		g_vibration.is_used = false;
		g_vibration.vib.wLeftMotorSpeed = 0;
		g_vibration.vib.wRightMotorSpeed = 0;
		XInputSetState(0, &g_vibration.vib);
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_IsPress(int key)
{
	return (map_key[key] == PUSH);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_IsTrigger(int key)
{
	return (key_state[key] == ENTER);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_IsTriggerL2(void)
{
	bool flag = false;
	R2_key = g_state.Gamepad.bLeftTrigger;
	if (L2_key && !L2_old){
		flag = true;
	}
	L2_old = L2_key;
	return flag;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_IsTriggerR2(void) 
{
	bool flag = false;
	R2_key = g_state.Gamepad.bRightTrigger;
	if (R2_key && !R2_old) {
		flag = true;
	}
	R2_old = R2_key;
	return flag;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Xinput_IsExit(int key)
{
	return (map_key[key] == EXIT);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
float Xinput_IsAxisLX(void)
{
	if (g_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// スティックの左が押された
		return (float)g_state.Gamepad.sThumbLX;
	}

	if (g_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// スティックの右が押された
		return (float)g_state.Gamepad.sThumbLX;
	}

	return 0.0f;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
float Xinput_IsAxisRX(void)
{
	if (g_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// スティックの左が押された
		return (float)g_state.Gamepad.sThumbRX;
	}

	if (g_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// スティックの右が押された
		return (float)g_state.Gamepad.sThumbRX;
	}

	return 0.0f;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
float Xinput_IsAxisLY(void)
{
	if (g_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// スティックの上が押された
		return (float)g_state.Gamepad.sThumbLY;
	}

	if (g_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// スティックの下が押された
		return (float)g_state.Gamepad.sThumbLY;
	}

	return 0.0f;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
float Xinput_IsAxisRY(void)
{
	if (g_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// スティックの上が押された
		return (float)g_state.Gamepad.sThumbRY;
	}

	if (g_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// スティックの下が押された
		return (float)g_state.Gamepad.sThumbRY;
	}

	return 0.0f;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	入力処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Xinput_Vibration(int frame, WORD left_speed, WORD right_speed)
{
	if (g_vibration.is_used) { return; }
	g_vibration.vib.wLeftMotorSpeed = left_speed;
	g_vibration.vib.wRightMotorSpeed = right_speed;
	g_vibration.frame = frame;
	g_vibration.is_used = true;
	XInputSetState(0, &g_vibration.vib);
}