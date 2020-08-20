#include "stdafx.h"
#include "ProcessClientMessage.h"
#include "Functions.h"

void Exec_MSG_DropItem(int conn, char* pMsg)
{
	char temp[4096];

	MSG_DropItem* m = (MSG_DropItem*)pMsg;

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

	if (m->GridX >= 4096 || m->GridY >= 4096)
	{
		sprintf(temp, "err,wrong drop pos %d %d", m->GridX, m->GridY);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int gridx = m->GridX;
	int gridy = m->GridY;

	int titem = GetEmptyItemGrid(&gridx, &gridy);

	m->GridX = gridx;
	m->GridY = gridy;

	if (titem == 0)
	{
		SendClientMessage(conn, "Não há mais espaço.");
		return;
	}

	if (m->SourType == 0)
	{
		Log("err,dropitem - sourtype", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (m->SourType)
	{
		if (m->SourType == 1)
		{
			if (m->SourPos < 0 || m->SourPos >= 64)
			{
				Log("err,dropitem - carry equip", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->SourType != 2)
			{
				Log("err,dropitem - sourtype", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->SourPos < 0 || m->SourPos >= 128)
			{
				Log("err,dropitem - sourpos cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
	}

	STRUCT_ITEM* SrcItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM* BackupItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);


	if (SrcItem == NULL || BackupItem == NULL)
		return;

	if (SrcItem->sIndex <= 0 || SrcItem->sIndex >= MAX_ITEMLIST)
		return;

	if (SrcItem->sIndex != 508 && SrcItem->sIndex != 509 && SrcItem->sIndex != 522
		&& (SrcItem->sIndex < 526 || SrcItem->sIndex > 537) && SrcItem->sIndex != 446
		&& SrcItem->sIndex != 747 && SrcItem->sIndex != 3993 && SrcItem->sIndex != 3994 && SrcItem->sIndex != 3394 && SrcItem->sIndex != 3395 && SrcItem->sIndex != 3980)
	{
		int drop = CreateItem(m->GridX, m->GridY, SrcItem, m->Rotate, 1, 0);

		if (drop <= 0 || drop >= 5000)
		{
			SendClientMessage(conn, "Can't create object(item)");
			return;
		}

		//char tmplog[2048];
		//BASE_GetItemCode(SrcItem, tmplog);
		//sprintf(temp, "dropitem, %s", tmplog);
		//ItemLog(temp, pUser[conn].AccountName, pUser[conn].IP);

		memset(SrcItem, 0, sizeof(STRUCT_ITEM));

		MSG_CNFDropItem sm_ditem;
		memset(&sm_ditem, 0, sizeof(MSG_CNFDropItem));

		sm_ditem.Type = 0x175;
		sm_ditem.Size = sizeof(MSG_CNFDropItem);

		sm_ditem.SourType = m->SourType;
		sm_ditem.SourPos = m->SourPos;
		sm_ditem.Rotate = m->Rotate;
		sm_ditem.GridX = m->GridX;
		sm_ditem.GridY = m->GridY;

		Func::SendPacket(conn, (uint8_t*)&sm_ditem, sizeof(MSG_CNFDropItem));
	}
	else
	{
		SendClientMessage(conn, "Este item não pode ser descartado.");
		return;
	}
}