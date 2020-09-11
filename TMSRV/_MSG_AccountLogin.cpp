#include "stdafx.h"

bool Exec_MSG_AccountLogin(int conn, char* pMsg)
{
	MSG_AccountLogin* m = (MSG_AccountLogin*)pMsg;


	m->AccountPassword[11] = '\0';
	m->AccountName[11] = '\0';
	m->MacAddress[17] = '\0';

	auto userData = &pUserData[conn];
	char Mac[18];
	memset(Mac, 0, sizeof(Mac));
	sprintf(Mac, "%s", m->MacAddress);

	if (strlen(Mac) < 10)
	{
		SendClientMessage(conn, "Impossível conectar. Tente novamente mais tarde.");
		return false;
	}
	try
	{
		Func::LoadAccount(conn, m->AccountName);

		memset(pUserData[conn].AccountInfo.MacAddress, 0, 18);
		strncpy(pUserData[conn].AccountInfo.MacAddress, Mac, 18);
		strncpy(pUserData[conn].AccountInfo.LastIP, m->IP, 16);

		Func::SaveAccount(conn, m->AccountName);
	}
	catch (...)
	{
		Log("err, insert MacAddress on account", pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}

	if (m->CheckShield != CHECK_SHIELD)
	{
		SendClientMessage(conn, "Baixe as atualizações novamente pelo site ou launcher.");
		return false;
	}

	Func::LoadAccount(conn, m->AccountName);

	int macBan = Func::ReadMacList(pUserData[conn].AccountInfo.MacAddress);

	if (macBan == TRUE)
	{
		SendClientMessage(conn, "Você foi impedido de acessar esse servidor.");
		return false;
	}

	if (pUserData[conn].AccountInfo.Ban.Permanent == TRUE)
	{
		SendClientMessage(conn, "Você foi banido permanentemente do servidor.");
		return false;
	}

	if (pUserData[conn].AccountInfo.Ban.TimeStamp != 0)
	{
		time_t rawtime;
		time(&rawtime);

		if (pUserData[conn].AccountInfo.Ban.TimeStamp <= rawtime)
		{
			pUserData[conn].AccountInfo.Ban.TimeStamp = 0;
			Func::SaveAccount(conn, m->AccountName);
		}
		else
		{
			tm* timeinfo = localtime(&pUserData[conn].AccountInfo.Ban.TimeStamp);
			char temp[256];
			strftime(temp, 256, "Sua conta foi banida, retorne em %d/%m/%Y às %H:%M:%S", timeinfo);
			SendClientMessage(conn, temp);
			return false;
		}
	} 

	return true;
}
