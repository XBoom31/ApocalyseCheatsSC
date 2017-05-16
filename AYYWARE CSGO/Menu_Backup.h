#include "stdafx.h"

int MenuRed;
int MenuGreen;
int MenuBlue;
int MenuAlpha;
int TextRed;
int TextGreen;
int TextBlue;
int TextAlpha;
int BackgroundRed;
int BackgroundGreen;
int BackgroundBlue;
int BackgroundAlpha;
int OutlineRed;
int OutlineGreen;
int OutlineBlue;
int OutlineAlpha;

char *speed_smothX = "Movement X";
char *speed_smothY = "Movement Y";
int changeaimtype = Settings.GetMenuSetting(Tab_LegitBot, Legit_typeofaim);
void colourUpdate()
{


	MenuRed = Settings.GetSetting( Tab_Other, Other_MenuRed);
	MenuGreen = Settings.GetSetting( Tab_Other, Other_MenuGreen);
	MenuBlue = Settings.GetSetting( Tab_Other, Other_MenuBlue);
	MenuAlpha = Settings.GetSetting( Tab_Other, Other_MenuAlpha);
	TextRed = Settings.GetSetting( Tab_Other, Other_TextRed);
	TextGreen = Settings.GetSetting( Tab_Other, Other_TextGreen);
	TextBlue = Settings.GetSetting( Tab_Other, Other_TextBlue);
	TextAlpha = Settings.GetSetting( Tab_Other, Other_TextAlpha);

	BackgroundRed = Settings.GetSetting( Tab_Other, Other_BackgroundRed);
	BackgroundGreen = Settings.GetSetting( Tab_Other, Other_BackgroundGreen);
	BackgroundBlue = Settings.GetSetting( Tab_Other, Other_BackgroundBlue);
	BackgroundAlpha = Settings.GetSetting( Tab_Other, Other_BackgroundAlpha);
	OutlineRed = Settings.GetSetting( Tab_Other, Other_OutlineRed);
	OutlineGreen = Settings.GetSetting( Tab_Other, Other_OutlineGreen);
	OutlineBlue = Settings.GetSetting( Tab_Other, Other_OutlineBlue);
	OutlineAlpha = Settings.GetSetting( Tab_Other, Other_OutlineAlpha);

}


bool Clicked_This_Frame;
bool Holding_Mouse_1;
bool Dont_Click;
bool Holding_Menu;
int Menu_Drag_X;
int Menu_Drag_Y;

int Tab_Count = 0;

bool keys[256];
bool oldKeys[256];
bool GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

char* KeyStrings[254] = { "undefined", "Left Mouse", "Right Mouse", "Break", "Middle Mouse", "Mouse 4", "Mouse 5",
"undefined", "Backspace", "TAB", "undefined", "undefined", "undefined", "ENTER", "undefined", "undefined", "SHIFT",
"CTRL", "ALT","PAUSE","CAPS LOCK", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"ESC", "undefined", "undefined", "undefined", "undefined", "SPACEBAR","PG UP", "PG DOWN", "END", "HOME", "Left",
"Up", "Right", "Down", "undefined", "Print", "undefined", "Print Screen", "Insert","Delete", "undefined", "0", "1",
"2", "3", "4", "5", "6", "7", "8", "9", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
"V", "W", "X","Y", "Z", "Left Windows", "Right Windows", "undefined", "undefined", "undefined", "NUM 0", "NUM 1",
"NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6","NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3",
"F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12","F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21",
"F22", "F23", "F24", "undefined", "undefined", "undefined", "undefined", "undefined","undefined", "undefined", "undefined",
"NUM LOCK", "SCROLL LOCK", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "LSHIFT", "RSHIFT", "LCONTROL",
"RCONTROL", "LMENU", "RMENU", "undefined","undefined", "undefined","undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "Next Track", "Previous Track", "Stop", "Play/Pause", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", ";", "+", ",", "-", ".", "/?", "~", "undefined", "undefined",
"undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined","undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "[{", "\\|", "}]", "'\"", "undefined",
"undefined", "undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined" };

