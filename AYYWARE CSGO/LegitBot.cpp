/*
Syn's AyyWare Framework 2015
*/

#include "LegitBot.h"
#include "RenderManager.h"
#include <iostream>

void CLegitBot::Init()
{
	IsLocked = false;
	TargetID = -1;
}

void CLegitBot::Draw()
{

}

void CLegitBot::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	// Master switch
	if (!Menu::Window.LegitBotTab.Active.GetState())
		return;

	// Aimbot
	if (Menu::Window.LegitBotTab.AimbotEnable.GetState())
		DoAimbot(pCmd, bSendPacket);

	// Triggerbot
	if (Menu::Window.LegitBotTab.TriggerEnable.GetState() && (!Menu::Window.LegitBotTab.TriggerKeyPress.GetState() || GUI.GetKeyState(Menu::Window.LegitBotTab.TriggerKeyBind.GetKey())))
		DoTrigger(pCmd);
}

void CLegitBot::SyncWeaponSettings()
{
	std::vector<int> HitBoxesToScan;
	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (GameUtils::IsPistol(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponPistSpeed.GetValue();
		FoV = Menu::Window.LegitBotTab.WeaponPistFoV.GetValue();
		RecoilControl = Menu::Window.LegitBotTab.WeaponPistRecoil.GetState();
		PSilent = Menu::Window.LegitBotTab.WeaponPistPSilent.GetState();
		Inacc = Menu::Window.LegitBotTab.WeaponPistInacc.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponPistHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			break;
		}
	}
	else if (GameUtils::IsSniper(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponSnipSpeed.GetValue();
		FoV = Menu::Window.LegitBotTab.WeaponSnipFoV.GetValue();
		RecoilControl = Menu::Window.LegitBotTab.WeaponSnipRecoil.GetState();
		PSilent = Menu::Window.LegitBotTab.WeaponSnipPSilent.GetState();
		Inacc = Menu::Window.LegitBotTab.WeaponSnipInacc.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponSnipHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			break;
		}
	}
	else
	{
		Speed = Menu::Window.LegitBotTab.WeaponMainSpeed.GetValue();
		FoV = Menu::Window.LegitBotTab.WeaponMainFoV.GetValue();
		RecoilControl = Menu::Window.LegitBotTab.WeaponMainRecoil.GetState();
		PSilent = Menu::Window.LegitBotTab.WeaponMainPSilent.GetState();
		Inacc = Menu::Window.LegitBotTab.WeaponMainInacc.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponMainHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			break;
		}
	}
}

// Functionality
void CLegitBot::DoAimbot(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* pLocal = hackManager.pLocal();
	bool FindNewTarget = true;
	//IsLocked = false;

	// Don't aimbot with the knife..
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			//TargetID = 0;
			//pTarget = nullptr;
			//HitBox = -1;
			return;
		}
		SyncWeaponSettings();

	}
	else
		return;

	// Make sure we have a good target
	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		if (pTarget  && TargetMeetsRequirements(pTarget))
		{
			SyncWeaponSettings();
			if (HitBox >= 0)
			{
				Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
				Vector View; Interfaces::Engine->GetViewAngles(View);
				View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;
				float nFoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (nFoV < FoV)
					FindNewTarget = false;
			}
		}
	}

	// Find a new target, apparently we need to
	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		TargetID = GetTargetCrosshair();

		// Memes
		if (TargetID >= 0)
		{
			pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		}
		else
		{
			pTarget = nullptr;
			HitBox = -1;
		}
	}

	SyncWeaponSettings();

	// If we finally have a good target
	if (TargetID >= 0 && pTarget)
	{
		//HitBox = (int)CSGOHitboxID::Head;//
		SyncWeaponSettings();

		// Key
		if (Menu::Window.LegitBotTab.AimbotKeyPress.GetState())
		{
			int Key = Menu::Window.LegitBotTab.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		Vector AimPoint = GetHitboxPosition(pTarget, HitBox);

		if (AimAtPoint(pLocal, AimPoint, pCmd, bSendPacket))
		{
			//IsLocked = true;
			if (Menu::Window.LegitBotTab.AimbotAutoFire.GetState() && !(pCmd->buttons & IN_ATTACK))
			{
				pCmd->buttons |= IN_ATTACK;
			}
		}
	}

	// Auto Pistol
	static bool WasFiring = false;
	if (GameUtils::IsPistol(pWeapon) && Menu::Window.LegitBotTab.AimbotAutoPistol.GetState())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}

bool TargetMeetsTriggerRequirements(IClientEntity* pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass *pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			// Team Check
			if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum() || Menu::Window.LegitBotTab.AimbotFriendlyFire.GetState())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity())
				{
					return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}

