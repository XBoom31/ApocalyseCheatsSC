/*
Rest In Peace ApocalypseCheats
*/

#include "UTIL Functions.h"
#include "Utilities.h"
#include "Menu.h"
#include "Hacks.h"
#include "Autowall.h"

#include "RenderManager.h"

ServerRankRevealAllFn GameUtils::ServerRankRevealAllEx;
IsReadyFn GameUtils::IsReady;

DWORD GameUtils::FindPattern1(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}

void UTIL_TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask,const IClientEntity *ignore, int collisionGroup, trace_t *ptr)
{
	typedef int(__fastcall* UTIL_TraceLine_t)(const Vector&, const Vector&, unsigned int, const IClientEntity*, int, trace_t*);
	static UTIL_TraceLine_t TraceLine = (UTIL_TraceLine_t)Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x7C\x56\x52", "xxxxxxxxxxx");
	TraceLine(vecAbsStart, vecAbsEnd, mask, ignore, collisionGroup, ptr);
}


void UTIL_ClipTraceToPlayers(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
{
	static DWORD dwAddress = Utilities::Memory::FindPattern("client.dll", (BYTE*)"\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x81\xEC\x00\x00\x00\x00\x8B\x43\x10", "xxxxxxxxxxxxxxxxxxxxxxxx????xxx");

	if (!dwAddress)
		return;

	_asm
	{
		MOV		EAX, filter
		LEA		ECX, tr
			PUSH	ECX
			PUSH	EAX
			PUSH	mask
			LEA		EDX, vecAbsEnd
			LEA		ECX, vecAbsStart
			CALL	dwAddress
			ADD		ESP, 0xC
	}
}

bool IsBreakableEntity(IClientEntity* ent)
{
	typedef bool(__thiscall* IsBreakbaleEntity_t)(IClientEntity*);
	IsBreakbaleEntity_t IsBreakbaleEntityFn = (IsBreakbaleEntity_t)Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x51\x56\x8B\xF1\x85\xF6\x74\x68", "xxxxxxxxxxx");
	if (IsBreakbaleEntityFn)
		return IsBreakbaleEntityFn(ent);
	else
		return false;
}

bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace)
{
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static TraceToExitFn TraceToExit = (TraceToExitFn)Utilities::Memory::FindPattern("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xEC\x2C\xF3\x0F\x10\x75\x00\x33\xC0", "xxxxxxxxxx?xx");

	if (!TraceToExit)
		return false;

	return TraceToExit(end, tr, start.x, start.y, start.z, vEnd.x, vEnd.y, vEnd.z, trace);
}

/*unsigned short GameUtils::UTIL_GetAchievementEventMask()
{
	static uintptr_t GetAchievementEventMask_func = Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????xx????x????");
	typedef unsigned short(__fastcall* UTIL_GetAchievementEventMask_t)();
	static UTIL_GetAchievementEventMask_t pUTIL_GetAchievementEventMask =
		reinterpret_cast<UTIL_GetAchievementEventMask_t>(GetAchievementEventMask_func);
	return pUTIL_GetAchievementEventMask();
}*/

void GameUtils::NormaliseViewAngle(Vector &angle)
{
	if (!Menu::Window.MiscTab.OtherSafeMode.GetState())
	{
		return;
	}
	else
	{
		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;


		if (angle.x > 89) angle.x = 89;
		if (angle.x < -89) angle.x = -89;
		if (angle.y < -180) angle.y = -179.999;
		if (angle.y > 180) angle.y = 179.999;

		angle.z = 0;
	}
}

void GameUtils::CL_FixMove(CUserCmd* pCmd, Vector viewangles)
{
	/*pCmd->forwardmove = DotProduct(forward * vForwardNorm, aimforward) + DotProduct(right * vRightNorm, aimforward) + DotProduct(up * vUpNorm, aimforward);
	pCmd->sidemove = DotProduct(forward * vForwardNorm, aimright) + DotProduct(right * vRightNorm, aimright) + DotProduct(up * vUpNorm, aimright);
	pCmd->upmove = DotProduct(forward * vForwardNorm, aimup) + DotProduct(right * vRightNorm, aimup) + DotProduct(up * vUpNorm, aimup);*/
}

char shit[16];
trace_t Trace;
char shit2[16];
IClientEntity* entCopy;

