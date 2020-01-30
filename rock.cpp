#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"model.h"
#include"texture.h"
#include"rock.h"
#include"Judgement.h"

Rock::Rock(float set_angleX,float set_angleY,float set_scale,D3DXVECTOR3 set_pos)
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

	
}

Rock::~Rock()
{
}

void Rock::Update()
{
	D3DXMATRIX mtxRotX, mtxRotY, mtxS, mtxT;
	D3DXMatrixTranslation(&mtxT, pos.x, pos.y, pos.z);
	D3DXMatrixRotationX(&mtxRotX, angleX);
	D3DXMatrixRotationY(&mtxRotY, angleY);
	D3DXMatrixScaling(&mtxS, scale, scale, scale);
	mtx = mtxS * mtxRotX*mtxRotY*mtxT;

	D3DXVECTOR3 upPosA(mtx._41, mtx._42, mtx._43);

	DebugLineSet(upPosA,0.5f);


}

Rocks::Rocks(Rock *setMe)
{
	me = setMe;

	next = nullptr;
}

Rocks::~Rocks()
{
}

Rocks* Rocks::AddRock(Rock *setRock)
{
	Rocks *forcus = this;
	while (true)
	{

		if (forcus->next == nullptr)
		{
			forcus->next = new Rocks(setRock);
			forcus->next->next = nullptr;
			return forcus->next;
		}
		else
		{
			forcus=forcus->next;
		}

	}}
void Rocks::Update(void)
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
void Rocks::Delete(void)
{
	if (next==nullptr)
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


static int g_texId;
static Rocks *g_rocks;
static Spheres *g_coli3;
static int g_model_id;
void RockInit()
{
	Rocks *a;
	//1
	g_rocks = new Rocks(new Rock(0.0f, 0.5f, 1.0f, D3DXVECTOR3(-4.0f, 0.5f, 15.0f)));
	g_coli3 = new Spheres(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &g_rocks->me->mtx));
	//
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f, 0.5f, 37.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//3
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f, 0.5f, 37.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//4
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(44.0f, 0.5f, 60.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//5
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(40.0f, 0.5f, 70.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//6
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(38.0f, 0.5f, 94.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//7
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(30.0f, 0.5f, 90.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//8
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(20.0f, 0.5f, 86.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//9
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f, 0.5f, 88.5f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//10
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(3.5f, 6.5f, 105.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//11
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-3.5f, 8.7f, 110.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	//12
	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(3.5f, 13.2f, 117.5f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(10.0f, 8.5f, 115.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(30.0f, 8.5f, 109.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(44.0f, 8.5f, 113.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(47.0f, 3.0f, 117.5f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(53.0f, 1.25f, 125.5f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(23.0f, -4.25f, 135.5f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(27.5f, -13.5f, 155.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

	a = g_rocks->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(47.5f, -22.0f, 160.0f)));
	g_coli3->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));


	//g_texId = Texture_SetLoadFile("Asset\\Texture\\tree000.png", 1024, 1024);
	g_model_id = Model_Load("rock.x");
}
void RockUpdate()
{

	g_rocks->Update();

	g_coli3->Update();

}
void RockUninit()
{
	if (g_rocks==nullptr)
	{

	}
	else
	{
		g_rocks->Delete();
		g_rocks = nullptr;
	}
	Model_Destroy(&g_model_id, 1);
}

void RockDraw()
{
	Rocks *focus = g_rocks;
	if (focus==nullptr)
	{
		return;
	}
	else
	{
		bool end = false;
		while (end == false)
		{

			//BillBoard::Draw(, g_texId);
			Model_Draw(g_model_id, focus->me->mtx);
			if (focus->next==nullptr)
			{
				end = true;
			}
			else
			{
				if (focus->me==nullptr)
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
}
Rocks *RocksGet(void)
{
	return g_rocks;
}
Spheres *RocksGetColi(void)
{
	return g_coli3;
}
