/*
Rest In Peace ApocalypseCheats
*/

#include "Hooks.h"
#include "Hacks.h"
#include "Chams.h"
#include "Menu.h"
#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscHacks.h"
#include "CRC32.h"
#include "Resolver.h"

Vector LastAngleAA;

// Funtion Typedefs
typedef void(__thiscall* DrawModelEx_)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4*);
typedef void(__thiscall* PaintTraverse_)(PVOID, unsigned int, bool, bool);
typedef bool(__thiscall* InPrediction_)(PVOID);
typedef void(__stdcall *FrameStageNotifyFn)(ClientFrameStage_t);
typedef void(__thiscall* RenderViewFn)(void*, CViewSetup&, CViewSetup&, int, int);

using OverrideViewFn = void(__fastcall*)(void*, void*, CViewSetup*);
typedef float(__stdcall *oGetViewModelFOV)();


// Function Pointers to the originals
PaintTraverse_ oPaintTraverse;
DrawModelEx_ oDrawModelExecute;
FrameStageNotifyFn oFrameStageNotify;
OverrideViewFn oOverrideView;
RenderViewFn oRenderView;

// Hook function prototypes
void __fastcall PaintTraverse_Hooked(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
bool __stdcall Hooked_InPrediction();
void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld);
bool __stdcall CreateMoveClient_Hooked(/*void* self, int edx,*/ float frametime, CUserCmd* pCmd);
void  __stdcall Hooked_FrameStageNotify(ClientFrameStage_t curStage);
void __fastcall Hooked_OverrideView(void* ecx, void* edx, CViewSetup* pSetup);
float __stdcall GGetViewModelFOV();
void __fastcall Hooked_RenderView(void* ecx, void* edx, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);

// VMT Managers
namespace Hooks
{
	// VMT Managers
	Utilities::Memory::VMTManager VMTPanel; // Hooking drawing functions
	Utilities::Memory::VMTManager VMTClient; // Maybe CreateMove
	Utilities::Memory::VMTManager VMTClientMode; // CreateMove for functionality
	Utilities::Memory::VMTManager VMTModelRender; // DrawModelEx for chams
	Utilities::Memory::VMTManager VMTPrediction; // InPrediction for no vis recoil
	Utilities::Memory::VMTManager VMTPlaySound; // Autoaccept 
	Utilities::Memory::VMTManager VMTRenderView;
};

/*// Initialise all our hooks
void Hooks::Initialise()
{
// Panel hooks for drawing to the screen via surface functions
VMTPanel.Initialise((DWORD*)Interfaces::Panels);
oPaintTraverse = (PaintTraverse_)VMTPanel.HookMethod((DWORD)&PaintTraverse_Hooked, Offsets::VMT::Panel_PaintTraverse);
//Utilities::Log("Paint Traverse Hooked");

// No Visual Recoil
VMTPrediction.Initialise((DWORD*)Interfaces::Prediction);
VMTPrediction.HookMethod((DWORD)&Hooked_InPrediction, 14);
//Utilities::Log("InPrediction Hooked");

// Chams
VMTModelRender.Initialise((DWORD*)Interfaces::ModelRender);
oDrawModelExecute = (DrawModelEx_)VMTModelRender.HookMethod((DWORD)&Hooked_DrawModelExecute, Offsets::VMT::ModelRender_DrawModelExecute);
//Utilities::Log("DrawModelExecute Hooked");

// Setup ClientMode Hooks
//VMTClientMode.Initialise((DWORD*)Interfaces::ClientMode);
//VMTClientMode.HookMethod((DWORD)&CreateMoveClient_Hooked, 24);
//Utilities::Log("ClientMode CreateMove Hooked");

// Setup client hooks
VMTClient.Initialise((DWORD*)Interfaces::Client);
oCreateMove = (CreateMoveFn)VMTClient.HookMethod((DWORD)&hkCreateMove, 21);
}*/

// Undo our hooks
void Hooks::UndoHooks()
{
	VMTPanel.RestoreOriginal();
	VMTPrediction.RestoreOriginal();
	VMTModelRender.RestoreOriginal();
	VMTClientMode.RestoreOriginal();
}


