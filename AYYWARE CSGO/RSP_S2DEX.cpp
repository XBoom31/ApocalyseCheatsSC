/*
Copyright (C) 2002 Rice1964

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/


// This file implements the S2DEX ucode, Yoshi story is using this ucodes
/*

#include "Stdafx.h"
#include "UcodeDefs.h"

uObjTxtr *gObjTxtr = NULL;
uObjTxtrTLUT *gObjTlut = NULL;
uint32 gObjTlutAddr = 0;
uObjMtx *gObjMtx = NULL;
uObjSubMtx *gSubObjMtx = NULL;
uObjMtxReal gObjMtxReal = { 1, 0, 0, 1, 0, 0, 0, 0 };
Matrix gD3DMtxReal(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
Matrix gD3DObjOffset(1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 0, 1.0, 0, 0, 0, 1.0);

uint32 g_TxtLoadBy = CMD_LOAD_OBJ_TXTR;


// YoshiStory uses this - 0x02
void RSP_S2DEX_BG_COPY(Gfx *gfx)
{



	SP_Timing(DP_Minimal16);
	DP_Timing(DP_Minimal16);

	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));
	uObjBg *sbgPtr = (uObjBg*)(g_pRDRAMu8 + dwAddr);
	CRender::g_pRender->LoadObjBGCopy(*sbgPtr);
	CRender::g_pRender->DrawObjBGCopy(*sbgPtr);
}

// YoshiStory uses this - 0x03
void RSP_S2DEX_OBJ_RECTANGLE(Gfx *gfx)
{



	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));
	uObjSprite *ptr = (uObjSprite*)(g_pRDRAMu8 + dwAddr);

	uObjTxSprite objtx;
	memcpy(&objtx.sprite, ptr, sizeof(uObjSprite));

	if (g_TxtLoadBy == CMD_LOAD_OBJ_TXTR)
	{
		memcpy(&(objtx.txtr.block), &(gObjTxtr->block), sizeof(uObjTxtr));
		CRender::g_pRender->LoadObjSprite(objtx, true);
	}
	else
	{
		PrepareTextures();
	}
	CRender::g_pRender->DrawSprite(objtx, false);
}

// YoshiStory uses this - 0x04
void RSP_S2DEX_OBJ_SPRITE(Gfx *gfx)
{



	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));
	uObjSprite *info = (uObjSprite*)(g_pRDRAMu8 + dwAddr);

	uint32 dwTile = gRSP.curTile;
	status.bAllowLoadFromTMEM = false;	// Because we need to use TLUT loaded by ObjTlut cmd
	PrepareTextures();
	status.bAllowLoadFromTMEM = true;

	uObjTxSprite drawinfo;
	memcpy(&(drawinfo.sprite), info, sizeof(uObjSprite));
	CRender::g_pRender->DrawSpriteR(drawinfo, false, dwTile, 0, 0, drawinfo.sprite.imageW / 32, drawinfo.sprite.imageH / 32);
}

// YoshiStory uses this - 0xb0
void RSP_S2DEX_SELECT_DL(Gfx *gfx)
{
	static BOOL bWarned = FALSE;
	//if (!bWarned)
	{
		bWarned = TRUE;
	}

}

void RSP_S2DEX_OBJ_RENDERMODE(Gfx *gfx)
{
}

// YoshiStory uses this - 0xb1
void RSP_GBI1_Tri2(Gfx *gfx);
void RSP_S2DEX_OBJ_RENDERMODE_2(Gfx *gfx)
{



	if (((gfx->words.cmd0) & 0xFFFFFF) != 0 || ((gfx->words.cmd1) & 0xFFFFFF00) != 0)
	{
		// This is a TRI2 cmd
		RSP_GBI1_Tri2(gfx);
		return;
	}

	RSP_S2DEX_OBJ_RENDERMODE(gfx);
}

void ObjMtxTranslate(float &x, float &y)
{
	float x1 = gObjMtxReal.A*x + gObjMtxReal.B*y + gObjMtxReal.X;
	float y1 = gObjMtxReal.C*x + gObjMtxReal.D*y + gObjMtxReal.Y;

	x = x1;
	y = y1;
}

void RSP_S2DEX_SPObjLoadTxtr(Gfx *gfx)
{



	gObjTxtr = (uObjTxtr*)(g_pRDRAMu8 + (RSPSegmentAddr((gfx->words.cmd1))&(g_dwRamSize - 1)));
	if (gObjTxtr->block.type == S2DEX_OBJLT_TLUT)
	{
		gObjTlut = (uObjTxtrTLUT*)gObjTxtr;
		gObjTlutAddr = (uint32)(RSPSegmentAddr(gObjTlut->image));

		// Copy tlut
		int size = gObjTlut->pnum + 1;
		int offset = gObjTlut->phead - 0x100;

		if (offset + size>0x100)
		{
			size = 0x100 - offset;
		}

		uint32 addr = (gObjTlutAddr);//&0xFFFFFFFC);
									 //if( addr & 3 ) addr = (addr&0xFFFFFFF0)+8;;
		uint16 *srcPal = (uint16*)(g_pRDRAMu8 + (addr& (g_dwRamSize - 1)));

		for (int i = offset; i<offset + size; i++)
		{
			g_wRDPTlut[i ^ 1] = RDRAM_UHALF(addr);
			addr += 2;
			//g_wRDPTlut[i] = (*(uint16 *)(addr+g_pRDRAMu8));
			//g_wRDPTlut[i] = *(srcPal++);
		}
	}
	else
	{
		// Loading ObjSprite
		g_TxtLoadBy = CMD_LOAD_OBJ_TXTR;
	}

}

// YoshiStory uses this - 0xc2
void RSP_S2DEX_SPObjLoadTxSprite(Gfx *gfx)
{



	uObjTxSprite* ptr = (uObjTxSprite*)(g_pRDRAMu8 + (RSPSegmentAddr((gfx->words.cmd1))&(g_dwRamSize - 1)));
	gObjTxtr = (uObjTxtr*)ptr;

	//Now draw the sprite
	CRender::g_pRender->LoadObjSprite(*ptr);
	CRender::g_pRender->DrawSpriteR(*ptr);

}


// YoshiStory uses this - 0xc3
void RSP_S2DEX_SPObjLoadTxRect(Gfx *gfx)
{



	uObjTxSprite* ptr = (uObjTxSprite*)(g_pRDRAMu8 + (RSPSegmentAddr((gfx->words.cmd1))&(g_dwRamSize - 1)));
	gObjTxtr = (uObjTxtr*)ptr;

	//Now draw the sprite
	CRender::g_pRender->LoadObjSprite(*ptr);
	CRender::g_pRender->DrawSprite(*ptr, false);

}

// YoshiStory uses this - 0xc4
void RSP_S2DEX_SPObjLoadTxRectR(Gfx *gfx)
{



	uObjTxSprite* ptr = (uObjTxSprite*)(g_pRDRAMu8 + (RSPSegmentAddr((gfx->words.cmd1))&(g_dwRamSize - 1)));
	gObjTxtr = (uObjTxtr*)ptr;

	//Now draw the sprite
	CRender::g_pRender->LoadObjSprite(*ptr);
	CRender::g_pRender->DrawSprite(*ptr, true);

}

void DLParser_TexRect(Gfx *gfx);
// YoshiStory uses this - 0xe4
void RSP_S2DEX_RDPHALF_0(Gfx *gfx)
{
	//RDP: RSP_S2DEX_RDPHALF_0 (0xe449c0a8 0x003b40a4)
	//0x001d3c88: e449c0a8 003b40a4 RDP_TEXRECT 
	//0x001d3c90: b4000000 00000000 RSP_RDPHALF_1
	//0x001d3c98: b3000000 04000400 RSP_RDPHALF_2

	uint32 dwPC = gDlistStack[gDlistStackPointer].pc;		// This points to the next instruction
	uint32 dwNextUcode = *(uint32 *)(g_pRDRAMu8 + dwPC);

	if ((dwNextUcode >> 24) != S2DEX_SELECT_DL)
	{
		// Pokemom Puzzle League
		if ((dwNextUcode >> 24) == 0xB4)
		{
			DLParser_TexRect(gfx);
		}
		else
		{
		}
	}
	else
	{
	}
}

// YoshiStory uses this - 0x05
void RSP_S2DEX_OBJ_MOVEMEM(Gfx *gfx)
{
	uint32 dwCommand = ((gfx->words.cmd0) >> 16) & 0xFF;
	uint32 dwLength = ((gfx->words.cmd0)) & 0xFFFF;
	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));

	if (dwAddr >= g_dwRamSize)
	{
	}

	if (dwLength == 0 && dwCommand == 23)
	{
		gObjMtx = (uObjMtx *)(dwAddr + g_pRDRAMu8);
		gObjMtxReal.A = gObjMtx->A / 65536.0f;
		gObjMtxReal.B = gObjMtx->B / 65536.0f;
		gObjMtxReal.C = gObjMtx->C / 65536.0f;
		gObjMtxReal.D = gObjMtx->D / 65536.0f;
		gObjMtxReal.X = float(gObjMtx->X >> 2);
		gObjMtxReal.Y = float(gObjMtx->Y >> 2);
		gObjMtxReal.BaseScaleX = gObjMtx->BaseScaleX / 1024.0f;
		gObjMtxReal.BaseScaleY = gObjMtx->BaseScaleY / 1024.0f;

	}
	else if (dwLength == 2 && dwCommand == 7)
	{
		gSubObjMtx = (uObjSubMtx*)(dwAddr + g_pRDRAMu8);
		gObjMtxReal.X = float(gSubObjMtx->X >> 2);
		gObjMtxReal.Y = float(gSubObjMtx->Y >> 2);
		gObjMtxReal.BaseScaleX = gSubObjMtx->BaseScaleX / 1024.0f;
		gObjMtxReal.BaseScaleY = gSubObjMtx->BaseScaleY / 1024.0f;

	}

	gD3DMtxReal._11 = gObjMtxReal.A;
	gD3DMtxReal._12 = gObjMtxReal.C;
	gD3DMtxReal._13 = 0;
	gD3DMtxReal._14 = 0;//gObjMtxReal.X;

	gD3DMtxReal._21 = gObjMtxReal.B;
	gD3DMtxReal._22 = gObjMtxReal.D;
	gD3DMtxReal._23 = 0;
	gD3DMtxReal._24 = 0;//gObjMtxReal.Y;

	gD3DMtxReal._31 = 0;
	gD3DMtxReal._32 = 0;
	gD3DMtxReal._33 = 1.0;
	gD3DMtxReal._34 = 0;

	gD3DMtxReal._41 = gObjMtxReal.X;
	gD3DMtxReal._42 = gObjMtxReal.Y;
	gD3DMtxReal._43 = 0;
	gD3DMtxReal._44 = 1.0;

}

// YoshiStory uses this - 0x01
extern void RSP_GBI0_Mtx(Gfx *gfx);

void RSP_S2DEX_BG_1CYC(Gfx *gfx)
{



	SP_Timing(DP_Minimal16);
	DP_Timing(DP_Minimal16);

	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));
	uObjScaleBg *sbgPtr = (uObjScaleBg *)(dwAddr + g_pRDRAMu8);
	CRender::g_pRender->LoadObjBG1CYC(*sbgPtr);
	CRender::g_pRender->DrawObjBG1CYC(*sbgPtr);

}

void RSP_S2DEX_BG_1CYC_2(Gfx *gfx)
{



	if (((gfx->words.cmd0) & 0x00FFFFFF) != 0)
	{
		RSP_GBI0_Mtx(gfx);
		return;
	}

	RSP_S2DEX_BG_1CYC(gfx);
}


// YoshiStory uses this - 0xb2
void RSP_S2DEX_OBJ_RECTANGLE_R(Gfx *gfx)
{



	uint32 dwAddr = RSPSegmentAddr((gfx->words.cmd1));
	uObjSprite *ptr = (uObjSprite*)(g_pRDRAMu8 + dwAddr);

	uObjTxSprite objtx;
	memcpy(&objtx.sprite, ptr, sizeof(uObjSprite));


	//uObjTxSprite* ptr = (uObjTxSprite*)(g_pRDRAMu8+(RSPSegmentAddr((gfx->words.cmd1))&(g_dwRamSize-1)));
	//gObjTxtr = (uObjTxtr*)ptr;

	//Now draw the sprite
	if (g_TxtLoadBy == CMD_LOAD_OBJ_TXTR)
	{
		memcpy(&(objtx.txtr.block), &(gObjTxtr->block), sizeof(uObjTxtr));
		//CRender::g_pRender->LoadObjSprite(*ptr,true);
		CRender::g_pRender->LoadObjSprite(objtx, true);
	}
	else
	{
		PrepareTextures();
	}
	//CRender::g_pRender->DrawSprite(*ptr, true);
	CRender::g_pRender->DrawSprite(objtx, true);

}
*/