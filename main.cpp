//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	主処理[main.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 11/04(月)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include "common.h"
#include "system_timer.h"
#include "direct3d.h"
#include "debug_font.h"
#include "scene.h"


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define CLASS_NAME     "GameWindow"
#define WINDOW_CAPTION "カヌー"
#define WINDOW_STYLE  (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)) //ウィンドウのスタイルを定義
#define FPS_MEASUREMENT_TIME (1.0f)


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static Window* g_pWindow = nullptr;
static int g_FrameCount = 0; // フレームカウンター
static int g_FPSBaseFrameCount = 0; // FPS計測の基となるフレームカウンター
static double g_FPSBaseTime = 0.0; // FPS計測の基となる時間
static double g_StaticFrameTime = 0; // フレーム固定用計測時間
static float g_FPS = 0.0f; // FPS

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	主処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	g_pWindow = new Window(hInstance);  //  ウィンドウインスタンス化

	g_pWindow->DisplayWindow(nCmdShow);
	g_pWindow->Initialize();

	g_pWindow->GameLoop();

	g_pWindow->Finalize();
	delete g_pWindow;

	return 0;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	ウィンドウプロシージャ
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN://キーの入力があった
		if (wParam == VK_ESCAPE) {//キーの名前を持っている Escapeキーで終了するようにする
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE://ウィンドウ閉じるときに出る
		if (MessageBox(hWnd, "本当に終了してもよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUITをGetMessageに出す
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//他のメッセージを処理したい
}


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス コンストラクタ
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
Window::Window(HINSTANCE hInst)
{
	hInstance = hInst;
	Device = nullptr;
	WNDCLASS wc = {};//0で初期化
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
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);//モニター幅
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);//モニター高さ
	int window_x = max((desktop_width - window_width) / 2, 0);//画面真ん中の座標を調べるX
	int window_y = max((desktop_height - window_height) / 2, 0);//Y
	hWnd = CreateWindow(
		CLASS_NAME,//クラス名
		WINDOW_CAPTION,//ウィンドウの名前
		WINDOW_STYLE,//ウィンドウの形 ウィンドウサイズ固定
		window_x,//座標左上X　テキストも含めて幅高さ
		window_y,//Y
		window_width,//幅
		window_height,//高さ
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス ウィンドウ表示
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Window::DisplayWindow(int nCmdShow)
{
	ShowWindow(hWnd, nCmdShow);//ウィンドウを表示する1 第二引数はほっとく
	UpdateWindow(hWnd);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Window::Initialize(void)
{
	D3D_Initialize(hWnd);
	
	Device = GetDevice();

	SystemTimer_Initialize();
	
	// システムタイマーの起動
	SystemTimer_Start();

	// FPS計測用変数群の初期化
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;

	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFrameTime = g_FPSBaseTime;

	DebugFont_Initialize();



	// 最後にSet_Sceneでタイトル
	// Set_Scene(SCENE_TITLE);


	return true;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス ゲームループ処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Window::GameLoop(void)
{
	MSG msg = {};
	while (WM_QUIT != msg.message) {//GetMessgeで止まっている
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {//ゲームの処理
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


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Window::Update(void)
{
	// フレームカウントの更新
	g_FrameCount++;

	// 現在のシステム時間の取得
	double time = SystemTimer_GetTime();

	// 前回のFPS計測時間が規定時間経っていたらFPS計測
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) { //　今の時間　－　とっておいた時間

														// FPS計算(前回からの経過フレーム÷経過時間)
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));

		// FPS計測の基になる変数を更新
		g_FPSBaseFrameCount = g_FrameCount;
		g_FPSBaseTime = time;

	}

	Scene_Update();

}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Window::Draw(void)
{
	//  画面のクリア
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(80, 100, 200, 255), 1.0f, 0);
	Device->BeginScene();

	Scene_Draw();



	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Window::Finalize(void)
{

	DebugFont_Finalize();

	D3D_Finalize();
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
HWND Window::GetWndHundle(void)
{
	return hWnd;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	Windowクラス Window内描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
HWND GetWndHundle(void)
{
	return g_pWindow->GetWndHundle();
}



