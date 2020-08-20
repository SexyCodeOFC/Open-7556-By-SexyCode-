#include "stdafx.h"
#include "Functions.h"
#include "Anti_RE.h"
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>

int Protect::Speed()
{
	if (*(int*)0x0502887 != 1000 ||
		*(int*)0x04612E3 != 1000 ||
		*(int*)0x054B05C != 1166747506 ||
		*(int*)0x0483DA9 != 200 ||
		*(int*)0x054B08E != 1300981106 ||
		*(int*)0x049AE64 != 2508937077 ||
		*(int*)0x05189BB != 1000 ||
		*(int*)0x046043E != 1000 ||
		*(int*)0x0463E60 != 1000)
		return 1;

	return 0;
}

int Protect::Range()
{
	if (*(int*)0x045C4B2 != 0 ||
		*(int*)0x045C4E0 != 1 ||
		*(int*)0x045FCD5 != 0 ||
		*(int*)0x045FD03 != 1 ||
		*(int*)0x0467365 != 0 ||
		*(int*)0x0467394 != 1 ||
		*(int*)0x046E002 != 0 ||
		*(int*)0x046E022 != 1 ||
		*(int*)0x049B052 != 0 ||
		*(int*)0x049B096 != 1 ||
		*(int*)0x049B8CB != 0 ||
		*(int*)0x049B8F9 != 1 ||
		*(int*)0x0502859 != 0 ||
		*(int*)0x0502879 != 1 ||
		*(int*)0x051898D != 0 ||
		*(int*)0x05189AC != 1)
		return 2;

	return 0;
}

bool GetFileName(char* text)
{
	sprintf(LoadFileName, text);
	return true;
}

unsigned static long dwRecvCall;
unsigned static long dwSendCall;
unsigned static char bAddr_r[6], bAddr_s[6];

void Protect::CheckNewDll()
{
	for (int i = 0x401000; i < 0x5F0FFF; i++)
	{
		if (*(DWORD*)i == 0x5CD164)
		{
			if (i != 0x4BF99C && i != 0x4C179E && i != 0x4C196A && i != 0x57C7F7 && i != 0x5C6063 && i != 0x5CC475)
			{
				int pushAddr = *(DWORD*)(i - 7);
				printf("1");

				__asm
				{
					PUSH pushAddr
						CALL GetFileName
						ADD ESP, 0x04
				}

				printf("2");

				HMODULE fileHandle = GetModuleHandleA(LoadFileName);

				printf("file %d", fileHandle);

				if (fileHandle != 0)
				{
					//FreeLibrary(fileHandle);
					//remove(LoadFileName);
				}

				printf("4");

				MessageBox(0, "Foi detectada uma modificação na estrutura do executável.\nO uso de programas ilegais é terminantemente proibido!\nUm relatório foi enviado ao servidor com detalhes do problema.\n\nCódigo do erro: 0xC029\nEntre em contato com o suporte para mais informações", "Game Protection", MB_ICONERROR | MB_OK);
				exit(1);
			}
		}
	}
}

int Protect::Explosao()
{
	if (*(int*)0x45CDEF != 2504821094)
		return 3;

	return 0;
}

int Protect::SMO()
{
	if (*(int*)0x49A659 != 870909310 ||
		*(int*)0x45C655 != 956301315)
		return 4;

	return 0;
}

int Protect::Unk()
{
	if (*(int*)0x05374D1 != 621561227 ||
		*(int*)0x05373E9 != 2298757822 ||
		*(int*)0x05375FD != 21529615)
		return 5;

	return 0;
}

int Protect::Wall()
{
	if (*(int*)0x0467CF8 != 177898767 ||
		*(int*)0x0467D0C != 176588047 ||
		*(int*)0x05029DE != 157517071 ||
		*(int*)0x05029F2 != 156206351)
		return 6;

	return 0;
}

int Protect::SkillRange()
{
	if (*(int*)0x970968 != 0 ||
		*(int*)(0x970944) != 13)
		return 7;

	return 0;
}

