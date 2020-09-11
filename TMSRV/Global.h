#ifndef GLOBAL_H
#define GLOBAL_H

extern UserData pUserData[MAX_USER];
extern CMob* pMob;
extern CUser* pUser;
extern CItem* pItem;
extern CPSock* DBServerSocket;
extern STRUCT_ITEMLIST* g_pItemList;
extern STRUCT_SPELL* g_pSpell;
extern char(*g_pMessageStringTable)[MAX_STRINGTABLESIZE];
extern unsigned short(*pItemGrid)[MAX_GRIDX];
extern unsigned short(*pMobGrid)[MAX_GRIDX];
extern char temp[4096]; 
extern CNPCGenerator* mNPCGen;
extern STRUCT_GUILD GuildInfo[MAX_USER];
extern MSG_STANDARD LastPacket;
extern int wtGuildKiller;
extern int wtState;
extern STRUCT_MILEAGESTORE pMileageStore[500];
extern int g_MileageCountLine;
extern char(*g_pFormation)[12][2]; 
extern STRUCT_GUILD(*g_pGuild)[4096]; 
extern ServerStatus ServerInfo;
extern int NumberMoedas;
extern Moeda coins[500];
#endif // !GLOBAL_H
