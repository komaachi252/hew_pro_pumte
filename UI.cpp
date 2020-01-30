//UI�̕\��
//����ҁ@���ی\��Y
//
//�f�t�H���g�ł́A���̉摜�����ɍ���Ă���A����ɕ\�����Ă���@�{�摜�������ꍇ�����K�{
//�i���o�[�\���̃|�W�V�����̃}�W�b�N�i���o�[�͂��e�͂��������@�idefine����ɂ��������Ȃ��j
//�^�C���\���̕����͏����_�͂Ȃ����A�f�t�H���g�̉�2���͏����ƂȂ��Ă���
//��F�Q�[����ʂŁuTime:11451�v�̏ꍇ�@�u114.51�b�v�ƂȂ�

#include "texture.h"
#include "sprite.h"
#include "number.h"
#include "common.h"
#include "camera.h"
#include "start_count.h"
#include "direct3d.h"
#include "flag.h"
#include "sound.h"

//#include "gool.h"

#define TEX_HIGHT (196)																	//�e�N�X�`���̍���
#define COUNTUP_TIME (0.017)															//�^�C���̃C���N�������g���@120�b��2.4�b�̌덷�A��
#define GATE_NUM (10)																	//�S�ẴQ�[�g���@�e�X�g�p��16�����Ă���
#define DECIMAL_POINT (100)																//�����_�ȉ�2����\�����邽�߂�100�{����p�̐��l
#define NUM_SPACE (28)																	//�����Ɛ����̊�
#define TIME_DIGIT (5)																	//�^�C���̌����@��2��������

/*																						UI�̉摜���������ɂȂ������p�̔ԍ��t��
enum UI_TYPE
{
UI_TIME,
UI_GATE,
UI_TYPE_MAX
};

*/

static int g_ui_timer_tex = 0;																//UI�̃e�N�X�`����ێ�����ϐ�
static int g_ui_flag_tex = 0;																//UI�̃e�N�X�`����ێ�����ϐ�
static int g_period_tex = 0;														    //�s���I�h�̃e�N�X�`����ێ�����ϐ�
static int g_goal_tex = 0;														    //�s���I�h�̃e�N�X�`����ێ�����ϐ�
static int g_new_tex = 0;														    //�s���I�h�̃e�N�X�`����ێ�����ϐ�
static double g_time = 0.0f;															//�^�C����ێ�����ϐ�
static int g_gate_count = 0;															//�ʉ߂����Q�[�g����ێ�����ϐ�
static int g_old_count = 0;															//�ʉ߂����Q�[�g����ێ�����ϐ�
static bool g_goal_sound;															//�ʉ߂����Q�[�g����ێ�����ϐ�

void UI_Init(void)
{
	Number_Init();																		//�i���o�[�̃C�j�b�g
	g_ui_timer_tex = Texture_SetLoadFile("Asset/Texture/ui_timer.png", 303, 107);	//UI�e�N�X�`���ǂݍ���
	g_ui_flag_tex = Texture_SetLoadFile("Asset/Texture/newflag.png", 303, 107);	//UI�e�N�X�`���ǂݍ���
	g_period_tex = Texture_SetLoadFile("Asset/Texture/period.png", 30, 28);	//UI�e�N�X�`���ǂݍ���
	g_goal_tex = Texture_SetLoadFile("Asset/Texture/goal_logo.png", 294, 294);	//UI�e�N�X�`���ǂݍ���
	g_new_tex = Texture_SetLoadFile("Asset/Texture/flagcount.png", 256, 43);	//UI�e�N�X�`���ǂݍ���
	Texture_Load();  //�e�N�X�`���Z�b�g
	g_time = 0.0f;																		//�^�C���̏�����
	g_gate_count = 0;																	//�ʉ߃Q�[�g���̏�����
	g_old_count = 0;//�ʉ߃Q�[�g���̏�����
	g_goal_sound = false;
}
	
void UI_Uninit(void)
{
	Texture_Destroy(&g_ui_flag_tex, 1);																//�e�N�X�`�����
	Texture_Destroy(&g_ui_timer_tex, 1);																//�e�N�X�`�����
	Texture_Destroy(&g_period_tex, 1);																//�e�N�X�`�����
	Texture_Destroy(&g_goal_tex, 1);																//�e�N�X�`�����
	
}
void UI_Update(void)
{
	if (!Is_Start_Count_End()) {
		return;
	}
	/*
	if(GoolGetCrear() && !g_goal_sound){
		PlaySound(SOUND_LABEL_WHI);
	}
	if (GoolGetCrear()) {
		return;
	}
	*/
	g_time += COUNTUP_TIME;															   //�^�C���̃J�E���g�A�b�v


}
void UI_Draw()
{
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_gate_count = FlagGetColiNum();
	if (g_old_count < g_gate_count) {
		PlaySound(SOUND_LABEL_SE_GATE);
		g_old_count = g_gate_count;
	}
	Camera_2D();
	Sprite_Draw(g_ui_timer_tex, 0, 0);														//UI�̕��������̕\��
	Sprite_Draw(g_ui_flag_tex, 0, 107);	//UI�̕��������̕\��
	//Sprite_Draw(g_new_tex, 75, 136, g_gate_count * 19.69f ,43);
	Sprite_Draw(g_new_tex, 75, 139, 0, 0, g_gate_count * 21.3333f, 43);
	//Number_Draw(FLAG_NUM/10,234,128);													//�S�ẴQ�[�g���̕\���@10�̈�
	//Number_Draw(FLAG_NUM % 10, 262, 128);												//�S�ẴQ�[�g���̕\���@1�̈�
	//Number_Draw(g_gate_count/10, 152, 128);												//�ʉ߃Q�[�g���̕\���@10�̈�
	//Number_Draw(g_gate_count%10, 180, 128);												//�ʉ߃Q�[�g���̕\���@1�̈�

	int num;																			//���[�v�ŎZ�o�����e���̐�����ێ�����ϐ�
	int time = g_time * DECIMAL_POINT;													//�������炵�Ȃ���^�C����ێ�����ϐ��@�ŏ��Ƀ^�C�������R���ŕێ�
	for (int i = 0; i < TIME_DIGIT; i++)												//�\���������������[�v�@
	{
		num = time % 10;																//1�̈ʂ̐������Z�o
		Number_Draw(num,234-i*NUM_SPACE,55);													//�Z�o����������\��
		time = time / 10;																//���̌��̐������Z�o���邽�߂ɁA�������炷
		if (i == 2) {
			Sprite_Draw(g_period_tex, 244 - i * NUM_SPACE, 66);
		}
	}
	/*

	(67.0f, -64.0f, 441.0f);

	if (GoolGetCrear()) {
		Sprite_Draw(g_goal_tex, 500, 100);
	}
	*/
}

double Get_Time(void) 
{
	return g_time;
}



