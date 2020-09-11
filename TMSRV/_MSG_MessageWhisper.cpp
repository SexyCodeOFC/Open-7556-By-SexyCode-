#include "stdafx.h"
#include "ProcessClientMessage.h"
#include "Functions.h"

bool Exec_MSG_MessageWhisper(int conn, char* pMsg)
{
	MSG_DBCNFAccountLogin* sm = (MSG_DBCNFAccountLogin*)pMsg;

	MSG_MessageWhisper* m = (MSG_MessageWhisper*)pMsg; 
	m->MobName[15] = 0;
	m->String[95] = 0;

	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int Clan = pMob[conn].MOB.Clan;

	if (pUser[conn].Mode != USER_PLAY)
		return false;

#pragma region Grupo com Senha
	if (!strcmp(m->MobName, "definirsenha"))
	{
		if (strlen(m->String) > 6)
		{
			SendClientMessage(conn, "Limite máximo de 6 caracteres.");
			return false;
		}

		int pos = -1;

		for (int i = 0; i < 6; i++)
		{
			if (m->String[i] == ' ')
			{
				pos = i;
				break;
			}
		}

		if (strlen(m->String) <= 0 || pos != -1)
		{
			SendClientMessage(conn, "Digite uma senha para seu grupo.");
			return false;
		}

		if (pMob[conn].Leader != 0)
		{
			SendClientMessage(conn, "Você não é lider de um grupo.");
			return false;
		}

		memset(pUserData[conn].Ingame.PartyPassword, 0, sizeof(pUserData[conn].Ingame.PartyPassword));

		strncpy(pUserData[conn].Ingame.PartyPassword, m->String, 6);

		char tmp[128];
		sprintf(tmp, "Senha [%s] foi definida com sucesso!", pUserData[conn].Ingame.PartyPassword);
		SendClientMessage(conn, tmp);

		return false;
	}

	if (!strcmp(m->MobName, "entrar"))
	{
		char TargetName[16];

		memset(TargetName, 0, sizeof(TargetName));

		char Password[7];

		memset(Password, 0, sizeof(Password));

		if (strlen(m->String) <= 0 || strlen(m->String) > 23)
			return false;

		if (sscanf_s(m->String, "%15s %6s", TargetName, _countof(TargetName), Password, _countof(Password)))
		{
			if (strlen(TargetName) <= 0 || strlen(TargetName) > 16)
			{
				SendClientMessage(conn, "Nome inválido.");
				return false;
			}

			if (strlen(Password) <= 0 || strlen(Password) > 6)
			{
				SendClientMessage(conn, "Senha inválida.");
				return false;
			}

			int idx = GetUserByName(TargetName);

			if (pUser[idx].Mode != USER_PLAY)
			{
				SendClientMessage(conn, "Este personagem não está conectado.");
				return false;
			}

			if (pMob[idx].Leader != 0)
			{
				SendClientMessage(conn, "Este personagem não é lider de grupo.");
				return false;
			}

			if (pMob[conn].Leader != 0)
			{
				SendClientMessage(conn, "Você já faz parte de um grupo.");
				return false;
			}

			if (pMob[conn].PartyList[0] != 0)
			{
				SendClientMessage(conn, "Você é lider de um grupo.");
				return false;
			}

			if (strcmp(pUserData[idx].Ingame.PartyPassword, Password) != 0)
			{
				SendClientMessage(conn, "Senha incorreta.");
				return false;
			}

			int c = 0;
			int counter = 0;

			for (c = 0; c < MAX_PARTY; c++)
			{
				if (pMob[idx].PartyList[c])
					counter++;

				if (!counter)
				{
					SendAddParty(idx, idx, 0);
					SendAddParty(conn, conn, 0);
				}
			}

			for (c = 0; c < MAX_PARTY && pMob[idx].PartyList[c]; c++);

			if (c == MAX_PARTY)
			{
				SendClientMessage(conn, "O grupo está cheio.");
				return false;
			}

			GetMobFromIndex(idx)->PartyList[c] = conn;
			GetMobFromIndex(conn)->Leader = idx;

			c++;

			SendAddParty(conn, idx, 0);
			SendAddParty(idx, conn, c);

			for (int m = 0; m < MAX_PARTY; m++)
			{
				int partyconn = GetMobFromIndex(idx)->PartyList[m];

				if (partyconn <= 0 || partyconn >= MAX_MOB)
					continue;

				if (partyconn != conn)
					SendAddParty(conn, partyconn, c);

				SendAddParty(partyconn, conn, m + 1);
			}

			char temp[256];
			sprintf(temp, "!Você entrou no grupo do jogador %s!", GetMobFromIndex(idx)->MOB.MobName);
			SendClientMessage(conn, temp);

			sprintf(temp, "!Jogador %s entrou no seu grupo!", GetMobFromIndex(conn)->MOB.MobName);
			SendClientMessage(idx, temp);

			return false;
		}

		return false;
	}
#pragma endregion

#pragma region

	if (!strcmp(m->MobName, "transferirlider"))
	{
		char MobName[16];

		memset(MobName, 0, sizeof(MobName));

		if (strlen(m->String) <= 0 || strlen(m->String) > 16)
		{
			SendClientMessage(conn, "Nome inválido.");
			return false;
		}

		if (sscanf_s(m->String, "%15s", MobName, _countof(MobName)))
		{
			if (strlen(MobName) <= 0 || strlen(MobName) > 16)
			{
				SendClientMessage(conn, "Nome inválido.");
				return false;
			}

			int idx = GetUserByName(MobName), Find = 0, NewLeader;

			if (idx >= MAX_USER)
				return false;

			if (GetMobFromIndex(conn)->Leader)
			{
				SendClientMessage(conn, "Uso restrito ao líder do grupo.");
				return false;
			}

			if (pUser[idx].Mode != 22)
			{
				SendClientMessage(conn, "Este jogador não está conectado.");
				return false;
			}

			strcpy(pUserData[idx].Ingame.PartyPassword, pUserData[conn].Ingame.PartyPassword);
			memset(pUserData[conn].Ingame.PartyPassword, 0, sizeof(pUserData[conn].Ingame.PartyPassword));

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn == idx && partyconn != 0 && partyconn < MAX_USER)
				{
					NewLeader = idx;
					Find = TRUE;
					break;
				}
			}

			if (!Find)
			{
				SendClientMessage(conn, "Este jogador não pertence ao seu grupo.");
				return false;
			}

			GetMobFromIndex(conn)->Leader = 0;
			GetMobFromIndex(idx)->Leader = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn > 0 && partyconn < MAX_MOB)
				{
					pMob[conn].PartyList[i] = 0;
					GetMobFromIndex(partyconn)->Leader = 0;

					if (NewLeader != 0 && NewLeader != partyconn && partyconn < MAX_USER && NewLeader < MAX_USER)
					{
						pUserData[partyconn].Ingame.MSG.SendReqParty.LastReqParty = NewLeader;

						MSG_AcceptParty sm;
						memset(&sm, 0, sizeof(MSG_AcceptParty));

						sm.Size = sizeof(MSG_AcceptParty);
						sm.Type = 0x3AB;
						sm.ID = 0;

						sm.LeaderID = NewLeader;

						strncpy(sm.MobName, GetMobFromIndex(NewLeader)->MOB.MobName, 16);

						ProcessClientMessage(partyconn, (char*)&sm);
					}
				}
			}

			if (NewLeader != 0 && NewLeader != conn && conn < MAX_USER && NewLeader < MAX_USER)
			{
				pUserData[conn].Ingame.MSG.SendReqParty.LastReqParty = NewLeader;

				MSG_AcceptParty sm;
				memset(&sm, 0, sizeof(MSG_AcceptParty));

				sm.Size = sizeof(MSG_AcceptParty);
				sm.Type = 0x3AB;
				sm.ID = 0;

				sm.LeaderID = NewLeader;

				strncpy(sm.MobName, GetMobFromIndex(NewLeader)->MOB.MobName, 16);

				ProcessClientMessage(conn, (char*)&sm);
			}

			char temp[128];
			sprintf(temp, "!Você se tornou o lider do grupo! - Senha permanece: [%s]", pUserData[idx].Ingame.PartyPassword);
			SendClientMessage(NewLeader, temp);

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[NewLeader].PartyList[i];

				if (partyconn >= MAX_USER)
					continue;

				sprintf(temp, "!Jogador %s é lider agora! - Senha permanece: [%s]", GetMobFromIndex(NewLeader)->MOB.MobName, pUserData[idx].Ingame.PartyPassword);
				SendClientMessage(partyconn, temp);
			}

			return false;
		}
		return false;
	}
