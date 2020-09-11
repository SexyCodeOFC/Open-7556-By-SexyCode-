#include "stdafx.h"

bool ClueOfRunesMgr::registerGroup(const uint32_t level, const uint16_t masterId)
{
	using namespace ClueLevel;
	std::time_t now = time(0);
	std::tm when;
	::localtime_s(&when, &now);

	auto min = when.tm_min;

	if ((min >= 16 && min <= 19) || (min >= 36 && min <= 39) || (min >= 56 && min <= 59))
	{
		auto clue = ClueOfRunesFactory::instance().getClueOfRunes(level);
		/*
		Se a pista do level indicado, já tiver registrado o número de grupos máximo
		retorna falso.
		*/
		if (clue->isFull())
			return false;

		/* Registra a pista */
		return clue->onGroupRegistered(masterId);
	}
	return false;
}




void ClueOfRunesMgr::onClueStart()
{
	/* Em cada level, executa a função OnClueStart*/
	for (auto& level : ClueOfRunesFactory::instance().getAllClueLevels())
		level->onClueStart();
}

void ClueOfRunesMgr::onClueReset()
{
	for (auto& level : ClueOfRunesFactory::instance().getAllClueLevels())
		level->onClueReset();
}

void ClueOfRunesMgr::onSpawnBoss()
{
	for (auto& level : ClueOfRunesFactory::instance().getAllClueLevels())
		level->onSpawnBoss();
}
void ClueOfRunesMgr::onPlayerTimer()
{
	for (auto& level : ClueOfRunesFactory::instance().getAllClueLevels())
		level->onPlayerTimer();
}



bool ClueOfRunesMgr::onMobKilled(const int32_t posX, const int32_t posY, const uint16_t mobId, const uint16_t masterId)
{
	int32_t level = -1;

	if (posX >= 3330 && posY >= 1600 && posX <= 3451 && posY <= 1661)
		level = 0;

	if (posX >= 3372 && posY >= 1419 && posX <= 3407 && posY <= 1454)
		level = 2;

	if (posX >= 3333 && posY >= 1029 && posX <= 3448 && posY <= 1144)
		level = 3;

	if (posX >= 3334 && posY >= 1285 && posX <= 3451 && posY <= 1402)
		level = 4;

	if (posX >= 3333 && posY >= 1157 && posX <= 3448 && posY <= 1271)
		level = 5;

	if (posX >= 3332 && posY >= 1471 && posX <= 3449 && posY <= 1529)
		level = 6;

	if (level == -1)
		return false;

	auto clueLevel = ClueOfRunesFactory::instance().getClueOfRunes(level);
	if (!clueLevel)
		return false;

	return clueLevel->onMobKilled(masterId, mobId);
}

bool ClueOfRunesMgr::onMoviment(const int32_t desX, const int32_t desY, const uint16_t masterId)
{
	int32_t level = -1;

	if (desX >= 3372 && desY >= 1419 && desX <= 3407 && desY <= 1454)
		level = 2;

	if (desX >= 3333 && desY >= 1157 && desX <= 3448 && desY <= 1271)
		level = 5;

	if (level == -1)
		return false;

	auto clueLevel = ClueOfRunesFactory::instance().getClueOfRunes(level);
	if (!clueLevel)
		return false;

	return clueLevel->onMovimented(masterId, desX, desY);
}

