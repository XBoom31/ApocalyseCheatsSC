#pragma once

#include "CommonIncludes.h"

#include <map>

extern bool SaveFile;
extern bool LoadFile;

class CControl;
class CTab;
class CWindow;
class CGUI;
class CSkinChanger;

extern CGUI GUI;
//extern CSkinChanger *Radar;

enum UIFlags
{
	UI_None = 0x00,
	UI_Drawable = 0x01,
	UI_Clickable = 0x02,
	UI_Focusable = 0x04,
	UI_RenderFirst = 0x08,
	UI_SaveFile = 0x10
};

enum UIControlTypes
{
	UIC_CheckBox = 1,
	UIC_Slider,
	UIC_KeyBind,
	UIC_ComboBox
};

// Base class for GUI controls
class CControl
{
	friend class CGUI;
	friend class CTab;
	friend class CWindow;
public:
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void GetSize(int &w, int &h);
	void SetFileId(std::string fid);

	bool Flag(int f);
protected:
	int m_x, m_y;
	int m_iWidth, m_iHeight;
	int m_Flags;
	CWindow* parent;

	std::string FileIdentifier;
	int FileControlType;

	virtual void Draw(bool) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnClick() = 0;

	POINT GetAbsolutePos();

	POINT GetAbsolutePos2();

};
#pragma once

#define UI_CURSORSIZE		12
#define UI_CURSORFILL		Color(255,255,255)
#define UI_CURSOROUTLINE	Color(20,20,20,140)

#define UI_WIN_TOPHEIGHT	26
#define UI_WIN_TITLEHEIGHT	32


#define UI_TAB_HEIGHT		32

#define UI_WIN_CLOSE_X		20
#define UI_WIN_CLOSE_Y      6

#define UI_CHK_SIZE			16

#define UI_CURSORSIZE		12
#define UI_CURSORFILL		Color(255,255,255)
#define UI_CURSOROUTLINE	Color(20,20,20,140)



#define UI_TAB_WIDTH		100

#define UI_WIN_CLOSE_Y      6

#define UI_CHK_SIZE			16

#define COL_WHITE			Color(255, 255, 255)
//#define UI_COL_MAIN			Color(37, 137, 255, 255)
#define UI_COL_MAINDARK		Color(28,136,0, 255)
#define UI_COL_FADEMAIN		Color(28,136,0, 255)
#define UI_COL_SHADOW		Color(0, 0, 0, 255)
#define UI_COL_CLIENTBACK	Color(30, 30, 30, 255)
#define UI_COL_TABSEPERATOR	Color(132, 132, 132, 200)
#define UI_COL_TABTEXT		Color(145, 145, 145, 255)
#define UI_COL_GROUPOUTLINE Color(222, 222, 222, 255)
// A GUI Control Container
class CTab
{
	friend class CControl;
	friend class CGUI;
	friend class CWindow;
	friend class CSkinChanger;
public:
	void SetTitle(std::string name);
	void SetTitle2(std::string name);

	void RegisterControl(CControl* control);
private:
	std::string Title;
	std::string Title2;

	std::vector<CControl*> Controls;
	CWindow* parent;
	CSkinChanger* parent1;
};

// Base class for a simple GUI window
class CWindow
{
	friend class CControl;
	friend class CGUI;
public:
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void SetTitle(std::string title);
	void Open();
	void Close();
	void Toggle();
	CControl* GetFocus();

	void RegisterTab(CTab* Tab);

	RECT GetClientArea();
	RECT GetTabArea1();
	RECT GetClientArea1();
	RECT GetTabArea();

private:
	void DrawControls();

	bool m_bIsOpen;

	std::vector<CTab*> Tabs;
	CTab* SelectedTab;

	bool IsFocusingControl;
	CControl* FocusedControl;

	std::string Title;
	int m_x;
	int m_y;
	int m_iWidth;
	int m_iHeight;




};
class CSkinChanger {
	friend class CControl;
	friend class CGUI;
public:
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void SetTitle(std::string title);
	void Open();
	void Close();
	void Toggle();
	CControl* GetFocus();

	void RegisterTab(CTab* Tab);

	RECT GetClientArea();
	RECT GetTabArea1();
	RECT GetClientArea1();
	RECT GetTabArea();

private:
	void DrawControls();

	bool m_bIsOpen;

	std::vector<CTab*> Tabs;
	CTab* SelectedTab;

	bool IsFocusingControl;
	CControl* FocusedControl;

	std::string Title;
	int m_x;
	int m_y;
	int m_iWidth;
	int m_iHeight;
};

// User interface manager
class CGUI
{
public:
	CGUI();

	// Draws all windows 
	void Draw();

	// Handle all input etc
	void Update();

	// Draws a single window
	bool DrawWindow(CWindow* window);
	bool DrawRadar(CSkinChanger * Radar);
	// Draws radar window
	bool DrawRadar();

	// Registers a window
	void RegisterWindow(CWindow* window);

	// Config saving/loading
	void SaveWindowState(CWindow* window, std::string Filename);
	void LoadWindowState(CWindow* window, std::string Filename);

	// Window Binds
	void BindWindow(unsigned char Key, CWindow* window);

	// Input
	bool GetKeyPress(unsigned int key);
	bool GetKeyState(unsigned int key);
	bool IsMouseInRegion(int x, int y, int x2, int y2);
	bool IsMouseInRegion(RECT region);
	POINT GetMouse();

private:
	// Input
	// keyboard
	bool keys[256];
	bool oldKeys[256];
	// Mouse
	POINT Mouse;
	bool MenuOpen;

	// Window Dragging
	bool IsDragging;
	CWindow* DraggingWindow;
	CSkinChanger* DraggingRadar;

	int DragOffsetX; int DragOffsetY;

	// Windows
	std::vector<CWindow*> Windows;

	// KeyBinds -> Windows Map
	std::map<int, CWindow*> WindowBinds;

};