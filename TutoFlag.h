#ifndef TUTO_FLAG_H_
#define TUTO_FLAG_H_
#include"Judgement.h"
#include"flag.h"

class TutoFlag
{
public:
	float angleX;
	float angleY;
	float scale;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtx;
	bool coliflag;
	Sphere *coliSphere;
	ForcusSpheresIsSphere *IsPlayer;
	void Update();
	TutoFlag(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos);
	~TutoFlag();

private:

};

class TutoFlags
{
public:
	TutoFlag *me;
	TutoFlags *next;
	TutoFlags(TutoFlag *setMe);
	~TutoFlags();
	TutoFlags *AddFlag(TutoFlag *setFlag);
	void ColiUpdate(void);
	void Update(void);
	void Delete(void);
private:

};
void TutoFlagInit();
void TutoFlagUpdate();
void TutoFlagUninit();
void TutoFlagDraw();
TutoFlags *TutoFlagsGet(void);
void TutoFlagAddScoer();


int TutoFlagGetColiNum();

#endif // !FLAG_H_