
#ifndef CLUE_OF_RUNES_H
#define CLUE_OF_RUNES_H

namespace ClueLevel
{

	class ClueOfRunes
	{
	public:
		virtual ~ClueOfRunes() = default;

		/*
		Fun��o que vai ser chamada quando um grupo se registrar
		no NPC Uxmall
		*/
		virtual bool onGroupRegistered(const uint16_t masterId) = 0;

		/*
		Fun��o que vai ser chamada quando a �rea da pista for limpa
		antes dos novos grupos entrarem.
		*/
		virtual void onClueReset() = 0;

		/*
		Fun��o que vai ser chamada quando a �rea estiver limpa, e os
		grupos forem teleportados para dentro.
		*/
		virtual void onClueStart() = 0;

		/*
		Fun��o que chama para nascer o Boss
		*/
		virtual void onSpawnBoss() = 0;

		/*
		Fun��o de Controle Timer dos Players
		*/
		virtual void onPlayerTimer() = 0;


		/*
		Fun��o que vai ser chamada quando algum mob dentro da �rea
		dessa pista for morto.
		*/
		virtual bool onMobKilled(const uint16_t masterId, const uint16_t mobId) = 0;

		/*
		Fun��o que verifica se o mob est� dentro da area permitida
		da pista
		*/
		virtual bool onMovimented(const uint16_t masterId, const uint16_t destX, const uint16_t destY) = 0;
		 /* 
		Fun��o que retorna o level dessa pista
		*/
		virtual const uint32_t getLevel() const = 0;

		/*
		Fun��o que indica se mais grupos podem ser registrados ou n�o
		*/
		virtual const uint32_t isFull() const = 0;

		virtual bool onPaymentGold(const uint16_t masterId, const uint16_t value) = 0;
		/*
		Vari�vel que diz se existe um boss vivo ou n�o
		*/
		bool isBossAlive = false;
		



	protected:
		/*
		Retorna a quantidade de grupos atualmente registrados.
		*/
		inline const uint32_t getGroupCount() const {
			return m_groupIndexes.size();
		}
		/*
		Adiciona um valor ao Kill do Grupo
		*/
		inline void incrimentKillCount(const uint16_t masterId)
		{
			//for (size_t i = 0; i < getGroupCount(); i++)
			for (size_t i = 0, ilen = getGroupCount(); i < ilen; ++i)
			{
				if (m_groupIndexes[i] == masterId)
					m_groupKillsCount[i]++;
			}
		}
		/*
		Retorna o valor de kill do grupo
		*/
		inline uint64_t getKillsCount(const uint16_t masterId)
		{
			//for (int i = 0; i < getGroupCount(); i++)
			for (size_t i = 0, ilen = getGroupCount(); i < ilen; ++i)
			{
				if (m_groupIndexes[i] == masterId)
					return m_groupKillsCount[i];
			}
			return 100;
		}
		/*
		Retorna o cId do master de um grupo
		*/
		inline uint16_t getMaster(const uint16_t pos)
		{
			return m_groupIndexes[pos];
		}
		/*
		Adiciona um grupo
		*/


		inline void addGroup(const uint16_t masterId) {
			m_groupIndexes.push_back(masterId);
			m_groupKillsCount.push_back(masterId);

			//for (int i = 0; i < getGroupCount(); i++)
			for (size_t i = 0, ilen = getGroupCount(); i < ilen; ++i)
			{
				if (m_groupIndexes[i] == masterId)
					m_groupKillsCount[i] = 0;
			}
		}
		/*
		Limpa a lista de grupos
		*/
		inline void resetGroups()
		{
			Func::clearPista();
			m_groupIndexes.clear();
			m_groupKillsCount.clear();
		}
		/*
		Executa uma fun��o para todos os grupos registrados
		*/
		inline void foreachGroup(const std::function<void(uint16_t member)> fn) {
			for (auto& i : m_groupIndexes)
				fn(i);
		}

	private:
		std::vector<uint16_t> m_groupIndexes = std::vector<uint16_t>();
		std::vector<uint64_t> m_groupKillsCount = std::vector<uint64_t>();
	};

} // end namespace ClueLevel

#endif // !CLUE_OF_RUNES_H
