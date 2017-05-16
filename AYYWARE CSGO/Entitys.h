#pragma once
#include "stdafx.h"

#define BONE_USED_BY_HITBOX 0x00000100

enum weaponClassification {
	WEPTYPE_NONE,
	WEPTYPE_PISTOL,
	WEPTYPE_RIFLE,
	WEPTYPE_SNIPER,
	WEPTYPE_SMG,
	WEPTYPE_SHOTGUN,
	WEPTYPE_MACHINEGUN,
	WEPTYPE_GRENADE,
	WEPTYPE_OTHER
};

enum {
	deagle = 1,
	p2000 = 32,
	fiveseven = 3,
	glock = 4,
	dualelites = 2,
	ak = 7,
	aug = 8,
	awp = 9,
	famas = 10,
	g3sg1 = 11,
	galil = 13,
	p250 = 36,
	tec9 = 30,
	m249 = 14,
	m4 = 16,
	mac10 = 17,
	p90 = 19,
	ump45 = 24,
	ppbizon = 26,
	negev = 28,
	mp7 = 33,
	mp9 = 34,
	scar30 = 38,
	sg553 = 39,
	ssg08 = 40,
	goldknife = 41,
	knife = 42,
	flashgren = 43,
	hegren = 44,
	smoke = 45,
	molotov = 46,
	incendiary = 48,
	decoygren = 47,
	bomb = 49,
	nova = 35,
	xm1014 = 25,
	sawedoff = 29,
	mag7 = 27,
	zeus = 31
};

