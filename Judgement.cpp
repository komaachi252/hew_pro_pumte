#include<d3dx9.h>
#include"Judgement.h"
#include"player.h"
#include "flag.h"
static ForcusSpheresIsSpheres *g_coliPlayerIsRock;
static ForcusSpheresIsSpheres *g_coliPlayerIsMapArea;


float Vec3Lenth(D3DXVECTOR3 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

}
float Vec2Lenth(D3DXVECTOR2 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);

}

void JudgementInit(void)
{
	g_coliPlayerIsRock = PlayerGet()->IsRock;
	g_coliPlayerIsMapArea = PlayerGet()->IsMapArea;
}
void JudgementUpdate(void)
{
	g_coliPlayerIsRock->Update();
	g_coliPlayerIsMapArea->Update();
	FlagsGet()->ColiUpdate();
}
bool FieldInFlag(D3DXVECTOR3 pos)
{
	

	if (50< pos.x)
	{
		return false;
	}
	if (50< pos.z)
	{
		return false;
	}
	if (-50> pos.x)
	{
		return false;
	}
	if (-50 > pos.z)
	{
		return false;
	}

	return true;
}
void DebugLineSet(D3DXVECTOR3 pos, float lenth)
{
	//////////////////////////////////
	LineSet
	(
		D3DXVECTOR3(pos.x + lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y + lenth, pos.z)
	);

	LineSet
	(
		D3DXVECTOR3(pos.x - lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y + lenth, pos.z)
	);
	LineSet
	(
		D3DXVECTOR3(pos.x, pos.y, pos.z + lenth),
		D3DXVECTOR3(pos.x, pos.y + lenth, pos.z)
	);

	LineSet
	(
		D3DXVECTOR3(pos.x, pos.y, pos.z - lenth),
		D3DXVECTOR3(pos.x, pos.y + lenth, pos.z)
	);
	//////////////////////////////
	LineSet
	(
		D3DXVECTOR3(pos.x + lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y - lenth, pos.z)
	);

	LineSet
	(
		D3DXVECTOR3(pos.x - lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y - lenth, pos.z)
	);
	LineSet
	(
		D3DXVECTOR3(pos.x, pos.y, pos.z + lenth),
		D3DXVECTOR3(pos.x, pos.y - lenth, pos.z)
	);

	LineSet
	(
		D3DXVECTOR3(pos.x, pos.y, pos.z - lenth),
		D3DXVECTOR3(pos.x, pos.y - lenth, pos.z)
	);
	/////////////////////////////////////////
	LineSet
	(
		D3DXVECTOR3(pos.x + lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y, pos.z + lenth)
	);
	LineSet
	(
		D3DXVECTOR3(pos.x + lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y, pos.z - lenth)
	);
	LineSet
	(
		D3DXVECTOR3(pos.x - lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y, pos.z + lenth)
	);
	LineSet
	(
		D3DXVECTOR3(pos.x - lenth, pos.y, pos.z),
		D3DXVECTOR3(pos.x, pos.y, pos.z - lenth)
	);
	///////////////////////////////////////////////////////
}


//Forcusメンバー関数/////////////////////////////
Forcus::Forcus()

{
	now = false;
	past = false;
}
Forcus::~Forcus()
{

}
void ForcusSphereIsSphere::Update()
{
	forcus.past = forcus.now;

	D3DXMATRIX mtx = A->mtxT * (*A->mtxW);
	D3DXVECTOR3 upPosA(mtx._41, mtx._42, mtx._43);
	mtx = B->mtxT * (*B->mtxW);
	D3DXVECTOR3 upPosB(mtx._41, mtx._42, mtx._43);

	float lenge_lenth = Vec3Lenth(upPosA - upPosB);
	if (lenge_lenth <= A->lenth + B->lenth)
	{

		forcus.now = true;
		return;
	}

	forcus.now = false;
	return;
}
//Forcusメンバー関数/////////////////////////////

//ForcusSphereIsSphereメンバー関数/////////////////////////////
ForcusSphereIsSphere::ForcusSphereIsSphere(Sphere *a, Sphere *b)
{
	A = a;
	B = b;
}

ForcusSphereIsSphere::~ForcusSphereIsSphere()
{

}
//ForcusSphereIsSphereメンバー関数/////////////////////////////

//ForcusSpheresIsSphereメンバー関数/////////////////////////////