void CLegitBot::DoTrigger(CUserCmd *pCmd)
{
	IClientEntity* pLocal = hackManager.pLocal();

	// Don't triggerbot with the knife..
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			return;
		}
	}
	else
		return;

	// Triggerbot
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

	trace_t Trace;
	UTIL_TraceLine(start, end, MASK_SOLID, pLocal, 0, &Trace);

	if (Trace.m_pEnt && 0 < Trace.hitgroup <= 7) // hitbox not hitgroup
	{
		if (TargetMeetsTriggerRequirements(Trace.m_pEnt) && !time < Menu::Window.LegitBotTab.TriggerDelay.GetValue())
		{
			float time = 0;
			time++;
			float delay = Menu::Window.LegitBotTab.TriggerDelay.GetValue() / 1000.f;

			if ((time * 64) < delay)
			{
				return;
			}
			else
			{
				pCmd->buttons |= IN_ATTACK;
				time = 0;
			}
		}
	}

	// Auto Pistol
	if (GameUtils::IsPistol(pWeapon) && Menu::Window.LegitBotTab.AimbotAutoPistol.GetState())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}

bool CLegitBot::TargetMeetsRequirements(IClientEntity* pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass *pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			// Team Check
			if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum() || Menu::Window.LegitBotTab.AimbotFriendlyFire.GetState())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity())
				{
					if (GameUtils::IsVisible(hackManager.pLocal(), pEntity, HitBox))
						return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}

float CLegitBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int aHitBox)
{
	Vector out[9];

	// Anything past 180 degrees is just going to wrap around
	CONST FLOAT MaxDegrees = 180.0f;

	// Get local angles
	Vector Angles = View;

	// Get local view / eye position
	Vector Origin = ViewOffSet;

	// Create and intiialize vectors for calculations below
	Vector Delta(0, 0, 0);
	//Vector Origin(0, 0, 0);
	Vector Forward(0, 0, 0);

	// Convert angles to normalized directional forward vector
	AngleVectors(Angles, &Forward);
	Vector AimPos = GetHitboxPosition(pEntity, aHitBox);
	// Get delta vector between our local eye position and passed vector
	VectorSubtract(AimPos, Origin, Delta);
	//Delta = AimPos - Origin;

	// Normalize our delta vector
	Normalize(Delta, Delta);

	// Get dot product between delta position and directional forward vectors
	FLOAT DotProduct = Forward.Dot(Delta);

	// Time to calculate the field of view
	return (acos(DotProduct) * (MaxDegrees / PI));
}

int CLegitBot::GetTargetCrosshair()
{
	// Target selection
	SyncWeaponSettings();
	int target = -1;
	float minFoV = FoV;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);
	View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (TargetMeetsRequirements(pEntity))
		{
			int NewHitBox = HitBox;
			if (NewHitBox >= 0)
			{
				float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
				if (fov < minFoV)
				{
					minFoV = fov;
					target = i;
				}
			}
		}
	}

	return target;
}

bool ShouldFire()
{
	IClientEntity* pLocalEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalEntity)
		return false;

	CBaseCombatWeapon* entwep = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocalEntity->GetActiveWeaponHandle());

	float flServerTime = (float)pLocalEntity->GetTickBase() * Interfaces::Globals->interval_per_tick;
	float flNextPrimaryAttack = entwep->GetNextPrimaryAttack();

	std::cout << flServerTime << " " << flNextPrimaryAttack << std::endl;

	return !(flNextPrimaryAttack > flServerTime);
}

bool CLegitBot::AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd, bool &bSendPacket)
{
	// Get the full angles
	if (point.Length() == 0) return false;

	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	static Vector Inaccuracy;

	if (timeSoFar > 0.2)
	{
		Inaccuracy.Init(-50 + rand() % 100, -50 + rand() % 100, -50 + rand() % 100);
		Inaccuracy.NormalizeInPlace();
		Inaccuracy *= Inacc;
		start_t = clock();
	}

	point += Inaccuracy;
	Vector angles;
	Vector src = pLocal->GetOrigin() + pLocal->GetViewOffset();

	CalcAngle(src, point, angles);
	GameUtils::NormaliseViewAngle(angles);

	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return false;
	}

	if (RecoilControl)
	{
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			angles -= AimPunch * 2;
			GameUtils::NormaliseViewAngle(angles);
		}
	}

	IsLocked = true;
	//-----------------------------------------------

	Vector ang = angles - pCmd->viewangles;
	bool v = false;

	if (ang.Length() > Speed)
	{
		Normalize(ang, ang);
		ang *= Speed;
	}
	else
	{
		v = true;
	}

	if (PSilent)
	{
		Vector Oldview = pCmd->viewangles;
		Vector qAimAngles = pCmd->viewangles;
		float Oldsidemove = pCmd->sidemove;
		float Oldforwardmove = pCmd->forwardmove;

		static int ChokedPackets = -1;

		if (ShouldFire() && ChokedPackets < 6)
		{
			bSendPacket = false;
			pCmd->viewangles += ang;
			pCmd->viewangles = angles;
			ChokedPackets++;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles = Oldview;
			pCmd->sidemove = Oldsidemove;
			pCmd->forwardmove = Oldforwardmove;
			ChokedPackets = -1;
		}

		pCmd->viewangles.z = 0;
	}
	else
	{
		pCmd->viewangles += ang;
		Interfaces::Engine->SetViewAngles(pCmd->viewangles);
	}
	return v;
}
