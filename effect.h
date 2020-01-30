#pragma once
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�G�t�F�N�g�w�b�_[effect.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���ۂ���
//                                                               �쐬�� 12/01(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3dx9.h>


HRESULT Effect_Init(void);
void Efffect_Uninit(void);
int Effect_Load(const wchar_t* filename);
void Effect_Destroy(int ids[], int count);
void Effect_Destroy(void);
void Effect_Draw(int idx, const D3DXMATRIX& mtx);

