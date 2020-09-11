#include "stdafx.h"

namespace ClueLevel
{
	Labirinto::Labirinto() {}
	Labirinto::~Labirinto() {}

	bool Labirinto::onGroupRegistered(const uint16_t masterId)
	{
		if (getGroupCount() > 1)
			return false;

		bool containsGroup = false;

		foreachGroup([&containsGroup, &masterId](uint16_t otherGroup) {
			if (otherGroup == masterId)
				containsGroup = true;
			});
		if (containsGroup)
			return false;

		addGroup(masterId);
		return true;
	}

	void Labirinto::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) {

			auto userData = &pUserData[masterId];

			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3443, 1395, 0);
			else
				Func::partyTeleportUxmal(masterId, 3443, 1295, 0);

			sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista do Labirinto.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Labirinto", 0);
			idx++;
			});

		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista do Labirinto %d", getGroupCount());
		Log(temp, "Pista-Labirinto", 0);
		spawnMobs();
	}

	void Labirinto::onClueReset()
	{
		if (getGroupCount() == 0)
			return;


		auto play = Func::getPlayerinArea({ 3334, 1285 }, { 3451, 1402 });
		if (play.size() > 0)
		{
			for (auto& i : play)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		auto play2 = Func::getPlayerinArea({ 3334, 1285 }, { 3451, 1402 });
		if (play2.size() > 0)
		{
			for (auto& i : play2)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		clearMobs(true);
		resetGroups();
	}

	void Labirinto::onSpawnBoss()
	{
		return;
	}

	bool Labirinto::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		auto mob = GetMobFromIndex(mobId);

#pragma region Dark_Shadow
		if (!strcmp(mob->MOB.MobName, "Dark Shadow"))
		{
			Func::executeForParty(masterId, [](uint16_t member) {DoTeleport(member, 3359, 1334, 0); });

			if (!Boss) //Caso o Boss já nasceu
			{
				CreateMobPista("Sombra_Negra__", 3351, 1334, "clue_of_runes/Labirinto", 0);
				Boss = true;
			}
			return true;
		}
#pragma endregion

#pragma region Boss_Sombra_Negra
		if (!strcmp(mob->MOB.MobName, "Sombra Negra  "))
		{
			auto rnd = Rnd::instance().IRandomX(0, 100);

			if (rnd <= 45)
			{
				Func::executeForParty(masterId, [](int32_t member) {
					STRUCT_ITEM runas[4] = {
						{ 5125, 0, 0, 0},
						{ 5126, 0, 0, 0},
						{ 5124, 0, 0, 0},
						{ 5127, 0, 0, 0},
					};
					if (Func::checkPlayerLiveInArea(member, { 3334, 1320 }, { 3365, 1349 }) == TRUE) PutItem(member, &runas[rand() % 4]);
					});
				Func::sendPistaLider(masterId, { 3334, 1320 }, { 3365, 1349 }, 5);
				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista ddo Labirinto.", GetMobFromIndex(masterId)->MOB.MobName);
				Log(temp, "Pista-Labirinto", 0);
				return true;
			}

			else
			{
				CreateMobPista("Sombra_Negra__", 3351, 1334, "clue_of_runes/Labirinto", 0);
				return true;
			}
		}
#pragma endregion


		return false;
	}

	bool Labirinto::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		return true;
	}

	void Labirinto::spawnMobs()
	{
		auto mobAll = Func::getMobsInAreaStr({ 3334, 1285 }, { 3451, 1402 }, { 101 });


		if (getGroupCount() == 1)
		{
			if (mobAll.size() == 0) CreateMobPista("Dark_Shadow", 3443, 1379, "clue_of_runes/Labirinto", 0);
		}
		else
		{
			if (mobAll.size() <= 1) CreateMobPista("Dark_Shadow", 3443, 1379, "clue_of_runes/Labirinto", 0);
			if (mobAll.size() <= 1) CreateMobPista("Dark_Shadow", 3444, 1309, "clue_of_runes/Labirinto", 0);
		}

		return;
	}

	void Labirinto::clearMobs(bool updatePlayerSight)
	{
		auto MobsClear = Func::getMobsInArea({ 3334, 1285 }, { 3451, 1402 });

		if (MobsClear.size() > 0)
		{
			for (auto& i : MobsClear)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

		Boss = false;
	}

	bool Labirinto::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Labirinto::onPlayerTimer()
	{
	}
}

