//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[start_count.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 11/20(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include "common.h"
#include "camera.h"
#include "direct3d.h"
#include "input.h"
#include "sound.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
class Start_Count {
private:
	int num;  //  �\������e�N�X�`�������ԍ�
	int frame_count;  //  �t���[���J�E���^�[
	int tex;  //  �e�N�X�`��id
	bool is_press;  //  ��荇�����{�^�������ꂽ��
	bool is_used;  //  �g�p���Ȃ�true
	bool is_go; //  �f�n�I�̃e�N�X�`����\�����true
	int start_frame;
	D3DXVECTOR2 pos;  //  �\�����W
	static const int TEX_WIDTH = 580;
	static const int TEX_HEIGHT = 580;
	static const int WAIT_FRAME = 80;  // �t���[��
	static const int GO_FRAME = 60;  // �t���[��
	static const int NUM_MAX = 3;
	static const float POS_X;
	static const float POS_Y;
public:
	Start_Count(void);
	~Start_Count(void);
	void Update(void);
	void Draw(void);
	bool Is_Go(void);
};



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
const float Start_Count::POS_X = SCREEN_WIDTH * 0.61f;  // �e�N�X�`���������W
const float Start_Count::POS_Y = SCREEN_HEIGHT * 0.5f;

static Start_Count* gp_start_count = nullptr;

static int g_goal_tex = 0;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Start_Count_Init(void)
{
	gp_start_count = new Start_Count;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Start_Count_Uninit(void)
{
	delete gp_start_count;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Start_Count_Update(void)
{
	gp_start_count->Update();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Start_Count_Draw(void)
{
	gp_start_count->Draw();
}

//��������������������������������������������������������������������������������
//	�f�n�I�\�����菈��
//��������������������������������������������������������������������������������
bool Is_Start_Count_End(void)
{
	if (gp_start_count == nullptr) return false;
	return gp_start_count->Is_Go();
}

//��������������������������������������������������������������������������������
//	Start_Count�N���X �R���X�g���N�^
//��������������������������������������������������������������������������������
Start_Count::Start_Count(void):num(0),frame_count(0),pos(POS_X, POS_Y),is_press(false),is_used(true),is_go(false),start_frame(60)
{
	tex = Texture_SetLoadFile("Asset/Texture/new_start.png", TEX_WIDTH, TEX_HEIGHT);
	
	Texture_Load();
}

//��������������������������������������������������������������������������������
//	Start_Count�N���X �f�X�g���N�^
//��������������������������������������������������������������������������������
Start_Count::~Start_Count(void)
{
	Texture_Destroy(&tex, 1);
}

//��������������������������������������������������������������������������������
//	Start_Count�N���X �X�V�֐�
//��������������������������������������������������������������������������������
void Start_Count::Update(void)
{
	if (!is_used) { return; }
	start_frame--;
	if (start_frame <= 0) {
		is_press = true;
	}
	/*
	if (Keyboard_IsTrigger(DIK_SPACE)) {
		is_press = true;  
	}
	*/
	if (frame_count == 1 && num == 0) {
		PlaySound(SOUND_LABEL_SE_COUNT);
	}

	if (frame_count >= WAIT_FRAME && num < NUM_MAX) {
		if (num != 2) {
			PlaySound(SOUND_LABEL_SE_COUNT);
		}
		else {
			PlaySound(SOUND_LABEL_SE_WHISTLE);
		}
		num++;
		frame_count = 0;
		if (num == NUM_MAX) { is_go = true; }
	}
	if (frame_count >= GO_FRAME && num == NUM_MAX) {
		frame_count = 0;
		is_used = false;
	}
	if (is_press) {
		frame_count++;
	}
}

//��������������������������������������������������������������������������������
//	Start_Count�N���X �`��֐�
//��������������������������������������������������������������������������������
void Start_Count::Draw(void)
{
	if (!is_used) { return; }
	D3DXMATRIX mtxW;

	D3DXMatrixIdentity(&mtxW);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	GetDevice()->SetTransform(D3DTS_WORLD, &mtxW);


	float tx = pos.x - TEX_WIDTH * 0.5f;
	float ty = pos.y - TEX_HEIGHT * 0.5f;
	
	// eye at up �ݒ�
	Camera_2D();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	Sprite_Draw(tex, tx, ty,  (int)(num % 2) * 0.5f * TEX_WIDTH, (int)(num / 2) * 0.5f * TEX_HEIGHT, (int)TEX_WIDTH * 0.5f, (int)TEX_HEIGHT * 0.5f);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//��������������������������������������������������������������������������������
//	Start_Count�N���X �f�n�I�\���ォ��true��Ԃ�
//��������������������������������������������������������������������������������
bool Start_Count::Is_Go(void)
{
	return is_go;
}
