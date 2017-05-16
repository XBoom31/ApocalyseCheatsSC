#pragma once
#include "stdafx.h"


class iClientClass
{
public:
	const char* iClientClass::GetName(void)
	{
		return *(char**)(this + 0x8);
	}
	RecvTable* iClientClass::GetTable()
	{
		return *(RecvTable**)(this + 0xC);
	}
	iClientClass* iClientClass::NextClass()
	{
		return *(iClientClass**)(this + 0x10);
	}
	int iClientClass::GetClassID(void)
	{
		return *(int*)(this + 0x14);
	}
	iClientClass* iClientClass::GetAllClasses(void)
	{
		typedef iClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 8)(this);
	}

};
class IClientNetworkable;
typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable*   (*CreateEventFn)();
class ClientClass {
public:
	CreateClientClassFn      m_pCreateFn;
	CreateEventFn            m_pCreateEventFn;
	char*                    m_pNetworkName;
	RecvTable*               m_pRecvTable;
	ClientClass*             m_pNext;
	int                      m_ClassID;
};


class HLCLient
{
public:
	ClientClass* GetAllClasses(VOID)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 8)(this);
	}
	int GetScreenWidth(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 63)(this);
	}
	int GetScreenHeight(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 64)(this);
	}
	void IN_DeactivateMouse(VOID)
	{
		typedef void(__thiscall* OriginalFn)(PVOID);
		getvfunc<OriginalFn>(this, 16)(this);
	}
};