/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "MiscDefinitions.h"
#include "ClientRecvProps.h"
#include "offsets.h"
#include "Vector.h"

// EngineClient
class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* oGetScreenSize)(PVOID, int&, int&);
		return call_vfunc< oGetScreenSize >(this, Offsets::VMT::Engine_GetScreenSize)(this, width, height);
	}
	bool GetPlayerInfo(int ent_num, player_info_t *pinfo)
	{
		typedef bool(__thiscall* oGetPlayerInfo)(PVOID, int, player_info_t*);
		return call_vfunc< oGetPlayerInfo >(this, Offsets::VMT::Engine_GetPlayerInfo)(this, ent_num, pinfo);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall* oLocal)(PVOID);
		return call_vfunc< oLocal >(this, Offsets::VMT::Engine_GetLocalPlayer)(this);
	}

	float Time()
	{
		typedef float(__thiscall* oTime)(PVOID);
		return call_vfunc< oTime >(this, Offsets::VMT::Engine_Time)(this);
	}
	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
		return call_vfunc< oSetViewAngles >(this, Offsets::VMT::Engine_GetViewAngles)(this, vAngles);
	}
	void SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
		return call_vfunc< oSetViewAngles >(this, Offsets::VMT::Engine_SetViewAngles)(this, vAngles);
	}
	int GetMaxClients()
	{
		typedef bool(__thiscall* oGetMaxClients)(PVOID);
		return call_vfunc< oGetMaxClients >(this, Offsets::VMT::Engine_GetMaxClients)(this);
	}
	bool IsConnected()
	{
		typedef bool(__thiscall* oGetScreenSize)(PVOID);
		return call_vfunc< oGetScreenSize >(this, Offsets::VMT::Engine_IsConnected)(this);
	}
	bool IsInGame()
	{
		typedef bool(__thiscall* oLocal)(PVOID);
		return call_vfunc< oLocal >(this, Offsets::VMT::Engine_IsInGame)(this);
	}
	const matrix3x4& WorldToScreenMatrix()
	{
		typedef const matrix3x4& (__thiscall* oWorldToScreenMatrix)(PVOID);
		return call_vfunc< oWorldToScreenMatrix >(this, Offsets::VMT::Engine_WorldToScreenMatrix)(this);
	}
	void ClientCmd_Unrestricted(char  const* cmd)
	{
		typedef void(__thiscall* oClientCmdUnres)(PVOID, const char*);
		return call_vfunc<oClientCmdUnres>(this, Offsets::VMT::Engine_ClientCmd_Unrestricted)(this, cmd);
	}
};