/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	�e�N�X�`������[texture.cpp]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#define _CRT_SECURE_NO_WARNINGS
#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�}�N����`
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define FILENAME_MAX    (128)
#define TEXTUREDATA_MAX  (64)



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�\���̐錾
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct Texture_tag
{
	char fliename[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureData;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�O���[�o���ϐ�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static TextureData g_TextureData[TEXTUREDATA_MAX] = {};



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�ǂݍ��ރe�N�X�`���̗\�񏈗�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_SetLoadFile(const char* pFilename, int width, int height)//�@���@�������ԈႦ��Ɗ댯
{
	//�����t�@�C������T��
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (strcmp(g_TextureData[i].fliename, pFilename) == 0) {//�����t�@�C����������
			return i;//�\��ԍ���Ԃ�
		}
	}
	//�V�K�o�^
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		//�g�p����Ă��Ȃ��ꏊ��T��
		if (g_TextureData[i].fliename[0] != 0) {//�z��ŏ���\0
			continue;//�O��for���ɖ߂�
		}
		//�o�^
		strcpy(g_TextureData[i].fliename, pFilename);
		g_TextureData[i].width  = width;
		g_TextureData[i].height = height;
		return i;
	}
	return -1;//�󂫂��Ȃ���
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�e�N�X�`���ǂݍ��ݏ���
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9  g_pDevice = GetDevice();
	int error_count = 0;
	
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {

		if (g_TextureData[i].fliename[0] == 0) {
			continue;
		}
		if (g_TextureData[i].pTexture != NULL) {
			continue;
		}
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(g_pDevice, g_TextureData[i].fliename, &g_TextureData[i].pTexture);

	}
	return error_count;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id)
{
	return g_TextureData[id].pTexture;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�w��e�N�X�`���j��֐�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Texture_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (g_TextureData[ids[i]].pTexture != NULL) {
			g_TextureData[ids[i]].pTexture->Release();
			g_TextureData[ids[i]].pTexture = NULL;
			g_TextureData[ids[i]].fliename[0] = 0;
			g_TextureData[ids[i]].width  = 0;
			g_TextureData[ids[i]].height = 0;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�S�e�N�X�`���j��֐�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Texture_Destroy(void)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureData[i].pTexture != NULL) {
			g_TextureData[i].pTexture->Release();
			g_TextureData[i].pTexture = NULL;
			g_TextureData[i].fliename[0] = 0;
			g_TextureData[i].width  = 0;
			g_TextureData[i].height = 0;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�e�N�X�`�����擾�֐�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_GetWidth(int id)
{
	return g_TextureData[id].width;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�e�N�X�`�������擾�֐�
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_GetHeight(int id)
{
	return g_TextureData[id].height;
}



