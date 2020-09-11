#ifndef NATIVE_FUNCTIONS_H
#define NATIVE_FUNCTIONS_H

#define f_ptr (__cdecl *)

#ifdef _DBSRV
static void(*ReportLog)() = (void(__cdecl*)()) 0x401415;
#elif _TMSRV


/***************************************************************************************************************
	OTHER
****************************************************************************************************************/
static void(*Log)(char* str1, char* str2, uint32_t ip) = (void(*)(char*, char*, uint32_t)) 0x4015D7;
static int32_t(*AddCrackError)(int32_t, int32_t, int32_t) = (int32_t(*)(int32_t, int32_t, int32_t)) 0x44EBA0;
static void(*MobKilled)(int32_t, int32_t, int32_t, int32_t) = (void(*)(int32_t, int32_t, int32_t, int32_t)) 0x4BADF0;
static void(*ProcessSecTimer)() = (void(*)()) 0x4AF390;
static void(*ProcessMinTimer)() = (void(*)()) 0x4B13B0;
static void(*SetTotKill)(int32_t conn, int32_t value) = (void(*)(int32_t conn, int32_t value)) 0x4017AD;
static void(*ProcessClientMessage)(int32_t client, char* pMsg) = (void(*)(int32_t, char*)) 0x45E200;
static int32_t(*ReadMob)(STRUCT_MOB*, char* folder) = (int32_t(*)(STRUCT_MOB*, char*)) 0x4013E8;
static void(*GenerateMob)(int32_t, int32_t, int32_t) = (void(*)(int32_t, int32_t, int32_t)) 0x401C30;
static void(*GenerateRandomMob)(int32_t) = (void(*)(int32_t)) 0x401627;
static int(*GenerateSummon)(int conn, int SummonID, STRUCT_ITEM* Item) = (int(__cdecl*)(int, int, STRUCT_ITEM*)) 0x401744;
static int32_t(*CreateMobPista)(char*, int32_t, int32_t, char*, int32_t) = (int32_t(*) (char*, int32_t, int32_t, char*, int32_t)) 0x40177B;
static int32_t(*CreateMob)(char *, int32_t, int32_t, char *) = (int32_t(*) (char *, int32_t, int32_t, char *)) 0x40177B;
static void(*CharLogOut)(int32_t client) = (void(*)(int32_t)) 0x401528;
static void(*ClearArea)(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = (void(*)(int32_t, int32_t, int32_t, int32_t)) 0x401ACD;
static void(*ClearAreaLevel)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t min, int32_t max) = (void(*)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)) 0x401230;
static int32_t(*GridMulticast)(int32_t posX, int32_t posY, void* msg, int32_t zero) = (int32_t(__cdecl *)(int32_t, int32_t, void*, int32_t)) 0x004014FB;
static int32_t(*SetAffect)(int32_t client, int32_t index, int32_t time, int32_t value) = (int32_t(*)(int32_t, int32_t, int32_t, int32_t)) 0x4C3FD0;
static int(*PutItem)(int32_t user, STRUCT_ITEM* item) = (int32_t(__cdecl*)(int32_t, STRUCT_ITEM*)) 0x0401401;
static void(*SaveUser)(int32_t client, int32_t e) = (void(__cdecl*)(int32_t, int32_t)) 0x4B9480;
static int(*CheckFailAccount)(char* account) = (int32_t(__cdecl*)(char*)) 0x4017A8;
static void(*RemoveTrade)(int32_t client) = (void(__cdecl*)(int32_t)) 0x40164F;
static int(*CreateItem)(int x, int y, STRUCT_ITEM* item, int Rotate, int Create, int Unknow) = (int32_t(*)(int, int, STRUCT_ITEM*, int, int, int)) 0x4016EA;
static void(*ProcessImple)(int conn, int level, char* str) = (void(*)(int, int, char*)) 0x401091;
static void(*CrackLog)(int conn, char* log) = (void(__cdecl*)(int, char*)) 0x4010EB;
static int(*GetEmptyAffect)(int conn, int Type) = (int(__cdecl*)(int, int)) 0x401433;
static void(*SetPKPoint)(int conn, int point) = (void(__cdecl*)(int, int)) 0x4014C4;
static int(*GetCurKill)(int conn) = (int(__cdecl*)(int)) 0x4013BB;
static void(*SetReqMp)(int conn) = (void(__cdecl*)(int)) 0x401C17;
static void(*DoRemoveAffect)(int conn, int Affect) = (void(__cdecl*)(int, int)) 0x401CB7;
static void(*SendReqParty)(int conn, int Leader, int PartyID) = (void(__cdecl*)(int, int, int)) 0x401591;
static int(*GetCitizen)(int conn) = (int(__cdecl*)(int)) 0x40109B;
static void(*DeleteMob)(int conn, int Type) = (void(__cdecl*)(int, int)) 0x401B90;
static void(*DeleteMobPista)(int32_t client, int32_t mob, int32_t reason, int32_t) = (void(*)(int32_t, int32_t, int32_t, int32_t)) 0x447A60;
static void(*GetGuildName)(int GuildIndex, char* strName) = (void(__cdecl*)(int, char*)) 0x4011CC;
static void(*SetGuildFame)(int GuildIndex, int Value) = (void(__cdecl*)(int, int)) 0x401C03;
static int(*PutItemCargo)(int conn, int ItemID, STRUCT_ITEM* Item) = (int(__cdecl*)(int, int, STRUCT_ITEM*)) 0x40144C;
static int(*UpdateItem)(int GateID, int State, int* Height) = (int(__cdecl*)(int, int, int*)) 0x401A14;
static void(*SendAddParty)(int, int, int) = (void(__cdecl*)(int, int, int)) 0x4016AE;
static void(*DeleteGenerateMob)(int Index, int Type) = (void(__cdecl*)(int, int)) 0x401857;
static int(*GetEmptyNPCMob)() = (int(__cdecl*)()) 0x401546;
static int(*GetEmptyMobGrid)(int Index, int* PosX, int* PosY) = (int(__cdecl*)(int, int*, int*)) 0x4015D2;
static void(*GetItemHpBonus)(int Index) = (void(__cdecl*)(int)) 0x4015AF;
static int(*GridMulticast2)(int TargetX, int TargetY, MSG_STANDARD* m, int Type) = (int(__cdecl*)(int, int, MSG_STANDARD*, int)) 0x4014FB;
static int(*GetMatchCombineAilyn)(STRUCT_ITEM* Item) = (int(__cdecl*)(STRUCT_ITEM*)) 0x4012E4;
static int(*ReturnCorrectitem)(int Selado, int Equivalente) = (int(*)(int, int)) 0x4DAEB0;
static void(*RegenMob)(int32_t client) = (void(*)(int32_t)) 0x4AB3A0;
/***************************************************************************************************************
	BASE
****************************************************************************************************************/ 
static int32_t(*BASE_GetHpMp)(STRUCT_MOB*) = (int32_t(*)(STRUCT_MOB*)) 0x4040F0;
static int32_t(*BASE_GetItemAbility)(STRUCT_ITEM* item, uint8_t eff) = (int32_t(*)(STRUCT_ITEM*, uint8_t)) 0x40191F;
static int32_t(*BASE_GetItemAmount)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x4013D9;
static void(*BASE_SetItemAmount)(STRUCT_ITEM* item, int32_t amount) = (void(*)(STRUCT_ITEM*, int32_t)) 0x40187F;
static int32_t(*BASE_GetMobAbility)(STRUCT_MOB* mob, uint8_t eff) = (int32_t(*)(STRUCT_MOB*, uint8_t)) 0x4088A0;
static int32_t(*BASE_GetMaxAbility)(STRUCT_MOB* mob, uint8_t eff) = (int32_t(*)(STRUCT_MOB*, uint8_t)) 0x408D60;
static int32_t(*BASE_GetMobChecksum)(STRUCT_MOB* mob) = (int32_t(__cdecl*)(STRUCT_MOB*)) 0x408E20;
static bool(*BASE_CheckValidString)(char*) = (bool(*)(char*)) 0x408F00;
static void(*BASE_ApplyAttribute)(char*, int32_t) = (void(*)(char*, int32_t)) 0x4093B0;
static void(*BASE_SpaceToUnderbar)(char*) = (void(*)(char*)) 0x4095D0;
static void(*BASE_UnderBarToSpace)(char*) = (void(*)(char*)) 0x409650;
static void(*BASE_ClearMob)(STRUCT_MOB*) = (void(*)(STRUCT_MOB*)) 0x4096F0;
static int32_t(*BASE_GetGuild)(int32_t, int32_t) = (int32_t(*)(int32_t, int32_t)) 0x40CF50;
static void(*BASE_ClearItem)(STRUCT_ITEM*) = (void(*)(STRUCT_ITEM*)) 0x40D420;
static void(*BASE_SetValidString)(char*) = (void(*)(char*)) 0x409000;
static int32_t(*BASE_GetSuccessRate)(STRUCT_ITEM*, int32_t) = (int32_t(*)(STRUCT_ITEM*, int32_t)) 0x407EC0;
static int32_t(*BASE_GetItemSanc)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x40103C;
static int32_t(*BASE_SetItemSanc)(STRUCT_ITEM* item, int32_t value, int32_t delta) = (int32_t(*)(STRUCT_ITEM*, int32_t, int32_t)) 0x401109;
static int32_t(*BASE_GetBonusSkillPoint)(STRUCT_MOB* mob) = (int32_t(*)(STRUCT_MOB*)) 0x403480;
static int32_t(*BASE_GetBonusScorePoint)(STRUCT_MOB* mob, int32_t, int32_t) = (int32_t(*)(STRUCT_MOB*, int32_t, int32_t)) 0x4015FA;
static int32_t(*BASE_GetDistance)(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = (int32_t(*)(int32_t, int32_t, int32_t, int32_t)) 0x411C00;
static int32_t(*BASE_GetVillage)(int32_t x1, int32_t y1) = (int32_t(*)(int32_t, int32_t)) 0x401C08;
static int(*BASE_CheckPacket)(MSG_STANDARD* m) = (int(*)(MSG_STANDARD*)) 0x40137F;
static void(*bGetCurrentScore)(STRUCT_MOB& MOB, STRUCT_AFFECT* Affect, CMob* extra, int* PosX, int* PosY, int* ForceDamage, int* Abs, int* Accuracy, signed int a9, int MotalFace) = (void(*)(STRUCT_MOB & MOB, STRUCT_AFFECT * Affect, CMob * extra, int* PosX, int* PosY, int* ForceDamage, int* Abs, int* Accuracy, signed int a9, int MotalFace)) 0x00409830;
static void(*BASE_GetItemCode)(STRUCT_ITEM* Item, char* ItemCode) = (void(__cdecl*)(STRUCT_ITEM*, char*)) 0x401B1D;
static void(*BASE_SetItemCode)(STRUCT_ITEM* Item, char* ItemCode) = (void(__cdecl*)(STRUCT_ITEM*, char*)) 0x401447;
/***************************************************************************************************************
	SEND FUNC
****************************************************************************************************************/
static void(*SendAffect)(int32_t clientid) = (void(*)(int32_t)) 0x449EE0;
static void(*SendClientMessage)(int32_t clientid, char* msg) = (void(*)(int32_t, char*)) 0x401B63;
static void(*SendScore)(int32_t client) = (void(*)(int32_t)) 0x4018B1;
static void(*SendEtc)(int32_t client) = (void(*)(int32_t)) 0x401348;
static void(*SendSay)(int32_t client, char* msg) = (void(*)(int32_t, char*)) 0x401550;
static void(*SendClientSignalParm)(int32_t client, int32_t id, uint16_t packetId, int32_t param) = (void(*)(int32_t, int32_t, uint16_t, int32_t)) 0x4015FF;
static void(*SendCarry)(int32_t client) = (void(*)(int32_t)) 0x4018B6;
static void(*SendItem)(int32_t client, int32_t slotType, int32_t slot, STRUCT_ITEM*) = (void(*)(int32_t, int32_t, int32_t, STRUCT_ITEM*)) 0x401960;
static void(*SendEmotion)(int32_t client, int32_t x, int32_t y) = (void(*)(int32_t, int32_t, int32_t)) 0x448EA0;
static void(*DoTeleport)(int32_t, int32_t, int32_t, int32_t) = (void(*)(int32_t, int32_t, int32_t, int32_t)) 0x401A19;
static void(*SendHpMode)(int32_t client) = (void(__cdecl*)(int32_t)) 0x4012F3;
static void(*SendNotice)(char*) = (void(*)(char *)) 0x0401479;
static void(*SendEnvEffect)(int32_t x, int32_t y, int32_t x2, int32_t y2, int32_t effectID, int32_t time) = (void(*)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)) 0x4018E8;
static void(*SendSetHpMp)(int32_t client) = (void(__cdecl*)(int32_t)) 0x4018A7;
/***************************************************************************************************************
	GET FUNC
****************************************************************************************************************/
static CMob*(*GetMobFromIndex)(int32_t client) = (CMob*(*)(int32_t)) 0x4016B3;
static int32_t(*GetEmptyUser)() = (int32_t(*)()) 0x401726;
static int32_t(*GetUserByName)(char* name) = (int32_t(*)(char*)) 0x4010D7;
static int32_t(*GetCreateMob)(int32_t, MSG_CreateMob*) = (int32_t(*)(int32_t, MSG_CreateMob*)) 0x4010FF;
static STRUCT_ITEM*(*GetItemPointer)(STRUCT_MOB *mob, STRUCT_ITEM *cargo, int32_t type, int32_t slot) = (STRUCT_ITEM*(*)(STRUCT_MOB*, STRUCT_ITEM*, int32_t, int32_t)) 0x401CA3;
static int32_t(*GetExpApply)(int32_t, int32_t, int32_t) = (int32_t(*)(int32_t, int32_t, int32_t)) 0x427020;
static int32_t(*GetUserInArea)(int32_t, int32_t, int32_t, int32_t, char*) = (int32_t(*)(int32_t, int32_t, int32_t, int32_t, char*)) 0x040145B;
static int(*GetEmptyItemGrid)(int* gridx, int* gridy) = (int(*)(int*, int*)) 0x40179E;
/***************************************************************************************************************
	CPSock
****************************************************************************************************************/
static int32_t(__stdcall* CPSock_AddMessage)(void* thisPtr, char*, int32_t) = (int32_t(__stdcall*)(void*, char*, int32_t)) 0x401203;
static int32_t(__stdcall* CPSock_SendOneMessage)(void* thisPtr, char*, int32_t) = (int32_t(__stdcall*)(void*, char*, int32_t)) 0x40132A;
static int32_t(__stdcall* CPSock_SendMessageA)(void* thisPtr) = (int32_t(__stdcall*)(void*)) 0x4019FB;
static int32_t(__stdcall* CPSock_SendAddMessage)(void* thisPtr, char*, int32_t, int32_t) = (int32_t(__stdcall*)(void*, char*, int32_t, int32_t)) 0x401B40;
static int32_t(__stdcall* _AddMessage)(void* thisPtr, char*, int32_t) = (int32_t(__stdcall*)(void*, char*, int32_t)) 0x420ED0;
static char* (__stdcall* CPSock_ReadMessage)(CPSock* thisPtr, int* ErrorCode, int* ErrorType) = (char* (__stdcall*)(CPSock*, int*, int*)) 0x40124E;
static char(*_ReadMessage)(int*, int*) = (char(__cdecl*)(int*, int*)) 0x4205F0;
/***************************************************************************************************************
	CMOB
****************************************************************************************************************/
static int32_t(__stdcall* _CheckGetLevel)(CMob* thisPtr) = (int32_t(__stdcall*)(CMob*)) 0x41B210;
static void(__stdcall* _GetCurrentScore)(CMob* thisPtr, int32_t clientid) = (void(__stdcall*)(CMob*, int32_t)) 0x4016EF;
static int32_t(__stdcall* _GetClass)(CMob* thisPtr) = (int32_t(__stdcall*)(CMob* thisPtr)) 0x401640;
static void(__stdcall* _Initialize)(CMob* thisPtr) = (void(__stdcall*)(CMob*)) 0x40193D;
/***************************************************************************************************************
	CUSER
****************************************************************************************************************/
static void(*CloseUser)(int32_t client) = (void(__cdecl*)(int32_t)) 0x4B8240;

