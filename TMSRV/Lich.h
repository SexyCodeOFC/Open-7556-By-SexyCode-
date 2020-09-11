#pragma once

namespace ClueLevel
{

	class Lich : public ClueOfRunes
	{
	public:
		Lich();
		virtual ~Lich();

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
		void spawnLichEsq();
		void spawnLichDir();
		void killLichEsq(bool updatePlayerSight);
		void killLichDir(bool updatePlayerSight);
		void killLichAll(bool updatePlayerSight);
	};

}