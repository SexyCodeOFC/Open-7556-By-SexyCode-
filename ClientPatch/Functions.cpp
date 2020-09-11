#include "stdafx.h"
#include "Functions.h"

char* Func::stringFormat(const char* str, ...)
{
	static char buffer[1024] = { 4, };          //[1024] = { 4, };  [512] = { 0, };   
	va_list va;
	va_start(va, str);
	vsprintf_s(buffer, str, va);
	va_end(va);
	return buffer;
}



char* Func::GetSerialHD()
{
	UINT DiskDriveNumber = 0;
	CString Serial_Number;
	DWORD dwResult = GetPhysicalDriveSerialNumber(DiskDriveNumber, Serial_Number);
	CString strReport;
	if (NO_ERROR == dwResult)
	{
	}
	else
		exit(1);

	char* s = stringFormat("%s", Serial_Number);
	char* s2 = stringFormat("%s", Serial_Number);

	do
	{
		if (*s2 == ' ' || *s2 == '_')
			continue;

		strcpy(s, s2);
		break;

	} while (*s2++);

	return s;
}

char* Func::GetMacAddress()
{
	UUID uuid;

	UuidCreateSequential(&uuid);

	char macAddress[18];
	memset(macAddress, 0, 18);

	strcpy(macAddress, stringFormat("%02X:%02X:%02X:%02X:%02X:%02X", uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]));

	return macAddress;
}

void Func::SendMessageExp(int color, char* s, ...)
{
	DWORD dwOldProt = 0x40;
	VirtualProtect((void*)0x49B50A, 4, dwOldProt, &dwOldProt);
	*(DWORD*)(0x49B50A + 1) = color;
	static int showmessage_addr = 0x49B497;
	auto dat = *(int*)0x6BDAF0;
	__asm
	{
		PUSH s
		MOV ECX, dat
		CALL showmessage_addr
	}
	*(DWORD*)(0x49B50A + 1) = 0xFFFFAAAA;
	VirtualProtect((void*)0x49B50A, 4, dwOldProt, &dwOldProt);
}

void Func::Change_ChatColor(int color)
{
	DWORD dwOldProt = 0x40;
	VirtualProtect((void*)0x004A571C, 4, dwOldProt, &dwOldProt);
	*(DWORD*)0x004A571C = color;
	VirtualProtect((void*)0x004A571C, 4, dwOldProt, &dwOldProt);
}

//char msg[256];

void Func::Shown(int color, const char* str, ...)
{
	char msg[4096];    // char msg[4096];  (crasha=char msg[256]);
	int32_t _ecx_1 = *(int32_t*)(*(int32_t*)(0x006BDAF0) + 0x27AB0);
	int32_t _addr_call_1 = addr_client_chat_1;
	int32_t _addr_call_2 = addr_client_chat_2;
	int32_t	_addr_call_3 = addr_client_chat_3;

	va_list pArgList;
	va_start(pArgList, str);
	vsprintf(msg, str, pArgList);
	va_end(pArgList);
	if (color != -1)
	{
		__asm
		{
			push 0xE54
			call _addr_call_1
			add esp, 4
			cmp eax, 0
			je __end
			mov ecx, eax
			push 0
			push 1
			push 0x77777777
			push 0
			push 0x41800000
			push 0x43960000
			push 0
			push 0
			push color
			lea eax, msg
			push eax
			call _addr_call_2
			push eax
			mov ecx, _ecx_1
			call _addr_call_3
			__end :
			nop
		}
	}
}

int Func::GetClientID()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x13FA9D4]
		ADD ECX, 0xDFC
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [ECX]
	}
}

short Func::GetPosClientX()
{
	return (short)(*(float*)((*(int*)((char*)(*(int**)0x6BDAF0) + 76)) + 40));
}

short Func::GetPosClientY()
{
	return (short)(*(float*)((*(int*)((char*)(*(int**)0x6BDAF0) + 76)) + 44));
}

STRUCT_MOB Func::GetChar()
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [0x13FA9D4]
		ADD EAX, 0x6EC
	}
}

void Func::ShowClientMessage(int delay, char* msg)
{
	static int msg_addr = 0x40409D;
	__asm
	{
		PUSH delay
		PUSH msg
		MOV ECX, DWORD PTR SS : [EBP - 0x788]
		MOV ECX, DWORD PTR DS : [ECX + 0x84]
		CALL msg_addr

		PUSH 0
		PUSH 1
		MOV EDX, DWORD PTR SS : [EBP - 0x788]
		MOV ECX, DWORD PTR DS : [EDX + 0x84]
		MOV EAX, DWORD PTR SS : [EBP - 0x788]
		MOV EDX, DWORD PTR DS : [EAX + 0x84]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL DWORD PTR DS : [EAX + 0x88]
		MOV EAX, 1
	}
}
 

