
#ifndef BROCKS_H_
#define BROCKS_H_
#include<d3dx9.h>
#include<d3d9.h>
#include"Judgement.h"
#define BROCK_NUM (13)
struct Brock
{
	D3DXVECTOR3 pos;
	float angleX;
	float angleY;
	float scale;
	Coli coli;
	float coliLenth;
	
	bool draw;
};


void BrocksInit(void);
void BrocksDraw(void);
void BrocksUninit(void);
void BrocksUpdate(void);
Brock* BrocksGetBrock(int id);
void BrocksSetColiFlag(int id, bool set);

#endif // !BROCKS_H_
