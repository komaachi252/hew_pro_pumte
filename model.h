//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[model.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/14(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef MODEL_H_
#define MODEL_H_

#include <d3dx9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Model_Init(void);	//�������֐�
int Model_Load(const char* pFilename);
void Model_Destroy(int ids[], int count);
void Model_Destroy(void);
void Model_Draw(int idx);
void Model_Draw(int idx,const D3DXMATRIX& mtx);
void Model_Uninit(void);
#endif
