//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	direct3d����[direct3d.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/04(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3d9.h>
#include <windows.h>
#include "common.h"

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
class Direct3D {
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 Device;
public:
	Direct3D(void);
	~Direct3D(void);
	bool Initialize(HWND hWnd);
	LPDIRECT3DDEVICE9 GetDevice(void);
};
//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Direct3D* g_pD3D = nullptr;


//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
bool D3D_Initialize(HWND hWnd)
{
	g_pD3D = new Direct3D;
	if (!g_pD3D->Initialize(hWnd)) {
		return false;
	}
	return true;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void D3D_Finalize(void)
{
	delete g_pD3D;
}

//��������������������������������������������������������������������������������
//	�f�o�C�X�擾����
//��������������������������������������������������������������������������������
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3D->GetDevice();
}

//��������������������������������������������������������������������������������
//	Direct3d�N���X �R���X�g���N�^
//��������������������������������������������������������������������������������
Direct3D::Direct3D(void)
{
	d3d = nullptr;
	Device = nullptr;
}

//��������������������������������������������������������������������������������
//	Direct3d�N���X ����������
//��������������������������������������������������������������������������������
bool Direct3D::Initialize(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);//�C���^�t�F�[�X���擾�@NULL���Ԃ��ꂽ��G���[�@���b�Z�[�W�{�b�N�X�ŕ\��
	if (d3d == NULL) {
		MessageBox(NULL, "�C���^�t�F�[�X���擾�o���܂���ł���", "�m�F", MB_OK);
	}

	D3DPRESENT_PARAMETERS d3dpp = {};//Direct3D�f�o�C�X�̎擾�ׂ̈̍\���̕ϐ�

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�v�X16bit D24S8�ɕς���
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//fream��  IMMEDIATE�@fps�ő��@�`���ɂ����\���X�V����
														 //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &Device);
	if (FAILED(hr)) {
		MessageBox(hWnd, "�f�o�C�X���擾�o���܂���ł����B", "�G���[", MB_OK);
		return false;
	}
	return true;
}

//��������������������������������������������������������������������������������
//	Direct3d�N���X �f�X�g���N�^
//��������������������������������������������������������������������������������
Direct3D::~Direct3D(void)
{
	if (Device != nullptr) {
		Device->Release();
		Device = nullptr;
	}
	if (d3d != nullptr) {
		d3d->Release();
		d3d = nullptr;
	}
}

//��������������������������������������������������������������������������������
//	Direct3d�N���X �f�o�C�X�擾�֐�
//��������������������������������������������������������������������������������
LPDIRECT3DDEVICE9 Direct3D::GetDevice(void)
{
	return Device;
}
