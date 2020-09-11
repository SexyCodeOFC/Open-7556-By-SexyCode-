#include "stdafx.h"

const INT16 NotCharms[] =
{
	540, 541, 551, 552, 553, 554, 555, 556, 557, 558, 559,
	560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570,
	591, 592, 593, 594, 595, 633, 1738, 661, 662, 663, 3464, 5603, 5604, 5605, 5606
}; 
#define RATE_RefOdin 20
#define RATE_CompOdin 20
#define RATE_CompOdin_ArmaCelestial 20
#define RATE_CompOdin_SetCelestial 20
#define RATE_CompPista 20
#define RATE_RefAmuha 20


int GetChanceRefOdin(STRUCT_ITEM *Item)
{
	if ((Item->EFV1 >= 234 && Item->EFV1 < 238) ||
		(Item->EFV2 >= 234 && Item->EFV2 < 238) ||
		(Item->EFV3 >= 234 && Item->EFV3 < 238))
		return 5;
	else if ((Item->EFV1 >= 238 && Item->EFV1 < 242) ||
		(Item->EFV2 >= 238 && Item->EFV2 < 242) ||
		(Item->EFV3 >= 238 && Item->EFV3 < 242))
		return 3;
	else if ((Item->EFV1 >= 242 && Item->EFV1 < 246) ||
		(Item->EFV2 >= 242 && Item->EFV2 < 246) ||
		(Item->EFV3 >= 242 && Item->EFV3 < 246))
		return 2;
	else if ((Item->EFV1 >= 246 && Item->EFV1 < 250) ||
		(Item->EFV2 >= 246 && Item->EFV2 < 250) ||
		(Item->EFV3 >= 246 && Item->EFV3 < 250))
		return 1;
	else
		return 0;
}

