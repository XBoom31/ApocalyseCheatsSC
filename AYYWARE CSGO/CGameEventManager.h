#pragma once
#include "CGameEvent.h"

class IGameEventManager {
public:
	bool FireEventClientSide(IGameEvent* pEvent) {
		if (!pEvent)
			return false;
		cout << pEvent << endl;
		return getvfunc<bool(__thiscall *)(void*, IGameEvent*)>(this, 8)(this, pEvent);
	}
};