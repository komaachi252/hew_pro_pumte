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
#include "texture.h"
#include "direct3d.h"
#include "model.h"
#include "Input2.h"
#include "debug_font.h"
#include "Judgement.h"
#include "brocks.h"
#include "player.h"
#include "input.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static int tex;
static int tex2;

static float x = 0.0f;
static float y = 0.0f;

static float jj = 0.0f;

static D3DXVECTOR3 g_pos(0.0f, 1.0f, -10.0f);

//�����蔻�蒷��
static float g_coliLenth = 0.0f;
//�����蔻��
static Coli g_coliBrock[BROCK_NUM] = { 0 };

//���x
static float g_speed = 0.1f;
//�����x
static float g_acceralation = 0.0f;

static int frame;

static float g_angle = 0.0f;
static int count = 0;
static int countl = 0;
static int countr = 0;
static int g_cuvetex = 0;
static float g_moveSpeed = 0.0f;
static D3DXVECTOR3 Position(0.0f, 0.8f, 0.0f);
static D3DXVECTOR3 vecDir(0.0f, 0.0f, 0.0f);
static bool turnl = false;
static bool turnr = false;
static float Rot_Ang;
static float Rot_Now = 0.0f;
static D3DXVECTOR3 vecfront;
static float g_rotationspeed = 0.0f;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Player_Init(void)
{

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//tex = Model_Load("gradriel.x");
	tex = Model_Load("ft.x");
	//tex = Model_Load("boat1.x");
	//tex = Model_Load("MetaKnight.x");
	//tex = Model_Load("cart.x");

	//�����蔻��n
	g_coliLenth = 1.0f;
	for (int i = 0; i < BROCK_NUM; i++)
	{
		g_coliBrock[i].now = false;
		g_coliBrock[i].past = false;
	}
	frame=-1;

}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Player_Uninit(void)
{

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Player_Update(void)
{
	D3DXVECTOR3 vecz(0.0f, 0.0f, 1.0f);

	float right = GetAxisZ(1, true);
	float left = GetAxisZ(0, true);

	Rot_Ang = right - left;

	//�����ʒu�ɖ߂�
	if (GetBotton(0, 5) || Keyboard_IsPress(DIK_1))
	{
		Position.x = 0.0f;
		Position.y = 0.0f;
		Position.z = 0.0f;
		g_moveSpeed = 0.0f;
	}

	if (GetBotton(0, 4))
	{
		Position.x = 0.0f;
		Position.y = 0.0f;
		Position.z = 0.0f;
	}

	if (count >= 20)
	{
		vecfront = vecz;
		count = 0;
	}
	/*
	if (Rot_Ang > 0)
	{
	//�E�ɉ�]
	D3DXMATRIX mtxrot;
	Rot_Ang *= 0.00001f;
	Rot_Now += Rot_Ang;
	D3DXMatrixRotationY(&mtxrot, Rot_Now);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxrot);
	//g_moveSpeed += 0.1f*j_conPos;
	g_moveSpeed += 0.00001f*(right + left);

	}
	else if (Rot_Ang < 0)
	{
	//���ɉ�]
	D3DXMATRIX mtxrot;
	Rot_Ang *= 0.00001f;
	Rot_Now += Rot_Ang;
	D3DXMatrixRotationY(&mtxrot, Rot_Now);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxrot);
	//g_moveSpeed += 0.1f*j_conPos;
	g_moveSpeed += 0.00001f*(right + left);
	}*/

	if (countr > 10 && countl > 10)
	{
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_moveSpeed += 0.01f;
		countl = 0;
		countr = 0;
	}

	if (countr > 15)
	{
		//�E�ɉ�]
		D3DXMATRIX mtxrot;
		Rot_Ang *= 0.00001f;
		Rot_Now += Rot_Ang;
		Rot_Now = 0.5f;
		D3DXMatrixRotationY(&mtxrot, Rot_Now);
		D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxrot);
		g_moveSpeed += 0.01f;
		countl = 0;
		countr = 0;
	}
	if (countl > 15)
	{
		//���ɉ�]
		D3DXMATRIX mtxrot;
		Rot_Ang *= 0.00001f;
		Rot_Now += Rot_Ang;
		Rot_Now = 0.5f;
		D3DXMatrixRotationY(&mtxrot, -Rot_Now);
		D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxrot);
		g_moveSpeed += 0.01f;
		countl = 0;
		countr = 0;
	}

	float axisz = GetAxisZ(0, true) - GetAxisZ(1, true);



	if (Keyboard_IsPress(DIK_F) || GetAxisZ(0, true) > 500)
	{
		countl++;
	}
	if (Keyboard_IsPress(DIK_J) || GetAxisZ(1, true) > 500)
	{
		countr++;
	}

	/*
	D3DXMATRIX mtxRotation;
	float rotate = acosf(D3DXVec3Dot(&vecfront, &vecz));
	D3DXVECTOR3 gaiseki(0.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&gaiseki, &vecfront, &vecz);
	if (gaiseki.y > 0)
	{
	if (fabs(rotate) < g_rotationspeed)
	{
	D3DXMatrixRotationY(&mtxRotation, -rotate);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxRotation);
	}
	else
	{
	D3DXMatrixRotationY(&mtxRotation, -g_rotationspeed);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxRotation);
	}
	}
	else
	{
	if (fabs(rotate) < g_rotationspeed)
	{
	D3DXMatrixRotationY(&mtxRotation, rotate);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxRotation);
	}
	else
	{
	D3DXMatrixRotationY(&mtxRotation, g_rotationspeed);
	D3DXVec3TransformNormal(&vecfront, &vecfront, &mtxRotation);
	}
	}
	*/

	Rot_Now *= 0.8f;
	g_moveSpeed = g_moveSpeed * 0.99f;

	vecDir = vecfront;
	D3DXVec3Normalize(&vecDir, &vecDir);
	Position += vecDir * g_moveSpeed;
	count++;
	/*
	if (Keyboard_IsPress(DIK_W)) {
		g_pos.z += g_speed;
	}
	if (Keyboard_IsPress(DIK_D)) {
		g_pos.x += g_speed;
	}
	if (Keyboard_IsPress(DIK_A)) {
		g_pos.x -= g_speed;
	}
	for (int i = 0; i < BROCK_NUM; i++)
	{

		if (ColiTriger(&g_coliBrock[i]))//�g���K�[
		{
			g_acceralation = 0.0f;
			g_speed = -g_speed;
			frame = 0;

		}
		if (ColiRelease(&g_coliBrock[i]))//�����[�X
		{

		}
	}

	if (frame >= 0)
	{

		if (frame>30)
		{
			g_speed *= -1;
			frame = -1;

		}
		else
		{

			frame++;

		}

	}
	*/
	for (int i = 0; i < PLAYER_COLI_NUM; i++)
	{
		switch (i)
		{
		case PLAYER_COLI_BROCKS:
			for (int j = 0; j < BROCK_NUM; j++)
			{
				g_coliBrock[j].past = g_coliBrock[j].now;
				g_coliBrock[j].now = false;
			}
			break;
		case PLAYER_COLI_NUM:
			break;
		default:
			break;
		}
	}
}



