#include "stdafx.h"
#include "TMSRV.h"

BOOL WINAPI DllMain(
	_In_  HINSTANCE hinstDLL,
	_In_  DWORD fdwReason,
	_In_  LPVOID lpvReserved
	)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		if (lpvReserved == nullptr) // Dynamic Load
		{
			return TMSRV::instance().initialize() ? TRUE : []() {
				MessageBox(0, "Não foi possível carregar a Dll", "Erro: TMSRV.dll", MB_OK);
				return FALSE;
			}();
		}
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		if (lpvReserved != nullptr) // Process Terminating
		{
			TMSRV::instance().cleanup();
			FreeLibrary(hinstDLL);
			return TRUE;
		}
	}
	return FALSE;
}