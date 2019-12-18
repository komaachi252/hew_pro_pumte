/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　　JoyCon.cpp
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#include"Input2.h"
#include<d3d9.h>
#include"d3dx9.h"
#include<dinput.h>
#include<dinputd.h>
#include<stdio.h>


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
<<<<<<< HEAD
　　　　定数定義
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#define JOYCON_MAX     (2)

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }

#define IDI_MAIN                        102
#define IDD_JOYST_IMM                   103
#define IDR_ACCELERATOR1                103
#define IDC_CLOSE                       1001
#define IDC_X_AXIS                      1010
#define IDC_Y_AXIS                      1011
#define IDC_Z_AXIS                      1012
#define IDC_X_AXIS_TEXT                 1013
#define IDC_Y_AXIS_TEXT                 1014
#define IDC_Z_AXIS_TEXT                 1015
#define IDC_X_ROT_TEXT                  1016
#define IDC_Y_ROT_TEXT                  1017
#define IDC_Z_ROT_TEXT                  1018
#define IDC_SLIDER0_TEXT                1019
#define IDC_X_ROT                       1020
#define IDC_Y_ROT                       1021
#define IDC_Z_ROT                       1022
#define IDC_SLIDER1_TEXT                1023
#define IDC_POV0_TEXT                   1024
#define IDC_POV1_TEXT                   1025
#define IDC_POV2_TEXT                   1026
#define IDC_POV3_TEXT                   1027
#define IDC_SLIDER0                     1030
#define IDC_SLIDER1                     1031
#define IDC_POV                         1040
#define IDC_POV0                        1040
#define IDC_BUTTONS                     1041
#define IDC_POV1                        1042
#define IDC_POV2                        1043
#define IDC_POV3                        1044


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=======
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
　　　　　構造体宣言
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
struct DI_ENUM_CONTEXT
{
<<<<<<< HEAD
	DIJOYCONFIG* p_preferredjoycfg;
	bool bpreferredjoycfgvalid;
=======
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
};


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　グローバル関数
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
<<<<<<< HEAD
static LPDIRECTINPUT8          g_glbdI = nullptr;
static LPDIRECTINPUTDEVICE8    g_glbjoystick[JOYCON_MAX] = {};
static DIDEVCAPS			   g_glbdidevcaps;
static DIJOYSTATE2 g_nowinput[JOYCON_MAX];
static DIJOYSTATE2 g_lastinput[JOYCON_MAX];
=======
static LPDIRECTINPUT8          g_glbDI = nullptr;
static LPDIRECTINPUTDEVICE8    g_glbJoystick[JOYCON_MAX] = {};
static DIDEVCAPS			   g_glbdiDevCaps;
static DIJOYSTATE2 g_nowInput[JOYCON_MAX];
static DIJOYSTATE2 g_lastInput[JOYCON_MAX];
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
static DI_ENUM_CONTEXT g_enumcontext;
static DIJOYCONFIG g_preferredjoycfg = { 0 };
static int g_joyconcount = 0;
static HWND g_hwnd;
<<<<<<< HEAD


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　CallBack関数宣言
=======
static float y = 0.0f;
static float z = 0.0f;


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　コールバック関数宣言
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
<<<<<<< HEAD
　　　　Get関数宣言
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
float GetAxisX(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowinput[JoyConNumber].lRz < 0)
		{
			return (float)g_nowinput[JoyConNumber].lRz*-1;
		}
	}
	return (float)g_nowinput[JoyConNumber].lRz;
}


float GetAxisY(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowinput[JoyConNumber].rglSlider[1] < 0)
		{
			return (float)g_nowinput[JoyConNumber].rglSlider[1] * -1.0f;
		}
	}
	return (float)g_nowinput[JoyConNumber].rglSlider[1];
}


float GetAxisZ(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowinput[JoyConNumber].rglSlider[0] < 0)
		{
			return (float)g_nowinput[JoyConNumber].rglSlider[0] * -1.0f;
		}
	}
	return (float)g_nowinput[JoyConNumber].rglSlider[0];
}


float GetlX(int JoyConNumber)
{
	return (float)g_nowinput[JoyConNumber].lX;
}


float GetlY(int JoyConNumber)
{
	return (float)g_nowinput[JoyConNumber].lY;
}


