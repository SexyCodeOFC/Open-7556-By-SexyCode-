#pragma once

class Global
{
public:
	static bool SenhaLiberado;
	static bool AutoGrupo;
	static bool PermitirGrupo;
	static char SenhaGrupo[12];
	static bool ModoFoto;
	static bool Effects2;
	static bool MacroPergas;
	static bool CameraLivre;
	static int	Donate; 
	static int LastPacket;
	static SvRtn ServerList;
	static char StoreName[20];
	static EffectName pEffectName[MAX_EFFECT_NAME];

	 
	static UpdateItemQuest::_CharacterInfo	ControlItemQuest;

	static std::vector<uint32_t>			ControlItemAmount;
	static std::vector<BuyDonate>			ControlItemDonate;
	static std::vector<RoyalBit>			ControlRoyalBit;
	static STRUCT_GUILD						ControlGuild;
};
 
extern bool agrupar_item;
extern std::vector<uint32_t> lista_itens_agrupar;