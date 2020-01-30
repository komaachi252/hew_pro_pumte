//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�G�t�F�N�g����[effect.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���ۂ���
//                                                               �쐬�� 12/01(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
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

//��������������������������������������������������������������������������������
//	�\���̒�`
//��������������������������������������������������������������������������������
#define FILENAME_LEN (256)
#define EFFECT_MAX (256)
#define EFFECT_FILE_PATH (L"Asset/Effects/")  //  ���f���f�[�^�܂ł̑��΃p�X

//��������������������������������������������������������������������������������
//	�\���̒�`
//��������������������������������������������������������������������������������
struct Effect
{
	wchar_t filename[FILENAME_LEN];

	::Effekseer::Effect* effect;
	//::Effekseer::Handle	handle;
	//::Effekseer::Vector3D position;
};

//��������������������������������������������������������������������������������
//	�O���[�o��
//��������������������������������������������������������������������������������
static IXAudio2MasteringVoice* a2_master;
static IXAudio2* g_xa2;
static Effect* gp_effects = nullptr;
static ::Effekseer::Manager* g_manager;
static ::EffekseerRendererDX9::Renderer* g_renderer;
static ::EffekseerSound::Sound* g_sound;
//��������������������������������������������������������������������������������
//	������
//��������������������������������������������������������������������������������
HRESULT Effect_Init(void)
{
	gp_effects = new Effect[EFFECT_MAX];

	for (int i = 0; i < EFFECT_MAX; i++) {
		gp_effects[i].filename[0] = '\0';  //  �������������
		gp_effects[i].effect = nullptr;
	}

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

	return S_OK;
}

//��������������������������������������������������������������������������������
//	������
//��������������������������������������������������������������������������������
void Efffect_Uninit(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		ES_SAFE_RELEASE(gp_effects[i].effect);
		
	}
	delete[] gp_effects;
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();
	// �T�E���h�p�C���X�^���X��j��
	//g_sound->Destroy();
	// �`��p�C���X�^���X��j��
	g_renderer->Destroy();
}

//��������������������������������������������������������������������������������
//	�G�t�F�N�g�ǂݍ���
//��������������������������������������������������������������������������������
int Effect_Load(const wchar_t* filename)
{
	//�����t�@�C������T��
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (wcscmp(gp_effects[i].filename, filename) == 0) {//�����t�@�C����������
			return i;//�\��ԍ���Ԃ�
		}
	}
	//�V�K�o�^
	for (int i = 0; i < EFFECT_MAX; i++) {
		//�g�p����Ă��Ȃ��ꏊ��T��
		if (gp_effects[i].filename[0] != 0) {//�z��ŏ���\0
			continue;//�O��for���ɖ߂�
		}
		//���f���ǂݍ���
		wcscpy(gp_effects[i].filename, filename);

		
		wchar_t buf[FILENAME_LEN];  //  �t�@�C���p�X�A���p�ϐ�

		//strcpy(buf, EFFECT_FILE_PATH);
		wcscpy(buf, EFFECT_FILE_PATH);

		//strcat(buf, gp_effects[i].filename);
		wcscat(buf, gp_effects[i].filename);

		//LPDIRECT3DDEVICE9 pDevice = GetDevice();  //  �f�o�C�X�̎擾

		// �G�t�F�N�g�̓Ǎ�
		if ((gp_effects[i].effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)buf)) == nullptr){
				MessageBox(nullptr,"�G�t�F�N�g","�����I",MB_OK);
		}
		
		//gp_effects[i].effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Asset/Texture/splash.efk");
		//g_handle = g_manager->Play(g_effect, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

		return i;
	}
	return -1;//�󂫂��Ȃ���
}

//��������������������������������������������������������������������������������
//	�G�t�F�N�g�j��
//��������������������������������������������������������������������������������
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

//��������������������������������������������������������������������������������
//	�G�t�F�N�g�j��
//��������������������������������������������������������������������������������
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


//��������������������������������������������������������������������������������
//	�G�t�F�N�g�`��
//��������������������������������������������������������������������������������
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
	// ���e�s��̍X�V
	g_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f));
	// �J�����s��̍X�V
	g_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(Get_Camera_Pos()->x, Get_Camera_Pos()->y, Get_Camera_Pos()->z),
		::Effekseer::Vector3D(Get_Camera_At()->x, Get_Camera_At()->y, Get_Camera_At()->z), ::Effekseer::Vector3D(Get_Camera_Up()->x, Get_Camera_Up()->y, Get_Camera_At()->z)));
	// 3D�T�E���h�p���X�i�[�ݒ�̍X�V
	//g_sound->SetListener(���X�i�[�ʒu, ���ړ_, ������x�N�g��);
	// �Đ����̃G�t�F�N�g�̈ړ���(::Effekseer::Manager�o�R�ŗl�X�ȃp�����[�^�[���ݒ�ł��܂��B)
	//g_manager->AddLocation(g_handle, ::Effekseer::);
	// �S�ẴG�t�F�N�g�̍X�V
	g_manager->Update();
	g_renderer->BeginRendering();
	g_manager->Draw();
	// �G�t�F�N�g�̍Đ�
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
*/