float GetBotton(int JoyConNumber, int BotonNumber)
{
	return (float)g_nowinput[JoyConNumber].rgbButtons[BotonNumber];
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=======
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
　　　　初期化
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
HRESULT InitDirectInput(HWND hWnd) {
	g_joyconcount = 0;
	g_hwnd = hWnd;
	HRESULT hr;

	if (FAILED(hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
<<<<<<< HEAD
		(VOID**)&g_glbdI,
=======
		(VOID**)&g_glbDI,
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		nullptr)))
	{
		return hr;
	}

<<<<<<< HEAD
	if (FAILED(hr = g_glbdI->EnumDevices(
=======
	if (FAILED(hr = g_glbDI->EnumDevices(
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		&g_enumcontext, DIEDFL_ATTACHEDONLY)))
	{
		return hr;
	}
	
	return S_OK;

}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　　終了処理
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
void UninitDirectInput()
{
	for (int i = 0; i < JOYCON_MAX; i++)
	{
		// Unacquire the device one last time just in case 
		// the app tried to exit while the device is still acquired.
<<<<<<< HEAD
		if (g_glbjoystick[i])
			g_glbjoystick[i]->Unacquire();

		// Release any DirectInput objects.
		SAFE_RELEASE(g_glbjoystick[i]);
		SAFE_RELEASE(g_glbdI);
=======
		if (g_glbJoystick[i])
			g_glbJoystick[i]->Unacquire();

		// Release any DirectInput objects.
		SAFE_RELEASE(g_glbJoystick[i]);
		SAFE_RELEASE(g_glbDI);
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
	}

}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　　JoyConに対する設定
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
	VOID* pContext)
{
<<<<<<< HEAD
	g_enumcontext.p_preferredjoycfg = &g_preferredjoycfg;
	g_enumcontext.bpreferredjoycfgvalid = false;
=======
	g_enumcontext.pPreferredJoyCfg = &g_preferredjoycfg;
	g_enumcontext.bPreferredJoyCfgValid = false;
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c

	auto pEnumContext = reinterpret_cast<DI_ENUM_CONTEXT*>(pContext);
	HRESULT hr;

	if (g_joyconcount >= JOYCON_MAX)
	{
		return DIENUM_STOP;
	}

	// Skip anything other than the perferred joystick device as defined by the control panel.  
	// Instead you could store all the enumerated joysticks and let the user pick.
<<<<<<< HEAD
	if (pEnumContext->bpreferredjoycfgvalid &&
		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->p_preferredjoycfg->guidInstance))
=======
	if (pEnumContext->bPreferredJoyCfgValid &&
		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
	{
		return DIENUM_CONTINUE;
	}
	// Obtain an interface to the enumerated joystick.
<<<<<<< HEAD
	hr = g_glbdI->CreateDevice(pdidInstance->guidInstance, &g_glbjoystick[g_joyconcount], nullptr);
=======
	hr = g_glbDI->CreateDevice(pdidInstance->guidInstance, &g_glbJoystick[g_joyconcount], nullptr);
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}
	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.

	IDirectInputJoyConfig8* pJoyConfig = nullptr;
<<<<<<< HEAD
	if (FAILED(hr = g_glbdI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
=======
	if (FAILED(hr = g_glbDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		return hr;

	g_preferredjoycfg.dwSize = sizeof(g_preferredjoycfg);
	if (SUCCEEDED(pJoyConfig->GetConfig(0, &g_preferredjoycfg, DIJC_GUIDINSTANCE))) // This function is expected to fail if no joystick is attached
	{
<<<<<<< HEAD
		g_enumcontext.bpreferredjoycfgvalid = true;
=======
		g_enumcontext.bPreferredJoyCfgValid = true;
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
	}

	SAFE_RELEASE(pJoyConfig);

	// Set the data format to "simple joystick" - a predefined data format 
	//
	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().

<<<<<<< HEAD
	if (FAILED(hr = g_glbjoystick[g_joyconcount]->SetDataFormat(&c_dfDIJoystick2)))
=======
	if (FAILED(hr = g_glbJoystick[g_joyconcount]->SetDataFormat(&c_dfDIJoystick2)))
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
	{
		return DIENUM_CONTINUE;
	}

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.

<<<<<<< HEAD
	if (FAILED(hr = g_glbjoystick[g_joyconcount]->SetCooperativeLevel(g_hwnd, DISCL_EXCLUSIVE |
=======
	if (FAILED(hr = g_glbJoystick[g_joyconcount]->SetCooperativeLevel(g_hwnd, DISCL_EXCLUSIVE |
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		DISCL_FOREGROUND)))
	{
		return DIENUM_CONTINUE;
	}

	
<<<<<<< HEAD
	g_glbdidevcaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(hr = g_glbjoystick[g_joyconcount]->GetCapabilities(&g_glbdidevcaps)))
=======
	g_glbdiDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(hr = g_glbJoystick[g_joyconcount]->GetCapabilities(&g_glbdiDevCaps)))
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
	{
		return DIENUM_CONTINUE;
	}
	
	
<<<<<<< HEAD
	if (!g_glbjoystick[g_joyconcount]) {
=======
	if (!g_glbJoystick[g_joyconcount]) {
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		MessageBox(nullptr, TEXT("Joystick not found."),
			TEXT("Warning!"),
			MB_ICONERROR | MB_OK);
		return S_OK;
	}


	// Enumerate the joystick objects. The callback function enabled user
	// interface elements for objects that are found, and sets the min/max
	// values property for discovered axes.

<<<<<<< HEAD
	if (FAILED(hr = g_glbjoystick[g_joyconcount]->EnumObjects(EnumObjectsCallback,
=======
	if (FAILED(hr = g_glbJoystick[g_joyconcount]->EnumObjects(EnumObjectsCallback,
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		(VOID*)g_hwnd, DIDFT_ALL)))
	{
		return DIENUM_CONTINUE;
	}

	g_joyconcount++;

	return DIENUM_CONTINUE;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　　JoyConの取得する数値などの設定
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
//-----------------------------------------------------------------------------
// Name: EnumObjectsCallback()
// Desc: Callback function for enumerating objects (axes, buttons, POVs) on a 
//       joystick. This function enables user interface elements for objects
//       that are found to exist, and scales axes min/max values.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi,
	VOID* pContext)
{
	HWND hDlg = (HWND)pContext;

	static int nSliderCount = 0;  // Number of returned slider controls
	static int nPOVCount = 0;     // Number of returned POV controls

	// For axes that are returned, set the DIPROP_RANGE property for the
	// enumerated axis in order to scale min/max values.
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		// Set the range for the axis
<<<<<<< HEAD
		if (FAILED(g_glbjoystick[g_joyconcount]->SetProperty(DIPROP_RANGE, &diprg.diph)))
=======
		if (FAILED(g_glbJoystick[g_joyconcount]->SetProperty(DIPROP_RANGE, &diprg.diph)))
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		{
			return DIENUM_STOP;
		}
	}

	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_X_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_X_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_YAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Y_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Y_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_ZAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Z_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Z_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RxAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_X_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_X_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RyAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Y_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Y_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RzAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Z_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Z_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_Slider)
	{
		switch (nSliderCount++)
		{
		case 0:
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER0), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER0_TEXT), TRUE);
			break;

		case 1:
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER1), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER1_TEXT), TRUE);
			break;
		}
	}
	if (pdidoi->guidType == GUID_POV)
	{
		switch (nPOVCount++)
		{
		case 0:
			EnableWindow(GetDlgItem(hDlg, IDC_POV0), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV0_TEXT), TRUE);
			break;

		case 1:
			EnableWindow(GetDlgItem(hDlg, IDC_POV1), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV1_TEXT), TRUE);
			break;

		case 2:
			EnableWindow(GetDlgItem(hDlg, IDC_POV2), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV2_TEXT), TRUE);
			break;

		case 3:
			EnableWindow(GetDlgItem(hDlg, IDC_POV3), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV3_TEXT), TRUE);
			break;
		}
	}

	return DIENUM_CONTINUE;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
