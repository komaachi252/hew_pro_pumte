#ifndef PLAYER_H_
#define PLAYER_H_
#define FVF_PLAYER (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)
#include"Judgement.h"
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"grid.h"
#include<math.h>
#include"input.h"
#include"line.h"
enum PLAY_MODE {
	MODE_2,
	MODE_4,
	MODE_MAX,
};

class Player
{
public:
	
	PLAY_MODE m_mode;
	//���W
	D3DXVECTOR3 pos;
	D3DXVECTOR3 pastPos;
	//���x
	float speed = 0.0f;
	float speedMax = 0.0f;

	//�����x
	float acceralation = 0.0f;

	//�p�x
	float angleX = 0.0f;
	float angleY = 0.0f;

	//��]���x
	float rotSpeed = 0.0f;
	//��]�����x
	float rotAcceralation = 0.0f;

	//�傫��
	float scale = 0.0f;

	Spheres* coliSpheres;
	ForcusSpheresIsSpheres* IsRock;
	ForcusSpheresIsSpheres* IsMapArea;


	//�p������
	D3DXVECTOR3 vecFront;
	D3DXVECTOR3 vecRight;
	D3DXVECTOR3 vecUp;
	
	float cameraAngleX;
	float cameraAngleY;

	float fov = 0.0f;
	int modelId;
	D3DXMATRIX mtxWorld;
	bool *m_is_used; // ���[�U�[���͗p
	int *m_is_frame; //	�����t���[��
	int m_effect;
	int m_effect_frame;

	~Player();
	void Init(void);
	void Draw(void);
	void Uninit(void);
	void Update(void);
	void AngleUpdate();
	void Set_Mode(PLAY_MODE mode);
	void Row(int index);
};

void PlayerInit(void);
void PlayerDraw(void);
void PlayerUninit(void);
void PlayerUpdate(void);
Player* PlayerGet();

D3DXVECTOR3* Get_Player_Front(void);
D3DXVECTOR3* Get_Player_Pos(void);
void Set_Player_Mode(PLAY_MODE mode);

#endif // !PLAYER_H_