bool GameUtils::IsVisible(IClientEntity* pLocal, IClientEntity* pEntity, int BoneID)
{
	if (BoneID < 0) return false;

	entCopy = pEntity;
	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = GetHitboxPosition(pEntity, BoneID);//pEntity->GetBonePos(BoneID);
	char shit3[32];
	
	//Interfaces::Trace->TraceRay(Ray,MASK_SOLID, NULL/*&filter*/, &Trace);
	UTIL_TraceLine(start, end, MASK_SOLID, pLocal, 0, &Trace);

	if (Trace.m_pEnt == entCopy)
	{
		return true;
	}

	if (Trace.fraction == 1.0f)
	{
		return true;
	}

	return false;

}

bool GameUtils::IsBallisticWeapon(void* weapon)
{
	if (weapon == nullptr) return false;
	CBaseCombatWeapon *pWeapon = (CBaseCombatWeapon*)weapon;
	int id = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
	return !(id >= WEAPON_KNIFE_CT && id <= WEAPON_KNIFE_T || id == 0 || id >= WEAPON_KNIFE_BAYONET);
}
bool GameUtils::IsAK(void* weapon)
{
	if (weapon == nullptr) return false;
	CBaseCombatWeapon *pWeapon = (CBaseCombatWeapon*)weapon;
	int id = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
	static const std::vector<int> v = {WEAPON_AK47};
	return (std::find(v.begin(), v.end(), id) != v.end());
}
bool GameUtils::IsPistol(void* weapon)
{
	if (weapon == nullptr) return false;
	CBaseCombatWeapon *pWeapon = (CBaseCombatWeapon*)weapon;
	int id = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
	static const std::vector<int> v = { WEAPON_DEAGLE,WEAPON_CZ75A,WEAPON_ELITE,WEAPON_USP_SILENCER,WEAPON_P250,WEAPON_HKP2000, WEAPON_TEC9,WEAPON_REVOLVER,WEAPON_FIVESEVEN,WEAPON_GLOCK };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool GameUtils::IsSniper(void* weapon)
{
	if (weapon == nullptr) return false;
	CBaseCombatWeapon *pWeapon = (CBaseCombatWeapon*)weapon;
	int id = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
	static const std::vector<int> v = { WEAPON_AWP,WEAPON_SSG08,WEAPON_G3SG1,WEAPON_SCAR20 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

bool GameUtils::IsScopedWeapon(void* weapon)
{
	if (weapon == nullptr) return false;
	CBaseCombatWeapon *pWeapon = (CBaseCombatWeapon*)weapon;
	int id = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
	static const std::vector<int> v = { WEAPON_AWP,WEAPON_SSG08,WEAPON_G3SG1,WEAPON_SCAR20, WEAPON_AUG, WEAPON_SG556 };
	return (std::find(v.begin(), v.end(), id) != v.end());
}

void SayInChat(const char *text)
{
	char buffer[250];
	sprintf_s(buffer, "say \"%s\"", text);
	Interfaces::Engine->ClientCmd_Unrestricted(buffer);
}

void SayInTeamChat(const char *text)
{
	char buffer[250];
	sprintf_s(buffer, "say_team \"%s\"", text);
	Interfaces::Engine->ClientCmd_Unrestricted(buffer);
}

Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
{
	matrix3x4 matrix[128];

	if (pEntity->SetupBones(matrix, 128, 0x100, 0.f))
	{
		studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (hitbox)
		{
			Vector vMin, vMax, vCenter, sCenter;
			VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
			VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);

			vCenter = ((vMin + vMax) *0.5f);

			return vCenter;
		}
	}

	return Vector(0, 0, 0);
}


/*bool GetBestPoint(IClientEntity* pEntity, Hitbox* hitbox, BestPoint *point)
{
	Vector center = hitbox->points[0];
	std::vector<int> HitBoxesToScan;

	if (hitbox->hitbox == ((int)CSGOHitboxID::Head))
	{
		Vector high = ((hitbox->points[3] + hitbox->points[5]) * .5f);

		float pitch = pEntity->GetEyeAngles().x;
		if ((pitch > 0.f) && (pitch <= 89.f))
		{
			Vector height = (((high - hitbox->points[0]) / 3) * 4);
			Vector new_height = (hitbox->points[0] + (height * (pitch / 89.f)));

			hitbox->points[0] = new_height;
			point->flags |= FL_HIGH;
		}
		else if ((pitch < 292.5f) && (pitch >= 271.f))
		{
			hitbox->points[0] -= Vector(0.f, 0.f, 1.f);
		point->flags |= FL_LOW;
		}
	}

	for (int index = 0; index <= 8; ++index)
	{
		int temp_damage = GetDamage(hitbox->points[index]);

		if ((point->dmg < temp_damage))
		{
			point->dmg = temp_damage;
			point->point = hitbox->points[index];
			point->index = index;
		}
	}

	return (point->dmg > Menu::Window.RageBotTab.AccuracyMinimumDamage.GetValue());
}*/

/*Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
{
	matrix3x4 matrix[128];

	if (pEntity->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
	{
		studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (hitbox)
		{	
			Vector points[9] =
			{
				((hitbox->bbmin + hitbox->bbmax) * .5f),
				Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmin.z),
				Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmin.z),
				Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmin.z),
				Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmin.z),
				Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmax.z),
				Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmax.z),
				Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmax.z),
				Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmax.z)
			};

			Vector vPoint = ((hitbox->bbmin + hitbox->bbmax) * .5f);

			for (int index = 0; index <= 8; ++index)
			{
				if (index != 0)
				{
					// scale down the hitbox size
					points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);
				}

				// transform the vector
				VectorTransform(points[index], matrix[hitbox->bone], vPoint[index]);
			}

			return vPoint;
		}
	}

	return Vector(0, 0, 0);
}*/

/*Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
{
	matrix3x4 matrix[128];

	if (pEntity->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
	{
		studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (hitbox)
		{
			Vector vMin, vMax, vCenter, sCenter;
			VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
			VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
			vCenter = (vMin + vMax) *0.5f;
			return vCenter;
		}
	}

	return Vector(0, 0, 0);
}*/

/*Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
{
	matrix3x4 matrix[128];

	if (!pEntity->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
		return Vector(0,0,0);

	studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

	if (!hitbox)
		return Vector(0,0,0);

	Vector vMin, vMax, vCenter, sCenter;
	VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
	VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
	vCenter = (vMin + vMax) *0.5f;
	return vCenter;
}*/

/*bool CRageBot::GetHitbox(CBaseEntity* target, Hitbox* hitbox)
{
	matrix3x4a_t matrix[MAXSTUDIOBONES];

	if (!target->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
		return false;


	studiohdr_t *hdr = I::ModelInfo->GetStudioModel(target->GetModel());

	if (!hdr)
		return false;

	mstudiohitboxset_t *hitboxSet = hdr->pHitboxSet(target->GetHitboxSet());
	mstudiobbox_t *untransformedBox = hitboxSet->pHitbox(hitbox->hitbox);

	Vector bbmin = untransformedBox->bbmin;
	Vector bbmax = untransformedBox->bbmax;

	if (untransformedBox->radius != -1.f)
	{
		bbmin -= Vector(untransformedBox->radius, untransformedBox->radius, untransformedBox->radius);
		bbmax += Vector(untransformedBox->radius, untransformedBox->radius, untransformedBox->radius);
	}

	Vector points[] =
	{ ((bbmin + bbmax) * .5f),
		Vector(bbmin.x, bbmin.y, bbmin.z),
		Vector(bbmin.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmin.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmin.y, bbmax.z),
		Vector(bbmax.x, bbmin.y, bbmax.z)
	};


	for (int index = 0; index <= 8; ++index)
	{
		if (index != 0)
			points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);

		M::VectorTransform(points[index], matrix[untransformedBox->bone], hitbox->points[index]);
	}

	return true;
}*/

/*Vector GetHitscan(IClientEntity* pEntity, int Hitbox)
{
	matrix3x4 matrix[128];

	if (!pEntity->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
		return Vector(0, 0, 0);

	studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

	for (int i = 0; i < 18; i++)
	{
		mstudiobbox_t* hitbox = set->GetHitbox(i);
		if (!hitbox)
			continue;

		Vector vAimPoint;

		Vector corners[17] =
		{
			Vector((hitbox->bbmin + hitbox->bbmax) * 0.5),
			Vector(hitbox->bbmax.x - 1.65, hitbox->bbmax.y - 1.65, hitbox->bbmin.z + 1.65),
			Vector(hitbox->bbmax.x - 1.65, hitbox->bbmax.y - 1.65, hitbox->bbmax.z - 1.65),
			Vector(hitbox->bbmin.x + 1.65, hitbox->bbmax.y - 1.65, hitbox->bbmin.z + 1.65),
			Vector(hitbox->bbmin.x + 1.65, hitbox->bbmax.y - 1.65, hitbox->bbmax.z - 1.65),
			Vector(hitbox->bbmax.x - 1.65, hitbox->bbmin.y + 1.65, hitbox->bbmin.z + 1.65),
			Vector(hitbox->bbmax.x - 1.65, hitbox->bbmin.y + 1.65, hitbox->bbmax.z - 1.65),
			Vector(hitbox->bbmin.x + 1.65, hitbox->bbmin.y + 1.65, hitbox->bbmin.z + 1.65),
			Vector(hitbox->bbmin.x + 1.65, hitbox->bbmin.y + 1.65, hitbox->bbmax.z - 1.65),
			Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmin.z),
			Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmax.z),
			Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmin.z),
			Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmax.z),
			Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmin.z),
			Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmax.z),
			Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmin.z),
			Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmax.z)
		};

		for (int j = 0; j < 17; j++)
		{
			if (!corners[j])
				continue;

			VectorTransform(corners[j], matrix[hitbox->bone], vAimPoint);
		}

		return vAimPoint;
	}
}*/

Vector GetEyePosition(IClientEntity* pEntity)
{
	Vector vecViewOffset = *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity) + 0x104);

	return pEntity->GetOrigin() + vecViewOffset;
}

