#ifndef TUTOPLAYER_H_
#define TUTOPLAYER_H_
#define FVF_TUTOPLAYER (  D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_NORMAL)
#include"TutoJudgement.h"
#include<d3d9.h>
#include"direct3d.h"
#include"common.h"
#include"camera.h"
#include"grid.h"
#include<math.h>
#include"input.h"
#include"line.h"
#include "player.h"
class TPlayer
{
public:
	PLAY_MODE m_mode;

	//座標
	D3DXVECTOR3 pos;
	D3DXVECTOR3 pastPos;
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
	ForcusSpheresIsSpheres* IsMapArea;


	//姿勢制御
	D3DXVECTOR3 vecFront;
	D3DXVECTOR3 vecRight;
	D3DXVECTOR3 vecUp;

	float cameraAngleX;
	float cameraAngleY;

	float fov = 0.0f;
	int modelId;
	D3DXMATRIX mtxWorld;
	bool *m_is_used; // ユーザー入力用
	int *m_is_frame; //	漕ぐフレーム

	~TPlayer();
	void Init(void);
	void Draw(void);
	void Uninit(void);
	void Update(void);
	void AngleUpdate();
	void Set_Mode(PLAY_MODE mode);
	void Row(int index);
};

void TutoPlayerInit(void);
void TutoPlayerDraw(void);
void TutoPlayerUninit(void);
void TutoPlayerUpdate(void);
TPlayer* TutoPlayerGet();
void Set_TPlayer_Mode(PLAY_MODE mode);


#endif // !PLAYER_H_