// Initialise all our hooks
void Hooks::Initialise()
{
	// Panel hooks for drawing to the screen via surface functions
	VMTPanel.Initialise((DWORD*)Interfaces::Panels);
	oPaintTraverse = (PaintTraverse_)VMTPanel.HookMethod((DWORD)&PaintTraverse_Hooked, Offsets::VMT::Panel_PaintTraverse);
	//Utilities::Log("Paint Traverse Hooked");

	// No Visual Recoi	l
	VMTPrediction.Initialise((DWORD*)Interfaces::Prediction);
	VMTPrediction.HookMethod((DWORD)&Hooked_InPrediction, 14);
	//Utilities::Log("InPrediction Hooked");

	// Chams
	VMTModelRender.Initialise((DWORD*)Interfaces::ModelRender);
	oDrawModelExecute = (DrawModelEx_)VMTModelRender.HookMethod((DWORD)&Hooked_DrawModelExecute, Offsets::VMT::ModelRender_DrawModelExecute);
	//Utilities::Log("DrawModelExecute Hooked");

	// Setup ClientMode Hooks
	VMTClientMode.Initialise((DWORD*)Interfaces::clientmode);
	VMTClientMode.HookMethod((DWORD)CreateMoveClient_Hooked, 24);

	oOverrideView = (OverrideViewFn)VMTClientMode.HookMethod((DWORD)&Hooked_OverrideView, 18);
	VMTClientMode.HookMethod((DWORD)&GGetViewModelFOV, 35);

	// Setup client hooks
	VMTClient.Initialise((DWORD*)Interfaces::Client);
	oFrameStageNotify = (FrameStageNotifyFn)VMTClient.HookMethod((DWORD)&Hooked_FrameStageNotify, 36);

}

void MovementCorrection(CUserCmd* pCmd)
{

}

//---------------------------------------------------------------------------------------------------------
//                                         Hooked Functions
//---------------------------------------------------------------------------------------------------------

void SetClanTag(const char* tag, const char* name)//190% paste
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx")));
	pSetClanTag(tag, name);
}
void NoClantag()
{
	SetClanTag("", "");
}

void ClanTag()
{
	static int counter = 0;
	switch (Menu::Window.MiscTab.OtherClantag.GetIndex())
	{
	case 0:
		SetClanTag("", "");
		break;
	case 1:
	{
		static int motion = 0;
		int ServerTime = (float)Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase() * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 19;
		switch (value) {
		case 0:SetClanTag("           ", "Apocalypse"); break;
		case 1:SetClanTag("          A", "Apocalypse"); break;
		case 2:SetClanTag("         Ap", "Apocalypse"); break;
		case 3:SetClanTag("        Apo", "Apocalypse"); break;
		case 4:SetClanTag("       Apoc", "Apocalypse"); break;
		case 5:SetClanTag("      Apoca", "Apocalypse"); break;
		case 6:SetClanTag("     Apocal", "Apocalypse"); break;
		case 7:SetClanTag("    Apocaly", "Apocalypse"); break;
		case 8:SetClanTag("   Apocalyp", "Apocalypse"); break;
		case 9:SetClanTag("  Apocalyps", "Apocalypse"); break;
		case 10:SetClanTag("Apocalypse", "Apocalypse"); break;
		case 11:SetClanTag("pocalypse ", "Apocalypse"); break;
		case 12:SetClanTag("ocalypse  ", "Apocalypse"); break;
		case 13:SetClanTag("calypse   ", "Apocalypse"); break;
		case 14:SetClanTag("alypse    ", "Apocalypse"); break;
		case 15:SetClanTag("lypse     ", "Apocalypse"); break;
		case 16:SetClanTag("ypse      ", "Apocalypse"); break;
		case 17:SetClanTag("pse       ", "Apocalypse"); break;
		case 18:SetClanTag("se        ", "Apocalypse"); break;
		case 19:SetClanTag("e         ", "Apocalypse"); break;
		case 20:SetClanTag("          ", "Apocalypse"); break;
		}
		counter++;
	}
	break;
	case 2:
	{
		static int motion = 0;
		int ServerTime = (float)Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase() * 3;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 1;
		switch (value) {
		case 0:SetClanTag("ApocalypseCheats - Beta", "ApocalypseCheats - Beta"); break;
		case 1:SetClanTag("XBoom", "XBoom"); break;
		case 2:SetClanTag("Derank service", "Derank service"); break;
		case 3:SetClanTag("Rekt by free cheats", "Rekt by free cheats"); break;
		case 4:SetClanTag("Skeet is trash", "Skeet is trash"); break;
		case 5:SetClanTag("Suicide Rate Raiser", "Suicide Rate Raiser"); break;
	    case 6:SetClanTag("UnknownCheats", "UnknownCheats"); break;
		}
		counter++;
	}
	break;
	case 3:
		// stainless
		SetClanTag("\r", "\r");
		break;
	case 4:
		SetClanTag("[VALV\xE1\xB4\xB1]", "Valve");
		break;
	}
}

