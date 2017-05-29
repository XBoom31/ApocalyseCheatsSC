/*
Syn's Payhake Framework for Insanity & Razor
*/

#define _CRT_SECURE_NO_WARNINGS

#include "Hacks.h"
#include "Interfaces.h"
#include "RenderManager.h"

#include "ESP.h"
#include "Visuals.h"
#include "RageBot.h"
#include "MiscHacks.h"
#include "LegitBot.h"

CEsp Esp;
CVisuals Visuals;
CMiscHacks MiscHacks;
CRageBot RageBot;
CLegitBot LegitBot;

// Initialise and register ALL hackmanager hacks in here nigga
void Hacks::SetupHacks()
{
	Esp.Init();
	Visuals.Init();
	MiscHacks.Init();
	RageBot.Init();
	LegitBot.Init();

	hackManager.RegisterHack(&Esp);
	hackManager.RegisterHack(&Visuals);
	hackManager.RegisterHack(&MiscHacks);
	hackManager.RegisterHack(&RageBot);
	hackManager.RegisterHack(&LegitBot);

	//--------------------------------
	hackManager.Ready();
}

/*void SpecList()
{
	IClientEntity *pLocal = hackManager.pLocal();

	RECT scrn = Render::GetViewport();
	int AC = 0;

	// Loop through all active entitys
	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		// The entity isn't some laggy peice of shit or something
		if (pEntity &&  pEntity != pLocal)
		{
			if (Interfaces::Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
			{
				HANDLE obs = pEntity->GetObserverTargetHandle();

				if (obs)
				{
					IClientEntity *pTarget = Interfaces::EntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{
						if (Interfaces::Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{
							char buf[255]; sprintf_s(buf, "%s => %s", pinfo.name, pinfo2.name);
							RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, buf);
							Render::Clear(scrn.right - 260, (scrn.bottom / 2) + (16 * AC), 260, 16, Color(0, 0, 0, 140));
							Render::Text(scrn.right - TextSize.right - 4, (scrn.bottom / 2) + (16 * AC), pTarget->GetIndex() == pLocal->GetIndex() ? Color(240, 70, 80, 255) : Color(255, 255, 255, 255), Render::Fonts::ESP, buf);
							AC++;
						}
					}
				}
			}
		}
	}

	Render::Outline(scrn.right - 261, (scrn.bottom / 2) - 1, 262, (16 * AC) + 2, Color(23, 23, 23, 255));
	Render::Outline(scrn.right - 260, (scrn.bottom / 2), 260, (16 * AC), Color(90, 90, 90, 255));
}*/

/*using PlaySoundFn = void(__stdcall*)(const char*);
extern PlaySoundFn oPlaySound;

namespace G // Global Stuff
{
	//extern bool			Aimbotting;
	//extern bool			InAntiAim;
	//extern bool			Return;
	//extern CUserCmd*	UserCmd;
	//extern HMODULE		Dll;
	extern HWND			Window;
	//extern bool			PressedKeys[256];
	//extern bool			d3dinit;
	//extern float		FOV;
	//extern int			ChamMode;
	//extern bool			SendPacket;
	//extern int			BestTarget;
}

HWND				G::Window;

PlaySoundFn oPlaySound;
void __stdcall Hooked__PlaySoundCSGO(const char* fileName)
{
	IClientEntity* pLocal = hackManager.pLocal();

	oPlaySound(fileName);

	if (Interfaces::Engine->IsInGame() || !Menu::Window.MiscTab.OtherAutoAccept.GetState())
		return;

	if (!strcmp(fileName, "weapons/hegrenade/beep.wav"))
	{
		//Accept the game
		GameUtils::IsReady = (IsReadyFn)(Offsets::Functions::dwIsReady);
		GameUtils::IsReady();

		//This will flash the CSGO window on the taskbar
		//so we know a game was found (you cant hear the beep sometimes cause it auto-accepts too fast)
		FLASHWINFO fi;
		fi.cbSize = sizeof(FLASHWINFO);
		fi.hwnd = G::Window;
		fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		fi.uCount = 0;
		fi.dwTimeout = 0;
		FlashWindowEx(&fi);
	}
}*/

// Only gets called in game, use a seperate draw UI call for menus in the hook
void Hacks::DrawHacks()
{
	IClientEntity *pLocal = hackManager.pLocal();

	void Hooked__PlaySoundCSGO(const char* fileName);

	// Spectator List
	/*if (Menu::Window.MiscTab.OtherSpectators.GetState())
		SpecList();*/

	// Check the master visuals switch, just to be sure
	if (!Menu::Window.VisualsTab.Active.GetState())
		return;

	if (Menu::Window.VisualsTab.OptionsCompRank.GetState() && GUI.GetKeyState(VK_TAB))
	{
		GameUtils::ServerRankRevealAll();
	}

	hackManager.Draw();
	//--------------------------------
		
}

// Game Cmd Changes
void Hacks::MoveHacks(CUserCmd *pCmd,bool &bSendPacket)
{
	Vector origView = pCmd->viewangles;
	IClientEntity *pLocal = hackManager.pLocal();
	hackManager.Move(pCmd, bSendPacket);
	// ------------------------------

	// Put it in here so it's applied AFTER the aimbot
	int AirStuckKey = Menu::Window.MiscTab.OtherAirStuck.GetKey();
	if (AirStuckKey > 0 && GUI.GetKeyState(AirStuckKey))
	{
		if (!(pCmd->buttons & IN_ATTACK))
		{
			pCmd->tick_count = INT_MAX;//0xFFFFF or 16777216
		}
	}

	int TeleportKey = Menu::Window.MiscTab.TeleportKey.GetKey();
	if (Menu::Window.MiscTab.TeleportEnable.GetState() && !Menu::Window.MiscTab.OtherSafeMode.GetState())
	{
		if (TeleportKey > 0 && GUI.GetKeyState(TeleportKey))
		{
			pCmd->viewangles.z = 9e+37;
		}
	}

}

//---------------------------------------------------------------------//
HackManager hackManager;

// Register a new hack
void HackManager::RegisterHack(CHack* hake)
{
	Hacks.push_back(hake);
	hake->Init();
}

// Draw all the hakes
void HackManager::Draw()
{
	if (!IsReady)
		return;

	// Grab the local player for drawing related hacks
	pLocalInstance = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Draw();
	}
}



// Handle all the move hakes
void HackManager::Move(CUserCmd *pCmd,bool &bSendPacket)
{
	if (!IsReady)
		return;

	// Grab the local player for move related hacks
	pLocalInstance = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Move(pCmd,bSendPacket); // 
	}
}

//---------------------------------------------------------------------//
// Other Utils and shit

// Saves hacks needing to call a bunch of virtuals to get the instance
// Saves on cycles and file size. Recycle your plastic kids
IClientEntity* HackManager::pLocal()
{
	return pLocalInstance;
}

// Makes sure none of the hacks are called in their 
// hooks until they are completely ready for use
void HackManager::Ready()
{
	IsReady = true;
}