#include "stdafx.h"

namespace ClueLevel
{
	Lobo::Lobo() {}
	Lobo::~Lobo() {}

	bool Lobo::onGroupRegistered(const uint16_t masterId)
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

	void Lobo::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) {

			auto userData = &pUserData[masterId];

			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3375, 1094, 0);

			else
				Func::partyTeleportUxmal(masterId, 3407, 1085, 0);

			sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista dos Lobos.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Lobo", 0);
			idx++;
			});

		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista dos Lobos %d", getGroupCount());
		Log(temp, "Pista-Lobo", 0);
	 }

	void Lobo::onClueReset()
	{
		if (getGroupCount() == 0)
			return;



		if (getGroupCount() > 1)
		{
			int leaderOne = getMaster(0),
				leaderTwo = getMaster(1),
				countOne = getKillsCount(leaderOne),
				countTwo = getKillsCount(leaderTwo);

			if (countOne > 0 && countOne > countTwo)
			{

				Func::executeForParty(leaderOne, [](int32_t member) {

					static STRUCT_ITEM runas[5] =
					{
						{ 5119, 0, 0, 0},
						{ 5126, 0, 0, 0},
						{ 5121, 0, 0, 0},
						{ 5116, 0, 0, 0},
						{ 5122, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3333, 1029 }, { 3448, 1144 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});

				Func::sendPistaLider(leaderOne, { 3333, 1029 }, { 3448, 1144 }, 4);
				 
				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista dos Lobos Quantidade de Boss Mortos %d .", GetMobFromIndex(leaderOne)->MOB.MobName, countOne);
				Log(temp, "Pista-Lobo", 0);
			
			}

			if (countTwo > 0 && countTwo > countOne)
			{

				Func::executeForParty(leaderTwo, [](int32_t member) {

					static STRUCT_ITEM runas[5] =
					{
						{ 5119, 0, 0, 0},
						{ 5126, 0, 0, 0},
						{ 5121, 0, 0, 0},
						{ 5116, 0, 0, 0},
						{ 5122, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3333, 1029 }, { 3448, 1144 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});
				Func::sendPistaLider(leaderTwo, { 3333, 1029 }, { 3448, 1144 }, 4);
 
				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista dos Lobos Quantidade de Boss Mortos %d .", GetMobFromIndex(leaderTwo)->MOB.MobName, leaderTwo);
				Log(temp, "Pista-Lobo", 0);
			}

			if (countTwo > 0 && countTwo == countOne) // Empate
			{
				int LeaderId = getMaster(rand() % 1);

				Func::executeForParty(LeaderId, [](int32_t member) {

					static STRUCT_ITEM runas[5] =
					{
						{ 5119, 0, 0, 0},
						{ 5126, 0, 0, 0},
						{ 5121, 0, 0, 0},
						{ 5116, 0, 0, 0},
						{ 5122, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3333, 1029 }, { 3448, 1144 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});

				Func::sendPistaLider(LeaderId, { 3333, 1029 }, { 3448, 1144 }, 4);

				 
				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista dos Lobos Empate .", GetMobFromIndex(LeaderId)->MOB.MobName);
				Log(temp, "Pista-Lobo", 0);
			
			}
		}
		else
		{
			int leaderOne = getMaster(0),
				countOne = getKillsCount(leaderOne);

			if (countOne > 0)
			{

				Func::executeForParty(leaderOne, [](int32_t member) {

					static STRUCT_ITEM runas[5] =
					{
						{ 5119, 0, 0, 0},
						{ 5126, 0, 0, 0},
						{ 5121, 0, 0, 0},
						{ 5116, 0, 0, 0},
						{ 5122, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3333, 1029 }, { 3448, 1144 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});
				Func::sendPistaLider(leaderOne, { 3333, 1029 }, { 3448, 1144 }, 4);

				 
				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista dos Lobos Quantidade de Boss Mortos %d .", GetMobFromIndex(leaderOne)->MOB.MobName, countOne);
				Log(temp, "Pista-Lobo", 0);
			
			}
		}

		auto play = Func::getPlayerinArea({ 3333, 1029 }, { 3448, 1144 });
		if (play.size() > 0)
		{
			for (auto& i : play)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		auto play2 = Func::getPlayerinArea({ 3333, 1029 }, { 3448, 1144 });
		if (play2.size() > 0)
		{
			for (auto& i : play2)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		clearDarkShadow(true);
		resetGroups();
	}

	void Lobo::onSpawnBoss()
	{

	}

	bool Lobo::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		auto mob = GetMobFromIndex(mobId);

		if (!strcmp(mob->MOB.MobName, "Sulrang"))
		{
			auto checkDarkShadow = Func::getMobsInAreaStr({ 3333, 1029 }, { 3448, 1144 }, { 1774 });

			if (checkDarkShadow.size() == 0) spawnDarkShadow();

			return true;
		}
		if (!strcmp(mob->MOB.MobName, "Sombra Negra "))
		{
			incrimentKillCount(masterId);
			return true;
		}

		return false;
	}

	bool Lobo::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		return true;
	}

	void Lobo::spawnDarkShadow()
	{
		static const STRUCT_POSITION spawn_pos[] =
		{
			{ 3355, 1052 }, { 3347, 1088 }, { 3357, 1121 }, { 3391, 1132 },
			{ 3425, 1122 }, { 3434, 1088 }, { 3422, 1051 }, { 3391, 1043 },
		};

		auto rnd = Rnd::instance().IRandomX(0, 7);

		CreateMobPista("Sombra_Negra_", spawn_pos[rnd].X, spawn_pos[rnd].Y, "clue_of_runes/Lobo", 0);
	}

	void Lobo::clearDarkShadow(bool updatePlayerSight)
	{
		auto checkDarkShadow = Func::getMobsInAreaStr({ 3333, 1029 }, { 3448, 1144 }, { 1774 });

		if (checkDarkShadow.size() > 0)
		{
			for (auto& i : checkDarkShadow)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

	}

	bool Lobo::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Lobo::onPlayerTimer()
	{
	}

}
