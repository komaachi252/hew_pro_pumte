//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒQ[ƒ€ƒtƒ‰ƒbƒOƒwƒbƒ_[game_flag.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 1/06(ŒŽ)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef GAME_FLAG_H_
#define GAME_FLAG_H_


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
class Game_Flag 
{
private:
	bool m_is_gameover;
	int m_death_tex;
	int m_clear_tex;
	int m_fade_tex;
	int m_alpha;
	bool is_nextscene;
	bool is_used;
public:
	Game_Flag(bool is_gameover);
	~Game_Flag(void);
	void Update(void);
	void Draw(void);
	bool Is_NextScene(void);
	bool Is_Used(void);
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Flag_Init(void);	//‰Šú‰»ŠÖ”
void Game_Flag_Uninit(void);	//I—¹ˆ—ŠÖ”
void Game_Flag_Update(void);	//XVˆ—
void Game_Flag_Draw(void);    //•`‰æˆ—
void Game_Flag_Create(bool is_gameover);	//‰Šú‰»ŠÖ”
bool Game_Flag_Is_NextScene(void);
bool Game_Flag_Is_Used(void);

#endif	// !GAME_FLAG_H_
