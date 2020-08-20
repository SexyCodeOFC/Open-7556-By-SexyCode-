#include "stdafx.h"
#include "Gui.h"

Gui* WindowGui(int SpriteIndex, float X, float Y, float Width, float Height, int unk1, int unk2)
{
	DWORD pAllocWindow = callCdecl(0x5B8113, DWORD, DWORD)(0x1E4);
	return callThiscall(0x401426, Gui*, DWORD, DWORD, float, float, float, float, int, int)(
		pAllocWindow, SpriteIndex, X, Y, Width, Height, unk1, unk2
		);
}

Gui* ButtonGui(int SpriteIndex, float X, float Y, float Width, float Height, int unk1, int unk2, const char* Text)
{
	// Create ButtonGUI (VMTable = 0x5CD418)
	DWORD pAllocButton = callCdecl(0x5B8113, DWORD, DWORD)(0x208);
	return callThiscall(0x40332E, Gui*, DWORD, int, float, float, float, float, int, int, const char*) (
		pAllocButton, SpriteIndex, X, Y, Width, Height, unk1, unk2, Text
		);//004DC637  |. E8 7886F2FF           CALL WYD.00404CB4                                                  ; \WYD.00404CB4


}

Gui* LabelGui(int SpriteIndex, const char* Text, int unk1, float X, float Y, float Width, float Height, int unk2, int unk3, int unk4, int unk5)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0xE4C);
	return callThiscall(0x401CCD, Gui*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)(
		pAllocLabel, SpriteIndex, Text, unk1, X, Y, Width, Height, unk2, unk3, unk4, unk5
		);
}

Gui* MessagePanelGui(int SpriteIndex, const char* Text, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x1FC);
	return callThiscall(0x403CF4, Gui*, DWORD, const char*, float, float, float, float, int)(
		pAllocLabel, Text, X, Y, Width, Height, 0x7D0);
}

Gui* ProgressBar(float X, float Y, float Width, float Height, int curr, int max, int backcolor, int color)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x374);
	return callThiscall(0x404CB4, Gui*, DWORD, int, int, int, float, float, float, float, int, int, int)(
		pAllocLabel, -1, curr, max, X, Y, Width, Height, color, backcolor, 1);
}

Gui* BarraRolagem(float X, float Y, float Width, float Height, int curpos, int maxpos)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x94);
	return callThiscall(0x4053E2, Gui*, DWORD, int, int, float, float, float, float, int, int, int, int)(
		pAllocLabel, curpos, maxpos, X, Y, Width, Height, 0, 1, 0xFFAAAAA, 0);
}

Gui* LabelColor(int Color, const char* Text, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0xE6C);
	return callThiscall(0x406AC8, Gui*, DWORD, const char*, int, float, float, float, float, char, int, int, int)(
		pAllocLabel, Text, Color, X, Y, Width, Height, 0, 0x77777777, 1, 0);
}

Gui* TextBox(const char* Text, int password, int center, float X, float Y, float Width, float Height)
{

	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x1064);
	return callThiscall(0x406082, Gui*, DWORD, int, const char*, int, int, int, float, float, float, float, char, int, int, int)(
		pAllocLabel, -1, Text, 15, password, -1, X, Y, Width, Height, 0, 0, 0, center);
	/*-1 = parece ser algo relacionado com atualização*/
}

Gui* Unk6Gui(int SpriteIndex, const char* Text, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x1E4);
	return callThiscall(0x401426, Gui*, DWORD, int, float, float, float, float, int, int)(
		pAllocLabel, -44, Height, Y, Width, Height, 0xAAFFFFFF, 4);
}

Gui* UnkGui(int SpriteIndex, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x3AC);
	return callThiscall(0x407FE9, Gui*, DWORD, int, int, int, float, float, float, float, int, int, int, char, char)(
		pAllocLabel, -1, 0xA, 0xA, X, Y, Width, Height, 0, 4, 1, 0, 0);
}

Gui* Unk2Gui(int SpriteIndex, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0xE54);
	return callThiscall(0x407FE9, Gui*, DWORD, int, int, float, float, float, float, char, int, int, int)(
		pAllocLabel, -1, 0xFFFFFFFF, X, Y, Width, Height, 0, 0x77777777, 1, 0);
	/*
	0xFFFFFFFF
	0xFFFFAAAA
	*/
}

Gui* Unk3Gui(int SpriteIndex, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0x678);
	return callThiscall(0x40C9EE, Gui*, DWORD, int, int, float, float)(
		pAllocLabel, 0, 0, 0, 0);
}

Gui* Unk4Gui(int SpriteIndex, float X, float Y, float Width, float Height)
{
	DWORD pAllocLabel = callCdecl(0x5B8113, DWORD, DWORD)(0xB8);
	return callThiscall(0x40C9EE, Gui*, DWORD, int, int, float, float)(
		pAllocLabel, 0, 0, 0, 0);
}