bool __stdcall CreateMoveClient_Hooked(/*void* self, int edx,*/ float frametime, CUserCmd* pCmd)
{
	if (!pCmd->command_number)
		return true;

	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame())
	{

		PVOID pebp;
		__asm mov pebp, ebp;
		bool* pbSendPacket = (bool*)(*(DWORD*)pebp - 0x1C);
		bool& bSendPacket = *pbSendPacket;

		if (Menu::Window.MiscTab.OtherClantag.GetIndex() > 0)
			ClanTag();

		//	CUserCmd* cmdlist = *(CUserCmd**)((DWORD)Interfaces::pInput + 0xEC);
		//	CUserCmd* pCmd = &cmdlist[sequence_number % 150];


			// Backup for safety
		Vector origView = pCmd->viewangles;
		Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
		Vector qAimAngles;
		qAimAngles.Init(0.0f, pCmd->viewangles.y, 0.0f);
		AngleVectors(qAimAngles, &viewforward, &viewright, &viewup);

		// Do da hacks
		IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
		if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal && pLocal->IsAlive())
			Hacks::MoveHacks(pCmd, bSendPacket);

		//Movement Fix
		//GameUtils::CL_FixMove(pCmd, origView);
		qAimAngles.Init(0.0f, GetAutostrafeView().y, 0.0f); // if pCmd->viewangles.x > 89, set pCmd->viewangles.x instead of 0.0f on first
		AngleVectors(qAimAngles, &viewforward, &viewright, &viewup);
		qAimAngles.Init(0.0f, pCmd->viewangles.y, 0.0f);
		AngleVectors(qAimAngles, &aimforward, &aimright, &aimup);
		Vector vForwardNorm;		Normalize(viewforward, vForwardNorm);
		Vector vRightNorm;			Normalize(viewright, vRightNorm);
		Vector vUpNorm;				Normalize(viewup, vUpNorm);

		// Original shit for movement correction
		float forward = pCmd->forwardmove;
		float right = pCmd->sidemove;
		float up = pCmd->upmove;
		if (forward > 450) forward = 450;
		if (right > 450) right = 450;
		if (up > 450) up = 450;
		if (forward < -450) forward = -450;
		if (right < -450) right = -450;
		if (up < -450) up = -450;
		pCmd->forwardmove = DotProduct(forward * vForwardNorm, aimforward) + DotProduct(right * vRightNorm, aimforward) + DotProduct(up * vUpNorm, aimforward);
		pCmd->sidemove = DotProduct(forward * vForwardNorm, aimright) + DotProduct(right * vRightNorm, aimright) + DotProduct(up * vUpNorm, aimright);
		pCmd->upmove = DotProduct(forward * vForwardNorm, aimup) + DotProduct(right * vRightNorm, aimup) + DotProduct(up * vUpNorm, aimup);

		// Angle normalisation
		if (Menu::Window.MiscTab.OtherSafeMode.GetState())
		{
			GameUtils::NormaliseViewAngle(pCmd->viewangles);

			if (pCmd->viewangles.z != 0.0f)
			{
				pCmd->viewangles.z = 0.00;
			}

			if (pCmd->viewangles.x < -89 || pCmd->viewangles.x > 89 || pCmd->viewangles.y < -180 || pCmd->viewangles.y > 180)
			{
				Utilities::Log("Having to re-normalise!");
				GameUtils::NormaliseViewAngle(pCmd->viewangles);
				Beep(750, 800); // Why does it do this
				if (pCmd->viewangles.x < -89 || pCmd->viewangles.x > 89 || pCmd->viewangles.y < -180 || pCmd->viewangles.y > 180)
				{
					pCmd->viewangles = origView;
					pCmd->sidemove = right;
					pCmd->forwardmove = forward;
				}
			}
		}

		if (pCmd->viewangles.x > 90)
		{
			pCmd->forwardmove = -pCmd->forwardmove;
		}

		if (pCmd->viewangles.x < -90)
		{
			pCmd->forwardmove = -pCmd->forwardmove;
		}

		if (bSendPacket)
			LastAngleAA = pCmd->viewangles;
	}

	return false;
}


