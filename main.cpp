//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�又��[main.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/04(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include <d3d9.h>
#include "common.h"
#include "system_timer.h"
#include "direct3d.h"
#include "debug_font.h"
#include "scene.h"
#include "input.h"
#include "Input2.h"
#include "model.h"
#include "camera.h"
#include "fade.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define CLASS_NAME     "GameWindow"
#define WINDOW_CAPTION "�J�k�["
#define WINDOW_STYLE  (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)) //�E�B���h�E�̃X�^�C�����`
#define FPS_MEASUREMENT_TIME (1.0f)


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
class Window {
private:
	HWND hWnd;
	HINSTANCE hInstance;
	LPDIRECT3DDEVICE9 Device;
public:
	Window(HINSTANCE hInst);
	void DisplayWindow(int nCmdShow);
	bool Initialize(void);
	void GameLoop(void);
	void Update(void);
	void Draw(void);
	HWND GetWndHundle(void);
	void Finalize(void);
};

//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Window* g_pWindow = nullptr;
static int g_FrameCount = 0; // �t���[���J�E���^�[
static int g_FPSBaseFrameCount = 0; // FPS�v���̊�ƂȂ�t���[���J�E���^�[
static double g_FPSBaseTime = 0.0; // FPS�v���̊�ƂȂ鎞��
static double g_StaticFrameTime = 0; // �t���[���Œ�p�v������
static float g_FPS = 0.0f; // FPS

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//��������������������������������������������������������������������������������
//	�又��
//��������������������������������������������������������������������������������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	g_pWindow = new Window(hInstance);  //  �E�B���h�E�C���X�^���X��

	g_pWindow->DisplayWindow(nCmdShow);
	g_pWindow->Initialize();

	g_pWindow->GameLoop();

	g_pWindow->Finalize();
	delete g_pWindow;
	return 0;
}

//��������������������������������������������������������������������������������
//	�E�B���h�E�v���V�[�W��
//��������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN://�L�[�̓��͂�������
		if (wParam == VK_ESCAPE) {//�L�[�̖��O�������Ă��� Escape�L�[�ŏI������悤�ɂ���
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE://�E�B���h�E����Ƃ��ɏo��
		if (MessageBox(hWnd, "�{���ɏI�����Ă���낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT��GetMessage�ɏo��
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//���̃��b�Z�[�W������������
}


//��������������������������������������������������������������������������������
//	Window�N���X �R���X�g���N�^
//��������������������������������������������������������������������������������
Window::Window(HINSTANCE hInst)
{
	hInstance = hInst;
	Device = nullptr;
	WNDCLASS wc = {};//0�ŏ�����
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };//

	AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);//���j�^�[��
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);//���j�^�[����
	int window_x = max((desktop_width - window_width) / 2, 0);//��ʐ^�񒆂̍��W�𒲂ׂ�X
	int window_y = max((desktop_height - window_height) / 2, 0);//Y
	hWnd = CreateWindow(
		CLASS_NAME,//�N���X��
		WINDOW_CAPTION,//�E�B���h�E�̖��O
		WINDOW_STYLE,//�E�B���h�E�̌` �E�B���h�E�T�C�Y�Œ�
		window_x,//���W����X�@�e�L�X�g���܂߂ĕ�����
		window_y,//Y
		window_width,//��
		window_height,//����
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

//��������������������������������������������������������������������������������
//	Window�N���X �E�B���h�E�\��
//��������������������������������������������������������������������������������
void Window::DisplayWindow(int nCmdShow)
{
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E��\������1 �������͂ق��Ƃ�
	UpdateWindow(hWnd);
}

//��������������������������������������������������������������������������������
//	Window�N���X Window������������
//��������������������������������������������������������������������������������
bool Window::Initialize(void)
{
	D3D_Initialize(hWnd);
	
	InitDirectInput(hWnd);

	Model_Init();

	Device = GetDevice();

	SystemTimer_Initialize();
	
	// �V�X�e���^�C�}�[�̋N��
	SystemTimer_Start();

	// FPS�v���p�ϐ��Q�̏�����
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;

	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFrameTime = g_FPSBaseTime;

	DebugFont_Initialize();

	Keyboard_Initialize(hInstance,hWnd);
	Camera_Init();

	Fade_Init();

	// �Ō��Set_Scene�Ń^�C�g��
	Set_Scene(SCENE_TITLE);
	//Set_Scene(SCENE_GAME);


	return true;
}

//��������������������������������������������������������������������������������
//	Window�N���X �Q�[�����[�v����
//��������������������������������������������������������������������������������
void Window::GameLoop(void)
{
	MSG msg = {};
	while (WM_QUIT != msg.message) {//GetMessge�Ŏ~�܂��Ă���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {//�Q�[���̏���
			double time = SystemTimer_GetTime();
			if (time - g_StaticFrameTime < 1.0f / 60.0f) {
				Sleep(0);
			}
			else {
				g_StaticFrameTime = time;
				Update();
				Draw();
			}
		}
	}
}


//��������������������������������������������������������������������������������
//	Window�N���X Window���X�V����
//��������������������������������������������������������������������������������
void Window::Update(void)
{
	// �t���[���J�E���g�̍X�V
	g_FrameCount++;

	// ���݂̃V�X�e�����Ԃ̎擾
	double time = SystemTimer_GetTime();

	// �O���FPS�v�����Ԃ��K�莞�Ԍo���Ă�����FPS�v��
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) { //�@���̎��ԁ@�|�@�Ƃ��Ă���������

														// FPS�v�Z(�O�񂩂�̌o�߃t���[�����o�ߎ���)
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));

		// FPS�v���̊�ɂȂ�ϐ����X�V
		g_FPSBaseFrameCount = g_FrameCount;
		g_FPSBaseTime = time;

	}

	UpdateInput(hWnd);

	Scene_Update();

	Keyboard_Update();

	Fade_Update();
}

//��������������������������������������������������������������������������������
//	Window�N���X Window���`�揈��
//��������������������������������������������������������������������������������
void Window::Draw(void)
{
	//  ��ʂ̃N���A
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(20, 200, 0, 255), 1.0f, 0);
	Device->BeginScene();
	Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // �G�t�F�N�g�̎��K�{


	Scene_Draw();

	Fade_Draw();
	//DebugFont_Draw(0, 0, "%f", g_FPS);

	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}

//��������������������������������������������������������������������������������
//	Window�N���X Window���I������
//��������������������������������������������������������������������������������
void Window::Finalize(void)
{
	Model_Uninit();

	Fade_Uninit();

	UninitDirectInput();

	DebugFont_Finalize();

	D3D_Finalize();
}

//��������������������������������������������������������������������������������
//	Window�N���X Window���`�揈��
//��������������������������������������������������������������������������������
HWND Window::GetWndHundle(void)
{
	return hWnd;
}

//��������������������������������������������������������������������������������
//	Window�N���X Window���`�揈��
//��������������������������������������������������������������������������������
HWND GetWndHundle(void)
{
	return g_pWindow->GetWndHundle();
}