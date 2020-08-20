#include "stdafx.h"

bool Exec_MSG_TradingItem(int conn, char* pMsg)
{
	MSG_TradingItem* m = (MSG_TradingItem*)pMsg;

	if (conn < 0 || conn >= MAX_USER)
		return false;

	if (pUser[conn].Mode != USER_PLAY)
		return false;

	if (sizeof(MSG_TradingItem) != m->Size)
		return false;

	if (m->DestPlace == 0 && m->DestSlot > MAX_EQUIP)// - 1)
		return false;

	if (m->SrcPlace == 0 && m->SrcPlace > MAX_EQUIP)// - 1)
		return false;

	if (m->DestPlace == 1 && m->DestSlot > 60)// - 1)
		return false;

	if (m->SrcPlace == 1 && m->SrcPlace >  60)// - 1)
		return false;

	if (m->DestPlace == 2 && m->DestSlot > MAX_CARGO)// - 1)
		return false;

	if (m->SrcPlace == 2 && m->SrcPlace > MAX_CARGO)// - 1)
		return false;

	if (m->DestPlace < 0 || m->DestPlace > 2 || m->SrcPlace < 0 || m->SrcPlace > 2)
		return false;

	// Teste Anti-DUP
	if (m->SrcPlace == m->DestPlace && m->SrcSlot == m->DestSlot)
		return false;

	if (m->DestPlace == 2 || m->SrcPlace == 2)
	{
		if (pUserData[conn].Ingame.MSG.UseItem.UseJewelBag == TRUE)
			return true;

		int Count = 0;
		int CargoGuard[10];
		int CargoIndex = -1;

		memset(CargoGuard, 0, sizeof(CargoGuard) / 4);

		for (int y = 0; y < 4096; y++)
		{
			for (int x = 0; x < 4096; x++)
			{
				if (pMob[pMobGrid[y][x]].MOB.CurrentScore.Merchant == 2 && Count < 10)
					CargoGuard[Count++] = pMobGrid[y][x];
			}
		}

		for (int i = 0; i < Count; i++)
		{
			if (CargoGuard[i] != 0 && CargoGuard[i] >= MAX_USER && CargoGuard[i] < MAX_MOB)
			{
				if (BASE_GetDistance(pMob[conn].TargetX, pMob[conn].TargetY, pMob[CargoGuard[i]].TargetX, pMob[CargoGuard[i]].TargetY) < 16)
				{
					CargoIndex = CargoGuard[i];
					break;
				}
				else
					continue;
			}
		}

		if (CargoIndex == -1)
		{
			Log("OpenCargo hack detected", pUser[conn].AccountName, pUser[conn].IP);
			return false;
		}


	}

	return true;
}