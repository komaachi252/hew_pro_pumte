#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	�e�N�X�`������[texture.h]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#include <d3d9.h>


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	�v���g�^�C�v�錾
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int Texture_SetLoadFile(const char* pFilename, int width, int height);//�ǂݍ��ރe�N�X�`���̗\��@(�t�@�C����, �e�N�X�`����,�@����)�߂�l �\��ԍ�(id) -1���Ԃ�����󂫂��Ȃ���
int Texture_Load(void);                       //�t�@�C���̓ǂݍ��� �߂�l�@�ǂݍ��߂Ȃ�������
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//�e�N�X�`���C���^�t�F�[�X���擾����֐��@(�\��ԍ�) �s���ԍ���NULL���Ԃ�
void Texture_Destroy(int ids[], int count);   //�e�N�X�`����������@��������@(���������id���������z��̐擪�A�h���X, ���̃A�h���X���牽���H)    int id; (&id,1)�ł������@
void Texture_Destroy(void);                   //�e�N�X�`����������@�S�����
int Texture_GetWidth(int id);                 //�e�N�X�`���̕����擾
int Texture_GetHeight(int id);                //�e�N�X�`���̍������擾

#endif