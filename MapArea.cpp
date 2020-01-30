#include "MapArea.h"
#include"Judgement.h"
#include"line.h"
#include"Texture.h"
#include "model.h"

MapArea::MapArea(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos)
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

MapArea::~MapArea()
{
}

void MapArea::Update()
{
	



}

MapAreas::MapAreas(MapArea *setMe)
{
	me = setMe;

	next = nullptr;
}

MapAreas::~MapAreas()
{
}

MapAreas* MapAreas::AddMapArea(MapArea *setMapArea)
{

	if (next == nullptr)
	{
		next = new MapAreas(setMapArea);
		next->next = nullptr;
		return next;
	}
	else
	{
		return next->AddMapArea(setMapArea);
	}
}
void MapAreas::Update(void)
{
	me->Update();


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
void MapAreas::Delete(void)
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


static int g_texId;
static MapAreas *g_mapAreas;
static Spheres *g_coli;
void MapAreaInit()
{
	MapAreas *a;
	D3DXVECTOR3 distance;
	g_mapAreas = new MapAreas(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, -15.0f)));
	g_coli = new Spheres(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &g_mapAreas->me->mtx));
	for (int i = 0; i < 40; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f, 0.0f, -5.0f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 40; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.0f, 0.0f, -5.0f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 9; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-4.0f + 1.0f*i, 0.0f, -5.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	
	a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.0f, 0.0f, 35.0f)));
	g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, 0.0f, 35.0f + sin(D3DXToRadian(90.0f*i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f + 1.0f*i, 0.0f, 45.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f + 1.0f*i, 0.0f, 35.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(35.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, 0.0f, 45.0f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	for (int i = 0; i < 40; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f, 0.0f, 45.0f + 1.0f*i)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 40; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(35.0f, 0.0f, 45.0f + 1.0f*i)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(35.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, 0.0f, 85.0f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f + 1.0f*i, 0.0f, 85.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f + 1.0f*i, 0.0f, 95.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, 0.0f, 95.0f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(-5.0f, 15.0f, 120.0f) - D3DXVECTOR3(-5.0f, 0.0f, 95.0f);
	for (int i = 0; i < 42; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f, 0.0f, 95.0f) + distance * i / 40));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(5.0f, 15.0f, 120.0f) - D3DXVECTOR3(5.0f, 0.0f, 95.0f);
	for (int i = 0; i < 42; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(-5.0f, 0.0f, 95.0f) + distance * i / 40));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 40; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, 15.0f, 120.0f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(-5.0f, 15.0f, 120.0f) - D3DXVECTOR3(-5.0f, 0.0f, 95.0f);
	for (int i = 0; i < 42; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f, 0.0f, 95.0f) + distance * i / 40));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, 8.0f, 114.0f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(15.0f, 8.2f, 114.0f) - D3DXVECTOR3(15.0f, 15.3f, 121.0f);
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f, 15.3f, 121.0f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(5.0f, 15.3f, 121.0f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f + 1.0f*i, 8.2f, 104.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 31; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f + 1.0f*i, 8.2f, 114.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, 8.0f, 114.0f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(55.0f, 8.2f, 114.0f) - D3DXVECTOR3(55.0f, -1.77f, 131.0f);
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(55.0f, -1.77f, 131.0f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f, -1.77f, 131.0f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -1.77f, 131.0f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	
	for (int i = 0; i < 11; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f - i * 1.0f, -1.77f, 131.2f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(45.0f - i * 1.0f, -1.77f, 141.2f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(35.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -1.77f, 131.2f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -1.77f, 131.2f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -1.77f, 131.2f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(15.0f, -1.77f, 131.2f) - D3DXVECTOR3(15.0f, -11.7f, 148.5f);
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(15.0f, -11.7f, 148.5f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f, -11.7f, 148.5f) + distance * i / 20));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(25.0f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -11.7f, 148.5f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(25.0f, -11.7f, 148.5f) - D3DXVECTOR3(42.2f, -21.77f, 148.5f);
	for (int i = 0; i < 25; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(42.2f, -21.77f, 148.5f) + distance * i / 24));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(42.2f, -21.77f, 158.5f) + distance * i / 24));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(42.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -21.77f, 158.5f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 21; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(42.2f, -21.77f, 158.5f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(52.2f, -21.77f, 158.5f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(52.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -21.77f, 178.5f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(52.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -21.77f, 188.5f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(52.2f, -21.77f, 188.5f) - D3DXVECTOR3(52.2f, -18.35f, 197.75f);
	for (int i = 0; i < 18; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(52.2f, -18.35f, 197.75f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -18.35f, 197.75f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -18.35f, 197.75f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -18.35f, 207.75f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(62.2f, -18.35f, 207.75f) - D3DXVECTOR3(62.2f, -21.77f, 217.75f);
	for (int i = 0; i < 18; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -21.77f, 217.75f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f, -21.77f, 217.75f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -21.77f, 217.75f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -21.77f, 227.75f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(62.2f, -21.77f, 227.75f) - D3DXVECTOR3(62.2f, -25.19f, 236.8f);
	for (int i = 0; i < 18; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -25.19f, 236.8f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(52.2f, -25.19f, 236.8f) + distance * i / 17));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -25.19f, 236.8f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -25.19f, 246.8f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	distance = D3DXVECTOR3(62.2f, -15.19f, 264.00f) - D3DXVECTOR3(62.2f, -25.19f, 246.8f);
	for (int i = 0; i < 27; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -25.19f, 246.8f) + distance * i / 26));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));

		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f, -25.19f, 246.8f) + distance * i /26));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}

	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 264.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}

	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 274.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 274.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 284.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 284.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}

	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 294.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 294.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	/////
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 304.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 304.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 314.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 314.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 324.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 324.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 334.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f + cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 334.00f + sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 20; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f - cos(D3DXToRadian(90.0f * i / 20)) * 10, -15.19f, 344.00f - sin(D3DXToRadian(90.0f * i / 20)) * 10)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}

	distance = D3DXVECTOR3(72.2f, -15.19f, 344.00f) - D3DXVECTOR3(72.2f, -64.68f, 393.0f);
	for (int i = 0; i < 71; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -64.68f, 393.0f) + distance * i / 70));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f, -64.68f, 393.0f) + distance * i /70));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
				
	for (int i = 0; i < 51; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(72.2f, -64.68f, 393.0f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f, -64.68f, 393.0f + i * 1.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}
	for (int i = 0; i < 11; i++)
	{
		a = g_mapAreas->AddMapArea(new MapArea(0.0f, 0.0f, 1.0f, D3DXVECTOR3(62.2f + i * 1.0f, -64.68f, 444.0f)));
		g_coli->AddSphare(new Sphere(0.5f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), &a->me->mtx));
	}

	//64.68
	//395

	/*
	g_texId = Texture_SetLoadFile("MyAccet\\texture\\tree000.png", 1024, 1024);
	Texture_Load();
	*/
	//g_texId = Model_Load("ft.x");
}
void MapAreaUpdate()
{

	g_mapAreas->Update();

	g_coli->Update();

}
void MapAreaUninit()
{
	if (g_mapAreas == nullptr)
	{

	}
	else
	{
		g_mapAreas->Delete();
		g_mapAreas = nullptr;
	}
}

void MapAreaDraw()
{
	//
	MapAreas *focus = g_mapAreas;
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
MapAreas *MapAreasGet(void)
{
	return g_mapAreas;
}
Spheres *MapAreasGetColi(void)
{
	return g_coli;
}