int GameUtils::GetPlayerCompRank(IClientEntity* pEntity) // 0x75671f7f is crc32 for comp rank netvar, 0x2ED6198 is CCSPlayerResource, 0x1A44 is netvar offset
{
	DWORD m_iCompetitiveRanking = NetVar.GetNetVar(0x75671F7F); //NetVar.GetNetVar(0x75671F7F);
	DWORD GameResources = *(DWORD*)(Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x85\xFF\x0F\x84\x00\x00\x00\x00\x81\xC7", "xx????xxxx????xx") + 0x2);
	
	return *(int*)((DWORD)GameResources + 0x1A44 + (int)pEntity->GetIndex() * 4);
}

extern void GameUtils::ServerRankRevealAll()
{
	static float fArray[3] = { 0.f, 0.f, 0.f };

	GameUtils::ServerRankRevealAllEx = (ServerRankRevealAllFn)(Offsets::Functions::dwGetPlayerCompRank);
	//GameUtils::ServerRankRevealAllEx = (ServerRankRevealAllFn)(offsets.ServerRankRevealAllEx);
	GameUtils::ServerRankRevealAllEx(fArray);
}

void ForceUpdate()
{
	// Shh
	static DWORD clientstateaddr = Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x8A\xF9\xF3\x0F\x11\x45\xF8\x83\xBF\xE8\x00\x00\x00\x02", "xx????xxxxxxxxxxxxxx");
	static uintptr_t pEngineBase = (uintptr_t)GetModuleHandleA("engine.dll");

	static uintptr_t pClientState = **(uintptr_t**)(Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x8A\xF9", "xx????xx") + 2);

	static uintptr_t dwAddr1 = Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00", "x????x????x????xx????????");

	//E8 call is being used here
	static uintptr_t dwRelAddr = *(uintptr_t*)(dwAddr1 + 1);
	static uintptr_t sub_B5E60 = ((dwAddr1 + 5) + dwRelAddr);

	__asm
	{
		pushad
		mov edi, pClientState
		lea ecx, dword ptr[edi + 0x8]
		call sub_B5E60
		mov dword ptr[edi + 0x154], 0xFFFFFFFF
		popad
	}
}

/*NET_SetConVar::NET_SetConVar(const char* name, const char* value)
{
	typedef void(__thiscall* SetConVarConstructor_t)(void*);
	static SetConVarConstructor_t pNET_SetConVar = (SetConVarConstructor_t)(Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x83\xE9\x04\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x56\x8B\xF1\xC7\x06\x00\x00\x00\x00\x8D\x4E\x08", "xxxx????xxxxxxxxxxxxxxxx????xxx") + 19);
	pNET_SetConVar(this);

	typedef void(__thiscall* SetConVarInit_t)(void*, const char*, const char*);
	static SetConVarInit_t pNET_SetConVarInit = (SetConVarInit_t)Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x55\x8B\xEC\x56\x8B\xF1\x57\x83\x4E\x14\x01\x83\x7E\x0C\x00", "xxxxxxxxxxxxxxx");
	pNET_SetConVarInit(this, name, value);
}

NET_SetConVar::~NET_SetConVar()
{
	typedef void(__thiscall* SetConVarConstructor_t)(void*);
	static SetConVarConstructor_t pNET_SetConVar = (SetConVarConstructor_t)(Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x56\x8B\xF1\x57\x8D\x7E\x04\xC7\x07\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx????") + 12);
	pNET_SetConVar(this);
}*/