#ifndef STRUCTS_H
#define STRUCTS_H

//-------Connecting User Modes----------------------------------------------------------------------------
#define USER_EMPTY       0 // There's no user on this slot
#define USER_ACCEPT      1
#define USER_LOGIN       2
//-------SelScreen User Modes----------------------------------------------------------------------------
#define USER_SELCHAR     11   // Waiting DB to send the SELCHAR struct
#define USER_CHARWAIT    12   // Waiting DB confirmation of char login
#define USER_WAITDB		 13	  // Waiting DB response to confirm
//#define USER_CREWAIT     14   // Waiting DB confirmation of character creation

//-------Ingame User Modes----------------------------------------------------------------------
#define USER_PLAY        22 // User is ingame playing with a character
#define USER_SAVING4QUIT 24 // User is saving game right before quitting

#define MOB_PER_ACCOUNT		4
#define MAX_USER			1000
#define	MAX_EQUIP			16
#define MAX_CARRY			64
#define MAX_CARGO			128
#define MAX_AFFECT			16
#define MOBNAME_LENGTH		16
#define ACCOUNTNAME_LENGTH	16
#define MAX_STATICEFFECT	12
#define ITEMNAME_LENGTH		64
#define	MAX_ITEMLIST		6500
#define MAX_PARTY			12
#define MAX_MOB				12800
#define MAX_ITEM			6500
#define REF_10				10
#define REF_11				12
#define REF_12				15
#define REF_13				18
#define REF_14				22
#define	REF_15				27
#define	ITEM_PLACE_EQUIP    0
#define	ITEM_PLACE_CARRY    1
#define	ITEM_PLACE_CARGO    2
#define ELMO_TYPE 2
#define PEITO_TYPE 4
#define CALCA_TYPE 8
#define LUVA_TYPE 16
#define BOTA_TYPE 32
#define ARMA_TYPE1 192
#define ARMA_TYPE2 64
#define ESCUDO_TYPE 128
#define EF_NOTRADE  127
#define EF1 stEffect[0].cEffect
#define EFV1 stEffect[0].cValue
#define EF2 stEffect[1].cEffect
#define EFV2 stEffect[1].cValue
#define EF3 stEffect[2].cEffect
#define EFV3 stEffect[2].cValue 

///Controle de Rates
//+9 +10  +11  +12  +13  +14  +15
static const int RateRefItemCele[] = { 100, 100, 100, 100, 100, 100, 100 };
#define RATE_Extração 100
#define pItem(id)(Func::GetItemListItem(id))
//Barras Mytril Controle de ADD
//Armas e Escudos
#define MAX_DAMAGE_ARMA 81
#define MAX_MAGIC_ARMA 36
#define MAX_AC_ARMA 60
#define MAX_CRITICO_ARMA 120
//Sets
#define MAX_DAMAGE_SET 42
#define MAX_MAGIC_SET 14
#define MAX_AC_SET 40
#define MAX_AC_LUVA 70
#define MAX_CRITICO_SET 90

#define FLAG_GAME2CLIENT	0x100
#define FLAG_CLIENT2GAME	0x200
#define FLAG_GAME2DB		0x800
#define FLAG_DB2GAME		0x400
#define FLAG_DB2NP			0x1000
#define FLAG_NP2DB			0x2000
#define	ESCENE_FIELD	    30000

#define	MAX_GRIDX		4096
#define MAX_GRIDY		4096
#define NAME_LENGTH		16
#define	AFFECT_1D		10800
#define	AFFECT_1H		450

#define LEARN_00	0x00000001
#define LEARN_01	0x00000002
#define LEARN_02	0x00000004
#define LEARN_03	0x00000008
#define LEARN_04	0x00000010
#define LEARN_05	0x00000020
#define LEARN_06	0x00000040
#define LEARN_07	0x00000080
#define LEARN_08	0x00000100
#define LEARN_09	0x00000200
#define LEARN_10	0x00000400
#define LEARN_11	0x00000800
#define LEARN_12	0x00001000
#define LEARN_13	0x00002000
#define LEARN_14	0x00004000
#define LEARN_15	0x00008000
#define LEARN_16	0x00010000
#define LEARN_17	0x00020000
#define LEARN_18	0x00040000
#define LEARN_19	0x00080000
#define LEARN_20	0x00100000
#define LEARN_21	0x00200000
#define LEARN_22	0x00400000
#define LEARN_23	0x00800000
#define LEARN_24	0x01000000
#define LEARN_25	0x02000000
#define LEARN_26	0x04000000
#define LEARN_27	0x08000000
#define LEARN_28	0x10000000
#define LEARN_29	0x20000000
#define LEARN_30	0x40000000

