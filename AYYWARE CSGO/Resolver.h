#pragma once

#include "Interfaces.h"
#include "Hacks.h"

namespace R
{
	void Resolve();
};

namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern bool change;
	extern int TargetID;
}