#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>

bool Exec_MSG_Quest(int conn, char* pMsg)
{

#pragma region Definições 
	MSG_STANDARDPARM2* m = (MSG_STANDARDPARM2*)pMsg;
	
	p28Bh* kk = (p28Bh*)pMsg;

	int npcIndex = m->Parm1;
	int confirm = m->Parm2;

	if (npcIndex < MAX_USER || npcIndex >= MAX_MOB)
		return false;

	int npcMode = -1;

	int STR = pMob[npcIndex].MOB.BaseScore.Str;
	int INT = pMob[npcIndex].MOB.BaseScore.Int;

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return false;
	}

	if (pUser[conn].TradeMode)
	{
		//SendClientMessage(conn, "#Erro");
		return false;
	}

	if (BASE_GetDistance(pMob[conn].TargetX, pMob[conn].TargetY, pMob[npcIndex].TargetX, pMob[npcIndex].TargetY) > 12)
		return false;
#pragma endregion 

#pragma region KIBITA

	if (pMob[npcIndex].MOB.CurrentScore.Merchant == 74)
	{
		int Price = Func::GetPlayerClass(conn) == 2 ? 4000000 : 2000000;

		int Citizen = GetCitizen(conn);

		if (Citizen == 0)
		{
			if (pMob[conn].MOB.Coin >= Price)
			{
				pMob[conn].MOB.Coin -= Price;

				int SetCitizen = 0x401087;

				__asm
				{
					MOV ECX, DWORD PTR DS : [0x5A1054]
					ADD ECX, 1
					PUSH ECX
					MOV EDX, conn
					PUSH EDX
					CALL SetCitizen
					ADD ESP, 8
				}

				SendClientMessage(conn, g_pMessageStringTable[_DD_JOINTOWNPEP]);
				return false;
			}
			else
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Cure_failed]);
				return false;
			}
		}
		else if (Func::GetPlayerClass(conn) == 0)
		{
			int Item = -1;

			for (int i = 0; i < 60 - 1; i++)
			{
				if (pMob[conn].MOB.Carry[i].sIndex == 420)
				{
					Item = i;
					break;
				}
			}

			if (Item == -1)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Cure_failed]);
				return false;
			}

			struct tm when;
			time_t now;
			time(&now);
			when = *localtime(&now);

			if (when.tm_hour == 23 && pMob[conn].MOB.CurrentScore.Level <= 369)
			{
				int amount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[Item]);

				if (amount > 1)
					BASE_SetItemAmount(&pMob[conn].MOB.Carry[Item], amount - 1);
				else
					memset(&pMob[conn].MOB.Carry[Item], 0, sizeof(STRUCT_ITEM));

				SendItem(conn, ITEM_PLACE_CARRY, Item, &pMob[conn].MOB.Carry[Item]);

				SendClientMessage(conn, g_pMessageStringTable[_DN_TOWN_SOUL_BUFF]);

				int sAffect = GetEmptyAffect(conn, 29);

				if (sAffect == -1)
					return false;

				pMob[conn].Affect[sAffect].Type = 29;
				pMob[conn].Affect[sAffect].Level = 0;
				pMob[conn].Affect[sAffect].Value = 0;
				pMob[conn].Affect[sAffect].Time = AFFECT_1H;

				Func::GetCurrentScore(conn);
				SendScore(conn);

				DoTeleport(conn, 2454 + rand() % 3, 1843 + rand() % 3, 0);

				sprintf(temp, "etc,kibita limit of soul mortal name:%s conn:%d", pMob[conn].MOB.MobName, conn);
				Log(temp, "-system", 0);
				return false;
			}
			else if (pMob[conn].MOB.CurrentScore.Level >= 370)
			{
				int i = 0;

				int stones[4] = { 5334, 5336, 5335, 5337 };

				for (i = 0; i < 60 - 1; i++)
				{
					if (pMob[conn].MOB.Carry[i].sIndex != stones[pMob[conn].MOB.Class])
						continue;

					break;
				}

				if (i != 60 - 1)
				{
					BASE_ClearItem(&pMob[conn].MOB.Carry[i]);
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

					pMob[conn].MOB.LearnedSkill |= 1 << 30;

					memset(&pMob[conn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

					if (pMob[conn].MOB.Clan == 7)
						pMob[conn].MOB.Equip[15].sIndex = 3194;

					else if (pMob[conn].MOB.Clan == 8)
						pMob[conn].MOB.Equip[15].sIndex = 3195;

					else
						pMob[conn].MOB.Equip[15].sIndex = 3196;

					SendItem(conn, ITEM_PLACE_EQUIP, 15, &pMob[conn].MOB.Equip[15]);

					CharLogOut(conn);

					sprintf(temp, "etc,learned limit of soul mortal name:%s conn:%d", pMob[conn].MOB.MobName, conn);
					Log(temp, "-system", 0);

					SendClientSignalParm(conn, ESCENE_FIELD, 948, pUser[conn].Slot);
					return false;
				}

				return false;
			}

			return false;
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cure_failed]);
			return false;
		}

		return false;
	}
