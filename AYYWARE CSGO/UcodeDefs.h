/*
Copyright (C) 2003-2009 Rice1964

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

#ifndef _UCODE_DEFS_H_
#define _UCODE_DEFS_H_

struct Instruction
{
	union
	{
		u32 cmd0;
		struct
		{
			u32 arg0 : 24;
			u32 cmd : 8;
		};
	};
	union
	{
		u32 cmd1;
		struct
		{
			u32 arg1 : 24;
			u32 pad : 8;
		};
	};
};

struct GGBI1_Matrix
{
	u32	len : 16;
	u32	projection : 1;
	u32	load : 1;
	u32	push : 1;
	u32 : 5;
		  u32	cmd : 8;
		  u32 addr;
};

struct GGBI1_PopMatrix
{
	u32 : 24;
		  u32	cmd : 8;
		  u32	projection : 1;
		  u32 : 31;
};

struct GGBI2_Matrix
{
	union
	{
		struct
		{
			u32	param : 8;
			u32	len : 16;
			u32	cmd : 8;
		};
		struct
		{
			u32	nopush : 1;
			u32	load : 1;
			u32	projection : 1;
			u32 : 5;
				  u32	len2 : 16;
				  u32	cmd2 : 8;
		};
	};
	u32 addr;
};


struct GGBI0_Vtx
{
	u32 len : 16;
	u32 v0 : 4;
	u32 n : 4;
	u32 cmd : 8;
	u32 addr;
};

struct GGBI1_Vtx
{
	u32 len : 10;
	u32 n : 6;
	u32 : 1;
		  u32 v0 : 7;
		  u32 cmd : 8;
		  u32 addr;
};

struct GGBI2_Vtx
{
	u32 vend : 8;
	u32 : 4;
		  u32 n : 8;
		  u32 : 4;
				u32 cmd : 8;
				u32 addr;
};

struct GGBI1_BranchZ
{
	u32 pad0 : 1;
	u32 vtx : 11;
	u32 pad1 : 12;
	u32 cmd : 8;
	u32 value : 32;
};

struct GGBI1_ModifyVtx
{
	u32 pad0 : 1;
	u32 vtx : 15;
	u32 offset : 8;
	u32 cmd : 8;
	u32 value;
};

struct GBI_Texture
{
	u32	enable_gbi0 : 1;
	u32	enable_gbi2 : 1;
	u32 : 6;
		  u32	tile : 3;
		  u32	level : 3;
		  u32 : 10;
				u32	cmd : 8;
				u32	scaleT : 16;
				u32	scaleS : 16;
};

struct SetCullDL
{
	u32 pad0 : 1;
	u32 first : 15;
	u32 pad2 : 8;
	u32 cmd : 8;
	u32 pad3 : 1;
	u32 end : 15;
	u32 pad4 : 8;
};

struct SetTImg
{
	u32 width : 12;
	u32 : 7;
		  u32 siz : 2;
		  u32 fmt : 3;
		  u32	cmd : 8;
		  u32 addr;
};

struct LoadTile
{
	u32	tl : 12; //Top
	u32	sl : 12; //Left
	u32	cmd : 8;

	u32	th : 12; //Bottom
	u32	sh : 12; //Right
	u32	tile : 3;
	u32	pad : 5;
};


struct GGBI1_MoveWord
{
	u32	type : 8;
	u32	offset : 16;
	u32	cmd : 8;
	u32	value;
};

struct GGBI2_MoveWord
{
	u32	offset : 16;
	u32	type : 8;
	u32	cmd : 8;
	u32	value;
};

struct GGBI2_Tri1
{
	u32 v0 : 8;
	u32 v1 : 8;
	u32 v2 : 8;
	u32 cmd : 8;
	u32 pad : 24;
	u32 flag : 8;
};

struct GGBI2_Tri2
{
	u32 : 1;
		  u32 v3 : 7;
		  u32 : 1;
				u32 v4 : 7;
				u32 : 1;
					  u32 v5 : 7;
					  u32 cmd : 8;
					  u32 : 1;
							u32 v0 : 7;
							u32 : 1;
								  u32 v1 : 7;
								  u32 : 1;
										u32 v2 : 7;
										u32 flag : 8;
};

struct GGBI2_Line3D
{
	u32 v3 : 8;
	u32 v4 : 8;
	u32 v5 : 8;
	u32 cmd : 8;

	u32 v0 : 8;
	u32 v1 : 8;
	u32 v2 : 8;
	u32 flag : 8;
};

struct GGBI1_Line3D
{
	u32 w0;
	u32 v2 : 8;
	u32 v1 : 8;
	u32 v0 : 8;
	u32 v3 : 8;
};

struct GGBI1_Tri1
{
	u32 w0;
	u32 v2 : 8;
	u32 v1 : 8;
	u32 v0 : 8;
	u32 flag : 8;
};

struct GGBI1_Tri2
{
	u32 v5 : 8;
	u32 v4 : 8;
	u32 v3 : 8;
	u32 cmd : 8;

	u32 v2 : 8;
	u32 v1 : 8;
	u32 v0 : 8;
	u32 flag : 8;
};

struct GGBI0_Tri4
{
	u32 v0 : 4;
	u32 v3 : 4;
	u32 v6 : 4;
	u32 v9 : 4;
	u32 pad : 8;
	u32 cmd : 8;
	u32 v1 : 4;
	u32 v2 : 4;
	u32 v4 : 4;
	u32 v5 : 4;
	u32 v7 : 4;
	u32 v8 : 4;
	u32 v10 : 4;
	u32 v11 : 4;
};

struct GSetColor
{
	u32	prim_level : 8;
	u32	prim_min_level : 8;
	u32	pad : 8;
	u32	cmd : 8;

	union
	{
		u32	color;
		struct
		{
			u32 fillcolor : 16;
			u32 fillcolor2 : 16;
		};
		struct
		{
			u32 a : 8;
			u32 b : 8;
			u32 g : 8;
			u32 r : 8;
		};
	};
};

struct GGBI1_Dlist {
	u32 : 16;
		  u32	param : 8;
		  u32	cmd : 8;
		  u32 addr;
};

struct SetScissor
{
	u32	y0 : 12;
	u32	x0 : 12;
	u32	cmd : 8;
	u32	y1 : 12;
	u32	x1 : 12;
	u32	mode : 2;
	u32	pad : 6;
};

struct Gsettile
{
	u32	tmem : 9;
	u32	line : 9;
	u32	pad0 : 1;
	u32	siz : 2;
	u32	fmt : 3;
	u32	cmd : 8;

	u32	shifts : 4;
	u32	masks : 4;
	u32	ms : 1;
	u32	cs : 1;
	u32	shiftt : 4;
	u32	maskt : 4;
	u32	mt : 1;
	u32	ct : 1;
	u32	palette : 4;
	u32	tile : 3;
	u32	pad1 : 5;
};

struct SetFillRect
{
	u32 pad1 : 2;
	u32 y1 : 10;
	u32 pad0 : 2;
	u32 x1 : 10;
	u32 cmd : 8;

	u32 pad3 : 2;
	u32 y0 : 10;
	u32 pad4 : 2;
	u32 x0 : 10;
	u32 pad2 : 8;
};

struct SetPrimDepth
{
	u32 pad0 : 24;
	u32 cmd : 8;
	u32 dz : 16;
	u32 z : 15;
	u32 pad : 1;
};

struct SetOthermode
{
	u32	len : 8;
	u32	sft : 8;
	u32	pad : 8;
	u32	cmd : 8;
	u32	data;
};


struct N64Viewport
{
	s16 scale_y, scale_x, scale_w, scale_z;
	s16 trans_y, trans_x, trans_w, trans_z;
};

struct N64mat
{
	struct _s16
	{
		s16 y, x, w, z;
	};

	struct _u16
	{
		unsigned short y, x, w, z;
	};

	_s16 h[4];
	_u16 l[4];
};

struct TriDKR
{
	u8	v2, v1, v0, flag;
	signed short	t0, s0;
	signed short	t1, s1;
	signed short	t2, s2;
};

struct N64Light
{
	u8 ca, b, g, r;					// Colour and ca (ca is different for conker)
	u8 la, b2, g2, r2;
	union
	{
		struct
		{
			s8 pad0, dir_z, dir_y, dir_x;	// Direction
			u8 pad1, qa, pad2, nonzero;
		};
		struct
		{
			s16 y1, x1, w1, z1;		// Position, GBI2 ex Majora's Mask
		};
	};
	s32 pad4, pad5, pad6, pad7;		// Padding..
	s16 y, x, w, z; 				// Position, Conker
};


union MicroCodeCommand
{
	Instruction		inst;
	GGBI0_Vtx		vtx0;
	GGBI1_Vtx		vtx1;
	GGBI2_Vtx		vtx2;

	GGBI1_ModifyVtx	modifyvtx;
	GGBI1_BranchZ	branchz;
	GGBI1_Matrix	mtx1;
	GGBI2_Matrix	mtx2;
	GGBI1_PopMatrix	popmtx;

	GGBI1_Line3D	gbi1line3d;
	GGBI1_Tri1		gbi1tri1;
	GGBI1_Tri2		gbi1tri2;
	GGBI2_Line3D	gbi2line3d;
	GGBI2_Tri1		gbi2tri1;
	GGBI2_Tri2		gbi2tri2;
	GGBI0_Tri4		tri4;

	GGBI1_MoveWord	mw1;
	GGBI2_MoveWord	mw2;
	GBI_Texture		texture;
	GGBI1_Dlist		dlist;

	SetCullDL		culldl;
	GSetColor		setcolor;
	SetTImg			img;

	SetScissor		scissor;
	LoadTile		loadtile;
	SetFillRect		fillrect;
	SetPrimDepth	primdepth;
	SetOthermode	othermode;
	Gsettile		settile;

	/*
	Gdma		dma;
	Gsegment	segment;
	GsetothermodeH	setothermodeH;
	GsetothermodeL	setothermodeL;
	Gtexture	texture;
	Gperspnorm	perspnorm;
	Gsetcombine	setcombine;
	Gfillrect	fillrect;
	Gsettile	settile;
	Gloadtile	loadtile;
	Gsettilesize	settilesize;
	Gloadtlut	loadtlut;
	*/
	__int64	force_structure_alignment;
};
#endif