void DrawMouse()
{
	static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
	unsigned char buffer[4] = { BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha };

	Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texturer);
	Interfaces.pSurface->DrawSetColor(MenuRed - 10, MenuGreen - 10, MenuBlue - 10, MenuAlpha);

	POINT Mouse;
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	Vertex_t Verts[3];
	Verts[0].x = Mouse.x;
	Verts[0].y = Mouse.y;
	Verts[1].x = Mouse.x + 16;
	Verts[1].y = Mouse.y + 10;
	Verts[2].x = Mouse.x;
	Verts[2].y = Mouse.y + 16;

	Interfaces.pSurface->DrawTexturedPolygon(3, Verts);
}

void CMenu::Set_Current_Tab(int tab)
{
	Current_tab = tab;
}
int CMenu::GetCurret_Tab()
{
	return Current_tab;
}
void CMenu::Update_Frame()
{
	if (!Holding_Mouse_1)
	{
		if (GetClicked())
		{
			Holding_Menu = true;
		}
		else
		{
			Holding_Menu = false;
		}
	}

	if (Holding_Menu)
	{
		MenuPOS NewPOS;
		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;
		NewPOS.x = Mouse.x - Menu_Drag_X;
		NewPOS.y = Mouse.y - Menu_Drag_Y;
		this->pos = NewPOS;
	}
}
bool CMenu::GetClicked()
{

	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		return false;
	}

	POINT Mouse;
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 900 && Mouse.y < this->pos.y + 20)
	{
		if (!Holding_Mouse_1)
		{
			Menu_Drag_X = Mouse.x - pos.x;
			Menu_Drag_Y = Mouse.y - pos.y;
		}
		return true;
	}
	else
	{
		return false;
	}
}

CMenu Menu;
class CButton;
class CSlider;
class CDropbox;
class CKeybutton;
class CTab;
class CMenuBox;

class CButton
{
private:
	MenuPOS pos;
	MenuPOS offset;
	int Tab;
	int Setting;
	char* Name = "ERROR";
	bool Clicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 20 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		return false;
	}
public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Clicked())
			{

				Dont_Click = true;
				Settings.SetBoolSetting(Tab, Setting, !Settings.GetSetting( Tab, Setting));

			}
		}
	}
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{

			Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 20, this->pos.y + 20);


			if (Settings.GetMenuSetting(this->Tab, this->Setting))
			{

				Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
				Interfaces.pSurface->DrawFilledRect(this->pos.x + 4, this->pos.y + 4, this->pos.x + 16, this->pos.y + 16);
				//	Interfaces.pSurface->DrawSetColor(OutlineRed, OutlineGreen, OutlineBlue, 255);
				//	Interfaces.pSurface->DrawOutlinedRect(this->pos.x + 4, this->pos.y + 4, this->pos.x + 16, this->pos.y + 16);

				//Interfaces.pSurface->DrawFilledCircle(this->pos.x + 10, this->pos.y + 10, 8, MenuRed, MenuGreen, MenuBlue, MenuAlpha);

			}

			Interfaces.pSurface->DrawSetColor(OutlineRed, OutlineGreen, OutlineBlue, OutlineAlpha);
			//Interfaces.pSurface->DrawColoredCircle(this->pos.x + 10, this->pos.y + 10, 10, 100, 100, 100, 255);

			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 20, this->pos.y + 20);

			Interfaces.pSurface->DrawT(this->pos.x + 30, this->pos.y + 6, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, this->Name);

		}
	}
	void Init(int Tab, int Setting, bool defult, int x, int y, char* name)
	{

		this->Tab = Tab;
		this->Setting = Setting;
		this->offset.y = y;
		this->offset.x = x;
		this->Name = name;
		Settings.SetBoolSetting(Tab, Setting, defult);

	}
};

