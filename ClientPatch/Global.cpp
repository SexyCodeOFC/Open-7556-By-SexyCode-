#include "stdafx.h"
#include "Global.h"

bool								Global::SenhaLiberado;
bool								Global::AutoGrupo;
bool								Global::MacroPergas;

bool								Global::PermitirGrupo;
char								Global::SenhaGrupo[12];

bool								Global::CameraLivre;
bool								Global::ModoFoto;
bool								Global::Effects2;
char								Global::StoreName[20] = { 0, };

EffectName							Global::pEffectName[MAX_EFFECT_NAME];
bool agrupar_item;
std::vector<uint32_t> lista_itens_agrupar = std::vector<uint32_t>();
int									Global::Donate;
int									Global::pTicketGold;
int									Global::pTicketPrata;
int									Global::LastPacket;
SvRtn								Global::ServerList;
STRUCT_GUILD						Global::ControlGuild = { 0, }; 
UpdateItemQuest::_CharacterInfo		Global::ControlItemQuest = { 0, };

std::vector<BuyDonate>				Global::ControlItemDonate = std::vector<BuyDonate>();
std::vector<RoyalBit>				Global::ControlRoyalBit = std::vector<RoyalBit>();
std::vector<uint32_t>				Global::ControlItemAmount = std::vector<uint32_t>();