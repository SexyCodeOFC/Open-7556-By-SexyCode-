#include "stdafx.h"
#include "HookImpl.h"
#include "Functions.h"
#include "ProcessClientMessage.h"

// Recebe do Client e DBServer

bool RecvPacketControl(MSG_STANDARD* pMsg, int clientId)
{
	// Para zerar um packet basta setar retn como true, 
	// O hook se encarregará do resto

	bool retn = false;
	 
	return retn;
}

BYTE* HookImpl::HKD_ReadMessage(int instModule, int* unkParam1, int* unkParam2)
{
	BYTE* packetBuffer = NULL;

	int clientId = Func::GetUserFromSocket(*(WORD*)instModule);

	// Chama função original
	__asm
	{
		PUSH DWORD PTR SS : [unkParam2]
		PUSH DWORD PTR SS : [unkParam1]
		MOV ECX, instModule
		//PUSH ECX
		CALL _ReadMessage
		//CALL HookImpl::ReadMessage

		MOV packetBuffer, EAX
	}

	if (!packetBuffer)
		return packetBuffer;

	// Faz as modificações necessárias no pacote
	bool clear = RecvPacketControl((MSG_STANDARD*)packetBuffer, clientId);

	if (clear)
		memset(packetBuffer, 0x0, *(WORD*)packetBuffer);

	return packetBuffer;
}