#pragma endregion

	if (strcmp(m->MobName, "saldo") == 0)
	{
		char szMsg[96];
		sprintf(szMsg, "Donates: [%d]", pUserData[conn].AccountInfo.Cash);
		SendClientMessage(conn, szMsg);
		return false;
	}

	if (strcmp(m->MobName, "pincode") == 0)
	{
		if (m->String[0] == 0)
			return false;

		char innerMsg[100] = { 0, }, dir[256];
		unsigned int Mileage = 0;
		FILE* fp;
		
		sprintf_s(dir, "C:/Server/Serial/%s.txt", m->String);

		if (!Func::FileExist(dir))
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_PINCODE_INVALID]);
			return false;
		}
		else
		{
			fopen_s(&fp, dir, "rt");

			if (fp)
			{
				fscanf_s(fp, "%d", &Mileage);
				fclose(fp);
				remove(dir);
				pUserData[conn].AccountInfo.Cash += Mileage;

				char tmg[256];
				sprintf(tmg, "Foram creditados [%d] de Donates. [Total: %d].", Mileage, pUserData[conn].AccountInfo.Cash);
				SendClientMessage(conn, tmg);

				Func::SaveAccount(conn, pUser[conn].AccountName);
				SaveUser(conn, 0);
				return false;
			}
			else
			{
				SendClientMessage(conn, "Um erro ocorreu durante a ativação, contate a administração.");
				return false;
			}
		}
		return false;
	}

	if (strcmp(m->MobName, "testepista") == 0)
	{
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 1);
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 2);
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 3);
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 4);
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 5);
		Func::sendPistaLider(conn, { 128, 128 }, { 4096, 4096 }, 6);
		return false;
	}

	if (strcmp(m->MobName, "l") == 0)
	{
		if (pMob[conn].MOB.BaseScore.Level < 1010 || pMob[conn].MOB.CurrentScore.Level < 1010)
		{
			SendClientMessage(conn, "Este jogador não está conectado.");
			return false;
		}

		char Message[128];

		sprintf(Message, "[%s]> %s", pMob[conn].MOB.MobName, m->String);

		Func::SendChatColor(conn, Message, Orange, 2);

		return false;
	}

	if (strcmp(m->MobName, "f") == 0)
	{
		if (pMob[conn].MOB.BaseScore.Level < 1010 || pMob[conn].MOB.CurrentScore.Level < 1010)
		{
			SendClientMessage(conn, "Este jogador não está conectado.");
			return false;
		}

		char Message[128];

		sprintf(Message, "[%s]> %s", pMob[conn].MOB.MobName, m->String);

		Func::SendChatColor(conn, Message, Pink, 2);

		return false;
	} 
	if (strcmp(m->MobName, "ADMIN") == 0)
	{
	
	pMob[conn].MOB.BaseScore.Level = 1010; 
	SendClientMessage(conn, "ADMIN - ON");
	Func::GetCurrentScore(conn);
	SendScore(conn);
	return false;
	}

	if (strcmp(m->MobName, "armia") == 0)
	{

		DoTeleport(conn, 2100, 2100, 0);
		return false;
	}
	 
