#pragma once
#include "stdafx.h"

class IMoveHelper
{
public:
	void SetHost(CBaseEntity *pPlayer)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity *pPlayer);
		getvfunc<OriginalFn>(this, 1)(this, pPlayer);
	}
};

//class CPrediction
//{
//public:
//	void SetupMove(CBaseEntity *player, CInput::CUserCmd *ucmd, PVOID empty, PVOID moveData);
//	void FinishMove(CBaseEntity *player, CInput::CUserCmd *ucmd, PVOID moveData);
//};

class CGameMovement
{
public:
	void ProcessMovement(CBaseEntity *pPlayer, PVOID moveData)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity *pPlayer, PVOID moveData);
		getvfunc<OriginalFn>(this, 1)(this, pPlayer, moveData);
	}
	void DecayPunchAngles()
	{
		typedef void(__thiscall* OriginalFn)(PVOID);
		getvfunc<OriginalFn>(this, 17)(this);	
	}
};