#include "stdafx.h"
#include "HookImpl.h"
#include "Functions.h"
#include "ProcessClientMessage.h"

// Envia para o Client e DBServer

bool SendPacketControl(char* NewMsg, MSG_STANDARD* OldMsg, int conn)
{
	// Para zerar um packet basta setar retn como true, 
	// O hook se encarregará do resto

	bool ret = false;
	 

	return ret;
}

int HookImpl::HKD_AddMessage(int Socket, MSG_STANDARD* OldMsg, int MsgSize)
{
	int ret = 0;
	int conn = Func::GetUserFromSocket(*(unsigned short*)Socket);

	char* NewMsg = (char*)malloc(MsgSize);

	if (NewMsg == NULL)
		return 0;

	memcpy(NewMsg, OldMsg, MsgSize);

	// Compara o size do pacote no header e passado por parametro
	if (*(unsigned short*)NewMsg != (unsigned short)MsgSize)
	{
		*(unsigned short*)NewMsg = (unsigned short)MsgSize;
	}

	// Faz as modificações necessárias no pacote
	bool clear = SendPacketControl(NewMsg, OldMsg, conn);

	if (clear)
		memset(NewMsg, 0x0, MsgSize);

	// Chama a função original
	__asm
	{
		PUSH DWORD PTR SS : [MsgSize]
		PUSH DWORD PTR SS : [NewMsg]
		MOV ECX, Socket
		//PUSH ECX
		//CALL HookImpl::AddMessage
		CALL _AddMessage

		MOV ret, EAX
	}

	free(NewMsg);

	return ret;
}