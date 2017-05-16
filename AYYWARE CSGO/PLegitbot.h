#pragma once
#include "stdafx.h"

class CLegitbot
{
public:
	void Move();
	void Normalise(Vector &angle);

private:
	Vector Rcs(bool first); 
	Vector RcsStandalone(bool aimbot);
	bool TriggerHold();
	bool MagnetTrigger();
	bool Aimbot(double Smooth, int PrimaryHitbox, int HitboxSelection, bool First, double Fov, double Curve, double Time);
	int getHitBox(int Hitbox, int Selection, Vector ViewOffSet, Vector View, CBaseEntity* pEntity, bool firstt);
	bool isVisable(CBaseEntity* Target, int HitBox);
	Vector CalculateSmoothPoint(Vector start, Vector end, double smooth, double BestFov);

	void Legitbot();
	Vector CalculateBezierPoint(double t, Vector start, Vector end, float curvefac, bool first);
	Vector GetHitboxPOS(CBaseEntity* Player, int HitboxID);
	void Do_pSilent(Vector AimbotAng, Vector Antiaimang);
	float FovToPlayer(Vector ViewOffSet, Vector View, CBaseEntity* pEntity, int HitBox);
	Vector AimAng(Vector point);
	Vector Getspeed(int value, double Smooth, Vector Target);
	double randomval(double value);
	double AngletoScreenX(double angle, double previous);
	double AngletoScreenY(double angle, double previous);
	void Triggerbot();
	void InXTriggerbot();
	bool HitboxTriggerbot();
	bool checkhitbox();
	bool IsPosVisable(Vector Target, CBaseEntity* Player);
	void SlowAim();
	bool IsGoodPlayer(CPlayer * Target);

	bool IsVisable(CPlayer* Target, int boneID);
	double posX =0;
	double posY =0;
	int tick = 1;
	int Target_Bone;
	int Target_Bone_PerEnt;
};
extern CLegitbot Legitbot;