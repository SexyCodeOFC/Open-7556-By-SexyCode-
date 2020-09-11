#include "stdafx.h"

ClueOfRunesFactory::ClueOfRunesFactory()
	: clueOfRunesMap_()
{
}

ClueLevel::ClueOfRunes* ClueOfRunesFactory::getClueOfRunes(const uint32_t level)
{
	auto it = clueOfRunesMap_.find(level);

	/* Não possui uma instance, retorna cria uma e adiciona no map */
	if (it == clueOfRunesMap_.end())
	{
		ClueLevel::ClueOfRunes* currentLevel = nullptr;


		if (level == 0)
			currentLevel = new ClueLevel::Lich();

		else if (level == 1)
			currentLevel = new ClueLevel::Torre();

		else if (level == 2)
			currentLevel = new ClueLevel::Amon();

		else if (level == 3)
			currentLevel = new ClueLevel::Lobo();

		else if (level == 4)
			currentLevel = new ClueLevel::Labirinto();

		else if (level == 5)
			currentLevel = new ClueLevel::Teleportador();

		else if (level == 6)
			currentLevel = new ClueLevel::Zakum();

		if (currentLevel == nullptr)
			return nullptr;

		clueOfRunesMap_.insert(std::make_pair(level, std::unique_ptr<ClueLevel::ClueOfRunes>(currentLevel)));
	}
	/* Já tem uma instance no map, apenas retorna essa instance. */
	return clueOfRunesMap_[level].get();
}
const std::vector<ClueLevel::ClueOfRunes*> ClueOfRunesFactory::getAllClueLevels() const
{
	auto tmpArray = std::vector<ClueLevel::ClueOfRunes*>();

	for (auto& kvp : clueOfRunesMap_)
		tmpArray.push_back(kvp.second.get());

	return tmpArray;
}

void ClueOfRunesFactory::TimerControl()
{
	time_t rawnow = time(NULL);

	struct tm* now = localtime(&rawnow);
	auto min = now->tm_min;
	auto seg = now->tm_sec;


	ClueOfRunesMgr::instance().onPlayerTimer();

	if (min == 00 || min == 20 || min == 40)
	{
		if (seg >= 0 && seg <= 2)
		{
			ClueOfRunesMgr::instance().onClueStart();
		}
	}

	if (min == 05 || min == 25 || min == 45)
	{
		if (seg >= 0 && seg <= 2)
		{
			ClueOfRunesMgr::instance().onSpawnBoss();
		}
	}

	if (min == 54 || min == 34 || min == 14)
	{
		if (seg >= 30 && seg <= 32)
		{
			ClueOfRunesMgr::instance().onClueReset();
			Func::clearPista();
		}
	}
}