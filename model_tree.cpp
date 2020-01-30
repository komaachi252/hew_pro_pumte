//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�K�w�\���t�����f������[model_tree.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/17(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "model_tree.h"
#include "model.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������

//armored vehicle

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Model_Tree_Draw(Model_Tree* p_model_tree, int index, D3DXMATRIX* p_mtx);


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
//static Model_Tree g_armored_vehicle[9] = {};

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Model_Tree_Init(Model_Tree model_tree[], int num)
{
	//	���f���c���[�̃t�@�C�����Ń��f����ǂݍ���
	for (int i = 0; i < num; i++) {
		model_tree[i].model_id = Model_Load(model_tree[i].name.c_str());
	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Model_Tree_Destroy(Model_Tree model_tree[], int num)
{
	//	���f���f�[�^���
	for (int i = 0; i < num; i++) {
		Model_Destroy(&model_tree[i].model_id, 1);
		model_tree[i].model_id = -1; // �g�p�s�\�ɂ���
	}
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Model_Tree_Draw(Model_Tree* p_model_tree, D3DXMATRIX* p_mtx)
{
	D3DXMATRIX mtx_trans, mtx_rot;

	// �����̎p�������
	D3DXMatrixTranslation(&mtx_trans, p_model_tree->offset.x + p_model_tree->position.x,
									  p_model_tree->offset.y + p_model_tree->position.y,
									  p_model_tree->offset.z + p_model_tree->position.z);

	D3DXMatrixRotationYawPitchRoll(&mtx_rot, p_model_tree->initrot.y + p_model_tree->rotation.y,
											 p_model_tree->initrot.x + p_model_tree->rotation.x, 
											 p_model_tree->initrot.z + p_model_tree->rotation.z);
	p_model_tree->mtx = mtx_rot * mtx_trans * (*p_mtx);

	// �`��
	Model_Draw(p_model_tree->model_id, p_model_tree->mtx);

	//   �Z��
	if (p_model_tree->sibling_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree->sibling_index, p_mtx);
	}
	//   �q�ǂ�
	if (p_model_tree->child_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree->child_index, &p_model_tree->mtx);
	}
}

//��������������������������������������������������������������������������������
//	�ċA�p�`�揈��
//��������������������������������������������������������������������������������
void Model_Tree_Draw(Model_Tree* p_model_tree, int index, D3DXMATRIX* p_mtx)
{
	D3DXMATRIX mtx_trans, mtx_rot;

	// �����̎p�������
	D3DXMatrixTranslation(&mtx_trans, p_model_tree[index].offset.x + p_model_tree[index].position.x,
									  p_model_tree[index].offset.y + p_model_tree[index].position.y,
									  p_model_tree[index].offset.z + p_model_tree[index].position.z);

	D3DXMatrixRotationYawPitchRoll(&mtx_rot, p_model_tree[index].initrot.y + p_model_tree[index].rotation.y,
											 p_model_tree[index].initrot.x + p_model_tree[index].rotation.x, 
											 p_model_tree[index].initrot.z + p_model_tree[index].rotation.z);
	p_model_tree[index].mtx = mtx_rot * mtx_trans * (*p_mtx);

	// �`��
	Model_Draw(p_model_tree[index].model_id, p_model_tree[index].mtx);

	//   �Z��
	if (p_model_tree[index].sibling_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree[index].sibling_index, p_mtx);
	}
	//   �q�ǂ�
	if (p_model_tree[index].child_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree[index].child_index, &p_model_tree->mtx);
	}
}
