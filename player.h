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
class Player
{
public:
	//ç¿ïW
	D3DXVECTOR3 pos;

	//ë¨ìx
	float speed = 0.0f;
	float speedMax = 0.0f;

	//â¡ë¨ìx
	float acceralation = 0.0f;

	//äpìx
	float angleX = 0.0f;
	float angleY = 0.0f;

	//âÒì]ë¨ìx
	float rotSpeed = 0.0f;
	//âÒì]â¡ë¨ìx
	float rotAcceralation = 0.0f;

	//ëÂÇ´Ç≥
	float scale = 0.0f;

	Spheres* coliSpheres;
	ForcusSpheresIsSpheres* IsRock;


	//épê®êßå‰
	D3DXVECTOR3 vecFront;
	D3DXVECTOR3 vecRight;
	D3DXVECTOR3 vecUp;
	
	float cameraAngleX;
	float cameraAngleY;

	float fov = 0.0f;
	int modelId;
	D3DXMATRIX mtxWorld;

	~Player();
	void Init(void);
	void Draw(void);
	void Uninit(void);
	void Update(void);
	void AngleUpdate();
};

void PlayerInit(void);
void PlayerDraw(void);
void PlayerUninit(void);
void PlayerUpdate(void);
Player* PlayerGet();


#endif // !PLAYER_H_
