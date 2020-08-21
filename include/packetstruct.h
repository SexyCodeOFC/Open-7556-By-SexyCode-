#ifndef PACKET_STRUCT_H
#define PACKET_STRUCT_H

#include "structs.h"
 
#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;

struct		 MSG_STANDARD
{
	_MSG;
};

struct		 MSG_STANDARDPARM
{
	_MSG;
	int Parm;
};

struct		 MSG_STANDARDPARM2
{
	_MSG;
	int Parm1;
	int Parm2;
};

struct		 MSG_STANDARDSHORTPARM2
{
	_MSG;
	short Parm1;
	short Parm2;
};

struct		 MSG_STANDARDPARM3
{
	_MSG;
	int Parm1;
	int Parm2;
	int Parm3;
};
 
#define _p373h (115 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct p373h
{
	MSG_STANDARD	Header;

	struct
	{
		int32_t		Type;
		int32_t		Slot;
	} Src;

	struct
	{
		int32_t		Type;
		int32_t		Slot;
	} Dst;

	STRUCT_POSITION Position;
	int32_t			Warp;
};

#define _p379h (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME)
struct p379h
{
	MSG_STANDARD	Header;
	int16_t			mobID;
	int16_t			sellSlot;
	int16_t			invSlot;
	int16_t Unknown1;
	int32_t Unknown2;
};


struct MSG_COMBINE
{
	MSG_STANDARD Header;
	STRUCT_ITEM Item[8];
	int8_t Slot[8];
};

#define _p28B (139 | FLAG_CLIENT2GAME)
struct p28Bh
{
	MSG_STANDARD	Header;
	uint16_t		npcID;
	uint8_t			Unknow1;
	uint8_t			Unknow2;
	uint16_t		Confirm;
};

////////////////////////////////////////////////////////////

struct MSG_AccountLogin_7556
{
	_MSG; // 0 - 11

	char AccountPassword[12]; // 12 - 23
	char AccountName[16]; // 24 - 39

	char Zero[52]; // 40 - 91

	int  ClientVersion; // 92 - 95

	int  DBNeedSave; // 96 - 99

	int AdapterName[4]; // 100 - 115
};

struct MSG_Action_7556
{
	_MSG; // 0 - 11

	short PosX, PosY; // 12 - 15

	int Effect; // 0 = walking, 1 = teleporting // 16 - 19
	int Speed; // 20 - 23

	char Route[24]; // 24 - 47

	short TargetX, TargetY; // 48 - 51
};

struct	MSG_DBCNFAccountLogin_7556 // TODO : Check and rename if it's used for MSG_CNFAccountLogin, rename to MSG_CNFAccountLogin and change references in DB source
{
	_MSG; // 0 - 11

  /*short		  Size;			\ // 0x1508 // 0x4AF0 // 0xFFFFB510
	char		  KeyWord;		\ // 0x1506 // 0x4AEE // 0xFFFFB512
	char		  CheckSum;		\ // 0x1505 // 0x4AED // 0xFFFFB513
	short		  Type;			\ // 0x1504 // 0x4AEC // 0xFFFFB514
	short		  ID;			\ // 0x1502 // 0x4AEA // 0xFFFFB516
	unsigned int  ClientTick;  */ // 0x1500 // 0x4AE8 // 0xFFFFB518

	char HashKeyTable[16]; // 12 - 27 // 0x14FC // 0x4AE4 // 0xFFFFB51C

	STRUCT_SELCHAR sel; // 28 - 771 // 0x14EC // 0x4AD4 // 0xFFFFB52C
	STRUCT_ITEM Cargo[128]; // 772 - 1795 // 0x1204 // 0x47EC // 0xFFFFB814

	int Coin; // 1796 - 1799 // 0xE04 // 0x43EC // 0xFFFFBC14
	char AccountName[ACCOUNTNAME_LENGTH]; // 1800 - 1815 // 0x0E00 // 0x43E8 // 0xFFFFBC18