#elif _CLIENT
 
static int32_t(*BASE_GetItemAmount)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x5386C1;
static int32_t(*BASE_GetItemSanc)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x537FEE;
static int32_t(*BASE_GetItemAbility)(STRUCT_ITEM* item, uint8_t ef) = (int32_t(*)(STRUCT_ITEM*, uint8_t)) 0x5368EE;
static void(*SendPacketDirect)(char*, int) = (void(__cdecl*)(char*, int)) 0x54B02D;
#define GetItemName(itemId) reinterpret_cast<char*>((itemId * 0x8C) + 0xD87150)
#define GetItemPrice(itemId) *reinterpret_cast<uint32_t*>((itemId * 0x8C) + 0xD871D0)
#define GetItemList(itemId) reinterpret_cast<STRUCT_ITEMLIST*>((itemId * 0x8C) + 0xD87150)
#define callCdecl(dwAddress, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) dwAddress)
#define callThiscall(dwAddress, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) dwAddress)
#define callThiscallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 4))))

static void(*SendPacket)(char*, int) = (void(__cdecl*)(char*, int)) 0x54B02D;
static int32_t __cdecl CalcAddress(int32_t addr)
{
	return (int32_t)GetModuleHandleA(0) + addr;
}

#define addr_client_chat_1 CalcAddress(0x005B8113 - 0x400000)
#define addr_client_chat_2 CalcAddress(0x00406AC8 - 0x400000)
#define addr_client_chat_3 CalcAddress(0x00408569 - 0x400000)
#define IPLocal "144.217.101.69"
#define IPServer "144.217.101.69"
#define IPTeste "144.217.101.69"
#endif

#endif // !NATIVE_FUNCTIONS_H
