#ifndef TUTOROCK_H_
#define TUTOROCK_H_

#include"Judgement.h"
#include "rock.h"


void TutoRockInit();
void TutoRockUpdate();
void TutoRockUninit();
void TutoRockDraw();
Rocks *TutoRocksGet(void);
Spheres *TutoRocksGetColi(void);


#endif // !ROCK_H_