#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_
#include<d3dx9.h>

struct Coli
{
	bool now;
	bool past;
};
float Vec3Lenth(D3DXVECTOR3 vec);
float Vec2Lenth(D3DXVECTOR2 vec);
bool ColiTriger(Coli* c);
bool ColiRelease(Coli* c);
bool ColiSphereIsSphere(D3DXVECTOR3 pos1, float lenth1, D3DXVECTOR3 pos2, float lenth2);
void JudgementUpdate(void);


#endif // !JUDGEMENT_H_