/*
Rest In Peace ApocalypseCheats
*/

#include "Menu.h"
#include "Controls.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "CRC32.h"
#include <string>
#include "ItemDefinitions.hpp"
#include "Hooks.h"
#include "Hacks.h"
#include "Chams.h"
#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscHacks.h"
#include "CRC32.h"
#include "Resolver.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 580

ApocalypseWindow Menu::Window;

void Unloadbk()
{
	DoUnload = true;
}

void SaveCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "legit.xml");
		break;
	case 1:
		GUI.SaveWindowState(&Menu::Window, "semirage.xml");
		break;
	case 2:
		GUI.SaveWindowState(&Menu::Window, "rage.xml");
		break;
	case 3:
		GUI.SaveWindowState(&Menu::Window, "custom.xml");
		break;
	case 4:
		GUI.SaveWindowState(&Menu::Window, "custom1.xml");
		break;
	}
	
}

void LoadCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "legit.xml");
		break;
	case 1:
		GUI.LoadWindowState(&Menu::Window, "semirage.xml");
		break;
	case 2:
		GUI.LoadWindowState(&Menu::Window, "rage.xml");
		break;
	case 3:
		GUI.LoadWindowState(&Menu::Window, "custom.xml");
		break;
	case 4:
		GUI.LoadWindowState(&Menu::Window, "custom2.xml");
		break;
	}
}