void Func::AgruparItem(int slot, int index)
{
	auto mob = &GetChar();
	uint16_t slotItem = -1;

	for (size_t i = 0; i < 60; i++)
	{
		if (mob->Carry[i].sIndex != index) continue;

		for (size_t a = 0; a < 3; a++)
		{
			if (mob->Carry[i].stEffect[a].cEffect == 61 && mob->Carry[i].stEffect[a].cValue == 120) continue;

			slotItem = i;
			break;
		}
		if (slotItem != -1) break;
	}

	if (slot == -1) return;

	struct
	{
		MSG_STANDARD Header;
		BYTE DstType;
		BYTE DstSlot;
		BYTE SrcType;
		BYTE SrcSlot;
		int Unknown;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Header.Size = sizeof(Packet);
	Packet.Header.Type = 0x376;
	Packet.Header.ID = GetClientID();
	Packet.DstType = 1;
	Packet.DstSlot = slotItem;
	Packet.SrcType = 1;
	Packet.SrcSlot = slot;

	SendPacketDirect((char*)&Packet, sizeof(Packet));
}
 

bool MacroPega = false; // Desativado Por Padrão
int WaterScrollPosition[3][10][2] = {
	{//N
		{ 1121, 3553 }, //LV1
		{ 1085, 3553 }, //2
		{ 1049, 3553 }, //3
		{ 1049, 3517 }, //4
		{ 1050, 3481 }, //5
		{ 1086, 3481 }, //6
		{ 1122, 3481 }, //7
		{ 1122, 3517 }, //8
		{ 1086, 3518 } //9
	},
	{//M
		{ 1249, 3681 }, //LV1
		{ 1213, 3681 }, //2
		{ 1178, 3681 }, //3
		{ 1178, 3645 }, //4
		{ 1178, 3609 }, //5
		{ 1214, 3609 }, //6
		{ 1249, 3609 }, //7
		{ 1249, 3645 }, //8
		{ 1214, 3645 }, //9
	},
	{//A
		{ 1378, 3554 }, //LV1
		{ 1342, 3553 }, //2
		{ 1306, 3553 }, //3
		{ 1306, 3517 }, //4
		{ 1306, 3481 }, //5
		{ 1342, 3481 }, //6
		{ 1378, 3481 }, //7
		{ 1378, 3517 }, //8
		{ 1342, 3517 } //9
	}
};


void DLL_UseItem(int slot) { // Usa um item consumível
	p373h sendData;
	memset(&sendData, 0x0, sizeof(p373h));
	sendData.Header.Size = sizeof(p373h);
	sendData.Header.Type = 0x373;
	sendData.Header.ID = GetClientID();
	sendData.Src.Type = sendData.Dst.Type = 1;
	sendData.Dst.Slot = sendData.Src.Slot = slot;
	sendData.Position.X = GetCPosX();
	sendData.Position.Y = GetCPosY();
	SendPacket((char*)&sendData, sizeof(p373h));
}

void WINAPI DllThreadMacro() {
	while (true) {
		Sleep(1000);
		if (MacroPega) {
			//Func::ShowExpMessage(0xFFFFAAAA, Func::stringFormat("Macro Perga ON"));
			auto mob = &GetChar();

			int usarPerga = 0;
			int slotsInv = 30;
			if (mob->Carry[60].sIndex == 3467) slotsInv += 15;
			if (mob->Carry[61].sIndex == 3467) slotsInv += 15;

			int salaFounded = false;
			int tipoPerga = -1;
			int SalaPerga = -1;
			int pergaItem = 0;

			// Procurar Tipo de Perga / Sala:
			for (tipoPerga = 0; tipoPerga < 3; tipoPerga++) {
				for (SalaPerga = 0; SalaPerga <= 8; SalaPerga++)
				{
					if (GetCPosX() >= WaterScrollPosition[tipoPerga][SalaPerga][0] - 15
						&& GetCPosX() <= WaterScrollPosition[tipoPerga][SalaPerga][0] + 15
						&& GetCPosY() >= WaterScrollPosition[tipoPerga][SalaPerga][1] - 15
						&& GetCPosY() <= WaterScrollPosition[tipoPerga][SalaPerga][1] + 15)
					{
						salaFounded = true;

						break;
					}
				}
				if (salaFounded) break;
			}
			if (salaFounded) {
				if (tipoPerga == 0) { pergaItem = SalaPerga + 3173; } // Agua N
				else if (tipoPerga == 1) { pergaItem = SalaPerga + 777; } // Agua M
				else if (tipoPerga == 2) { pergaItem = SalaPerga + 3182; } // Agua A

				if (SalaPerga == 8) { Sleep(1000); } // Boss
				else if (pergaItem <= 0) { Sleep(1000); }
				else {
					int pergaSlotItem = -1;
					for (int j = 0; j < slotsInv; ++j) {
						if (mob->Carry[j].sIndex == pergaItem + 1)
							pergaSlotItem = j;
					}

					if (pergaSlotItem >= 0) {
						DLL_UseItem(pergaSlotItem);
						Sleep(1000);
					}
					else { Sleep(1000); } // Está na sala mas ainda não chegou o item.
				}
			}
			else {
				short posX = GetCPosX();
				short posY = GetCPosY();
				if (posX == NULL || posY == NULL) MacroPega = false;
				else {
					if (GetCPosX() >= 1965 - 10 && GetCPosX() <= 1965 + 10 && GetCPosY() >= 1770 - 10 && GetCPosY() <= 1770 + 10) {
						int pergaSlotItem = -1;
						for (int k = 0; k < slotsInv; ++k) {
							if (mob->Carry[k].sIndex == 3173 || mob->Carry[k].sIndex == 777 || mob->Carry[k].sIndex == 3182)
								pergaSlotItem = k;
						}
						if (pergaSlotItem >= 0) {
							Sleep(5000);
							DLL_UseItem(pergaSlotItem);
							Sleep(1000);
						}
						else {
							MacroPega = false;
							Func::SendMessageExp(Red, "Macro de Pergaminho desativado.");
						}
					}
					else {
						MacroPega = false;
						Func::SendMessageExp(Red, "Macro de Pergaminho desativado.");
					}
				}
			}
		}
	}
}