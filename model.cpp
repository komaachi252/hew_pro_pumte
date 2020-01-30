//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[model.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/14(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#define _CRT_SECURE_NO_WARNINGS
#include <d3dx9.h>
#include <d3d9.h>
#include "texture.h"
#include "direct3d.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define MODEL_FILE_PATH ("Asset/Texture/")  //  ���f���f�[�^�܂ł̑��΃p�X
#define MODEL_MAX (36)  //  ���f����
#define MODEL_FILE_LEN (256)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
struct Model{
	char filename[MODEL_FILE_LEN];
	LPD3DXMESH pMesh; //  ���b�V����� �����Ȃ畡���K�v
	DWORD MaterialCount; //  �}�e���A���̐�
	LPD3DXBUFFER pMaterials;  //  �}�e���A���̏��i�[�p
	int* TextureIds;  //  �e�N�X�`���Ǘ��ԍ��ۑ��p
};

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Model* g_pModel = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Model_Init(void)
{
	g_pModel = new Model[MODEL_MAX];

	for (int i = 0; i < MODEL_MAX; i++) {
		g_pModel[i].filename[0] = '\0';  //  �������������
		g_pModel[i].pMesh = nullptr;
		g_pModel[i].MaterialCount = 0;
		g_pModel[i].pMaterials = nullptr;
		g_pModel[i].TextureIds = nullptr;
	}
}

//��������������������������������������������������������������������������������
//	���f���ǂݍ��ݏ���
//��������������������������������������������������������������������������������
int Model_Load(const char* pFilename)
{
	//�����t�@�C������T��
	for (int i = 0; i < MODEL_MAX; i++) {
		if (strcmp(g_pModel[i].filename, pFilename) == 0) {//�����t�@�C����������
			return i;//�\��ԍ���Ԃ�
		}
	}
	//�V�K�o�^
	for (int i = 0; i < MODEL_MAX; i++) {
		//�g�p����Ă��Ȃ��ꏊ��T��
		if (g_pModel[i].filename[0] != 0) {//�z��ŏ���\0
			continue;//�O��for���ɖ߂�
		}
		//���f���ǂݍ���
		strcpy(g_pModel[i].filename, pFilename);

		char buf[MODEL_FILE_LEN];  //  �t�@�C���p�X�A���p�ϐ�

		strcpy(buf, MODEL_FILE_PATH);

		strcat(buf, g_pModel[i].filename);

		LPDIRECT3DDEVICE9 pDevice = GetDevice();  //  �f�o�C�X�̎擾

		HRESULT hr = D3DXLoadMeshFromX(buf, D3DXMESH_MANAGED, pDevice, nullptr, &g_pModel[i].pMaterials, nullptr,
									 &g_pModel[i].MaterialCount, &g_pModel[i].pMesh);  //  �ǂ߂Ȃ�������I�v�V�������^��
		if (FAILED(hr)) {
			MessageBox(nullptr, "���f���ǂݍ��݂Ɏ��s���܂���", "���s", MB_OK);
			exit(1);
		}

		g_pModel[i].TextureIds = new int[g_pModel[i].MaterialCount];

		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[i].pMaterials->GetBufferPointer();

		//  �e�}�e���A�������擾
		for (unsigned int j = 0; j < g_pModel[i].MaterialCount; j++) {
			//  �F�̎擾
			//pMat[i].MatD3D.Diffuse

			//  �e�N�X�`���̓ǂݍ���
			if (pMat[j].pTextureFilename == nullptr) {
				//  �Ȃ��Ƃ�
				g_pModel[i].TextureIds[j] = -1;  //  �ǂݍ��߂ĂȂ��Ƃ����؋�  Texture.cpp��-1�ɑΉ�������
			}
			else {
				//  �t�@�C�����̉��H �p�X�̒ǉ� �t�@�C�����o�Ȃ��悤��

				strcpy(buf, MODEL_FILE_PATH);
				strcat(buf, pMat[j].pTextureFilename);
				g_pModel[i].TextureIds[j] = Texture_SetLoadFile(buf, 0, 0);  //  �e�N�X�`���J��
			}
		}
		Texture_Load();

		return i;
	}
	return -1;//�󂫂��Ȃ���

}


