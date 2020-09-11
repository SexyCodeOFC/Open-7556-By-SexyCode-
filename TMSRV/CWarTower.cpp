#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <errno.h>

#include "stdafx.h"

void CWarTower::GuildProcess(tm* timeinfo)
{
	if (timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == 21)
	{
		if (wtState == 0 && timeinfo->tm_min < 5)
		{
			SendNotice("Guerra de Torres será iniciada em 5 minutos");
			wtState = 1;
			wtGuildKiller = 0;
			*(int*)0x8C761C0 = 10;
		}

		if (wtState == 1 && timeinfo->tm_min >= 5)
		{
			ClearArea(2445, 1850, 2546, 1920);

			GenerateMob(ENDLESSTOWER, 0, 0);

			SendNotice("Guerra de Torres iniciada!");
			wtState = 2;
		}
	}
}

void CWarTower::ProcessEnd(tm* timeinfo)
{
	//A Guerra acabou a guilda que está defendendo a torre recebe 100 de fama.
	if (wtState == 2 && timeinfo->tm_min == 35 && timeinfo->tm_sec >= 0)
	{
		ClearArea(2445, 1850, 2546, 1920);

		for (int i = MAX_USER; i < MAX_MOB; i++)
		{
			if (pMob[i].GenerateIndex == ENDLESSTOWER)
			{
				if (pMob[i].MOB.Guild == wtGuildKiller)
				{
					int Guild = pMob[i].MOB.Guild;

					char GuildName[12];

					GetGuildName(Guild, GuildName);

					SetGuildFame(Guild, 100);

					char szMsg[96];
					sprintf(szMsg, "Guerra de Torres finalizada! A Guild [%s] foi a vencedora!\n", GuildName);
					SendNotice(szMsg);

					sprintf(temp, "etc,war_tower guild:%s-%d +100 fame\n", GuildName, Guild);
					Log(temp, "-system", 0);
				}
				else
				{
					char szMsg[96];
					sprintf(szMsg, "Guerra de Torres finalizada! Não teve vencedor!");
					SendNotice(szMsg);
				}

				DeleteMob(i, 1);
				memset(&pMob[i], 0, sizeof(CMob));
			}
		}

		wtState = 0;
		wtGuildKiller = 0;
		*(int*)0x8C761C0 = 0;
	}
}

void CWarTower::MobKilled(int target, int conn, int PosX, int PosY)
{
	int GenerateID = pMob[target].GenerateIndex;

	if (GenerateID == ENDLESSTOWER && wtState)
	{
		DeleteGenerateMob(ENDLESSTOWER, 1);
		memset(&pMob[target], 0, sizeof(CMob));

		if (pMob[conn].MOB.Guild)
		{
			char GuildName[12];

			GetGuildName(pMob[conn].MOB.Guild, GuildName);

			char szMsg[96];
			sprintf(szMsg, "A Guild [%s] está agora dominando a torre!", GuildName);
			SendNotice(szMsg);

			wtGuildKiller = pMob[conn].MOB.Guild;
		}

		ClearArea(2445, 1850, 2546, 1920);

		GenerateMob(ENDLESSTOWER, 0, 0);
	}
}

void CWarTower::CGenerateMob(int index, int PosX, int PosY, int tmob)
{
	if (index == ENDLESSTOWER && wtGuildKiller)
	{
		pMob[tmob].MOB.Guild = wtGuildKiller;
		pMob[tmob].MOB.GuildLevel = 0;
	}
}

BOOL CWarTower::TowerAttack(int conn, int idx)
{
	if (pMob[idx].GenerateIndex != ENDLESSTOWER)
		return TRUE;

	if (pMob[conn].MOB.Guild == 0 || pMob[conn].MOB.Guild == pMob[idx].MOB.Guild)
		return FALSE;

	return TRUE;
}