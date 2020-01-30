//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	���f���c���[�w�b�_[model_tree.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 1/17(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef MODEL_TREE_H_
#define MODEL_TREE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X��`
//��������������������������������������������������������������������������������
struct Model_Tree
{
	std::string name;
	D3DXMATRIX mtx; //
	int child_index;
	int sibling_index;
	D3DXVECTOR3 offset;
	D3DXVECTOR3 initrot;
	int model_id;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
};

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Model_Tree_Init(Model_Tree model_tree[], int num);
void Model_Tree_Destroy(Model_Tree model_tree[], int num);
void Model_Tree_Draw(Model_Tree* p_model_tree, D3DXMATRIX* p_mtx);

#endif // MODEL_TREE_H_