int Protect::CheckAddress()
{
	if (*(int*)0x0502887 != 1000 ||
		*(int*)0x04612E3 != 1000 ||
		*(int*)0x054B05C != 1166747506 ||
		*(int*)0x0483DA9 != 200 ||
		*(int*)0x054B08E != 1300981106 ||
		*(int*)0x049AE64 != 2508937077 ||
		*(int*)0x05189BB != 1000 ||
		*(int*)0x046043E != 1000 ||
		*(int*)0x0463E60 != 1000 ||
		*(int*)0x045C4B2 != 0 ||
		*(int*)0x045C4E0 != 1 ||
		*(int*)0x045FCD5 != 0 ||
		*(int*)0x045FD03 != 1 ||
		*(int*)0x0467365 != 0 ||
		*(int*)0x0467394 != 1 ||
		*(int*)0x046E002 != 0 ||
		*(int*)0x046E022 != 1 ||
		*(int*)0x049B052 != 0 ||
		*(int*)0x049B096 != 1 ||
		*(int*)0x049B8CB != 0 ||
		*(int*)0x049B8F9 != 1 ||
		*(int*)0x0502859 != 0 ||
		*(int*)0x0502879 != 1 ||
		*(int*)0x051898D != 0 ||
		*(int*)0x05189AC != 1 ||
		*(int*)0x45CDEF != 2504821094 ||
		*(int*)0x49A659 != 870909310 ||
		*(int*)0x45C655 != 956301315 ||
		*(int*)0x05374D1 != 621561227 ||
		*(int*)0x05373E9 != 2298757822 ||
		*(int*)0x05375FD != 21529615 ||
		*(int*)0x0467CF8 != 177898767 ||
		*(int*)0x0467D0C != 176588047 ||
		*(int*)0x05029DE != 157517071 ||
		*(int*)0x05029F2 != 156206351 ||
		*(int*)0x970968 != 0 ||
		*(int*)(0x970944) != 13)
		return 8;

	return 0;
}

int Protect::CheckTitle()
{
	static const LPCTSTR Names[] =
	{
		"Cheat Engine 5.0",
		"Cheat Engine 5.1",
		"Cheat Engine 5.1.1",
		"Cheat Engine 5.3",
		"Cheat Engine 5.2",
		"Cheat Engine 5.4",
		"Cheat Engine 5.5",
		"Cheat Engine 5.6.1",
		"Cheat Engine 6.0",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Cheat Engine 6.5",
		"Cheat Engine",
		"WPE PRO",
		"WPePro 0.9a",
		"WPePro 1.3"
		"wSyck",
		"HACK",
		"hack",
		"inject",
		"WSYCK",
		"DropList",
		"ZoT",
		"Cheat Engine 5.0",
		"Cheat Engine",
		"WPE",
		"WPe",
		"WPePro",
		"wSyck",
		"HACK",
		"hack",
		"inject",
		"WSYCK",
		"DropList",
		"Drop",
		"DROPLIST",
		"INJECT",
		"wall",
		"speedatk",
		"fastkill",
		"move",
		"bot",
		"BOT",
		"Bot",
		"ZoT",
		"zot",
		"ZOT",
		"Cheat Engine 5.0",
		"Cheat Engine 5.1",
		"Cheat Engine 5.1.1",
		"Cheat Engine 5.2",
		"Cheat Engine 5.3",
		"Cheat Engine 5.4",
		"Cheat Engine 5.5",
		"Cheat Engine 5.6",
		"Cheat Engine 5.6.1",
		"Cheat Engine 6.0",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Cheat Engine 6.5",
		"Cheat Engine 7.0",
		"Cheat Engine 7.1",
		"Cheat Engine",
		"WPE PRO",
		"WPePro 0.9a",
		"WPePro 1.3",
		"JPprojectorDll",
		"dllinjector",
		"SpyHunter",
		"SpyHunter product.",
		"SpyHunter product",
		"WYDfak",
		"WYDf4k",
		"WYDFAK",
		"error",
		"sucesso",
		"sucess",
		"Error",
		"Sucess",
		"Sucesso",
		"DLL ",
		"dll injector",
		"Confirmation",
		"Cheat Engine 6.7",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Select a DLL file",
		"Select a DLL File"
	};

	for (size_t i = 0; i < 92; i++)
	{
		if (!Titles(Names[i]))
			return 9;
	}

	return 0;
}

int Protect::CheckInjection()
{
	if (GetModuleHandle("speedhack.dll") ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed_hack.dll")) ||
		(GetModuleHandle("hack_speed.dll")) ||
		(GetModuleHandle("hack-speed.dll")) ||
		(GetModuleHandle("hackspeed.dll")) ||
		(GetModuleHandle("hack.dll")) ||
		(GetModuleHandle("wpepro.dll")) ||
		(GetModuleHandle("Cr4ck3r.dll")) ||
		(GetModuleHandle("wpeprospy.dll")) ||
		(GetModuleHandle("engine.dll")) ||
		(GetModuleHandle("CheatEngine.dll")) ||
		(GetModuleHandle("c.e.dll")) ||
		(GetModuleHandle("cheat.dll")) ||
		(GetModuleHandle("mukilin.dll")) ||
		(GetModuleHandle("Whook.dll")) ||
		(GetModuleHandle("whook7556.dll")) ||
		(GetModuleHandle("hook.dll")) ||
		(GetModuleHandle("wHook.dll")) ||
		(GetModuleHandle("Hook756.dll")) ||
		(GetModuleHandle("WHOOK.dll")) ||
		(GetModuleHandle("whook756.dll")) ||
		(GetModuleHandle("w.dll")) ||
		(GetModuleHandle("k.dll")) ||
		(GetModuleHandle("oo.dll")) ||
		(GetModuleHandle("ok.dll")) ||
		(GetModuleHandle("wook.dll")) ||
		(GetModuleHandle("whook.dll"))
		)
		return 9;

	return 0;
}