// Paint Traverse Hooked function
void __fastcall PaintTraverse_Hooked(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	oPaintTraverse(pPanels, vguiPanel, forceRepaint, allowForce);

	static unsigned int FocusOverlayPanel = 0;
	static bool FoundPanel = false;

	if (!FoundPanel)
	{
		PCHAR szPanelName = (PCHAR)Interfaces::Panels->GetName(vguiPanel);
		if (strstr(szPanelName, "MatSystemTopPanel"))
		{
			FocusOverlayPanel = vguiPanel;
			FoundPanel = true;
		}
	}
	else if (FocusOverlayPanel == vguiPanel)
	{ 
		
		if (Menu::Window.MiscTab.OtherWatermark.GetState())
		{
			RECT scrn = Render::GetViewport();
			//Render::GradientV(8, 8, 160, 18, Color(0, 0, 0, 0), Color(7, 39, 17, 255));
			RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, "ApocalypseCheats");
			Render::Text(scrn.right - TextSize.right - 20, 10, Color(Menu::Window.ColorTab.MenuInnerR.GetValue(), Menu::Window.ColorTab.MenuInnerG.GetValue(), Menu::Window.ColorTab.MenuInnerB.GetValue(), 255), Render::Fonts::MenuBold, "ApocalypseCheats");
			Render::Text(10, 10, Color(Menu::Window.ColorTab.MenuInnerR.GetValue(), Menu::Window.ColorTab.MenuInnerG.GetValue(), Menu::Window.ColorTab.MenuInnerB.GetValue(), 255), Render::Fonts::MenuBold, "Private");
		}
		
		if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame())
			Hacks::DrawHacks();

		// Update and draw the menu
		Menu::DoUIFrame();
	}
}

// InPrediction Hooked Function
bool __stdcall Hooked_InPrediction()
{
	bool result;
	static InPrediction_ origFunc = (InPrediction_)Hooks::VMTPrediction.GetOriginalFunction(14);
	static DWORD *ecxVal = Interfaces::Prediction;
	result = origFunc(ecxVal);

	// If we are in the right place where the player view is calculated
	// Calculate the change in the view and get rid of it
	if (Menu::Window.VisualsTab.OtherNoVisualRecoil.GetState() && (DWORD)(_ReturnAddress()) == Offsets::Functions::dwCalcPlayerView)
	{
		IClientEntity* pLocalEntity = NULL;

		float* m_LocalViewAngles = NULL;

		__asm
		{
			MOV pLocalEntity, ESI
			MOV m_LocalViewAngles, EBX
		}

		Vector viewPunch = pLocalEntity->localPlayerExclusive()->GetViewPunchAngle();
		Vector aimPunch = pLocalEntity->localPlayerExclusive()->GetAimPunchAngle();

		m_LocalViewAngles[0] -= (viewPunch[0] + (aimPunch[0] * 2 * 0.4499999f));
		m_LocalViewAngles[1] -= (viewPunch[1] + (aimPunch[1] * 2 * 0.4499999f));
		m_LocalViewAngles[2] -= (viewPunch[2] + (aimPunch[2] * 2 * 0.4499999f));
		return true;
	}

	return result;
}

