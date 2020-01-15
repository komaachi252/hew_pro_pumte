#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_
#include<d3dx9.h>
#include"line.h"
#include"input.h"
//#include"debugPrintf.h"
float Vec3Lenth(D3DXVECTOR3 vec);
float Vec2Lenth(D3DXVECTOR2 vec);
bool FieldInFlag(D3DXVECTOR3 pos);
void JudgementInit(void);
void JudgementUpdate(void);
void DebugLineSet(D3DXVECTOR3 pos, float lenth);

class Sphere
{
public:
	D3DXVECTOR3 pos;
	float lenth;
	D3DXMATRIX mtxT,*mtxW;
	Sphere(float setLenth, D3DXVECTOR3 setPos, D3DXMATRIX *setMtxW)
	{
		pos = setPos;
		lenth = setLenth;
		mtxW = setMtxW;
		D3DXMatrixTranslation(&mtxT, setPos.x, setPos.y, setPos.z);

	};

	~Sphere()
	{

	}
};
class Spheres
{
public:

	Spheres *next;
	Sphere *me;
	
	Spheres(Sphere* fast)
	{
		me = fast;
		next = nullptr;
	};
	~Spheres()
	{
	};
	void AddSphare(Sphere* add)
	{
		if (next==nullptr)
		{
			next = new Spheres(add);
			next->next = nullptr;
			return;
		}
		else
		{
			next->AddSphare(add);
			return;
		}
	}
	
	//母体のワールド行列
	void Update()
	{


		//当たり判定のローカル座標＊プレイヤーのワールド変換
		D3DXMATRIX mtx = me->mtxT * (*me->mtxW);
		D3DXVECTOR3 upPosA(mtx._41, mtx._42, mtx._43);

		DebugLineSet(upPosA,me->lenth);

		
		if (next == nullptr)
		{
			return;
		}
		else
		{

			next->Update();
			return;
		}
	}
	void Delete()
	{
		if (next == nullptr)
		{
			delete this;
			return;
		}
		else
		{
			next->Delete();
			delete this;
			return;
		}
	}
	
private:

};
class Forcus
{
public:
	bool now;
	bool past;

	Forcus();
	~Forcus();

private:

};

class ForcusSphereIsSphere
{
public:
	Forcus forcus;
	Sphere *A, *B;
	
	void Update();
	ForcusSphereIsSphere(Sphere *a, Sphere *b);
	~ForcusSphereIsSphere();

private:

};

class ForcusSpheresIsSphere
{
public:
	Forcus forcus;
	Spheres *A;
	Sphere *B;

	void Update();
	ForcusSpheresIsSphere(Spheres *a, Sphere *b);
	~ForcusSpheresIsSphere();
private:

};
class ForcusSpheresIsSpheres
{
public:
	Forcus focus;
	Spheres *A;
	Spheres *B;

	void Update();
	ForcusSpheresIsSpheres(Spheres *a, Spheres *b);
	~ForcusSpheresIsSpheres();

};


#endif // !JUDGEMENT_H_