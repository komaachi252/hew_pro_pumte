//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒ‚ƒfƒ‹ƒcƒŠ[ƒwƒbƒ_[model_tree.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 1/17(‹à)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef MODEL_TREE_H_
#define MODEL_TREE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒX’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Model_Tree_Init(Model_Tree model_tree[], int num);
void Model_Tree_Destroy(Model_Tree model_tree[], int num);
void Model_Tree_Draw(Model_Tree* p_model_tree, D3DXMATRIX* p_mtx);

#endif // MODEL_TREE_H_