class CSlider
{
private:
	int Tab = 0;
	int Setting = 0;
	double Max = 100;
	double Min = 0;
	MenuPOS pos;
	MenuPOS offset;
	char* Name = "ERROR";
	bool Is_Holding;
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			this->Is_Holding = false;
			return false;
		}
		if (Holding_Mouse_1)
		{
			if (!this->Is_Holding)
			{
				return false;
			}
		}
		if (Dont_Click)
			return false;

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			this->Is_Holding = true;
			return true;
		}
		else if (this->Is_Holding)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
			double Location = Ratio * 100;
			Interfaces.pSurface->DrawSetColor(80, 80, 80, 255);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 100, this->pos.y + 15);
			Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 2, this->pos.y + 7, this->pos.x + Location, this->pos.y + 13);
			Interfaces.pSurface->DrawSetColor(200, 200, 200, 255);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);
			Interfaces.pSurface->DrawSetColor(170, 170, 170, 255);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);

			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, "%s: %.1f", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
		}
	}
	void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
	{

		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Max = max;
		Min = min;
		Name = name;

		Settings.SetSetting(Tab, Setting, defult);

	}
	void Update()
	{

		this->pos.x = Menu.pos.x + offset.x;
		this->pos.y = Menu.pos.y + offset.y;

		// get clicked and changing value
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (this->GetClicked())
			{
				Dont_Click = true;
				POINT Mouse;
				POINT mp; GetCursorPos(&mp);
				ScreenToClient(GetForegroundWindow(), &mp);
				Mouse.x = mp.x; Mouse.y = mp.y;
				// get differance
				double idifference;
				idifference = Mouse.x - this->pos.x;
				// Set Value
				double value = ((idifference / 100)*(this->Max - this->Min));
				if (value < Min)
				{
					value = Min;
				}
				else if (value > Max)
				{
					value = Max;
				}

				Settings.SetSetting(Tab, Setting, value);
			}
		}
	}

};

class CDropBox
{
private:
	int Tab = 0;
	int Setting = 0;

	char* Name = "ERROR";
	char* Parts[20];
	int Amount = 0;

	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;

	bool GetClicked()
	{

		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}
		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	int GetPartClicked()
	{
		if (!Clicked_This_Frame)
		{
			return -1;
		}
		if (Holding_Mouse_1)
		{
			return -1;
		}
		if (Dont_Click)
		{
			return -1;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		for (int i = 1; i < this->Amount; i++)
		{
			if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (20 * (i)) && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + (20 * (i + 1)))
			{
				return i;
			}
		}
		return -1;

	}

public:
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if (Tab == Menu.GetCurret_Tab())
		{
			if (this->GetClicked())
			{
				if (this->Dropping == true)
				{
					this->Dropping = false;
				}
				else
				{
					this->Dropping = true;
				}
				Dont_Click = true;
			}
			else if (this->Dropping)
			{
				int index = this->GetPartClicked();
				if (index != -1)
				{
					Settings.SetSetting(this->Tab, this->Setting, index);
					this->Dropping = false;
					Dont_Click = true;
				}
				else if (Clicked_This_Frame && !Holding_Mouse_1)
				{
					Dropping = false;
				}
			}
		}
		else
		{
			Dropping = false;
		}

	}
	void Draw()
	{
		if (Tab == Menu.GetCurret_Tab())
		{
			Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
			Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);;
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, this->Name);

			if (this->Dropping)
			{
				for (int i = 1; i < this->Amount; i++)
				{
					Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
					Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
					Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
					Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
					Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5 + (20 * i), CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, this->Parts[i]);
				}
			}
			else
			{
				Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, this->Parts[(int)Settings.GetMenuSetting(Tab, Setting)]);

				static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
				unsigned char buffer[4] = { BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha };//{ color.r(), color.g(), color.b(), color.a() };

				Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
				Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
				Interfaces.pSurface->DrawSetTexture(Texture); // bind texture

				Vertex_t Verts2[3];
				Verts2[0].x = this->pos.x + 85;
				Verts2[0].y = this->pos.y + 6;
				Verts2[1].x = this->pos.x + 95;
				Verts2[1].y = this->pos.y + 6;
				Verts2[2].x = this->pos.x + 90;
				Verts2[2].y = this->pos.y + 14;

				Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);

			}
		}
	}
	void Init(int x, int y, int tab, int setting, char* name, int parts, char* arr[100])
	{
		Name = name;
		Amount = parts;

		for (int i = 0; i < parts; i++)
		{
			Parts[i] = arr[i];
		}

		Tab = tab;
		Setting = setting;
		offset.x = x;
		offset.y = y;

	}
};

