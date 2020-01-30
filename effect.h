#pragma once
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒGƒtƒFƒNƒgƒwƒbƒ_[effect.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò ˆÀ•Û‚­‚ñ
//                                                               ì¬“ú 12/01(“ú)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3dx9.h>


HRESULT Effect_Init(void);
void Efffect_Uninit(void);
int Effect_Load(const wchar_t* filename);
void Effect_Destroy(int ids[], int count);
void Effect_Destroy(void);
void Effect_Draw(int idx, const D3DXMATRIX& mtx);

