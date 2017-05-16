#pragma once
#include "stdafx.h"
class CDebugOverlay
{
public:
	int CDebugOverlay::ScreenPosition(const Vector& vecOrigin, Vector& vecScreen)
	{
		typedef int(__thiscall* ScreenPosition_t)(PVOID, const Vector&, Vector&);
		return getvfunc< ScreenPosition_t >(this, 13)(this, vecOrigin, vecScreen);
	}
};