#define COLORBASE	0xFF000000

#define MAX_STRINGTABLEID 500
#define MAX_STRINGTABLESIZE 128

#define SECRETSTONE_RATE 95 // Padrão 95
#define SPIRITUALSTONE_RATE 10 // Padrão 20
#define RATE_Mytrill_Falha 25
#define RATE_Mytrill_Sucesso 26
#define Ref_Selado 100
#define MAX_EFFECT_NAME 50

#define CHECK_SHIELD 4294967294

#define TIME_1DAY 86400
#define TIME_1HOUR 3600

#define TIME_30DAY TIME_1DAY * 30
#define TIME_15DAY TIME_1DAY * 15
#define TIME_7DAY TIME_1DAY * 7

#define TIME_3HOUR TIME_1HOUR * 3

#define ENDLESSTOWER 1019

#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;


enum ClientColor
{
	Black = COLORBASE + 0x000000,
	White = COLORBASE + 0xFFFFFF,
	Red = COLORBASE + 0xFF0000,
	Blue = COLORBASE + 0x0000FF,
	Yellow = COLORBASE + 0xFFFF00,
	LightGreen = COLORBASE + 0x00FF00,
	Orange = COLORBASE + 0xFD7403,
	Brown = COLORBASE + 0xA62A2A,
	Pink = COLORBASE + 0xFC0FC0
};

static const uint8_t g_RefineTable[] = { 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 43 };

enum class SlotType : int32_t
{
	Equipment = 0,
	Inventory,
	Storage
};

enum EquipType : int32_t
{
	Face = 1,
	Helm = 2,
	Armor = 4,
	Pants = 8,
	Gloves = 16,
	Boots = 32,
	Weapon2Hand = 64,
	Shield = 128,
	Weapon1Hand = 192,
	Ring = 256,
	Amulet = 512,
	Orb = 1024,
	Ankh = 2048,
	Guild = 4096,
	Fairy = 8192,
	Mount = 16384,
	Cape = 32768
};

struct STRUCT_SCORE
{
	uint16_t Level;
	uint16_t Ac;
	uint16_t Damage;

	uint8_t Merchant;
	uint8_t AttackRun;

	uint16_t MaxHp, MaxMp;
	uint16_t Hp, Mp;

	uint16_t Str, Int;
	uint16_t Dex, Con;

	uint8_t Special[4];
};

struct STRUCT_POSITION
{
	uint16_t X;
	uint16_t Y;
};

struct STRUCT_ITEM
{
	uint16_t sIndex;

	union
	{
		uint16_t sValue;

		struct
		{
			uint8_t cEffect;
			uint8_t cValue;
		};

	} stEffect[3];

#define EF1 stEffect[0].cEffect
#define EFV1 stEffect[0].cValue
#define EF2 stEffect[1].cEffect
#define EFV2 stEffect[1].cValue
#define EF3 stEffect[2].cEffect
#define EFV3 stEffect[2].cValue
};

struct STRUCT_AFFECT
{
	uint8_t Type;
	uint8_t Level;
	uint16_t Value;
	uint32_t Time;
};

struct STRUCT_MOB
{
	char MobName[MOBNAME_LENGTH];
	uint8_t Clan;

	struct
	{
		uint8_t Merchant : 6;
		uint8_t CityID : 2;
	} Info;

	uint16_t Guild;
	uint8_t Class;

	uint8_t Rsv;

	// |= 1 First Trainer, Pílula Mágica
	// |= 2 MysticLand // Pegou primeira parte da quest
	// |= 4 MysticLand 2
	// |= 8 MysticLand 3 // Recebeu a recompensa
	// |= 16 Quest Reset Skill 1, Reset com Safira
	// |= 32 Quest Reset Skill 2
	// |= ??  00441F5F Arch Talvez?

	uint16_t Quest;

	int32_t Coin;
	uint32_t Exp;

	int16_t SPX;
	int16_t SPY;

	STRUCT_SCORE BaseScore;
	STRUCT_SCORE CurrentScore;

	STRUCT_ITEM Equip[MAX_EQUIP];
	STRUCT_ITEM Carry[MAX_CARRY];

