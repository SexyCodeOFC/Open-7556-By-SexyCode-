#ifndef CLUE_OF_RUNES_MGR_H
#define CLUE_OF_RUNES_MGR_H

class ClueOfRunesMgr : public Singleton<ClueOfRunesMgr>
{
protected:
	friend class Singleton<ClueOfRunesMgr>;

	ClueOfRunesMgr() {}
	virtual ~ClueOfRunesMgr() {}
	ClueOfRunesMgr(const ClueOfRunesMgr&) = delete;
	ClueOfRunesMgr& operator=(const ClueOfRunesMgr&) = delete;

public:
	bool registerGroup(const uint32_t level, const uint16_t masterId);

	void onClueReset();

	void onClueStart();

	void onSpawnBoss();

	void onPlayerTimer();

	bool isBossAlive;

	bool onMobKilled(const int32_t posX, const int32_t posY, const uint16_t mobId, const uint16_t masterId);

	bool onMoviment(const int32_t desX, const int32_t desY, const uint16_t masterId);

	
};
#endif // !CLUE_OF_RUNES_MGR_H
