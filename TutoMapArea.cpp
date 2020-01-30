#include "MapArea.h"
#include"Judgement.h"
#include"line.h"
#include"Texture.h"
#include "model.h"

static int g_texId;
static MapAreas *g_mapAreas2;
static Spheres *g_coli2;
void TutoMapAreaInit()
{
	MapAreas *a;
	D3DXVECTOR3 distance;
	g_mapAreas2 = new MapAreas(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, -15.0f)));
	g_coli2 = new Spheres(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &g_mapAreas2->me->mtx));
	
	for (int i = 0; i < 11; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.5f + i * 1.0f, 0.0f, -5.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	
	for (int i = 0; i < 30; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.5f, 0.0f, -5.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.5f, 0.0f, -5.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
	
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.5f - cos(D3DXToRadian(90.0f * i / 20))*11.0f, 0.0f, 25.0f + sin(D3DXToRadian(90.0f * i / 20))*11.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.5f + i * 1.0f, 0.0f, 24.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.5f + i * 1.0f, 0.0f, 35.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.5f + cos(D3DXToRadian(90.0f * i / 20))*10.0f, 0.0f, 35.0f - sin(D3DXToRadian(90.0f * i / 20))*10.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(24.5f, 0.0f, 35.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(35.5f, 0.0f, 35.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.5f + cos(D3DXToRadian(90.0f * i / 20))*10.0f, 0.0f, 55.0f + sin(D3DXToRadian(90.0f * i / 20))*10.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(24.5f - i * 1.0f, 0.0f, 54.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(24.5f - i * 1.0f, 0.0f, 65.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f - cos(D3DXToRadian(90.0f * i / 20))*10.5f, 0.0f, 65.5f - sin(D3DXToRadian(90.0f * i / 20))*10.5f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.5f , 0.0f, 66.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.5f, 0.0f, 66.0f + i * 1.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 11; i++)
	{
		a = g_mapAreas2->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.0f + i * 1.0f, 0.0f, 85.0f)));
		g_coli2->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		
	}
	
	//64.68
	//395

	/*
	g_texId = Texture_SetLoadFile("MyAccet\\texture\\tree000.png", 1024, 1024);
	Texture_Load();
	*/
	g_texId = Model_Load("ft.x");
}
void TutoMapAreaUpdate()
{

	g_mapAreas2->Update();

	g_coli2->Update();

}
void TutoMapAreaUninit()
{
	if (g_mapAreas2 == nullptr)
	{

	}
	else
	{
		g_mapAreas2->Delete();
		g_mapAreas2 = nullptr;
	}
}

void TutoMapAreaDraw()
{
	//
	MapAreas *focus = g_mapAreas2;
	if (focus == nullptr)
	{
		return;
	}
	else
	{
		bool end = false;
		while (end == false)
		{

			//BillDraw(focus->me->mtx, g_texId);
			//Model_Draw(g_texId, focus->me->mtx);
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
MapAreas *TutoMapAreasGet(void)
{
	return g_mapAreas2;
}
Spheres *TutoMapAreasGetColi(void)
{
	return g_coli2;
}