	uint32_t LearnedSkill;

	uint16_t
		ScoreBonus,
		SpecialBonus,
		SkillBonus;

	uint8_t Critical;
	uint8_t SaveMana;

	char SkillBar[4];

	char GuildLevel;
	uint8_t Magic;

	uint8_t
		RegenHP,
		RegenMP;

	uint8_t
		Resist[4];
};

struct ServerStatus
{
	struct
	{
		int AltarTime;
	} CastleWar;
};

struct STRUCT_SELCHAR
{
	STRUCT_POSITION LastPosition[MOB_PER_ACCOUNT];
	char Name[MOB_PER_ACCOUNT][MOBNAME_LENGTH];
	STRUCT_SCORE Status[MOB_PER_ACCOUNT];
	STRUCT_ITEM Equip[MOB_PER_ACCOUNT][MAX_EQUIP];

	int16_t GuildId[MOB_PER_ACCOUNT];
	int32_t Gold[MOB_PER_ACCOUNT];
	uint32_t Experience[MOB_PER_ACCOUNT];
};

struct CPSock
{
	unsigned int Sock; // 0 - 3
	char* pSendBuffer; // 4 - 7
	char* pRecvBuffer; // 8 - 11
	int nSendPosition; // 12 - 15
	int nRecvPosition; // 16 - 19
	int nProcPosition; // 20 - 23
	int nSentPosition; // 24 - 27
	int Init; // 28 - 31
	char UnknowByte_32[16]; // 32 - 47
	char UnknowByte_48[16]; // 48 - 63
	int UnknowByte_64; // 64 - 67
	int UnknowByte_68; // 68 - 71
	int UnknowByte_72; // 72 - 75
};

struct STRUCT_LEVELITEM
{
	int Index;

	STRUCT_ITEM Item;

	STRUCT_ITEM SendItem;
};

struct STRUCT_MILEAGESTORE
{
	STRUCT_ITEM Item;
	uint16_t Price;
	uint8_t Store;
};

struct CUserDB
{
	unsigned int IP; // 0 - 3
	int    Mode; // 4 - 7
	CPSock cSock; // 8
	int    Count;
	int    Level;
	int    Encode1;
	int    Encode2;
	char   Name[ACCOUNTNAME_LENGTH];
	int    DisableID;
};

#ifdef _TMSRV

struct UserData
{
	struct _AccountInfo
	{
		
		char LastIP[16];
		unsigned int Cash;
		unsigned int sTicketGold;
		unsigned int sTicketPrata;
		unsigned int NewbieReward;
		unsigned int Type;
		struct
		{
			time_t TimeStamp;
			unsigned int Permanent;
		} Ban;

		char Empty[100];

	} AccountInfo;

	struct _CharacterInfo
	{
		char Empty[50];

		struct
		{
			uint16_t CytheraArch;
		}Especial;

	} CharacterInfo[MOB_PER_ACCOUNT];

	struct _Ingame
	{
		unsigned int Warning;

		uint64_t PointStore;

		struct
		{
			struct
			{
				unsigned int LastAttackTime;
				unsigned int Warning;
			} Attack;

			struct
			{
				unsigned int Warning;
			} Action;

			struct
			{
				unsigned int LastReqParty;
			} SendReqParty;

			struct
			{
				unsigned int UseJewelBag;
			} UseItem;

		} MSG;

		char PartyPassword[6];

		char Empty[94];

		bool autoStore;

		bool GrupoAceitarSolicitação;

		char GrupoSenha[12];

		bool Quiz;

		int QuizResposta;

		int QuizErrado;

		int QuizLanHouse;

		int QuizTempo;

		int chave;
		  
		char MacAddress[18];

		int CountDownPacketSecurity;

		int WarningPacketSecurity;

		int ClientOK;

	} Ingame;

	struct _Fixer
	{
		int Novato;
	}Fixer;
};

enum MobClass
{
	Mortal = 0,
	God = 1,
	Celestial = 2
};

