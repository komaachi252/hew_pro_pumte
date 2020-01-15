//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒ‰ƒCƒgˆ—[light.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 10/31(–Ø)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3d9.h>
#include <d3dx9.h>
#include "Direct3d.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static D3DLIGHT9 g_Light = {};  //  ƒ‰ƒCƒg\‘¢‘Ì

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Init(void)
{
	g_Light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(0.0f, -1.0f, 0.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&g_Light.Direction, &vecDirLight);

	g_Light.Diffuse.r = 1.0f;
	g_Light.Diffuse.g = 1.0f;
	g_Light.Diffuse.b = 1.0f;
	g_Light.Diffuse.a = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetLight(0, &g_Light);

	pDevice->LightEnable(0, TRUE);

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);  //  Šg‘åk¬‚Å‚à³í‚ÈŒõ‚É‚È‚é

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(32, 0, 100));

	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Uninit(void)
{


}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Update(void)
{

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Draw(void)
{

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒ‰ƒCƒgÝ’èˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Set_Light(void)
{

}
