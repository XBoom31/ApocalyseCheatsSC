/*
Rest In Peace ApocalypseCheats
*/

#pragma once

// It's actually in DLLMain but w/e
extern bool DoUnload;

#include "Utilities.h"
#include "Hacks.h"


namespace Hooks
{
	void Initialise();
	void UndoHooks();
	
	class HooksXD;
	// VMT Managers
	extern Utilities::Memory::VMTManager VMTPanel; // Hooking drawing functions
	extern Utilities::Memory::VMTManager VMTClient; // Maybe CreateMove
	extern Utilities::Memory::VMTManager VMTClientMode; // CreateMove for functionality
	extern Utilities::Memory::VMTManager VMTModelRender; // DrawModelEx for chams
	extern Utilities::Memory::VMTManager VMTPrediction; // InPrediction for no vis recoil
	extern Utilities::Memory::VMTManager VMTPlaySound; // Autoaccept shit
	extern Utilities::Memory::VMTManager VMTRenderView;
	
};
class HooksXD
{
public:
	static void XD3();
	static int night;
	static int night2;
};
//void XD3();


