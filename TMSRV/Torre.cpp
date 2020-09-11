#include "stdafx.h"

namespace ClueLevel
{
	Torre::Torre()
	{
	}
	Torre::~Torre()
	{
	}

	bool Torre::onGroupRegistered(const uint16_t masterId)
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

	void Torre::onClueReset()
	{
		if (getGroupCount() == 0)
			return;

		auto playinArea = Func::getPlayerinArea({ 3338, 1545 }, { 3444, 1591 });

		auto torre1 = Func::getMobsInAreaStr({ 3382, 1546 }, { 3390, 1551 }, { 1255 });
		auto torre2 = Func::getMobsInAreaStr({ 3415, 1580 }, { 3422, 1586 }, { 1255 });

		if (torre1.size() == 1 && torre2.size() == 1) // empate
		{
			int LeaderId = getMaster(0);
			Func::executeForParty(LeaderId, [](int32_t member) {

				static STRUCT_ITEM runas[6] = {
					{ 5114, 0, 0, 0},
					{ 5113, 0, 0, 0},
					{ 5117, 0, 0, 0},
					{ 5111, 0, 0, 0},
					{ 5115, 0, 0, 0},
					{ 5112, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3338, 1545 }, { 3444, 1591 }) == TRUE) PutItem(member, &runas[rand() % 6]);

				});
			Func::sendPistaLider(LeaderId, { 3338, 1545 }, { 3444, 1591 }, 2);
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista das Torres.", GetMobFromIndex(LeaderId)->MOB.MobName);
			Log(temp, "Pista-Torre",0);

			int LeaderId2 = getMaster(1);
			Func::executeForParty(LeaderId2, [](int32_t member) {

				static STRUCT_ITEM runas[6] = {
					{ 5114, 0, 0, 0},
					{ 5113, 0, 0, 0},
					{ 5117, 0, 0, 0},
					{ 5111, 0, 0, 0},
					{ 5115, 0, 0, 0},
					{ 5112, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3338, 1545 }, { 3444, 1591 }) == TRUE) PutItem(member, &runas[rand() % 6]);

				});
			Func::sendPistaLider(LeaderId2, { 3338, 1545 }, { 3444, 1591 }, 2);
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista das Torres.", GetMobFromIndex(LeaderId2)->MOB.MobName);
			Log(temp, "Pista-Torre",0);
		
		}

		if (torre1.size() == 1 && torre2.size() == 0) // Grupo 1
		{
			int LeaderId = getMaster(0);
			Func::executeForParty(LeaderId, [](int32_t member) {

				static STRUCT_ITEM runas[6] = {
					{ 5114, 0, 0, 0},
					{ 5113, 0, 0, 0},
					{ 5117, 0, 0, 0},
					{ 5111, 0, 0, 0},
					{ 5115, 0, 0, 0},
					{ 5112, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3338, 1545 }, { 3444, 1591 }) == TRUE) PutItem(member, &runas[rand() % 6]);

				});
			Func::sendPistaLider(LeaderId, { 3338, 1545 }, { 3444, 1591 }, 2);
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista das Torres.", GetMobFromIndex(LeaderId)->MOB.MobName);
			Log(temp, "Pista-Torre", 0);
		
		}
		if (torre2.size() == 1 && torre1.size() == 0) // Grupo 2
		{
			int LeaderId = getMaster(1);
			Func::executeForParty(LeaderId, [](int32_t member) {

				static STRUCT_ITEM runas[6] = {
					{ 5114, 0, 0, 0},
					{ 5113, 0, 0, 0},
					{ 5117, 0, 0, 0},
					{ 5111, 0, 0, 0},
					{ 5115, 0, 0, 0},
					{ 5112, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3338, 1545 }, { 3444, 1591 }) == TRUE) PutItem(member, &runas[rand() % 6]);

				});
			Func::sendPistaLider(LeaderId, { 3338, 1545 }, { 3444, 1591 }, 2);

			 
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista das Torres.", GetMobFromIndex(LeaderId)->MOB.MobName);
			Log(temp, "Pista-Torre", 0);
		
		}

		if (playinArea.size() > 0)
		{
			for (auto& i : playinArea)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		auto playinArea2 = Func::getPlayerinArea({ 3338, 1545 }, { 3444, 1591 });
		if (playinArea2.size() > 0)
		{
			for (auto& i : playinArea2)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		clearTorres(true);
		resetGroups();
	}

	void Torre::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) {

			auto userData = &pUserData[masterId];

			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3386, 1555, 0);

			else
				Func::partyTeleportUxmal(masterId, 3418, 1575, 0);

 
			sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista das Torres.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Torre", 0);
			Func::SpawnClueTowers(idx);
			idx++;
			});


		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista das Torres %d", getGroupCount());
		Log(temp, "Pista-Torre", 0);
	
	}

	bool Torre::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		bool containsGroup = false;



		return false;
	}

	bool Torre::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		bool containsGroup = false;

		return true;
	}

	void Torre::clearTorres(bool updatePlayerSight)
	{
		auto liveMobs = Func::getMobsInAreaStr({ 3338, 1545 }, { 3444, 1591 }, { 1255 });

		if (liveMobs.size() > 0)
		{
			for (auto& i : liveMobs)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

	}

	void Torre::spawnTorre1(int pos)
	{

	}

	void Torre::spawnTorre2()
	{

	}

	bool Torre::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Torre::onSpawnBoss()
	{

	}

	void Torre::onPlayerTimer()
	{
	}

}