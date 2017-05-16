#pragma once
#include "stdafx.h"



extern double PlistArray[102][200];

extern int currentplayerinplst;
class CPlayer
{
public:

	void Add_Player(CBaseEntity* Ent)
	{
		Entity = Ent;
		Team = Ent->GetTeam();
		if (!Entity)
			Index = -1;
		else
			Index = Entity->GetIndex();
		Interfaces.pEngine->GetPlayerInfo(Index, info);
		Name = info->m_szPlayerName;
		Is_Empty = false;
	}

	void Reset_Player()
	{
		Is_Empty = true;
		Last_Update = 0;
		Name = "ERROR! UNNAMED!";
		Selected_On_Menu = false;
		friendly = false;
		priority = false;

		if (Index != -1) {
			for (int i = 0; i < 199; i++)
			{
				PlistArray[Index][i] = 0;
			}
		}
		Index = -1;
	}

	player_info_t* info = new player_info_t;
	CBaseEntity* Entity;
	int Last_Update = 0;
	int Team = 0;
	bool Is_Empty = true;
	int Index = -1;
	char* Name = "ERROR! UNNAMED!";
	bool Selected_On_Menu = false;
	bool friendly = false;
	bool priority = false;
	float beforexdyna = 0;
	Vector Resolved_Angle;
	int sanitycheck = 0;
	int lastpelvisang = 0;
	float difference = 0;
	Vector Resolved_Angles = Vector(0,0,0);
	Vector RealAng = Vector(0, 0, 0);
	Vector FakeAng = Vector(0, 0, 0);
	char * aa = "Unkown";
	bool updated;
	Vector Orig_Angle;
	Vector reset = Vector(0, 0, 0);
	Vector delta = Vector(0, 0, 0);
};




class CPlayerList
{
public:
	void Update()
	{
		if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
		{
			CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

			for (int i = 0; i < 99; i++)
			{
				CBaseEntity* Ent = Interfaces.pEntList->GetClientEntity(i);
				if (!Ent) { Playerlist_Players[i].Reset_Player(); continue; }

				ClientClass* cClass = (ClientClass*)Ent->GetClientClass();
				if (cClass->m_ClassID != 35)
				{
					Playerlist_Players[i].Reset_Player(); continue;
				}

				if (Ent == me) { Playerlist_Players[i].Reset_Player(); continue; }
				Playerlist_Players[i].Add_Player(Ent);
			}
			
			if (Settings.GetSetting(Tab_Misc, Misc_ResetPlist)) {
				for (int i = 0; i < 99; i++)
				{
					Playerlist_Players[i].Reset_Player();
				}
				Settings.SetSetting(Tab_Misc, Misc_ResetPlist, 0);
			}
			Setup = true;
		}
	}
	
	CPlayer* Get_Player_By_Index(int i)
	{
		return &Playerlist_Players[i];
	}

	void Menu_Playerlist_Drawing(int x, int y /* MENU POS */)
	{
		Interfaces.pSurface->DrawSetColor(BackgroundRed / 4, BackgroundGreen / 4, BackgroundBlue / 4, BackgroundAlpha);
		Interfaces.pSurface->DrawOutlinedRect(x, y, x + 150, y + 300);

		if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && Setup)
		{

			std::vector<CPlayer*> Players_To_Draw;

			for (int i = 0; i < 99; i++)
			{
				if (!Playerlist_Players[i].Is_Empty)
				{
					Players_To_Draw.push_back(&Playerlist_Players[i]);
				}
			}

			int Players = 0;

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				POINT Mouse;
				POINT mp; GetCursorPos(&mp);
				ScreenToClient(GetForegroundWindow(), &mp);
				Mouse.x = mp.x; Mouse.y = mp.y;
				bool c = true;
				for (CPlayer* Player : Players_To_Draw)
				{
					if (Mouse.x > x && Mouse.y > y + (Players * 20) && Mouse.x < x + 150 && Mouse.y < y + 20 + (Players * 20))
					{
						for (int y = 0; y < 99; y++)
						{
							Playerlist_Players[y].Selected_On_Menu = false;
						}
						Player->Selected_On_Menu = true;		
						break;
					}
					Players++;
				}
			}

			Players = 0;



			int Team = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer())->GetTeam();

			for (CPlayer* Player : Players_To_Draw)
			{
				if (Player->Selected_On_Menu) {
					if (Player->Team == Team) {
						Interfaces.pSurface->DrawSetColor(230, 230, 0, 150);
					}else
					Interfaces.pSurface->DrawSetColor(0, 91, 230, 150);
					char * value = "";
					Interfaces.pSurface->DrawT(x + 500, y + 170, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, value);
					Interfaces.pSurface->DrawT(x + 500, y + 100, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, "Fake");
					char *value2 = "";
					Interfaces.pSurface->DrawT(x + 500, y + 130, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, value2);

					char *AA = "";
					Interfaces.pSurface->DrawT(x + 500, y + 160, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, "AntiAim");
					Interfaces.pSurface->DrawT(x + 500, y + 190, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, Player->aa);

					Interfaces.pSurface->DrawT(x + 500, y + 40, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, "Real");
				}
				else if (Player->Team == Team)
					Interfaces.pSurface->DrawSetColor(255, 255, 0, 150);
				else
					Interfaces.pSurface->DrawSetColor(23, 116, 255, 150);

				Interfaces.pSurface->DrawFilledRect(x + 1, y + 1 + (Players * 20), x + 148, y + 20 + (Players * 20));
				Interfaces.pSurface->DrawSetColor(OutlineRed, OutlineGreen, OutlineBlue, 255);
				Interfaces.pSurface->DrawOutlinedRect(x + 1, y + 1 + (Players * 20), x + 148, y + 20 + (Players * 20));
				Interfaces.pSurface->DrawT(x + 20, y + (Players * 20) + 2, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 11, false, Player->Name); // 39 STRIKES AGAIN!!!!!!!!!!!!!!!!!!! :))))

				Players++;

				if (Player->Selected_On_Menu)
				{
					currentplayerinplst = Player->Entity->GetIndex();
				}
			}
		}
	}

private:
	bool Setup = false;
	int Current_Tick = 0;
	CPlayer Playerlist_Players[100];
};

extern CPlayerList Playerlist;