int Protect::NomeJanela()
{
	for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
	{
		if (!IsWindowVisible(hwnd))
			continue;

		int length = GetWindowTextLength(hwnd);
		if (length == 0)
			continue;

		char* title = new char[length + 1];
		GetWindowText(hwnd, title, length + 1);

		if (title == "Program Manager")
			continue;

		string Titulo = (string)title;

		static const string Names[] =
		{ 
		"Cheat Engine 5.0",
		"Cheat Engine 5.1",
		"Cheat Engine 5.1.1",
		"Cheat Engine 5.3",
		"Cheat Engine 5.2",
		"Cheat Engine 5.4",
		"Cheat Engine 5.5",
		"Cheat Engine 5.6.1",
		"Cheat Engine 6.0",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Cheat Engine 6.5",
		"Cheat Engine 7.0",
		"Cheat Engine",
		"WPE PRO",
		"WPePro 0.9a",
		"WPePro 1.3"
		"wSyck",
		"HACK",
		"hack",
		"inject",
		"WSYCK",
		"DropList",
		"ZoT",
		"Cheat Engine 5.0",
		"Cheat Engine",
		"WPE",
		"WPe",
		"WPePro",
		"wSyck",
		"HACK",
		"hack",
		"inject",
		"WSYCK",
		"DropList",
		"Drop",
		"DROPLIST",
		"INJECT",
		"wall",
		"speedatk",
		"fastkill",
		"move",
		"bot",
		"BOT",
		"Bot",
		"ZoT",
		"zot",
		"ZOT",
		"Cheat Engine 5.0",
		"Cheat Engine 5.1",
		"Cheat Engine 5.1.1",
		"Cheat Engine 5.2",
		"Cheat Engine 5.3",
		"Cheat Engine 5.4",
		"Cheat Engine 5.5",
		"Cheat Engine 5.6",
		"Cheat Engine 5.6.1",
		"Cheat Engine 6.0",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Cheat Engine 6.5",
		"Cheat Engine 7.0",
		"Cheat Engine",
		"WPE PRO",
		"WPePro 0.9a",
		"WPePro 1.3",
		"JPprojectorDll",
		"dllinjector",
		"SpyHunter",
		"SpyHunter product.",
		"SpyHunter product",
		"WYDfak",
		"WYDf4k",
		"WYDFAK",
		"error",
		"sucesso",
		"sucess",
		"Error",
		"Sucess",
		"Sucesso",
		"DLL ",
		"dll injector",
		"Confirmation",
		"Cheat Engine 6.7",
		"Cheat Engine 6.1",
		"Cheat Engine 6.2",
		"Cheat Engine 6.3",
		"Cheat Engine 6.4",
		"Select a DLL file",
		"Select a DLL File"
		};

		printf_s("Name: %s \n", Titulo.c_str());

		for (auto i = 0; i < 24; i++)
			if (strstr(Titulo.c_str(), Names[i].c_str()))
			{
				printf("%s %s \n", Names[i].c_str(), Titulo.c_str());
				return 9;
			}
	}
	return 0;
}

bool Protect::Titles(LPCTSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL, WindowTitle);
	if (WinTitle > 0)
		return false;

	return true;
}

int Protect::Validar()
{
	int speed = Speed();
	int range = Range();
	int explosao = Explosao();
	int smo = SMO();
	int unk = Unk();
	int wall = Wall();
	int skillrange = SkillRange();
	int address = CheckAddress();
	int programs = CheckTitle();
	int dlls = CheckInjection();
	int janela = NomeJanela();

	printf("%d", janela);

	if (speed > 0)
		return speed;
	else if (range > 0)
		return range;
	else if (explosao > 0)
		return explosao;
	else if (smo > 0)
		return smo;
	else if (unk > 0)
		return unk;
	else if (wall > 0)
		return wall;
	else if (skillrange > 0)
		return skillrange;
	else if (address > 0)
		return address;
	else if (programs > 0)
		return programs;
	else if (dlls > 0)
		return dlls;
	else if (janela > 0)
		return janela;

	return 0;
}