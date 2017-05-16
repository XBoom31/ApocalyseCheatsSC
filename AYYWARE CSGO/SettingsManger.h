#pragma once
#include "stdafx.h"

//Don't change the location of max value, always at the end.
enum MenuTabs
{
	Tab_Ragebot = 0,
	Tab_LegitBot,
	Tab_Visuals,
	Tab_Misc,
	Tab_Other,
	Tab_Plist,
	Tab_Config,


	MAXVALUEMENU
};
enum SubTabs
{
	Sub_Colour1 = 0,
	Sub_Colour2,
	Sub_Aimbot = 0,
	Sub_Trigger,
	Sub_Misc = 0,
	Sub_Skins,
};

enum Config {
	Config_save,
	Config_load,
	Config_type,
};

enum RagebotTab
{
	Ragebot_Enable,//
	Ragebot_Aimbot,//
	Ragebot_On_Key_Press,//
	Rabebot_On_Key_Button,//
	Ragebot_Autoscope,
	Ragebot_AutoDuck,//
	Ragebot_AutoStop,//
	Ragebot_Speed_Limit,//
	Ragebot_Speed_Limit_Amount,//
	Ragebot_Silent_Aim,//
	Ragebot_pSilent,//
	Ragebot_Multibox,
	Ragebot_PSX,
	Ragebot_Bone,
	Ragebot_Resolver,
	Ragebot_MinDam,
	AntiAim_Enable,
	AntiAim_X,
	AntiAim_Y,
	Ragebot_Height,
	AntiAim_LispAngles,
	AntiAim_AtTarget,
	Ragebot_ResolverX,
	Ragebot_ResolverY,
	Ragebot_ResolverX_Man,
	AntiAim_FY,
	AntiAim_LispAnglesX,
	AntiAim_LispAnglesY,
	Ragebot_AutoPSX,
	Ragebot_Selection,
	Ragebot_Duck,
	Ragebot_NewAimbot,
	Ragebot_ResolverY_Man,
	Ragebot_Hitchance_Amount,
	Ragebot_SA,
	Ragebot_MultiboxSpeed,
	Ragebot_LispFix,
	Ragebot_CustomPSX,
	Ragebot_NoRecoil,
	Ragebot_AutoShoot,
	Ragebot_SaveFps,
	Ragebot_AntiAimKnife,
	Ragebot_AntiAimLadders,
	Ragebot_AntiAimTargets,
	Ragebot_AntiAimWarmup,
	MAXVALUERAGE
};

enum LegitbotTab
{
	Legit_Activate,
	Legit_Aimbot_Key,

	Legit_Normal_Active,
	Legit_Normal_FOV,
	Legit_Normal_SelectionBone,
	Legit_Normal_SelectionType,
	Legit_Normal_Speed,
	Legit_Normal_Curve,
	Legit_Normal_AimTime,

	Legit_SA_Amount,
	Legit_SA_FOV,
	Legit_SA_SelectionBone,
	Legit_SA_SelectionType,
	Legit_SA_Speed,
	Legit_SA_Curve,
	Legit_SA_AimTime,


	Legit_RCS_Enable,
	Legit_RCS_X,
	Legit_RCS_Y,
	Legit_RCS_Type,

	Legit_SlowAim_Active,
	Legit_SlowAim_Type,
	Legit_SlowAim_Amount,
	Legit_SlowAim_FOV,
	Legit_SlowAim_Bone,

	Legit_TargetDelay,

	Trigger_Active,
	Trigger_Type,
	Trigger_Key,
	Trigger_Hitboxs,
	Trigger_Delay,
	Trigger_After,
	Trigger_Check_Scope,

	Trigger_Magnet_Active,
	Trigger_Magnet_FOV,
	Trigger_Magnet_SelectionBone,
	Trigger_Magnet_SelectionType,
	Trigger_Magnet_Speed,
	Trigger_Magnet_Curve,
	Trigger_Magnet_AimTime,

	Trigger_Magnet,

