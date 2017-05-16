/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "MiscDefinitions.h"
#include "ClientRecvProps.h"
#include "offsets.h"

class IBaseClientDLL
{
public:

	ClientClass* GetAllClasses(void)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID); //Anything inside a VTable is a __thiscall unless it completly disregards the thisptr. You can also call them as __stdcalls, but you won't have access to the __thisptr.
		return call_vfunc<OriginalFn>(this, Offsets::VMT::CHL_GetAllClasses)(this); //Return the pointer to the head CClientClass.
	}
};