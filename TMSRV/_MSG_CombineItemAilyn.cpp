#include "stdafx.h"

bool Exec_MSG_CombineItemAilyn(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	for (int i = 0; i < 8; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		int invPos = m->InvenPos[i];

		if (invPos < 0 || invPos >= 60 - 1)
		{
			RemoveTrade(conn);
			return false;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			SendClientSignalParm(conn, ESCENE_FIELD, 935, 0);
			return false;
		}
	}

	if (pMob[conn].MOB.Coin < 50000000)
	{
		sprintf(temp, g_pMessageStringTable[_DN_D_Cost], 50000000);
		SendClientMessage(conn, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, 935, 0);
		return false;
	}

	if (pMob[conn].MOB.Coin < 50000000)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, 935, 0);
		return false;
	}

	int combine = GetMatchCombineAilyn(m->Item);

	if (combine == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);

		SendClientSignalParm(conn, ESCENE_FIELD, 935, 0);
		return false;
	}

	for (int i = 2; i < 8; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	//SendEtc(conn);

	for (int i = 0; i < 8; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];

			BASE_GetItemCode(&m->Item[i], itemlog);

			strcat(temp, itemlog);
		}
	}

	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	int zrand = rand() % 115;
	if (zrand >= 100)
		zrand -= 15;

	int ipos1 = 0;
	int ipos2 = 0;


	if (_rand <= combine)
	{
		ipos1 = m->InvenPos[0];
		ipos2 = m->InvenPos[1];

		if (pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect == pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect)
		{
			sprintf(temp, "%s - Compos [%d %d:%d:%d:%d] com [%d %d:%d:%d:%d] no NPC Aylin.\n", pMob[conn].MOB.MobName, pMob[conn].MOB.Carry[ipos1].sIndex, pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect,
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect, pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue, pMob[conn].MOB.Carry[ipos2].sIndex,
				pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect, pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect, pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue);
			Log("-system", temp, pUser[conn].IP);

			if (zrand <= 25)
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
			}
			else if (zrand <= 50)
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
			}
			else if (zrand <= 75)
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
			}
			else
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
			}
		}
		else
		{
			sprintf(temp, "%s - Compos [%d %d:%d:%d:%d] com [%d %d:%d:%d:%d] no NPC Aylin.\n", pMob[conn].MOB.MobName, pMob[conn].MOB.Carry[ipos1].sIndex, pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect,
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect, pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue, pMob[conn].MOB.Carry[ipos2].sIndex,
				pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect, pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect, pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue);
			Log("-system", temp, pUser[conn].IP);

			if (zrand <= 50)
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
			}
			else
			{
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
				pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
			}
		}


		BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos1], 10, m->Item[3].sIndex - 2441);

		memset(&pMob[conn].MOB.Carry[ipos2], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, ipos2, &pMob[conn].MOB.Carry[ipos2]);

		pMob[conn].MOB.Coin -= 50000000;

		SendEtc(conn);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, 935, 1);

		char tt[512];

		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos1], tt);
		strcat(temp, tt);

		SendItem(conn, ITEM_PLACE_CARRY, ipos1, &pMob[conn].MOB.Carry[ipos1]);

		return false;
	}
	else
	{
		sprintf(temp, "%s", g_pMessageStringTable[_NN_CombineFailed]);
		SendClientMessage(conn, temp);

		pMob[conn].MOB.Coin -= 50000000;
		SendEtc(conn);

		SendClientSignalParm(conn, ESCENE_FIELD, 935, 2);

		return false;
	}
}