enum eWeaponType1 {
	WEAPON_DEAGLE = 1,
	WEAPON_DUALBERETTA = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_ZEUSX27 = 31,
	WEAPON_USP = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

inline int GetWepType(int weaponID) {
	int WeaponType = WEPTYPE_NONE;
	if (weaponID == WEAPON_DEAGLE || weaponID == WEAPON_DUALBERETTA || weaponID == WEAPON_FIVESEVEN || weaponID == WEAPON_GLOCK || weaponID == WEAPON_TEC9 || weaponID == WEAPON_USP || weaponID == WEAPON_P250 || weaponID == WEAPON_USPS || weaponID == WEAPON_CZ75 || weaponID == WEAPON_REVOLVER)
		WeaponType = WEPTYPE_PISTOL;
	if (weaponID == WEAPON_KNIFE || weaponID == WEAPON_C4 || weaponID == WEAPON_KNIFE_T || weaponID == WEAPON_KNIFE_BAYONET || weaponID == WEAPON_KNIFE_FLIP || weaponID == WEAPON_KNIFE_GUT || weaponID == WEAPON_KNIFE_KARAMBIT || weaponID == WEAPON_KNIFE_M9_BAYONET || weaponID == WEAPON_KNIFE_TACTICAL || weaponID == WEAPON_KNIFE_FALCHION || weaponID == WEAPON_KNIFE_SURVIVAL_BOWIE || weaponID == WEAPON_KNIFE_BUTTERFLY || weaponID == WEAPON_KNIFE_PUSH)
		WeaponType = WEPTYPE_OTHER;
	if (weaponID == WEAPON_FLASHBANG || weaponID == WEAPON_HEGRENADE || weaponID == WEAPON_SMOKEGRENADE || weaponID == WEAPON_MOLOTOV || weaponID == WEAPON_DECOY || weaponID == WEAPON_INC)
		WeaponType = WEPTYPE_GRENADE;
	if (weaponID == WEAPON_AK47 || weaponID == WEAPON_AUG || weaponID == WEAPON_FAMAS || weaponID == WEAPON_GALIL || weaponID == WEAPON_M4A1 || weaponID == WEAPON_SG553 || weaponID == WEAPON_M4A1S)
		WeaponType = WEPTYPE_RIFLE;
	if (weaponID == WEAPON_AWP || weaponID == WEAPON_G3SG1 || weaponID == WEAPON_SCAR20 || weaponID == WEAPON_SSG08)
		WeaponType = WEPTYPE_SNIPER;
	if (weaponID == WEAPON_MAC10 || weaponID == WEAPON_P90 || weaponID == WEAPON_UMP45 || weaponID == WEAPON_BIZON || weaponID == WEAPON_MP7 || weaponID == WEAPON_MP9)
		WeaponType = WEPTYPE_SMG;
	if (weaponID == WEAPON_XM1014 || weaponID == WEAPON_MAG7 || weaponID == WEAPON_SAWEDOFF || weaponID == WEAPON_NOVA)
		WeaponType = WEPTYPE_SHOTGUN;
	if (weaponID == WEAPON_M249 || weaponID == WEAPON_NEGEV)
		WeaponType = WEPTYPE_MACHINEGUN;
	return WeaponType;
}

class IHandleEntity;
class CBaseHandle {
	friend class C_BaseEntityList;
public:
protected:
};

template< class T >
class CHandle : public CBaseHandle
{
public:
};

struct model_t {};
enum class CSGOHitboxID {
	Head = 0,
	Neck,
	NeckLower,
	Pelvis,
	Stomach,
	LowerChest,
	Chest,
	UpperChest,
	RightThigh,
	LeftThigh,
	RightShin,
	LeftShin,
	RightFoot,
	LeftFoot,
	RightHand,
	LeftHand,
	RightUpperArm,
	RightLowerArm,
	LeftUpperArm,
	LeftLowerArm,
};

//enum class CSGOHitboxID
//{
//	//YOUR USING BONES BUT THIS IS HITBOXES 
//	Head = 6,
//	Neck = 5,
//	NeckLower = 7,
//	Pelvis = 0,
//	Stomach = 68,
//	LowerChest = 3,
//	Chest = 80,
//	UpperChest =35,
//	RightThigh = 74,
//	LeftThigh = 52,
//	RightShin = 71,
//	LeftShin = 64,
//	RightFoot = 72,
//	LeftFoot = 70,
//	RightHand = 60,
//	LeftHand = 2,
//	RightUpperArm = 36,
//	RightLowerArm = 59,
//	LeftUpperArm = 8,
//	LeftLowerArm = 32,
//};

extern const char *Ranks[19];

class CCSBomb {
private:
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	float GetTimerLength() {
		static int m_flTimerLength = GET_NETVAR("DT_PlantedC4", "m_flTimerLength");
		return GetFieldValue<float>(m_flTimerLength);
	}
	float GetC4BlowTime() {
		static int m_flC4Blow = GET_NETVAR("DT_PlantedC4", "m_flC4Blow");
		return GetFieldValue<float>(m_flC4Blow);
	}
	float GetC4DefuseCountDown() {
		static int m_flDefuseCountDown = GET_NETVAR("DT_PlantedC4", "m_flDefuseCountDown");
		return GetFieldValue<float>(m_flDefuseCountDown);
	}
};

class CBaseEntity;

class CCSWeaponInfo {
public:
	float GetPen() {
		return *(float*)((DWORD)this + (DWORD)0x814);
	}
	int GetDamage() {
		return *(int*)((DWORD)this + (DWORD)0x818);
	}
	float GetRange() {
		return *(float*)((DWORD)this + (DWORD)0x81C);
	}
	float GetRangeModifier() {
		return *(float*)((DWORD)this + (DWORD)0x820);
	}
	float GetArmorRatio() {
		return *(float*)((DWORD)this + (DWORD)0x800);
	}
	float GetStandInacc() {
		return *(float*)((DWORD)this + (DWORD)0x9E0);
	}
	float GetJumpInacc() {
		return *(float*)((DWORD)this + (DWORD)0x9E8);
	}
};

class IHandleEntity {
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const HANDLE &handle) = 0;
	virtual const HANDLE& GetRefEHandle() const = 0;
};

class IClientUnknown : public IHandleEntity {
public:
	virtual void*              GetCollideable() = 0;
	virtual void*        GetClientNetworkable() = 0;
	virtual void*         GetClientRenderable() = 0;
	virtual void*            GetIClientEntity() = 0;
	virtual void*               GetBaseEntity() = 0;
	virtual void*          GetClientThinkable() = 0;
	virtual void*      GetClientAlphaProperty() = 0;
};

