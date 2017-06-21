/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "CommonIncludes.h"
#include "Utilities.h"

// Various offsets
namespace Offsets
{
	// Sets up all the shit we need
	void Initialise();

	// Addresses of loaded game modules
	namespace Modules
	{
		extern DWORD Client;
		extern DWORD Engine;
		extern DWORD VGUI2;
		extern DWORD VGUISurface;
		extern DWORD Material;
		extern DWORD VPhysics;
		extern DWORD Stdlib;
		extern DWORD InputLib;

	};

	// Virtual Method Table Indexes
	namespace VMT
	{
		//CHL Client
		extern DWORD CHL_GetAllClasses;

		//Engine Client
		extern DWORD Engine_GetScreenSize;
		extern DWORD Engine_GetPlayerInfo;
		extern DWORD Engine_GetLocalPlayer;
		extern DWORD Engine_Time;
		extern DWORD Engine_GetViewAngles;
		extern DWORD Engine_SetViewAngles;
		extern DWORD Engine_GetMaxClients;
		extern DWORD Engine_IsConnected;
		extern DWORD Engine_IsInGame;
		extern DWORD Engine_WorldToScreenMatrix;
		extern DWORD Engine_GetNetChannelInfo;
		extern DWORD Engine_ClientCmd_Unrestricted;

		// Panels
		extern DWORD Panel_GetName;
		extern DWORD Panel_PaintTraverse;

		// Surface
		extern DWORD Surface_DrawSetColorA;
		extern DWORD Surface_DrawSetColorB;
		extern DWORD Surface_DrawFilledRect;
		extern DWORD Surface_DrawOutlinedRect;
		extern DWORD Surface_DrawLine;
		extern DWORD Surface_DrawSetTextFont;
		extern DWORD Surface_DrawSetTextColorA;
		extern DWORD Surface_DrawSetTextColorB;
		extern DWORD Surface_DrawSetTextPos;
		extern DWORD Surface_DrawPrintText;
		extern DWORD Surface_DrawSetTextureRGBA;
		extern DWORD Surface_DrawSetTexture;
		extern DWORD Surface_CreateNewTextureID;
		extern DWORD Surface_FontCreate;
		extern DWORD Surface_SetFontGlyphSet;
		extern DWORD Surface_GetTextSize;
		extern DWORD Surface_DrawOutlinedCircle;
		extern DWORD Surface_SurfaceGetCursorPos;
		extern DWORD Surface_DrawTexturedPolygon;

		extern DWORD Material_GetName;
		extern DWORD Material_SetMaterialVarFlag;
		extern DWORD Material_GetMaterialVarFlag;
		extern DWORD Material_AlphaModulate;
		extern DWORD Material_ColorModulate;
		extern DWORD Material_IncrementReferenceCount;

		extern DWORD MaterialSystem_FindMaterial;
		extern DWORD MaterialSystem_CreateMaterial;

		extern DWORD ModelRender_ForcedMaterialOverride;
		extern DWORD ModelRender_DrawModelExecute;

		extern DWORD ModelInfo_GetModelName;
		extern DWORD ModelInfo_GetStudiomodel;
		
		extern DWORD RenderView_SetBlend;
		extern DWORD RenderView_SetColorModulation;

		// Weapon entities
		extern DWORD Weapon_GetSpread;
	};

	// Addresses of engine functions to call
	namespace Functions
	{
		extern DWORD KeyValues_KeyValues;
		extern DWORD KeyValues_LoadFromBuffer;
		extern DWORD dwCalcPlayerView;
		extern DWORD dwGetPlayerCompRank;
		extern DWORD dwIsReady;
	};

};