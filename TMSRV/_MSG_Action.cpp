#include "stdafx.h"
#include "HookImpl.h"

bool Exec_MSG_Action(int conn, char* pMsg)
{
	MSG_Action_7556* m = (MSG_Action_7556*)pMsg;

	if (pUserData[conn].Ingame.MSG.Action.Warning >= 1)
	{
		Log("SpeedMove hack detected", pUser[conn].AccountName, pUser[conn].IP);
		CloseUser(conn);
		return false;
	}

	pUserData[conn].Ingame.MSG.UseItem.UseJewelBag = FALSE;
	return true; 

	if (m->Size == 28) //Check Hack Use
	{
		auto Packet = (p36Ch*)pMsg;
		if (Packet->Origin.X == 255)
		{
			if (Packet->Type >= 1 && Packet->Type <= 9)
			{
				CloseUser(conn);
			}

		}

		else if (Packet->Origin.X == 300)
		{
			pUserData[conn].Ingame.WarningPacketSecurity = 0;
			pUserData[conn].Ingame.CountDownPacketSecurity = 20; // Send information that client is Okay.
			pUserData[conn].Ingame.ClientOK = TRUE;
		}

		return false;
	}
}

void HookImpl::ActionWarning(int conn)
{
	pUserData[conn].Ingame.MSG.Action.Warning++;
}