class CKeyButton
{
private:
	MenuPOS pos;
	MenuPOS offset;

	int Tab;
	int Setting;
	bool Getting_New_Key;
	char* Name = "ERROR";

	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, "%s", this->Name);
			Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 20);
			Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 20);

			if (this->Getting_New_Key)
			{
				Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, "<GETTING KEY>");
			}
			else
			{
				if (Settings.GetMenuSetting(this->Tab, this->Setting) == -1)
					Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, "<UNSET>");
				else
				{
					char* NameOfKey = KeyStrings[(int)Settings.GetMenuSetting(this->Tab, this->Setting)];
					Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, NameOfKey);
				}
			}
		}
	}
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Getting_New_Key)
			{
				for (int i = 0; i < 255; i++)
				{
					if (GetKeyPress(i))
					{
						if (i == VK_BACK)
						{
							this->Getting_New_Key = false;
							Settings.SetSetting(Tab, Setting, -1);
							break;
						}

						Settings.SetSetting(Tab, Setting, i);
						this->Getting_New_Key = false;
						break;
					}
				}
			}
			else if (this->GetClicked())
			{

				this->Getting_New_Key = !this->Getting_New_Key;

			}
		}

	}
	void Init(int x, int y, int tab, int setting, char* name)
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Name = name;
		Settings.SetSetting(Tab, Setting, -1);
	}

};

class CTab
{

public:
	void Update()
	{
		pos.x = Menu.pos.x + ((700 / Tab_Count) * Tab) + 2;
		pos.y = Menu.pos.y + 20;

		if (GetClicked())
		{
			Dont_Click = true;
			Menu.Set_Current_Tab(Tab);
		}
	}
	void Draw()
	{
		Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
		Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + (700 / Tab_Count), pos.y + 20);
		if (Menu.GetCurret_Tab() == Tab)
		{
			Interfaces.pSurface->DrawSetColor(MenuRed - 20, MenuGreen - 20, MenuBlue - 20, 255);
			Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + (700 / Tab_Count), pos.y + 20);
		}

		Interfaces.pSurface->DrawT(pos.x + ((700 / Tab_Count) / 2), pos.y + 3, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, Name);
	}
	void Init(char* name, int tab)
	{
		Name = name;
		Tab = tab;
	}
private:
	int Tab;
	MenuPOS pos;
	char* Name = "ERROR";
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;


		if (Mouse.x > pos.x && Mouse.y > pos.y && Mouse.x < pos.x + ((700 / Tab_Count)) && Mouse.y < pos.y + 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CMenuBox
{
public:
	void Init(char* name, int x, int y, int w, int h, int tab)
	{

		Name = name;
		offset.x = x;
		offset.y = y;
		size.x = w;
		size.y = h;
		Tab = tab;

	}
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

	}
	void Draw()
	{
		if (Tab == Menu.GetCurret_Tab())
		{
			Interfaces.pSurface->DrawT(pos.x + (size.x / 2), pos.y - 3, CColor(TextRed, TextBlue, TextGreen, 255), 39, true, Name);
			char Buffer[2048] = { '\0' };
			va_list Args;
			va_start(Args, Name);
			vsprintf_s(Buffer, Name, Args);
			va_end(Args);
			size_t Size = strlen(Buffer) + 1;
			/* set up size.xidebuffer*/
			wchar_t* wBuffer = new wchar_t[Size];
			/* char -> size.xchar */
			mbstowcs_s(0, wBuffer, Size, Buffer, Size - 1);
			/* check center */
			int Width = 0, Height = 0;
			Interfaces.pSurface->GetTextSize(5, wBuffer, Width, Height);
			Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
			Interfaces.pSurface->DrawLine(pos.x, pos.y, pos.x, pos.y + size.y);
			Interfaces.pSurface->DrawLine(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y);
			Interfaces.pSurface->DrawLine(pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y);
			Interfaces.pSurface->DrawLine(pos.x, pos.y, pos.x + ((size.x / 2) - (Width / 2) - 2), pos.y);
			Interfaces.pSurface->DrawLine(pos.x + ((size.x / 2) + (Width / 2) + 2), pos.y, pos.x + size.x, pos.y);
		}
	}


private:
	MenuPOS pos;
	MenuPOS offset;
	MenuPOS size;
	char* Name = "ERROR";
	int Tab;
};

