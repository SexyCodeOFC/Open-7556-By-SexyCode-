#include "stdafx.h"
#include "ProcessClientMessage.h"
#include "Functions.h"

void Exec_MSG_GetItem(int conn, char* pMsg)
{
	char temp[4096];

	MSG_GetItem* m = (MSG_GetItem*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
	{
		CharLogOut(conn);
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		SendClientMessage(conn, "Não é possível durante a auto venda.");
		return;
	}

	if (m->DestType != 1)
	{
		Log("DEBUG:GetItem with wrong desttype", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int itemID = m->ItemID - 15000;

	if (itemID <= 0 || itemID >= 5000)
		return;

	if (itemID <= 0 || itemID >= 5000 || pItem[itemID].Mode == 0)
	{
		if (pItem[itemID].Mode)
		{
			sprintf(temp, "GetItemFail idx:%d mode:%d", itemID, pItem[itemID].Mode);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		}

		MSG_DecayItem sm_deci;
		memset(&sm_deci, 0, sizeof(MSG_DecayItem));

		sm_deci.Type = 0x16F;
		sm_deci.Size = sizeof(MSG_DecayItem);
		sm_deci.ID = 30000;
		sm_deci.ItemID = m->ItemID;
		sm_deci.unk = 0;
		Func::SendAddPacket(conn, (uint8_t*)&sm_deci, sizeof(MSG_DecayItem));
		return;
	}

	if (pMob[conn].TargetX < pItem[itemID].PosX - 3 || pMob[conn].TargetY < pItem[itemID].PosY - 3
		|| pMob[conn].TargetX > pItem[itemID].PosX + 3 || pMob[conn].TargetY > pItem[itemID].PosY + 3)
	{
		sprintf(temp, "GetItemFail posx:%d posx:%d tx:%d ty:%d", pItem[itemID].PosX, pItem[itemID].PosY,
			pMob[conn].TargetX, pMob[conn].TargetY);

		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (itemID == 1727 && pMob[conn].MOB.CurrentScore.Level < 1000)
		return;

	STRUCT_ITEM* ditem = &pItem[itemID].ITEM;
	int sIndex = ditem->sIndex;

	if (sIndex <= 0 || sIndex >= MAX_ITEMLIST)
		return;

	if (ditem->sIndex == 470)
	{
		/*if (pMob[conn].extra.QuestInfo.Mortal.PilulaOrc)
		{
			BASE_GetLanguage(temp, _NN_Youve_Done_It_Already);
			SendClientMessage(conn, temp);
		}
		else*/
		{
			SendClientMessage(conn, "Quest: Seu ponto de skill aumentou por 9.");

			//pMob[conn].extra.QuestInfo.Mortal.PilulaOrc = 1;
			BASE_ClearItem(ditem);

			pItemGrid[pItem[itemID].PosY][pItem[itemID].PosX] = 0;
			pItem[itemID].Mode = 0;

			MSG_DecayItem sm_deci;
			memset(&sm_deci, 0, sizeof(MSG_DecayItem));

			sm_deci.Type = 0x16F;
			sm_deci.Size = sizeof(MSG_DecayItem);
			sm_deci.ID = 30000;
			sm_deci.ItemID = m->ItemID;
			sm_deci.unk = 0;
			GridMulticast(pItem[itemID].PosX, pItem[itemID].PosY, (MSG_STANDARD*)&sm_deci, 0);

			pMob[conn].MOB.SkillBonus += 9;

			SendEmotion(conn, 14, 3);
			SendEtc(conn);
		}
		return;
	}

	/*if (sIndex >= 490 && sIndex < 500)
	{
		sprintf(temp, "%s ganha %s-%s", pMob[conn].MOB.MobName, g_pItemList[sIndex].Name, "");
		SendNotice(temp);

		MSG_DecayItem sm_deci;
		memset(&sm_deci, 0, sizeof(MSG_DecayItem));

		sm_deci.Type = 0x16F;
		sm_deci.Size = sizeof(MSG_DecayItem);
		sm_deci.ID = 30000;
		sm_deci.ItemID = m->ItemID;
		sm_deci.unk = 0;
		GridMulticast(pItem[itemID].PosX, pItem[itemID].PosY, (MSG_STANDARD*)&sm_deci, 0);
	}*/

	int itemX = pItem[itemID].PosX;
	int itemY = pItem[itemID].PosY;

	MSG_DecayItem sm_deci;
	memset(&sm_deci, 0, sizeof(MSG_DecayItem));

	sm_deci.Type = 0x16F;
	sm_deci.Size = sizeof(MSG_DecayItem);
	sm_deci.ID = 30000;
	sm_deci.ItemID = m->ItemID;
	sm_deci.unk = 0;

	if (itemX < 0 || itemX >= 4096 || itemY <= 0 || itemY >= 4096)
	{
		Func::SendAddPacket(conn, (uint8_t*)&sm_deci, sizeof(MSG_DecayItem));
		pItem[itemID].Mode = 0;
		return;
	}

	if (pItemGrid[itemY][itemX] != itemID)
	{
		Func::SendAddPacket(conn, (uint8_t*)&sm_deci, sizeof(MSG_DecayItem));

		if (!pItemGrid[itemY][itemX])
			pItemGrid[itemY][itemX] = itemID;

		return;
	}

	if (itemX != m->GridX || itemY != m->GridY)
	{
		Func::SendAddPacket(conn, (uint8_t*)&sm_deci, sizeof(MSG_DecayItem));
		return;
	}

	int Vol = BASE_GetItemAbility(ditem, EF_VOLATILE);

	if (Vol == 2)
	{
		int HWORDCOIN = BASE_GetItemAbility((STRUCT_ITEM*)ditem, EF_HWORDCOIN);
		int coin1 = HWORDCOIN << 8;

		HWORDCOIN = BASE_GetItemAbility((STRUCT_ITEM*)ditem, EF_LWORDCOIN);

		coin1 += HWORDCOIN;
		int tcoin = coin1 + pMob[conn].MOB.Coin;

		if (tcoin >= 2000000000)
		{
			SendClientMessage(conn, "Não é possível armazenar mais que 2 bilhões de Gold.");
			return;
		}
		pMob[conn].MOB.Coin += coin1;

		Func::SendAddPacket(conn, (uint8_t*)&sm_deci, sizeof(MSG_DecayItem));

		BASE_ClearItem(ditem);
	}
	else
	{
		if (m->DestPos < 0 || m->DestPos >= 64)
		{
			Log("DEBUG:Trading Fails.(Wrong source position)", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		STRUCT_ITEM* bItem = &pMob[conn].MOB.Carry[m->DestPos];

		int error = -2;
		int can = bItem->sIndex == 0 ? 1 : 0;

		if (can == 0)
		{
			if (m->DestPos > 0 && m->DestPos <= 64)
			{
				m->DestPos--;
				SendItem(conn, 1, m->DestPos, &pMob[conn].MOB.Carry[m->DestPos]);
			}
			return;
		}
		memcpy(bItem, ditem, sizeof(STRUCT_ITEM));

		//char itemLog[2048];
		//BASE_GetItemCode(bItem, itemLog);
		//sprintf(temp, "getitem, %s", itemLog);
		//ItemLog(temp, pUser[conn].AccountName, pUser[conn].IP);
	}

	MSG_CNFGetItem cnfGet;
	memset(&cnfGet, 0, sizeof(MSG_CNFGetItem));

	cnfGet.Type = 0x171;
	cnfGet.Size = sizeof(MSG_CNFGetItem);
	cnfGet.ID = 30000;

	cnfGet.DestPos = m->DestPos;
	cnfGet.DestType = m->DestType;

	Func::SendAddPacket(conn, (uint8_t*)&cnfGet, sizeof(MSG_CNFGetItem));

	GridMulticast(itemX, itemY, (MSG_STANDARD*)&sm_deci, 0);

	pItemGrid[itemY][itemX] = 0;
	pItem[itemID].Mode = 0;

	SendItem(conn, 1, m->DestPos, &pMob[conn].MOB.Carry[m->DestPos]);
}