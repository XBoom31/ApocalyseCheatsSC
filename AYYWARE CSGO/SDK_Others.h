#pragma once
#include "stdafx.h"


inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//SRC SDK VECTORADD
inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}



enum weapons {
	weapon_deagle = 1,
	weapon_elite = 2,
	weapon_fiveseven = 3,
	weapon_glock = 4,
	weapon_ak47 = 7,
	weapon_aug = 8,
	weapon_awp = 9,
	weapon_famas = 10,
	weapon_g3sg1 = 11,
	weapon_galilar = 13,
	weapon_m249 = 14,
	weapon_m4a1 = 16,
	weapon_mac10 = 17,
	weapon_p90 = 19,
	weapon_ump = 24,
	weapon_xm1014 = 25,
	weapon_bizon = 26,
	weapon_mag7 = 27,
	weapon_negev = 28,
	weapon_sawedoff = 29,
	weapon_tec9 = 30,
	weapon_taser = 31,
	weapon_hkp2000 = 32,
	weapon_mp7 = 33,
	weapon_mp9 = 34,
	weapon_nova = 35,
	weapon_p250 = 36,
	weapon_scar20 = 38,
	weapon_sg556 = 39,
	weapon_ssg08 = 40,
	weapon_knife = 42,
	weapon_flashbang = 43,
	weapon_hegrenade = 44,
	weapon_smokegrenade = 45,
	weapon_molotov = 46,
	weapon_decoy = 47,
	weapon_incgrenade = 48,
	weapon_c4 = 49,
	weapon_knife_t = 59,
	weapon_m4a1_silencer = 60,
	weapon_usp_silencer = 61,
	weapon_cz75a = 63,
	weapon_revolver = 64,
	weapon_bayonet = 500,
	weapon_knife_flip = 505,
	weapon_knife_gut = 506,
	weapon_knife_karambit = 507,
	weapon_knife_m9_bayonet = 508,
	weapon_knife_tactical = 509,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly = 515,
	weapon_knife_push = 516
};