//��������������������������������������������������������������������������������
//	�w�胂�f���j������ 
//��������������������������������������������������������������������������������
void Model_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (g_pModel[ids[i]].filename[0] == '\0') {
			continue;
		}
		g_pModel[ids[i]].filename[0] = '\0';
		g_pModel[ids[i]].pMesh = nullptr;
		g_pModel[ids[i]].MaterialCount = 0;
		g_pModel[ids[i]].pMaterials = nullptr;
		delete[] g_pModel[ids[i]].TextureIds;
	}
}

//��������������������������������������������������������������������������������
//	�S���f���j������ 
//��������������������������������������������������������������������������������
void Model_Destroy(void)
{
	for (int i = 0; i < MODEL_MAX; i++) {
		if (g_pModel[i].filename[0] == '\0') {
			continue;
		}
		g_pModel[i].filename[0] = '\0';
		g_pModel[i].pMesh = nullptr;
		g_pModel[i].MaterialCount = 0;
		g_pModel[i].pMaterials = nullptr;
		delete[] g_pModel[i].TextureIds;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈�� �e�N�X�`���\��ԍ��������ɒP�ʍs��ŕ\��
//��������������������������������������������������������������������������������
void Model_Draw(int idx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DMATERIAL9 mat = {}; // �}�e���A���ݒ�p

	for (DWORD i = 0; i < g_pModel[idx].MaterialCount; i++) {
		//  �}�e���A���ݒ�
		if (g_pModel[idx].TextureIds[i] < 0) {
			//  �}�e���A���J���[�̂�
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[idx].pMaterials->GetBufferPointer();

			//  �}�e���A��������
			mat.Diffuse = pMat->MatD3D.Diffuse;
			mat.Ambient = pMat->MatD3D.Ambient;
			mat.Specular = pMat->MatD3D.Specular;
			mat.Emissive = pMat->MatD3D.Emissive;
			mat.Power = pMat->MatD3D.Power;

			//  �}�e���A�����f�o�C�X�ɐݒ�
			pDevice->SetMaterial(&mat);
		}
		else {
			mat.Diffuse.r = 1.0;
			mat.Diffuse.b = 1.0;
			mat.Diffuse.g = 1.0;
			mat.Diffuse.a = 1.0;

			pDevice->SetMaterial(&mat);
			//  �}�e���A���J���[�𔒂ɂ��ăe�N�X�`����\��
			pDevice->SetTexture(0, Texture_GetTexture(g_pModel[idx].TextureIds[i]));
		}
		//  ���b�V���`��
		g_pModel[idx].pMesh->DrawSubset(i);
	}
}

//��������������������������������������������������������������������������������
//	�`�揈�� �e�N�X�`���\��ԍ���������
//��������������������������������������������������������������������������������
void Model_Draw(int idx, const D3DXMATRIX& mtx)
{
	if (idx <= -1) {
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	for (DWORD i = 0; i < g_pModel[idx].MaterialCount; i++) {
		//  �}�e���A���ݒ�
		if (g_pModel[idx].TextureIds[i] < 0) {
			//  �}�e���A���J���[�̂�
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[idx].pMaterials->GetBufferPointer();
			D3DMATERIAL9 mat = {};

			//  �}�e���A��������
			mat.Diffuse = pMat->MatD3D.Diffuse;
			mat.Ambient = pMat->MatD3D.Ambient;
			mat.Specular = pMat->MatD3D.Specular;
			mat.Emissive = pMat->MatD3D.Emissive;
			mat.Power = pMat->MatD3D.Power;

			//  �}�e���A�����f�o�C�X�ɐݒ�
			pDevice->SetMaterial(&mat);
		}
		else {
			D3DMATERIAL9 mat = {};
			mat.Diffuse.r = 1.0f;
			mat.Diffuse.b = 1.0f;
			mat.Diffuse.g = 1.0f;
			mat.Diffuse.a = 1.0f;
			mat.Ambient.r = 1.0f;
			mat.Ambient.g = 1.0f;
			mat.Ambient.b = 1.0f;
			mat.Ambient.a = 1.0f;

			pDevice->SetMaterial(&mat);
			//  �}�e���A���J���[�𔒂ɂ��ăe�N�X�`����\��
			pDevice->SetTexture(0, Texture_GetTexture(g_pModel[idx].TextureIds[i]));
		}
		//  ���b�V���`��
		g_pModel[idx].pMesh->DrawSubset(i);
	}
}



//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Model_Uninit(void)
{
	delete[] g_pModel;
}

