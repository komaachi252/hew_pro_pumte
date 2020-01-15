#ifndef LINE_H_
#define LINE_H_

#define LINE_MAX (20)


void LineInit();
void LineUninit();
void LineDraw();
void LineUpdate();
void LineSet(D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd);
#endif // !LINE_H_
