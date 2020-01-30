//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�Q�[���t���b�O�w�b�_[game_flag.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/06(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef GAME_FLAG_H_
#define GAME_FLAG_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
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

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Game_Flag_Init(void);	//�������֐�
void Game_Flag_Uninit(void);	//�I�������֐�
void Game_Flag_Update(void);	//�X�V����
void Game_Flag_Draw(void);    //�`�揈��
void Game_Flag_Create(bool is_gameover);	//�������֐�
bool Game_Flag_Is_NextScene(void);
bool Game_Flag_Is_Used(void);

#endif	// !GAME_FLAG_H_
