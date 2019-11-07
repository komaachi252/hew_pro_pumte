#ifndef UI_H_
#define UI_H_

void UI_Init(void);
void UI_Uninit(void);
void UI_Update(void);
void UI_Draw(void);


enum UI_TYPE
{
	UI_TIME,
	UI_GATE,
	UI_TYPE_MAX
};

#endif UI_H_