enum EClassIds {
	_CAI_BaseNPC = 0,
	_CAK47,
	_CBaseAnimating,
	_CBaseAnimatingOverlay,
	_CBaseAttributableItem,
	_CBaseButton,
	_CBaseCombatCharacter,
	_CBaseCombatWeapon,
	_CBaseCSGrenade,
	_CBaseCSGrenadeProjectile,
	_CBaseDoor,
	_CBaseEntity,
	_CBaseFlex,
	_CBaseGrenade,
	_CBaseParticleEntity,
	_CBasePlayer,
	_CBasePropDoor,
	_CBaseTeamObjectiveResource,
	_CBaseTempEntity,
	_CBaseToggle,
	_CBaseTrigger,
	_CBaseViewModel,
	_CBaseVPhysicsTrigger,
	_CBaseWeaponWorldModel,
	_CBeam,
	_CBeamSpotlight,
	_CBoneFollower,
	_CBreakableProp,
	_CBreakableSurface,
	_CC4,
	_CCascadeLight,
	_CChicken,
	_CColorCorrection,
	_CColorCorrectionVolume,
	_CCSGameRulesProxy,
	_CCSPlayer,
	_CCSPlayerResource,
	_CCSRagdoll,
	_CCSTeam,
	_CDEagle,
	_CDecoyGrenade,
	_CDecoyProjectile,
	_CDynamicLight,
	_CDynamicProp,
	_CEconEntity,
	_CEmbers,
	_CEntityDissolve,
	_CEntityFlame,
	_CEntityFreezing,
	_CEntityParticleTrail,
	_CEnvAmbientLight,
	_CEnvDetailController,
	_CEnvDOFController,
	_CEnvParticleScript,
	_CEnvProjectedTexture,
	_CEnvQuadraticBeam,
	_CEnvScreenEffect,
	_CEnvScreenOverlay,
	_CEnvTonemapController,
	_CEnvWind,
	_CFireCrackerBlast,
	_CFireSmoke,
	_CFireTrail,
	_CFish,
	_CFlashbang,
	_CFogController,
	_CFootstepControl,
	_CFunc_Dust,
	_CFunc_LOD,
	_CFuncAreaPortalWindow,
	_CFuncBrush,
	_CFuncConveyor,
	_CFuncLadder,
	_CFuncMonitor,
	_CFuncMoveLinear,
	_CFuncOccluder,
	_CFuncReflectiveGlass,
	_CFuncRotating,
	_CFuncSmokeVolume,
	_CFuncTrackTrain,
	_CGameRulesProxy,
	_CHandleTest,
	_CHEGrenade,
	_CHostage,
	_CHostageCarriableProp,
	_CIncendiaryGrenade,
	_CInferno,
	_CInfoLadderDismount,
	_CInfoOverlayAccessor,
	_CItem_Healthshot,
	_CKnife,
	_CKnifeGG,
	_CLightGlow,
	_CMaterialModifyControl,
	_CMolotovGrenade,
	_CMolotovProjectile,
	_CMovieDisplay,
	_CParticleFire,
	_CParticlePerformanceMonitor,
	_CParticleSystem,
	_CPhysBox,
	_CPhysBoxMultiplayer,
	_CPhysicsProp,
	_CPhysicsPropMultiplayer,
	_CPhysMagnet,
	_CPlantedC4,
	_CPlasma,
	_CPlayerResource,
	_CPointCamera,
	_CPointCommentaryNode,
	_CPoseController,
	_CPostProcessController,
	_CPrecipitation,
	_CPrecipitationBlocker,
	_CPredictedViewModel,
	_CProp_Hallucination,
	_CPropDoorRotating,
	_CPropJeep,
	_CPropVehicleDriveable,
	_CRagdollManager,
	_CRagdollProp,
	_CRagdollPropAttached,
	_CRopeKeyframe,
	_CSCAR17,
	_CSceneEntity,
	_CSensorGrenade,
	_CSensorGrenadeProjectile,
	_CShadowControl,
	_CSlideshowDisplay,
	_CSmokeGrenade,
	_CSmokeGrenadeProjectile,
	_CSmokeStack,
	_CSpatialEntity,
	_CSpotlightEnd,
	_CSprite,
	_CSpriteOriented,
	_CSpriteTrail,
	_CStatueProp,
	_CSteamJet,
	_CSun,
	_CSunlightShadowControl,
	_CTeam,
	_CTeamplayRoundBasedRulesProxy,
	_CTEArmorRicochet,
	_CTEBaseBeam,
	_CTEBeamEntPoint,
	_CTEBeamEnts,
	_CTEBeamFollow,
	_CTEBeamLaser,
	_CTEBeamPoints,
	_CTEBeamRing,
	_CTEBeamRingPoint,
	_CTEBeamSpline,
	_CTEBloodSprite,
	_CTEBloodStream,
	_CTEBreakModel,
	_CTEBSPDecal,
	_CTEBubbles,
	_CTEBubbleTrail,
	_CTEClientProjectile,
	_CTEDecal,
	_CTEDust,
	_CTEDynamicLight,
	_CTEEffectDispatch,
	_CTEEnergySplash,
	_CTEExplosion,
	_CTEFireBullets,
	_CTEFizz,
	_CTEFootprintDecal,
	_CTEFoundryHelpers,
	_CTEGaussExplosion,
	_CTEGlowSprite,
	_CTEImpact,
	_CTEKillPlayerAttachments,
	_CTELargeFunnel,
	_CTEMetalSparks,
	_CTEMuzzleFlash,
	_CTEParticleSystem,
	_CTEPhysicsProp,
	_CTEPlantBomb,
	_CTEPlayerAnimEvent,
	_CTEPlayerDecal,
	_CTEProjectedDecal,
	_CTERadioIcon,
	_CTEShatterSurface,
	_CTEShowLine,
	_CTesla,
	_CTESmoke,
	_CTESparks,
	_CTESprite,
	_CTESpriteSpray,
	_CTest_ProxyToggle_Networkable,
	_CTestTraceline,
	_CTEWorldDecal,
	_CTriggerPlayerMovement,
	_CTriggerSoundOperator,
	_CVGuiScreen,
	_CVoteController,
	_CWaterBullet,
	_CWaterLODControl,
	_CWeaponAug,
	_CWeaponAWP,
	_CWeaponBaseItem,
	_CWeaponBizon,
	_CWeaponCSBase,
	_CWeaponCSBaseGun,
	_CWeaponCycler,
	_CWeaponElite,
	_CWeaponFamas,
	_CWeaponFiveSeven,
	_CWeaponG3SG1,
	_CWeaponGalil,
	_CWeaponGalilAR,
	_CWeaponGlock,
	_CWeaponHKP2000,
	_CWeaponM249,
	_CWeaponM3,
	_CWeaponM4A1,
	_CWeaponMAC10,
	_CWeaponMag7,
	_CWeaponMP5Navy,
	_CWeaponMP7,
	_CWeaponMP9,
	_CWeaponNegev,
	_CWeaponNOVA,
	_CWeaponP228,
	_CWeaponP250,
	_CWeaponP90,
	_CWeaponSawedoff,
	_CWeaponSCAR20,
	_CWeaponScout,
	_CWeaponSG550,
	_CWeaponSG552,
	_CWeaponSG556,
	_CWeaponSSG08,
	_CWeaponTaser,
	_CWeaponTec9,
	_CWeaponTMP,
	_CWeaponUMP45,
	_CWeaponUSP,
	_CWeaponXM1014,
	_CWorld,
	_DustTrail,
	_MovieExplosion,
	_ParticleSmokeGrenade,
	_RocketTrail,
	_SmokeTrail,
	_SporeExplosion,
	_SporeTrail,
};