struct CMob
{ 
	// size 1724 -> 0x1FDECA0
	STRUCT_MOB MOB; // 0 - 755
	unsigned int Hold; // 756 - 759
	unsigned int CrackError; // 760 - 763
	int NTCount; // 764 - 767
	int Mileage; // 768 - 771
	unsigned int UnknowByte_772; // 772 - 775
	int Fame; // 776 - 779
	int UnknowByte_780; // 780 - 783
	int UnknowByte_784; // 784 - 787
	STRUCT_AFFECT SaveAffect[MAX_AFFECT]; // 788 - 915
	char UnknowByte_916[288]; // 916 - 1203
	STRUCT_AFFECT Affect[MAX_AFFECT]; // 1204 - 1331
	int Mode; // 1332 - 1335
	int Leader; // 1336 - 1339
	int Formation; // 1340 - 1343
	int RouteType; // 1344 - 1347
	int LastX; // 1348 - 1351
	int LastY; // 1352 - 1355
	int LastTime; // 1356 - 1359
	int LastSpeed; // 1360 - 1363
	int TargetX; // 1364 - 1367
	int TargetY; // 1368 - 1371
	int NextX; // 1372 - 1375
	int NextY; // 1376 - 1379
	int NextAction; // 1380 - 1383
	char Route[24]; // 1384 - 1407
	int WaitSec; // 1408 - 1411
	int UnknowByte_1412; // 1412 - 1415
	int SegmentHold; // 1416 - 1419
	int Segment; // 1420 - 1423
	int SegmentX; // 1424 - 1427
	int SegmentY; // 1428 - 1431
	int SegmentListX[5]; // 1432 - 1451
	int SegmentListY[5]; // 1452 - 1471
	int SegmentWait[5]; // 1472 - 1491
	int SegmentDirection; // 1492 - 1495
	int SegmentProgress; // 1496 - 1499
	int GenerateIndex; // 1500 - 1503
	short CurrentTarget; // 1504 - 1505
	short EnemyList[4]; // 1506 - 1513
	short PartyList[MAX_PARTY]; // 1514 - 1537
	short UnknowByte_1538; // 1538 - 1539
	int WeaponDamage; // 1540 - 1543
	int Summoner; // 1544 - 1547
	int PotionCount; // 1548 - 1551
	int GuildDisable; // 1552 - 1555
	int DropBonus; // 1556 - 1559
	int ExpBonus; // 1560 - 1563
	int RangeBonus; // 1564 - 1567
	int ForceBonus; // 1568 - 1571
	int UnknowByte_1572; // 1572 - 1575
	int CurrentFace; // 1576 - 1579
	char UnknowByte_1580[76]; // 1580 - 1659
	char Tab[26]; // 1660 - 1683
	char UnknowByte_1684[24]; // 1684 - 1707
	int Rsv; // 1708 - 1711
	char Unknowbyte_1712[8]; // 1712 - 1719
	int Parry; // 1720 - 1723
	 
};

enum UserMode
{
	Playing = 22
};


enum ClassInfo : uint8_t
{
	Transknight = 0,
	Foema = 1,
	BeastMaster = 2,
	Huntress = 3
};
struct MSG_SendAutoTrade
{
	_MSG;

	char Title[24];

	STRUCT_ITEM Item[12];

	char CarryPos[12];

	int Coin[12];

	short Tax;
	short Index;
};

struct MSG_Trade
{
	_MSG;

	STRUCT_ITEM		Item[15];

	char			InvenPos[15];
	int				TradeMoney;
	unsigned char	MyCheck;
	unsigned short	OpponentID;
};

struct Moeda
{
	uint16_t item;
	uint16_t preço;
	uint16_t quantidades;
};

struct Lixo
{
	uint16_t item;
	uint16_t preço;
	uint16_t quantidades;
};

struct CUser
{
	char AccountName[ACCOUNTNAME_LENGTH];
	int Slot;
	unsigned int IP;
	int Mode;
	int TradeMode;
	CPSock cSock;
	STRUCT_ITEM Cargo[128];
	int Coin;
	unsigned short cProgress;
	short UnknowByte_1138;
	MSG_Trade Trade;
	MSG_SendAutoTrade AutoTrade;
	int LastAttack;
	int LastAttackTick;
	int LastMove;
	int LastAction;
	int LastActionTick;
	int LastIllusionTick;
	unsigned int NumError;
	int Billing;
	STRUCT_SELCHAR SelChar;
	char LastChat[16];
	int IsBillConnect;
	char UserStatus[4];
	char Session[32];
	unsigned char CharShortSkill[16];
	int nTargetX;
	int nTargetY;
	int Whisper;
	int Guildchat;
	int PartyChat;
	int Chatting;
	int UnknowByte_2364;
	char AutoTradeName[24];
	int PKMode;
	int ReqHp;
	int ReqMp;
	int bQuaff;
	int Mac[4];
	int RankingMode;
	int RankingTarget;
	int RankingType;
	int LastReceiveTime;
	int Admin;
	int Child;
	unsigned int CheckBillingTime;
	int CharLoginTime;
	int CastleStatus; // 2456
	int UnknowByte_2476[6];
	char HashKeyTable[16];
	char UnknowByte_2548[108];
	char Snd[96];
	int UnknowByte_2704[10];
	int LastSkillTick[104];
};