bool Exec_MSG_OdinFixRefinação(int32_t client, char* pMsg)
{	 
	MSG_CombineItem* p = (MSG_CombineItem*)pMsg;

	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(p->ID);

	MSG_STANDARD* packet = (MSG_STANDARD*)pMsg;

	if (p->ID <= 0 || p->ID >= MAX_USER)
		return false;

	for (INT8 i = 0; i < 7; i++)
	{
		if (p->InvenPos[i] == 0xFF)
			return false;

		else if (memcmp(&p->Item[i], &player->Carry[p->InvenPos[i]], sizeof STRUCT_ITEM))
			return false;

		else if (p->Item[i].sIndex != player->Carry[p->InvenPos[i]].sIndex)
			return false;

		else if (p->Item[i].sIndex < 0 || p->Item[i].sIndex > 6500)
			return false;
		Log("err,msg_CombineOdin - item remove or changed.", pUser[client].AccountName, pUser[client].IP);

	}


	if (p->Item[0].sIndex == 4043 && p->Item[1].sIndex == 4043)
	{
		if (p->Item[3].sIndex != 3338)
		{
			SendClientMessage(p->ID, "Algo está errado com a combinação.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
			ZeroMemory(&packet, *(short*)packet);
			return false;
		}
		else if (p->Item[4].sIndex != 3338)
		{
			SendClientMessage(p->ID, "Algo está errado com a combinação.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
			ZeroMemory(&packet, *(short*)packet);
			return false;
		}
		else if (p->Item[5].sIndex != 3338)
		{
			SendClientMessage(p->ID, "Algo está errado com a combinação.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
			ZeroMemory(&packet, *(short*)packet);
			return false;
		}
		else if (p->Item[6].sIndex != 3338)
		{
			SendClientMessage(p->ID, "Algo está errado com a combinação.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
			ZeroMemory(&packet, *(short*)packet);
			return false;
		}

		for (INT8 i = 0; i < sizeof(NotCharms) / sizeof(INT16); i++)
		{
			if (player->Carry[p->InvenPos[2]].sIndex == NotCharms[i])
			{
				if (NotCharms[i] == 3464)
					SendClientMessage(p->ID, "Refinação amuha somente com PL.");
				else
					SendClientMessage(p->ID, "Algo está errado com a combinação.");

				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				ZeroMemory(&packet, *(short*)packet);
				return false;
			}
		}

		INT16 RefDoItem = Func::GetItemSanc(&p->Item[2]);
		int Chances = Rnd::instance().IRandomX(0, 100);

		if (RefDoItem <= 233 || RefDoItem >= 250)
		{
			SendClientMessage(p->ID, "A refinação do item deve estar entre +11 e +14.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
			ZeroMemory(&packet, *(short*)packet);
			return false;
		}

		UINT8 chances = RATE_RefOdin;
		chances += (BASE_GetItemSanc(&p->Item[3]));
		chances += (BASE_GetItemSanc(&p->Item[4]));
		chances += (BASE_GetItemSanc(&p->Item[5]));
		chances += (BASE_GetItemSanc(&p->Item[6]));
		chances += GetChanceRefOdin(&p->Item[2]);

		for (INT8 e = 3; e < 7; e++)
			memset(&player->Carry[p->InvenPos[e]], 0, sizeof STRUCT_ITEM);

		memset(&player->Carry[p->InvenPos[0]], 0, sizeof STRUCT_ITEM);
		memset(&player->Carry[p->InvenPos[1]], 0, sizeof STRUCT_ITEM);
		
		if (Chances <= chances)
		{
			SendEmotion(p->ID, 14, 3);
			Func::RefinarItemMais(&player->Carry[p->InvenPos[2]], 4);
			SendClientMessage(p->ID, "Sucesso na refinação.");
			Log(Func::strFmt("%s ref %s sucess", player->MobName, pItem(player->Carry[p->InvenPos[2]].sIndex)->Name), "AlquimistaOdim", 0);
		}
		else
		{
			Func::RefinarItemMais(&player->Carry[p->InvenPos[2]], -4);
			SendEmotion(client, 15, 2);
			SendClientMessage(p->ID, "Refinação falhou.");
			Log(Func::strFmt("%s ref %s fail", player->MobName, pItem(player->Carry[p->InvenPos[2]].sIndex)->Name), "AlquimistaOdim", 0);

		}
		for (int i = 0; i < 7; i++)
			SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[i], &player->Carry[p->InvenPos[i]]);


		SendEtc(p->ID);
		SendScore(p->ID);
		SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
		ZeroMemory(&packet, *(short*)packet);
		return false;
	}
	else
	{
		//Slot 0 Item: Emblema_da_Proteção
		//Slot 1 Item : Pacote_Lactolerium
		//Slot 2 Item : Armadura_Rake
		//Slot 3 Item : Refinação_Abençoada
		//Slot 4 Item : Refinação_Abençoada
		//Slot 5 Item : Refinação_Abençoada
		//Slot 6 Item : Pedra_Secreta_(Vento
		if (p->Item[0].sIndex == 4043 && p->Item[1].sIndex == 3448 || p->Item[0].sIndex == 3448 && p->Item[1].sIndex == 4043)
		{
			for (INT8 i = 0; i < sizeof(NotCharms) / sizeof(INT16); i++)
			{
				if (player->Carry[p->InvenPos[2]].sIndex == NotCharms[i])
				{
					SendClientMessage(p->ID, "Algo está errado com a combinação.");
					SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
					ZeroMemory(&packet, *(short*)packet);
					return false;
				}
			}

			INT16 RefDoItem = Func::GetItemSanc(&p->Item[2]);

			if (RefDoItem <= 233 || RefDoItem >= 250)
			{
				SendClientMessage(p->ID, "A refinação do item deve estar entre +11 e +14.");
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				ZeroMemory(&packet, *(short*)packet);
				return false;
			}
			else
			{
				SendClientMessage(p->ID, "Impossivel fazer isso");
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				ZeroMemory(&packet, *(short*)packet);
				return false;
			}
			return true;

		}
		if (p->Item[0].sIndex == 3448 && p->Item[1].sIndex == 3448)
		{
			for (INT8 i = 0; i < sizeof(NotCharms) / sizeof(INT16); i++)
			{
				if (player->Carry[p->InvenPos[2]].sIndex == NotCharms[i])
				{
					SendClientMessage(p->ID, "Algo está errado com a combinação.");
					SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
					ZeroMemory(&packet, *(short*)packet);
					return false;
				}
			}

			INT16 RefDoItem = Func::GetItemSanc(&p->Item[2]);

			if (RefDoItem <= 233 || RefDoItem >= 250)
			{
				SendClientMessage(p->ID, "A refinação do item deve estar entre +11 e +14.");
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				ZeroMemory(&packet, *(short*)packet);
				return false;
			}
			else
			{
				SendClientMessage(p->ID, "Impossivel fazer isso");
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				ZeroMemory(&packet, *(short*)packet);
				return false;
			}
			return true;
		}
		else
			return true;
	}

	return false;
}

bool Exec_MSG_ComposiçãoPistaDeRunas(int32_t client, char* pMsg)
{

	MSG_STANDARD* packet = (MSG_STANDARD*)pMsg;

	MSG_CombineItem* p = (MSG_CombineItem*)pMsg;

	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(p->ID);

	if (client != p->ID || p->ID <= 0 || p->ID >= MAX_USER)
		return false;

	for (INT8 i = 0; i < 7; i++)
	{
		if (p->InvenPos[i] == 0xFF)
			return false;

		else if (memcmp(&p->Item[i], &player->Carry[p->InvenPos[i]], sizeof STRUCT_ITEM))
			return false;

		else if (p->Item[i].sIndex != player->Carry[p->InvenPos[i]].sIndex)
			return false;

		else if (p->Item[i].sIndex < 0 || p->Item[i].sIndex > 6500)
			return false;
	}

	
	int PLs = 0;
	for (INT8 x = 0; x < 7; x++)
	{
		if (p->Item[x].sIndex == 413)
			PLs++;
	}

	const int SancPista[] = { 0, 1, 2, 3 };
	srand(time(NULL) / 5 * (rand() % 500) * 5);
	if (PLs == 7)
	{

		int Chance = rand() % 100;

		if (Chance <= RATE_CompPista)
		{
			Func::RemoveItens(7, player, p);
			Func::GiveItem(client, 5134, 43, SancPista[rand() % 7], 0);
			SendEmotion(p->ID, 14, 3);
			SendClientMessage(p->ID, "Sucesso na Composição.");
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
		}
		else
		{
			Func::RemoveItens(7, player, p);
			SendClientMessage(p->ID, "Falha na Composição.");
			SendEmotion(client, 15, 2);
			SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
		}
		return false;
	}

	return true;

}

bool Exec_MSG_OdinFixArmaCele(int32_t client, char* pMsg)
{

	MSG_STANDARD* packet = (MSG_STANDARD*)pMsg;

	MSG_CombineItem* p = (MSG_CombineItem*)pMsg;

	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(p->ID);

	if (p->ID <= 0 || p->ID >= MAX_USER)
		return false;

	for (INT8 i = 0; i < 7; i++)
	{
		if (p->InvenPos[i] == 0xFF)
			return false;

		else if (memcmp(&p->Item[i], &player->Carry[p->InvenPos[i]], sizeof STRUCT_ITEM))
			return false;

		else if (p->Item[i].sIndex != player->Carry[p->InvenPos[i]].sIndex)
			return false;

		else if (p->Item[i].sIndex < 0 || p->Item[i].sIndex > 6500)
			return false;

		 
	}

	int Chance = Rnd::instance().IRandomX(0, 100);

	int EquivalenteID = -1, Equivale;

	if (p->Item[0].sIndex == 1901 || p->Item[0].sIndex == 1902 || p->Item[0].sIndex == 1903 || p->Item[0].sIndex == 1904 || p->Item[0].sIndex == 1905 || p->Item[0].sIndex == 1906 || p->Item[0].sIndex == 1907 || p->Item[0].sIndex == 1908 || p->Item[0].sIndex == 1909 || p->Item[0].sIndex == 1910 || p->Item[0].sIndex == 1714)
	{
		static int ArmaSelado[] = { 1901, 1902, 1903, 1904, 1905, 1906, 1907, 1908, 1909, 1910, 1714 };
		static int ArmaEquiva[] = { 2491, 2551, 2611, 2671, 2731, 2791, 2859, 2863, 2895, 2935, 1711 };




		for (int i = 0; i < sizeof(ArmaSelado) / sizeof(int); i++)
		{
			if (p->Item[0].sIndex == ArmaSelado[i])
			{
				EquivalenteID = i;
				break;
			}
		}

		if (EquivalenteID == -1)
			return false;

		if (ArmaSelado[EquivalenteID] == 1714)
			Equivale = ArmaEquiva[EquivalenteID];
		else
			Equivale = ArmaEquiva[EquivalenteID] + 3;

		if (p->Item[1].sIndex >= ArmaEquiva[EquivalenteID] && p->Item[1].sIndex <= Equivale)
		{
			int Selado = BASE_GetItemSanc(&p->Item[0]);
			int Arch = BASE_GetItemSanc(&p->Item[1]);
			if (Selado != 9)
			{
				SendClientMessage(p->ID, "Item Selado deve ser +9");
				return false;
			}
			if (Arch < 27 && Arch > 30)
			{
				SendClientMessage(p->ID, "Item Arch deve ser +15");
				return false;
			}
			if (p->Item[2].sIndex != 772)
			{
				SendClientMessage(p->ID, "Equipe a Jóia_da_Escuridão");
				return false;
			}


			if (p->Item[3].sIndex != 5334 || p->Item[4].sIndex != 5335 || p->Item[5].sIndex != 5336 || p->Item[6].sIndex != 5337)
			{
				SendClientMessage(p->ID, "Coloque as Pedras Secretas em Ordem");
				return false;
			}
			if (!ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex))
			{
				SendClientMessage(p->ID, "Selado não confere!");
				return false;
			}
			if (Chance <= RATE_CompOdin_ArmaCelestial)
			{
				STRUCT_ITEM sGiveItem;
				BASE_ClearItem(&sGiveItem);

				memcpy(&sGiveItem, &player->Carry[p->InvenPos[1]], sizeof STRUCT_ITEM);//salva o item arch
				sGiveItem.sIndex = ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex); //conserva os adds e muda apenas o ID
				for (INT8 j = 0; j < 7; j++)//deleta todos os itens
				{
					memset(&player->Carry[p->InvenPos[j]], 0, sizeof STRUCT_ITEM);
					SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[j], &player->Carry[p->InvenPos[j]]);
				}
				SendNotice(Func::strFmt("%s acaba de adquirir %s", player->MobName, pItem(sGiveItem.sIndex)->Name));
				BASE_SetItemSanc(&sGiveItem, 0, 0);
				PutItem(p->ID, &sGiveItem);
				SendEtc(p->ID);
				BASE_ClearItem(&sGiveItem);
				SendEmotion(p->ID, 14, 3);
				SendClientMessage(p->ID, "Composição concluída.");
				Log(Func::strFmt("%s comp %s sucess", player->MobName, pItem(ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex))->Name), "AlquimistaOdim", 0);

				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				return false;
			}
			else
			{
				STRUCT_ITEM GiveItem;
				BASE_ClearItem(&GiveItem);

				memcpy(&GiveItem, &player->Carry[p->InvenPos[1]], sizeof STRUCT_ITEM);//salva o item arch
				for (INT8 j = 0; j < 7; j++)//deleta todos os itens
				{
					memset(&player->Carry[p->InvenPos[j]], 0, sizeof STRUCT_ITEM);
					SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[j], &player->Carry[p->InvenPos[j]]);
				}
				PutItem(p->ID, &GiveItem);
				BASE_ClearItem(&GiveItem);

				SendEmotion(client, 15, 2);
				SendClientMessage(p->ID, "Composição Falhou.");
				Log(Func::strFmt("%s comp %s fail", player->MobName, pItem(ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex))->Name), "AlquimistaOdim", 0);
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				return false;
			}
		}
		else
		{
			SendClientMessage(p->ID, "Item equivalente não confere!");
			return false;
		}
		return false;
	}
	if (p->Item[0].sIndex == 1234 || p->Item[0].sIndex == 1235 || p->Item[0].sIndex == 1236 || p->Item[0].sIndex == 1237 || p->Item[0].sIndex == 1369 || p->Item[0].sIndex == 1370 || p->Item[0].sIndex == 1371 || p->Item[0].sIndex == 1372 || p->Item[0].sIndex == 1519 || p->Item[0].sIndex == 1520 || p->Item[0].sIndex == 1521 || p->Item[0].sIndex == 1522 || p->Item[0].sIndex == 1669 || p->Item[0].sIndex == 1670 || p->Item[0].sIndex == 1671 || p->Item[0].sIndex == 1672)
	{

		static int SetSelado[] = { 1234, 1235, 1236, 1237, 1369, 1370, 1371, 1372, 1519, 1520, 1521, 1522, 1669, 1670, 1671, 1672 };
		static int SetEquiva[] = { 1221, 1222, 1223, 1224, 1356, 1357, 1358, 1359, 1506, 1507, 1508, 1509, 1656, 1657, 1658, 1659 };
		for (int i = 0; i < sizeof(SetSelado) / sizeof(int); i++)
		{
			if (p->Item[0].sIndex == SetSelado[i])
			{
				EquivalenteID = i;
				break;
			}
		}

		if (EquivalenteID == -1)
			return false;

		if (p->Item[1].sIndex == SetEquiva[EquivalenteID])
		{
			int Selado = BASE_GetItemSanc(&p->Item[0]);
			int Arch = BASE_GetItemSanc(&p->Item[1]);
			if (Selado != 9)
			{
				SendClientMessage(p->ID, "Item Selado deve ser +9");
				return false;
			}
			if (Arch < 27 && Arch > 30)
			{
				SendClientMessage(p->ID, "Item Arch deve ser +15");
				return false;
			}
			if (p->Item[2].sIndex != 542)
			{
				SendClientMessage(p->ID, "Equipe a Pedra Lunar");
				return false;
			}
			if (ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex) == 0)
			{
				SendClientMessage(p->ID, "Algo está errado!");
				return false;
			}

			if (p->Item[3].sIndex != 5334 || p->Item[4].sIndex != 5335 || p->Item[5].sIndex != 5336 || p->Item[6].sIndex != 5337)
			{
				SendClientMessage(p->ID, "Coloque as Pedras Secretas em Ordem");
				return false;
			}

			if (Chance <= RATE_CompOdin_SetCelestial)
			{
				STRUCT_ITEM sGiveItem;
				BASE_ClearItem(&sGiveItem);

				memcpy(&sGiveItem, &player->Carry[p->InvenPos[1]], sizeof STRUCT_ITEM);//salva o item arch
				sGiveItem.sIndex = ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex); //conserva os adds e muda apenas o ID
				for (INT8 j = 0; j < 7; j++)//deleta todos os itens
				{
					memset(&player->Carry[p->InvenPos[j]], 0, sizeof STRUCT_ITEM);
					SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[j], &player->Carry[p->InvenPos[j]]);
				}
				SendNotice(Func::strFmt("%s acaba de adquirir %s", player->MobName, pItem(sGiveItem.sIndex)->Name));
				BASE_SetItemSanc(&sGiveItem, 0, 0);
				PutItem(p->ID, &sGiveItem);
				SendEtc(p->ID);
				SendScore(p->ID);
				BASE_ClearItem(&sGiveItem);
				SendEmotion(p->ID, 14, 3);
				SendClientMessage(p->ID, "Composição concluída.");
				Log(Func::strFmt("%s comp %s sucess", player->MobName, pItem(ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex))->Name), "AlquimistaOdim", 0);
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				return false;
			}
			else
			{
				STRUCT_ITEM GiveItem;
				BASE_ClearItem(&GiveItem);

				memcpy(&GiveItem, &player->Carry[p->InvenPos[1]], sizeof STRUCT_ITEM);//salva o item arch
				for (INT8 j = 0; j < 7; j++)//deleta todos os itens
				{
					memset(&player->Carry[p->InvenPos[j]], 0, sizeof STRUCT_ITEM);
					SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[j], &player->Carry[p->InvenPos[j]]);
				}
				PutItem(p->ID, &GiveItem);
				BASE_ClearItem(&GiveItem);

				SendEmotion(client, 15, 2);
				SendClientMessage(p->ID, "Composição Falhou.");
				Log(Func::strFmt("%s comp %s fail", player->MobName, pItem(ReturnCorrectitem(p->Item[0].sIndex, p->Item[1].sIndex))->Name), "AlquimistaOdim", 0);
				SendClientSignalParm(p->ID, 0x7530, 0x3A7, 2);
				return false;
			}
		}
		else
		{
			SendClientMessage(p->ID, "Item equivalente não confere!");
			return false;
		}
		return false;
	}

	return true;
}