	int UnknowByte_1816; // 1816 - 1819
	int UnknowByte_1820; // 1820 - 1823 - 1824
};

struct STRUCT_DAM
{
	short TargetID;
	short Damage;
};

struct MSG_Attack_7556 // 0x367
{
	_MSG; // 0 - 11
	unsigned char Motion; // 12
	unsigned char SkillParm; // 13
	unsigned char DoubleCritical; // 14
	unsigned char FlagLocal; // 15
	unsigned short PosX, PosY; // 16 - 19
	unsigned short TargetX, TargetY; // 20 - 23
	unsigned short AttackerID; // 24 - 25
	unsigned short Progress; // 26 - 27
	unsigned short CurrentMp; // 28 - 29
	short SkillIndex; // 30 - 31
	int Hold; // 32 - 35
	unsigned short ReqMp; // 36 - 37
	unsigned short Rsv; // 38 - 39
	unsigned int CurrentExp; // 40 - 43
	STRUCT_DAM Dam[13]; // 44 - 95
};

struct MSG_AttackOne_7556 // 0x39D
{
	_MSG; // 0 - 11
	unsigned char Motion; // 12
	unsigned char SkillParm; // 13 
	unsigned char DoubleCritical; // 14
	unsigned char FlagLocal; // 15
	unsigned short PosX, PosY; // 16 - 19
	unsigned short TargetX, TargetY; // 20 - 23
	unsigned short AttackerID; // 24 - 25
	unsigned short Progress; // 26 - 27
	unsigned short CurrentMp; // 28 - 29
	short SkillIndex; // 30 - 31
	int Hold; // 32 - 35
	unsigned short ReqMp; // 36 - 37
	unsigned short Rsv; // 38 - 39
	unsigned int CurrentExp; // 40 - 43
	STRUCT_DAM Dam[1]; // 44 - 47
};

struct MSG_AttackTwo_7556 // 0x39E
{
	_MSG; // 0 - 11
	unsigned char Motion; // 12
	unsigned char SkillParm; // 13 
	unsigned char DoubleCritical; // 14
	unsigned char FlagLocal; // 15
	unsigned short PosX, PosY; // 16 - 19
	unsigned short TargetX, TargetY; // 20 - 23
	unsigned short AttackerID; // 24 - 25
	unsigned short Progress; // 26 - 27
	unsigned short CurrentMp; // 28 - 29
	short SkillIndex; // 30 - 31
	int Hold; // 32 - 35
	unsigned short ReqMp; // 36 - 37
	unsigned short Rsv; // 38 - 39
	unsigned int CurrentExp; // 40 - 43
	STRUCT_DAM Dam[2]; // 44 - 52
};

////////////////////////////////////////////////////////////

struct MSG_AccountLogin
{
	_MSG; // 0 - 11

	char AccountName[16]; // 12 - 27
	char AccountPassword[12]; // 28 - 39

	int ClientVersion; // 40 - 43
	int DBNeedSave; // 44 - 47

	char AdapterName[16]; // 48 - 63
	char IP[16]; // 64 - 79

	unsigned int CheckShield; // 80 - 83
	char MacAddress[18]; // 84 - 101

	char Keys[16]; // 102 - 115
};

struct MSG_Action
{
	_MSG; // 0 - 11

	short PosX, PosY; // 12 - 15

	int Speed; // 16 - 19
	int Effect; // 0 = walking, 1 = teleporting // 20 - 23

	short TargetX, TargetY; // 24 - 27

	char Route[24]; // 28 - 51
};

struct MSG_DBCNFAccountLogin // TODO : Check and rename if it's used for MSG_CNFAccountLogin, rename to MSG_CNFAccountLogin and change references in DB source
{
	_MSG; // 0 - 11

