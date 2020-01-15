#include"player.h"
#include"Judgement.h"
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"grid.h"
#include<math.h>
#include"input.h"
#include"line.h"
#include"player.h"
#include"model.h"
//#include"Bullet.h"
//#include"shadow.h"
//\#include"debugPrintf.h"
#include"debug_font.h"
#include"rock.h"
#include"Input2.h"
Player::~Player()
{
	coliSpheres->Delete();
}

void Player::Init(void)
{
	//���f���n//////////////////////////
	modelId = Model_Load("ft.x");
	/*
	modelId = SetLordModel("MyAccet\\model\\boat\\ft.x");
	ModelLord(modelId, "boat\\");
	*/
	////////////////////////////////////_

	//���W�n////////////////////////////
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speedMax = 0.1f;
	rotSpeed = D3DXToRadian(0.85f);
	rotAcceralation = 0.0f;

	scale = 1.0;

	vecFront = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	//�O�����x�N�g�����O�̒l�̃x�N�g�������̒P�ʃx�N�g���A���񂩂���X����
	vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//�O�����x�N�g���𐳋K��
	D3DXVec3Normalize(&vecFront, &vecFront);
	//�O�ςŏ�x�N�g��
	D3DXVec3Cross(&vecUp, &vecFront, &vecRight);
	D3DXVec3Normalize(&vecUp, &vecUp);

	D3DXMATRIX mtxRot;

	D3DXMatrixRotationAxis(&mtxRot, &vecRight, D3DXToRadian(45));
	D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxRot);
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRot);
	vecFront.y = 0.0f;
	vecRight.y = 0.0f;
	D3DXVec3Normalize(&vecFront, &vecFront);
	D3DXVec3Normalize(&vecRight, &vecRight);


	angleY = atan2(vecFront.z, vecFront.x);

	D3DXMatrixRotationY(&mtxRot, angleY + D3DXToRadian(-90));
	D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxRot);
	D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRot);
	D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxRot);

	AngleUpdate();

	//���W�n////////////////////////////_

	//�s��
	D3DXMATRIX mtxScal, mtxTranslation, mtxRotationY, mtxRotationX;
	//�X�P�[�����O
	D3DXMatrixScaling(&mtxScal, scale, scale, scale);
	//�g�����X���[�V����
	D3DXMatrixTranslation(&mtxTranslation, pos.x, pos.y, pos.z);
	//���[�e�[�V����
	AngleUpdate();
	D3DXMatrixRotationY(&mtxRotationY, angleY);
	D3DXMatrixRotationAxis(&mtxRotationX, &vecRight, -angleX);
	//�X�P�[�����O�����[�e�[�V�������g�����X���[�V����
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;



	//�����蔻��n//////////////////////

	coliSpheres = new Spheres(new Sphere(0.5, D3DXVECTOR3(-0.5f, 0.0f, 0.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.5f, 0.0f, 0.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, 2.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, 3.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, -2.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.5, D3DXVECTOR3(0.0f, 0.0f, -3.0f), &mtxWorld));
	IsRock = new ForcusSpheresIsSpheres(coliSpheres, RocksGetColi());

	//�����蔻��n//////////////////////_		



};
void Player::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	Device->SetFVF(FVF_PLAYER);
	Device->SetTexture(0, NULL);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	////�A���t�@�e�X�g�i�u�����h�Ƃ͈Ⴄ�j//�I�������I�t�ɂ���
	//g_sampleDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	////�Ȃ�
	//g_sampleDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	////��l�̐ݒ�@0-255
	//g_sampleDevice->SetRenderState(D3DRS_ALPHAREF, 200);
	//
	//g_sampleDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_sampleDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);




	//ModelDraw(modelId, mtxWorld);

	Model_Draw(modelId, mtxWorld);
};
void Player::Uninit(void)
{

};
void Player::Update(void)
{



	camera *cam = CameraGet();


	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > 1200)
	{
		if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//�E�̂ق��������Ȃ�
		{
			vecDir += cam->vec_right;

	
		}
	}
	if (GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true) > 1200)
	{
		if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) < GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//���̂ق��������Ȃ�
		{
			vecDir += -cam->vec_right;
		}
	}
	
	

	if (Keyboard_IsPress(DIK_UPARROW))
	{
		vecDir += cam->vec_flont;
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_RIGHTARROW))
	{
		vecDir += cam->vec_right;
	
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_LEFTARROW))
	{
		vecDir += -cam->vec_right;
	
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_DOWNARROW))
	{
	
		vecDir += -cam->vec_flont;
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_W))
	{
		pos.y += 0.075f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		pos.y += -0.075f;
	}

	if (vecDir != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		acceralation += 0.01f;

		//���K��
		D3DXVec3Normalize(&vecFront, &vecFront);
		D3DXVec3Normalize(&vecDir, &vecDir);

		//�J�����̑O�x�N�g���ƃv���C���[�̑O�x�N�g���̊O��
		D3DXVECTOR3 outCloss = D3DXVECTOR3(
			(vecDir.y*vecFront.z) - (vecDir.z*vecFront.y),
			(vecDir.z*vecFront.x) - (vecDir.x*vecFront.z),
			(vecDir.x*vecFront.y) - (vecDir.y*vecFront.x));

		D3DXVECTOR2 dir(vecDir.x, vecDir.z);
		D3DXVECTOR2 vec2(vecFront.x, vecFront.z);

		D3DXVec2Normalize(&dir, &dir);
		D3DXVec2Normalize(&vec2, &vec2);

		float inCloss = (dir.x*vec2.x) + (dir.y*vec2.y);
		float angleCisP = acosf(inCloss);

		//�E���
		if (outCloss.y < 0.0f)
		{

			if (angleCisP > rotSpeed)
			{
				D3DXMATRIX mtxRot;

				D3DXMatrixRotationY(&mtxRot, rotSpeed);
				D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxRot);
				D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRot);
				D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxRot);

			}
		}
		//�����
		else if (outCloss.y > 0.0f)
		{

			if (angleCisP > rotSpeed)
			{
				D3DXMATRIX mtxRot;
				D3DXMatrixRotationY(&mtxRot, -rotSpeed);
				D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxRot);
				D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRot);
				D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxRot);

			}
		}
		//���s
		else if (outCloss.y == 0.0f)
		{
			if (inCloss < 0)
			{

				D3DXMATRIX mtxRot;
				D3DXMatrixRotationY(&mtxRot, rotSpeed);
				D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxRot);
				D3DXVec3TransformNormal(&vecRight, &vecRight, &mtxRot);
				D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxRot);
			}
		}
	}


	//�ړ�����
	D3DXVECTOR3 vecmove;
	Spheres* now = coliSpheres;

	if (IsRock->focus.now == true)
	{

		if (IsRock->focus.past == false)
		{
			//�������Ă���Ȃ�
			acceralation *= -0.5f;
			speed *= -1;
		}
	}

	D3DXMATRIX mtxRot;
	D3DXMatrixRotationY(&mtxRot, angleY);
	D3DXVECTOR3 vecpos;
	bool endFlag;
	if (Keyboard_IsPress(DIK_SPACE) == FALSE)
	{
		now = coliSpheres;
		endFlag = false;

		while (endFlag == false)
		{

			vecpos = now->me->pos;
			D3DXVec3TransformNormal(&vecpos, &vecpos, &mtxRot);
			vecmove = pos + vecpos + (vecFront*(speed + now->me->lenth));
			//if (FieldInFlag(vecmove) == true)
			//{


			if (now->next == nullptr)
			{
				pos += vecFront * speed;
				endFlag = true;
			}
			else
			{

				now = now->next;
			}
			//}
			//else
			//{
			//
			//	speed *= 0.5f;
			//	acceralation *= 0.5f;
			//	endFlag = true;
			//
			//}

		}
	}

	//����
	acceralation *= 0.9f;
	speed *= 0.9f;

	speed += acceralation;
	if (speed > speedMax)
	{
		speed = speedMax;
	}
	if (speed < -speedMax)
	{
		speed = -speedMax;
	}


	//�s��
	D3DXMATRIX mtxScal, mtxTranslation, mtxRotationY, mtxRotationX;


	//�X�P�[�����O
	D3DXMatrixScaling(&mtxScal, scale, scale, scale);

	//�g�����X���[�V����
	D3DXMatrixTranslation(&mtxTranslation, pos.x, pos.y, pos.z);

	//���[�e�[�V����

	AngleUpdate();


	D3DXMatrixRotationY(&mtxRotationY, angleY);
	D3DXMatrixRotationAxis(&mtxRotationX, &vecRight, -angleX);

	//�X�P�[�����O�����[�e�[�V�������g�����X���[�V����
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;
	coliSpheres->Update();

};
void Player::AngleUpdate()
{
	if (vecUp.y > 0)
	{
		angleX = atan2(vecFront.y, Vec2Lenth(-D3DXVECTOR2(vecFront.x, vecFront.z)));
	}
	else
	{

		angleX = atan2(vecFront.y, -Vec2Lenth(-D3DXVECTOR2(vecFront.x, vecFront.z)));
	}
	angleY = atan2(vecFront.x, vecFront.z);
};

Player g_player;
void PlayerInit(void)
{
	g_player.Init();
}

void PlayerDraw(void)
{
	g_player.Draw();
	
}

void PlayerUninit(void)
{
	g_player.Uninit();
}

void PlayerUpdate(void)
{
	g_player.Update();
}
Player* PlayerGet()
{
	return &g_player;
}