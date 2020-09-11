#include "stdafx.h"

bool Exec_MSG_OpenLojinha(int conn, char* pMsg)
{
	MSG_STANDARD* packet = (MSG_STANDARD*)pMsg;
	p397h* p = (p397h*)pMsg;
	auto mobStore = Func::getPlayerLoja({ packet->ID }, { pUserData[conn].Ingame.MacAddress });


	if (mobStore.size() <= 500)
	{
		pUserData[conn].Ingame.autoStore = true;
		time_t now;
		time(&now);
		tm when;
		localtime_s(&when, &now);

		char tmp[256] = { 0, };
		strftime(tmp, 256, "!%d-%m-%y %H:%M:%S Sistema de Auto Venda Ativado.", &when);
		SendClientMessage(conn, tmp);
	}
	return true;
}




bool Exec_MSG_ClosedLojinha(int conn, char* pMsg)
{ 
	auto userData = &pUserData[conn];
	userData->Ingame.autoStore = false;
	userData->Ingame.PointStore = 0;
	return true;
}

bool Exec_MSG_ActionLojinha(int conn, char* pMsg)
{
	p398h *p = (p398h*)pMsg;
	auto user = Func::GetUserFromIndex(p->Index); // player que vendeu
	auto userData2 = &pUserData[p->Index]; // player que vendeu
	if (p->Index <= NULL || p->Index >= MAX_USER) 

	if (p->Gold <= 99) {
		SendClientMessage(conn, "!Modo demonstração"); 
	}
	/* falta ser testado.
	if (p->Gold >= 100 && p->Gold <= 20000)
	{
		if (pUserData[conn].AccountInfo.Mileage < p->Gold)
		{
			SendClientMessage(conn, "Cash insuficiente");
			return false;
		}

		pUserData[conn].AccountInfo.Mileage -= p->Gold; // cash de quem comprou
		pUserData[conn].AccountInfo.Mileage += p->Gold; // cash de quem vendeu
		pMob[conn].MOB.Coin += p->Gold; // gold do inventario de quem comprou
		pUser[conn].Coin -= p->Gold; // gold do bau de quem vendeu
		SendClientMessage(p->Index, Func::strFmt("!%s comprou o um Item por %d Donate", pMob[conn].MOB.MobName, p->Gold));
	}
	*/
	return true;
}