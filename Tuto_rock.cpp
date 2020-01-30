#include<d3dx9.h>
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"model.h"
#include"texture.h"
#include"rock.h"
#include"Judgement.h"

static int g_texId;
static Rocks *g_rocks2;
static Spheres *g_coli1;
static int g_model_id;
void TutoRockInit()
{
	Rocks *a;
	//1
	g_rocks2 = new Rocks(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-4.0f, 0.5f, 15.0f)));
	g_coli1 = new Spheres(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &g_rocks2->me->mtx));
	//2
	a = g_rocks2->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(30.0f, 0.5f, 37.0f)));
	g_coli1->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	a = g_rocks2->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(20.0f, 0.5f, 60.0f)));
	g_coli1->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	a = g_rocks2->AddRock(new Rock(0.0f, 0.0f, 1.0f, D3DXVECTOR3(3.0f, 0.5f, 70.0f)));
	g_coli1->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	g_model_id = Model_Load("rock.x");
}
void TutoRockUpdate()
{

	g_rocks2->Update();

	g_coli1->Update();

}
void TutoRockUninit()
{
	if (g_rocks2==nullptr)
	{

	}
	else
	{
		g_rocks2->Delete();
	}
	Model_Destroy(&g_model_id, 1);
}

void TutoRockDraw()
{
	Rocks *focus = g_rocks2;
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
				focus = focus->next;
			}
		}
	}
}
Rocks *TutoRocksGet(void)
{
	return g_rocks2;
}
Spheres *TutoRocksGetColi(void)
{
	return g_coli1;
}
