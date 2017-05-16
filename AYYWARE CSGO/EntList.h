#pragma once
#include "stdafx.h"
class CBaseEntity;
class CEntityList
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual CBaseEntity*		GetClientEntity(int entnum);
	virtual CBaseEntity*		GetClientEntityFromHandle(HANDLE hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void);
	virtual void				SetMaxEntities(int maxents);
	virtual int					GetMaxEntities();
};