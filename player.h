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
	//座標
	D3DXVECTOR3 pos;

	//速度
	float speed = 0.0f;
	float speedMax = 0.0f;

	//加速度
	float acceralation = 0.0f;

	//角度
	float angleX = 0.0f;
	float angleY = 0.0f;

	//回転速度
	float rotSpeed = 0.0f;
	//回転加速度
	float rotAcceralation = 0.0f;

	//大きさ
	float scale = 0.0f;

	Spheres* coliSpheres;
	ForcusSpheresIsSpheres* IsRock;


	//姿勢制御
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
