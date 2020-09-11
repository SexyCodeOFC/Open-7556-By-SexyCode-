#include "stdafx.h"

bool Exec_MSG_UseItem(int conn, char* pMsg)
{
	MSG_UseItem* m = (MSG_UseItem*)pMsg;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return false;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return false;
	}

	if (pUser[conn].TradeMode)
	{
		RemoveTrade(conn);
		return false;
	}

	if (pMob[conn].MOB.CurrentScore.Hp == 0)
	{
		SendHpMode(conn);
		//CloseUser(conn);

		if (m->SourType == ITEM_PLACE_CARRY)
			SendItem(conn, m->SourType, m->SourPos, &pMob[conn].MOB.Carry[m->SourPos]); 

		else if (m->SourType == ITEM_PLACE_CARGO)
			SendItem(conn, m->SourType, m->SourPos, &pUser[conn].Cargo[m->SourPos]);
		else
			SendItem(conn, m->SourType, m->SourPos, &pMob[conn].MOB.Equip[m->SourPos]);

		sprintf(temp, "-Movimentação rapida de itens- %d %d", m->SourType, m->SourPos);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		return false;
	}

	if (m->GridX >= MAX_GRIDX || m->GridY >= MAX_GRIDY)
	{
		//CrackLog(conn, "Drop grid, out of range");
		return false;
	}

	STRUCT_ITEM* item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);

	if (item == NULL)
	{
		sprintf(temp, "err,use item fail source %d %d", m->SourType, m->SourPos);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}

	int Vol = BASE_GetItemAbility(item, EF_VOLATILE);
	int amount = BASE_GetItemAmount(item);

	if (item->sIndex >= 490 && item->sIndex < 500)
	{
		SendItem(conn, m->SourType, m->SourPos, item);
		return false;
	}

#pragma region Poção Saúde
	if (Vol == 58)
	{
		int sAffect = GetEmptyAffect(conn, 35);

		if (sAffect == -1)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		if (item->sIndex == 3364) // 7 Dias
		{
			pMob[conn].Affect[sAffect].Type = 35;
			pMob[conn].Affect[sAffect].Level = 1;
			pMob[conn].Affect[sAffect].Value = 0;
			pMob[conn].Affect[sAffect].Time = AFFECT_1D * 7;

			BASE_GetHpMp(&pMob[conn].MOB);
			Func::GetCurrentScore(conn);

			SendScore(conn);

			sprintf(temp, "useitem,item saude");
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return false;
		}
		else if (item->sIndex == 3365) // 15 Dias
		{
			pMob[conn].Affect[sAffect].Type = 35;
			pMob[conn].Affect[sAffect].Level = 1;
			pMob[conn].Affect[sAffect].Value = 0;
			pMob[conn].Affect[sAffect].Time = AFFECT_1D * 15;

			BASE_GetHpMp(&pMob[conn].MOB);
			Func::GetCurrentScore(conn);

			SendScore(conn);

			sprintf(temp, "useitem,item saude");
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return false;
		}
		else if (item->sIndex == 3366) // 30 Dias
		{
			pMob[conn].Affect[sAffect].Type = 35;
			pMob[conn].Affect[sAffect].Level = 1;
			pMob[conn].Affect[sAffect].Value = 0;
			pMob[conn].Affect[sAffect].Time = AFFECT_1D * 30;

			BASE_GetHpMp(&pMob[conn].MOB);
			Func::GetCurrentScore(conn);

			SendScore(conn);

			sprintf(temp, "useitem,item saude");
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return false;
		}

		return false;
	}
#pragma endregion 


#pragma region GameRoom Ticket
	if (item->sIndex == 4111)
	{
		//auto mobinArea = Func::CheckMacUserInArea({ 3604, 3604 }, { 3691, 3690 }, { pUserData[conn].AccountInfo.MacAddress });

		//if (mobinArea.size() > 0)
		//	goto fim;

		if (Func::GetPlayerClass(conn) == Mortal || pMob[conn].MOB.CurrentScore.Level > 999)
		{
			Func::AmountMinus(item);
			SendItem(conn, m->SourType, m->SourPos, item);
			DoTeleport(conn, 3655, 3655, 0);
			return false;
		}
	/*fim:
		SendClientMessage(conn, "Entrada não permitida. (Apenas uma conta)");
		SendItem(conn, m->SourType, m->SourPos, item);
		return false;*/
	}

	// 3732 3563 - 3819 3476
	if (item->sIndex == 4112)
	{
		//auto mobinArea = Func::CheckMacUserInArea({ 3732, 3476 }, { 3819, 3563 }, { pUserData[conn].AccountInfo.MacAddress });

		//if (mobinArea.size() > 0)
		//	goto ending;

		if (Func::GetPlayerClass(conn) == Mortal || pMob[conn].MOB.CurrentScore.Level > 999)
		{
			Func::AmountMinus(item);
			SendItem(conn, m->SourType, m->SourPos, item);
			DoTeleport(conn, 3782, 3525, 0);
			return false;
		}

	/*ending:
		SendClientMessage(conn, "Entrada não permitida. (Apenas uma conta)");
		SendItem(conn, m->SourType, m->SourPos, item);
		return false;*/
	}
	// 3860 3690 - 3946 3604
	if (item->sIndex == 4113)
	{
		//auto mobinArea = Func::CheckMacUserInArea({ 3860, 3604 }, { 3946, 3690 }, { pUserData[conn].AccountInfo.MacAddress });

		//if (mobinArea.size() > 0)
		//	goto fim2;

		if (Func::GetPlayerClass(conn) == God || pMob[conn].MOB.CurrentScore.Level > 999)
		{
			Func::AmountMinus(item);
			SendItem(conn, m->SourType, m->SourPos, item);
			DoTeleport(conn, 3895, 3639, 0);
			return false;
		}
	/*fim2:
		SendClientMessage(conn, "Entrada não permitida. (Apenas uma conta)");
		SendItem(conn, m->SourType, m->SourPos, item);
		return false;*/
	}
