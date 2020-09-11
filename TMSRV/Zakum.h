#pragma once

namespace ClueLevel
{

	class Zakum : public ClueOfRunes
	{
	public:
		Zakum();
		virtual ~Zakum();
		 

		bool onGroupRegistered(const uint16_t masterId) override;

		void onClueReset() override;

		void onClueStart() override;

		void onSpawnBoss() override;

		void onPlayerTimer() override;

		bool onMobKilled(const uint16_t masterId, const uint16_t mobId) override;

		bool onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY) override;
		
		bool onPaymentGold(const uint16_t masterId, const uint16_t value) override;

		const uint32_t getLevel() const override
		{
			return 0;
		}
		const uint32_t isFull() const override
		{
			return getGroupCount() > 1 ? true : false;
		}

	private:
		void clearMobs(bool Check);
		void killMobs();
		bool Started = false;
		int carbunkle = 100;
		bool bossCreated = false;
		bool payment = false;
		bool sentRunas = false;
		void spawnBoss();
	};

}