class IClientRenderable {
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual Vector const&              GetRenderOrigin(void) = 0;
	virtual Vector const&              GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       Unused(void) const {}
	virtual HANDLE				       GetShadowHandle() const = 0;
	virtual HANDLE&				       RenderHandle() = 0;
	virtual const model_t*             GetModel() const = 0;
	virtual int                        DrawModel(int flags, const int /*RenderableInstance_t*/ &instance) = 0;
	virtual int                        GetBody() = 0;
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4 *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void* /*IPVSNotify*/       GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector &mins, Vector &maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool                       GetShadowCastDistance(float *pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector *pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int /*ShadowType_t*/       ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual HANDLE				       GetModelInstance() = 0;
	virtual const matrix3x4&         RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char *pAttachmentName) = 0;
	virtual bool					   GetAttachment(int number, Vector &origin, Vector &angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4 &matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
};

class bf_read
{};

class IClientNetworkable {
public:
	virtual IClientUnknown*  GetIClientUnknown() = 0;
	virtual void             Release() = 0;
	virtual ClientClass*	 GetClientClass() = 0;
	virtual void             NotifyShouldTransmit(int state) = 0;
	virtual void             OnPreDataChanged(int updateType) = 0;
	virtual void             OnDataChanged(int updateType) = 0;
	virtual void             PreDataUpdate(int updateType) = 0;
	virtual void             PostDataUpdate(int updateType) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             IsDormant(void) = 0;
	virtual int              EntIndex(void) const = 0;
	virtual void             ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void*            GetDataTableBasePtr() = 0;
	virtual void             SetDestroyedOnRecreateEntities(void) = 0;
};

class CBaseCombatWeapon;

#define m_nIndex					0x64
#define m_nModelIndex				0x254
#define m_hWeapon					0x29B8
#define m_hOwner					0x29BC
#define m_lifeState					0x25B
#define m_hMyWeapons				0x2DE8
#define m_hViewModel				0x32FC
#define m_AttributeManager			0x2D70
#define m_Item						0x40
#define m_iItemDefinitionIndex		0x1D8
#define m_iItemIDHigh				0x1F0
#define m_iAccountID				0x1F8
#define m_iEntityQuality			0x1DC
#define m_szCustomName				0x26C
#define m_OriginalOwnerXuidLow		0x3168
#define m_OriginalOwnerXuidHigh		0x316C
#define m_nFallbackPaintKit			0x3170
#define m_nFallbackSeed				0x3174
#define m_flFallbackWear			0x3178
#define m_nFallbackStatTrak			0x317C

class CBaseViewModel : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	inline int GetModelIndex() {
		// DT_BaseViewModel -> m_nModelIndex
		return *(int*)((DWORD)this + m_nModelIndex);
	}
	inline DWORD GetOwner() {
		// DT_BaseViewModel -> m_hOwner
		return *(PDWORD)((DWORD)this + m_hOwner);
	}
	inline DWORD GetWeapon() {
		// DT_BaseViewModel -> m_hWeapon
		return *(PDWORD)((DWORD)this + m_hWeapon);
	}
	inline void SetWeaponModel(const char* Filename, IClientUnknown* Weapon) {
		return getvfunc<void(__thiscall*)(void*, const char*, IClientUnknown*)>(this, 242)(this, Filename, Weapon);
	}
};

class CBaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
	Vector GetAbsOrigin() {
		static int VecOrigin = GET_NETVAR("DT_BaseEntity", "m_vecOrigin");
		return this->GetFieldValue<Vector>(VecOrigin);
	}
	float pelvisangs() {
		static int ioffset = GET_NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget");
		return this->GetFieldValue<float>(ioffset);
	}
	Vector GetVecOrigin() {
		return *(Vector*)((DWORD)this + 0x134);
	}
	Vector GetVecViewOffset() {
		static int iOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
		return *(Vector*)((DWORD)this + iOffset);
	}
	int GetObserverMode() {
		static int iOffset = GET_NETVAR("DT_BasePlayer", "m_iObserverMode");
		return *(int*)((DWORD)this + iOffset);
	}
	Vector GetEyeAngles() {
		static int iOffset = GET_NETVAR("DT_CSPlayer", "m_angEyeAngles[0]");
		return *(Vector*)((DWORD)this + iOffset);
	}
	int GetMoney() {
		static int iOffset = GET_NETVAR("DT_CSPlayer", "m_iMatchStats_MoneySaved");
		return *(int*)((DWORD)this + iOffset);
	}
	Vector* GetEyeAnglesPointer() {
		static int iOffset = GET_NETVAR("DT_CSPlayer", "m_angEyeAngles[0]");
		return GetFieldPointer<Vector>(iOffset);
	}
	int* GetObserverModePointer() {
		static int iOffset = GET_NETVAR("DT_BasePlayer", "m_iObserverMode");
		return GetFieldPointer<int>(iOffset);
	}
	Vector GetAbsAngles() {
		__asm {
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX];
			CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}
	bool IsDormant() {
		__asm {
			MOV EDI, this
			LEA ECX, [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ecx]
				CALL[EDX + 0x24]
		}
	}
	int GetIndex() {
		int iEntIndex;
		PVOID pEnt = (PVOID)this;
		__asm {
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX + 0x8]
				MOV EDX, DWORD PTR DS : [EAX + 0x28]
				LEA ESI, DWORD PTR DS : [ECX + 0x8]
				MOV ECX, ESI
				CALL EDX
				MOV iEntIndex, EAX
		}
		return iEntIndex;
	}
	int GetTickBase(void) {
		static int m_nTickBase = GET_NETVAR("DT_BasePlayer", "localdata", "m_nTickBase");
		return GetFieldValue<int>(m_nTickBase);
	}
	bool IsPlayer() {
		if (!this)
			return false;

		if (this->IsDormant())
			return false;

		if (this->GetTeam() == 0)
			return false;

		ClientClass* cClass = (ClientClass*)this->GetClientClass();
		if (cClass->m_ClassID != 35)
			return false;
		return true;
	}
	bool isValidPlayer() {
		return (isAlive() && !IsDormant() && GetHealth() > 0);
	}
	int GetHealth() {
		return *reinterpret_cast<int*>((DWORD)this + 0xFC);
	}
	bool isAlive() {
		BYTE lifestate = *(BYTE*)((DWORD)this + 0x025B);
		return (lifestate == 0);
	}
	int GetFlags() {
		return *reinterpret_cast<int*>((DWORD)this + 0x0100);
	}
	int GetArmorValue() {
		static int armorValue = GET_NETVAR("DT_CSPlayer", "m_ArmorValue");
		return GetFieldValue<int>(armorValue);
	}
	int GetTeam() {
		return *reinterpret_cast<int*>((DWORD)this + 0xF0);
	}
	std::string GetClientClassName() {
		uintptr_t pNext = *(uintptr_t*)((DWORD)this + 0x8);
		pNext = *(uintptr_t*)((DWORD)pNext + 0x8);
		pNext = *(uintptr_t*)((DWORD)pNext + 0x1);
		return std::string(*(char**)((DWORD)pNext + 0x8));
	}
	Vector *GetViewPunchAnglePtr() {
		static int m_aimPunchAngle = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
		return GetFieldPointer<Vector>(m_aimPunchAngle);
	}
	Vector* GetPunchAnglePtr() {
		static int m_aimPunchAngle = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		return GetFieldPointer<Vector>(m_aimPunchAngle);
	}
	Vector GetVecVelocity() {
		return *(Vector*)((DWORD)this + 0x110);
	}
	Vector GetPunchAngle() {
		static int m_aimPunchAngle = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		return *GetFieldPointer<Vector>(m_aimPunchAngle);
	}
	int SetFov(int fovvalue) {
		static int iOffset = GET_NETVAR("DT_BasePlayer", "m_iDefaultFOV");
		*(int*)((DWORD)this + iOffset) = fovvalue;
		static int iOffset2 = GET_NETVAR("DT_CSPlayer", "m_bIsScoped");
		bool scopecheck = *(bool*)((DWORD)this + iOffset2);
		if (!scopecheck) {
			static int iOffset3 = GET_NETVAR("DT_BasePlayer", "m_iFOV");
			*(int*)((DWORD)this + iOffset3) = fovvalue;
		}
		return true;
	}
	bool getscoreboard() {
		static int m_bCameraManScoreBoard = GET_NETVAR("DT_BasePlayer", "m_bCameraManScoreBoard");
		return GetFieldValue<bool>(m_bCameraManScoreBoard);
	}
	bool GetScope() {
		static int iOffset2 = GET_NETVAR("DT_CSPlayer", "m_bIsScoped");
		bool scopecheck = *(bool*)((DWORD)this + iOffset2);
		if (scopecheck)
			return true;
		return false;
	}
	int GetiShots() {
		static int iOffset = GET_NETVAR("DT_CSPlayer", "m_iShotsFired");
		return *(int*)((DWORD)this + iOffset);
	}
	CColor GetHealthColor() {
		int nHealth = GetHealth();
		float r = 255.f - float(nHealth) * 2.55f;
		float g = float(nHealth) * 2.55f;
		return CColor(int(r), int(g), 0, 200);
	}
	CBaseCombatWeapon* GetActiveBaseCombatWeapon();
	bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
		static DWORD m_nWritableBones = GET_NETVAR("DT_CSPlayer", "m_nForceBone") + 0x20;
		static DWORD m_dwOcclusionArray = *(uintptr_t*)(Utils.PFindPattern("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0x1);
		static DWORD m_bDidCheckForOcclusion = *(uintptr_t*)(Utils.PFindPattern("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0xE);

		*(int*)((uintptr_t)this + m_nWritableBones) = 0;
		*(int*)((uintptr_t)this + m_bDidCheckForOcclusion) = reinterpret_cast<int*>(m_dwOcclusionArray)[1];

		typedef bool(__thiscall* oSetupBones)(PVOID, matrix3x4*, int, int, float);
		return getvfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	Vector GetBonePos(int i) {
		matrix3x4 boneMatrix[128];
		if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, (float)GetTickCount64()))
			return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
		return Vector(0, 0, 0);
	}
	Vector GetEyePosition() {
		return GetAbsOrigin() + GetVecViewOffset();
	}
	int GetArmor() {
		static int Armor = GET_NETVAR("DT_CSPlayerResource", "m_iArmor");
		return GetFieldValue<int>(Armor);
	}
	bool HasHelmet() {
		static int Helm = GET_NETVAR("DT_CSPlayerResource", "m_bHasHelmet");
		return GetFieldValue<bool>(Helm);
	}
	bool HasGunGameImmunity() {
		static int m_bGunGameImmun = GET_NETVAR("DT_CSPlayer", "m_bGunGameImmunity");
		return *GetFieldPointer<bool>(m_bGunGameImmun);
	}
	float LowerBodyYaw() {
		static int ioffset = GET_NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget");
		return GetFieldValue<float>(ioffset);
	}
	Vector Rotationang() {
		static int m_angRotation = GET_NETVAR("DT_BaseEntity", "m_angRotation");
		return GetFieldValue<Vector>(m_angRotation);
	}
	float m_flUseLookAtAngle() {
		static int m_flUseLookAtAngle = GET_NETVAR("DT_BaseEntity", "m_flUseLookAtAngle");
		return GetFieldValue<float>(m_flUseLookAtAngle);
	}
	char* LastPlaceName() {
		static int m_szLastPlaceName = GET_NETVAR("DT_BasePlayer", "m_szLastPlaceName");
		return GetFieldPointer<char>(m_szLastPlaceName);
	}
	Vector BBMin() {
		static int m_vecMins = GET_NETVAR("DT_BaseEntity", "m_Collision", "m_vecMins");
		return GetFieldValue<Vector>(m_vecMins);
	}
	Vector BBMax() {
		static int m_vecMaxs = GET_NETVAR("DT_BaseEntity", "m_Collision", "m_vecMaxs");
		return GetFieldValue<Vector>(m_vecMaxs);
	}
	bool m_bIsScoped() {
		static int m_bIsScoped = GET_NETVAR("DT_CSPlayer", "m_bIsScoped");
		return GetFieldValue<bool>(m_bIsScoped);
	}
	int GetMoveType() {
		return GetFieldValue<int>(0x258);
	}
	const char* CompRank() {
		static int m_iCompetitiveRanking = GET_NETVAR("DT_CSPlayerResource", "m_iCompetitiveRanking");
		int Rank = GetFieldValue<int>(m_iCompetitiveRanking);
		return Ranks[Rank];
	}
	int ICompRank() {
		static int m_iCompetitiveRanking = GET_NETVAR("DT_CSPlayerResource", "m_iCompetitiveRanking");
		int Rank = GetFieldValue<int>(m_iCompetitiveRanking);
		return Rank;
	}
	int CompWins() {
		static int m_iCompetitiveRanking = GET_NETVAR("DT_CSPlayerResource", "m_iCompetitiveWins");
		int Rank = GetFieldValue<int>(m_iCompetitiveRanking);
		return Rank;
	}
	Vector WorldSpaceCenter() {
		Vector Max = this->BBMax() + this->GetAbsOrigin();
		Vector Min = this->BBMin() + this->GetAbsOrigin();
		Vector Size = Max - Min;
		Size /= 2;
		Size += Min;
		return Size;
	}
};

class CBaseAttributableItem : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	inline int* GetItemDefinitionIndex() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		return (int*)((DWORD)this + m_AttributeManager + m_Item + m_iItemDefinitionIndex);
	}
	inline int* GetItemIDHigh() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		return (int*)((DWORD)this + m_AttributeManager + m_Item + m_iItemIDHigh);
	}
	inline int* GetAccountID() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		return (int*)((DWORD)this + m_AttributeManager + m_Item + m_iAccountID);
	}
	inline int* GetEntityQuality() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)((DWORD)this + m_AttributeManager + m_Item + m_iEntityQuality);
	}
	inline char* GetCustomName() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_szCustomName
		return (char*)((DWORD)this + m_AttributeManager + m_Item + m_szCustomName);
	}
	inline int* GetOriginalOwnerXuidLow() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		return (int*)((DWORD)this + m_OriginalOwnerXuidLow);
	}
	inline int* GetOriginalOwnerXuidHigh() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		return (int*)((DWORD)this + m_OriginalOwnerXuidHigh);
	}
	inline int* GetFallbackPaintKit() {
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		return (int*)((DWORD)this + m_nFallbackPaintKit);
	}
	inline int* GetFallbackSeed() {
		// DT_BaseAttributableItem -> m_nFallbackSeed
		return (int*)((DWORD)this + m_nFallbackSeed);
	}
	inline float* GetFallbackWear() {
		// DT_BaseAttributableItem -> m_flFallbackWear
		return (float*)((DWORD)this + m_flFallbackWear);
	}
	inline int* GetFallbackStatTrak() {
		// DT_BaseAttributableItem -> m_nFallbackStatTrak
		return (int*)((DWORD)this + m_nFallbackStatTrak);
	}
};

