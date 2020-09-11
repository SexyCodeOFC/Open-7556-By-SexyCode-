#include "stdafx.h"

namespace ClueLevel
{

	Lich::Lich()
	{
	}
	Lich::~Lich()
	{
	}

	bool Lich::onGroupRegistered(const uint16_t masterId)
	{
		if (getGroupCount() >= 1)
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

	void Lich::onClueReset()
	{
		if (getGroupCount() == 0)
			return;



		for (int client = 0; client < MAX_USER; client++)
		{
			auto user = Func::GetUserFromIndex(client);
			auto mob = GetMobFromIndex(client);

			auto play = Func::getPlayerinArea({ 3330, 1600 }, { 3451, 1661 });

			if (play.size() > 0)
			{
				for (auto& i : play)
					DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
			}

			auto play2 = Func::getPlayerinArea({ 3330, 1600 }, { 3451, 1661 });

			if (play2.size() > 0)
			{
				for (auto& i : play2)
					DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
			}


		}
		resetGroups();
		killLichAll(true);
	}

	void Lich::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) 
			{

				auto userData = &pUserData[masterId];

				if (idx == 0)
					Func::partyTeleportUxmal(masterId, 3347, 1605, 0);
				//Func::executeForParty(masterId, [&idx](uint16_t member){DoTeleport(member, 3347, 1605, 0); });
				else
					Func::partyTeleportUxmal(masterId, 3406, 1605, 0);
				//Func::executeForParty(masterId, [&idx](uint16_t member){DoTeleport(member, 3406, 1605, 0); });

				sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista de Lich.", GetMobFromIndex(masterId)->MOB.MobName);			
				Log(temp, "Pista-Lich",0);
				idx++;
			});

		 
		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista de Lich %d", getGroupCount());
		Log(temp, "Pista-Lich", 0);

		spawnLichEsq();
		spawnLichDir();
	}

	bool Lich::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		bool containsGroup = false;

		auto mob = GetMobFromIndex(mobId);
		auto play = GetMobFromIndex(masterId);
		auto rnd = Rnd::instance().IRandomX(0, 100);

		if (!strcmp(mob->MOB.MobName, "Lich Infernal"))
		{
			if (rnd >= 25 && rnd <= 32)
			{
				Func::executeForParty(masterId, [](int32_t member) {

					STRUCT_ITEM runas[5] = 
					{
						{ 5110, 0, 0, 0},
						{ 5112, 0, 0, 0},
						{ 5115, 0, 0, 0},
						{ 5113, 0, 0, 0},
						{ 5111, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3330, 1600 }, { 3451, 1661 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});

				Func::sendPistaLider(masterId, { 3330, 1600 }, { 3451, 1661 }, 1);

				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista de Lich lado Direito.", play->MOB.MobName);
				Log(temp, "Pista-Lich", 0);
				killLichAll(true);
				return true;
			}
			killLichEsq(true);
			spawnLichEsq();
			return false;
		}

		if (!strcmp(mob->MOB.MobName, "Lich Infernal "))
		{
			if (rnd >= 25 && rnd <= 32)
			{
				Func::executeForParty(masterId, [](int32_t member) {

					STRUCT_ITEM runas[5] = {
						{ 5110, 0, 0, 0},
						{ 5112, 0, 0, 0},
						{ 5115, 0, 0, 0},
						{ 5113, 0, 0, 0},
						{ 5111, 0, 0, 0},
					};

					if (Func::checkPlayerLiveInArea(member, { 3330, 1600 }, { 3451, 1661 }) == TRUE) PutItem(member, &runas[rand() % 5]);

					});
				Func::sendPistaLider(masterId, { 3330, 1600 }, { 3451, 1661 }, 1);

				sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista de Lich lado Esquerdo.", play->MOB.MobName);
				Log(temp, "Pista-Lich", 0);
				killLichAll(true);
				return true;
			}
			killLichDir(true);
			spawnLichDir();
			return false;
		}
		return false;
	}

	bool Lich::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		bool containsGroup = false;

		return true;
	}

	void Lich::killLichEsq(bool updatePlayerSight)
	{

		auto liveMobs = Func::getMobsInAreaStr({ 3330, 1600 }, { 3390, 1656 }, { 2566 });

		if (liveMobs.size() > 0)
		{
			for (auto& i : liveMobs)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;


			if (updatePlayerSight)
			{
				foreachGroup([&liveMobs](uint16_t groupMaster)
					{ Func::executeForParty(groupMaster,
						[&liveMobs](int32_t member)
						{ for (auto& i : liveMobs)
						DeleteMobPista(member, i, 5, 0);
						});
					});
			}
		}

	}

	void Lich::killLichDir(bool updatePlayerSight)
	{
		auto liveMobs = Func::getMobsInAreaStr({ 3388, 1601 }, { 3451, 1656 }, { 2566 });

		if (liveMobs.size() > 0)
		{
			for (auto& i : liveMobs)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;


			if (updatePlayerSight)
			{
				foreachGroup([&liveMobs](uint16_t groupMaster)
					{ Func::executeForParty(groupMaster,
						[&liveMobs](int32_t member)
						{ for (auto& i : liveMobs)
						DeleteMobPista(member, i, 5, 0);
						});
					});
			}
		}

	}

	void Lich::killLichAll(bool updatePlayerSight)
	{
		// 3451 1645
		auto liveMobs = Func::getMobsInAreaStr({ 3330, 1600 }, { 3451, 1656 }, { 2566 });

		if (liveMobs.size() > 0)
		{
			for (auto& i : liveMobs)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

	}

	void Lich::spawnLichEsq()
	{
		static const STRUCT_POSITION spawn_pos[3] =
		{
			{ 3368, 1634 }, { 3357, 1621 }, { 3355, 1637 },
		};

		auto rnd = Rnd::instance().IRandomX(0, 2);

		for (auto x = 0; x < 7; x++)// esse loop faz a quantidade de Lich
			CreateMobPista("Lich_Infernal", spawn_pos[rnd].X, spawn_pos[rnd].Y, "clue_of_runes/Lich", 0); // Lado Esquerdo

	}

	void Lich::spawnLichDir()
	{
		static const STRUCT_POSITION spawn_pos[3] =
		{
			{ 3423, 1632 }, { 3413, 1623 }, { 3411, 1632 },

		};

		auto rnd = Rnd::instance().IRandomX(0, 2);

		for (auto x = 0; x < 7; x++)// esse loop faz a quantidade de Lich
			CreateMobPista("Lich_Infernal_", spawn_pos[rnd].X, spawn_pos[rnd].Y, "clue_of_runes/Lich", 0); // Lado Direito

	}

	bool Lich::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Lich::onSpawnBoss()
	{

	}

	void Lich::onPlayerTimer()
	{
	}

} // end namespace ClueLevel