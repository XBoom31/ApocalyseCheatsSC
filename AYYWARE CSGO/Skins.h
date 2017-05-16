#pragma once

#include "dt_recv2.h"
#include "stdafx.h"

#include <unordered_map>

extern RecvVarProxyFn fnSequenceProxyFn;

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

#define	LIFE_ALIVE 0

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

struct SkinStruct {
	int nItemDefinitionIndex = 0;
	int nFallbackPaintKit = 0;
	int nFallbackSeed = 0;
	int nFallbackStatTrak = -1;
	int nEntityQuality = 0;
	float flFallbackWear = 0.1f;
	char* szWeaponName = nullptr;
};

extern std::unordered_map<int, SkinStruct>  g_SkinCFG;
extern std::unordered_map<int, const char*> g_ViewModelCFG;
extern std::unordered_map<const char*, const char*> g_KillIconCfg;

extern void SetSkinCFG();

extern void SetViewModelCFG();

extern void SetKillIconCFG();

extern void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);

extern bool ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex);

extern bool ApplyCustomModel(CBaseEntity* pLocal, CBaseAttributableItem* pWeapon, int nWeaponIndex);

extern bool ApplyCustomKillIcon(IGameEvent* pEvent);