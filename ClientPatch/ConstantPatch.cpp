#include "stdafx.h"
#include <hook.h>
#include "ConstantPatch.h"
#include "Functions.h"

uint32_t structIcons[] =
{
	0xFFFFFFFF ,0x01,
	0x29 ,0x02,
	0x7C ,0x77,
	0x76 ,0x04,
	0x78 ,0x2C,
	0x33 ,0x2B,
	0x54 ,0x0B,
	0x03 ,0x2D,
	0x47 ,0x05,
	0x2E ,0x4C,
	0x28 ,0x4D,
	0x25 ,0x36,
	0x0D ,0x35,
	0x59 ,0x4B,
	0x5F ,0x66,
	0x7A ,0x55,
	0x2F ,0x60,
	0x7B ,0x7D,
	0x5C ,0x51,
	0x57 ,0x79,
	0x80, 0x81,
	0x82,
	0x83, 0x84,
	0x85, 0x86,
	0x87, 0x88,
	0x89, 0x8A,
	0x8B, 0x8C,
	0x8D, 0x8E,
	0x8F,
};

bool Fixed::setEffectStringBuffer()
{

	DWORD OldProtect;
	VirtualProtect((int*)0x0401000, 0x05CCFFF - 0x0401000, 0x40, &OldProtect);

	auto& hooks = HookMgr::instance();

	//0x5F5550, ElementSize = 0x18, Count = 0x28
	hooks.setValue<uint32_t>(0x44E1FA + 2, hooks.getAddress(&Global::pEffectName[0]));
	hooks.setValue<uint32_t>(0x47DE45 + 2, hooks.getAddress(&Global::pEffectName[0]));
	hooks.setValue<uint32_t>(0x546B6D + 2, hooks.getAddress(&Global::pEffectName[0]));

	hooks.setValue<uint8_t>(0x44E1EC, MAX_EFFECT_NAME);
	hooks.setValue<uint8_t>(0x546B64, MAX_EFFECT_NAME);

	hooks.setValue<uint8_t>(0x47DA37 + 2, MAX_EFFECT_NAME);

	hooks.setValue<unsigned char>(0x4B8BE4, 0xEB);

	//hooks.setValue(0x0046ECE7 + 6, 1);
	//hooks.setValue(0x00547CA6 + 6, 1);
	////hooks.setValue<int>(0x00547D1A, 0);
	//hooks.setValue(0x00547C9C + 6, 0);
	//hooks.setValue(0x00547CB0 + 6, 1);
	//hooks.setValue(0x46ECF7, 0);
	//hooks.setValue(0x46ECE3, 1);
	return true;
}

bool Fixed::setNewResolution()
{
	DWORD OldProtect;
	VirtualProtect((int*)0x0401000, 0x05CCFFF - 0x0401000, 0x40, &OldProtect);

	auto& hooks = HookMgr::instance();

	// Set Width x Height x 32 Bits
	hooks.setValue(0x005475FF + 6, 800);  hooks.setValue(0x00547609 + 6, 600); hooks.setValue(0x00547613 + 6, 32);
	hooks.setValue(0x0054761D + 6, 1024); hooks.setValue(0x00547627 + 6, 768); hooks.setValue(0x00547631 + 6, 32);
	hooks.setValue(0x0054763B + 6, 1280); hooks.setValue(0x00547645 + 6, 720); hooks.setValue(0x0054764F + 6, 32);
	hooks.setValue(0x00547659 + 6, 1280); hooks.setValue(0x00547663 + 6, 800); hooks.setValue(0x0054766D + 6, 32);
	hooks.setValue(0x00547677 + 6, 1280); hooks.setValue(0x00547681 + 6, 960); hooks.setValue(0x0054768B + 6, 32);
	hooks.setValue(0x00547695 + 6, 1280); hooks.setValue(0x0054769F + 6, 1024);
	hooks.setValue(0x005476B3 + 6, 1440); hooks.setValue(0x005476BD + 6, 900);
	hooks.setValue(0x005476D1 + 6, 1600); hooks.setValue(0x005476DB + 6, 900);
	hooks.setValue(0x005476EF + 6, 1600); hooks.setValue(0x005476F9 + 6, 1024);
	hooks.setValue(0x0054770D + 6, 1920); hooks.setValue(0x00547717 + 6, 1080);

	// Set New CMP Widths + FontSize
	hooks.setValue(0x00547FB3 + 3, 800);
	hooks.setValue(0x00547FBC + 6, 12);
	hooks.setValue(0x00547FDB + 3, 1024);
	hooks.setValue(0x00547FE4 + 6, 12);
	hooks.setValue(0x00548000 + 3, 1280);
	hooks.setValue(0x00548009 + 6, 14);
	hooks.setValue(0x00548025 + 3, 1440);
	hooks.setValue(0x0054802E + 6, 18);
	hooks.setValue(0x00548044 + 6, 18);

	return true;
}

bool Fixed::MontariasDano()   //montaria client
{
	static auto MountData = reinterpret_cast<MountTable*>(0x5F52C0);

	MountData->Mounts[3997 - 3980].AttackDmg = 450;
	MountData->Mounts[3995 - 3980].MagicDmg = 55;
	MountData->Mounts[3995 - 3980].MoveSpeed = 6;
	MountData->Mounts[3995 - 3980].ResistAll = 0;
	MountData->Mounts[3995 - 3980].Parry = 0;
	MountData->Mounts[3995 - 3980].unk = 0;

	
	MountData->Mounts[3997 - 3980].AttackDmg = 450;
	MountData->Mounts[3996 - 3980].MagicDmg = 55;
	MountData->Mounts[3996 - 3980].MoveSpeed = 6;
	MountData->Mounts[3996 - 3980].ResistAll = 0;
	MountData->Mounts[3996 - 3980].Parry = 0;
	MountData->Mounts[3996 - 3980].unk = 0;

	
	MountData->Mounts[3997 - 3980].AttackDmg = 450;
	MountData->Mounts[3997 - 3980].MagicDmg = 55;
	MountData->Mounts[3997 - 3980].MoveSpeed = 6;
	MountData->Mounts[3997 - 3980].ResistAll = 0;
	MountData->Mounts[3997 - 3980].Parry = 0;
	MountData->Mounts[3997 - 3980].unk = 0;

	return false;
}

bool Fixed::setNewIconesSkill()
{
	DWORD OldProtect;
	VirtualProtect((int*)0x0401000, 0x05CCFFF - 0x0401000, 0x40, &OldProtect);

	auto& hooks = HookMgr::instance();

	hooks.setValue<char>(0x44E66E, 80);
	hooks.setValue<char>(0x480F88 + 2, 80);
	hooks.setValue<INT32>(0x44E6BE, (uint32_t)structIcons);
	hooks.setValue<INT32>(0x49A805, (uint32_t)structIcons);
	hooks.setValue<INT32>(0x49A842, (uint32_t)structIcons);
	hooks.setValue<INT32>(0x480FCE + 3, (uint32_t)structIcons);

	return true;
}