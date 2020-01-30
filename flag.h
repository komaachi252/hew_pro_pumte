#ifndef FLAG_H_
#define FLAG_H_

#include"Judgement.h"

class Flag
{
public:
	float angleX;
	float angleY;
	float scale;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtx;
	bool coliflag;
	int m_frame;
	Sphere *coliSphere;
	ForcusSpheresIsSphere *IsPlayer;
	void Update();
	Flag(float set_angleX, float set_angleY, float set_scale, D3DXVECTOR3 set_pos);
	~Flag();

private:

};

class Flags
{
public:
	Flag *me;
	Flags *next;

	Flags(Flag *setMe);
	~Flags();
	Flags *AddFlag(Flag *setFlag);
	void ColiUpdate(void);
	void Update(void);
	void Delete(void);
private:

};
void FlagInit();
void FlagUpdate();
void FlagUninit();
void FlagDraw();
Flags *FlagsGet(void);
void FlagAddScoer();
int FlagGetColiNum();

#endif // !FLAG_H_