/*
Rest In Peace ApocalypseCheats
*/

// Credits to Valve and Shad0w
#include "Interfaces.h"
#include "Menu.h"

// Shad0ws Yaw fix
// (FIX ME UP LATER)
void FixY(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	static Vector vLast[65];
	static bool bShotLastTime[65];
	static bool bJitterFix[65];

	float *flPitch = (float*)((DWORD)pOut - 4);
	float flYaw = pData->m_Value.m_Float;
	bool bHasAA;
	bool bSpinbot;
	static bool last[128];
	bool tmp = last[((IClientEntity*)(pStruct))->GetIndex()];
	float yaw = pData->m_Value.m_Float;
	yaw -= 0.087929;

	switch (Menu::Window.RageBotTab.AccuracyResolver.GetIndex() == 5)
	{
	case 0:
		// No resolver needed
		break;
	case 1:
		// Normal Fix
		yaw -= 0.087929;

		last[((IClientEntity*)(pStruct))->GetIndex()] = (yaw >= 180 && yaw <= 360);

		if (tmp && (yaw >= 0 && yaw <= 180))
			yaw += 359;

		yaw -= (int)(yaw / 360) * 360;
		if (yaw < -180)
			yaw += 360;
		else if (yaw > 180)
			yaw -= 360;

		break;
	case 2:
		// Anglefix
		bHasAA = ((*flPitch == 90.0f) || (*flPitch == 270.0f));
		bSpinbot = false;

		if (!bShotLastTime[((IClientEntity*)(pStruct))->GetIndex()]
			&& (fabsf(flYaw - vLast[((IClientEntity*)(pStruct))->GetIndex()].y) > 15.0f) && !bHasAA)
		{
			flYaw = vLast[((IClientEntity*)(pStruct))->GetIndex()].y;
			bShotLastTime[((IClientEntity*)(pStruct))->GetIndex()] = true;
		}
		else
		{
			if (bShotLastTime[((IClientEntity*)(pStruct))->GetIndex()]
				&& (fabsf(flYaw - vLast[((IClientEntity*)(pStruct))->GetIndex()].y) > 15.0f))
			{
				bShotLastTime[((IClientEntity*)(pStruct))->GetIndex()] = true;
				bSpinbot = true;
			}
			else
			{
				bShotLastTime[((IClientEntity*)(pStruct))->GetIndex()] = false;
			}
		}

		vLast[((IClientEntity*)(pStruct))->GetIndex()].y = flYaw;


		bool bTmp = bJitterFix[((IClientEntity*)(pStruct))->GetIndex()];

		bJitterFix[((IClientEntity*)(pStruct))->GetIndex()] = (flYaw >= 180.0f && flYaw <= 360.0f);

		if (bTmp && (flYaw >= 0.0f && flYaw <= 180.0f))
		{
			flYaw += 359.0f;
		}
		break;
	}

	*(float*)(pOut) = flYaw;
}

// Simple fix for some Fake-Downs
void FixX(const CRecvProxyData* pData, void* pStruct, void* pOut) // Clamp other player angles to fix fakedown or lisp
{
	float* ang = (float*)pOut;
	*ang = pData->m_Value.m_Float;
	DWORD hex = *(DWORD*)(&ang);

	switch (Menu::Window.RageBotTab.AccuracyResolver.GetIndex() == 5)
	{
	case 0:
		// No resolver needed
		break;
	case 1:
		// Regular Pitch Resolver
		if (hex >= 0x43330000)
		{
			*ang -= 360.f;
		}
		else if (hex <= -0x43330000)
		{
			*ang += 360.f;
		}

		if (hex == 0x42b40000)
		{
			*ang = 90.f;
		}
		else if (hex == -0x42b40000)
		{
			*ang = -90.f;
		}

		*(float*)(pOut) = *ang;
		break;
	case 2:
		if (pData->m_Value.m_Float > 180.0f)
			*ang -= 360.0f;
		else if (pData->m_Value.m_Float < -180.0f)
			*ang += 360.0f; 
		break;
	}
}

RecvVarProxyFn oRecvnModelIndex;

void Hooked_RecvProxy_Viewmodel(CRecvProxyData *pData, void *pStruct, void *pOut)
{
	// Get the knife view model id's
	static int default_t = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	static int default_ct = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	static int bayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	static int karam = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	
	static int bayon = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	static int Hunts = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	static int fchion = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	
	static int iBowie = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
	static int flip = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	static int gut = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	static int butter = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	static int daggers = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	/*
	int iBayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
			int iButterfly = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
			int iFlip = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
			int iGut = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
			int iKarambit = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			int iM9Bayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			int iHuntsman = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
			int iFalchion = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
			int iDagger = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
			int iBowie = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
	*/
	// Get local player (just to stop replacing spectators knifes)
	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (Menu::Window.MiscTab.KnifeEnable.GetState() && pLocal)
	{
		// If we are alive and holding a default knife(if we already have a knife don't worry about changing)
		if (pLocal->IsAlive() && (pData->m_Value.m_Int == default_t || pData->m_Value.m_Int == default_ct))
		{
			// Set whatever knife we want
			if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 0)
				pData->m_Value.m_Int = karam;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 1)
				pData->m_Value.m_Int = bayonet;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 2)
				pData->m_Value.m_Int = bayon;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 3)
				pData->m_Value.m_Int = flip;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 4)
				pData->m_Value.m_Int = gut;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 5)
				pData->m_Value.m_Int = Hunts;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 6)
				pData->m_Value.m_Int = fchion;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 7)
				pData->m_Value.m_Int = iBowie;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 8)
				pData->m_Value.m_Int = butter;
			else if (Menu::Window.MiscTab.KnifeModel.GetIndex() == 9)
				pData->m_Value.m_Int = daggers;
			
		}
	}

	// Carry on the to original proxy
	oRecvnModelIndex(pData, pStruct, pOut);
}

void ApplyAAAHooks()
{
	ClientClass *pClass = Interfaces::Client->GetAllClasses();
	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;
		if (!strcmp(pszName, "DT_CSPlayer"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
				const char *name = pProp->m_pVarName;

				// Pitch Fix
				if (!strcmp(name, "m_angEyeAngles[0]"))
				{
					pProp->m_ProxyFn = FixX;
				}

				// Yaw Fix
				if (!strcmp(name, "m_angEyeAngles[1]"))
				{
					Utilities::Log("Yaw Fix Applied");
					pProp->m_ProxyFn = FixY;
				}
			}
		}
		else if (!strcmp(pszName, "DT_BaseViewModel"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
				const char *name = pProp->m_pVarName;

				// Knives
				if (!strcmp(name, "m_nModelIndex"))
				{
					oRecvnModelIndex = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = Hooked_RecvProxy_Viewmodel;
				}
			}
		}
		pClass = pClass->m_pNext;
	}
}