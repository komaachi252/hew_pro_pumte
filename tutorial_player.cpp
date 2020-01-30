#define _CRT_SECURE_NO_WARNINGS
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
#include"model.h"
#include"debug_font.h"
#include"rock.h"
#include"Input2.h"
#include "map.h"
#include "MapArea.h"
#include "collision_draw.h"
#include "tutorial_player.h"
#include "TutoMapArea.h"
#include "Tuto_rock.h"
#include "tutocamera.h"
#include "data.h"
#include "model_tree.h"
#include "sound.h"

static TPlayer* g_player;
//	まるで装甲車
static Model_Tree g_play2[3] = {};
static Model_Tree g_armored_vehicle[5] = {};
static bool is_p = false;
static int frame = 0;
TPlayer::~TPlayer()
{
	coliSpheres->Delete();
	
	if (m_mode == PLAY_MODE::MODE_2) {
		Model_Tree_Destroy(g_play2, 3);
	}
	else {
		Model_Tree_Destroy(g_armored_vehicle, 5);
	}
	delete[] m_is_frame;
	delete[] m_is_used;
}

void TPlayer::Init(void)
{
	m_mode = Get_Mode();

	if (m_mode == PLAY_MODE::MODE_2) {
		m_is_used = new bool[2];
		for (int i = 0; i < 2; i++) {
			m_is_used[i] = false;
		}

		m_is_frame = new int[2];
		for (int i = 0; i < 2; i++) {
			m_is_frame[i] = 0;
		}
		g_play2[0].name = "wide2.x";
		D3DXMATRIX mtx;
		D3DXMatrixIdentity(&mtx);
		g_play2[0].mtx = mtx;
		g_play2[0].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[0].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[0].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[0].child_index = 1;
		g_play2[0].sibling_index = -1;
		g_play2[0].model_id = -1;

		g_play2[1].name = "tete.x";
		g_play2[1].mtx = mtx;
		g_play2[1].offset = D3DXVECTOR3(-0.5f, 0.88f, 0.4f);
		g_play2[1].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[1].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_play2[1].child_index = -1;
		g_play2[1].sibling_index = 2;
		g_play2[1].model_id = -1;

		g_play2[2].name = "tete2.x";
		g_play2[2].mtx = mtx;
		g_play2[2].offset = D3DXVECTOR3(0.5f, 0.88f, 0.4f);
		g_play2[2].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[2].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_play2[2].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_play2[2].child_index = -1;
		g_play2[2].sibling_index = -1;
		g_play2[2].model_id = -1;

		Model_Tree_Init(g_play2, 3);
	}
	else {
		m_is_used = new bool[4];
		for (int i = 0; i < 4; i++) {
			m_is_used[i] = false;
		}

		m_is_frame = new int[4];
		for (int i = 0; i < 4; i++) {
			m_is_frame[i] = 0;
		}

		g_armored_vehicle[0].name = "wide4.x";
		D3DXMATRIX mtx;
		D3DXMatrixIdentity(&mtx);
		g_armored_vehicle[0].mtx = mtx;
		g_armored_vehicle[0].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[0].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[0].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[0].child_index = 1;
		g_armored_vehicle[0].sibling_index = -1;
		g_armored_vehicle[0].model_id = -1;

		g_armored_vehicle[1].name = "tete.x";
		g_armored_vehicle[1].mtx = mtx;
		g_armored_vehicle[1].offset = D3DXVECTOR3(-0.5f, 0.78f, 0.5f);
		g_armored_vehicle[1].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[1].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[1].child_index = -1;
		g_armored_vehicle[1].sibling_index = 2;
		g_armored_vehicle[1].model_id = -1;

		g_armored_vehicle[2].name = "tete2.x";
		g_armored_vehicle[2].mtx = mtx;
		g_armored_vehicle[2].offset = D3DXVECTOR3(0.5f, 0.78f, 0.5f);
		g_armored_vehicle[2].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[2].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[2].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[2].child_index = -1;
		g_armored_vehicle[2].sibling_index = 3;
		g_armored_vehicle[2].model_id = -1;

		g_armored_vehicle[3].name = "tete3.x";
		g_armored_vehicle[3].mtx = mtx;
		g_armored_vehicle[3].offset = D3DXVECTOR3(-0.5f, 0.78f, -0.5f);
		g_armored_vehicle[3].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[3].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[3].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[3].child_index = -1;
		g_armored_vehicle[3].sibling_index = 4;
		g_armored_vehicle[3].model_id = -1;

		g_armored_vehicle[4].name = "tete4.x";
		g_armored_vehicle[4].mtx = mtx;
		g_armored_vehicle[4].offset = D3DXVECTOR3(0.5f, 0.78f, -0.5f);
		g_armored_vehicle[4].initrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[4].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_armored_vehicle[4].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[4].child_index = -1;
		g_armored_vehicle[4].sibling_index = -1;
		g_armored_vehicle[4].model_id = -1;

		Model_Tree_Init(g_armored_vehicle, 5);

	}
	//モデル系//////////////////////////
	/*
	if (m_mode == MODE_2) {
		modelId = Model_Load("ft.x");
	}
	else {
		modelId = Model_Load("wideboat.x");
	}
	*/
	/*
	modelId = SetLordModel("MyAccet\\model\\boat\\ft.x");
	ModelLord(modelId, "boat\\");
	*/
	////////////////////////////////////_

	//座標系////////////////////////////
	pos = D3DXVECTOR3(0.0f, 0.3f, 0.0f);
	pastPos = pos;
	speedMax = 0.2f;
	rotSpeed = D3DXToRadian(0.85f);
	rotAcceralation = 0.0f;

	scale = 0.4f;

	vecFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//座標系////////////////////////////_

	//行列
	D3DXMATRIX mtxScal, mtxTranslation, mtxRotationY, mtxRotationX;
	//スケーリング
	D3DXMatrixScaling(&mtxScal, scale, scale, scale);
	//トランスレーション
	D3DXMatrixTranslation(&mtxTranslation, pos.x, pos.y, pos.z);
	//ローテーション
	AngleUpdate();
	D3DXMatrixRotationY(&mtxRotationY, angleY);
	D3DXMatrixRotationAxis(&mtxRotationX, &vecRight, -angleX);
	//スケーリング＊ローテーション＊トランスレーション
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;



	//当たり判定系//////////////////////

	coliSpheres = new Spheres(new Sphere(0.3, D3DXVECTOR3(-0.5f, 0.0f, 0.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.5f, 0.0f, 0.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, 2.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, 3.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, -2.0f), &mtxWorld));
	coliSpheres->AddSphare(new Sphere(0.3, D3DXVECTOR3(0.0f, 0.0f, -3.0f), &mtxWorld));
	//Spheres *r = RocksGetColi();
	//Spheres *M = MapAreasGetColi();


	IsRock = new ForcusSpheresIsSpheres(coliSpheres, TutoRocksGetColi());
	IsMapArea = new ForcusSpheresIsSpheres(coliSpheres, TutoMapAreasGetColi());

	//当たり判定系//////////////////////_		
}
void TPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	Device->SetFVF(FVF_PLAYER);
	Device->SetTexture(0, NULL);
	//Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	////アルファテスト（ブレンドとは違う）//終わったらオフにする
	//g_sampleDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	////なんか
	//g_sampleDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	////基準値の設定　0-255
	//g_sampleDevice->SetRenderState(D3DRS_ALPHAREF, 200);
	//
	//g_sampleDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_sampleDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	D3DXVECTOR3 colli[8];
	colli[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	colli[1] = D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	colli[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	colli[3] = D3DXVECTOR3(0.0f, 0.0f, 2.0f);
	colli[4] = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	colli[5] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	colli[6] = D3DXVECTOR3(0.0f, 0.0f, -2.0f);
	colli[7] = D3DXVECTOR3(0.0f, 0.0f, -3.0f);

	D3DXVECTOR3 pos(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	for (int i = 0; i < 8; i++) {
		D3DXVec3TransformNormal(&colli[i], &colli[i], &mtxWorld);
		colli[i] += pos;
	}
	float rad = 0.3f;

	//Model_Draw(modelId, mtxWorld);

	if (m_mode == PLAY_MODE::MODE_2) {
		Model_Tree_Draw(g_play2, &mtxWorld);
	}
	else {
		Model_Tree_Draw(g_armored_vehicle, &mtxWorld);
	}
	//DebugFont_Draw(10, 400, "x:%3.3f y:%3.3f z:%3.3f, ", mtxWorld._41, mtxWorld._42, mtxWorld._43);
	DebugFont_Draw(10, 400, "frame:%d, ", frame);
	DebugFont_Draw(10, 500, "arm1:%3.3f arm2:%3.3farm1:%3.3f  ", g_play2[1].rotation.x, g_play2[1].rotation.y, g_play2[1].rotation.z);
	//if (IsMapArea->focus.now && !IsMapArea->focus.past) {
		//DebugFont_Draw(10, 440, "Areanoe:%d,Areapast:%d, ", IsMapArea->focus.now, IsMapArea->focus.past);
	//}
	/*
	for (int i = 0; i < 8; i++) {
		//Sphere_Draw(GetDevice(), colli[i], rad, D3DCOLOR_RGBA(0, 255, 0, 255));
	}
	*/

};
void TPlayer::Uninit(void)
{

};
void TPlayer::Update(void)
{
	/*
	if (frame <= 31) {
		anglef = 0.2f;
		D3DXMATRIX mtx_rot;
		D3DXMatrixRotationY(&mtx_rot, anglef);
		D3DXVec3TransformNormal(&g_armored_vehicle[1].rotation, &g_armored_vehicle[1].rotation, &mtx_rot);
		D3DXVec3TransformNormal(&g_armored_vehicle[3].rotation, &g_armored_vehicle[3].rotation, &mtx_rot);
		D3DXMatrixRotationY(&mtx_rot, -anglef);
		D3DXVec3TransformNormal(&g_armored_vehicle[2].rotation, &g_armored_vehicle[2].rotation, &mtx_rot);
		D3DXVec3TransformNormal(&g_armored_vehicle[4].rotation, &g_armored_vehicle[4].rotation, &mtx_rot);
		frame++;
	}
	if (frame >= 31) {
		g_armored_vehicle[1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[2].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[3].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[4].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		frame = 0;
	}
	*/
	camera *cam = TutoCameraGet();


	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_mode == PLAY_MODE::MODE_2) {
		if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > 1200)
		{
			if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//右のほうが強いなら
			{
				if (!m_is_used[0]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += cam->vec_right;
				Row(0);
			}
		}
		if (GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true) > 1200)
		{
			if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) < GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//左のほうが強いなら
			{
				if (!m_is_used[1]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += -cam->vec_right;
				Row(1);
			}
		}
	}
	else {
		if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > 1200)
		{
			if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) > GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//右のほうが強いなら
			{
				if (!m_is_used[0]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += cam->vec_right * 0.5f;
				Row(0);
			}
		}
		if (GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true) > 1200)
		{
			if (GetAxisX(0, true) + GetAxisY(0, true) + GetAxisZ(0, true) < GetAxisX(1, true) + GetAxisY(1, true) + GetAxisZ(1, true))//左のほうが強いなら
			{
				if (!m_is_used[1]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += -cam->vec_right* 0.5f;
				Row(1);
			}
		}
		if (GetAxisX(2, true) + GetAxisY(2, true) + GetAxisZ(2, true) > 1200)
		{
			if (GetAxisX(2, true) + GetAxisY(2, true) + GetAxisZ(2, true) > GetAxisX(3, true) + GetAxisY(3, true) + GetAxisZ(3, true))//右のほうが強いなら
			{
				if (!m_is_used[2]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += cam->vec_right* 0.5f;
				Row(2);
			}
		}
		if (GetAxisX(3, true) + GetAxisY(3, true) + GetAxisZ(3, true) > 1200)
		{
			if (GetAxisX(2, true) + GetAxisY(2, true) + GetAxisZ(2, true) < GetAxisX(3, true) + GetAxisY(3, true) + GetAxisZ(3, true))//左のほうが強いなら
			{
				if (!m_is_used[3]) {
					PlaySound(SOUND_LABEL_SE_SPLASH);
				}
				vecDir += -cam->vec_right* 0.5f;
				Row(3);
			}
		}

	}



	if (Keyboard_IsPress(DIK_UPARROW))
	{
		vecDir += cam->vec_flont;
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_RIGHTARROW))
	{
		if (!m_is_used[1]) {
			PlaySound(SOUND_LABEL_SE_SPLASH);
		}
		vecDir += cam->vec_right;
		Row(1);
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_LEFTARROW))
	{
		if (!m_is_used[0]) {
			PlaySound(SOUND_LABEL_SE_SPLASH);
		}
		vecDir += -cam->vec_right;
		Row(0);
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_DOWNARROW))
	{

		vecDir += -cam->vec_flont;
		acceralation += 0.01f;
	}
	if (Keyboard_IsPress(DIK_W))
	{
		//pos.y += 0.075f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		//pos.y += -0.075f;
	}

	if (vecDir != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		//acceralation = 0.1f;
		acceralation += 0.001f;

		//正規化
		D3DXVec3Normalize(&vecFront, &vecFront);
		D3DXVec3Normalize(&vecDir, &vecDir);

		//カメラの前ベクトルとプレイヤーの前ベクトルの外積
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

		//右回り
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
		//左回り
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
		//平行
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


	//移動処理
	D3DXVECTOR3 vecmove;
	Spheres* now = coliSpheres;
	
	if (((IsRock->focus.now == true) && (IsRock->focus.past == false)) || ((IsMapArea->focus.now == true) && (IsMapArea->focus.past == false))) {
		if (acceralation>0)
		{
			acceralation *= -2;
		}
		else
		{
			acceralation *= 2;
		}
		speed *= -2.0f;
		PlaySound(SOUND_LABEL_SE_HIT1);
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

			vecpos = now->me->pos;///////////////////////////////////////////////////////////////////////////////////////////////////////
			D3DXVec3TransformNormal(&vecpos, &vecpos, &mtxRot);
			vecmove = pos + vecpos + (vecFront*(speed + now->me->lenth));
			//if (FieldInFlag(vecmove) == true)
			//{

			if (now->next == nullptr)
			{
				float angleB = 1.0f + (-1.0f*(angleX / D3DXToRadian(90)));

				pos += vecFront * speed * angleB;
				endFlag = true;
			}
			else
			{

				now = now->next;
			}


		}
	}

	//減速
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

	//行列
	D3DXMATRIX mtxScal, mtxTranslation, mtxRotationY, mtxRotationX;


	//スケーリング
	D3DXMatrixScaling(&mtxScal, scale, scale, scale);

	//トランスレーション
	D3DXMatrixTranslation(&mtxTranslation, pos.x, pos.y, pos.z);

	//ローテーション

	AngleUpdate();

	D3DXMatrixRotationY(&mtxRotationY, angleY);
	D3DXMatrixRotationAxis(&mtxRotationX, &vecRight, -angleX);

	//スケーリング＊ローテーション＊トランスレーション
	mtxWorld = mtxScal * mtxRotationY *mtxRotationX* mtxTranslation;

	coliSpheres->Update();

	pastPos = pos;

	/*
	if (frame <= 31) {
		anglef = 0.2f;
		D3DXMATRIX mtx_rot;
		D3DXMatrixRotationY(&mtx_rot, anglef);
		D3DXVec3TransformNormal(&g_armored_vehicle[1].rotation, &g_armored_vehicle[1].rotation, &mtx_rot);
		D3DXVec3TransformNormal(&g_armored_vehicle[3].rotation, &g_armored_vehicle[3].rotation, &mtx_rot);
		D3DXMatrixRotationY(&mtx_rot, -anglef);
		D3DXVec3TransformNormal(&g_armored_vehicle[2].rotation, &g_armored_vehicle[2].rotation, &mtx_rot);
		D3DXVec3TransformNormal(&g_armored_vehicle[4].rotation, &g_armored_vehicle[4].rotation, &mtx_rot);
		frame++;
	}
	if (frame >= 31) {
		g_armored_vehicle[1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[2].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[3].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_armored_vehicle[4].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		frame = 0;
	}
	*/
	D3DXMATRIX mtx_rot, mtx_rot_inv;
	float angle = 0.2f;
	D3DXMatrixRotationY(&mtx_rot, angle);
	D3DXMatrixRotationY(&mtx_rot_inv, -angle);

	//	入力状態の更新
	if (m_mode == PLAY_MODE::MODE_2) {
		for (int i = 0; i < 2; i++) {
			if (m_is_used[i]) {
				switch (i)
				{
				case 0:
					D3DXVec3TransformNormal(&g_play2[1].rotation, &g_play2[1].rotation, &mtx_rot);
					break;
				case 1:
					D3DXVec3TransformNormal(&g_play2[2].rotation, &g_play2[2].rotation, &mtx_rot_inv);
					break;
				default:
					break;
				}
				m_is_frame[i]++;
				if (m_is_frame[i] >= 31) {
					m_is_used[i] = false;
					m_is_frame[i] = 0;
					g_play2[i + 1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				}
			}
		}
	}else {
		for (int i = 0; i < 4; i++) {
			if (m_is_used[i]) {
				switch (i)
				{
				case 0:
					D3DXVec3TransformNormal(&g_armored_vehicle[1].rotation, &g_armored_vehicle[1].rotation, &mtx_rot);
					break;
				case 1:
					D3DXVec3TransformNormal(&g_armored_vehicle[2].rotation, &g_armored_vehicle[2].rotation, &mtx_rot_inv);
					break;
				case 2:
					D3DXVec3TransformNormal(&g_armored_vehicle[3].rotation, &g_armored_vehicle[3].rotation, &mtx_rot);
					break;
				case 3:
					D3DXVec3TransformNormal(&g_armored_vehicle[4].rotation, &g_armored_vehicle[4].rotation, &mtx_rot_inv);
					break;
				default:
					break;
				}
				m_is_frame[i]++;
				if (m_is_frame[i] >= 31) {
					m_is_used[i] = false;
					g_armored_vehicle[i + 1].rotation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				}
			}
		}
	}
}

