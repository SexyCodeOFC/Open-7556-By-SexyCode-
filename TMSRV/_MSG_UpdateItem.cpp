#include "stdafx.h"

bool Exec_MSG_UpdateItem(int conn, char* pMsg)
{
	MSG_UpdateItem* m = (MSG_UpdateItem*)pMsg;

	if (!pMob[conn].MOB.CurrentScore.Hp || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		CharLogOut(conn);

		return false;
	}

	if (m->State < 0 || m->State > 5)
		return false;

	if (m->ItemID < 15000 || m->ItemID >= 15000 + MAX_ITEM)
		return false;

	int GateID = m->ItemID - 15000;
	int GateState = m->State;

	if (GateID < 0 || GateID >= MAX_ITEM)
		return false;

	int State = pItem[GateID].State;
	int State2 = m->State;

	int GateKey = BASE_GetItemAbility(&pItem[GateID].ITEM, EF_KEYID);

	if (State != 3 && State2 != 3)
		goto NoNeedKey;

	if (GateKey == 0)
		goto NoNeedKey;

	int Key = 0;
	int i = 0;

	for (i = 0; i < 60; i++)
	{
		Key = BASE_GetItemAbility(&pMob[conn].MOB.Carry[i], EF_KEYID);

		if (Key == GateKey)
			break;
	}

	if (Key != GateKey)
	{
		if (pItem[GateID].ITEM.sIndex != 773 || pItem[GateID].ITEM.sIndex != 359)
			SendClientMessage(conn, g_pMessageStringTable[_NN_No_Key]);

		return false;
	}

	memset(&pMob[conn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
	SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

NoNeedKey:
	int Height = 0;
	int isUpdate = UpdateItem(GateID, GateState, &Height);

	if (!isUpdate)
		return false;

	m->Height = Height;

	GridMulticast(pItem[GateID].PosX, pItem[GateID].PosY, (MSG_STANDARD*)m, 0);
	return false;
}