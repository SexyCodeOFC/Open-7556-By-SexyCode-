#include "stdafx.h"

bool Exec_MSG_AcceptParty(int conn, char* pMsg)
{
	MSG_AcceptParty* m = (MSG_AcceptParty*)pMsg;

	if (m->LeaderID != pUserData[conn].Ingame.MSG.SendReqParty.LastReqParty)
	{
		Log("PartyHack detected", pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}

	return true;
}