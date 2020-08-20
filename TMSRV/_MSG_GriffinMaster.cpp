#include "stdafx.h"

bool Exec_MSG_GriffinMaster(int conn, char* pMsg)
{
	MSG_GriffinMaster* m = (MSG_GriffinMaster*)pMsg;

	if (m->MessageType == 1)
	{
		SendClientMessage(conn, "Obrigado por viajar comigo!");
		return false;
	}

	switch (m->WarpID)
	{
	case 0:
		DoTeleport(conn, 2112, 2051,0);
		break;

	case 1:
		DoTeleport(conn, 2372, 2099,0);
		break;

	case 2:
		DoTeleport(conn, 2220, 1714,0);
		break;

	case 3:
		DoTeleport(conn, 2365, 2249,0);
		break;

	case 4:
		DoTeleport(conn, 1826, 1771,0);
		break;
	}

	return false;
}
