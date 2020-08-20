#ifndef __HOOK_H__
#define __HOOK_H__

#include <singleton.h>
#include <Windows.h>
#include <new>
#include <string>

enum class eHookType
{
	// Inconditional Jump 
	JMP = 1, // 0xE9

	// Call
	CALL, // 0xE8

	JE, // 0xF 0x84
	JZ,
	JNZ, // 0xF 0x85
	JNE,

	// Signed Jumps
	JL, // 0xF 0x8C
	JGE, // 0xF 0x8D
	JLE, // 0xF 0x8E
	JG, // 0xF 0x8F

	// Unsigned Jumps
	JB, // 0xF 0x82
	JNB, // 0xF 0x83
	JBE, // 0xF 0x86
	JA // 0xF 0x87
};

class HookMgr : public Singleton<HookMgr>
{
public:
	void setHook(const eHookType hType, unsigned int hSourceAddress, unsigned int hDestAddress,  unsigned int hNopSize = 0)
	{
		DWORD protect = 0;

		auto instructionSize = [](const eHookType type)
		{
			unsigned int size = 0;
			switch (type)
			{
			case eHookType::JMP:
			case eHookType::CALL:
				size = 5;
				break;
			default:
				size = 6;
				break;
			}
			return size;
		}(hType);

		auto instruction = new (std::nothrow) unsigned char[instructionSize + hNopSize];

		if (instruction == nullptr)
			return;

		auto distance = ((hDestAddress - hSourceAddress) - instructionSize);
		
		unsigned int distanceOffset = 0;

		if (hType == eHookType::JMP || hType == eHookType::CALL)
			distanceOffset = 1;
		else
			distanceOffset = 2;

		switch (hType)
		{
		case eHookType::JMP:
			instruction[0] = 0xE9;
			break;
		case eHookType::CALL:
			instruction[0] = 0xE8;
			break;
		case eHookType::JE:
		case eHookType::JZ:
			instruction[0] = 0x0F;
			instruction[1] = 0x84;
			break;
		case eHookType::JNZ:
		case eHookType::JNE:
			instruction[0] = 0x0F;
			instruction[1] = 0x85;
			break;
		case eHookType::JL:
			instruction[0] = 0x0F;
			instruction[1] = 0x8C;
			break;
		case eHookType::JGE:
			instruction[0] = 0x0F;
			instruction[1] = 0x8D;
			break;
		case eHookType::JLE:
			instruction[0] = 0x0F;
			instruction[1] = 0x8E;
			break;
		case eHookType::JG:
			instruction[0] = 0x0F;
			instruction[1] = 0x8F;
			break;
		case eHookType::JB:
			instruction[0] = 0x0F;
			instruction[1] = 0x82;
			break;
		case eHookType::JNB:
			instruction[0] = 0x0F;
			instruction[1] = 0x83;
			break;
		case eHookType::JBE:
			instruction[0] = 0x0F;
			instruction[1] = 0x86;
			break;
		case eHookType::JA:
			instruction[0] = 0x0F;
			instruction[1] = 0x87;
			break;
		}

		*(unsigned int*)&instruction[distanceOffset] = distance;

		if(hNopSize > 0)
		{
			for (unsigned int i = 0; i < hNopSize; i++)
				instruction[i + instructionSize] = 0x90;
		}

		if (VirtualProtect(reinterpret_cast<void*>(hSourceAddress), instructionSize + hNopSize, PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		memcpy(reinterpret_cast<void*>(hSourceAddress), instruction, instructionSize + hNopSize);

		if (VirtualProtect(reinterpret_cast<void*>(hSourceAddress), instructionSize + hNopSize, protect, &protect) == 0)
			return;
		
		FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<const void*>(hSourceAddress),
			instructionSize + hNopSize);

		delete[] instruction;
	}

	template<typename I>
	void setValue(unsigned int hSourceAddress, I hValue)
	{
		DWORD protect = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), sizeof(I), PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		*(I*)hSourceAddress = hValue;

		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), sizeof(I), protect, &protect) == 0)
			return;
	}
	template<typename I>
	void setValue(unsigned int hSourceAddress, I hValue, unsigned int hSize)
	{
		DWORD protect = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), hSize, PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		*(I*)hSourceAddress = hValue;

		if(VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), hSize, protect, &protect) == 0)
			return;
	}

	void fillWithNop(unsigned int hAddress, unsigned int hNopCount)
	{
		DWORD p = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hAddress), hNopCount, PAGE_EXECUTE_READWRITE, &p) == 0)
			return;

		for (unsigned int i = 0; i < hNopCount; i++)
			*(unsigned char*)(hAddress + i) = 0x90;

		if (VirtualProtect(reinterpret_cast<LPVOID>(hAddress), hNopCount, p, &p) == 0)
			return;
	}
	unsigned int getAddress(const void* ptr)
	{
		return reinterpret_cast<unsigned int>(ptr);
	}
protected:
	friend class Singleton<HookMgr>;
	HookMgr() {}
	virtual ~HookMgr() {}
	HookMgr(const HookMgr&) = delete;
	HookMgr& operator=(const HookMgr&) = delete;
	
};

#endif // !__HOOK_H__
