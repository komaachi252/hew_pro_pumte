//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	処理[model.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 11/14(木)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#define _CRT_SECURE_NO_WARNINGS
#include <d3dx9.h>
#include <d3d9.h>
#include "texture.h"
#include "direct3d.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define MODEL_FILE_PATH ("Asset/Texture/")  //  モデルデータまでの相対パス
#define MODEL_MAX (36)  //  モデル個数
#define MODEL_FILE_LEN (256)

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
struct Model{
	char fliename[MODEL_FILE_LEN];
	LPD3DXMESH pMesh; //  メッシュ情報 複数なら複数必要
	DWORD MaterialCount; //  マテリアルの数
	LPD3DXBUFFER pMaterials;  //  マテリアルの情報格納用
	int* TextureIds;  //  テクスチャ管理番号保存用
};

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static Model* g_pModel = nullptr;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Init(void)
{
	g_pModel = new Model[MODEL_MAX];

	for (int i = 0; i < MODEL_MAX; i++) {
		g_pModel[i].fliename[0] = '\0';  //  文字列を初期化
		g_pModel[i].pMesh = nullptr;
		g_pModel[i].MaterialCount = 0;
		g_pModel[i].pMaterials = nullptr;
		g_pModel[i].TextureIds = nullptr;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	モデル読み込み処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
int Model_Load(const char* pFilename)
{
	//同じファイル名を探す
	for (int i = 0; i < MODEL_MAX; i++) {
		if (strcmp(g_pModel[i].fliename, pFilename) == 0) {//同じファイルを見つけた
			return i;//予約番号を返す
		}
	}
	//新規登録
	for (int i = 0; i < MODEL_MAX; i++) {
		//使用されていない場所を探す
		if (g_pModel[i].fliename[0] != 0) {//配列最初が\0
			continue;//前のfor文に戻る
		}
		//モデル読み込み
		strcpy(g_pModel[i].fliename, pFilename);

		char buf[MODEL_FILE_LEN];  //  ファイルパス連結用変数

		strcpy(buf, MODEL_FILE_PATH);

		strcat(buf, g_pModel[i].fliename);

		LPDIRECT3DDEVICE9 pDevice = GetDevice();  //  デバイスの取得

		HRESULT hr = D3DXLoadMeshFromX(buf, D3DXMESH_MANAGED, pDevice, nullptr, &g_pModel[i].pMaterials, nullptr,
									 &g_pModel[i].MaterialCount, &g_pModel[i].pMesh);  //  読めなかったらオプションを疑う
		if (FAILED(hr)) {
			MessageBox(nullptr, "モデル読み込みに失敗しました", "失敗", MB_OK);
			exit(1);
		}

		g_pModel[i].TextureIds = new int[g_pModel[i].MaterialCount];

		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[i].pMaterials->GetBufferPointer();

		//  各マテリアル情報を取得
		for (unsigned int j = 0; j < g_pModel[i].MaterialCount; j++) {
			//  色の取得
			//pMat[i].MatD3D.Diffuse

			//  テクスチャの読み込み
			if (pMat[j].pTextureFilename == nullptr) {
				//  ないとき
				g_pModel[i].TextureIds[j] = -1;  //  読み込めてないという証拠  Texture.cppで-1に対応させる
			}
			else {
				//  ファイル名の加工 パスの追加 ファイル名出ないように

				strcpy(buf, MODEL_FILE_PATH);
				strcat(buf, pMat[j].pTextureFilename);
				g_pModel[i].TextureIds[j] = Texture_SetLoadFile(buf, 0, 0);  //  テクスチャ開放
			}
		}
		Texture_Load();

		return i;
	}
	return -1;//空きがないよ

}


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	指定モデル破棄処理 
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (g_pModel[ids[i]].fliename[0] == '\0') {
			continue;
		}
		g_pModel[ids[i]].fliename[0] = '\0';
		g_pModel[ids[i]].pMesh = nullptr;
		g_pModel[ids[i]].MaterialCount = 0;
		g_pModel[ids[i]].pMaterials = nullptr;
		delete[] g_pModel[ids[i]].TextureIds;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	全モデル破棄処理 
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Destroy(void)
{
	for (int i = 0; i < MODEL_MAX; i++) {
		if (g_pModel[i].fliename[0] == '\0') {
			continue;
		}
		g_pModel[i].fliename[0] = '\0';
		g_pModel[i].pMesh = nullptr;
		g_pModel[i].MaterialCount = 0;
		g_pModel[i].pMaterials = nullptr;
		delete[] g_pModel[i].TextureIds;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理 テクスチャ予約番号を引数に単位行列で表示
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Draw(int idx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DMATERIAL9 mat = {}; // マテリアル設定用

	for (DWORD i = 0; i < g_pModel[idx].MaterialCount; i++) {
		//  マテリアル設定
		if (g_pModel[idx].TextureIds[i] < 0) {
			//  マテリアルカラーのみ
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[idx].pMaterials->GetBufferPointer();

			//  マテリアル情報を代入
			mat.Diffuse = pMat->MatD3D.Diffuse;
			mat.Ambient = pMat->MatD3D.Ambient;
			mat.Specular = pMat->MatD3D.Specular;
			mat.Emissive = pMat->MatD3D.Emissive;
			mat.Power = pMat->MatD3D.Power;

			//  マテリアルをデバイスに設定
			pDevice->SetMaterial(&mat);
		}
		else {
			mat.Diffuse.r = 1.0;
			mat.Diffuse.b = 1.0;
			mat.Diffuse.g = 1.0;
			mat.Diffuse.a = 1.0;

			pDevice->SetMaterial(&mat);
			//  マテリアルカラーを白にしてテクスチャを貼る
			pDevice->SetTexture(0, Texture_GetTexture(g_pModel[idx].TextureIds[i]));
		}
		//  メッシュ描画
		g_pModel[idx].pMesh->DrawSubset(i);
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理 テクスチャ予約番号を引数に
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Draw(int idx, const D3DXMATRIX& mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	for (DWORD i = 0; i < g_pModel[idx].MaterialCount; i++) {
		//  マテリアル設定
		if (g_pModel[idx].TextureIds[i] < 0) {
			//  マテリアルカラーのみ
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pModel[idx].pMaterials->GetBufferPointer();
			D3DMATERIAL9 mat = {};

			//  マテリアル情報を代入
			mat.Diffuse = pMat->MatD3D.Diffuse;
			mat.Ambient = pMat->MatD3D.Ambient;
			mat.Specular = pMat->MatD3D.Specular;
			mat.Emissive = pMat->MatD3D.Emissive;
			mat.Power = pMat->MatD3D.Power;

			//  マテリアルをデバイスに設定
			pDevice->SetMaterial(&mat);
		}
		else {
			//  マテリアルカラーを白にしてテクスチャを貼る
			pDevice->SetTexture(0, Texture_GetTexture(g_pModel[idx].TextureIds[i]));
		}
		//  メッシュ描画
		g_pModel[idx].pMesh->DrawSubset(i);
	}
}



//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Model_Uninit(void)
{
	delete[] g_pModel;
}

