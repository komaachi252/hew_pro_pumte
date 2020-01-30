//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	エフェクト処理[effect.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 安保くん
//                                                               作成日 12/01(日)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#define _CRT_SECURE_NO_WARNINGS

#include <d3d9.h>
#include <XAudio2.h>
#include <string>
#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "xaudio2.lib" )
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#include <stdio.h>
#include <windows.h>
#include <string>
#include "input.h" 
#include "camera.h"
#include <d3dx9.h>
#include "common.h"
#include "direct3D.h"
#include "camera.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	構造体定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define FILENAME_LEN (256)
#define EFFECT_MAX (256)
#define EFFECT_FILE_PATH (L"Asset/Effects/")  //  モデルデータまでの相対パス

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	構造体定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
struct Effect
{
	wchar_t filename[FILENAME_LEN];

	::Effekseer::Effect* effect;
	//::Effekseer::Handle	handle;
	//::Effekseer::Vector3D position;
};

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static IXAudio2MasteringVoice* a2_master;
static IXAudio2* g_xa2;
static Effect* gp_effects = nullptr;
static ::Effekseer::Manager* g_manager;
static ::EffekseerRendererDX9::Renderer* g_renderer;
static ::EffekseerSound::Sound* g_sound;
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
HRESULT Effect_Init(void)
{
	gp_effects = new Effect[EFFECT_MAX];

	for (int i = 0; i < EFFECT_MAX; i++) {
		gp_effects[i].filename[0] = '\0';  //  文字列を初期化
		gp_effects[i].effect = nullptr;
	}

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

	return S_OK;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Efffect_Uninit(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		ES_SAFE_RELEASE(gp_effects[i].effect);
		
	}
	delete[] gp_effects;
	// エフェクト管理用インスタンスを破棄
	g_manager->Destroy();
	// サウンド用インスタンスを破棄
	//g_sound->Destroy();
	// 描画用インスタンスを破棄
	g_renderer->Destroy();
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	エフェクト読み込み
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
int Effect_Load(const wchar_t* filename)
{
	//同じファイル名を探す
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (wcscmp(gp_effects[i].filename, filename) == 0) {//同じファイルを見つけた
			return i;//予約番号を返す
		}
	}
	//新規登録
	for (int i = 0; i < EFFECT_MAX; i++) {
		//使用されていない場所を探す
		if (gp_effects[i].filename[0] != 0) {//配列最初が\0
			continue;//前のfor文に戻る
		}
		//モデル読み込み
		wcscpy(gp_effects[i].filename, filename);

		
		wchar_t buf[FILENAME_LEN];  //  ファイルパス連結用変数

		//strcpy(buf, EFFECT_FILE_PATH);
		wcscpy(buf, EFFECT_FILE_PATH);

		//strcat(buf, gp_effects[i].filename);
		wcscat(buf, gp_effects[i].filename);

		//LPDIRECT3DDEVICE9 pDevice = GetDevice();  //  デバイスの取得

		// エフェクトの読込
		if ((gp_effects[i].effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)buf)) == nullptr){
				MessageBox(nullptr,"エフェクト","無し！",MB_OK);
		}
		
		//gp_effects[i].effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Asset/Texture/splash.efk");
		//g_handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

		return i;
	}
	return -1;//空きがないよ
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	エフェクト破棄
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Effect_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (gp_effects[ids[i]].filename[0] == '\0') {
			continue;
		}
		gp_effects[ids[i]].filename[0] = '\0';
		ES_SAFE_RELEASE(gp_effects[ids[i]].effect);
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	エフェクト破棄
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Effect_Destroy(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (gp_effects[i].filename[0] == '\0') {
			continue;
		}
		gp_effects[i].filename[0] = '\0';
		ES_SAFE_RELEASE(gp_effects[i].effect);
	}
}


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	エフェクト描画
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Effect_Draw(int idx, const D3DXMATRIX& mtx)
{
	/*
	D3DXVECTOR3 position = GetCameraPosition();
	D3DXVECTOR3 at = GetAt();
	D3DXVECTOR3 up = GetUpVec();

	g_position.X = position.x;
	g_position.Y = position.y;
	g_position.Z = position.z;
	*/
	// 投影行列の更新
	g_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f));
	// カメラ行列の更新
	g_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(Get_Camera_Pos()->x, Get_Camera_Pos()->y, Get_Camera_Pos()->z),
		::Effekseer::Vector3D(Get_Camera_At()->x, Get_Camera_At()->y, Get_Camera_At()->z), ::Effekseer::Vector3D(Get_Camera_Up()->x, Get_Camera_Up()->y, Get_Camera_At()->z)));
	// 3Dサウンド用リスナー設定の更新
	//g_sound->SetListener(リスナー位置, 注目点, 上方向ベクトル);
	// 再生中のエフェクトの移動等(::Effekseer::Manager経由で様々なパラメーターが設定できます。)
	//g_manager->AddLocation(g_handle, ::Effekseer::);
	// 全てのエフェクトの更新
	g_manager->Update();
	g_renderer->BeginRendering();
	g_manager->Draw();
	// エフェクトの再生
	g_manager->Play(gp_effects[idx].effect, ::Effekseer::Vector3D(mtx._41, mtx._42, mtx._43));
	g_renderer->EndRendering();
	//GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
}
/*
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
*/