#pragma endregion

#pragma region Gabarito npc mode
	// aqui e a npcmode correspondente a case que vc irá definir na continuidade do switch 
	/* OS NPCS DEVEM TER A MERCHANT 96 E STR= FORÇA  INT = INTELIGENCIA

	EXEMPLO: 4 DE FORÇA 4 DE INTELIGENCIA É MERCHANT 96 (SEMPRE ESSA MERCHANT) É O NPC EVENTO 1, É ASSIM VOCÊ  SEGUE ESSA LÓGICA.

	*/ 
#pragma endregion

#pragma region CONFIG NPC MODE

	if (STR == 1 && INT == 1)
		npcMode = 1;

	if (STR == 2 && INT == 2)
		npcMode = 2;

	if (STR == 3 && INT == 3)
		npcMode = 3;

	if (STR == 4 && INT == 4) //NPC 1
		npcMode = 4;
	
	if (STR == 5 && INT == 5) //NPC 2
		npcMode = 5;

	if (STR == 6 && INT == 6) //NPC 3
		npcMode = 6;

	if (STR == 7 && INT == 7) //NPC 4
		npcMode = 7;

	if (STR == 8 && INT == 8) //RECICLADOR
		npcMode = 8;

	if (STR == 9 && INT == 9) //LOOTBOX
		npcMode = 9;

	if (STR == 10 && INT == 10) //UXMAL
		npcMode = 10;

	if (npcMode == -1)
		return true;

#pragma endregion

