#include "stdafx.h"
#include "HookPatch.h"
#include "HookImpl.h"
#include <hook.h>

static int jmp_addr;
static int reg_aux;

bool HookPatch::initialize()
{
	try
	{
		auto& hooks = HookMgr::instance();

		//hooks.setHook(eHookType::JMP, 0x42B12C, hooks.getAddress(&HookPatch::NKD_MainWndProc_ReadMessageUser), 2);
		//hooks.setHook(eHookType::JMP, 0x4011EF, hooks.getAddress(&HookPatch::NKD_ReadMessage));
		//hooks.setHook(eHookType::JMP, 0x4011DB, hooks.getAddress(&HookPatch::NKD_AddMessage)); 

		return true;
	}
	catch (...)
	{
		return false;
	}
}
 
__declspec(naked) void HookPatch::NKD_AddMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HookImpl::HKD_AddMessage
	}
}

__declspec(naked) void HookPatch::NKD_ReadMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HookImpl::HKD_ReadMessage
	}
}