std::vector<CSlider> Sliders;
std::vector<CButton> Buttons;
std::vector<CDropBox> Dropboxes;
std::vector<CKeyButton> KeyButtons;
std::vector<CMenuBox> MenuBoxs;
std::vector<CTab> Tabs;

int Dropboxs_Amount = 0;

void AddNewButton(int Tab, int Setting, bool defult, int x, int y, char* name)
{
	CButton Filler;
	Filler.Init(Tab, Setting, defult, x, y, name);
	Buttons.push_back(Filler);

}
void AddNewSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
{
	CSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting);
	Sliders.push_back(Slid);
}
void AddNewDropbox(int x, int y, int tab, int setting, char* name, int parts, char* arr[100])
{
	CDropBox Dropper;
	Dropper.Init(x, y, tab, setting, name, parts, arr);
	Dropboxes.push_back(Dropper);
	Dropboxs_Amount++;
}
void AddNewKeyButton(int x, int y, int tab, int setting, char* name)
{
	CKeyButton KeyButton;
	KeyButton.Init(x, y, tab, setting, name);
	KeyButtons.push_back(KeyButton);
}
void AddNewTab(char* Name, int Tab)
{
	CTab Filler;
	Filler.Init(Name, Tab);
	Tabs.push_back(Filler);
	Tab_Count++;
}
void AddNewMenuBox(char* name, int x, int y, int w, int h, int tab)
{
	CMenuBox Filler;
	Filler.Init(name, x, y, w, h, tab);
	MenuBoxs.push_back(Filler);
}

