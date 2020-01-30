#ifndef MAP_AREA_H_
#define MAP_AREA_H_
#include"Judgement.h"
class MapArea
{
public:
	float angleX;
	float angleY;
	float scale;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtx;
	void Update();

	MapArea(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos);
	~MapArea();

private:

};

class MapAreas
{
public:
	MapArea *me;
	MapAreas *next;
	MapAreas(MapArea *setMe);
	~MapAreas();
	MapAreas *AddMapArea(MapArea *setMapArea);
	void Update(void);
	void Delete(void);
private:

};


void MapAreaInit();
void MapAreaUpdate();
void MapAreaUninit();
void MapAreaDraw();
MapAreas *MapAreasGet(void);
Spheres *MapAreasGetColi(void);

#endif //MAP_AREA_H_
