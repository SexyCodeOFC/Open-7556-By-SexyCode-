#include "stdafx.h"
ServerStatus ServerInfo;
UserData pUserData[MAX_USER];
CMob* pMob;
CUser* pUser;
CItem* pItem;
CPSock* DBServerSocket;
STRUCT_ITEMLIST* g_pItemList;
STRUCT_SPELL* g_pSpell;
CNPCGenerator* mNPCGen;
STRUCT_GUILD GuildInfo[MAX_USER];
MSG_STANDARD LastPacket;
STRUCT_MILEAGESTORE pMileageStore[500];
STRUCT_GUILD(*g_pGuild)[4096];
Moeda coins[500];
char(*g_pMessageStringTable)[MAX_STRINGTABLESIZE];
unsigned short (*pItemGrid)[MAX_GRIDX];
unsigned short (*pMobGrid)[MAX_GRIDX];
char temp[4096]; 
int wtGuildKiller = 0;
int wtState;
int g_MileageCountLine = 0;
char(*g_pFormation)[12][2]; 
int NumberMoedas;