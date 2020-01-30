//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒ^ƒCƒgƒ‹ƒGƒ“ƒ^[ƒwƒbƒ_[Title_enter.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 1/4(“y)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef TITLE_ENTER_H_
#define TITLE_ENTER_H_

#include <d3d9.h>
#include <d3dx9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
class Title_Enter
{
private:
	static const int LOGO_TEX_WIDTH = 300;
	static const int LOGO_TEX_HEIGHT = 40;
	static const int LOGO_WIDTH = 600;
	static const int LOGO_HEIGHT = 80;
	int m_tex;
	int m_alpha;
	bool m_is_next_scene;
	int m_frame;
	float m_sin;
	D3DXVECTOR3 m_pos;
public:
	Title_Enter(void);
	~Title_Enter(void);
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	bool Next_Scene(void);
};

#endif	 // TITLE_ENTER_H_
