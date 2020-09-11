#include "stdafx.h"


namespace ClueLevel
{

	Teleportador::Teleportador()
	{
	}
	Teleportador::~Teleportador()
	{
	}

	bool Teleportador::onGroupRegistered(const uint16_t masterId)
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

	void Teleportador::onClueReset()
	{
		if (getGroupCount() == 0)
			return;

		auto playinArea = Func::getPlayerinArea({ 3333, 1157 }, { 3448, 1271 });

		if (playinArea.size() > 0)
		{
			for (auto& i : playinArea)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		auto playinArea2 = Func::getPlayerinArea({ 3333, 1157 }, { 3448, 1271 });

		if (playinArea2.size() > 0)
		{
			for (auto& i : playinArea2)
				DoTeleport(i, 3284 + rand() % 2, 1685 + rand() % 2, 0);
		}
		clearMobs(true);
		resetGroups();
	}

	void Teleportador::onClueStart()
	{
		if (getGroupCount() == 0)
			return;

		uint8_t idx = 0;

		foreachGroup([&idx](uint16_t masterId) {

			auto userData = &pUserData[masterId];

			if (idx == 0)
				Func::partyTeleportUxmal(masterId, 3433, 1211, 0);
			else
				Func::partyTeleportUxmal(masterId, 3438, 1215, 0);

			sprintf(temp, "[Enter] -> Grupo do %s Entrou na Pista do Teleportador.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Teleportador", 0);
			idx++;
			});

		sprintf(temp, "[GroupCounter] -> Número de Grupo Registrado na Pista do Teleportador %d", getGroupCount());
		Log(temp, "Pista-Teleportador", 0);
		if (!Boss)
		{
			CreateMobPista("Balrog", 3390, 1209, "clue_of_runes/Teleportador", 0);
			Boss = true;
		}
	}

	bool Teleportador::onMobKilled(const uint16_t masterId, const uint16_t mobId)
	{
		auto mob = GetMobFromIndex(mobId);

		if (!strcmp(mob->MOB.MobName, "Balrog"))
		{
			Func::executeForParty(masterId, [](int32_t member) {
				STRUCT_ITEM runas[7] = {
					{ 5120, 0, 0, 0},
					{ 5131, 0, 0, 0},
					{ 5118, 0, 0, 0},
					{ 5119, 0, 0, 0},
					{ 5123, 0, 0, 0},
					{ 5132, 0, 0, 0},
					{ 5121, 0, 0, 0},
				};
				if (Func::checkPlayerLiveInArea(member, { 3377, 1193 }, { 3411, 1229 }) == TRUE) PutItem(member, &runas[rand() % 7]);
				});

			Func::sendPistaLider(masterId, { 3377, 1193 }, { 3411, 1229 }, 6);
			 
			sprintf(temp, "[Winner] -> Grupo do %s ganhou a pista do Teleportador.", GetMobFromIndex(masterId)->MOB.MobName);
			Log(temp, "Pista-Teleportador", 0);
		
		}

		return false;
	}

	bool Teleportador::onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY)
	{
		auto mob = GetMobFromIndex(masterId);
		auto semente = Func::GetFirstSlot(masterId, SlotType::Inventory, 4032,0);
		auto rnd = Rnd::instance().IRandomX(0, 100);


		auto isLeader = [&mob] {
			return mob->Leader <= 0 ? true : false;
		};

		if (!isLeader()) return false; // Se não for lider não tem efeito

		if (semente == -1) return false; // caso não tenha a semente



#pragma region Parte_1
		if (destX == 3430 && destY == 1198)
		{
			if (rnd <= 40) // Sucesso
			{
				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3388, 1163 });
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3388, 1163 });

				return true;
			}
			Func::AmountMinus(&mob->MOB.Carry[semente]);
			SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
			return true;
		}
#pragma endregion

#pragma region Parte_2
		if (destX == 3380 && destY == 1167 || destX == 3380 && destY == 1179)
		{
			if (rnd <= 30) // Sucesso 
			{
				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3340, 1215 });
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3340, 1215 });

				return true;
			}
			if (rnd >= 26 && rnd <= 70) // Apenas Falha
			{
				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				return true;
			}
			// Retorna uma Casa 
			Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3433, 1211 });
			Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3433, 1211 });

			Func::AmountMinus(&mob->MOB.Carry[semente]);
			SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
			return true;
		}
#pragma endregion

#pragma region Parte_3
		if (destX == 3341 && destY == 1224 || destX == 3352 && destY == 1224 || destX == 3363 && destY == 1224)
		{
			if (rnd <= 25) // Sucesso 
			{
				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3392, 1247 });
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3392, 1247 });

				return true;
			}

			if (rnd >= 41 && rnd <= 80) // Falha
			{
				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				return true;
			}

			Func::AmountMinus(&mob->MOB.Carry[semente]);
			SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
			Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3388, 1163 });
			Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3388, 1163 });

			return true;
		}
#pragma endregion

#pragma region Parte_4
		if (destX == 3403 && destY == 1238 || destX == 3395 && destY == 1238 || destX == 3387 && destY == 1238 || destX == 3379 && destY == 1238)
		{
			if (rnd <= 15) // Sucesso
			{


				Func::AmountMinus(&mob->MOB.Carry[semente]);
				SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3402, 1223 });
				Func::PartyTeleport(masterId, { 3333, 1157 }, { 3448, 1271 }, { 3402, 1223 });

				return true;
			}
			Func::AmountMinus(&mob->MOB.Carry[semente]);
			SendItem(masterId, (uint16_t)SlotType::Inventory, semente, &mob->MOB.Carry[semente]);
			return true;
		}
#pragma endregion





		return true;
	}

	void Teleportador::onSpawnBoss()
	{

	}

	void Teleportador::clearMobs(bool Check)
	{
		auto MobsClear = Func::getMobsInArea({ 3333, 1157 }, { 3448, 1271 });

		if (MobsClear.size() > 0)
		{
			for (auto& i : MobsClear)
				GetMobFromIndex(i)->MOB.CurrentScore.Hp = 0;
		}

		Boss = false;
	}

	bool Teleportador::onPaymentGold(const uint16_t masterId, const uint16_t value)
	{
		return false;
	}
	void Teleportador::onPlayerTimer()
	{
	}

} // end namespace ClueLevel
