/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "Hacks.h"

// All misc visuals (Crosshairs etc) go in this class

class CVisuals : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	void DrawCrosshair();
	void DrawRecoilCrosshair();
	void DrawCenterRadar();
	void DrawHitCrosshair();
};