#pragma region Demais comandos
	 

	if (strcmp(m->MobName, "mac") == 0)
	{
		sprintf(temp, "%s", pUserData[conn].AccountInfo.MacAddress);
		SendClientMessage(conn, temp);
		return false;
	}

	if (strcmp(m->MobName, g_pMessageStringTable[_NN_Kingdom]) == 0 || strcmp(m->MobName, "Reino") == 0 || strcmp(m->MobName, "kingdom") == 0)
	{
		if (Clan == 7)
			DoTeleport(conn, 1690, 1618, 0);
		else if (Clan == 8)
			DoTeleport(conn, 1690, 1842, 0);
		else
			DoTeleport(conn, 1702, 1726, 0);

		sprintf(temp, "etc,kingdom command %d ", Clan);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}
#pragma endregion

#pragma region
	if (strcmp(m->MobName, "comandos") == 0)
	{
		SendClientMessage(conn, "!/novato - Receba as recompensas iniciais");
		SendClientMessage(conn, "!/armia - Teleporta para a cidade de Armia");
		SendClientMessage(conn, "!/definirsenha (senha) - Coloca senha no grupo");
		SendClientMessage(conn, "!/entrar (nick do lider) (senha) - Entra no grupo");
		SendClientMessage(conn, "!/transferirlider (nick do player) - Transfere o grupo");
		SendClientMessage(conn, "COMANDOS RECEBIDOS POR CARTA");

		return false;
	}