   /*short		  Size;			\ // 0x1508 // 0x4AF0 // 0xFFFFB510
	char		  KeyWord;		\ // 0x1506 // 0x4AEE // 0xFFFFB512
	char		  CheckSum;		\ // 0x1505 // 0x4AED // 0xFFFFB513
	short		  Type;			\ // 0x1504 // 0x4AEC // 0xFFFFB514
	short		  ID;			\ // 0x1502 // 0x4AEA // 0xFFFFB516
	unsigned int  ClientTick;  */ // 0x1500 // 0x4AE8 // 0xFFFFB518

	STRUCT_SELCHAR sel; // 12 - 755 // 0x14FC // 0x4AE4 // 0xFFFFB51C
	STRUCT_ITEM Cargo[128]; // 756 - 1779 // 0x1214 // 0x47FC // 0xFFFFB804

	int Coin; // 1780 - 1783 // 0x0E14 // 0x43FC // 0xFFFFBC04
	char AccountName[ACCOUNTNAME_LENGTH]; // 1784 - 1799 // 0x0E10 // 0x43F8 // 0xFFFFBC08
	char Keys[16]; // 1800 - 1815 // 0x0E00 // 0x43E8 // 0xFFFFBC18
};

struct MSG_Attack // 0x36C
{
	_MSG; // 0 - 11

	unsigned short		AttackerID; // 12 - 13
	unsigned short		Progress; // 14 - 15
	unsigned short		PosX, PosY; // 16 - 19
	unsigned short		TargetX, TargetY; // 20 - 23

	unsigned short				SkillIndex; // 24 - 25
	unsigned short 				CurrentMp; // 26 - 27

	unsigned char		Motion; // 28
	unsigned char		SkillParm; // 29
	unsigned char		FlagLocal; // 30
	unsigned char		DoubleCritical; // 31

	unsigned int					Hold; // 32 - 35
	unsigned int		CurrentExp; // 36 - 39

	unsigned short				ReqMp; // 40 - 41
	unsigned short				Rsv; // 42 - 43

	STRUCT_DAM			Dam[13]; // 44 - 95
};

struct MSG_AttackOne // 0x39D
{
	_MSG;

	unsigned short		AttackerID;
	unsigned short		Progress;
	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short				SkillIndex;
	unsigned short 				CurrentMp;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		FlagLocal;
	unsigned char		DoubleCritical;

	unsigned int					Hold;
	unsigned int		CurrentExp;

	unsigned short				ReqMp;
	unsigned short				Rsv;

	STRUCT_DAM			Dam[1];
};

struct MSG_AttackTwo //0x39E
{
	_MSG;

	unsigned short		AttackerID;
	unsigned short		Progress;
	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short				SkillIndex;
	unsigned short 				CurrentMp;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		FlagLocal;
	unsigned char		DoubleCritical;

	unsigned int					Hold;
	unsigned int		CurrentExp;

	unsigned short				ReqMp;
	unsigned short				Rsv;

	STRUCT_DAM			Dam[2];
};

struct MSG_DropItem
{
	_MSG;

	int      SourType;
	int      SourPos;
	int      Rotate;
	unsigned short GridX, GridY;
	unsigned short ItemID;
};

struct	MSG_CNFDropItem
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      Rotate;

	unsigned short GridX, GridY;
};

struct MSG_GetItem
{
	_MSG;

	int      DestType;
	int      DestPos;
	unsigned short	ItemID;
	unsigned short GridX, GridY;
};

struct MSG_DecayItem
{
	_MSG;

	short ItemID;
	short unk;
};

struct MSG_CNFGetItem
{
	_MSG;
	int DestType;
	int	DestPos;
	STRUCT_ITEM	Item;
};

