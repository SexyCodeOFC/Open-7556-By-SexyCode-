#include "stdafx.h" 

bool  Exec_MSG_Alquimista_Real(int conn, char* pMsg)
{
	auto Packet = (MSG_COMBINE*)pMsg;
	auto User = Func::GetUserFromIndex(conn);

	if (User->Mode != Playing)
		return false;
	 
	auto userData = &pUserData[conn];

	int result = 2;
	for (int i = 0; i < 7; i++)
	{
		if (Packet->Slot[i] == 0xFF)
			result = 1;

		else if (memcmp(&Packet->Item[i], &pMob[conn].MOB.Carry[Packet->Slot[i]], sizeof(STRUCT_ITEM)))
			result = 1;

		else if (Packet->Item[i].sIndex != pMob[conn].MOB.Carry[Packet->Slot[i]].sIndex)
			result = 1;

		else if (Packet->Item[i].sIndex < 0 || Packet->Item[i].sIndex > 6500)
			result = 1;
	}

	if (result == 2)
	{
		if (Packet->Item[0].sIndex == 5409 && Packet->Item[1].sIndex == 5410 && Packet->Item[2].sIndex == 1742) /* Verifica se é a função que busco */
		{
			for (int i = 3; i < 4; i++)
			{
				if (Packet->Item[i].sIndex != 4127)
				{
					 SendClientMessage(conn, "Composição Ínvalida.");
					Func::CloseWindows(conn);
					return false;
				}
			}

			if (userData->CharacterInfo[User->Slot].Especial.CytheraArch == TRUE)
			{
				 SendClientMessage(conn, "Você já completou essa quest.");
				Func::CloseWindows(conn);
				return false;
			}

			auto fragmento_Luar = Func::ReturnAmount(&Packet->Item[0]);
			auto fragmento_Celeste = Func::ReturnAmount(&Packet->Item[1]);



			if (Func::GetPlayerClass(conn) != God)
			{
				 SendClientMessage(conn, "Somente para classes Archs.");
				Func::CloseWindows(conn);
				return false;
			}

			if (pMob[conn].MOB.CurrentScore.Level < 399)
			{
				 SendClientMessage(conn, "Necessário level 400.");
				Func::CloseWindows(conn);
				return false;
			}

			if (fragmento_Luar != 20 || fragmento_Celeste != 20)
			{
				 SendClientMessage(conn, "Traga-me 20 fragmentos Lunar e Celestes.");
				Func::CloseWindows(conn);
				return false;
			}




			for (int i = 0; i < 7; i++)
			{
				Func::ClearItemInventory(conn, Packet->Slot[i]);
			}

			userData->CharacterInfo[User->Slot].Especial.CytheraArch = TRUE;
			Func::SaveAccount(conn, pUser[conn].AccountName);
			SaveUser(conn, 0);

			pMob[conn].MOB.Exp = 2624000000;
			pMob[conn].MOB.CurrentScore.Level = 370;
			pMob[conn].MOB.BaseScore.Level = 370;
			STRUCT_ITEM cythera = { 5411,0,0,0 };

			Func::SendItem2(conn, &cythera);
			CloseUser(conn);

			char msg[4096] = { 0, };
			sprintf_s(msg, 4096, "Char: %s Completou a Quest Cythera Divina e Recebeu a Cytherae ", pMob[conn].MOB.MobName);
			Log(msg, "-system", 0);

			return false;
		}

	}

	if (result == 1)
	{
	 SendClientMessage(conn, "Composição Ínvalida.");
	 Func::CloseWindows(conn);
		return false;
	}

	return true;
}

