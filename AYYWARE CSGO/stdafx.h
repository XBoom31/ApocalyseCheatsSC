#pragma once

#define WIN32_LEAN_AND_MEAN

#include "targetver.h"
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <psapi.h>
#include <time.h>
#include <process.h>
#include <vector>
#include <map>
#include <ostream>
#include <Shlobj.h>
#include <math.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <cmath>
#include <float.h>
#include <codecvt>
using namespace std;
#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
#include <atlcom.h>
#include <sapi.h>
#include <algorithm>
#include <iterator>


/* Some other shit */
#include "ConsoleColours.h"

extern HMODULE hMod;
DWORD WINAPI CheatMain(LPVOID lpThreadParameter);

#include "VMTManager.h"
extern VMTManager VMTPanel;
extern VMTManager VMTClient;
extern VMTManager VMTModelRender;
extern VMTManager VMTD3DDevice9;
extern VMTManager VMTGameEvent;

#include "SettingsManger.h"

/*SDK*/
#include "Vectors.h"
#include "Utils.h"
#include "SDK.h"


/* Cheat And Hooks */
class CHackManager;
extern CHackManager Hacks;

/* some random stuffs */
extern int MenuRed;
extern int MenuGreen;
extern int MenuBlue;
extern int MenuAlpha;
extern int TextRed;
extern int TextGreen;
extern int TextBlue;
extern int TextAlpha;
extern int BackgroundRed;
extern int BackgroundGreen;
extern int BackgroundBlue;
extern int BackgroundAlpha;
extern int OutlineRed;
extern int OutlineGreen;
extern int OutlineBlue;
extern int OutlineAlpha;
extern bool Clicked_This_Frame;
extern bool Holding_Mouse_1;
extern bool Dont_Click;
extern bool warmup;

#include "Menu.h"
#include "Playerlist.h"
#include "Playerlist.h"
#include "Hacks.h"
#include "Hooks.h"