//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150
#define CURRENTCOMMANDOFFSET 0x16E8
#define CURRENTPLAYERCOMMANDOFFSET 0x1640
#define PREIDCTIONSEEDOFFSET 0x30
#define PREDICTIONPLAYEROFFSET 0x54
#define GLOBALSOFFSET 0x53
#define WEAPONDATA_MAXRANGEOFFSET 0x77C
#define WEAPONDATA_DAMAGEOFFSET 0x778
#define WEAPONDATA_RANGEMODIFIEROFFSET 0x780
#define WEAPONDATA_PENETRATIONPOWEROFFSET 0x774
#define INPUTOFFSET 0x5F
#define GETSPREADOFFSET 0x740
#define GETCONEOFFSET 0x744
#define UPDATEACCURACYPENALTYOFFSET 0x748
#define WEAPONIDOFFSET 0x6D8
#define WEAPONDATAOFFSET 0x708
#define GETNAMEOFFSET 0x5CC
#define APPSYSTEMFACTORYOFFSET 0x3D
#define CLIENTFACTORYOFFSET 0x75
#define GLOWINDEXOFFSET 0x1DB8

//LIFESTATE
#define	LIFE_ALIVE				0 
#define	LIFE_DYING				1 
#define	LIFE_DEAD				2 
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water


//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

struct mstudiobbox_t
{
	int		bone;
	int		group; // intersection group
	Vector	bbmin; // bounding box 
	Vector	bbmax;
	int		hitboxnameindex; // offset to the name of the hitbox.
	int		pad[3];
	float	radius;
	int		pad2[4];

	char* getHitboxName()
	{
		if (hitboxnameindex == 0)
			return "";

		return ((char*)this) + hitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int                                             sznameindex;
	inline char* const              pszName(void) const { return ((char*)this) + sznameindex; }
	int                                             numhitboxes;
	int                                             hitboxindex;
	inline mstudiobbox_t*   pHitbox(int i) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
};

struct mstudiobone_t
{
	int                                     sznameindex;
	inline char * const GetName(void) const { return ((char *)this) + sznameindex; }
	int                                     parent;
	int                                     bonecontroller[6];

