#define callCdecl(dwAddress, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) dwAddress)
#define callThiscall(dwAddress, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) dwAddress)
#define callThiscallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 4))))
#define callstdcall(dwAddress, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) dwAddress)

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Func
{
private:
	Func() = delete;
	virtual ~Func() = delete;
	Func(const Func&) = delete;
	Func& operator=(const Func&) = delete;
public:

	static int ReturnAmount(STRUCT_ITEM* item);
	static void SendGuildMedal(int clientId);
	static STRUCT_GUILD* GetGuild(int guildIndex);
	static const std::vector<uint16_t> PlayerInAreaMac(const int32_t client, const STRUCT_POSITION minPos, const STRUCT_POSITION maxPos, char* mac);
	static void UpdateStatus(int clientId);
	static void SendSenhaGrupo(int clientId);
	static void SendDonateUpdate(int clientId);  
	static void SendPacket2(int32_t client, void* const pMsg, int32_t len);
	static void SendItem2(int clientId, STRUCT_ITEM* item);
	static bool StartCoinsNPC();
	static bool ClearAmountItem(uint16_t client, uint16_t item, uint16_t quant);
	static int  GetItemSanc(STRUCT_ITEM *item);
	static int  BASE_GetItemSanc(STRUCT_ITEM *item);
	static void  RemoveItens(int  loop, STRUCT_MOB *player, MSG_CombineItem *p);
	static void  GiveItem(int clientid, int ItemID, int add1, int add2, int add3); 
	static void SendSignalParmArea(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm);
	static void  RefinarItemMais(STRUCT_ITEM *item, int value);
	static int BASE_GetItemGem(STRUCT_ITEM *item);
	static int  GetMatchCombineOdin(STRUCT_ITEM *Item);
	static int GetUserInAreaMac(int notUsage, int x1, int y1, int x2, int y2);
	static char* strFmt(const char* str, ...);
	static CUser* GetUserFromIndex(int conn);
	static void CloseWindows(int clientId);
	static INT32 getIndexStruct(UINT32 pBase, UINT32 pStruct, size_t sizeStruct);
	static void GetCurrentScore(int32_t client);
	static int32_t CheckGetLevel(int32_t client);
	static bool WriteData(uint32_t connId, char *folderName);
	static void AmountMinus(STRUCT_ITEM* item);
	static bool File_exists(const char *filename);
	static void SendPacket(int32_t client, uint8_t* pMsg, int32_t len);
	static void SendDBPacket(char* pMsg, int32_t len);
	static void SendAddPacket(int32_t client, uint8_t* pMsg, int32_t len);
	static void NpcTab(int mob, MSG_CreateMob *sm);
	static int32_t GetPlayerClass(int32_t client);
	static void CMobInitialize(int Index);
	static const std::vector<uint16_t> getPlayerLoja(const int client, char* mac);
	static int ReturnSlotEmpty(int clientId, SlotType Type);
	static int32_t GetFirstSlot(int32_t client, SlotType slot, uint16_t itemId, char* Msg);
	static bool LoadAccount(int32_t client, const char* accountName);
	static bool SaveAccount(int32_t client, const char* accountName); 
	static uint8_t ReadMacList(char* macAddress);
	static void MacBan(uint16_t conn);
	static void ClearItemInventory(int clientId, int slot);
	static void UpdateItemInventory(int clientId, int slot);
	static int GetUserFromSocket(int Sock);
	static bool LoadGuildInfo(int conn);
	static void SendGuildInfo(int conn);
	static int ReturnItemSlot(int clientId, SlotType slot, int itemId);
	static void SendChatColor(const uint16_t conn, char* Msg, int Color, const uint16_t Type);
	static bool FileExist(const char* Name);
	static bool ReadMileageListItem();
	static bool CheckItemCelestial(uint16_t ItemId);
	static int PossivelRefinar(STRUCT_ITEM *item);
	static STRUCT_ITEMLIST* GetItemListItem(uint16_t itemId);
	static int GetArmorType(short ItemID);
	static bool CheckArchItem(int id);
	static const std::vector<uint16_t> CheckMacUserInArea(const STRUCT_POSITION minPos, const STRUCT_POSITION maxPos, char* mac);
	static void  DoRemoveHide(int conn);
	static int GetAttackMiss(int conn, int a_iTarget);
	static void ClearItemEquip(int clientId, int slot);
	static void UpdateItemEquip(int clientId, int slot);
	static int GetDistance(int x1, int y1, int x2, int y2);
};
#endif // !FUNCTIONS_H