class CBaseCombatWeapon : public CBaseEntity {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	CBaseEntity* GetOwner() {
		//static int m_hOwnerEntity = GET_NETVAR(("DT_BaseEntity"), ("m_hOwnerEntity"));
		//return (CBaseEntity*)Interfaces.pEntList->GetClientEntityFromHandle(GetFieldValue<CHandle<CBaseEntity>>(m_hOwnerEntity));
		return NULL;
	}
	float NextPrimaryAttack() {
		static int m_flNextPrimaryAttack = GET_NETVAR(("DT_BaseCombatWeapon"), ("LocalActiveWeaponData"), ("m_flNextPrimaryAttack"));
		return GetFieldValue<float>(m_flNextPrimaryAttack);
	}
	int GetId() {
		typedef int(__thiscall* tGetId)(void*);
		return getvfunc<tGetId>(this, 458)(this);
	}
	const char* GetName() {
		if (this == NULL) 
			return "Null";
		typedef const char* (__thiscall* tGetName)(void*);
		if (this == NULL) 
			return "Null";
		return getvfunc<tGetName>(this, 378)(this);
	}
	char* GetPName() {
		if (this == NULL) 
			return "Null";
		typedef char* (__thiscall* tGetName)(void*);
		if (this == NULL) 
			return "Null";
		return getvfunc<tGetName>(this, 378)(this);
	}
	char* CBaseCombatWeapon::GetWeaponName() {
		if (!this)
			return "";

		int id = this->GetId();
		switch (id) {
		case WEAPON_DEAGLE:
			return ("Deagle");
		case WEAPON_DUALBERETTA:
			return ("Dual Berettas");
		case WEAPON_FIVESEVEN:
			return ("Five-SeveN");
		case WEAPON_GLOCK:
			return ("Glock-18");
		case WEAPON_AK47:
			return ("AK-47");
		case WEAPON_AUG:
			return ("AUG");
		case WEAPON_AWP:
			return ("AWP");
		case WEAPON_FAMAS:
			return ("FAMAS");
		case WEAPON_G3SG1:
			return ("G3SG1");
		case WEAPON_GALIL:
			return ("Galil");
		case WEAPON_M249:
			return ("M249");
		case WEAPON_M4A1:
			return ("M4A1");
		case WEAPON_MAC10:
			return ("MAC-10");
		case WEAPON_P90:
			return ("P90");
		case WEAPON_UMP45:
			return ("UMP-45");
		case WEAPON_XM1014:
			return ("XM1014");
		case WEAPON_BIZON:
			return ("PP-Bizon");
		case WEAPON_MAG7:
			return ("MAG-7");
		case WEAPON_NEGEV:
			return ("Negev");
		case WEAPON_SAWEDOFF:
			return ("Sawed-Off");
		case WEAPON_TEC9:
			return ("Tec-9");
		case WEAPON_ZEUSX27:
			return ("Taser");
		case p2000:
			return ("P2000");
		case WEAPON_MP7:
			return ("MP7");
		case WEAPON_MP9:
			return ("MP9");
		case WEAPON_NOVA:
			return ("Nova");
		case WEAPON_P250:
			return ("P250");
		case WEAPON_SCAR20:
			return ("SCAR-20");
		case WEAPON_SG553:
			return ("SG 553");
		case WEAPON_SSG08:
			return ("SSG 08");
		case WEAPON_KNIFE:
			return ("Knife");
		case WEAPON_FLASHBANG:
			return ("Flashbang");
		case WEAPON_HEGRENADE:
			return ("HE Grenade");
		case WEAPON_SMOKEGRENADE:
			return ("Smoke Grenade");
		case WEAPON_MOLOTOV:
			return ("Molly");
		case WEAPON_DECOY:
			return ("Decoy");
		case WEAPON_INC:
			return ("Incendiary Grenade");
		case WEAPON_C4:
			return ("C4");
		case WEAPON_M4A1S:
			return ("M4A1-S");
		case WEAPON_USPS:
			return ("USP-S");
		case WEAPON_CZ75:
			return ("CZ75-Auto");
		default:
			return ("Knife");
		}
		return "";
	}
	int GetItemDefinitionIndex() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		static int m_iItemDefinitionIndex1 = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
		return *(int*)((DWORD)this + m_iItemDefinitionIndex1);
	}
	int* GetItemIDHigh() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		static int m_iItemIDHigh1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iItemIDHigh"));
		return GetFieldPointer<int>(m_iItemIDHigh1);
	}
	int* GetAccountID() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		static int m_iAccountID1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iAccountID"));
		return GetFieldPointer<int>(m_iAccountID1);
	}
	int* GetEntityQuality() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		static int m_iEntityQuality1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_iEntityQuality"));
		return GetFieldPointer<int>(m_iEntityQuality1);

	}
	char* GetCustomName() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_szCustomName
		static int m_szCustomName1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_AttributeManager"), ("m_Item"), ("m_szCustomName"));
		return GetFieldPointer<char>(m_szCustomName1);
	}
	int* GetOriginalOwnerXuidLow() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		static int m_OriginalOwnerXuidLow1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_OriginalOwnerXuidLow"));
		return GetFieldPointer<int>(m_OriginalOwnerXuidLow1);

	}
	int* GetOriginalOwnerXuidHigh() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		static int m_OriginalOwnerXuidHigh1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_OriginalOwnerXuidHigh"));
		return GetFieldPointer<int>(m_OriginalOwnerXuidHigh1);

	}
	int* GetFallbackPaintKit() {
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		static int m_nFallbackPaintKit1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_nFallbackPaintKit"));
		return GetFieldPointer<int>(m_nFallbackPaintKit1);

	}
	int* GetFallbackSeed() {
		// DT_BaseAttributableItem -> m_nFallbackSeed
		static int m_nFallbackSeed1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_nFallbackSeed"));
		return GetFieldPointer<int>(m_nFallbackSeed1);

	}
	float* GetFallbackWear() {
		// DT_BaseAttributableItem -> m_flFallbackWear
		static int m_flFallbackWear1 = GET_NETVAR("DT_BaseAttributableItem", "m_flFallbackWear");
		return GetFieldPointer<float>(m_flFallbackWear1);

	}
	int* GetFallbackStatTrak() {
		// DT_BaseAttributableItem -> m_nFallbackStatTrak
		static int m_nFallbackStatTrak1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_nFallbackStatTrak"));
		return GetFieldPointer<int>(m_nFallbackStatTrak1);

	}
	void CBaseCombatWeapon::UpdateAccuracyPenalty() {
		typedef void(__thiscall* OriginalFn)(void*);
		getvfunc<OriginalFn>(this, 486)(this);
	}
	float& CBaseCombatWeapon::GetAccuracyPenalty() {
		static int m_fAccuracyPenalty = GET_NETVAR(("DT_WeaponCSBase"), ("m_fAccuracyPenalty"));

		return *(float*)((DWORD)this + m_fAccuracyPenalty);
	}
	float CBaseCombatWeapon::GetInaccuracy() {
		if (!this)
			return 0.f;
		typedef float(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 484)(this);
	}
	float CBaseCombatWeapon::GetSpread() {
		if (!this)
			return 0.f;
		typedef float(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 479)(this);
	}
	float CBaseCombatWeapon::GetWeaponCone() {
		if (!this)
			return 0.f;
		typedef float(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 478)(this);
	}
	int ammo() {
		static int m_Clip = GET_NETVAR("DT_BaseCombatWeapon", "m_iClip1");
		return *GetFieldPointer<int>(m_Clip);
	}
	bool HasAmmo() {
		if (ammo() > 0)
			return true;
		else
			return false;
	}
	bool isPistoleW() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_PISTOL) {
			return true;
		}
		return false;
	}
	bool isShotgunW() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_SHOTGUN) {
			return true;
		}
		return false;
	}
	bool isSniper() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_SNIPER) {
			return true;
		}
		return false;
	}
	bool isAWP() {
		return this->GetItemDefinitionIndex() == WEAPON_AWP;
	}
	bool isScout() {
		return this->GetItemDefinitionIndex() == WEAPON_SSG08;
	}
	bool isDak() {
		return this->GetItemDefinitionIndex() == WEAPON_SCAR20 || this->GetItemDefinitionIndex() == WEAPON_G3SG1;
	}
	bool isRifle() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_RIFLE) {
			return true;
		}
		return false;
	}
	bool isSmgW() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_SMG) {
			return true;
		}
		return false;
	}
	bool isMashineW() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_MACHINEGUN) {
			return true;
		}
		return false;
	}
	bool IsPistol() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_PISTOL) {
			return true;
		}
		return false;
	}

	bool IsMiscWeapon()
	{
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_OTHER) {
			return true;
		}
		return false;
	}
	bool IsNade()
	{
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_GRENADE) {
			return true;
		}
		return false;
	}
	bool IsNotWeapon()
	{
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_OTHER || GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_NONE) {
			return true;
		}
		return false;
	}
	bool IsZeus() {
		return this->GetItemDefinitionIndex() == WEAPON_ZEUSX27;
	}

	bool IsKnife() {
		if (GetWepType(this->GetItemDefinitionIndex()) == WEPTYPE_OTHER) {
			return true;
		}
		return false;
	}
	bool IsReloading() {
		false;
	}
	CCSWeaponInfo* GetCSWpnData() {
		static DWORD GetCSWpnDataAddr = Utils.PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x57", "xxxxx????x????x", NULL, NULL);
		if (GetCSWpnDataAddr) {
			CCSWeaponInfo* retData;
			__asm {
				mov ecx, this
				call GetCSWpnDataAddr
					mov retData, eax
			}
			return retData;
		} else {
			return nullptr;
		}
	}
};


