#include "stdafx.h"

namespace ClueLevel
{
	Zakum::Zakum()
	{
	}

	Zakum::~Zakum()
	{
	}

	bool Zakum::onGroupRegistered(const uint16_t masterId)
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

	void Zakum::onClueReset()
	{
		if (getGroupCount() == 0)
			return;

		auto mobs = Func::getPlayerinArea({ 3332, 1471 }, { 3449, 1529 });

		for (auto& i : mobs)
			DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2,0);

		resetGroups();
		killMobs();
	}

	void Zakum::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		carbunkle = 100;
		payment = bossCreated = false;
		sentRunas = false;

		killMobs();
		foreachGroup([&idx](uint16_t masterId) {

			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3428, 1486,0);
			else
				Func::partyTeleportUxmal(masterId, 3428, 1515,0);


			char msg[4096] = { 0, };
			sprintf_s(msg, 4096, "Char: %s Iniciou Pista + 6 ", GetMobFromIndex(masterId)->MOB.MobName); 
			Log(temp, "Pista-Zakun", 0);
			idx++;
			}); 
	}

	void Zakum::onPlayerTimer()
	{
	}
	 
	void Zakum::onSpawnBoss()
	{
	}

	bool Zakum::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		return false;
	}

	bool Zakum::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		bool containsGroup = false;


		auto mob = GetMobFromIndex(mobId);
		auto player = GetMobFromIndex(masterId);

		if (!strcmp(mob->MOB.MobName, "Rei Carbuncle"))
		{

			Func::executeForParty(masterId, [](int32_t member) {

				STRUCT_ITEM runas[9] = {
					{ 5130, 0, 0, 0},
					{ 5131, 0, 0, 0},
					{ 5119, 0, 0, 0},
					{ 5133, 0, 0, 0},
					{ 5120, 0, 0, 0},
					{ 5123, 0, 0, 0},
					{ 5132, 0, 0, 0},
					{ 5129, 0, 0, 0},
					{ 5128, 0, 0, 0},
				};

				if (Func::checkPlayerLiveInArea(member, { 3332, 1471 }, { 3449, 1529 }) == TRUE) PutItem
				(member, &runas[rand() % 9]);

				});

			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista do Zakum.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Zakum", 0);
		}

		if (!bossCreated)
		{
			if (!strcmp(mob->MOB.MobName, "Carbuncle Ouro"))
			{
				if (player->Leader <= 0)
				{
					if (carbunkle > 0)
						carbunkle--;

					if (carbunkle == 0)
						spawnBoss();

					int total = carbunkle;
					Func::executeForParty(masterId, [total](int32_t member)
						{
							if (Func::checkPlayerLiveInArea(member, { 3332, 1471 }, { 3449, 1529 }))
								Func::SendOrangeNumber(member, total, 100);
						}, true);
				}
			}
		}
		return false;
	}

	bool Zakum::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		char msg[4096] = { 0, };
		memset(msg, 0x0, 4096);

		auto mob = GetMobFromIndex(masterId);
		// Boss já nasceu
		if (bossCreated)
		{
			sprintf_s(msg, 4096, "Desculpe, não é possível realizar mais o pagamento.");
			SendClientMessage(masterId, msg);
			return false;
		}
		// Somente o Leader
		if (mob->Leader > 0)
		{
			sprintf_s(msg, 4096, "Somente o lider do grupo por realizar o pagamento.");
			SendClientMessage(masterId, msg);
			return false;
		}
		// Se o mesmo já fez o pagamento ( somente um por Pista )
		if (payment)
		{
			sprintf_s(msg, 4096, "O pagamento já foi realizado.");
			SendClientMessage(masterId, msg);
			return false;
		}
		// Valores Superior a 10.000.000 e inferior a 50.000.000 em Gold.
		if (value < 10 || value > 50)
		{
			sprintf_s(msg, 4096, "Pagamento deve ser entre 10.000.000 e 50.000.000 de gold.");
			SendClientMessage(masterId, msg);
			return false;
		}
		auto valueGold = value * 1000000;
		// Verifica se o Player contém a quantidade de gold da aposta.
		if (mob->MOB.Coin < valueGold)
		{
			sprintf_s(msg, 4096, "Você não possui o valor em gold informado.");
			 SendClientMessage(masterId, msg);
			return false;
		}


		if (carbunkle - value < 0)
			carbunkle = 0;
		else
			carbunkle -= value;

		payment = true;
		mob->MOB.Coin -= valueGold;
		Func::UpdateStatus(masterId);

		if (carbunkle == 0)
			spawnBoss();

		int total = carbunkle;

		Func::executeForParty(masterId, [total](int32_t member)
			{
				if (Func::checkPlayerLiveInArea(member, { 3332, 1471 }, { 3449, 1529 }))
					Func::SendOrangeNumber(member, total, 100);
			}, true);

		return false;
	}

	void Zakum::killMobs()
	{
	 
		auto mobs = Func::getMobsInArea({ 3332, 1471 }, { 3449, 1529 });
		if (mobs.size() > 0)
		{
			for (auto& i : mobs)
			{
				auto mob = GetMobFromIndex(i);
				mob->MOB.CurrentScore.Hp = 0;
			}
		}
	}

	void Zakum::spawnBoss()
	{
		if (bossCreated)
			return;


		auto mobsZakum = Func::getMobsInAreaStr({ 3424,1492 }, { 3441 ,1511 }, 2);

		if (mobsZakum.size() > 0)
			return;

		CreateMobPista("Rei_Carbuncle", 3431, 1502, "clue_of_runes/Zakum", 0);
		bossCreated = true;
	}
}

