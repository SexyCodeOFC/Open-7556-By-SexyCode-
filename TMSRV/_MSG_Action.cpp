#include "stdafx.h"
#include "HookImpl.h"

bool Exec_MSG_Action(int conn, char* pMsg)
{
	MSG_Action_7556* m = (MSG_Action_7556*)pMsg;

	if (pUserData[conn].Ingame.MSG.Action.Warning >= 1)
	{
		Log("SpeedMove hack detected", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	pUserData[conn].Ingame.MSG.UseItem.UseJewelBag = FALSE;
	return true; 

}

void HookImpl::ActionWarning(int conn)
{
	pUserData[conn].Ingame.MSG.Action.Warning++;
}
