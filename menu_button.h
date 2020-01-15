//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[menu_button.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/09(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef MENU_BUTTON_H_
#define MENU_BUTTON_H_

#include <d3dx9.h>


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
class Menu_Button {
private:
	int m_tex_id;
	float m_x;
	float m_y;
	float m_width;
	float m_height;
public:
	Menu_Button(int tex_id, float x, float y, float width, float height);
	~Menu_Button(void);
	void Update(void);
	void Draw(void);
};

#endif	//	!MENU_BUTTON_H_