	Vector                          pos;
	float                           quat[4];
	Vector                          rot;
	Vector                          posscale;
	Vector                          rotscale;

	matrix3x4                     poseToBone;
	float                           qAlignment[4];
	int                                     flags;
	int                                     proctype;
	int                                     procindex;              // procedural rule
	mutable int                     physicsbone;    // index into physically simulated bone
	inline void *           GetProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int                                     surfacepropidx; // index into string tablefor property name
	inline char * const GetSurfaceProps(void) const { return ((char *)this) + surfacepropidx; }
	int                                     contents;               // See BSPFlags.h for the contents flags

	int                                     unused[8];              // remove as appropriate
};

struct studiohdr_t
{
	int                                     id;
	int                                     version;

	int                                     checksum;

	char                            name[64];
	int                                     length;


	Vector                          eyeposition;

	Vector                          illumposition;

	Vector                          hull_min;
	Vector                          hull_max;

	Vector                          view_bbmin;
	Vector                          view_bbmax;

	int                                     flags;

	int                                     numbones;
	int                                     boneindex;

	inline mstudiobone_t *GetBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };
	//	inline mstudiobone_t *pBone(int i) const { Assert(i >= 0 && i < numbones); return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };

	int                                     numbonecontrollers;
	int                                     bonecontrollerindex;

	int                                     numhitboxsets;
	int                                     hitboxsetindex;

	mstudiohitboxset_t* GetHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((byte*)this) + hitboxsetindex) + i;
	}

	inline mstudiobbox_t* GetHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);

		if (!s)
			return NULL;

		return s->pHitbox(i);
	}

	inline int GetHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);

		if (!s)
			return 0;

		return s->numhitboxes;
	}

	int                                     numlocalanim;
	int                                     localanimindex;

	int                                     numlocalseq;
	int                                     localseqindex;

	mutable int                     activitylistversion;
	mutable int                     eventsindexed;

	int                                     numtextures;
	int                                     textureindex;

	int                                     numcdtextures;
	int                                     cdtextureindex;

	int                                     numskinref;
	int                                     numskinfamilies;
	int                                     skinindex;

	int                                     numbodyparts;
	int                                     bodypartindex;

	int                                     numlocalattachments;
	int                                     localattachmentindex;

	int                                     numlocalnodes;
	int                                     localnodeindex;
	int                                     localnodenameindex;

	int                                     numflexdesc;
	int                                     flexdescindex;

	int                                     numflexcontrollers;
	int                                     flexcontrollerindex;

	int                                     numflexrules;
	int                                     flexruleindex;

	int                                     numikchains;
	int                                     ikchainindex;

	int                                     nummouths;
	int                                     mouthindex;

	int                                     numlocalposeparameters;
	int                                     localposeparamindex;

	int                                     surfacepropindex;

	int                                     keyvalueindex;
	int                                     keyvaluesize;


	int                                     numlocalikautoplaylocks;
	int                                     localikautoplaylockindex;

	float                           mass;
	int                                     contents;

	int                                     numincludemodels;
	int                                     includemodelindex;

	mutable void            *virtualModel;

	int                                     szanimblocknameindex;
	int                                     numanimblocks;
	int                                     animblockindex;

	mutable void            *animblockModel;

	int                                     bonetablebynameindex;

	void                            *pVertexBase;
	void                            *pIndexBase;

	byte                            constdirectionallightdot;

	byte                            rootLOD;

	byte                            numAllowedRootLODs;

	byte                            unused[1];

	int                                     unused4;

	int                                     numflexcontrollerui;
	int                                     flexcontrolleruiindex;
	float                           flVertAnimFixedPointScale;
	int                                     unused3[1];
	int                                     studiohdr2index;
	int                                     unused2[1];
};

class CBaseEntity;

typedef struct
{
	byte r, g, b, a;
} color32;

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};