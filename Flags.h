#ifndef FLAGS_H_
#define FLAGS_H_
#include<d3dx9.h>
#include<d3d9.h>
#include"Judgement.h"
#define FLAG_NUM (15)
struct Flag
{
	D3DXVECTOR3 pos;
	float angleX;
	float angleY;
	float scale;
	Coli coli;
	float coliLenth;
	bool isColi;
};


void FlagsInit(void);
void FlagsDraw(void);
void FlagsUninit(void);
void FlagsUpdate(void);
Flag* FlagsGetFlag(int id);
void FlagsSetColi(int id, bool set);
void FlagsAddScore(void);
int FlagsGetCnt(void);

#endif // !FLAGS_H_
