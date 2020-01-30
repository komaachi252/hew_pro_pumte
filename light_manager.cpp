//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒ‰ƒCƒgˆ—[light_manager.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 1/10(‹à)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static D3DLIGHT9 g_Light = {};  //  ƒ‰ƒCƒg\‘¢‘Ì


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Manager_Init(void)
{
	g_Light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(0.0f, -1.0f, 1.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&g_Light.Direction, &vecDirLight);

	g_Light.Diffuse.r = 1.0f;
	g_Light.Diffuse.g = 1.0f;
	g_Light.Diffuse.b = 1.0f;
	g_Light.Diffuse.a = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetLight(0, &g_Light);

	pDevice->LightEnable(0, TRUE);

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1); //  D3DMCS_MATERAL

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);  //  Šg‘åk¬‚Å‚à³í‚ÈŒõ‚É‚È‚é

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(102, 100, 100));

	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR2);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Manager_Uninit(void)
{


}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Manager_Update(void)
{
	g_Light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(0.0f, -1.0f, 1.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&g_Light.Direction, &vecDirLight);

	g_Light.Diffuse.r = 1.0f;
	g_Light.Diffuse.g = 1.0f;
	g_Light.Diffuse.b = 1.0f;
	g_Light.Diffuse.a = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetLight(0, &g_Light);

	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1); //  D3DMCS_MATERAL

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);  //  Šg‘åk¬‚Å‚à³í‚ÈŒõ‚É‚È‚é

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(102, 100, 100));

	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR2);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Light_Manager_Draw(void)
{

}
