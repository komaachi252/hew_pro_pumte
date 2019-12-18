//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒwƒbƒ_[model.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 11/14(–Ø)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef MODEL2_H_
#define MODEL2_H_

#include <d3dx9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum PLAYER_COLI
{
	PLAYER_COLI_BROCKS = 0,
	PLAYER_COLI_NUM
};


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Init(void);	//‰Šú‰»ŠÖ”
void Player_Uninit(void);	//I—¹ˆ—ŠÖ”
void Player_Update(void);
void Player_Draw(void);    //•`‰æˆ—
float Get_Player_Pos_Z(void);
D3DXVECTOR3* PlayerGetPos(void);
float* PlayerGetColiLenth(void);
void PlayerSetColiFlag(PLAYER_COLI e, bool set, int ID);

#endif