void UnLoadCallbk()
{
	DoUnload = true;
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");

}/*void SetAKCB()
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	IClientEntity* WeaponEnt = Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)WeaponEnt;
	*Weapon->FallbackPaintKit() = 524;

}*/
void ApocalypseWindow::Setup()
{
	SetPosition(50, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("Apocalyplse | Private");

	RegisterTab(&RageBotTab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	RegisterTab(&ColorTab);
	RegisterTab(&SettingsTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	LegitBotTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();
	ColorTab.Setup();
	SettingsTab.Setup();

}

void CRageBotTab::Setup()
{
	
	SetTitle("RageBot");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot

	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(376, 270);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto Fire", this, &AimbotAutoFire);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(180.f);
	AimbotGroup.PlaceLabledControl("FOV Range", this, &AimbotFov);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl("Silent Aim", this, &AimbotSilentAim);

	AimbotPerfectSilentAim.SetFileId("aim_psilent");
	AimbotGroup.PlaceLabledControl("Perfect Silent", this, &AimbotPerfectSilentAim);

	AimbotAutoPistol.SetFileId("aim_autopistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

	AimbotAimStep.SetFileId("aim_aimstep");
	AimbotGroup.PlaceLabledControl("Aim Step", this, &AimbotAimStep);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key Press", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key", this, &AimbotKeyBind);

	AimbotStopKey.SetFileId("aim_stop");
	AimbotGroup.PlaceLabledControl("Stop Aim", this, &AimbotStopKey);
#pragma endregion Aimbot Controls Get Setup in here

#pragma region Target
	TargetGroup.SetPosition(16, 334);
	TargetGroup.SetText("Target");
	TargetGroup.SetSize(376, 168);
	RegisterControl(&TargetGroup);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("FOV");
	TargetSelection.AddItem("Distance");
	TargetSelection.AddItem("Health");
	TargetGroup.PlaceLabledControl("Selection", this, &TargetSelection);

	TargetFriendlyFire.SetFileId("tgt_friendlyfire");
	TargetGroup.PlaceLabledControl("Shot Trought Team", this, &TargetFriendlyFire);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Head");
	TargetHitbox.AddItem("Neck");
	TargetHitbox.AddItem("Chest");
	TargetHitbox.AddItem("Stomach");
	TargetHitbox.AddItem("Shins");
	TargetGroup.PlaceLabledControl("Hitbox", this, &TargetHitbox);

	TargetHitscan.SetFileId("tgt_hitscan");
	TargetGroup.PlaceLabledControl("Hitscan", this, &TargetHitscan);

	TargetMultipoint.SetFileId("tgt_multipoint");
	TargetGroup.PlaceLabledControl("Multipoint", this, &TargetMultipoint);

	TargetPointscale.SetFileId("tgt_pointscale");
	TargetPointscale.SetBoundaries(0.f, 10.f);
	TargetPointscale.SetValue(5.f);
	TargetGroup.PlaceLabledControl("Aim Height", this, &TargetPointscale);
#pragma endregion Targetting controls 

#pragma region Accuracy
	AccuracyGroup.SetPosition(408, 48);
	AccuracyGroup.SetText("Accuracy");
	AccuracyGroup.SetSize(360, 240); //280
	RegisterControl(&AccuracyGroup);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AccuracyGroup.PlaceLabledControl("NoRecoil", this, &AccuracyRecoil);

	AccuracyAutoWall.SetFileId("acc_awall");
	AccuracyGroup.PlaceLabledControl("AutoWall", this, &AccuracyAutoWall);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(1.f, 100.f);
	AccuracyMinimumDamage.SetValue(1.f);
	AccuracyGroup.PlaceLabledControl("AutoWall Minimum Damage", this, &AccuracyMinimumDamage);

	AccuracyAutoStop.SetFileId("acc_stop");
	AccuracyGroup.PlaceLabledControl("Auto Stop", this, &AccuracyAutoStop);

	AccuracyAutoCrouch.SetFileId("acc_crouch");
	AccuracyGroup.PlaceLabledControl("Auto Crouch", this, &AccuracyAutoCrouch);

	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl("Auto Scope", this, &AccuracyAutoScope);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(10);
	AccuracyGroup.PlaceLabledControl("Hit Chance", this, &AccuracyHitchance);
	
	AccuracyResolver.SetFileId("acc_aaa");
	AccuracyResolver.AddItem("Off");
	AccuracyResolver.AddItem("Resolver");
	AccuracyResolver.AddItem("Advanced Resolver");
	AccuracyGroup.PlaceLabledControl("Anti Aim Resolver", this, &AccuracyResolver);

	//AccuracyPositionAdjustment.SetFileId("acc_posadj");
	//AccuracyGroup.PlaceLabledControl("Position Adjustment", this, &AccuracyPositionAdjustment);

	AccuracySmart.SetFileId("acc_smart");
	AccuracySmart.SetBoundaries(0, 20);
	AccuracySmart.SetValue(0);
	AccuracyGroup.PlaceLabledControl("Smart Aim", this, &AccuracySmart);
#pragma endregion  Accuracy controls get Setup in here

#pragma region AntiAim
	AntiAimGroup.SetPosition(408, 307); //344
	AntiAimGroup.SetText("Anti Aim");
	AntiAimGroup.SetSize(360, 195);
	RegisterControl(&AntiAimGroup);

	AntiAimEnable.SetFileId("aa_enable");
	AntiAimGroup.PlaceLabledControl("Enable", this, &AntiAimEnable);

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("None");
	AntiAimPitch.AddItem("Down");
	AntiAimPitch.AddItem("SMAC Safe");
	AntiAimPitch.AddItem("Jitter");
	AntiAimPitch.AddItem("Static");
	AntiAimPitch.AddItem("Fake Down");
	AntiAimPitch.AddItem("Lisp Down");
	AntiAimPitch.AddItem("Lisp Up");
	AntiAimGroup.PlaceLabledControl("Pitch", this, &AntiAimPitch);

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("None");
	AntiAimYaw.AddItem("Fake Edge");
	AntiAimYaw.AddItem("Fake Sideways");
	AntiAimYaw.AddItem("Fake Static");
	AntiAimYaw.AddItem("T Fake");
	AntiAimYaw.AddItem("Fake Jitter");
	AntiAimYaw.AddItem("Jitter");
	AntiAimYaw.AddItem("T Jitter");
	AntiAimYaw.AddItem("Back Jitter");
	AntiAimYaw.AddItem("Backwards");
	AntiAimYaw.AddItem("Fake Lowerbody");
	AntiAimYaw.AddItem("Custom");
	AntiAimGroup.PlaceLabledControl("Yaw", this, &AntiAimYaw);

	AntiAimEdge.SetFileId("aa_edge");
	AntiAimGroup.PlaceLabledControl("Auto Edge", this, &AntiAimEdge);

	AntiAimOffset.SetFileId("aa_offset");
	AntiAimOffset.SetBoundaries(0, 360);
	AntiAimOffset.SetValue(69);
	AntiAimGroup.PlaceLabledControl("Yaw Offset", this, &AntiAimOffset);

	AntiAimKnife.SetFileId("aa_knife");
	AntiAimGroup.PlaceLabledControl("SpinBot With Knife", this, &AntiAimKnife);

	AntiAimSpeed.SetFileId("aa_offset");
	AntiAimSpeed.SetBoundaries(0, 179.9);
	AntiAimSpeed.SetValue(69);
	AntiAimGroup.PlaceLabledControl("Speed", this, &AntiAimSpeed);

	//AntiAimTarget.SetFileId("aa_target");
	//AntiAimGroup.PlaceLabledControl("SpinBot At Target", this, &AntiAimTarget);
#pragma endregion  AntiAim controls get setup in here
}

void CLegitBotTab::Setup()
{
	SetTitle("LegitBot");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(240, 210);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto Fire", this, &AimbotAutoFire);

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl("Friendly Fire", this, &AimbotFriendlyFire);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key Press", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key Bind", this, &AimbotKeyBind);
	
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

#pragma endregion Aimbot shit

#pragma region Triggerbot
	TriggerGroup.SetPosition(272, 48);
	TriggerGroup.SetText("Triggerbot");
	TriggerGroup.SetSize(240, 210);
	RegisterControl(&TriggerGroup);

	TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl("Enable", this, &TriggerEnable);

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl("On Key Press", this, &TriggerKeyPress);

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl("Key Bind", this, &TriggerKeyBind);

	TriggerDelay.SetFileId("trig_time");
	TriggerDelay.SetBoundaries(1.f, 1000.f);
	TriggerDelay.SetValue(1.f);
	TriggerGroup.PlaceLabledControl("Delay (ms)", this, &TriggerDelay);
#pragma endregion Triggerbot stuff

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(16, 274);
	WeaponMainGroup.SetText("Rifles/Other - DONT USE");
	WeaponMainGroup.SetSize(240, 210);
	RegisterControl(&WeaponMainGroup);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 2.f); 
	WeaponMainSpeed.SetValue(1.0f);
	WeaponMainGroup.PlaceLabledControl("Max Speed", this, &WeaponMainSpeed);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.f, 30.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl("FoV", this, &WeaponMainFoV);

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainGroup.PlaceLabledControl("Recoil", this, &WeaponMainRecoil);

	WeaponMainPSilent.SetFileId("main_psilent");
	WeaponMainGroup.PlaceLabledControl("Silent", this, &WeaponMainPSilent);

	WeaponMainInacc.SetFileId("main_inacc");
	WeaponMainInacc.SetBoundaries(0.f, 15.f);
	WeaponMainGroup.PlaceLabledControl("Inaccuracy", this, &WeaponMainInacc);

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl("Hitbox", this, &WeaponMainHitbox);
#pragma endregion

#pragma region Pistols
	WeaponPistGroup.SetPosition(272, 274);
	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetSize(240, 210);
	RegisterControl(&WeaponPistGroup);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 2.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl("Max Speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 5.f);
	WeaponPistFoV.SetValue(0.78f);
	WeaponPistGroup.PlaceLabledControl("FoV", this, &WeaponPistFoV);

	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistGroup.PlaceLabledControl("Recoil", this, &WeaponPistRecoil);

	WeaponPistPSilent.SetFileId("pist_psilent");
	WeaponPistGroup.PlaceLabledControl("Silent", this, &WeaponPistPSilent);

	WeaponPistInacc.SetFileId("pist_inacc");
	WeaponPistInacc.SetBoundaries(0.f, 15.f);
	WeaponPistInacc.SetValue(0.f);
	WeaponPistGroup.PlaceLabledControl("Inaccuracy", this, &WeaponPistInacc);

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl("Hitbox", this, &WeaponPistHitbox);
#pragma endregion

#pragma region Snipers
	WeaponSnipGroup.SetPosition(528, 274);
	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetSize(240, 210);
	RegisterControl(&WeaponSnipGroup);

	

	WeaponSnipSpeed.SetFileId("wconf_speed_ak");
	WeaponSnipSpeed.SetBoundaries(0.1f, 2.f);
	WeaponSnipSpeed.SetValue(1.0f);
	WeaponSnipGroup.PlaceLabledControl("Max Speed", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("wconf_fov_ak");
	WeaponSnipFoV.SetBoundaries(0.1f, 30.f);
	WeaponSnipFoV.SetValue(5.f);
	WeaponSnipGroup.PlaceLabledControl("FoV", this, &WeaponSnipFoV);

	WeaponSnipRecoil.SetFileId("wconf_recoil_ak");
	WeaponSnipGroup.PlaceLabledControl("Recoil", this, &WeaponSnipRecoil);

	WeaponSnipPSilent.SetFileId("wconf_psilent_ak");
	WeaponSnipGroup.PlaceLabledControl("Silent", this, &WeaponSnipPSilent);

	WeaponSnipInacc.SetFileId("wconf_inacc_ak");
	WeaponSnipInacc.SetBoundaries(0.f, 15.f);
	WeaponSnipGroup.PlaceLabledControl("Inaccuracy", this, &WeaponSnipInacc);

	WeaponSnipHitbox.SetFileId("wconf_hitbox_ak");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
	WeaponSnipGroup.PlaceLabledControl("Hitbox", this, &WeaponSnipHitbox);

	WeaponSnipEnable.SetFileId("wconf_enable_ak");
	WeaponSnipGroup.PlaceLabledControl("Aimbot Unscoped", this, &WeaponSnipEnable);
#pragma endregion

#pragma More
	AimMoreGroup.SetPosition(528, 48);
	AimMoreGroup.SetText("More");
	AimMoreGroup.SetSize(240, 210);
	RegisterControl(&AimMoreGroup);

	FoVRadius.SetFileId("fov_aim");
	AimMoreGroup.PlaceLabledControl("FoV Radius", this, &FoVRadius);

	WeaponConfig.SetFileId("wconf_toggle");
	AimMoreGroup.PlaceLabledControl("Weapon Configs", this, &WeaponConfig);
	WeaponConf.SetFileId("wconf_weapon");
	WeaponConf.AddItem("AK-47");
	WeaponConf.AddItem("AUG");
	WeaponConf.AddItem("AWP");
	WeaponConf.AddItem("CZ75-Auto");
	WeaponConf.AddItem("Desert Eagle");
	WeaponConf.AddItem("Dual Beretas");
	WeaponConf.AddItem("Famas");
	WeaponConf.AddItem("Five-SeveN");
	WeaponConf.AddItem("Galil AR");
	WeaponConf.AddItem("G3SG1");
	WeaponConf.AddItem("Glock-18");
	WeaponConf.AddItem("M249");
	WeaponConf.AddItem("M4A1-S");
	WeaponConf.AddItem("M4A4");
	WeaponConf.AddItem("MAC-10");
	WeaponConf.AddItem("MAG-7");
	WeaponConf.AddItem("MP7");
	WeaponConf.AddItem("MP9");
	WeaponConf.AddItem("Negev");
	WeaponConf.AddItem("Nova");
	WeaponConf.AddItem("P2000");
	WeaponConf.AddItem("P250");
	WeaponConf.AddItem("P90");
	WeaponConf.AddItem("PP-Bizon");
	WeaponConf.AddItem("R8 Revolver");
	WeaponConf.AddItem("Sawed-Off");
	WeaponConf.AddItem("SCAR-20");
	WeaponConf.AddItem("SSG 08");
	WeaponConf.AddItem("SG 553");
	WeaponConf.AddItem("TEC-9");
	WeaponConf.AddItem("UMP-45");
	WeaponConf.AddItem("USP-S");
	WeaponConf.AddItem("XM-1014");
	AimMoreGroup.PlaceLabledControl("Weapon", this, &WeaponConf);


#pragma endregion
}

void CVisualTab::Setup()
{
	SetTitle("ESP");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Options
	OptionsGroup.SetText("Options");
	OptionsGroup.SetPosition(16, 48);
	OptionsGroup.SetSize(193, 430);
	RegisterControl(&OptionsGroup);

	OptionsBox.SetFileId("opt_box");
	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);

	OptionsHealth.SetFileId("opt_hp");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionsHealth);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	OptionsChams.SetFileId("opt_chams");
	OptionsChams.AddItem("Off");
	OptionsChams.AddItem("Normal");
	OptionsChams.AddItem("Flat");
	OptionsGroup.PlaceLabledControl("Chams", this, &OptionsChams);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	OptionsVisibleOnly.SetFileId("opt_vonly");
	OptionsGroup.PlaceLabledControl("Visible Only", this, &OptionsVisibleOnly);

	OptionsAimSpot.SetFileId("opt_aimspot");
	OptionsGroup.PlaceLabledControl("Head Cross", this, &OptionsAimSpot);
	
	OptionsCompRank.SetFileId("opt_comprank");
	OptionsGroup.PlaceLabledControl("Player Ranks", this, &OptionsCompRank);

	
#pragma endregion Setting up the Options controls

#pragma region Filters
	FiltersGroup.SetText("Filters");
	FiltersGroup.SetPosition(225, 48);
	FiltersGroup.SetSize(193, 430);
	RegisterControl(&FiltersGroup);

	FiltersAll.SetFileId("ftr_all");
	FiltersGroup.PlaceLabledControl("All", this, &FiltersAll);

	FiltersPlayers.SetFileId("ftr_players");
	FiltersGroup.PlaceLabledControl("Players", this, &FiltersPlayers);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	FiltersGroup.PlaceLabledControl("Enemies Only", this, &FiltersEnemiesOnly);

	FiltersWeapons.SetFileId("ftr_weaps");
	FiltersGroup.PlaceLabledControl("Weapons", this, &FiltersWeapons);

	FiltersChickens.SetFileId("ftr_chickens");
	FiltersGroup.PlaceLabledControl("Chickens", this, &FiltersChickens);

	FiltersC4.SetFileId("ftr_c4");
	FiltersGroup.PlaceLabledControl("C4", this, &FiltersC4);
#pragma endregion Setting up the Filters controls

#pragma region Other
	OtherGroup.SetText("Other");
	OtherGroup.SetPosition(434, 48);
	OtherGroup.SetSize(334, 430);
	RegisterControl(&OtherGroup);

	OtherCrosshair.SetFileId("otr_xhair");
	OtherGroup.PlaceLabledControl("Crosshair", this, &OtherCrosshair);

	OtherRecoilCrosshair.SetFileId("otr_recoilhair");
	OtherRecoilCrosshair.AddItem("Off");
	OtherRecoilCrosshair.AddItem("Recoil Position");
	OtherRecoilCrosshair.AddItem("Radius");
	OtherGroup.PlaceLabledControl("Recoil Crosshair", this, &OtherRecoilCrosshair);

	OtherRadar.SetFileId("otr_radar");
	OtherGroup.PlaceLabledControl("Radar", this, &OtherRadar);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("No Visual Recoil", this, &OtherNoVisualRecoil);

	OtherNoFlash.SetFileId("otr_noflash");
	//OtherNoFlas.SetBoundaries(0.f, 90.f);
	//OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("No Flash Enable", this, &OtherNoFlash);

	OtherNoFlashVal.SetFileId("otr_noflashval");
	OtherNoFlashVal.SetBoundaries(0,255);
	OtherViewmodelFOV.SetValue(200);
	OtherGroup.PlaceLabledControl("Max Flash", this, &OtherNoFlashVal);

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Transparent");
	OtherNoHands.AddItem("Chams");
	OtherNoHands.AddItem("Rainbow");
	OtherGroup.PlaceLabledControl("Hands", this, &OtherNoHands);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 90.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Viewmodel FOV Changer", this, &OtherViewmodelFOV);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl("Field of View Changer", this, &OtherFOV);

	OtherNoSky.SetFileId("otr_nosky");
	OtherGroup.PlaceLabledControl("NoSky", this, &OtherNoSky);

	OtherNoSmoke.SetFileId("otr_nosmoke");
	OtherGroup.PlaceLabledControl("NoSmoke", this, &OtherNoSmoke);

	
#pragma endregion Setting up the Other controls
}

void CMiscTab::Setup()
{
	SetTitle("Misc");

#pragma region Knife
	KnifeGroup.SetPosition(16, 16);
	KnifeGroup.SetSize(360, 126);
	KnifeGroup.SetText("Knife Changer");
	RegisterControl(&KnifeGroup);

	KnifeEnable.SetFileId("knife_enable");
	KnifeGroup.PlaceLabledControl("Enable", this, &KnifeEnable);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Falchion Knife");
    KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeSkin.AddItem("Doppler Sapphire");
	KnifeSkin.AddItem("Doppler Ruby");
	KnifeSkin.AddItem("Tiger Tooth");
	KnifeSkin.AddItem("Lore");
	KnifeSkin.AddItem("Forest DDPAT");
	KnifeSkin.AddItem("Crimson Web");
	KnifeSkin.AddItem("Slaughter");
	KnifeSkin.AddItem("Vanilla");
	KnifeSkin.AddItem("Fade");
	KnifeSkin.AddItem("Night");
	KnifeSkin.AddItem("Blue Steel");
	KnifeSkin.AddItem("Stained");
	KnifeSkin.AddItem("Case Hardended");
	KnifeSkin.AddItem("Safari Mesh");
	KnifeSkin.AddItem("Boreal Forest");
	KnifeSkin.AddItem("Ultaviolet");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Romania's Flag <3");
	

	KnifeGroup.PlaceLabledControl("Skin", this, &KnifeSkin);

	KnifeApply.SetText("Apply Knife");
	KnifeApply.SetCallback(KnifeApplyCallbk);
	KnifeGroup.PlaceLabledControl("", this, &KnifeApply);

#pragma endregion

#pragma region Other
	OtherGroup.SetPosition(408, 16);
	OtherGroup.SetSize(360, 430);
	OtherGroup.SetText("Other");
	RegisterControl(&OtherGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl("Bhop", this, &OtherAutoJump);

	OtherEdgeJump.SetFileId("otr_edgejump");
	OtherGroup.PlaceLabledControl("Edge Jump", this, &OtherEdgeJump);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("Off");
	OtherAutoStrafe.AddItem("Legit");
	OtherAutoStrafe.AddItem("Rage");
	OtherGroup.PlaceLabledControl("Auto Strafer", this, &OtherAutoStrafe);

	OtherAutoCounterStafe.SetFileId("otr_autocs");
	OtherGroup.PlaceLabledControl("Auto Counter-Stafer Enable", this, &OtherAutoCounterStafe);

	OtherAutoCounterStafeKey.SetFileId("otr_autocs_key");
	OtherGroup.PlaceLabledControl("Auto Counter-Stafer Key", this, &OtherAutoCounterStafeKey);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl("Safe Mode", this, &OtherSafeMode);

	OtherChatSpam.SetFileId("otr_spam");
	OtherChatSpam.AddItem("Off");
	OtherChatSpam.AddItem("Namestealer");
	OtherChatSpam.AddItem("Apocalypse - CS");
	OtherChatSpam.AddItem("Apocalypse - NS");
	OtherChatSpam.AddItem("Rekt");
	OtherChatSpam.AddItem("Aimware - CS");
	OtherChatSpam.AddItem("Aimware - NS");
	OtherGroup.PlaceLabledControl("Chat Spam", this, &OtherChatSpam);

	OtherClantag.SetFileId("otr_spam");
	OtherClantag.AddItem("Off");
	OtherClantag.AddItem("Apocalypse");
	OtherClantag.AddItem("'SlideShow'");
	OtherClantag.AddItem("None");
	OtherClantag.AddItem("Valve");
	OtherGroup.PlaceLabledControl("Custom Clantag", this, &OtherClantag);

	OtherTeamChat.SetFileId("otr_teamchat");
	OtherGroup.PlaceLabledControl("Team Chat Only", this, &OtherTeamChat);

	OtherChatDelay.SetFileId("otr_chatdelay");
	OtherChatDelay.SetBoundaries(0.1, 3.0);
	OtherChatDelay.SetValue(0.5);
	OtherGroup.PlaceLabledControl("Spam Delay", this, &OtherChatDelay);

	OtherAirStuck.SetFileId("otr_astuck");
	OtherGroup.PlaceLabledControl("Air Stuck", this, &OtherAirStuck);

	OtherSpectators.SetFileId("otr_speclist");
	OtherGroup.PlaceLabledControl("Spectators List", this, &OtherSpectators);

	OtherThirdperson.SetFileId("aa_thirdpsr");
	OtherGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdperson);

	OtherSpectators.SetFileId("otr_skin");
	OtherGroup.PlaceLabledControl("SkinChanger", this, &OtherSkinChanger);

	bool wmon;

	
    OtherWatermark.SetFileId("otr_watermark");
	
	OtherGroup.PlaceLabledControl("Watermark", this, &OtherWatermark);

	//DisableAll.SetFileId("otr_disableall");
	//OtherGroup.PlaceLabledControl("Disable All", this, &DisableAll);

#pragma endregion other random options

#pragma region FakeLag
	FakeLagGroup.SetPosition(16, 160);
	FakeLagGroup.SetSize(360, 141);
	FakeLagGroup.SetText("Fake Lag");
	RegisterControl(&FakeLagGroup);

	FakeLagEnable.SetFileId("fakelag_enable");
	FakeLagGroup.PlaceLabledControl("Fake Lag", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 16);
	FakeLagChoke.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Choke Factor", this, &FakeLagChoke);

	FakeLagSend.SetFileId("fakelag_send");
	FakeLagSend.SetBoundaries(0, 16);
	FakeLagSend.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Send Factor", this, &FakeLagSend);

	ChokeRandomize.SetFileId("choke_random");
	FakeLagGroup.PlaceLabledControl("Randomize Choke", this, &ChokeRandomize);

	SendRandomize.SetFileId("send_random");
	FakeLagGroup.PlaceLabledControl("Randomize Send", this, &SendRandomize);
#pragma endregion fakelag shit

#pragma region Teleport
	TeleportGroup.SetPosition(16, 316);
	TeleportGroup.SetSize(360, 75);
	TeleportGroup.SetText("Teleport");
	RegisterControl(&TeleportGroup);

	TeleportEnable.SetFileId("teleport_enable");
	TeleportGroup.PlaceLabledControl("Enable", this, &TeleportEnable);

	TeleportKey.SetFileId("teleport_key");
	TeleportGroup.PlaceLabledControl("Key", this, &TeleportKey);

#pragma endregion

/*#pragma region OverideFov
	FOVGroup.SetPosition(16, 365);
	FOVGroup.SetSize(360, 75);
	FOVGroup.SetText("FOV Changer");
	RegisterControl(&FOVGroup);

	FOVEnable.SetFileId("fov_enable");
	FOVGroup.PlaceLabledControl("Enable", this, &FOVEnable);

	FOVSlider.SetFileId("fov_slider");
	FOVSlider.SetBoundaries(0, 200);
	FOVSlider.SetValue(0);
	FOVGroup.PlaceLabledControl("FOV Amount", this, &FOVSlider);

#pragma endregion*/
}

/*void CPlayersTab::Setup()
{
	SetTitle("PlayerList");

#pragma region PList

	pListGroup.SetPosition(16, 16);
	pListGroup.SetSize(680, 200);
	pListGroup.SetText("Player List");
	pListGroup.SetColumns(2);
	RegisterControl(&pListGroup);

	pListPlayers.SetPosition(26, 46);
	pListPlayers.SetSize(640, 50);
	pListPlayers.SetHeightInItems(20);
	RegisterControl(&pListPlayers);

#pragma endregion

#pragma region Options
	
	OptionsGroup.SetPosition(16, 257);
	OptionsGroup.SetSize(450, 120);
	OptionsGroup.SetText("Player Options");
	RegisterControl(&OptionsGroup);

	OptionsFriendly.SetFileId("pl_friendly");
	OptionsGroup.PlaceLabledControl("Friendly", this, &OptionsFriendly);

	OptionsAimPrio.SetFileId("pl_priority");
	OptionsGroup.PlaceLabledControl("Priority", this, &OptionsAimPrio);

	OptionsCalloutSpam.SetFileId("pl_callout");
	OptionsGroup.PlaceLabledControl("Callout Spam", this, &OptionsCalloutSpam);

#pragma endregion
}

DWORD GetPlayerListIndex(int EntId)
{
	player_info_t pinfo;
	Interfaces::Engine->GetPlayerInfo(EntId, &pinfo);

	// Bot
	if (pinfo.guid[0] == 'B' && pinfo.guid[1] == 'O')
	{
		char buf[64]; sprintf_s(buf, "BOT_420%sAY", pinfo.name);
		return CRC32(buf, 64);
	}
	else
	{
		return CRC32(pinfo.guid, 32);
	}
}

bool IsFriendly(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Friendly;
	}

	return false;
}

bool IsAimPrio(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].AimPrio;
	}

	return false;
}

bool IsCalloutTarget(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Callout;
	}

	return false;
}

void UpdatePlayerList()
{
	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal && pLocal->IsAlive())
	{
		Menu::Window.Playerlist.pListPlayers.ClearItems();

		// Loop through all active entitys
		for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
		{
			// Get the entity

			player_info_t pinfo;
			if (i != Interfaces::Engine->GetLocalPlayer() && Interfaces::Engine->GetPlayerInfo(i, &pinfo))
			{
				IClientEntity* pEntity = Interfaces::EntList->GetClientEntity(i);
				int HP = 100; char* Location = "Unknown";
				char *Friendly = " ", *AimPrio = " ";

				DWORD plistId = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());
				if (PlayerList.find(plistId) != PlayerList.end())
				{
					Friendly = PlayerList[plistId].Friendly ? "Friendly" : "";
					AimPrio = PlayerList[plistId].AimPrio ? "AimPrio" : "";
				}

				if (pEntity && !pEntity->IsDormant())
				{
					HP = pEntity->GetHealth();
					Location = pEntity->GetLastPlaceName();
				}

				char nameBuffer[512];
				sprintf_s(nameBuffer, "%-24s %-10s %-10s [%d HP] [Last Seen At %s]", pinfo.name, IsFriendly(i) ? "Friend" : " ", IsAimPrio(i) ? "AimPrio" : " ", HP, Location);
				Menu::Window.Playerlist.pListPlayers.AddItem(nameBuffer, i);

			}

		}

		DWORD meme = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());

		// Have we switched to a different player?
		static int PrevSelectedPlayer = 0;
		if (PrevSelectedPlayer != Menu::Window.Playerlist.pListPlayers.GetValue())
		{
			if (PlayerList.find(meme) != PlayerList.end())
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(PlayerList[meme].Friendly);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(PlayerList[meme].AimPrio);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(PlayerList[meme].Callout);

			}
			else
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(false);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(false);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(false);

			}
		}
		PrevSelectedPlayer = Menu::Window.Playerlist.pListPlayers.GetValue();

		PlayerList[meme].Friendly = Menu::Window.Playerlist.OptionsFriendly.GetState();
		PlayerList[meme].AimPrio = Menu::Window.Playerlist.OptionsAimPrio.GetState();
		PlayerList[meme].Callout = Menu::Window.Playerlist.OptionsCalloutSpam.GetState();
	}
}*/

void CColorTab::Setup()
{
	SetTitle("Colors");
#pragma region Colors
	CTNVisGroup.SetPosition(16, 16);
	CTNVisGroup.SetSize(360, 100);
	CTNVisGroup.SetText("CT Not Visible");
	RegisterControl(&CTNVisGroup);

	// CT NOT VISIBLE
	CTNVisColorR.SetFileId("ct_not_vis_r");
	CTNVisColorR.SetBoundaries(1, 255);
	CTNVisColorR.SetValue(15);
	CTNVisGroup.PlaceLabledControl("Red", this, &CTNVisColorR);

	CTNVisColorG.SetFileId("ct_not_vis_g");
	CTNVisColorG.SetBoundaries(1, 255);
	CTNVisColorG.SetValue(1);
	CTNVisGroup.PlaceLabledControl("Green", this, &CTNVisColorG);

	CTNVisColorB.SetFileId("ct_not_vis_b");
	CTNVisColorB.SetBoundaries(1, 255);
	CTNVisColorB.SetValue(220);
	CTNVisGroup.PlaceLabledControl("Blue", this, &CTNVisColorB);



	//CT VISIBLE
	CTVisGroup.SetPosition(408, 16);
	CTVisGroup.SetSize(360, 100);
	CTVisGroup.SetText("CT Visible");
	RegisterControl(&CTVisGroup);

	CTVisColorR.SetFileId("ct_vis_r");
	CTVisColorR.SetBoundaries(1, 255);
	CTVisColorR.SetValue(187);
	CTVisGroup.PlaceLabledControl(" Red", this, &CTVisColorR);

	CTVisColorG.SetFileId("ct_vis_g");
	CTVisColorG.SetBoundaries(1, 255);
	CTVisColorG.SetValue(1);
	CTVisGroup.PlaceLabledControl("Green", this, &CTVisColorG);

	CTVisColorB.SetFileId("ct_vis_b");
	CTVisColorB.SetBoundaries(1, 255);
	CTVisColorB.SetValue(255);
	CTVisGroup.PlaceLabledControl("Blue", this, &CTVisColorB);

	//T Not Visible
	TNVisGroup.SetPosition(16, 137);
	TNVisGroup.SetSize(360, 100);
	TNVisGroup.SetText("T Not Visible");
	RegisterControl(&TNVisGroup);

	TNVisColorR.SetFileId("t_not_vis_r");
	TNVisColorR.SetBoundaries(1, 255);
	TNVisColorR.SetValue(235);
	TNVisGroup.PlaceLabledControl("Red", this, &TNVisColorR);

	TNVisColorG.SetFileId("t_not_vis_g");
	TNVisColorG.SetBoundaries(1, 255);
	TNVisColorG.SetValue(50);
	TNVisGroup.PlaceLabledControl("Red", this, &TNVisColorG);

	TNVisColorB.SetFileId("t_not_vis_b");
	TNVisColorB.SetBoundaries(1, 255);
	TNVisColorB.SetValue(1);
	TNVisGroup.PlaceLabledControl("Blue", this, &TNVisColorB);

	// T Vis Color

	TVisGroup.SetPosition(408, 137);
	TVisGroup.SetSize(360, 100);
	TVisGroup.SetText("T Visible");
	RegisterControl(&TVisGroup);

	TVisColorR.SetFileId("t_vis_r");
	TVisColorR.SetBoundaries(1, 255);
	TVisColorR.SetValue(255);
	TVisGroup.PlaceLabledControl("Red", this, &TVisColorR);

	TVisColorG.SetFileId("t_vis_g");
	TVisColorG.SetBoundaries(1, 255);
	TVisColorG.SetValue(200);
	TVisGroup.PlaceLabledControl("Green", this, &TVisColorG);

	TVisColorB.SetFileId("t_vis_b");
	TVisColorB.SetBoundaries(1, 255);
	TVisColorB.SetValue(1);
	TVisGroup.PlaceLabledControl("Blue", this, &TVisColorB);


#pragma endregion
	/**/
#pragma MenuGroup
	MenuGroup.SetPosition(16, 258);
	MenuGroup.SetSize(360, 100);
	MenuGroup.SetText("Bar Color 1");
	RegisterControl(&MenuGroup);

	//Menu Gradient Color 1
	MenuBar1R.SetFileId("bar_grad_1R");
	MenuBar1R.SetBoundaries(0, 255);
	MenuBar1R.SetValue(255);
	MenuGroup.PlaceLabledControl("Red", this, &MenuBar1R);

	MenuBar1G.SetFileId("bar_grad_1G");
	MenuBar1G.SetBoundaries(0, 255);
	MenuBar1G.SetValue(144);
	MenuGroup.PlaceLabledControl("Green", this, &MenuBar1G);

	MenuBar1B.SetFileId("bar_grad_1B");
	MenuBar1B.SetBoundaries(0, 255);
	MenuBar1B.SetValue(0);
	MenuGroup.PlaceLabledControl("Blue", this, &MenuBar1B);


	//Menu Gradient Color 2
	MenuBar2.SetPosition(408, 258);
	MenuBar2.SetSize(360, 100);
	MenuBar2.SetText("Bar Color 2");
	RegisterControl(&MenuBar2);

	MenuBar2R.SetFileId("bar_grad_2R");
	MenuBar2R.SetBoundaries(0, 255);
	MenuBar2R.SetValue(255);
	MenuBar2.PlaceLabledControl("Red", this, &MenuBar2R);

	MenuBar2G.SetFileId("bar_grad_2G");
	MenuBar2G.SetBoundaries(0, 255);
	MenuBar2G.SetValue(93);
	MenuBar2.PlaceLabledControl("Green", this, &MenuBar2G);

	MenuBar2B.SetFileId("bar_grad_2B");
	MenuBar2B.SetBoundaries(0, 255);
	MenuBar2B.SetValue(0);
	MenuBar2.PlaceLabledControl("Blue", this, &MenuBar2B);


	//MenuOpacity.SetFileId("men_oapacity");
	//MenuOpacity.SetBoundaries(0, 255);
	//MenuOpacity.SetValue(0);
	//MenuGroup.PlaceLabledControl("Menu Opacity", this, &MenuOpacity);

	//Inner
	MenuInside.SetPosition(408, 258);
	MenuInside.SetSize(360, 100);
	MenuInside.SetText("Menu Inner Color");
	RegisterControl(&MenuInside);

	MenuInnerR.SetFileId("in_R");
	MenuInnerR.SetBoundaries(0, 255);
	MenuInnerR.SetValue(255);
	MenuInside.PlaceLabledControl("Red", this, &MenuInnerR);

	MenuInnerG.SetFileId("in_G");
	MenuInnerG.SetBoundaries(0, 255);
	MenuInnerG.SetValue(93);
	MenuInside.PlaceLabledControl("Green", this, &MenuInnerG);

	MenuInnerB.SetFileId("in_B");
	MenuInnerB.SetBoundaries(0, 255);
	MenuInnerB.SetValue(0);
	MenuInside.PlaceLabledControl("Blue", this, &MenuInnerB);

#pragma endregion

}
void CSettingsTab::Setup()
{

	SetTitle("Settings");
#pragma ButtonGroup
	ButtonGroup.SetPosition(16, 16);
	ButtonGroup.SetSize(360, 460);
	ButtonGroup.SetText("Buttons");
	RegisterControl(&ButtonGroup);

	SaveButton.SetText("Save Configuration");
	SaveButton.SetCallback(SaveCallbk);
	ButtonGroup.PlaceLabledControl("Save", this, &SaveButton);

	LoadButton.SetText("Load Configuration");
	LoadButton.SetCallback(LoadCallbk);
	ButtonGroup.PlaceLabledControl("Load", this, &LoadButton);

	//Options


	SetNr.AddItem("Legit");
	SetNr.AddItem("Semi Rage");
	SetNr.AddItem("Rage");
	SetNr.AddItem("Custom 1");
	SetNr.AddItem("Custom 2");
	SetNr.AddItem("Disable All");
	ButtonGroup.PlaceLabledControl("Number", this, &SetNr);

	Unload.SetText("Force Crash(time out)");
	Unload.SetCallback(Unloadbk);
	ButtonGroup.PlaceLabledControl("", this, &Unload);
};


void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
	// General Processing

	// If the "all filter is selected tick all the others
	if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersChickens.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
	}
	

	GUI.Update();
	GUI.Draw();

	
}