　　　　　更新処理
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
HRESULT UpdateInput(HWND hWnd)
{
	for (int i = 0; i < JOYCON_MAX; i++)
	{
		HRESULT     hr;
		DIJOYSTATE2 js;           // Direct Input joystick state 

<<<<<<< HEAD
		g_lastinput[i] = g_nowinput[i];

		if (NULL == g_glbjoystick[i]) {
=======
		g_lastInput[i] = g_nowInput[i];

		if (NULL == g_glbJoystick[i]) {
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
			return S_OK;
		}

		// Poll the device to read the current state
<<<<<<< HEAD
		hr = g_glbjoystick[i]->Poll();
		if (FAILED(hr))
		{
			hr = g_glbjoystick[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = g_glbjoystick[i]->Acquire();

		}
		hr = g_glbjoystick[i]->GetDeviceState(sizeof(DIJOYSTATE2), &js);
=======
		hr = g_glbJoystick[i]->Poll();
		if (FAILED(hr))
		{
			hr = g_glbJoystick[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = g_glbJoystick[i]->Acquire();

		}
		hr = g_glbJoystick[i]->GetDeviceState(sizeof(DIJOYSTATE2), &js);
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
		if (FAILED(hr)) {
			return hr;
		}

<<<<<<< HEAD
		g_nowinput[i] = js;
=======
		g_nowInput[i] = js;
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c

	}
	return S_OK;

<<<<<<< HEAD
=======
}


float GetAxisX(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[JoyConNumber].lRz < 0)
		{
			return (float)g_nowInput[JoyConNumber].lRz*-1;
		}
	}
	return (float)g_nowInput[JoyConNumber].lRz;
}


float GetAxisY(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[JoyConNumber].rglSlider[1] < 0)
		{
			return (float)g_nowInput[JoyConNumber].rglSlider[1] * -1.0f;
		}
	}
	return (float)g_nowInput[JoyConNumber].rglSlider[1];
}