struct MSG_MessageWhisper
{
	_MSG;
	char MobName[16]; 
	char String[96];
};
const uint16_t _p334h = (52 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct p334h
{
	MSG_STANDARD	Header;
	char			Cmd[16];
	char			Msg[100];
};

const uint16_t  _MSG_UseItem = (115 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); 
struct		  MSG_UseItem
{
	_MSG; // 0 - 11

	int      SourType; // 12 - 15
	int      SourPos; // 16 - 19
	int      DestType; // 20 - 23
	int      DestPos; // 24 - 27

	unsigned short GridX, GridY;
	unsigned short WarpID;
};

const short _MSG_GriffinMaster = (217 | FLAG_GAME2DB | FLAG_CLIENT2GAME);
struct       MSG_GriffinMaster
{
	_MSG;

	int WarpID;
	int MessageType;
};

const short _MSG_Buy = (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Buy
{
	_MSG;
	unsigned short TargetID;
	short TargetInvenPos;
	short MyInvenPos;
	int Coin;
};

struct MSG_SendGuildInfo
{
	_MSG;

	STRUCT_GUILD GuildInfo;
};

struct MSG_TradingItem
{
	_MSG; // 0 - 11

	unsigned char DestPlace; // 12
	unsigned char DestSlot; // 13
	unsigned char SrcPlace; // 14
	unsigned char SrcSlot; // 15

	int WarpID; // 16 - 19
};

struct MSG_AcceptParty
{
	_MSG;

	short LeaderID;
	char MobName[NAME_LENGTH];
};

struct MSG_SendMacInfo
{
	_MSG;

	char Mac[18];
};

struct MSG_SendChatColor
{
	_MSG;

	char Message[92];
	int Color;
};

struct MSG_UpdateItem
{
	_MSG; // 0 - 11

	int ItemID; // 12 - 15
	short State; // 16 - 17
	short Height; // 18 - 19
};

struct MSG_CreateMob
{
	_MSG; // 0 - 11

	short PosX, PosY; // 12 - 15
	unsigned short MobID; // 16 - 17
	char MobName[NAME_LENGTH]; // 18 - 33
	unsigned short Equip[MAX_EQUIP]; // 34 - 65
	unsigned short Affect[MAX_AFFECT]; // 66 - 97
	unsigned short Guild; // 98 - 99
	STRUCT_SCORE Score; // 100 - 127
	unsigned char CreateType; // 128
	unsigned char GuildMemberType; // 129
	unsigned char AnctCode[16]; // 130 - 145
	char Tab[26]; // 146 - 171
	int	Citizen; // 172 - 175
};

struct MSG_CombineItem
{
	_MSG;

	STRUCT_ITEM Item[8];
	char InvenPos[8];
};

typedef struct
{
	MSG_STANDARD Header;

	char Name[24];
	STRUCT_ITEM Item[12];
	unsigned char Slot[12];
	int Gold[12];
	short Unknown;
	short Index;
} p397h;

struct p398h
{
	MSG_STANDARD Header;

	int Slot;
	int Index;
	int Gold;
	int Unknown;

	STRUCT_ITEM Item;
};

struct p182h
{
	MSG_STANDARD	Header;

	BYTE type;
	BYTE null;
	uint16_t slot;
	STRUCT_ITEM item;

};

const short  _pD1Dh = (108 | FLAG_CLIENT2GAME | FLAG_CLIENT2GAME);
struct pD1Dh
{
	_MSG ;
	char message[92];
	int color;
};
 
const uint16_t _pDNTh = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct pDNTh
{
	MSG_STANDARD Header; // 0 - 11
	int donate;	
};
const short  _p3BBh = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct p3BBh
{
	_MSG;
	unsigned short cur_mob;
	unsigned short max_mob;
};

struct p37Fh
{
	MSG_STANDARD Header;
	short Unk, Level, MaxHP, CurHP, ClientId;
	char Name[16];
	int Unk2;
	short TargetId;
};
struct Quiz
{
	MSG_STANDARD Header;
	char title[96];
	char asw[4][32];
	int correct;
};

struct PowderLak
{
	int Destroy;

	int MessageRate;

	int Sanc_10;

	int Rate[5];
};
const uint16_t _SvRtn = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct  SvRtn
{
	char Server[39];
};
const uint16_t _UpdateItemQuest = (108 | FLAG_CLIENT2GAME | FLAG_CLIENT2GAME);
struct UpdateItemQuest
{
	MSG_STANDARD Header;

	struct _CharacterInfo
	{
		char Empty[50];

		struct
		{
			uint16_t CytheraArch;
		}Especial;

		struct
		{
			uint64_t sub : 1;

			uint64_t camp_1 : 1;
			uint64_t camp_2 : 1;
			uint64_t camp_3 : 1;
			uint64_t camp_4 : 1;

			uint64_t OutrasQuests : 59;
		}QuestData;

		struct _CampTrein
		{
			uint16_t mobI;
			uint16_t mobII;
			uint16_t mobIII;
			uint16_t mobIV;

		}CampTrein;

	} CharacterInfo[MOB_PER_ACCOUNT];
};

const uint16_t _DropGlobal = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct DropGlobal
{
	STRUCT_ITEM Item;
	short GuildID;
	short PosX;
	short PosY;
	short Owner;
	BYTE Rotation;
	bool MobKilled;
	char OwnerName[16];
	int GenerateTime;
};


struct LocalCP
{
	STRUCT_POSITION min;

	STRUCT_POSITION max;

	LocalCP(int x1, int y1, int x2, int y2)
	{
		this->min.X = (uint16_t)x1;
		this->min.Y = (uint16_t)y1;
		this->max.X = (uint16_t)x2;
		this->max.Y = (uint16_t)y2;
	}
};

struct ClearLocal
{
	uint16_t minutes;
	STRUCT_POSITION MinCoords;
	STRUCT_POSITION MaxCoords;

	ClearLocal(uint16_t minutes, STRUCT_POSITION MinCoords, STRUCT_POSITION MaxCoords)
	{
		this->minutes = minutes;
		this->MinCoords = MinCoords;
		this->MaxCoords = MaxCoords;
	}
};

struct MessageTime
{
	int minutes;

	char text[102];

	MessageTime(int minutes, char text[102])
	{
		this->minutes = minutes;
		sprintf_s(this->text, "%s", text);
	}
};

struct SpecialArea
{
	uint16_t level;
	uint16_t classe;
	STRUCT_POSITION MinCoords;
	STRUCT_POSITION MaxCoords;

	SpecialArea(uint16_t level, uint16_t classe, STRUCT_POSITION MinCoords, STRUCT_POSITION MaxCoords)
	{
		this->level = level;
		this->classe = classe;
		this->MinCoords = MinCoords;
		this->MaxCoords = MaxCoords;
	}
};

struct SpecialAreaOnMac
{
	STRUCT_POSITION MinCoords;
	STRUCT_POSITION MaxCoords;

	SpecialAreaOnMac(STRUCT_POSITION MinCoords, STRUCT_POSITION MaxCoords)
	{
		this->MinCoords = MinCoords;
		this->MaxCoords = MaxCoords;
	}
};

struct BuyDonate
{
	uint16_t id;

	STRUCT_ITEM item;

	uint16_t price;

	uint16_t store;

	BuyDonate(STRUCT_ITEM item, uint16_t price)
	{
		this->item = item;
		this->price = price;
	}

	BuyDonate(uint16_t item, uint16_t price)
	{
		this->item.sIndex = item;
		this->price = price;
	}
};

struct RoyalBit
{
	uint16_t id;

	STRUCT_ITEM item;

	uint16_t price;

	RoyalBit(STRUCT_ITEM item, uint16_t price)
	{
		this->item = item;
		this->price = price;
	}

	RoyalBit(uint16_t item, uint16_t price)
	{
		this->item.sIndex = item;
		this->price = price;
	}
};

const uint16_t _pFDEh = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct pFDEh {
	MSG_STANDARD Header; // 0 - 11
	char numeric[6];
	char others[10];
	int32_t change;
};
const uint16_t _STRUCT_SERVERLIS = (108 | FLAG_CLIENT2GAME | FLAG_CLIENT2GAME);
struct STRUCT_SERVERLIST
{
	struct
	{
		char Site[64];
		char IP[16];
		char Unk[624];
	}ServerList[10];
};

const uint16_t _STRUCT_SERVERNAME = (108 | FLAG_CLIENT2GAME | FLAG_CLIENT2GAME);
struct STRUCT_SERVERNAME
{
	//A Leitura é feita invertida [Ultimo server primeiro, finalizando com o Novato que é o primeiro]
	struct
	{
		char Nome[9];
	}ServerName[10];
};
const uint16_t _STRUCT_NOMEJANEL = (108 | FLAG_CLIENT2GAME | FLAG_CLIENT2GAME);
struct STRUCT_NOMEJANELA
{
	char Nome[20];
};
const uint16_t _p383h = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct p383h {
	MSG_STANDARD Header;
	STRUCT_ITEM TradeItem[15];
	unsigned char TradeItemSlot[15];
	unsigned char Unknow;
	int Gold;
	bool Confirma;
	unsigned short OtherClientid;
};
const uint16_t _GateGlobal = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct GateGlobal
{
	int index;
	int delay;
	int status;
	int mode;
};

struct STRUCT_CITEM {
	STRUCT_ITEM ITEM;
	int  Mode;
	int  PosX, PosY;
	int  GridCharge;
	int  State;
	int  Rotate;
	int  Delay;
	int  Decay;
	int  Height;
	int  Money;
	int  Owner;
};

const uint16_t _p374h = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct p374h {
	MSG_STANDARD Header;
	int InitID;
	short Status;
	char Height;
	char Dummy;
};

const uint16_t _p26Eh = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct p26Eh {
	MSG_STANDARD Header;
	STRUCT_POSITION loc;
	unsigned short Index;
	STRUCT_ITEM ItemP;
	BYTE Rotation;
	BYTE Status;
	BYTE collision;
	BYTE sound;
	short unk1;
};

struct NPCTeleport
{
	char Name[16];

	STRUCT_POSITION StartPosition;

	INT16 ControleLimite;

	STRUCT_POSITION MinCoords;

	STRUCT_POSITION MaxCoords;

	NPCTeleport(char Name[16], STRUCT_POSITION StartPosition, INT16 ControleLimite, STRUCT_POSITION MinCoords, STRUCT_POSITION MaxCoords)
	{
		memcpy(this->Name, Name, 16);
		this->StartPosition = StartPosition;
		this->ControleLimite = ControleLimite;
		this->MinCoords = MinCoords;
		this->MaxCoords = MaxCoords;
	}
};
struct ItemNPCTrade
{
	int RateMin;

	int RateMax;

	STRUCT_ITEM ItemReturn;
};

struct NPCTrade
{
	char Name[16];

	INT16 ItemRequest;

	ItemNPCTrade Premiun;

	NPCTrade(char Name[16], INT16 ItemRequest, ItemNPCTrade Premiun)
	{
		memcpy(this->Name, Name, 16);
		this->ItemRequest = ItemRequest;
		this->Premiun = Premiun;
	}
};


struct ItemLevel
{

	BYTE tipo;

	uint16_t level;

	BYTE classe;

	STRUCT_ITEM item;

	ItemLevel(BYTE tipo, uint16_t level, BYTE classe, STRUCT_ITEM item)
	{
		this->tipo = tipo;
		this->level = level;
		this->classe = classe;
		this->item = item;
	}
};

struct RvR_
{
	bool happening;

	int Hekalotia;

	int Akelonia;

	bool TorreHekalotia;

	bool TorreAkelonia;

	int TempoTorreHekalotia;

	int TempoTorreAkelonia;
};

struct STConnectBuffer
{
	struct
	{
		char AccountName[16];
		bool Exists;
		bool Banido;
		bool Analise;
		bool PC;
		bool Permanente;
		char Motivo[100];
		bool DBLoaded;
		DWORD Timeout;
		bool Completed;
	}Buffer[100];


	int Register(const char* Account)
	{
		if (strlen(Account) < 4)
			return -1;

		auto Timer = timeGetTime();
		for (auto i = 0; i < 1000; i++)
		{
			if (Timer > Buffer[i].Timeout || Buffer[i].Timeout == 0)
			{
				Clear(i);
				strcpy(Buffer[i].AccountName, Account);
				Buffer[i].Timeout = Timer + 60000;
				return i;
			}
		}
		return -1;
	}

	bool Registered(const char* Account)
	{
		auto Timer = timeGetTime();
		for (auto i = 0; i < 1000; i++)
		{
			if (Timer > Buffer[i].Timeout)
			{
				Clear(i);
				continue;
			}

			if (Buffer[i].Timeout == 0 || strlen(Buffer[i].AccountName) < 4)
				continue;

			if (!strcmp(Buffer[i].AccountName, Account))
				return true;
		}
		return false;
	}

	int InBuffer(const char* Account)
	{
		if (strlen(Account) < 4)
			return -1;

		auto Timer = timeGetTime();
		for (auto i = 0; i < 1000; i++)
		{
			if (Timer > Buffer[i].Timeout)
			{
				Clear(i);
				continue;
			}

			if (strlen(Buffer[i].AccountName) < 4)
				continue;

			if (!strcmp(Buffer[i].AccountName, Account))
				return i;
		}
		return -1;
	}

	bool Exists(const char* Account)
	{
		if (strlen(Account) < 4)
			return false;

		auto Timer = timeGetTime();
		for (auto i = 0; i < 1000; i++)
		{
			if (Timer > Buffer[i].Timeout)
			{
				Clear(i);
				continue;
			}

			if (strlen(Buffer[i].AccountName) < 4)
				continue;

			if (!strcmp(Buffer[i].AccountName, Account))
				return Buffer[i].Exists;
		}
		return false;
	}

	void Clear(int i)
	{
		memset(Buffer[i].AccountName, 0, 16);
		Buffer[i].Exists = false;
		Buffer[i].DBLoaded = false;
		Buffer[i].Banido = false;
		Buffer[i].Analise = false;
		Buffer[i].PC = false;
		Buffer[i].Permanente = false;
		memset(Buffer[i].Motivo, 0, 100);
		Buffer[i].Timeout = 0;
		Buffer[i].Completed = false;
	}
};
struct Kephra {
	uint8_t alive;

	uint8_t up_exp;

	uint8_t time_respawn;

	uint8_t day_respawn;

	uint16_t guild;
};

struct MobDrop
{
	STRUCT_ITEM item;
	char name[12];

	MobDrop(STRUCT_ITEM item, char name[12])
	{
		memcpy(&this->item, &item, sizeof(STRUCT_ITEM));
		sprintf_s(this->name, 12, "%s", name);
	}
};
struct Tower
{
	bool happening;

	bool tower;

	uint16_t time;
};

const uint16_t _ServerData = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct ServerData
{

	uint16_t Manutence;

	uint16_t Version;

	uint16_t RvR;

	uint16_t Tower;

	uint16_t RvRHour;

	uint16_t TowerHour;

	uint16_t TowerPoints;

	uint16_t TowerWinnerID;

	char TowerWinner[20];

	uint16_t RvRWinner;

	uint16_t RvRBonus;

	uint16_t limite;

	uint16_t limite_total;

	uint16_t EventoDrop;

	uint16_t ItemDrop;

	uint16_t RateDrop;

	uint16_t RateAilyn;

	char MobDrop[16];

	int TotalItens;

	int ControleItens;

	int ItensDropados;

	bool hackerControl;

	bool packetControl;

	bool controlExp;

	bool userDataControl;

	bool acessControl;
};
struct Boss
{
	struct LanN
	{
		int mobs;

		bool alive;

	}_LanN;

};

const uint16_t _p36Ch = (108 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct p36Ch
{
	_MSG;
	STRUCT_POSITION Origin;
	int32_t Speed; 
	char Command[24];
	STRUCT_POSITION Dest;
};
#endif // !PACKET_STRUCT_H
