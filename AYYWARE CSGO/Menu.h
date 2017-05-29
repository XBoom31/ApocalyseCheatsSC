/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "GUI.h"
#include "Controls.h"

class CRageBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider	  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox AimbotPerfectSilentAim;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotAimStep;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;

	// Target Selection Settings
	CGroupBox TargetGroup;
	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CCheckBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSlider   TargetPointscale;

	// Accuracy Settings
	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider	  AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider   AccuracyHitchance;
	CComboBox AccuracyResolver;
	CCheckBox AccuracyPositionAdjustment;
	CSlider   AccuracySmart;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox AntiAimYaw;
	CCheckBox AntiAimEdge;
	CSlider	  AntiAimOffset;
	CCheckBox AntiAimKnife;
	CSlider   AntiAimSpeed;
	CCheckBox AntiAimTarget;

};

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CSlider   AimbotInaccuracy;
	CKeyBind  AimbotDisableVis;

	// Main
	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CSlider   TriggerDelay;

	// Main
	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CCheckBox WeaponMainPSilent;
	CSlider   WeaponMainInacc;
	CComboBox WeaponMainHitbox;

	// Pistol
	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;
	CComboBox WeaponPistHitbox;

	// Sniper
	CCheckBox WeaponSnipEnable;
	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;
	CComboBox WeaponSnipHitbox;

	CGroupBox TriggerFilterGroup;

	CCheckBox TriggerHead;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerArms;
	CCheckBox TriggerLegs;
	CCheckBox TriggerTeammates;
	CCheckBox TriggerRecoil;
	//More
	CGroupBox AimMoreGroup;
	CCheckBox FoVRadius;
	CCheckBox WeaponConfig;
	CComboBox WeaponConf;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Options Settings
	CGroupBox OptionsGroup;
	CCheckBox OptionsBox;
	CCheckBox OptionsBoxFill;
	CCheckBox OptionsBoxFillColor;
	CCheckBox OptionsName;
	CCheckBox OptionsHealth;
	CCheckBox OptionsWeapon;
	CCheckBox OptionsInfo;
	CCheckBox OptionsHelmet;
	CCheckBox OptionsKit;
	CCheckBox OptionsDefuse;
	CCheckBox OtherWireframe;
	//CCheckBox OptionsGlow;
	CComboBox OptionsChams;
	CCheckBox OptionsSkeleton;
	CCheckBox OptionsVisibleOnly;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsCompRank;
	CCheckBox OtherAsus;

	// Filters Settings
	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersC4;

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherCrosshair;
	CComboBox OtherRecoilCrosshair;
	CCheckBox OtherHitmarker;
	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky; 
	CCheckBox OtherNoFlash; 
	CSlider   OtherNoFlashVal;
	CCheckBox NightMode;
	CCheckBox OtherNoSmoke;
	CCheckBox OtherAsusWalls;
	CComboBox OtherNoHands;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
	CCheckBox OtherNoScope;


};

class CMiscTab : public CTab
{
public:
	void Setup();

	// Knife Changer
	/*CGroupBox KnifeGroup;
	CCheckBox KnifeEnable;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;
	CButton   KnifeApply;*/

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherEdgeJump;
	CComboBox OtherAutoStrafe;
	CCheckBox OtherSafeMode;
	CComboBox OtherChatSpam;
	CCheckBox OtherTeamChat;
	CSlider	  OtherChatDelay;
	CKeyBind  OtherAirStuck;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpectators;
	CCheckBox OtherThirdperson;
	CCheckBox OtherSkinChanger;
	CCheckBox OtherWatermark;
	CCheckBox OtherAutoCounterStafe;
	CKeyBind  OtherAutoCounterStafeKey;
	//CCheckBox OtherAutoAccept;
	CCheckBox OtherWalkbot;
	CComboBox OtherClantag;
	CCheckBox DisableAll;
	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;
	CTextField OtherPName;
	CTextField OtherCName;
	CButton NApply;
	// Fake Lag Settings
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CSlider   FakeLagChoke;
	CSlider	  FakeLagSend;
	CCheckBox ChokeRandomize;
	CCheckBox SendRandomize;
	//CCheckBox FakeLagWhileShooting;

	// Teleport shit cause we're cool
	CGroupBox TeleportGroup;
	CCheckBox TeleportEnable;
	CKeyBind  TeleportKey;
};
class CColorTab : public CTab
{
public:
	void Setup();

	//Groups
	CGroupBox ColorsGroup;
	CGroupBox CTNVisGroup;
	CGroupBox CTVisGroup;
	CGroupBox TNVisGroup;
	CGroupBox TVisGroup;
	//Menu Groups
	CGroupBox MenuGroup;
	CGroupBox MenuBar2;
	CGroupBox MenuInside;
	CGroupBox MenuBackround;
	//CT Not Visible
	CSlider  CTNVisColorR;
	CSlider  CTNVisColorG;
	CSlider  CTNVisColorB;
	//CT Visible
	CSlider  CTVisColorR;
	CSlider  CTVisColorG;
	CSlider  CTVisColorB;
	//T Not Visible
	CSlider  TNVisColorR;
	CSlider  TNVisColorG;
	CSlider  TNVisColorB;
	//T Visible
	CSlider  TVisColorR;
	CSlider  TVisColorG;
	CSlider  TVisColorB;

	//Menu Colors

	
	CSlider  MenuBar1R;
	CSlider  MenuBar1G;
	CSlider  MenuBar1B;
	CSlider  MenuBar2R;
	CSlider  MenuBar2G;
	CSlider  MenuBar2B;
	//Inner
	CSlider  MenuInnerR;
	CSlider  MenuInnerG;
	CSlider  MenuInnerB;

	CSlider  MenuBGR;
	CSlider  MenuBGG;
	CSlider  MenuBGB;
	CSlider  MenuOpacity;
};
class CSkinchangerTab : public CTab
{
public:
	void Setup();

	// Knife Changer/Skin Changer
	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	// Knife
	CGroupBox KnifeGroup;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;

	// Pistols
	CGroupBox PistolGroup;
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	// MPs
	

	// Rifles
	CGroupBox Riflegroup;
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;


	// Machineguns
	CGroupBox MachinegunsGroup;
	CComboBox NEGEVSkin;
	CComboBox M249Skin;

	// Snipers
	CGroupBox Snipergroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;

	// Shotguns
	CGroupBox Shotgungroup;
	CComboBox MAG7Skin;
	CComboBox XM1014Skin;
	CComboBox SAWEDOFFSkin;
	CComboBox NOVASkin;

	// Skinsettings
	CGroupBox SkinsettingsGroup;
	CCheckBox StatTrakEnable;
	/*
*/
	CTextField StatTrackAmount;
	CTextField2 SkinName;
	CTextField2 KnifeName;
};

class CSettingsTab : public CTab
{
public:
	void Setup();
	CGroupBox ButtonGroup;
	CButton SaveButton;
	CButton LoadButton;
	//Options
	CComboBox SetNr;
	CButton Unload;
	

	
};
class ApocalypseWindow : public CWindow
{
public:
	void Setup();

	CRageBotTab RageBotTab;
	CLegitBotTab LegitBotTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CColorTab ColorTab;
	CSettingsTab SettingsTab;
	CSkinchangerTab SkinchangerTab;

	CButton SaveButton;
	CButton LoadButton;
	CButton UnloadButton;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern ApocalypseWindow Window;
};