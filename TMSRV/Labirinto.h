#pragma once

namespace ClueLevel
{

	class Labirinto : public ClueOfRunes
	{
	public:
		Labirinto();
		virtual ~Labirinto();

		bool onGroupRegistered(const uint16_t masterId) override;
		bool onPaymentGold(const uint16_t masterId, const uint16_t value) override;
		void onClueReset() override;

		void onClueStart() override;

		void onSpawnBoss() override;

		void onPlayerTimer() override;

		bool onMobKilled(const uint16_t masterId, const uint16_t mobId) override;

		bool onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY) override;

		const uint32_t getLevel() const override {
			return 0;
		}
		const uint32_t isFull() const override
		{
			return getGroupCount() > 1 ? true : false;
		}

	private:
		void spawnMobs();
		void clearMobs(bool updatePlayerSight);
		bool Boss = false;
		uint16_t valorDir = 0;
		uint16_t valorEsq = 0;
		uint16_t chance = 5;
	};

} // end namespace ClueLevel