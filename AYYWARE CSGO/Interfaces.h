/*
Syn's Apocalypse Framework
*/

#pragma once

// Includes
#include "CommonIncludes.h"
#include "SDK.h"

// Namespace to contain all the valve interfaces
class IClientModeShared
{
public:

};
namespace Interfaces
{
	// Gets handles to all the interfaces needed
	void Initialise();

	extern IBaseClientDLL* Client;
	extern IVEngineClient* Engine;
	extern IPanel* Panels;
	extern IClientEntityList* EntList;
	extern ISurface* Surface;
	extern IVDebugOverlay* DebugOverlay;
	extern IClientModeShared *clientmode;
	extern CGlobalVarsBase *Globals;
	extern DWORD *Prediction;
	extern DWORD *ClientMode;
	extern CMaterialSystem* MaterialSystem;
	extern CVRenderView* RenderView;
	extern IVModelRender* ModelRender;
	extern CModelInfo* ModelInfo;
	extern IEngineTrace* Trace;
	extern IPhysicsSurfaceProps* PhysProps;
	extern ICVar *CVar;
	extern CInput* pInput;
};