//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Player_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxW,mtxT,mtxR;
	/*
	D3DXMatrixIdentity(&mtxW);

	pDevice->SetTransform(D3DTS_WORLD, &mtxW);

	Model_Draw(tex);

	D3DXMatrixTranslation(&mtxT, 1.0f, 0.0f, 0.0f);
	mtxW = mtxT;
	pDevice->SetTransform(D3DTS_WORLD, &mtxW);
	Model_Draw(tex2);
	*/
	/*
	x += GetAxisX(0) * 0.0003f / 2; //  X�̂ق����ǂ����H
	x += GetAxisX(1) * 0.0003f / 2;
	x += GetAxisX(2) * 0.0003f / 2;
	x += GetAxisX(3) * 0.0003f / 2;

	// Ljoy�̒l���͈͈ȓ��@���@RJoy�̒l���͈͈ȏ�Ȃ�@�E�ɋȂ���

	//  �p�h���̎d�l�Ɉˑ�����@�l�͓K���@���E�l���`�F�b�N����
	if (GetAxisX(0) * 0.0005f < 0.01f && GetAxisX(1) * 0.0005f > 0.1f) {
		y += GetAxisX(1) * 0.0003f;
	}
	if (GetAxisX(1) * 0.0005f < 0.01f && GetAxisX(0) * 0.0005f > 0.1f) {
		y -= GetAxisX(0) * 0.0003f;
	}

	if (GetAxisX(2) * 0.0005f < 0.01f && GetAxisX(3) * 0.0005f > 0.1f) {
		y += GetAxisX(3) * 0.0003f;
	}
	if (GetAxisX(3) * 0.0005f < 0.01f && GetAxisX(2) * 0.0005f > 0.1f) {
		y -= GetAxisX(2) * 0.0003f;
	}
	*/



	//x += GetlRz(1) * 0.0005f;
	//y += GetlX(0) * 0.0005f;
	//y += GetAxisX(0) * 0.0005f;
	//x += GetAxisY(0) * 0.0005f;

	//DebugFont_Draw(100, 100, "%d",x);
	/*
	D3DXMatrixIdentity(&mtxW);


	D3DXMatrixTranslation(&mtxT, g_pos.x, g_pos.y, g_pos.z);

	D3DXMatrixRotationY(&mtxR,D3DX_PI);

	mtxW = mtxR * mtxT;
	pDevice->SetTransform(D3DTS_WORLD, &mtxW);

	*/
	D3DXMATRIX mtxWorld, mtxTranslation;   //int a ���ď������̂Ɠ����B���ɂ͂܂��S�~�������Ă�Bfloat��16�����Ă�悤�Ȃ���
	D3DXMatrixIdentity(&mtxWorld);  //�P�ʍs�� a = 1 �Ɠ����悤�Ȃ���
	D3DXMatrixTranslation(&mtxTranslation, Position.x, Position.y, Position.z);
	mtxWorld = mtxTranslation;
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	Model_Draw(tex);

}

float Get_Player_Pos_Z(void) {
	return Position.z;
}

D3DXVECTOR3* PlayerGetPos(void)
{
	return &Position;
}

float* PlayerGetColiLenth(void)
{
	return &g_coliLenth;
}

void PlayerSetColiFlag(PLAYER_COLI e, bool set, int ID)
{
	switch (e)
	{
	case PLAYER_COLI_BROCKS:

		g_coliBrock[ID].now = set;
		break;
	case PLAYER_COLI_NUM:
		break;
	default:
		break;
	}
}