// DrawModelExec for chams and shit
void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	Color color;
	float flColor[3] = { 0.f };
	static IMaterial* CoveredLit = CreateMaterial(true);
	static IMaterial* OpenLit = CreateMaterial(false);
	static IMaterial* CoveredFlat = CreateMaterial(true, false);
	static IMaterial* OpenFlat = CreateMaterial(false, false);
	bool DontDraw = false;

	const char* ModelName = Interfaces::ModelInfo->GetModelName((model_t*)pInfo.pModel);
	IClientEntity* pModelEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(pInfo.entity_index);
	IClientEntity* pLocal = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (Menu::Window.VisualsTab.Active.GetState())
	{
		// Player Chams
		int ChamsStyle = Menu::Window.VisualsTab.OptionsChams.GetIndex();
		int HandsStyle = Menu::Window.VisualsTab.OtherNoHands.GetIndex();
		if (ChamsStyle != 0 && Menu::Window.VisualsTab.FiltersPlayers.GetState() && strstr(ModelName, "models/player"))
		{
			if (pLocal /*&& (!Menu::Window.VisualsTab.FiltersEnemiesOnly.GetState() || pModelEntity->GetTeamNum() != pLocal->GetTeamNum())*/)
			{
				IMaterial *covered = ChamsStyle == 1 ? CoveredLit : CoveredFlat;
				IMaterial *open = ChamsStyle == 1 ? OpenLit : OpenFlat;

				IClientEntity* pModelEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(pInfo.entity_index);
				if (pModelEntity)
				{
					IClientEntity *local = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
					if (local)
					{
						if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0 /*&& pModelEntity->GetTeamNum() != local->GetTeamNum()*/)
						{
							float alpha = 1.f;

							if (pModelEntity->HasGunGameImmunity())
								alpha = 0.5f;

							if (pModelEntity->GetTeamNum() == 2)
							{
								flColor[0] = 240.f / 255.f;
								flColor[1] = 30.f / 255.f;
								flColor[2] = 35.f / 255.f;
							}
							else
							{
								flColor[0] = 63.f / 255.f;
								flColor[1] = 72.f / 255.f;
								flColor[2] = 205.f / 255.f;
							}

							Interfaces::RenderView->SetColorModulation(flColor);
							Interfaces::RenderView->SetBlend(alpha);
							Interfaces::ModelRender->ForcedMaterialOverride(covered);
							oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

							if (pModelEntity->GetTeamNum() == 2)
							{
								flColor[0] = 247.f / 255.f;
								flColor[1] = 180.f / 255.f;
								flColor[2] = 20.f / 255.f;
							}
							else
							{
								flColor[0] = 32.f / 255.f;
								flColor[1] = 180.f / 255.f;
								flColor[2] = 57.f / 255.f;
							}

							Interfaces::RenderView->SetColorModulation(flColor);
							Interfaces::RenderView->SetBlend(alpha);
							Interfaces::ModelRender->ForcedMaterialOverride(open);
						}
						else
						{
							color.SetColor(255, 255, 255, 255);
							ForceMaterial(color, open);
						}
					}
				}
			}
		}
		else if (HandsStyle != 0 && strstr(ModelName, "arms"))
		{
			if (HandsStyle == 1)
			{
				DontDraw = true;
			}
			else if (HandsStyle == 2)
			{
				Interfaces::RenderView->SetBlend(0.3);
			}
			else if (HandsStyle == 3)
			{
				IMaterial *covered = ChamsStyle == 1 ? CoveredLit : CoveredFlat;
				IMaterial *open = ChamsStyle == 1 ? OpenLit : OpenFlat;
				if (pLocal)
				{
					if (pLocal->IsAlive())
					{
						int alpha = pLocal->HasGunGameImmunity() ? 150 : 255;

						if (pLocal->GetTeamNum() == 2)
							color.SetColor(240, 30, 35, alpha);
						else
							color.SetColor(63, 72, 205, alpha);

						ForceMaterial(color, covered);
						oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

						if (pLocal->GetTeamNum() == 2)
							color.SetColor(247, 180, 20, alpha);
						else
							color.SetColor(32, 180, 57, alpha);
					}
					else
					{
						color.SetColor(255, 255, 255, 255);
					}

					ForceMaterial(color, open);
				}
			}
			else
			{
				static int counter = 0;
				static float colors[3] = { 1.f, 0.f, 0.f };

				if (colors[counter] >= 1.0f)
				{
					colors[counter] = 1.0f;
					counter += 1;
					if (counter > 2)
						counter = 0;
				}
				else
				{
					int prev = counter - 1;
					if (prev < 0) prev = 2;
					colors[prev] -= 0.05f;
					colors[counter] += 0.05f;
				}

				Interfaces::RenderView->SetColorModulation(colors);
				Interfaces::RenderView->SetBlend(0.3);
				Interfaces::ModelRender->ForcedMaterialOverride(OpenLit);
			}
		}
		else if (ChamsStyle != 0 && Menu::Window.VisualsTab.FiltersWeapons.GetState() && strstr(ModelName, "_dropped.mdl"))
		{
			IMaterial *covered = ChamsStyle == 1 ? CoveredLit : CoveredFlat;
			color.SetColor(255, 255, 255, 255);
			ForceMaterial(color, covered);
		}
	}

	if (!DontDraw)
		oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	Interfaces::ModelRender->ForcedMaterialOverride(NULL);
}


