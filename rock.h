#ifndef ROCK_H_
#define ROCK_H_

#include"Judgement.h"
class Rock
{
public:
	float angleX;
	float angleY;
	float scale;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtx;
	void Update();

	Rock(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos);
	~Rock();

private:

};

class Rocks
{
public:
	Rock *me;
	Rocks *next;
	Rocks(Rock *setMe);
	~Rocks();
	Rocks *AddRock(Rock *setRock);
	void Update(void);
	void Delete(void);
private:

};



void RockInit();
void RockUpdate();
void RockUninit();
void RockDraw();
Rocks *RocksGet(void);
Spheres *RocksGetColi(void);


#endif // !ROCK_H_