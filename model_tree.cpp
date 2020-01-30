//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	階層構造付きモデル処理[model_tree.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 1/17(金)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include "model_tree.h"
#include "model.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆

//armored vehicle

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Tree_Draw(Model_Tree* p_model_tree, int index, D3DXMATRIX* p_mtx);


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//static Model_Tree g_armored_vehicle[9] = {};

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Tree_Init(Model_Tree model_tree[], int num)
{
	//	モデルツリーのファイル名でモデルを読み込む
	for (int i = 0; i < num; i++) {
		model_tree[i].model_id = Model_Load(model_tree[i].name.c_str());
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Tree_Destroy(Model_Tree model_tree[], int num)
{
	//	モデルデータ解放
	for (int i = 0; i < num; i++) {
		Model_Destroy(&model_tree[i].model_id, 1);
		model_tree[i].model_id = -1; // 使用不能にする
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Tree_Draw(Model_Tree* p_model_tree, D3DXMATRIX* p_mtx)
{
	D3DXMATRIX mtx_trans, mtx_rot;

	// 自分の姿勢を作る
	D3DXMatrixTranslation(&mtx_trans, p_model_tree->offset.x + p_model_tree->position.x,
									  p_model_tree->offset.y + p_model_tree->position.y,
									  p_model_tree->offset.z + p_model_tree->position.z);

	D3DXMatrixRotationYawPitchRoll(&mtx_rot, p_model_tree->initrot.y + p_model_tree->rotation.y,
											 p_model_tree->initrot.x + p_model_tree->rotation.x, 
											 p_model_tree->initrot.z + p_model_tree->rotation.z);
	p_model_tree->mtx = mtx_rot * mtx_trans * (*p_mtx);

	// 描画
	Model_Draw(p_model_tree->model_id, p_model_tree->mtx);

	//   兄弟
	if (p_model_tree->sibling_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree->sibling_index, p_mtx);
	}
	//   子ども
	if (p_model_tree->child_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree->child_index, &p_model_tree->mtx);
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	再帰用描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Tree_Draw(Model_Tree* p_model_tree, int index, D3DXMATRIX* p_mtx)
{
	D3DXMATRIX mtx_trans, mtx_rot;

	// 自分の姿勢を作る
	D3DXMatrixTranslation(&mtx_trans, p_model_tree[index].offset.x + p_model_tree[index].position.x,
									  p_model_tree[index].offset.y + p_model_tree[index].position.y,
									  p_model_tree[index].offset.z + p_model_tree[index].position.z);

	D3DXMatrixRotationYawPitchRoll(&mtx_rot, p_model_tree[index].initrot.y + p_model_tree[index].rotation.y,
											 p_model_tree[index].initrot.x + p_model_tree[index].rotation.x, 
											 p_model_tree[index].initrot.z + p_model_tree[index].rotation.z);
	p_model_tree[index].mtx = mtx_rot * mtx_trans * (*p_mtx);

	// 描画
	Model_Draw(p_model_tree[index].model_id, p_model_tree[index].mtx);

	//   兄弟
	if (p_model_tree[index].sibling_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree[index].sibling_index, p_mtx);
	}
	//   子ども
	if (p_model_tree[index].child_index >= 0){
		Model_Tree_Draw(p_model_tree, p_model_tree[index].child_index, &p_model_tree->mtx);
	}
}