void TPlayer::AngleUpdate()
{
	D3DXVECTOR3 distance = pastPos - pos;
	
	float distAngleX = -atan2(distance.y, Vec2Lenth(D3DXVECTOR2(distance.x, distance.z)));
	float distAngleY = atan2(vecFront.x, vecFront.z);
	if (speed>0)
	{
		if (distAngleX - angleX  > D3DXToRadian(1.5f))
		{
			angleX += D3DXToRadian(1.5f);
		}
		else if (angleX - distAngleX > D3DXToRadian(1.5f))
		{
			angleX -= D3DXToRadian(1.5f);
		}
		else
		{
			angleX = distAngleX;
		}
	}
	else
	{

	}
	angleY = distAngleY;
};


void TutoPlayerInit(void)
{
	g_player = new TPlayer();
	g_player->Init();
}

void TutoPlayerDraw(void)
{
	if (g_player == nullptr) {
		return;
	}
	g_player->Draw();
	
}

void TutoPlayerUninit(void)
{
	delete g_player;
	g_player = nullptr;
}

void TutoPlayerUpdate(void)
{
	if (g_player == nullptr) {
		return;
	}
	g_player->Update();
}
TPlayer* TutoPlayerGet()
{
	return g_player;
}

void TPlayer::Set_Mode(PLAY_MODE mode)
{
	m_mode = mode;
}

void Set_TPlayer_Mode(PLAY_MODE mode)
{
	g_player->Set_Mode(mode);
}

void TPlayer::Row(int index)
{
	if (!m_is_used[index]) {
		m_is_used[index] = true;
		m_is_frame[index] = 0;
	}
}