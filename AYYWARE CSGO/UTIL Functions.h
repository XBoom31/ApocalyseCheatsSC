/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "SDK.h"
#include <Psapi.h>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

using IsReadyFn = void(__cdecl*)();
using ServerRankRevealAllFn = bool(__cdecl*)(float*);

struct Hitbox
{
	Hitbox(void)
	{
		hitbox = -1;
	}

	Hitbox(int newHitBox)
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	Vector points[9];
};

enum
{
	FL_HIGH = (1 << 0),
	FL_LOW = (1 << 1),
	FL_SPECIAL = (1 << 2)
};

struct BestPoint
{
	BestPoint(void)
	{
		hitbox = -1;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	BestPoint(int newHitBox)
	{
		hitbox = newHitBox;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	Vector point;
	int  index;
	int  dmg;
	int  flags;
	int  hitbox;
};


namespace GameUtils
{
	extern DWORD FindPattern1(std::string moduleName, std::string pattern);
	extern ServerRankRevealAllFn ServerRankRevealAllEx;
	extern IsReadyFn IsReady;
	void NormaliseViewAngle(Vector &angle);
	void CL_FixMove(CUserCmd* cmd, Vector viewangles);
	bool IsVisible(IClientEntity* pLocal, IClientEntity* pEntity, int BoneID);
	bool IsBallisticWeapon(void* weapon);
	bool IsAK(void* weapon);
	bool IsUSP(void* weapon);
	bool IsPistol(void* weapon);
	bool IsSniper(void* weapon);
	bool IsScopedWeapon(void* weapon);
	int GetPlayerCompRank(IClientEntity* pEntity);
	extern void ServerRankRevealAll();
	unsigned short UTIL_GetAchievementEventMask();
};

// Trace Line Memes
void UTIL_TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, const IClientEntity *ignore, int collisionGroup, trace_t *ptr);

void UTIL_ClipTraceToPlayers(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr);

bool IsBreakableEntity(IClientEntity* ent);

bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace);

void SayInChat(const char *text);

void SayInTeamChat(const char *text);

void SetName(std::string name);

Vector GetHitpointPosition(IClientEntity* pEntity, int Hitbox, Vector *Point);

//bool GetBestPoint(IClientEntity* pEntity, Hitbox* hitbox, Vector *point);

Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox);

//Vector GetHitscan(IClientEntity* pEntity, int Hitbox);

Vector GetEyePosition(IClientEntity* pEntity);

void ForceUpdate();

//unsigned short UTIL_GetAchievementEventMask();