#ifndef TUTOMAP_AREA_H_
#define TUTOMAP_AREA_H_
#include"Judgement.h"
#include "MapArea.h"


void TutoMapAreaInit();
void TutoMapAreaUpdate();
void TutoMapAreaUninit();
void TutoMapAreaDraw();
MapAreas *TutoMapAreasGet(void);
Spheres *TutoMapAreasGetColi(void);

#endif //MAP_AREA_H_