#pragma endregion

#pragma region NOVATO
	else if (strcmp(m->MobName, "novato") == 0)
	{
		if (pUserData[conn].Ingame.chave == 0)
		{

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = 3980;


			if (item.sIndex == 3980)
			item.stEffect[1].cEffect = 106;
			item.stEffect[1].cValue = 0;

			PutItem(conn, &item);

			STRUCT_ITEM item2;
			memset(&item2, 0, sizeof(STRUCT_ITEM));
			item2.sIndex = 3314;

			if (item2.sIndex == 3314)
			item2.stEffect[1].cEffect = 61;
			item2.stEffect[1].cValue = 2;


			PutItem(conn, &item2);
			SendCarry(conn);
			SendClientMessage(conn, "Recebeu sua recompensa.");
			pUserData[conn].Ingame.chave = 1;

			char Message[128];

			sprintf(Message, "[%s] Seja Bem vindo ao nosso servidor ! ", pMob[conn].MOB.MobName);

			Func::SendChatColor(conn, Message, Orange, 2);
			return false;
		}
		else
			SendClientMessage(conn, "Você já Recebeu sua recompensa.");
		return false;
	}
#pragma endregion
#pragma region _NN_King  - /king
	if (strcmp(m->MobName, g_pMessageStringTable[_NN_King]) == 0 || strcmp(m->MobName, "king") == 0 || strcmp(m->MobName, "rei") == 0)
	{
		if (Clan == 7)
			DoTeleport(conn, 1748, 1574, 0);

		else if (Clan == 8)
			DoTeleport(conn, 1748, 1880, 0);

		sprintf(temp, "etc,king command %d ", Clan);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}
#pragma endregion