#pragma endregion

#pragma region Barra de Mithril

	auto rt = true;
	switch (item->sIndex)
	{
	case 3027:
		rt = HookImpl::BarraMytril_Dano(conn, pMsg);
		break;
	case 3028:
		rt = HookImpl::BarraMytril_AtqMágico(conn, pMsg);
		break;
	case 3029:
		rt = HookImpl::BarraMytril_Defesa(conn, pMsg);
		break;
	case 3030:
		rt = HookImpl::BarraMytril_Crítico(conn, pMsg);
		break;


	default:
		break;
	} 
	 
	if (Vol >= 235 && Vol <= 238)
	{
		STRUCT_ITEM* dest = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestType, m->DestPos);

		if (!dest)
		{
			SendItem(conn, m->SourType, m->SourPos, item);
			SendClientMessage(conn, g_pMessageStringTable[271]);
			return false;
		}

		int ItemAbility = BASE_GetItemAbility(dest, 112);

		if (ItemAbility != 3)
		{
			int Sanc = BASE_GetItemSanc(dest);

			if (Sanc < 11)
			{
				SendClientMessage(conn, g_pMessageStringTable[271]);
				SendItem(conn, m->SourType, m->SourPos, item);
				return false;
			}
		}

		int BaseEffect = 0;

		if (ItemAbility == 1 || ItemAbility == 3)
		{
			switch (Vol)
			{
			case 235:
				BaseEffect = 2;
				break;
			case 236:
				BaseEffect = 60;
				break;
			case 237:
				BaseEffect = 3;
				break;
			case 238:
				BaseEffect = 71;
				break;
			}
		}

		if (BaseEffect == 0)
			return true;

		int ArmorType = BASE_GetItemAbility(dest, 17);

		if (ArmorType != 4 && ArmorType != 8)
		{
			if (ArmorType == 16)
			{
				int ItemType = BASE_GetItemAbility(dest, 87);

				if (ItemType != 5)
				{
					SendClientMessage(conn, g_pMessageStringTable[271]);
					SendItem(conn, m->SourType, m->SourPos, item);
					return false;
				}

				if (BaseEffect == 3)
					BaseEffect = 72;
			}
		}

		bool FindEffect = false;

		for (int i = 0; i < 3; i++)
		{
			if (dest->stEffect[i].cEffect == BaseEffect)
			{
				FindEffect = true;

				if (dest->stEffect[i].cValue > 127 && dest->stEffect[i].cValue < 206) // Locked -50 aditional
				{
					SendClientMessage(conn, g_pMessageStringTable[271]);
					SendItem(conn, m->SourType, m->SourPos, item);
					return false;
				}
			}
		}

		if (!FindEffect)
		{
			SendClientMessage(conn, g_pMessageStringTable[271]);
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		return true;
	}
#pragma endregion

