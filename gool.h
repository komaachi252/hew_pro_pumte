#ifndef GOOL_H_
#define GOOL_H_
#include<d3dx9.h>
#include<d3d9.h>
#include"Judgement.h"

struct Gool
{
	D3DXVECTOR3 pos;
	float angleX;
	float angleY;
	float scale;
	Coli coli;
	float coliLenth;
	bool isColi;
};


void GoolInit(void);
void GoolDraw(void);
void GoolUninit(void);
void GoolUpdate(void);
Gool* GoolGetGool(void);
void GoolSetColi(bool set);
bool GoolGetIsColi(void);
bool GoolGetCrear(void);

#endif // !GOOL_H_

