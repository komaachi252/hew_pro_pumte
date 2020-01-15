#include"Circle.h"

bool CircleIsCircle(Circle* pA,Circle* pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius) > D3DXVec2LengthSq(&(pA->position - pB->position));

}