#pragma region Removedor de Tintura
	if (Vol == 186)
	{
		try 
		{

		STRUCT_ITEM *dest = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			Log(temp, "-system", 0);
			return false;
		}

		if (m->DestType || m->DestPos >= 6 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_To_Equips]);
			Log("err,use item fail - dest", pUser[conn].AccountName, pUser[conn].IP);
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		int sanc = BASE_GetItemSanc(dest);

		if (sanc < 1)
		{
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		int color = item->sIndex - 3407;

		//Removedor
		if (color == 10)
		{
			if ((dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
			{
				if ((dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
				{
					if ((dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
					{
						SendClientMessage(conn,"Este item não pode ser mais refinado.");
						SendItem(conn, m->SourType, m->SourPos, item);
						return false;
					}
					dest->stEffect[2].cEffect = 43;
				}
				else
					dest->stEffect[1].cEffect = 43;
			}
			else
				dest->stEffect[0].cEffect = 43;
		}
		else
		{
			if (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect != 43 && (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
			{
				if (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect != 43 && (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
				{
					if (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect != 43 && (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
					{
						SendClientMessage(conn, "Este item não pode ser mais refinado.");
						SendItem(conn, m->SourType, m->SourPos, item);
						return false;
					}
					dest->stEffect[2].cEffect = 116 + color;
				}
				else
					dest->stEffect[1].cEffect = 116 + color;
			}
			else
				dest->stEffect[0].cEffect = 116 + color;
		}

			SendClientMessage(conn, "Refinação bem sucedida.");

		Func::GetCurrentScore(conn);
		SendScore(conn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(conn, m->DestType, m->DestPos, dest);
		SendEmotion(conn, 14, 3);
		}
		catch (...)
		{

		}
		return false;
	}
#pragma endregion

#pragma region Contrato do Reino
	if (item->sIndex >= 3210 && item->sIndex < 3215)
	{
		int Evock = item->sIndex - 3210;
		/*	if (CastleState == 0)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Only_when_castle_war]);
				SendItem(conn, m->SourType, m->SourPos, item);
				return;
			}*/

		GenerateSummon(conn, Evock + 46,0);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		//	sprintf(temp, "useitem,contrato_de_reino evock:%d", Evock + 28);
			//ItemLog(temp, pUser[conn].AccountName, pUser[conn].IP);
		return false;
	}
#pragma endregion

#pragma region Bônus PVM e EXP
	if (item->sIndex == 3394)
	{
		int sAffect = GetEmptyAffect(conn, 39);

		if (pMob[conn].Affect[sAffect].Type == 39)
		{
			SendClientMessage(conn, "Você já possui um bônus de ExP ativo.");
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		pMob[conn].Affect[sAffect].Type = 39;
		pMob[conn].Affect[sAffect].Level = 0;
		pMob[conn].Affect[sAffect].Value = 0;
		pMob[conn].Affect[sAffect].Time += AFFECT_1H/2;

		if (pMob[conn].Affect[sAffect].Time >= 324000)
			pMob[conn].Affect[sAffect].Time = 324000;

		Func::GetCurrentScore(conn);
		SendScore(conn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return false;
	}

	if (item->sIndex == 3395)
	{
		int sAffect = GetEmptyAffect(conn, 30);

		if (pMob[conn].Affect[sAffect].Type == 30)
		{
			SendClientMessage(conn, "Você já possui um bônus de PvM ativo.");
			SendItem(conn, m->SourType, m->SourPos, item);
			return false;
		}

		pMob[conn].Affect[sAffect].Type = 30;
		pMob[conn].Affect[sAffect].Level = 2;
		pMob[conn].Affect[sAffect].Value = 30;
		pMob[conn].Affect[sAffect].Time += AFFECT_1H/2;

		if (pMob[conn].Affect[sAffect].Time >= 324000)
			pMob[conn].Affect[sAffect].Time = 324000;

		Func::GetCurrentScore(conn);
		SendScore(conn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return false;
	}
#pragma endregion	

#pragma region Extrações

	if (item->sIndex == 3021)
	{
		HookImpl::ExtraElmo(conn, pMsg);
		return false;
	}
	if (item->sIndex == 3022)
	{
		HookImpl::ExtraPeito(conn, pMsg);
		return false;
	}
	if (item->sIndex == 3023)
	{
		HookImpl::ExtraCalça(conn, pMsg);
		return false;
	}
	if (item->sIndex == 3024)
	{
		HookImpl::ExtraLuva(conn, pMsg);
		return false;
	}
	if (item->sIndex == 3025)
	{
		HookImpl::ExtraBota(conn, pMsg);
		return false;
	}
	if (item->sIndex == 3026)
	{
		HookImpl::ExtraArma(conn, pMsg);
		return false;
	}
#pragma endregion

#pragma region Jóia de Cargo
	if (Vol == 243)
	{
		if (item->sIndex == 3207)
		{
			pUserData[conn].Ingame.MSG.UseItem.UseJewelBag = TRUE;// usar variavel semelhante a essa para verificação dragao noatun depois.
			return false;
		}
	}
#pragma endregion

	if (m->SourType == ITEM_PLACE_CARRY)
	{
#pragma region VOLATILES USADAS NO INVENTÁRIO
		int invitem = pMob[conn].MOB.Carry[m->SourPos].sIndex;
		
		 if (pMob[conn].MOB.Carry[m->SourPos].sIndex == 413) return  HookImpl::FixRefItemCele(conn, pMsg);

#pragma endregion		
	}  

	if (pMob[conn].MOB.Carry[m->SourPos].sIndex >= 777 && pMob[conn].MOB.Carry[m->SourPos].sIndex <= 785 ||
		pMob[conn].MOB.Carry[m->SourPos].sIndex >= 3173 && pMob[conn].MOB.Carry[m->SourPos].sIndex <= 3190)
	{

		SendCarry(conn);
	}

	return true;
}


