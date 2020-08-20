#include "stdafx.h"

bool Exec_MSG_Quest(int conn, char* pMsg)
{
	MSG_STANDARDPARM2* m = (MSG_STANDARDPARM2*)pMsg;

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

	if (STR == 1 && INT == 1)
		npcMode = 1;

	if (STR == 2 && INT == 2)
		npcMode = 2;

	if (STR == 3 && INT == 3)
		npcMode = 3;

	if (STR == 4 && INT == 4)
		npcMode = 4;
	
	if (STR == 5 && INT == 5)
		npcMode = 5; 
	// aqui e a npcmode correspondente a case que vc irá definir na continuidade do switch 

	/* OS NPCS DEVEM TER A MERCHANT 96 E STR= FORÇA  INT = INTELIGENCIA
	
	EXEMPLO: 4 DE FORÇA 4 DE INTELIGENCIA É MERCHANT 96 (SEMPRE ESSA MERCHANT) É O NPC EVENTO 1, É ASSIM VOCÊ  SEGUE ESSA LÓGICA.
	
	*/
	//	if (npcMerc == 74)
		//	npcMode = KIBITA; //Depois tem que adicionar a kibita em source...o nativo para de funcionar do nada..

	if (npcMode == -1)
		return true;

#pragma endregion

	switch (npcMode)
	{
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

	case 3:
	{
		//if (BASE_GetItemSanc(&pMob[conn].MOB.Equip[6]) != 3)
		///{
		//	SendSay(npcIndex, "É necessário que este item esteja +3.");
		//	return;
		//}

		if (pMob[conn].MOB.Equip[6].sIndex == 917)//Florete
		{

			pMob[conn].MOB.Equip[6].sIndex = 939;
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
			pMob[conn].MOB.Equip[6].sIndex = 943;
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
			pMob[conn].MOB.Equip[6].sIndex = 940;
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
			pMob[conn].MOB.Equip[6].sIndex = 941;
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
	 

	// NPC DE EVENTO
	case 4:
	{
			auto mob = GetMobFromIndex(conn);
			auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 475, 0);

			if (Item == -1)
			{
				sprintf(temp, "Traga-me o Bau do Tesouro para realizar a troca !", g_pItemList[Item].Name);
				SendClientMessage(conn, temp);
				return false;
			}
			srand(time(NULL));
			static uint16_t premio[] = { 4019, 4019, 4019, 4020, 412, 412, 412, 413, 413, 3314 };

			STRUCT_ITEM itemPut;
			BASE_ClearItem(&itemPut);
			itemPut.sIndex = premio[rand() % 10];
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 412)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 2;
			}
			//aqui vc atribui o efeito ao item
			if (itemPut.sIndex == 4019)
			{
				itemPut.stEffect[0].cEffect = 61;
				itemPut.stEffect[0].cValue = 3;
			}

			Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
			SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
			PutItem(conn, &itemPut);
			SendClientMessage(conn, "Traga-me o item para realizar a troca.");
			return true;

	}  break;

	// NPC EVENTO
	case 5:
	{
		auto Item = Func::GetFirstSlot(conn, SlotType::Inventory, 5441, 0);

		if (Item == -1)
		{
			sprintf(temp, "Traga-me o %s para realizar a troca !", g_pItemList[Item].Name);
			SendClientMessage(conn, temp);
			return false;
		}
		srand(time(NULL));
		static uint16_t premio[] = { 3171, 3171, 3171, 3172, 3172, 3172, 3172, 4128, 4128, 4140, 4140, 777, 777, 3379, 3380, 3348 };

		STRUCT_ITEM itemPut;
		BASE_ClearItem(&itemPut);
		itemPut.sIndex = premio[rand() % 16];
		//aqui vc atribui o efeito ao item
		if (itemPut.sIndex == 3172)
		{
			itemPut.stEffect[0].cEffect = 61;
			itemPut.stEffect[0].cValue = 5;
		}
		//aqui vc atribui o efeito ao item
		if (itemPut.sIndex == 3171)
		{
			itemPut.stEffect[0].cEffect = 61;
			itemPut.stEffect[0].cValue = 5;
		}
		//aqui vc atribui o efeito ao item
		if (itemPut.sIndex == 4140)
		{
			itemPut.stEffect[0].cEffect = 61;
			itemPut.stEffect[0].cValue = 5;
		}
		//aqui vc atribui o efeito ao item
		if (itemPut.sIndex == 777)
		{
			itemPut.stEffect[0].cEffect = 61;
			itemPut.stEffect[0].cValue = 30;
		}


		Func::AmountMinus(&pMob[conn].MOB.Carry[Item]);
		SendItem(conn, (uint16_t)SlotType::Inventory, Item, &pMob[conn].MOB.Carry[Item]);
		PutItem(conn, &itemPut);
		SendClientMessage(conn, "Traga-me o item para realizar a troca.");
		return true;

	} break; 

	return false; // aqui encerra o code do npc evento

	}

	return true;
}