#pragma region SWITCH NPC MODE

	switch (npcMode)
	{
#pragma region JULLY GELO 1
	case 1:
	{
		if (pMob[conn].MOB.Coin < 1000)
		{
			SendSay(npcIndex, "Gold insuficiente.");
			return false;
		}
		pMob[conn].MOB.Coin -= 1000;
		SendCarry(conn);
		DoTeleport(conn, 3652, 3134, 0);
		SendSay(npcIndex, "Teleportado.");
	} break;
#pragma endregion

#pragma region JULLY GELO 2
	case 2:
	{
		if (pMob[conn].MOB.Coin < 1000)
		{
			SendSay(npcIndex, "Gold insuficiente.");
			return false;
		}
		pMob[conn].MOB.Coin -= 1000;
		SendCarry(conn);
		DoTeleport(conn, 2480, 1649, 0);
		SendSay(npcIndex, "Teleportado.");

	} break;
#pragma endregion 

#pragma region UNICORNIO QUEST INICIANTE
	case 3:
	{
		//if (BASE_GetItemSanc(&pMob[conn].MOB.Equip[6]) != 3)
		///{
		//	SendSay(npcIndex, "É necessário que este item esteja +3.");
		//	return;
		//}

		if (pMob[conn].MOB.Equip[6].sIndex == 917)//Florete
		{

			pMob[conn].MOB.Equip[6].sIndex = 939;//katana
			pMob[conn].MOB.Equip[6].stEffect[1].cEffect = 43;
			pMob[conn].MOB.Equip[6].stEffect[1].cValue = 3;
			pMob[conn].MOB.Equip[6].stEffect[2].cEffect = 2;
			pMob[conn].MOB.Equip[6].stEffect[2].cValue = 45;
			SendSay(npcIndex, "Tome este presente, mas não se acostume a isso...");
			SendItem(conn, ITEM_PLACE_EQUIP, 6, &pMob[conn].MOB.Equip[6]);
			return false;
		}


		if (pMob[conn].MOB.Equip[6].sIndex == 923)//arco de madeira
		{
			pMob[conn].MOB.Equip[6].sIndex = 943; //arco caveira
			pMob[conn].MOB.Equip[6].stEffect[1].cEffect = 43;
			pMob[conn].MOB.Equip[6].stEffect[1].cValue = 3;
			pMob[conn].MOB.Equip[6].stEffect[2].cEffect = 2;
			pMob[conn].MOB.Equip[6].stEffect[2].cValue = 45;
			SendSay(npcIndex, "Tome este presente, mas não se acostume a isso...");
			SendItem(conn, ITEM_PLACE_EQUIP, 6, &pMob[conn].MOB.Equip[6]);
			return false;
		}
		if (pMob[conn].MOB.Equip[6].sIndex == 918)//Lança Mágica
		{
			pMob[conn].MOB.Equip[6].sIndex = 940; //cajado orc
			pMob[conn].MOB.Equip[6].stEffect[1].cEffect = 43;
			pMob[conn].MOB.Equip[6].stEffect[1].cValue = 3;
			pMob[conn].MOB.Equip[6].stEffect[2].cEffect = 60;
			pMob[conn].MOB.Equip[6].stEffect[2].cValue = 20;
			SendSay(npcIndex, "Tome este presente, mas não se acostume a isso...");
			SendItem(conn, ITEM_PLACE_EQUIP, 6, &pMob[conn].MOB.Equip[6]);
			return false;
		}
		if (pMob[conn].MOB.Equip[6].sIndex == 920)//Lança de caça
		{
			pMob[conn].MOB.Equip[6].sIndex = 941;//Foice do mago
			pMob[conn].MOB.Equip[6].stEffect[1].cEffect = 43;
			pMob[conn].MOB.Equip[6].stEffect[1].cValue = 3;
			pMob[conn].MOB.Equip[6].stEffect[2].cEffect = 60;
			pMob[conn].MOB.Equip[6].stEffect[2].cValue = 20;
			SendSay(npcIndex, "Tome este presente, mas não se acostume a isso...");
			SendItem(conn, ITEM_PLACE_EQUIP, 6, &pMob[conn].MOB.Equip[6]);
			return false;
		}
		SendSay(npcIndex, "Se você não trazer a arma corresponde, Não poderia lhe ajudar.");
	} break;
	 
#pragma endregion

#pragma region NPC EVENTO 1
	// NPC DE EVENTO
	case 4:
	{
			auto mob = GetMobFromIndex(conn);
			auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 475, 0);

			if (Item == -1)
			{
				sprintf(temp, "Traga-me o %s para realizar a troca !", g_pItemList[Item].Name);
				SendClientMessage(conn, temp);
				return false;
			}
			srand(time(NULL));
			static uint16_t premio[] = { 413, 412, 4019, 2403, 476 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 5];
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 412)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 4;
			}
			if (itemPut.sIndex == 413)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 2;
			}
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 4019)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 10;
			}
			if (itemPut.sIndex == 2403)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 10;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
			return true;

	}  break;
#pragma endregion

#pragma region NPC EVENTO 2
	case 5:
	{
		auto mob = GetMobFromIndex(conn);
		auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 476, 0);

		std::mt19937 generator;
		generator.seed((unsigned int)std::time(0));
		std::uniform_int_distribution<uint32_t> dice(1, 100);
		int random = dice(generator);

		if (Item == -1)
		{
			sprintf(temp, "Traga-me o %s para realizar a troca !", g_pItemList[Item].Name);
			SendClientMessage(conn, temp);
			return false;
		}

		if (random < 80) {
			srand(time(NULL));
			static uint16_t premio[] = { 4020, 2404, 2399, 4141, 480 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 5];
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 4020)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 2404)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2399)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		if (random >= 80) {
			srand(time(NULL));
			static uint16_t premio[] = { 2441, 2442, 2443, 2444 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 4];
			//aqui vc atribui o efeito ao item

			if (itemPut.sIndex == 2441)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2442)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2443)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2444)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		return true;

	}  break;
#pragma endregion

#pragma region NPC EVENTO 3
	case 6:
	{
		auto mob = GetMobFromIndex(conn);
		auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 480, 0);

		std::mt19937 generator;
		generator.seed((unsigned int)std::time(0));
		std::uniform_int_distribution<uint32_t> dice(1, 100);
		int random = dice(generator);

		if (Item == -1)
		{
			sprintf(temp, "Traga-me o %s para realizar a troca !", g_pItemList[Item].Name);
			SendClientMessage(conn, temp);
			return false;
		}

		if (random < 80) {
			srand(time(NULL));
			static uint16_t premio[] = { 2400, 2405, 2400, 2405, 2400, 2405, 2310, 2315, 1774, 1774, 482, 482 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 12];
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 2400)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 2405)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		if (random >= 80) {
			srand(time(NULL));
			static uint16_t premio[] = { 3397, 3398, 3399, 3400, 3401, 3402, 3403, 3405, 3406 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 9];
			//aqui vc atribui o efeito ao item

			if (itemPut.sIndex == 3397)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3398)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3399)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3400)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3401)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3402)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3403)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3405)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 3406)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		return true;

	}  break;