	Legit_Random,
	LegitBot_ME,
	Legit_HsPer,
	Legit_IgnoreInAir,
	Legit_AimPause,
	Legit_FireDelay,
	/*
	Old_Legit_Activate,
	Old_Legit_Active,
	Old_Legit_LegitFOV,
	Old_Legit_AimBone,
	Old_Legit_LegitNormalAimSpeedX,
	Old_Legit_LegitNormalAimSpeedY,
	Old_Legit_typeofaim,
	Old_Legit_Random,
	Old_Legit_Saim,
	Old_Legit_Sabone,
	Old_Legit_SAActive,
	Old_Legit_SALegitNormalAimSpeedX,
	Old_Legit_SALegitNormalAimSpeedY,
	Old_Legit_Factor,
	Old_Legit_Curve,
	Old_Legit_RCS_Enable,
	Old_Legit_RCS_X,
	Old_Legit_RCS_Y,
	Old_Legit_RCS_Type,
	Old_Legit_lastcount,
	Old_Trigger_Key,
	Old_Legit_Trick,
	Old_Trigger_Active,
	Old_Trigger_Magnet,
	Old_Trigger_Delay,
	Old_Trigger_After,
	Old_Trigger_Type,
	Old_Trigger_Fov,
	Old_Trigger_AimBone,
	Old_Trigger_SpeedY,
	Old_Trigger_SpeedX,
	Old_Trigger_Instant,
	Old_LegitBot_ME,
	Old_Legit_HsPer,
	Old_Legit_IgnoreInAir,
	Old_Legit_AimPause,
	*/
	Trigger_Lock_Active,
	Trigger_Lock_Smooth,
	Trigger_Lock_Strength,
	Trigger_Lock_Key,
	Legit_RCS_Smooth,
	Legit_ME,
	Legit_typeofaim,
	MAXVALUELEGIT
};

enum Visualstab
{
	Vis_Active,
	Vis_Glow,
	Vis_Glow_Team,
	Vis_Glow_Vis,
	Vis_Box,
	Vis_Box_Team,
	Vis_Name,
	Vis_Weapon,
	Vis_Health,
	Vis_Box_Vis,
	Vis_Background,
	Cham_Active,
	Cham_ShowTeam,
	Cham_OnlyVis,
	Cham_Weapon,
	Cham_Hands,
	Cham_Asus,
	Vis_Rainbow,
	Vis_FOV,
	Vis_Recoil,
	Vis_GreySacle,
	Vis_AimLines,
	ESP_Sonar_Active,
	Vis_Bomb,
	Vis_Skel,
	Vis_NoSky,
	Vis_Word,
	Vis_Ammo,
	Vis_GrenadePred,
	Cham_Weapon_Type,
	Cham_Hands_Type,
	Cham_Bomb,
	Vis_NoFlash,
	Vis_BombDamage,
	Vis_BombTime,
	Vis_ThirdPerson,
	Vis_CompRank,
	MAXVALUEVISUALS
};
enum MiscTab
{
	Misc_Anti_Untrust,
	Misc_Bunny_Hop,
	Misc_Auto_Strafer,
	Misc_Unhook,
	Misc_WeaponConfigs,
	Misc_WhichWeapon,
	Misc_Apistol,
	Misc_NameStealer,
	Misc_NameStealer_Index,
	//Misc_Fakelag,
	Misc_Fakelagtype,
	Misc_Airstuck_Key,
	Misc_CircleStrafe_Key,
	Misc_NameStealer_Invis,
	Misc_CircleStrafe_Max,
	Misc_Teliport,
	Misc_Teliport_Type,
	Misc_Teleport_Enable,
	Misc_CircleStrafe_Min,
	Misc_Fakelag_Shoot,
	Misc_Clan_Active,
	Misc_Clan_Index,
	Misc_CircleStrafe_Mode,
	Misc_ResetPlist,
	Misc_Spam_Active,
	Misc_Spam_Index,
	Misc_Spam_Speed,
	Misc_CircleStrafe_Enabled,
	Misc_Airstuck_Enabled,
	Misc_WaterMark,
	MAXVALUEMISC
};
enum OtherTab
{
	Other_MenuRed,
	Other_MenuGreen,
	Other_MenuBlue,
	Other_MenuAlpha,
	Other_TextRed,
	Other_TextGreen,
	Other_TextBlue,
	Other_TextAlpha,
	Other_BackgroundRed,
	Other_BackgroundGreen,
	Other_BackgroundBlue,
	Other_BackgroundAlpha,
	Other_OutlineRed,
	Other_OutlineGreen,
	Other_OutlineBlue,
	Other_OutlineAlpha,
	Other_Esp_T_Visible_Red,
	Other_Esp_T_Visible_Green,
	Other_Esp_T_Visible_Blue,
	Other_Esp_T_Visible_Alpha,
	Other_Esp_T_inVisible_Red,
	Other_Esp_T_inVisible_Green,
	Other_Esp_T_inVisible_Blue,
	Other_Esp_T_inVisible_Alpha,
	Other_Esp_CT_Visible_Red,
	Other_Esp_CT_Visible_Green,
	Other_Esp_CT_Visible_Blue,
	Other_Esp_CT_Visible_Alpha,
	Other_Esp_CT_inVisible_Red,
	Other_Esp_CT_inVisible_Green,
	Other_Esp_CT_inVisible_Blue,
	Other_Esp_CT_inVisible_Alpha,
	Other_Glow_Visible_Red,
	Other_Glow_Visible_Green,
	Other_Glow_Visible_Blue,
	Other_Glow_Visible_Alpha,
	Other_Glow_inVisible_Red,
	Other_Glow_inVisible_Green,
	Other_Glow_inVisible_Blue,
	Other_Glow_inVisible_Alpha,

