#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"Texture.h"
#include"rock.h"
#include"Judgement.h"
#include"flag.h"
#include"model.h"
#include"player.h"
#include"debug_font.h"
#include "effect.h"


Flag::Flag(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos)
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
	coliSphere = new Sphere(0.3f*scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &mtx);
	coliflag = false;
	IsPlayer = new ForcusSpheresIsSphere(PlayerGet()->coliSpheres, coliSphere);
	m_frame = 30000;
}

Flag::~Flag()
{
}

void Flag::Update()
{
	
	
	if (IsPlayer->forcus.now==true)
	{
		if (coliflag==false)
		{
			coliflag = true;
			//EffectDraw()
			FlagAddScoer();
		}
	}
	D3DXMATRIX mtxRotX, mtxRotY, mtxS, mtxT;
	D3DXMatrixTranslation(&mtxT, pos.x, pos.y, pos.z);
	D3DXMatrixRotationX(&mtxRotX, angleX);
	D3DXMatrixRotationY(&mtxRotY, angleY);
	D3DXMatrixScaling(&mtxS, scale, scale, scale);
	mtx = mtxS * mtxRotX*mtxRotY*mtxT;


	

}

Flags::Flags(Flag *setMe)
{
	me = setMe;

	next = nullptr;
}

Flags::~Flags()
{
}

Flags* Flags::AddFlag(Flag *setFlag)
{

	if (next == nullptr)
	{
		next = new Flags(setFlag);
		next->next = nullptr;
		return next;
	}
	else
	{
		return next->AddFlag(setFlag);
	}
}
void Flags::Update(void)
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
void Flags::Delete(void)
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
void Flags::ColiUpdate(void)
{
	Flags *forcus = this;
	while (true)
	{
		forcus->me->IsPlayer->Update();
		if (forcus->next==nullptr)
		{
			return;
		}
		else
		{
			forcus = forcus->next;
		}


	}
}

static int g_modelId;
static int g_coliNum;
static Flags *g_flags;
static int g_effect_id;
void FlagInit()
{
	Flags *a;
	//1
	g_flags = new Flags(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(0.0f, 0.0f, 25.0f)));
	//2
	g_flags->AddFlag(new Flag(0.0f, 0.0f, 3.0f, D3DXVECTOR3(25.0f, 0.0f, 42.0f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(40.0f, 0.0f, 65.0f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(40.0f, 0.0f, 80.0f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(0.0f, 2.0f, 98.0f)));
	g_flags->AddFlag(new Flag(0.0f, 0.0f, 3.0f, D3DXVECTOR3(25.0f, 8.1f, 110.0f)));
	g_flags->AddFlag(new Flag(0.0f, 0.0f, 3.0f, D3DXVECTOR3(38.0f, 8.1f, 105.0f)));
	//g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(30.0f,-1.7f, 131.0f)));
	//g_flags->AddFlag(new Flag(0.0f, 0.0f, 3.0f, D3DXVECTOR3(38.0f, -18.5f ,156.0f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(47.5f, -21.5f, 170.0f)));
	//g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(57.5f, -20.82f, 191.16f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(70.64f, -18.86f, 209.0f)));
	g_flags->AddFlag(new Flag(0.0f, D3DXToRadian(90), 3.0f, D3DXVECTOR3(60.14f, -24.88f, 235.89f)));


	g_effect_id = Effect_Load(L"gate.efk");

	g_coliNum = 0;


	g_modelId = Model_Load("pole.x");
	
}
void FlagUpdate()
{

	g_flags->Update();


}
void FlagUninit()
{
	if (g_flags == nullptr)
	{

	}
	else
	{
		g_flags->Delete();
	}
	Model_Destroy(&g_modelId, 1);
	Effect_Destroy(&g_effect_id, 1);
}

void FlagDraw()
{
	D3DXMATRIX mtx_scale,mtx_world;
	D3DXMatrixScaling(&mtx_scale, 2.0f, 2.0f, 2.0f);
	Flags *focus = g_flags;
	if (focus == nullptr)
	{
		return;
	}
	else
	{
		bool end = false;
		while (end == false)
		{
			
			if (focus->me->coliflag) {
				focus->me->m_frame--;
				if (focus->me->m_frame > 0) {
					
					//Effect_Draw(g_effect_id, focus->me->mtx);
					
				}
			}
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
	DebugFont_Draw(32, 332, "flag::%d", g_coliNum);
}
Flags *FlagsGet(void)
{
	return g_flags;
}

void FlagAddScoer()
{
	g_coliNum++;
}
int FlagGetColiNum()
{
	return g_coliNum;
}
