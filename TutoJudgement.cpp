#include<d3dx9.h>
#include"Judgement.h"
#include"tutorial_player.h"
#include"TutoFlag.h"
static ForcusSpheresIsSpheres *g_coliPlayerIsRock;
static ForcusSpheresIsSpheres *g_coliPlayerIsMapArea;


float TutoVec3Lenth(D3DXVECTOR3 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

}
float TutoVec2Lenth(D3DXVECTOR2 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);

}

void TutoJudgementInit(void)
{
	g_coliPlayerIsRock = TutoPlayerGet()->IsRock;
	g_coliPlayerIsMapArea = TutoPlayerGet()->IsMapArea;
}
void TutoJudgementUpdate(void)
{
	g_coliPlayerIsRock->Update();
	g_coliPlayerIsMapArea->Update();
	TutoFlagsGet()->ColiUpdate();
}