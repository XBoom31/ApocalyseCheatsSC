/*
ApocalypseCheats
*/

#include "Interfaces.h"
#include "Utilities.h"

//SDK Specific Definitions
typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
//DWORD Offsets::Modules::InputLib;
//Some globals for later
CreateInterface_t EngineFactory = NULL; // These are used to store the individual
CreateInterface_t ClientFactory = NULL; //  CreateInterface functions for each game
CreateInterface_t VGUISurfaceFactory = NULL; //  dll that we need access to. Can call
CreateInterface_t VGUI2Factory = NULL; //  them to recieve pointers to game classes.
CreateInterface_t MatFactory = NULL;
CreateInterface_t PhysFactory = NULL;
CreateInterface_t StdFactory = NULL;
CreateInterface_t InputFactory = NULL;


void Interfaces::Initialise()
{

	//Get function pointers to the CreateInterface function of each module
	EngineFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Engine, "CreateInterface");
	ClientFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Client, "CreateInterface");
	VGUI2Factory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VGUI2, "CreateInterface");
	VGUISurfaceFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VGUISurface, "CreateInterface");
	MatFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Material, "CreateInterface");
	PhysFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VPhysics, "CreateInterface");
	StdFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Stdlib, "CreateInterface");
	InputFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::InputLib, "CreateInterface");

	//Get the interface names regardless of their version number by scanning for each string
	char* CHLClientInterfaceName = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClient0");
	char* VGUI2PanelsInterfaceName = (char*)Utilities::Memory::FindTextPattern("vgui2.dll", "VGUI_Panel0");
	char* VGUISurfaceInterfaceName = (char*)Utilities::Memory::FindTextPattern("vguimatsurface.dll", "VGUI_Surface0");
	char* EntityListInterfaceName = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClientEntityList0");
	char* EngineDebugThingInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VDebugOverlay0");
	char* EngineClientInterfaceName = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineClient0");
	char* ClientPredictionInterface = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClientPrediction0");
	char* MatSystemInterfaceName = (char*)Utilities::Memory::FindTextPattern("materialsystem.dll", "VMaterialSystem0");
	char* EngineRenderViewInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineRenderView0");
	char* EngineModelRenderInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineModel0");
	char* EngineModelInfoInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VModelInfoClient0");
	char* EngineTraceInterfaceName = (char*)Utilities::Memory::FindTextPattern("engine.dll", "EngineTraceClient0");
	char* PhysPropsInterfaces = (char*)Utilities::Memory::FindTextPattern("client.dll", "VPhysicsSurfaceProps0");
	char* VEngineCvarName = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineCvar00");
	char* SInputSystem = (char*)Utilities::Memory::FindTextPattern("inputsystem.dll", "InputSystemVersion001");


	MaterialSystem = reinterpret_cast<CMaterialSystem*>(Utilities::Memory::CaptureInterface(XorStr("materialsystem.dll"), XorStr("VMaterialSystem")));
	printf("0x%X\n", reinterpret_cast<DWORD>(MaterialSystem));

	// Use the factory function pointers along with the interface versions to grab
	//  pointers to the interfaces
	Client = (IBaseClientDLL*)ClientFactory(CHLClientInterfaceName, NULL);
	Engine = (IVEngineClient*)EngineFactory(EngineClientInterfaceName, NULL);
	Panels = (IPanel*)VGUI2Factory(VGUI2PanelsInterfaceName, NULL);
	Surface = (ISurface*)VGUISurfaceFactory(VGUISurfaceInterfaceName, NULL);
	EntList = (IClientEntityList*)ClientFactory(EntityListInterfaceName, NULL);
	DebugOverlay = (IVDebugOverlay*)EngineFactory(EngineDebugThingInterface, NULL);
	Prediction = (DWORD*)ClientFactory(ClientPredictionInterface, NULL);
	MaterialSystem = (CMaterialSystem*)MatFactory(MatSystemInterfaceName, NULL);
	RenderView = (CVRenderView*)EngineFactory(EngineRenderViewInterface, NULL);
	ModelRender = (IVModelRender*)EngineFactory(EngineModelRenderInterface, NULL);
	ModelInfo = (CModelInfo*)EngineFactory(EngineModelInfoInterface, NULL);
	Trace = (IEngineTrace*)EngineFactory(EngineTraceInterfaceName, NULL);
	PhysProps = (IPhysicsSurfaceProps*)PhysFactory(PhysPropsInterfaces, NULL);
	CVar = (ICVar*)StdFactory(VEngineCvarName, NULL);
	ClientMode = **(IClientModeShared***)((*(DWORD**)Interfaces::Client)[10] + 0x5);
	InputSystem = (IInputSystem*)InputFactory(SInputSystem, NULL);
	// Get ClientMode Pointer
	DWORD p = Utilities::Memory::FindPattern("client.dll", (BYTE*)"\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xA8\x01\x75\x1A\x83\xC8\x01\xA3\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56", "xx????????xxxxxxxx????x????x????x????xxxx????x????x");


	// Search through the first entry of the Client VTable
	// The initializer contains a pointer to the 'GlobalsVariables' Table

	Globals = **(CGlobalVarsBase***)((*(DWORD**)Interfaces::Client)[0] + 0x1B);

	PDWORD pdwClientVMT = *(PDWORD*)Client;
	pInput = *(CInput**)((*(DWORD**)Client)[15] + 0x1);

	Utilities::Log("Interfaces Ready");
}

// Namespace to contain all the valve interfaces
namespace Interfaces
{
	IBaseClientDLL* Client;
	IVEngineClient* Engine;
	IPanel* Panels;
	IClientEntityList* EntList;
	ISurface* Surface;
	IVDebugOverlay* DebugOverlay;
	IClientModeShared* ClientMode;
	CGlobalVarsBase *Globals;
	IInputSystem* InputSystem;
	DWORD *Prediction;
	CMaterialSystem* MaterialSystem;
	CVRenderView* RenderView;
	IVModelRender* ModelRender;
	CModelInfo* ModelInfo;
	IEngineTrace* Trace;
	IPhysicsSurfaceProps* PhysProps;
	ICVar *CVar;
	CInput* pInput;

};