bool _FixUpAddons(int32_t client, MSG_STANDARD* packet)
{

	MSG_CombineItem *p = (MSG_CombineItem*)packet;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(p->ID);

	if (client != p->ID || p->ID <= 0 || p->ID >= MAX_USER)
		return false;

	for (INT8 i = 0; i < 7; i++)
	{
		if (p->InvenPos[i] == 0xFF)
			return false;

		else if (memcmp(&p->Item[i], &player->Carry[p->InvenPos[i]], sizeof STRUCT_ITEM))
			return false;

		else if (p->Item[i].sIndex != player->Carry[p->InvenPos[i]].sIndex)
			return false;

		else if (p->Item[i].sIndex < 0 || p->Item[i].sIndex > 6500)
			return false;
	}

	static const UINT8 AddTypes[4] = { EF_DAMAGE, EF_MAGIC, EF_AC, EF_CRITICAL };
	static const UINT8 Add[4][2] = {
		{ 6, 9 },
		{ 2, 4 },
		{ 6, 0 },
		{ 5, 0 }
	};
	static const UINT8 MaxAdds[4][2] = {
		{ 10, 50 },
		{ 4, 12 },
		{ 10, 50 },
		{ 30, 90 }
	};
	static const UINT8 Arma_MaxAdds[4][2] = {
		{ 10, 80 },
		{ 4, 36 },
		{ 10, 50 },
		{ 30, 90 }
	};
	INT8 place = -1;
	if (p->Item[0].sIndex == 4043 && p->Item[1].sIndex == 4043)
	{

		int Sanc = BASE_GetItemSanc(&p->Item[2]);
		UINT8 Type = rand() % 3;
		if (Sanc < 10 && Sanc > 14)
		{
			SendClientMessage(p->ID, "Item  deve ser +11");
			return false;
		}
		if (p->Item[3].sIndex != 5334 && p->Item[4].sIndex != 5335 && p->Item[5].sIndex != 5336 && p->Item[6].sIndex != 5337)
		{
			SendClientMessage(p->ID, "Coloque as secretas em ordem");
			return false;
		}
		else
		{
			UINT8 Armor_ = 0;

			if (pItem(p->Item[2].sIndex)->nPos == ARMA_TYPE1 || pItem(p->Item[2].sIndex)->nPos == ARMA_TYPE2)
				Armor_ = 1;
			else if (pItem(p->Item[2].sIndex)->nPos != ELMO_TYPE && pItem(p->Item[2].sIndex)->nPos != PEITO_TYPE &&
				pItem(p->Item[2].sIndex)->nPos != LUVA_TYPE && pItem(p->Item[2].sIndex)->nPos != BOTA_TYPE  &&
				pItem(p->Item[2].sIndex)->nPos != CALCA_TYPE)
				Armor_ = -1;

			if (Armor_ == -1)
			{
				SendClientMessage(p->ID, "Possível usar somente em armas ou armaduras.");
				return false;
			}
			for (int e = 0; e < 3; e++)
			{
				if (p->Item[2].stEffect[e].cEffect == AddTypes[Type])
				{
					// Acha em qual slot dos efs no item está o add
					place = e;

					break;
				}
			}
			int Type_ = pItem(p->Item[2].sIndex)->nPos;
			if (Type_ == 2 || Type_ == 4 || Type_ == 8 || Type_ == 16 || Type_ == 32)
			{
				if ((p->Item[2].stEffect[place].cValue + Add[Type][Armor_]) > MaxAdds[Type][Armor_])
				{
					SendClientMessage(p->ID, "Limite de Adicional Atingido");
					return false;
				}
				else
					return true;

				return false;
			}
			else
			{
				if (pItem(p->Item[2].sIndex)->nPos == ARMA_TYPE1 || pItem(p->Item[2].sIndex)->nPos == ARMA_TYPE2)
				{
					if ((p->Item[2].stEffect[place].cValue + Add[Type][Armor_]) > Arma_MaxAdds[Type][Armor_])
					{
						SendClientMessage(p->ID, "Limite de Adicional Atingido");
						return false;
					}
					else
						return true;

					return false;
				}
				else
				{
					SendClientMessage(p->ID, "Possível usar somente em armas ou armaduras.");
					return false;
				}
				return false;
			}
		}
	}
	return true;
}