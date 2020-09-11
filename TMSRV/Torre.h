#pragma once

namespace ClueLevel
{

	class Torre : public ClueOfRunes
	{
	public:
		Torre();
		virtual ~Torre();

		bool onGroupRegistered(const uint16_t masterId) override;

		bool onPaymentGold(const uint16_t masterId, const uint16_t value) override;

		void onClueReset() override;

		void onClueStart() override;

		void onSpawnBoss() override;

		void onPlayerTimer() override;

		bool onMobKilled(const uint16_t masterId, const uint16_t mobId) override;

		bool onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY);

		const uint32_t getLevel() const override {
			return 0;
		}
		const uint32_t isFull() const override
		{
			return getGroupCount() > 1 ? true : false;
		}

	private:
		void spawnTorre1(int pos);
		void spawnTorre2();
		void clearTorres(bool updatePlayerSight);

	};

} // end namespace ClueLevel