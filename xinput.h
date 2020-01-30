//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	xinput�w�b�_[xinput.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 12/21(�y)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef XINPUT_H_
#define XINPUT_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#include <d3d9.h>
#include <XInput.h>
//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
bool Xinput_Init(HWND hWnd);	//�������֐�
void Xinput_Uninit(void);	//�I�������֐�
void Xinput_Update(void);	//�X�V����
bool Xinput_IsPress(int key);
bool Xinput_IsTrigger(int key);
bool Xinput_IsExit(int key);
float Xinput_IsAxisLX(void);
float Xinput_IsAxisRX(void);
float Xinput_IsAxisLY(void);
float Xinput_IsAxisRY(void);
bool Xinput_IsTriggerL2(void);
bool Xinput_IsTriggerR2(void);
void Xinput_Vibration(int frame, WORD left_speed, WORD right_speed);
#endif
