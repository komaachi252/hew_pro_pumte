
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

	// �`��Ǘ��C���X�^���X�̐���
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 2000);
	// �T�E���h�Ǘ��C���X�^���X�̐���
	//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

	// �`����@���w�肵�܂��B�Ǝ��Ɋg�����邱�Ƃ��ł��܂��B
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());

	// �T�E���h�Đ��p�C���X�^���X�̎w��
	//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

	// �T�E���h�f�[�^�̓Ǎ����@�̎w��(���k�t�H�[�}�b�g�A�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());

	// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
	g_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// �G�t�F�N�g�̓Ǎ�
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Asset/splash.efk");
	//g_handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
}

void Effect_Uninit(void)
{
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	ES_SAFE_RELEASE(g_effect);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();
	// �T�E���h�p�C���X�^���X��j��
	//g_sound->Destroy();
	// �`��p�C���X�^���X��j��
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

	// ���e�s��̍X�V
	g_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HIGHT, 0.1f, 100.0f));
	// �J�����s��̍X�V
	g_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(g_position, ::Effekseer::Vector3D(at.x, at.y, at.z), ::Effekseer::Vector3D(up.x, up.y, up.z)));
	// 3D�T�E���h�p���X�i�[�ݒ�̍X�V
	//g_sound->SetListener(���X�i�[�ʒu, ���ړ_, ������x�N�g��);
	// �Đ����̃G�t�F�N�g�̈ړ���(::Effekseer::Manager�o�R�ŗl�X�ȃp�����[�^�[���ݒ�ł��܂��B)
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D);
	// �S�ẴG�t�F�N�g�̍X�V
	g_manager->Update();
}

void Effect_Draw(void)
{
	g_renderer->BeginRendering();
	g_manager->Draw();
	// �G�t�F�N�g�̍Đ�
	if (Keyboard_IsTrigger(DIK_B))
	{
		Effekseer::Handle handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
	}
	
	g_renderer->EndRendering();
}