void SetupMenu()
{

	char* arr[20] = { "ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR" };

	AddNewTab("Ragebot", Tab_Ragebot);
	AddNewTab("Legitbot", Tab_LegitBot);
	AddNewTab("Visuals", Tab_Visuals);
	AddNewTab("Misc", Tab_Misc);
	AddNewTab("Configs", Tab_Config);
	AddNewTab("Others", Tab_Other);

	AddNewButton(Tab_LegitBot, Legit_Activate, false, 10, 50, "Active");

	/* LEGITBOT */
	AddNewMenuBox("Aimbot", 10, 80, 120, 200, Tab_LegitBot);
	{
		AddNewButton(Tab_LegitBot, Legit_Active, false, 20, 90, "Active");
		AddNewSlider(20, 130, 0, 20, 4, "FOV", Tab_LegitBot, Legit_LegitFOV);
		char *aimbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
		AddNewDropbox(20, 170, Tab_LegitBot, Legit_AimBone, "Aimbone", 7, aimbone);
		AddNewSlider(20, 210, 0, 100, 4, speed_smothX, Tab_LegitBot, Legit_LegitNormalAimSpeedX);
		AddNewSlider(20, 250, 0, 100, 4, speed_smothY, Tab_LegitBot, Legit_LegitNormalAimSpeedY);

	}
	AddNewMenuBox("Smart Aim", 140, 80, 120, 200, Tab_LegitBot);
	{
		AddNewButton(Tab_LegitBot, Legit_SAActive, false, 160, 90, "Active");
		AddNewSlider(150, 130, 0, 20, 4, "SA Bullets", Tab_LegitBot, Legit_Saim);
		char *Saimbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
		AddNewDropbox(150, 170, Tab_LegitBot, Legit_Sabone, "SA Bone", 7, Saimbone);
		AddNewSlider(150, 210, 0, 100, 4, speed_smothX, Tab_LegitBot, Legit_SALegitNormalAimSpeedX);
		AddNewSlider(150, 250, 0, 100, 4, speed_smothY, Tab_LegitBot, Legit_SALegitNormalAimSpeedY);

	}

	AddNewMenuBox("Global", 270, 80, 120, 200, Tab_LegitBot);
	{
		AddNewSlider(280, 100, 0, 20, 0, "Randomise", Tab_LegitBot, Legit_Random);
		char *typeofaim[10] = { "Speed", "Speed", "Smooth", "Curve" };
		AddNewDropbox(280, 140, Tab_LegitBot, Legit_typeofaim, "Type", 4, typeofaim);
		AddNewSlider(280, 180, 0, 10, 5, "Type Factor", Tab_LegitBot, Legit_Factor);
		AddNewSlider(280, 220, 0, 200, 50, "Target Delay", Tab_LegitBot, Legit_lastcount);
		AddNewSlider(280, 250, 0, 100, 0, "TrickShot", Tab_LegitBot, Legit_Trick);

	}
	AddNewButton(Tab_LegitBot, Trigger_Active, false, 400, 50, "Active");

	AddNewMenuBox("Trigger", 400, 80, 120, 200, Tab_LegitBot);
	{
		AddNewButton(Tab_LegitBot, Trigger_Type, true, 410, 90, "On Key");
		AddNewKeyButton(410, 130, Tab_LegitBot, Trigger_Key, "Key");
		AddNewSlider(410, 170, 0, 30, 0, "Delay", Tab_LegitBot, Trigger_Delay);
		AddNewSlider(410, 210, 0, 30, 0, "After", Tab_LegitBot, Trigger_After);
		AddNewButton(Tab_LegitBot, Trigger_Magnet, true, 410, 250, "Mag Active");

	}
	AddNewMenuBox("Magnet Trigger", 530, 80, 120, 200, Tab_LegitBot);
	{
		char *Trigbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
		AddNewDropbox(540, 100, Tab_LegitBot, Trigger_AimBone, "Bone", 7, Trigbone);
		AddNewSlider(540, 140, 0, 10, 3, "Fov", Tab_LegitBot, Trigger_Fov);
		AddNewSlider(540, 180, 0, 100, 3, speed_smothX, Tab_LegitBot, Trigger_SpeedX);
		AddNewSlider(540, 220, 0, 100, 3, speed_smothY, Tab_LegitBot, Trigger_SpeedY);
		AddNewButton(Tab_LegitBot, Trigger_Instant, false, 540, 250, "Instant");

	}

	AddNewMenuBox("RCS", 10, 290, 240, 100, Tab_LegitBot);
	{
		AddNewButton(Tab_LegitBot, Legit_RCS_Enable, true, 20, 300, "Active");
		char *rcstype[10] = { "Aim", "Aim", "Standalone", "+Aim" };
		AddNewDropbox(20, 340, Tab_LegitBot, Legit_RCS_Type, "Type", 4, rcstype);
		AddNewSlider(130, 310, 0, 2, 2, "RCS X", Tab_LegitBot, Legit_RCS_X);
		AddNewSlider(130, 350, 0, 2, 2, "RCS Y", Tab_LegitBot, Legit_RCS_Y);


	}



	/* Ragebot */
	AddNewButton(Tab_Ragebot, Ragebot_Enable, false, 10, 50, "Enable Ragebot");
	AddNewMenuBox("Aimbot", 10, 80, 130, 100, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_Aimbot, false, 20, 90, "Enable Aimbot");
		AddNewButton(Tab_Ragebot, Ragebot_Silent_Aim, false, 20, 120, "Silent");
		AddNewButton(Tab_Ragebot, Ragebot_pSilent, false, 20, 150, "pSilent");
	}
	AddNewButton(Tab_Ragebot, Ragebot_Multipoint, false, 300, 150, "MutiPoint");

	AddNewMenuBox("Speed", 10, 190, 130, 80, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_Speed_Limit, false, 20, 200, "Max Speed");
		AddNewSlider(20, 240, 0, 180, 30, "Speed Amount", Tab_Ragebot, Ragebot_Speed_Limit_Amount);
	}

	AddNewMenuBox("On Button", 10, 280, 130, 80, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_On_Key_Press, false, 20, 290, "Enabled");
		AddNewKeyButton(20, 330, Tab_Ragebot, Rabebot_On_Key_Button, "Key");
	}

	AddNewMenuBox("Movement", 150, 80, 130, 80, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_AutoDuck, false, 160, 90, "Auto Duck");
		AddNewButton(Tab_Ragebot, Ragebot_AutoStop, false, 160, 120, "Auto Stop");
	}

	AddNewMenuBox("Sniper", 150, 170, 130, 40, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_Autoscope, false, 160, 180, "Auto Scope");
	}

	AddNewMenuBox("AntiAim", 290, 170, 130, 40, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, AntiAim_Enable, false, 300, 180, "AntiAim");

		char *Antiaim_X[10] = { "", "","Emotion", "Down", "Up", "Jitter", "Fakedown" };
		AddNewDropbox(300, 200, Tab_Ragebot, AntiAim_X, "Antiaim_X", 7, Antiaim_X);

		char *Antiaim_Y[10] = { "", "","Back", "Side", "Fake Sideways", "Fast Spin", "Slow Spin" };
		AddNewDropbox(300, 220, Tab_Ragebot, AntiAim_Y, "Antiaim_Y", 7, Antiaim_Y);

		AddNewButton(Tab_Ragebot, AntiAim_Enable, false, 300, 180, "AntiAim");
		AddNewButton(Tab_Ragebot, AntiAim_LispAngles, false, 300, 250, "LISP ANGLES");
	}



	/* MISC */
	AddNewMenuBox("Bunny Hop", 10, 80, 130, 100, Tab_Misc);
	{
		AddNewButton(Tab_Misc, Misc_Bunny_Hop, true, 20, 90, "Enabled");
		AddNewButton(Tab_Misc, Misc_Auto_Strafer, true, 20, 120, "AutoStrafer");
	}
	//Move them pls dont remove them
	AddNewButton(Tab_Misc, Misc_Unhook, false, 20, 190, "unhook");
	AddNewButton(Tab_Misc, Misc_WeaponConfigs, false, 20, 230, "Weapon Configs");
	char *wgroup[10] = { "Current", "Rifle","Pistol", "Dak", "Awp", "Scout", "Shotgun", "SMG", "Heavy", "Current" };
	AddNewDropbox(20, 270, Tab_Misc, Misc_WhichWeapon, "Weapon Group", 10, wgroup);


	//Config
	AddNewMenuBox("Load", 10, 80, 130, 100, Tab_Config);
	{
		char *configtype[10] = { "Default", "Legit","HvH", "Rage", "Casual", "Custom1", "Custom2" };
		AddNewDropbox(20, 100, Tab_Config, Config_type, "Config", 7, configtype);

		AddNewButton(Tab_Config, Config_save, false, 20, 140, "Save");
		AddNewButton(Tab_Config, Config_load, false, 20, 180, "Load");

	}


	/* OTHER */
	AddNewMenuBox("Menu", 10, 50, 130, 140, Tab_Other);
	{
		AddNewSlider(20, 70, 0, 255, 70, "Red", Tab_Other, Other_MenuRed);
		AddNewSlider(20, 100, 0, 255, 250, "Green", Tab_Other, Other_MenuGreen);
		AddNewSlider(20, 130, 0, 255, 170, "Blue", Tab_Other, Other_MenuBlue);
		AddNewSlider(20, 160, 0, 255, 255, "Alpha", Tab_Other, Other_MenuAlpha);

	}
	AddNewMenuBox("Text", 10, 200, 130, 140, Tab_Other);
	{
		AddNewSlider(20, 200, 0, 255, 0, "Red", Tab_Other, Other_TextRed);
		AddNewSlider(20, 230, 0, 255, 0, "Green", Tab_Other, Other_TextGreen);
		AddNewSlider(20, 260, 0, 255, 0, "Blue", Tab_Other, Other_TextBlue);
		AddNewSlider(20, 290, 0, 255, 255, "Alpha", Tab_Other, Other_TextAlpha);
	}
	AddNewMenuBox("Background", 150, 50, 130, 140, Tab_Other);
	{
		AddNewSlider(160, 70, 0, 255, 255, "Red", Tab_Other, Other_BackgroundRed);
		AddNewSlider(160, 100, 0, 255, 255, "Green", Tab_Other, Other_BackgroundGreen);
		AddNewSlider(160, 130, 0, 255, 255, "Blue", Tab_Other, Other_BackgroundBlue);
		AddNewSlider(160, 160, 0, 255, 255, "Alpha", Tab_Other, Other_BackgroundAlpha);
	}
	AddNewMenuBox("Outline", 150, 200, 130, 140, Tab_Other);
	{
		AddNewSlider(160, 200, 0, 100, 100, "Red", Tab_Other, Other_OutlineRed);
		AddNewSlider(160, 230, 0, 100, 100, "Green", Tab_Other, Other_OutlineGreen);
		AddNewSlider(160, 260, 0, 100, 100, "Blue", Tab_Other, Other_OutlineBlue);
		AddNewSlider(160, 290, 0, 255, 255, "Alpha", Tab_Other, Other_OutlineAlpha);
	}
}

