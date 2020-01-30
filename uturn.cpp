//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�t�^�[������[uturn.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/25(�y)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "model.h"
#include <d3dx9.h>
#include "player.h"
#include "scene.h"
#include "fade.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
class Uturn
{
private:

	enum STATE 
	{
		NONE,
		POP,
		WAIT,
		BACK
	};
	STATE m_state;
	int m_model_id;
	D3DXVECTOR3 m_pos;
	float m_y;
	D3DXVECTOR3 m_p_front;
	float m_sin;
	bool m_is_used;
	float m_angle;
	int m_frame;
public:
	Uturn(void);
	~Uturn(void);
	void Update(void);
	void Draw(void);
	void Create(void);
	void Pop(void);
	void Wait(void);
	void Back(void);
	bool Is_Used(void);
};

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Uturn* gp_u = nullptr;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Uturn_Init(void)
{
	gp_u = new Uturn();
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Uturn_Uninit(void)
{
	delete gp_u;
	gp_u = nullptr;

}

static bool m_is_fade = false;
//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Uturn_Update(void)
{
	
	
	gp_u->Update();
	if (Keyboard_IsTrigger(DIK_RETURN) && !m_is_fade) {
		Fade_Start(30, D3DCOLOR_RGBA(1, 1, 1, 1), true);
		m_is_fade = true;
	}
	if (m_is_fade && !Fade_IsFade()) {
		Set_Scene(SCENE_RESULT);
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn_Draw(void)
{
	gp_u->Draw();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn_Create(void)
{
	gp_u->Create();
}



//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
Uturn::Uturn(void)
{
	m_model_id = Model_Load("oct.x");
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_state = NONE;

	m_sin = 0.0f;

	m_is_used = false;

	m_angle = 0.0f;

	m_is_fade = false;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
Uturn::~Uturn(void)
{
	Model_Destroy(&m_model_id, 1);
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Update(void)
{
	if (!m_is_used) {
		return;
	}
	switch (m_state)
	{
	case Uturn::NONE:
		break;
	case Uturn::POP:
		Pop();
		break;
	case Uturn::WAIT:
		Wait();
		break;
	case Uturn::BACK:
		Back();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Draw(void)
{
	if (!m_is_used) {
		return;
	}
	D3DXMATRIX mtx_rot, mtx_trans;


	D3DXVECTOR3 front_inv = m_p_front * -1.0f;
	D3DXVECTOR3 p_vec = *Get_Player_Front();


	m_angle = atan2(p_vec.z, p_vec.x);

	D3DXMatrixTranslation(&mtx_trans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&mtx_rot, -m_angle + D3DXToRadian(180));

	mtx_trans = mtx_rot * mtx_trans;

	Model_Draw(m_model_id, mtx_trans);

}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Create(void)
{
	if (m_is_used) {
		return;
	}

	D3DXVECTOR3 p = *Get_Player_Pos();
	D3DXVECTOR3 p_vec = *Get_Player_Front();

	
	m_pos = p + p_vec * 3;

	m_pos.y = p.y + 5.0f;

	m_y = m_pos.y;

	m_state = POP;

	m_p_front = p_vec;

	m_is_used = true;

	m_angle = 0.0f;

	m_frame = 0;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Pop(void)
{

	D3DXVECTOR3 p = *Get_Player_Pos();
	D3DXVECTOR3 p_vec = *Get_Player_Front();
	m_pos = p + p_vec * 3;

	m_y -= 0.1f;

	m_pos.y = m_y;

	if (m_y <= p.y + 1.2f) {
		m_state = WAIT;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Wait(void)
{
	m_sin += 0.05f;

	D3DXVECTOR3 p = *Get_Player_Pos();
	D3DXVECTOR3 p_vec = *Get_Player_Front();
	m_pos = p + p_vec * 3;

	m_y += sinf(m_sin) * 0.02f;

	m_pos.y = m_y;

	float angle = acosf(D3DXVec3Dot(&m_p_front, &p_vec));

	if (fabs(angle) >= D3DXToRadian(160)) {
		m_state = BACK;
	}
	
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Uturn::Back(void)
{
	D3DXVECTOR3 p = *Get_Player_Pos();
	D3DXVECTOR3 p_vec = *Get_Player_Front();
	m_pos = p + p_vec * 3;

	m_y += 0.05f;

	m_pos.y = m_y;

	if (m_y >= p.y + 8.0f) {
		m_is_used = false;
		m_state = NONE;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
bool Uturn::Is_Used(void)
{
	return m_is_used;
}

bool Uturn_Is_Used(void)
{
	return gp_u->Is_Used();
}