#pragma endregion

#pragma region NPC EVENTO 4
	case 7:
	{
		auto mob = GetMobFromIndex(conn);
		auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 482, 0);

		std::mt19937 generator;
		generator.seed((unsigned int)std::time(0));
		std::uniform_int_distribution<uint32_t> dice(1, 100);
		int random = dice(generator);

		if (Item == -1)
		{
			sprintf(temp, "Traga-me o %s para realizar a troca !", g_pItemList[Item].Name);
			SendClientMessage(conn, temp);
			return false;
		}

		if (random < 60) {
			srand(time(NULL));
			static uint16_t premio[] = { 4029, 4029, 2406, 2406, 2408 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 5];
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 2406)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 2408)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		if (random < 90) {
			srand(time(NULL));
			static uint16_t premio[] = { 2411, 2412, 2413, 2414 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 4];
			//aqui vc atribui o efeito ao item

			if (itemPut.sIndex == 2411)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2412)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2413)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}
			if (itemPut.sIndex == 2414)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 5;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		if (random >= 90) {
			srand(time(NULL));
			static uint16_t premio[] = { 2316, 2316, 2316, 2318, 2318, 2321, 2321, 2322, 2322, 2323, 2323, 2324, 5455, 5455, 5455 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 15];
			//aqui vc atribui o efeito ao item

			if (itemPut.sIndex == 2316)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}
			if (itemPut.sIndex == 2318)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}
			if (itemPut.sIndex == 2321)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}
			if (itemPut.sIndex == 2322)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}
			if (itemPut.sIndex == 2323)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}
			if (itemPut.sIndex == 2324)
			{
				itemPut.stEffect[0].cEffect = 78;
				itemPut.stEffect[0].cValue = 6;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
		}
		return true;

	}  break;
#pragma endregion

#pragma region UXMAL
	case 10:
	{
		 
		auto mob = GetMobFromIndex(conn);
		auto user = Func::GetUserFromIndex(conn); 

		auto isLeader = [&mob] {
			return mob->Leader <= 0 ? true : false;
		};

		if (!isLeader())
		{
			SendClientMessage(conn, "somente o lider");
			return true;
		}

		if (pUserData[conn].Ingame.PistaRegistro)
		{
			SendSay(kk->npcID, "não foi possivel registrar");
			return true;
		}

		int32_t memberCount = 0;

		Func::executeForParty(conn, [&memberCount](int32_t member) { memberCount++; });

		/*if (memberCount < 4)
		{
		sendSay(conn, Language::instance().getStringFormat(GroupNeedMoreMembers, 4));
		return true;
		}*/

		auto itemSlot = Func::GetFirstSlot(conn, SlotType::Inventory, 5134,0);
		if (itemSlot < 0)
		{
			auto iList = Func::GetItemListItem(5134);
			sprintf(temp, "necessario o %s para se registrar", iList->Name);

			SendClientMessage(conn, temp);
			return true;
		}

		STRUCT_ITEM* item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, (uint16_t)SlotType::Inventory, itemSlot);
		
		if (!item)
			return true;

		/*0 1 2 3 4 5 6*/
		auto level = BASE_GetItemSanc(item);
		if (level > 6)
		{
			SendSay(kk->npcID, "desculpe");
			return true;
		}

		auto success = ClueOfRunesMgr::instance().registerGroup(level, conn);

		if (!success)
		{
			SendSay(kk->npcID,"nao registrador");
			return true;
		}


		sprintf(temp,"[Register] -> Grupo do %s foi registrado na pista + %d", pMob[conn].MOB.MobName, level);
		
		Log(temp, "Log_Pista", 0);

		BASE_ClearItem(&pMob[conn].MOB.Carry[itemSlot]);

		SendItem(conn, (uint16_t)SlotType::Inventory, itemSlot, &pMob[conn].MOB.Carry[itemSlot]);

		printf(temp, " Grupo do %s foi registrado", pMob[conn].MOB.MobName);

		SendSay(kk->npcID,temp);

		pUserData[conn].Ingame.PistaRegistro = true;

		return true;

	} break;
#pragma endregion 

 
	return false; // aqui encerra o switch.
	}
#pragma endregion

}