float GetAxisZ(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[JoyConNumber].rglSlider[0] < 0)
		{
			return (float)g_nowInput[JoyConNumber].rglSlider[0] * -1.0f;
		}
	}
	return (float)g_nowInput[JoyConNumber].rglSlider[0];
}


float GetLastAxisZ(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_lastInput[JoyConNumber].rglSlider[0] < 0)
		{
			return (float)g_lastInput[JoyConNumber].rglSlider[0] * -1.0f;
		}
	}
	return (float)g_lastInput[JoyConNumber].rglSlider[0];
}


float GetlX(int JoyConNumber)
{
	return (float)g_nowInput[JoyConNumber].lX;
}


float GetlY(int JoyConNumber)
{
	return (float)g_nowInput[JoyConNumber].lY;
}


float GetBotton(int JoyConNumber, int BotonNumber)
{
	return (float)g_nowInput[JoyConNumber].rgbButtons[BotonNumber];
}

float GetRotY(int joyConNumber)
{
	D3DXMATRIX mtxroty;
	D3DXVECTOR3 vecy(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 vecjoycony(0.0f, 0.0f, 1.0f);
	float axisy = GetAxisY(joyConNumber, false);
	y += axisy / 10000;
	D3DXMatrixRotationY(&mtxroty, y);
	D3DXVec3TransformNormal(&vecjoycony, &vecjoycony, &mtxroty);
	float y_z = vecy.z * vecjoycony.z;
	float naisekiy = y_z / (vecjoycony.x * vecjoycony.x + vecjoycony.y * vecjoycony.y + vecjoycony.z * vecjoycony.z);
	float kakudoy = acosf(naisekiy);
	kakudoy = D3DXToDegree(kakudoy);
	if (GetAxisY(joyConNumber, true) < 50.0f)
	{
		if (kakudoy > 0.0f)
		{
			kakudoy = 0.0f;
			y = 0.0f;
		}
	}
	return kakudoy;
}

float GetRotZ(int joyConNumber)
{
	D3DXMATRIX mtxrotz;
	D3DXVECTOR3 vecz(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vecjoyconz(0.0f, 1.0f, 0.0f);
	z += GetAxisZ(joyConNumber, false) / 10000;
	D3DXMatrixRotationZ(&mtxrotz, z);
	D3DXVec3TransformNormal(&vecjoyconz, &vecjoyconz, &mtxrotz);
	float z_y = vecz.y * vecjoyconz.y;
	float naisekiz = z_y / (vecjoyconz.x * vecjoyconz.x + vecjoyconz.y * vecjoyconz.y + vecjoyconz.z * vecjoyconz.z);
	float kakudoz = acosf(naisekiz);
	kakudoz = D3DXToDegree(kakudoz);
	if (GetAxisZ(joyConNumber, true) < 50.0f)
	{
		if (kakudoz > 0.0f)
		{
			kakudoz = 0.0f;
			z = 0.0f;
		}
	}
	return kakudoz;
}

float GetAxis(int JoyConNumber, bool plus)
{
	float goukei;
	goukei = GetAxisX(JoyConNumber, plus) + GetAxisY(JoyConNumber, plus) + GetAxisZ(JoyConNumber, plus);
	return goukei;
>>>>>>> 81cc111614e193111ef69219f9201b653f7f287c
}