void ForcusSpheresIsSphere::Update()
{
	D3DXMATRIX mtx;
	D3DXVECTOR3 upPosA;
	mtx = B->mtxT * (*B->mtxW);
	D3DXVECTOR3 upPosB(mtx._41, mtx._42, mtx._43);
	float lenge_lenth;
	Spheres *now = A;
	bool end = false;
	forcus.past = forcus.now;
	while (end == false)
	{
		//ローカル座標行列＊ワールド空間行列
		mtx = now->me->mtxT * (*now->me->mtxW);
		upPosA = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

		//DebugLineSet(me->pos, me->lenth);
		//DebugLineSet(me->pos, me->lenth);

		LineSet(upPosA + D3DXVECTOR3(0.0f, 3.0f, 0.0f), upPosA);
		lenge_lenth = Vec3Lenth(upPosA - upPosB);
		if (lenge_lenth <= now->me->lenth + B->lenth)
		{
			//当たっているなら
			forcus.now = true;
			end = true;
		}
		else
		{
			if (now->next == nullptr)
			{
				//リストの最後なら
				forcus.now = false;
				end = true;
			}
			else
			{
				//リストの最後でないなら
				now = now->next;
			}
		}
	}
}
ForcusSpheresIsSphere::ForcusSpheresIsSphere(Spheres *a, Sphere *b)
{
	A = a;
	B = b;
}
ForcusSpheresIsSphere::~ForcusSpheresIsSphere()
{

}
//ForcusSpheresIsSphereメンバー関数/////////////////////////////
void ForcusSpheresIsSpheres::Update()
{
	D3DXMATRIX mtxA, mtxB;
	float lenge_lenth;
	Spheres *focusA = A;
	Spheres *focusB = B;
	bool updateA, updateB;//行列の更新をするかどうか

	D3DXVECTOR3 upPosA;
	D3DXVECTOR3 upPosB;

	bool end = false;
	updateA = true;
	updateB = true;


	focus.past = focus.now;
	focus.now = false;

	while (end == false)
	{


		if (updateA == true)
		{
			mtxA = focusA->me->mtxT * (*focusA->me->mtxW);
			upPosA = D3DXVECTOR3(mtxA._41, mtxA._42, mtxA._43);
		}
		//ローカル座標行列＊ワールド空間行列
		if (updateB == true)
		{
			mtxB = focusB->me->mtxT * (*focusB->me->mtxW);
			upPosB = D3DXVECTOR3(mtxB._41, mtxB._42, mtxB._43);
		}
		
		

		LineSet(upPosA + D3DXVECTOR3(0.0f, 3.0f, 0.0f), upPosA);
		lenge_lenth = Vec3Lenth(upPosA - upPosB);
		if (lenge_lenth <= focusA->me->lenth + focusB->me->lenth)
		{
			//当たっているとき
			focus.now = true;
			end = true;
		}
		else
		{
			//当っていないとき
			updateA = false;
			updateB = false;
			if (focusB->next == nullptr)
			{
				if (focusA->next == nullptr)
				{

					//リストの最後なら

					end = true;
				}
				else
				{
					//リストの最後でないなら
					focusA = focusA->next;
					focusB = B;
					updateA = true;
					updateB=true;
				}
			}
			else
			{
				//リストの最後でないなら
				focusB = focusB->next;
				updateB = true;
			}
		}
	}
}
void ForcusSpheresIsSpheres::Update(int b_num)
{
	int cnt = 0;
	D3DXMATRIX mtxA, mtxB;
	float lenge_lenth;
	Spheres *focusA = A;
	Spheres *focusB = B;
	bool updateA, updateB;//行列の更新をするかどうか

	D3DXVECTOR3 upPosA;
	D3DXVECTOR3 upPosB;

	bool end = false;
	updateA = true;
	updateB = true;


	focus.past = focus.now;
	focus.now = false;

	while (end == false)
	{
		if (cnt >= b_num) {
			return;
		}

		if (updateA == true)
		{
			mtxA = focusA->me->mtxT * (*focusA->me->mtxW);
			upPosA = D3DXVECTOR3(mtxA._41, mtxA._42, mtxA._43);
		}
		//ローカル座標行列＊ワールド空間行列
		if (updateB == true)
		{
			mtxB = focusB->me->mtxT * (*focusB->me->mtxW);
			upPosB = D3DXVECTOR3(mtxB._41, mtxB._42, mtxB._43);
		}



		LineSet(upPosA + D3DXVECTOR3(0.0f, 3.0f, 0.0f), upPosA);
		lenge_lenth = Vec3Lenth(upPosA - upPosB);
		if (lenge_lenth <= focusA->me->lenth + focusB->me->lenth)
		{
			//当たっているとき
			focus.now = true;
			end = true;
		}
		else
		{
			//当っていないとき
			updateA = false;
			updateB = false;
			if (focusB->next == nullptr)
			{
				if (focusA->next == nullptr)
				{

					//リストの最後なら

					end = true;
				}
				else
				{
					//リストの最後でないなら
					focusA = focusA->next;
					focusB = B;
					updateA = true;
					updateB = true;
				}
			}
			else
			{
				//リストの最後でないなら
				focusB = focusB->next;
				cnt++;
				updateB = true;
			}
		}
	}
}
ForcusSpheresIsSpheres::ForcusSpheresIsSpheres(Spheres *a, Spheres *b)
{

	A = a;
	B = b;
}
ForcusSpheresIsSpheres::~ForcusSpheresIsSpheres()
{

}