#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"model.h"
#include"texture.h"
#include"TutoFlag.h"
#include"tutorial_player.h"
#include"Judgement.h"
TutoFlag::TutoFlag(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos)
{
	angleX = set_angleX;
	angleY = set_angleY;
	scale = set_scale;
	pos = set_pos;
	D3DXMATRIX mtxRotX, mtxRotY, mtxS, mtxT;
	D3DXMatrixTranslation(&mtxT, pos.x, pos.y, pos.z);
	D3DXMatrixRotationX(&mtxRotX, angleX);
	D3DXMatrixRotationY(&mtxRotY, angleY);
	D3DXMatrixScaling(&mtxS, scale, scale, scale);
	mtx = mtxS * mtxRotX*mtxRotY*mtxT;
	coliSphere = new Sphere(0.5f*scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &mtx);
	coliflag = false;
	IsPlayer = new ForcusSpheresIsSphere(TutoPlayerGet()->coliSpheres, coliSphere);

}

TutoFlag::~TutoFlag()
{
}

void TutoFlag::Update()
{
	if (IsPlayer->forcus.now == true)
	{
		if (coliflag == false)
		{
			coliflag = true;
			TutoFlagAddScoer();
		}
	}
	D3DXMATRIX mtxRotX, mtxRotY, mtxS, mtxT;
	D3DXMatrixTranslation(&mtxT, pos.x, pos.y, pos.z);
	D3DXMatrixRotationX(&mtxRotX, angleX);
	D3DXMatrixRotationY(&mtxRotY, angleY);
	D3DXMatrixScaling(&mtxS, scale, scale, scale);
	mtx = mtxS * mtxRotX*mtxRotY*mtxT;




}

TutoFlags::TutoFlags(TutoFlag *setMe)
{
	me = setMe;

	next = nullptr;
}

TutoFlags::~TutoFlags()
{
}

TutoFlags* TutoFlags::AddFlag(TutoFlag *setFlag)
{

	if (next == nullptr)
	{
		next = new TutoFlags(setFlag);
		next->next = nullptr;
		return next;
	}
	else
	{
		return next->AddFlag(setFlag);
	}
}
void TutoFlags::Update(void)
{
	if (next == nullptr)
	{
		me->Update();

		return;
	}
	else
	{
		next->Update();
		me->Update();
		return;
	}

}
void TutoFlags::Delete(void)
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
void TutoFlags::ColiUpdate(void)
{
	TutoFlags *forcus = this;
	while (true)
	{
		forcus->me->IsPlayer->Update();
		if (forcus->next == nullptr)
		{
			return;
		}
		else
		{
			forcus = forcus->next;
		}


	}
}
static int g_coliNum;
static TutoFlags *g_flags;
static int g_modelId;
void TutoFlagInit()
{
	//1
	g_flags = new TutoFlags(new TutoFlag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(0.0f, 0.0f, 5.0f)));
	//2
	g_flags->AddFlag(new TutoFlag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(30.0f, 0.0f, 47.0f)));
	g_coliNum = 0;
	g_modelId = Model_Load("pole.x");
}
void TutoFlagUpdate()
{
	g_flags->Update();
}
void TutoFlagUninit()
{
	if (g_flags == nullptr)
	{
	}
	else
	{
		g_flags->Delete();
	}
	Model_Destroy(&g_modelId, 1);
}

void TutoFlagDraw()
{
	D3DXMATRIX mtx_world, mtx_scale;
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	TutoFlags *focus = g_flags;
	if (focus == nullptr)
	{
		return;
	}
	else
	{
		bool end = false;
		while (end == false)
		{
			mtx_world = mtx_scale * focus->me->mtx;
			Model_Draw(g_modelId, mtx_world);
			if (focus->next == nullptr)
			{
				end = true;
			}
			else
			{
				focus = focus->next;
			}
		}
	}
}
TutoFlags *TutoFlagsGet(void)
{
	return g_flags;
}
void TutoFlagAddScoer()
{
	g_coliNum++;
}
int TutoFlagGetColiNum()
{
	return g_coliNum;
}
