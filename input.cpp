<<<<<<< HEAD
//=============================================================================
//
// ���͏��� [input.cpp]
//
//=============================================================================
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static bool initialize(HINSTANCE hInstance);
static void finalize(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N

//=============================================================================
// ���͏����̏�����
//=============================================================================
bool initialize(HINSTANCE hInstance)
{
	if(g_pInput == NULL) {

		// DirectInput�I�u�W�F�N�g�̍쐬
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {

			return false;
		}
	}

	return true;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void finalize(void)
{
	if(g_pInput != NULL) {

		// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}


//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if( !initialize(hInstance) ) {

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �f�o�C�X�̍쐬
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return true;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void Keyboard_Finalize(void)
{
	if(g_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	finalize();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void Keyboard_Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80

		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];


			// �L�[�v���X����ۑ�
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool Keyboard_IsPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool Keyboard_IsTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool Keyboard_IsRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
=======
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�@JoyCon.cpp
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#include"input.h"
#include<d3d9.h>
#include<dinput.h>
#include<dinputd.h>
#include<stdio.h>
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
�@�@�@�@�@�\���̐錾
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
};


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�O���[�o���֐�
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
static LPDIRECTINPUT8          g_glbDI = nullptr;
static LPDIRECTINPUTDEVICE8    g_glbJoystick[JOYCON_MAX] = {};
static DIDEVCAPS			   g_glbdiDevCaps;
static DIJOYSTATE2 g_nowInput[JOYCON_MAX];
static DIJOYSTATE2 g_lastInput[JOYCON_MAX];
static DI_ENUM_CONTEXT g_enumcontext;
static DIJOYCONFIG g_preferredjoycfg = { 0 };
static int g_joyconcount = 0;
static HWND g_hwnd;


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�R�[���o�b�N�֐��錾
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@������
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
HRESULT InitDirectInput(HWND hWnd) {
	g_joyconcount = 0;
	g_hwnd = hWnd;
	HRESULT hr;

	if (FAILED(hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&g_glbDI,
		nullptr)))
	{
		return hr;
	}

	if (FAILED(hr = g_glbDI->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		&g_enumcontext, DIEDFL_ATTACHEDONLY)))
	{
		return hr;
	}
	
	return S_OK;

}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�@�I������
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
void UninitDirectInput()
{
	for (int i = 0; i < JOYCON_MAX; i++)
	{
		// Unacquire the device one last time just in case 
		// the app tried to exit while the device is still acquired.
		if (g_glbJoystick[i])
			g_glbJoystick[i]->Unacquire();

		// Release any DirectInput objects.
		SAFE_RELEASE(g_glbJoystick[i]);
		SAFE_RELEASE(g_glbDI);
	}

}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�@JoyCon�ɑ΂���ݒ�
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
	VOID* pContext)
{
	g_enumcontext.pPreferredJoyCfg = &g_preferredjoycfg;
	g_enumcontext.bPreferredJoyCfgValid = false;

	auto pEnumContext = reinterpret_cast<DI_ENUM_CONTEXT*>(pContext);
	HRESULT hr;

	if (g_joyconcount >= JOYCON_MAX)
	{
		return DIENUM_STOP;
	}

	// Skip anything other than the perferred joystick device as defined by the control panel.  
	// Instead you could store all the enumerated joysticks and let the user pick.
	if (pEnumContext->bPreferredJoyCfgValid &&
		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
	{
		return DIENUM_CONTINUE;
	}
	// Obtain an interface to the enumerated joystick.
	hr = g_glbDI->CreateDevice(pdidInstance->guidInstance, &g_glbJoystick[g_joyconcount], nullptr);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}
	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.

	IDirectInputJoyConfig8* pJoyConfig = nullptr;
	if (FAILED(hr = g_glbDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
		return hr;

	g_preferredjoycfg.dwSize = sizeof(g_preferredjoycfg);
	if (SUCCEEDED(pJoyConfig->GetConfig(0, &g_preferredjoycfg, DIJC_GUIDINSTANCE))) // This function is expected to fail if no joystick is attached
	{
		g_enumcontext.bPreferredJoyCfgValid = true;
	}

	SAFE_RELEASE(pJoyConfig);

	// Set the data format to "simple joystick" - a predefined data format 
	//
	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().

	if (FAILED(hr = g_glbJoystick[g_joyconcount]->SetDataFormat(&c_dfDIJoystick2)))
	{
		return DIENUM_CONTINUE;
	}

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.

	if (FAILED(hr = g_glbJoystick[g_joyconcount]->SetCooperativeLevel(g_hwnd, DISCL_EXCLUSIVE |
		DISCL_FOREGROUND)))
	{
		return DIENUM_CONTINUE;
	}

	
	g_glbdiDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(hr = g_glbJoystick[g_joyconcount]->GetCapabilities(&g_glbdiDevCaps)))
	{
		return DIENUM_CONTINUE;
	}
	
	
	if (!g_glbJoystick[g_joyconcount]) {
		MessageBox(nullptr, TEXT("Joystick not found."),
			TEXT("Warning!"),
			MB_ICONERROR | MB_OK);
		return S_OK;
	}


	// Enumerate the joystick objects. The callback function enabled user
	// interface elements for objects that are found, and sets the min/max
	// values property for discovered axes.

	if (FAILED(hr = g_glbJoystick[g_joyconcount]->EnumObjects(EnumObjectsCallback,
		(VOID*)g_hwnd, DIDFT_ALL)))
	{
		return DIENUM_CONTINUE;
	}

	g_joyconcount++;

	return DIENUM_CONTINUE;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
�@�@�@�@�@JoyCon�̎擾���鐔�l�Ȃǂ̐ݒ�
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
		if (FAILED(g_glbJoystick[g_joyconcount]->SetProperty(DIPROP_RANGE, &diprg.diph)))
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
�@�@�@�@�@�X�V����
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
HRESULT UpdateInput(HWND hWnd)
{
	for (int i = 0; i < JOYCON_MAX; i++)
	{
		HRESULT     hr;
		DIJOYSTATE2 js;           // Direct Input joystick state 

		g_lastInput[i] = g_nowInput[i];

		if (NULL == g_glbJoystick[i]) {
			return S_OK;
		}

		// Poll the device to read the current state
		hr = g_glbJoystick[i]->Poll();
		if (FAILED(hr))
		{
			hr = g_glbJoystick[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = g_glbJoystick[i]->Acquire();

		}
		hr = g_glbJoystick[i]->GetDeviceState(sizeof(DIJOYSTATE2), &js);
		if (FAILED(hr)) {
			return hr;
		}

		g_nowInput[i] = js;

	}
	return S_OK;

}

float GetAxisX(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[g_joyconcount].lRz < 0)
		{
			g_nowInput[g_joyconcount].lRz = g_nowInput[g_joyconcount].lRz*-1;
		}
	}
	return (float)g_nowInput[JoyConNumber].lRz;
}



float GetAxisY(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[g_joyconcount].rglSlider[1] < 0)
		{
			return (float)g_nowInput[g_joyconcount].rglSlider[1] * -1.0f;
		}
	}
	return (float)g_nowInput[JoyConNumber].rglSlider[1];
}


float GetAxisZ(int JoyConNumber, bool plus)
{
	if (plus)
	{
		if (g_nowInput[g_joyconcount].rglSlider[0] < 0)
		{
			return (float)g_nowInput[g_joyconcount].rglSlider[0] * -1.0f;
		}
	}
	return (float)g_nowInput[JoyConNumber].rglSlider[0];
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
>>>>>>> 3b73f20ab355e091174d7e2d0657ef0d01b278b8
}