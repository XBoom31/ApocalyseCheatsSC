/*
Rest In Peace ApocalypseCheats
*/

#include "Visuals.h"
#include "Interfaces.h"
#include "RenderManager.h"

// Any init here
void CVisuals::Init()
{
	// Idk
}

// Don't really need to do anything in here
void CVisuals::Move(CUserCmd *pCmd, bool &bSendPacket) {}

// Main ESP Drawing loop
void CVisuals::Draw()
{
	// Crosshair
	if (Menu::Window.VisualsTab.OtherCrosshair.GetState())
		DrawCrosshair();

	// Recoil Crosshair
	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex())
		DrawRecoilCrosshair();

	
}

// Draw a basic crosshair
void CVisuals::DrawCrosshair()
{
	// Crosshair
	RECT View = Render::GetViewport();
	int MidX = View.right / 2;
	int MidY = View.bottom / 2;
	Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY + 8, Color(0, 0, 0, 200));
	Render::Line(MidX + 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 0, 0, 200));
	Render::Line(MidX - 4, MidY - 4, MidX + 4, MidY + 4, Color(0, 255, 0, 255));
	Render::Line(MidX + 4, MidY - 4, MidX - 4, MidY + 4, Color(0, 255, 0, 255));
}

void CVisuals::DrawHitCrosshair()
{

}

// Recoil crosshair
void CVisuals::DrawRecoilCrosshair()
{
	if (Menu::Window.RageBotTab.AccuracyRecoil.GetState())
		return;

	IClientEntity *pLocal = hackManager.pLocal();

	// Get the view with the recoil
	Vector ViewAngles;
	Interfaces::Engine->GetViewAngles(ViewAngles);
	ViewAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	// Build a ray going fowards at that angle
	Vector fowardVec;
	AngleVectors(ViewAngles, &fowardVec);
	fowardVec *= 10000;

	// Get ray start / end
	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = start + fowardVec, endScreen;

	if (Render::WorldToScreen(end, endScreen) && pLocal->IsAlive())
	{
		Render::Line(endScreen.x - 4, endScreen.y - 4, endScreen.x + 4, endScreen.y + 4, Color(0, 255, 0, 255));
		Render::Line(endScreen.x + 4, endScreen.y - 4, endScreen.x - 4, endScreen.y + 4, Color(0, 255, 0, 255));
		Render::Line(endScreen.x - 2, endScreen.y - 2, endScreen.x + 2, endScreen.y + 2, Color(0, 0, 0, 200));
		Render::Line(endScreen.x + 2, endScreen.y - 2, endScreen.x - 2, endScreen.y + 2, Color(0, 0, 0, 200));
	}
}