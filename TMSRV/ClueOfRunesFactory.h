
#ifndef CLUE_OF_RUNES_FACTORY_H
#define CLUE_OF_RUNES_FACTORY_H

class ClueOfRunesFactory : public Singleton<ClueOfRunesFactory>
{
protected:
	friend class Singleton<ClueOfRunesFactory>;

	ClueOfRunesFactory();
	virtual ~ClueOfRunesFactory() {}
	ClueOfRunesFactory(const ClueOfRunesFactory&) = delete;
	ClueOfRunesFactory& operator=(const ClueOfRunesFactory&) = delete;

public:
	ClueLevel::ClueOfRunes* getClueOfRunes(const uint32_t level); 
	const std::vector<ClueLevel::ClueOfRunes*> getAllClueLevels() const;
	 
	static void TimerControl();

private:
	std::map<uint32_t, std::unique_ptr<ClueLevel::ClueOfRunes>> clueOfRunesMap_;
};
#endif // !CLUE_OF_RUNES_FACTORY_H