	Other_Cham_Enemy_Visible_Red,
	Other_Cham_Enemy_Visible_Green,
	Other_Cham_Enemy_Visible_Blue,
	Other_Cham_Enemy_Visible_Alpha,
	Other_Cham_Enemy_inVisible_Red,
	Other_Cham_Enemy_inVisible_Green,
	Other_Cham_Enemy_inVisible_Blue,
	Other_Cham_Enemy_inVisible_Alpha,
	Other_Cham_Team_Visible_Red,
	Other_Cham_Team_Visible_Green,
	Other_Cham_Team_Visible_Blue,
	Other_Cham_Team_Visible_Alpha,
	Other_Cham_Team_inVisible_Red,
	Other_Cham_Team_inVisible_Green,
	Other_Cham_Team_inVisible_Blue,
	Other_Cham_Team_inVisible_Alpha,
	Other_Cham_Chicken_Visible_Red,
	Other_Cham_Chicken_Visible_Green,
	Other_Cham_Chicken_Visible_Blue,
	Other_Cham_Chicken_Visible_Alpha,
	Other_Cham_Chicken_inVisible_Red,
	Other_Cham_Chicken_inVisible_Green,
	Other_Cham_Chicken_inVisible_Blue,
	Other_Cham_Chicken_inVisible_Alpha,
	Other_Cham_Weapon_Red,
	Other_Cham_Weapon_Green,
	Other_Cham_Weapon_Blue,
	Other_Cham_Weapon_Alpha,
	Other_Cham_Hands_Red,
	Other_Cham_Hands_Green,
	Other_Cham_Hands_Blue,
	Other_Cham_Hands_Alpha,
	Other_SkinChanger,
	Other_SkinChanger_Update,
	Other_SkinChanger_Set,
	Other_SkinChanger_FallBack,
	Other_SkinChanger_Quality,
	Other_SkinChanger_Seed,
	Other_SkinChanger_StatTrak,
	Other_SkinChanger_Wear,
	Other_SkinChanger_ID,
	Other_Cham_Weapon_Rainbow,
	Other_Cham_Enemy_Rainbow,
	Other_Cham_Team_Rainbow,
	Other_Esp_Enemy_Rainbow,
	Other_Esp_Team_Rainbow,
	Other_Glow_Rainbow,
	Other_Cham_Chicken_Rainbow,
	MAXVALUEOTHER
};
enum PlayerListTab {
	MAXVALUESKIN,
	Plist_Bone,
	Plist_Multibox,
	Plist_MultiboxSpeed,
	Plist_CustomPSX,
	Plist_PSX,
	Plist_AutoPSX,
	Plist_ResolverX,
	Plist_ResolverY,
	Plist_LispFix,

};
enum weapongroups {
	Group_Default = 0,
	Group_Rifle,
	Group_Pistol,
	Group_Dak,
	Group_AWP,
	Group_Scout,
	Group_Shotgun,
	Group_SMG,
	Group_Heavy,



	MAXVALUEWEAPONGROUPS
};
class SettingsManger
{
public:
	bool weaponconfigs();
	void playerlist();
	void SetSetting(int Tab, int Setting, double Value);
	double GetSetting(int Tab, int Setting);
	double GetPlayer(int index, int Tab, int Setting);


	double GetMenuSetting(int Tab, int Setting);

	bool GetBoolSetting(int Tab, int Setting);
	void SetBoolSetting(int Tab, int Setting, double Value);
};

extern SettingsManger Settings;