
#include <stdio.h>
#include <windows.h>
#include <string>
#include "input.h" 
#include "camera.h"
#include <d3dx9.h>
#include "common.h"
#include "direct3D.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <d3d9.h>
#include <XAudio2.h>
#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "xaudio2.lib" )

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

static HWND g_window_handle = NULL;
static int g_window_width = 800;
static int g_window_height = 600;
static ::Effekseer::Manager*				g_manager = NULL;
static ::EffekseerRendererDX9::Renderer*	g_renderer = NULL;
//static ::EffekseerSound::Sound*			g_sound = NULL;
static ::Effekseer::Effect*				g_effect = NULL;
static ::Effekseer::Handle				g_handle = -1;
static ::Effekseer::Vector3D			g_position;

static LPDIRECT3D9						g_d3d = NULL;
static LPDIRECT3DDEVICE9				g_d3d_device = NULL;
static IXAudio2*						g_xa2 = NULL;
static IXAudio2MasteringVoice*			g_xa2_master = NULL;

void Effect_Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 描画管理インスタンスの生成
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 2000);
	// サウンド管理インスタンスの生成
	//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);
	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);

	// 描画方法を指定します。独自に拡張することもできます。
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());

	// サウンド再生用インスタンスの指定
	//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

	// サウンドデータの読込方法の指定(圧縮フォーマット、パッケージ等から読み込む場合拡張する必要があります。)
	//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());

	// 座標系の指定(RHで右手系、LHで左手系)
	g_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// エフェクトの読込
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Asset/splash.efk");
	//g_handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
}

void Effect_Uninit(void)
{
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(g_effect);
	// エフェクト管理用インスタンスを破棄
	g_manager->Destroy();
	// サウンド用インスタンスを破棄
	//g_sound->Destroy();
	// 描画用インスタンスを破棄
	g_renderer->Destroy();

}

void Effect_Update(void)
{
	D3DXVECTOR3 position = GetCameraPosition();
	D3DXVECTOR3 at = GetAt();
	D3DXVECTOR3 up = GetUpVec();

	g_position.X = position.x;
	g_position.Y = position.y;
	g_position.Z = position.z;

	// 投影行列の更新
	g_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HIGHT, 0.1f, 100.0f));
	// カメラ行列の更新
	g_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(g_position, ::Effekseer::Vector3D(at.x, at.y, at.z), ::Effekseer::Vector3D(up.x, up.y, up.z)));
	// 3Dサウンド用リスナー設定の更新
	//g_sound->SetListener(リスナー位置, 注目点, 上方向ベクトル);
	// 再生中のエフェクトの移動等(::Effekseer::Manager経由で様々なパラメーターが設定できます。)
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D);
	// 全てのエフェクトの更新
	g_manager->Update();
}

void Effect_Draw(void)
{
	g_renderer->BeginRendering();
	g_manager->Draw();
	// エフェクトの再生
	if (Keyboard_IsTrigger(DIK_B))
	{
		Effekseer::Handle handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
	}
	
	g_renderer->EndRendering();
}
