#include "stdafx.h"
#include "HookPatch.h"
#include <iostream>#include <unistd.h>
#include <fcntl.h>
#include <sstream>

BOOL WINAPI DllMain(
	_In_  HINSTANCE hinstDLL,
	_In_  DWORD fdwReason,
	_In_  LPVOID lpvReserved
	)
{
	//AllocConsole();
	//SetConsoleTitle("GameServer");
	//stdout = *_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_WRONLY), "w");
	//printf("Game Console Iniciado"); //Console para ver packt
 
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		if (lpvReserved == nullptr) // Dynamic Load
		{
			return HookPatch::instance().initialize() ? TRUE : []() {
				MessageBox(0, "Não foi possível carregar a Dll", "Erro: TMSRV.dll", MB_OK);
				return FALSE;
			}();
		}
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		if (lpvReserved != nullptr) // Process Terminating
		{
			FreeLibrary(hinstDLL);
			return TRUE;
		}
	}
	return FALSE;
} 