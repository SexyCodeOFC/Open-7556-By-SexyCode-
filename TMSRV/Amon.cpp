#include "stdafx.h"

namespace ClueLevel
{
	Amon::Amon()
	{
	}
	Amon::~Amon()
	{
	}

	bool Amon::onGroupRegistered(const uint16_t masterId)
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

	void Amon::onClueReset()
	{
		if (getGroupCount() == 0)
			return;

		auto playinArea = Func::getPlayerinArea({ 3340, 1412 }, { 3449, 1463 });
		if (playinArea.size() > 0)
		{
			for (auto& i : playinArea)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}

		clearBossAmon(true);
		resetGroups();
	}

	void Amon::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) {
			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3359, 1439, 0);

			else
				Func::partyTeleportUxmal(masterId, 3424, 1443, 0);
			 
			sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista dos Amons.\n", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Amon", 0);

			idx++;
			});

		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista dos Amons %d\n", getGroupCount());
		Log(temp, "Pista-Amon", 0);

		auto liveMobs = Func::getMobsInArea({ 3372, 1419 }, { 3407, 1454 });

		for (auto& i : liveMobs)
			GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
	}

	bool Amon::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		bool containsGroup = false;
		auto mob = GetMobFromIndex(mobId);

		if (!strcmp(mob->MOB.MobName, "Valquiria"))
		{
			Func::executeForParty(masterId, [](int32_t member) {

				STRUCT_ITEM runas[6] = {
					{ 5118, 0, 0, 0},
					{ 5121, 0, 0, 0},
					{ 5122, 0, 0, 0},
					{ 5116, 0, 0, 0},
					{ 5130, 0, 0, 0},
					{ 5119, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3340, 1412 }, { 3449, 1463 }) == TRUE) PutItem(member, &runas[rand() % 6]);

				});

			Func::sendPistaLider(masterId, { 3340, 1412 }, { 3449, 1463 }, 3);
			 
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista dos Amons.\n", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp,"Pista-Amon", 0);
			return true;

		}
		return false;
	}

	bool Amon::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		bool containsGroup = false;

		auto liveMobs = Func::getMobsInAreaStr({ 3372, 1419 }, { 3407, 1454 }, { 1257 });
		auto mob = GetMobFromIndex(masterId);

		if (liveMobs.size() == 1)
		{
			auto isLeader = [&mob] {
				return mob->Leader <= 0 ? true : false;
			};

			if (!isLeader())
			{
				DoTeleport(masterId, 3368, 1452, 0);
				return true;
			}
		}

		return true;
	}

	void Amon::clearBossAmon(bool updatePlayerSight)
	{
		// 3451 1645
		auto liveMobs = Func::getMobsInAreaStr({ 3372, 1419 }, { 3407, 1454 }, { 1257 });

		if (liveMobs.size() > 0)
		{
			for (auto& i : liveMobs)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

	}

	void Amon::onSpawnBoss()
	{
		auto Boss = Func::getMobsInAreaStr({ 3340, 1412 }, { 3449, 1463 }, { 1257 });

		if (Boss.size() > 0) return;

		CreateMobPista("Valquiria", 3390, 1438, "clue_of_runes/Agmon", 0); // um teste apenas
		sprintf(temp, "[Boss] -> Valquiria Nasceu no Templo do Gelo.\n");
		Log(temp, "Pista-Amon", 0);
	}

	bool Amon::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Amon::onPlayerTimer()
	{
	}
}