// Hooked FrameStageNotify for removing visual recoil
void  __stdcall Hooked_FrameStageNotify(ClientFrameStage_t curStage)
{
	DWORD eyeangles = NetVar.GetNetVar(0xBFEA4E7B);
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && curStage == FRAME_RENDER_START)
	{

		if (pLocal->IsAlive())
		{
			if (*(bool*)((DWORD)Interfaces::pInput + 0xA5))
				*(Vector*)((DWORD)pLocal + 0x31C8) = LastAngleAA;
		}

		if ((Menu::Window.MiscTab.OtherThirdperson.GetState()) || Menu::Window.RageBotTab.AccuracyPositionAdjustment.GetState())
		{
			static bool rekt = false;
			if (!rekt)
			{
				ConVar* sv_cheats = Interfaces::CVar->FindVar("sv_cheats");
				SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
				sv_cheats_spoofed->SetInt(1);
				rekt = true;
			}
		}

		static bool rekt1 = false;
		if (Menu::Window.MiscTab.OtherThirdperson.GetState() && pLocal->IsAlive() && pLocal->IsScoped() == 0)
		{
			if (!rekt1)
			{
				Interfaces::Engine->ClientCmd_Unrestricted("thirdperson");
				rekt1 = true;
			}
		}
		else if (!Menu::Window.MiscTab.OtherThirdperson.GetState())
		{
			rekt1 = false;
		}

		static bool rekt = false;
		if (!Menu::Window.MiscTab.OtherThirdperson.GetState() || pLocal->IsAlive() == 0 || pLocal->IsScoped())
		{
			if (!rekt)
			{
				Interfaces::Engine->ClientCmd_Unrestricted("firstperson");
				rekt = true;
			}
		}
		else if (Menu::Window.MiscTab.OtherThirdperson.GetState() || pLocal->IsAlive() || pLocal->IsScoped() == 0)
		{
			rekt = false;
		}

		static bool meme = false;
		if (Menu::Window.MiscTab.OtherThirdperson.GetState() && pLocal->IsScoped() == 0)
		{
			if (!meme)
			{
				Interfaces::Engine->ClientCmd_Unrestricted("thirdperson");
				meme = true;
			}
		}
		else if (pLocal->IsScoped())
		{
			meme = false;
		}

		static bool kek = false;
		if (Menu::Window.MiscTab.OtherThirdperson.GetState() && pLocal->IsAlive())
		{
			if (!kek)
			{
				Interfaces::Engine->ClientCmd_Unrestricted("thirdperson");
				kek = true;
			}
		}
		else if (pLocal->IsAlive() == 0)
		{
			kek = false;
		}
	}

	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	/*	for (int i = 1; i < 65; i++)
		{
			IClientEntity* pEnt = Interfaces::EntList->GetClientEntity(i);
			if (!pEnt) continue;
			if (pEnt->IsDormant()) continue;
			if (pEnt->GetHealth() < 1) continue;
			if (pEnt->GetLifeState() != 0) continue;

			*(float*)((DWORD)pEnt + eyeangles) = pEnt->GetTargetYaw();
			//Msg("%f\n", *(float*)((DWORD)pEnt + m_angEyeAnglesYaw));
		} */

		if (Menu::Window.MiscTab.KnifeEnable.GetState() && pLocal)
		{
			IClientEntity* WeaponEnt = Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
			CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)WeaponEnt;

			int iBayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
			int iButterfly = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
			int iFlip = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
			int iGut = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
			int iKarambit = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			int iM9Bayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			int iHuntsman = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
			int iFalchion = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
			int iDagger = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
			int iBowie = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

			int Model = Menu::Window.MiscTab.KnifeModel.GetIndex();
			int Skin = Menu::Window.MiscTab.KnifeSkin.GetIndex();

			if (Weapon)
			{
				if (WeaponEnt->GetClientClass()->m_ClassID == (int)CSGOClassID::CKnife)
				{
				
						if (Model == 0) // Karambit
						{
							*Weapon->ModelIndex() = iKarambit; // m_nModelIndex
							*Weapon->ViewModelIndex() = iKarambit;
							*Weapon->WorldModelIndex() = iKarambit + 1;
							*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 507;

							if (Skin == 0)
								*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
							else if (Skin == 1)
								*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
							else if (Skin == 2)
								*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
							else if (Skin == 3)
								*Weapon->FallbackPaintKit() = 558; // Lore
							else if (Skin == 4)
								*Weapon->FallbackPaintKit() = 5; // forest
							else if (Skin == 5)
								*Weapon->FallbackPaintKit() = 12; // Crimson
							else if (Skin == 6)
								*Weapon->FallbackPaintKit() = 59; // saughter
							else if (Skin == 7)
								*Weapon->FallbackPaintKit() = 29; // bone mask
							else if (Skin == 8)
								*Weapon->FallbackPaintKit() = 38; // fade
							else if (Skin == 9)
								*Weapon->FallbackPaintKit() = 40; // Night
							else if (Skin == 10)
								*Weapon->FallbackPaintKit() = 42; // blue steel
							else if (Skin == 11)
								*Weapon->FallbackPaintKit() = 43; // stained
							else if (Skin == 12)
								*Weapon->FallbackPaintKit() = 44; // case hard
							else if (Skin == 13)
								*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
							else if (Skin == 14)
								*Weapon->FallbackPaintKit() = 77; // boreal forest
							else if (Skin == 15)
								*Weapon->FallbackPaintKit() = 98; // Untraviolet
							else if (Skin == 16)
								*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
							else if (Skin == 17)
								*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST

						}
					

					else if (Model == 1) // Bayo
					{
						*Weapon->ModelIndex() = iBayonet; // m_nModelIndex
						*Weapon->ViewModelIndex() = iBayonet;
						*Weapon->WorldModelIndex() = iBayonet + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 500;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 2) // m8Bayo
					{
						*Weapon->ModelIndex() = iM9Bayonet; // m_nModelIndex
						*Weapon->ViewModelIndex() = iM9Bayonet;
						*Weapon->WorldModelIndex() = iM9Bayonet + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 508;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 3) // flip
					{
						*Weapon->ModelIndex() = iFlip; // m_nModelIndex
						*Weapon->ViewModelIndex() = iFlip;
						*Weapon->WorldModelIndex() = iFlip + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 505;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 4) // gut
					{
						*Weapon->ModelIndex() = iGut; // m_nModelIndex
						*Weapon->ViewModelIndex() = iGut;
						*Weapon->WorldModelIndex() = iGut + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 506;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 5) // huntsman
					{
						*Weapon->ModelIndex() = iHuntsman; // m_nModelIndex
						*Weapon->ViewModelIndex() = iHuntsman;
						*Weapon->WorldModelIndex() = iHuntsman + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 509;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 6) // falchion
					{
						*Weapon->ModelIndex() = iFalchion; // m_nModelIndex
						*Weapon->ViewModelIndex() = iFalchion;
						*Weapon->WorldModelIndex() = iFalchion + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 512;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 7) // bowie
					{
						*Weapon->ModelIndex() = iBowie; // m_nModelIndex
						*Weapon->ViewModelIndex() = iBowie;
						*Weapon->WorldModelIndex() = iBowie + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 514;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 8) // butterfly
					{
						*Weapon->ModelIndex() = iButterfly; // m_nModelIndex
						*Weapon->ViewModelIndex() = iButterfly;
						*Weapon->WorldModelIndex() = iButterfly + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 515;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					else if (Model == 9) // shadowdg
					{
						*Weapon->ModelIndex() = iDagger; // m_nModelIndex
						*Weapon->ViewModelIndex() = iDagger;
						*Weapon->WorldModelIndex() = iDagger + 1;
						*Weapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 516;

						if (Skin == 0)
							*Weapon->FallbackPaintKit() = 416; // Doppler Sapphire
						else if (Skin == 1)
							*Weapon->FallbackPaintKit() = 415; // Doppler Ruby
						else if (Skin == 2)
							*Weapon->FallbackPaintKit() = 409; // Tiger Tooth
						else if (Skin == 3)
							*Weapon->FallbackPaintKit() = 558; // Lore
						else if (Skin == 4)
							*Weapon->FallbackPaintKit() = 5; // forest
						else if (Skin == 5)
							*Weapon->FallbackPaintKit() = 12; // Crimson
						else if (Skin == 6)
							*Weapon->FallbackPaintKit() = 59; // saughter
						else if (Skin == 7)
							*Weapon->FallbackPaintKit() = 29; // bone mask
						else if (Skin == 8)
							*Weapon->FallbackPaintKit() = 38; // fade
						else if (Skin == 9)
							*Weapon->FallbackPaintKit() = 40; // Night
						else if (Skin == 10)
							*Weapon->FallbackPaintKit() = 42; // blue steel
						else if (Skin == 11)
							*Weapon->FallbackPaintKit() = 43; // stained
						else if (Skin == 12)
							*Weapon->FallbackPaintKit() = 44; // case hard
						else if (Skin == 13)
							*Weapon->FallbackPaintKit() = 72; // safari mesh, ce-si permite petreus
						else if (Skin == 14)
							*Weapon->FallbackPaintKit() = 77; // boreal forest
						else if (Skin == 15)
							*Weapon->FallbackPaintKit() = 98; // Untraviolet
						else if (Skin == 16)
							*Weapon->FallbackPaintKit() = 414; // ruginit ca petreus
						else if (Skin == 17)
							*Weapon->FallbackPaintKit() = 413; // ROMANIA4EVER IS DA BEST
					}
					*Weapon->OwnerXuidLow() = 0;
					*Weapon->OwnerXuidHigh() = 0;
					*Weapon->FallbackWear() = 0.001f;
					*Weapon->m_AttributeManager()->m_Item()->ItemIDHigh() = 2;
				}
			}
		}
		if (pLocal->IsAlive())
			R::Resolve();
	}

	oFrameStageNotify(curStage);
}

