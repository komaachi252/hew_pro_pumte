//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[Result_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 12/17(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "input.h"
#include "fade.h"
#include "scene.h"
#include <d3d9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
class Result_Manager
{
private:
	//	�萔��`
	static const int FADE_FRAME = 60;
	static const D3DCOLOR FADE_COLOR;
	//	�ϐ���`
	bool m_is_fade;
public:
	Result_Manager();
	virtual ~Result_Manager();
	void Update();
};

const D3DCOLOR Result_Manager::FADE_COLOR = D3DCOLOR_RGBA(0,0,0,0);
//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Result_Manager* gp_manager = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Result_Manager_Init(void)
{
	gp_manager = new Result_Manager;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Result_Manager_Uninit(void)
{
	delete gp_manager;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Result_Manager_Update(void)
{
	gp_manager->Update();
}

//��������������������������������������������������������������������������������
//	�R���X�g���N�^
//��������������������������������������������������������������������������������
Result_Manager::Result_Manager(void):m_is_fade(false)
{
}

//��������������������������������������������������������������������������������
//	�f�X�g���N�^
//��������������������������������������������������������������������������������
Result_Manager::~Result_Manager(void)
{
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Result_Manager::Update(void)
{
	if (Keyboard_IsTrigger(DIK_SPACE) && !m_is_fade) {
		Fade_Start(FADE_FRAME, FADE_COLOR, true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_TITLE);
	}
}