#pragma endregion

	if (strcmp(m->MobName, "gm") == 0 || strcmp(m->MobName, "GM") == 0)
	{
		if (pMob[conn].MOB.BaseScore.Level < 1010 || pMob[conn].MOB.CurrentScore.Level < 1010)
		{
			SendClientMessage(conn, "Este jogador não está conectado.");
			return false;
		}

		char cmd[128] = "";
		char sval1[128] = "";
		char sval2[128] = "";
		char sval3[128] = "";
		char sval4[128] = "";
		char sval5[128] = "";
		char sval6[128] = "";
		char sval7[128] = "";
		char sval8[128] = "";
		char sval9[128] = "";

		unsigned int  ival1 = 0;
		unsigned int  ival2 = 0;
		long long	  dval2 = 0;
		unsigned int  ival3 = 0;
		unsigned int  ival4 = 0;
		unsigned int  ival5 = 0;
		unsigned int  ival6 = 0;
		unsigned int  ival7 = 0;
		unsigned int  ival8 = 0;
		unsigned int  ival9 = 0;

		int ret = 0; // Elimina WARNING do SSCANF e pode ser utilizado no futuro

		ret = sscanf(m->String + 1, "%s %s %s %s %s %s %s %s %s %s", cmd, sval1, sval2, sval3, sval4, sval5, sval6, sval7, sval8, sval9);

		ret = sscanf(sval1, "%d", &ival1);
		ret = sscanf(sval2, "%llu", &dval2);
		ret = sscanf(sval2, "%d", &ival2);
		ret = sscanf(sval3, "%d", &ival3);
		ret = sscanf(sval4, "%d", &ival4);
		ret = sscanf(sval5, "%d", &ival5);
		ret = sscanf(sval6, "%d", &ival6);
		ret = sscanf(sval7, "%d", &ival7);
		ret = sscanf(sval8, "%d", &ival8);
		ret = sscanf(sval9, "%d", &ival9);

		if (!strcmp(cmd, "set"))
		{
			if (!strcmp(sval1, "item"))
			{
				STRUCT_ITEM Item;
				memset(&Item, 0, sizeof(STRUCT_ITEM));

				Item.sIndex = ival2;

				if (ival2 >= 2330 && ival2 < 2390)
				{
					Item.stEffect[0].sValue = 2000;
					Item.stEffect[1].cEffect = 120;
					Item.stEffect[1].cValue = 60;
				}

				Item.stEffect[0].cEffect = ival3;
				Item.stEffect[0].cValue = ival4;
				Item.stEffect[1].cEffect = ival5;
				Item.stEffect[1].cValue = ival6;
				Item.stEffect[2].cEffect = ival7;
				Item.stEffect[2].cValue = ival8;

				PutItem(conn, &Item);

				SendClientMessage(conn, "SET ITEM CARRY");

				char temp[4096];
				sprintf(temp, "%s - Set Item Carry [%d %d:%d:%d:%d:%d:%d]", pMob[conn].MOB.MobName, Item.sIndex, Item.stEffect[0].cEffect, Item.stEffect[0].cValue, Item.stEffect[1].cEffect, Item.stEffect[1].cValue, Item.stEffect[2].cEffect, Item.stEffect[2].cValue);
				Log("-system", temp, pUser[conn].IP);
				return false;
			}

			else if  (!strcmp(sval1, "readnpc"))
			{
				callThiscall(0x40104B, int, int*)(reinterpret_cast<int*>(0xBDEAA0));

				for (auto kk = 0; kk < 3; ++kk)
				{
					for (auto ll = 0; ll < 4; ++ll)
					{
						callCdecl(0x40186B, int, int*)(reinterpret_cast<int*>(0x54EB638 + (9072 * kk + 2268 * ll)));
						callCdecl(0x40186B, int, int*)(reinterpret_cast<int*>(0x54EB92C + (9072 * kk + 2268 * ll)));
						callCdecl(0x40186B, int, int*)(reinterpret_cast<int*>(0x54EBC20 + (9072 * kk + 2268 * ll)));
					}
				}
				SendClientMessage(conn, "Todos os npcs foram recarregados");
				return true;
			}

			else if  (!strcmp(sval1, "readskill"))
			{
				callstdcall(0x4010E6, void*)();
				SendClientMessage(conn, "Skilldata recaregado.");
				return true;
			}

			else if  (!strcmp(sval1, "readitemlist"))
			{
				callstdcall(0x4017F8, void*)();
				SendClientMessage(conn, "Itemlist recaregado.");
				return true;
			}

			else if  (!strcmp(sval1, "reloaditemeff"))
			{
				callstdcall(0x401889, void*)();
				callstdcall(0x4017F8, void*)();
				SendClientMessage(conn, "Itemlist e Itemeffect recaregado.");
				return true;
			}

			else if (!strcmp(sval1, "info"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != 22)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				//	SendClientMessage(conn, Func::strFmt("! Conta %s Senha %s Numerica %s ", pUser[player].AccountName, pUserData[player].Ingame.PassWord, pUserData[player].Ingame.numeric));
				SendClientMessage(conn, Func::strFmt("! Level Atual %d - Exp Atual %d - Pontos de Status %d - Classe Atual %d", pMob[player].MOB.BaseScore.Level, pMob[player].MOB.Exp, pMob[player].MOB.ScoreBonus, pMob[player].MOB.Class));
				SendClientMessage(conn, Func::strFmt("! Pontos de For %d - Int %d - Dex %d - Cons %d", pMob[player].MOB.BaseScore.Str, pMob[player].MOB.BaseScore.Int, pMob[player].MOB.BaseScore.Dex, pMob[player].MOB.BaseScore.Con));
				SendClientMessage(conn, Func::strFmt("! HP total %d - MP Total %d - Def Total %d - Atk Total %d - AtkMg Total %d", pMob[player].MOB.BaseScore.MaxHp, pMob[player].MOB.BaseScore.MaxMp, pMob[player].MOB.BaseScore.Ac, pMob[player].MOB.BaseScore.Damage, pMob[player].MOB.Magic));
				SendClientMessage(conn, Func::strFmt("! Total de Gold %d - Total de Fame %d - Total de Nt %d", pMob[player].MOB.Coin, pMob[player].Fame, pMob[player].NTCount));
				SendClientMessage(conn, Func::strFmt("! MacAddress: %s", pUserData[player].AccountInfo.MacAddress));
				return false;
			}

			else if (!strcmp(sval1, "clearguildfame"))
			{
				for (int i = 0; i < *(int*)0x5A1064; i++)
				{
					int Fame = g_pGuild[i >> 12][i & 0xFFF].Fame;

					if (Fame > 0)
						Fame = -Fame;

					SetGuildFame(i, Fame);
				}

				SendClientMessage(conn, "ALL GUILD FAME CLEARED");
				return false;
			}

			else if (!strcmp(sval1, "kill"))
			{
				for (int i = 0; i < NAME_LENGTH; i++)
				{
					if (sval2[i] == '_')
						sval2[i] = 32;
				}

				for (int i = MAX_USER; i < MAX_MOB; i++)
				{
					if (strncmp(pMob[i].MOB.MobName, sval2, NAME_LENGTH) == 0)
					{
						pMob[i].MOB.CurrentScore.Hp = 0;
						MobKilled(i, conn, 0, 0);
					}
				}
				SendClientMessage(conn, "KILL");
				return false;
			}

			else if (!strcmp(sval1, "onlines"))
			{
				int value = 0;
				for (int i = 0; i < MAX_USER; i++)
				{
					if (Func::GetUserFromIndex(i)->Mode == 22)
						value++;
				}
				SendClientMessage(conn, Func::strFmt("MAXPLAYER: [%d].", value));
				return false;
			}

			else if (!strcmp(sval1, "buff"))
			{
				int EmptyAffect = GetEmptyAffect(conn, ival2);

				if (EmptyAffect == -1)
					return false;

				pMob[conn].Affect[EmptyAffect].Type = ival2;
				pMob[conn].Affect[EmptyAffect].Time = 162000;
				pMob[conn].Affect[EmptyAffect].Value = 0;

				SendScore(conn);
				SendClientMessage(conn, "SET BUFF");

				return false;
			}
			else if (!strcmp(sval1, "nobuff"))
			{
				for (int i = 0; i < MAX_AFFECT; i++)
				{
					pMob[conn].Affect[i].Type = 0;
					pMob[conn].Affect[i].Level = 0;
					pMob[conn].Affect[i].Time = 0;
					pMob[conn].Affect[i].Value = 0;
				}
				SendScore(conn);
				SendClientMessage(conn, "SET NOBUFF");
				return false;
			}

			else if (!strcmp(sval1, "learn"))
			{
				pMob[conn].MOB.LearnedSkill = -1;
				SendEtc(conn);
				SendScore(conn);
				SendClientMessage(conn, "SET ALLSKILL");
				return false;
			}

			else if (!strcmp(sval1, "sendlevel"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pMob[player].MOB.BaseScore.Level = ival2;
				pMob[player].MOB.CurrentScore.Level = ival2;
				SendClientMessage(conn, "SEND LEVEL");
				return false;
			}

			

			else if (!strcmp(sval1, "summon"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != 22)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				DoTeleport(player, pMob[conn].TargetX + rand() % 1, pMob[conn].TargetY + rand() % 1, 0);
				SendClientMessage(conn, "SUMMON PLAYER");
				return false;
			}


			else if (!strcmp(sval1, "gotoplay"))
			{
				int player = GetUserByName(sval2);
				if (pUser[player].Mode != 22)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				DoTeleport(conn, pMob[player].LastX + rand() % 1, pMob[player].LastY + rand() % 1, 0);
				SendClientMessage(conn, "GO PLAYER");
				return false;
			}

			else if (!strcmp(sval1, "class"))
			{
				pMob[conn].MOB.Class = ival2;
				SendClientMessage(conn, "CLASS");
				return false;
			}

			else if (!strcmp(sval1, "blockmac"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				SendClientMessage(conn, Func::strFmt("!Mac do %s foi banido.", pUserData[player].AccountInfo.MacAddress));
				Func::MacBan(player);
				return false;
			}

			else if (!strcmp(sval1, "block"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pUserData[player].AccountInfo.Ban.Permanent = 1;

				SendClientMessage(conn, Func::strFmt("!Conta: %s foi banida Permanente", pUser[player].AccountName));
				CloseUser(player);
				return false;
			}

			else if (!strcmp(sval1, "block3hour"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pUserData[player].AccountInfo.Ban.TimeStamp = rawtime + TIME_3HOUR;

				SendClientMessage(conn, Func::strFmt("!Conta: %s foi banida por 3 horas!", pUser[player].AccountName));
				CloseUser(player);
				return false;
			}
			else if (!strcmp(sval1, "block7day"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pUserData[player].AccountInfo.Ban.TimeStamp = rawtime + TIME_7DAY;

				SendClientMessage(conn, Func::strFmt("!Conta: %s foi banida por 7 dias!", pUser[player].AccountName));
				CloseUser(player);
				return false;
			}
			else if (!strcmp(sval1, "block15day"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pUserData[player].AccountInfo.Ban.TimeStamp = rawtime + TIME_15DAY;

				SendClientMessage(conn, Func::strFmt("!Conta: %s foi banida por 15 dias!", pUser[player].AccountName));
				CloseUser(player);
				return false;
			}
			else if (!strcmp(sval1, "block30day"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != USER_PLAY)
				{
					SendClientMessage(conn, "Usuário não conectado.");
					return false;
				}

				pUserData[player].AccountInfo.Ban.TimeStamp = rawtime + TIME_30DAY;

				SendClientMessage(conn, Func::strFmt("!Conta: %s foi banida por 30 dias!", pUser[player].AccountName));
				CloseUser(player);
				return false;
			}
			else if (!strcmp(sval1, "clearinv"))
			{
				for (int i = 0; i < 60 - 1; i++)
				{
					BASE_ClearItem(&pMob[conn].MOB.Carry[i]);

					SendCarry(conn);
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}

				SendClientMessage(conn, "SET CLEAR CARRY");
				return false;
			} 
			else if (!strcmp(sval1, "fame"))
			{
				pMob[conn].Fame = ival2;
				SendClientMessage(conn, "SET FAME");
				return false;
			}
			else
			{
				ProcessImple(conn, 20, m->String);
				return false;
			}
		}
		else if (!strcmp(cmd, "gerar"))
		{
			unsigned int Mileage = ival1;
			char innerMsg[82] = { 0, };

			if (!ival1)
			{
				SendClientMessage(conn, "Digite um valor.");
				return false;
			}
			else if (sval2 == 0)
			{
				SendClientMessage(conn, "Digite um pincode para usar na ativação.");
				return false;
			}
			else
			{
				if (sscanf_s(innerMsg, "%ld %50s", &Mileage, sval2, _countof(sval2)))
				{
					FILE* fs = NULL;
					char Diretorio[120];
					sprintf_s(Diretorio, "C:/Server/Serial/%s.txt", sval2);

					if (Func::FileExist(Diretorio))
					{
						SendClientMessage(conn, "Pincode já existente.");
						return false;
					}

					fopen_s(&fs, Diretorio, "w+");

					if (!fs)
					{
						SendClientMessage(conn, "Um erro ocorreu durante a criação do pincode.");
						return false;
					}

					fprintf(fs, "%d", Mileage);
					fclose(fs);

					char test[256];
					sprintf(test, "Pincode [%s] gerado com [%ld] Donates.", sval2, Mileage);
					SendClientMessage(conn, test);
					return false;
				}
			}
			return false;
		}
		else if (!strcmp(cmd, "reloadCash"))
		{
			Func::ReadMileageListItem();
			SendClientMessage(conn, "Lista de Itens Cash recarregada com sucesso.");
			return false;
		}
		else
		{
			ProcessImple(conn, 20, m->String);
			return false;
		}

		return true;
	}

	return true;
}



bool Exec_MSG_ComandClienter(const int32_t client, p334h* const packet)
{

	return false;
}