void __fastcall Hooked_OverrideView(void* ecx, void* edx, CViewSetup* pSetup)
{
	IClientEntity* pLocal = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame())
	{
		if (Menu::Window.VisualsTab.Active.GetState() && pLocal->IsAlive() && !pLocal->IsScoped())
		{
			if (pSetup->fov = 90)
				pSetup->fov = Menu::Window.VisualsTab.OtherFOV.GetValue();
		}

		oOverrideView(ecx, edx, pSetup);
	}

}

void GetViewModelFOV(float& fov)
{
	IClientEntity* localplayer = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame())
	{

		if (!localplayer)
			return;


		if (Menu::Window.VisualsTab.Active.GetState())
		fov += Menu::Window.VisualsTab.OtherViewmodelFOV.GetValue();
	}
}

float __stdcall GGetViewModelFOV()
{
	float fov = Hooks::VMTClientMode.GetMethod<oGetViewModelFOV>(35)();

	GetViewModelFOV(fov);

	return fov;
}

void __fastcall Hooked_RenderView(void* ecx, void* edx, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw)
{
	static DWORD oRenderView = Hooks::VMTRenderView.GetOriginalFunction(6);

	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	__asm
	{
		PUSH whatToDraw
		PUSH nClearFlags
		PUSH hudViewSetup
		PUSH setup
		MOV ECX, ecx
		CALL oRenderView
	}
} //hooked for no reason yay