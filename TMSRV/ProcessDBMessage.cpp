#include "stdafx.h"
#include "HookImpl.h"

void HookImpl::ProcessDBMessage(char* Msg)
{
	MSG_STANDARD* std = (MSG_STANDARD*)Msg;
	
	int conn = std->ID; 


	//printf("DBMessage RECV=> Packet: 0x%X Size: %d ClientId %d pUserSlot %d Name %s \n", Header->PacketId, Header->Size, Header->ClientId, user->Slot, user->AccountName);
}