//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	���j���[����[Tutorial.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/06(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c

//  �����Ƀw�b�_���C���N���[�h
#include "Tutorial_manager.h"
#include "Tutorial_Logo.h"
#include "fade.h"
#include "camera.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Tutorial_Initialize(void)
{
	// --------------------------------
	//  �������֐����L�q
	// --------------------------------
	//  JKimouto_Initialize();
	//  Mama_Initialize();

	Tutorial_Manager_Init();
	Tutorial_Logo_Init();
	Camera_2D();
	Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Tutorial_Update(void)
{
	// --------------------------------
	//  �X�V�֐����L�q
	// --------------------------------
	Tutorial_Manager_Update();
	Tutorial_Logo_Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Tutorial_Draw(void)
{
	// --------------------------------
	//  �`��֐����L�q
	// --------------------------------
	Tutorial_Logo_Draw();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Tutorial_Finalize(void)
{
	// --------------------------------
	//  �I���֐����L�q
	// --------------------------------
	Tutorial_Logo_Uninit();
	Tutorial_Manager_Uninit();
}
