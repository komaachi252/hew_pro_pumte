#include<d3dx9.h>
#include"Judgement.h"
#include"player.h"
#include"brocks.h"
#include"Flags.h"
#include "gool.h"


void JudgementUpdate(void)
{
	bool flag = false;
	Brock *p_brock;
	for (int i = 0; i < BROCK_NUM; i++)
	{
		p_brock = BrocksGetBrock(i);

		flag = ColiSphereIsSphere(D3DXVECTOR3( PlayerGetPos()->x, PlayerGetPos()->y, PlayerGetPos()->z+4), *PlayerGetColiLenth(), p_brock->pos, p_brock->coliLenth);
		if (flag==true)
		{
			BrocksSetColiFlag(i, flag);
			PlayerSetColiFlag(PLAYER_COLI_BROCKS, flag, i);

		}
	}

	Flag* p_flag;
	bool flag2 = false;

	for (int i = 0; i < FLAG_NUM; i++)
	{
		p_flag = FlagsGetFlag(i);

		flag2 = FlagsGetFlag(i);
		flag2 = ColiSphereIsSphere(*PlayerGetPos(), *PlayerGetColiLenth(), p_flag->pos, p_flag->coliLenth);
		if (flag2) {
			FlagsSetColi(i, flag2);
		}
	}

	Gool* p_gool;
	bool flag3 = false;

	p_gool = GoolGetGool();
	flag3 = ColiSphereIsSphere(*PlayerGetPos(), *PlayerGetColiLenth(), p_gool->pos, p_gool->coliLenth);

	if (flag3) {
		GoolSetColi(flag3);
	}


}
float Vec3Lenth(D3DXVECTOR3 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

}
float Vec2Lenth(D3DXVECTOR2 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);

}
bool ColiSphereIsSphere(D3DXVECTOR3 pos1, float lenth1, D3DXVECTOR3 pos2, float lenth2)
{

	float lenth = Vec3Lenth(pos1 - pos2);
	if (lenth <= lenth1 + lenth2)
	{
		return true;
	}


	return false;
}
bool ColiTriger(Coli* c)
{
	if (c->now == true)
	{
		if (c->past == false)
		{
			return true;
		}
	}
	return false;
}

bool ColiRelease(Coli* c)
{
	if (c->now == false)
	{
		if (c->past == true)
		{
			return true;
		}
	}
	return false;
}