extern void savesets();
extern std::string settingstostring();
void DrawMenu()
{
	if (Settings.GetSetting( Tab_Config, Config_save)) {
		settingstostring();
		Settings.SetSetting(Tab_Config, Config_save, 0);
	}
	if (Settings.GetSetting( Tab_Config, Config_load)) {
		savesets();
		Settings.SetSetting(Tab_Config, Config_load, 0);
	}

	colourUpdate();
	static bool firsttime = true;
	Dont_Click = false;

	/* UPDATE KEYS */
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		keys[x] = (GetAsyncKeyState(x));
	}

	if (GetKeyPress(VK_INSERT))
	{
		Menu.Opened = !Menu.Opened;
		std::string msg = "cl_mouseenable " + std::to_string(!Menu.Opened);
		Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str());
	}
	//Interfaces.pSurface->DrawSetColor(100, 100, 100, 255);
	//Interfaces.pSurfaceeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee->DrawFilledRect(0, 0, 1000, 1000);

	if (firsttime /* SNIP!!, THIS WILL CAUSE ERRORS FFS! */)
	{
		/* Init Menu Here */
		SetupMenu();
		firsttime = false;
	}


	if (Menu.Opened)
	{
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			Holding_Mouse_1 = false;
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			Clicked_This_Frame = true;
		}
		else
		{
			Clicked_This_Frame = false;
		}

		Menu.Update_Frame();


		Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 700, Menu.pos.y + 400);
		Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 700, Menu.pos.y + 20);
		Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
		Interfaces.pSurface->DrawOutlinedRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 700, Menu.pos.y + 400);
		Interfaces.pSurface->DrawOutlinedRect(Menu.pos.x + 1, Menu.pos.y + 1, Menu.pos.x + 699, Menu.pos.y + 399);
		Interfaces.pSurface->DrawT(Menu.pos.x + 350, Menu.pos.y + 5, CColor(0, 0, 0, 255), 39, true, "Aim Pulse");



		for (CTab& Tab : Tabs)
			Tab.Update();

		for (CMenuBox& MenuBox : MenuBoxs)
			MenuBox.Update();

		for (CDropBox& Dropbox : Dropboxes)
			Dropbox.Update();

		for (CSlider& slider : Sliders)
			slider.Update();

		for (CButton& Button : Buttons)
			Button.Update();

		for (CKeyButton& KeyButton : KeyButtons)
			KeyButton.Update();





		for (CTab& Tab : Tabs)
			Tab.Draw();

		for (CMenuBox& MenuBox : MenuBoxs)
			MenuBox.Draw();

		for (CKeyButton& KeyButton : KeyButtons)
			KeyButton.Draw();

		for (CSlider& slider : Sliders)
			slider.Draw();

		for (CButton& Button : Buttons)
			Button.Draw();

		std::reverse(Dropboxes.begin(), Dropboxes.end());

		for (CDropBox& Dropbox : Dropboxes)
			Dropbox.Draw();

		std::reverse(Dropboxes.begin(), Dropboxes.end());

		DrawMouse();

		if (Clicked_This_Frame)
		{
			Holding_Mouse_1 = true;
		}
	}


}