struct CItem
{
	STRUCT_ITEM ITEM; // 0 - 7
	int  Mode; // 8 - 11
	int  PosX, PosY; // 12 - 19
	int  GridCharge; // 20 - 23
	int  State; // 24 - 27
	int  Rotate; // 28 - 31
	int  Delay; // 32 - 35
	int  Decay; // 36 - 39
	int  Height; // 40 - 43
	int  Money; // 44 - 47
	int  Open; // 48 - 51
};

struct NPCGENLIST
{
	int Mode; //BDEAA0
	int MinuteGenerate;
	int MaxNumMob;
	int CurrentNumMob;
	int MinGroup;
	int MaxGroup;
	int SegmentListX[5];
	int SegmentListY[5];
	int SegmentRange[5];
	int SegmentWait[5];
	char SegmentAction[5][80];
	char FightAction[4][80];
	char FleeAction[4][80];
	char DieAction[4][80];
	int Formation;
	int RouteType;
	int	Offset;
	int MobIndex;
	STRUCT_MOB Leader;
	STRUCT_MOB Follower;
};

struct CNPCGenerator
{
	NPCGENLIST pList[7000];
	int NumOld[7000];
	int NumList;
};


#elif _CLIENT

struct EffectName { uint8_t name[24]; };

typedef struct
{

	int type;

	int damage;

	int HP;

}HelperStatus;

struct pAF1h
{
	_MSG;
	char msg[150];
	int color;
};

struct pAFA
{
	_MSG;
	short sType;
};

typedef struct
{
	_MSG;

	HelperStatus pHelper;
}pAF2h;

typedef struct
{
	_MSG;
	unsigned short cur_mob;
	unsigned short max_mob;
} p3BBc;

#endif
struct STRUCT_ITEMLIST
{
	char Name[ITEMNAME_LENGTH]; // 0 - 63 = 9CCC40
	short IndexMesh; // 64 - 65
	short IndexTexture; // 66 - 67
	short IndexVisualEffect; // 68 - 69
	short ReqLvl; // 70 - 71
	short ReqStr; // 72 - 73
	short ReqInt; // 74 - 75
	short ReqDex; // 76 - 77
	short ReqCon; // 78 - 79

	struct
	{
		short sEffect;
		short sValue;

	} stEffect[MAX_STATICEFFECT]; // 80 - 127

	int Price; // 128 - 131
	short nUnique; // 132 - 133
	short nPos; // 134 - 135
	short Extra; // 136 - 137
	short Grade; // 138 - 139 
};

struct STRUCT_SPELL // Size 96
{
	int	SkillPoint;
	int	TargetType;
	int	ManaSpent;
	int	Delay;
	int	Range;
	int	InstanceType;
	int	InstanceValue;
	int	TickType;
	int	TickValue;
	int	AffectType;
	int	AffectValue;
	int	AffectTime;
	unsigned char Act1[8];
	unsigned char Act2[8];
	int	InstanceAttribute;
	int	TickAttribute;
	int	Aggressive;
	int	MaxTarget;
	int	bParty;
	int	AffectResist;
	int	Passive;
	int ForceDamage;
};

struct STRUCT_GUILD
{
	int Index;
	char Name[12];
	char SubName[3][12];
	char Citizen;
	char LeaderCity;
	short Clan;
	int Fame;
};

typedef struct
{
	struct
	{
		int AttackDmg;
		int MagicDmg;
		int Parry;
		int ResistAll;
		int MoveSpeed;
		int unk;
	} Mounts[20];
}MountTable;

typedef struct
{
	INT16 Check;
}CheckClient;


typedef struct
{
	uint16_t ItemID;
	uint16_t Price;
}DonatePrice;

typedef struct
{
	uint16_t min, hora, dia, mes, ano;
	uint16_t Permanent, analyze;
}STRUCT_BAN;

#endif // !STRUCTS_H
