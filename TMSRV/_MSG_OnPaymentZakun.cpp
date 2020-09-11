#include "stdafx.h"

bool onPaymentGold(int conn, char* pMsg)
{
	p3D1h* ks = (p3D1h*)pMsg;

	auto mob = GetMobFromIndex(conn);
	int32_t level = -1;

	if (mob->TargetX >= 3332 && mob->TargetY >= 1471 && mob->TargetX <= 3449 && mob->TargetY <= 1529)
		level = 6;

	auto clueLevel = ClueOfRunesFactory::instance().getClueOfRunes(level);

	if (!clueLevel)
		return false;


	return clueLevel->onPaymentGold(conn, ks->aposta / 1000000);
}