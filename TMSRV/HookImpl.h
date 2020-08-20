#ifndef HOOK_IMPL_H
#define HOOK_IMPL_H

class HookImpl
{
private:
	HookImpl() = delete;
	virtual ~HookImpl() = delete;
	HookImpl(const HookImpl&) = delete;
	HookImpl& operator=(const HookImpl&) = delete;

public:
	static bool __stdcall Commands(const int32_t client, p334h* const packet);
	static bool ExtraElmo(int32_t client, char* pMsg);
	static bool ExtraPeito(int32_t client, char* pMsg);
	static bool ExtraCalça(int32_t client, char* pMsg);
	static bool ExtraBota(int32_t client, char* pMsg);
	static bool ExtraLuva(int32_t client, char* pMsg);
	static bool ExtraArma(int32_t client, char* pMsg);
	static int ExpControl(int conn, int Exp);
	static bool __stdcall ProcessClientMessage(int32_t conn, char* pMsg);
	static bool __stdcall MobKilledEvent(int32_t generID, int32_t killed, int32_t killer);
	static void __stdcall FixBuyItem(int conn, MSG_Buy* m);
	static BYTE* SendPacket(BYTE *pBuffer, UINT32* socketId, UINT32 packetSize);
	static bool __stdcall AddJoinableItens(STRUCT_ITEM* item);
	static bool __stdcall AfterEnterWorld(int clientId);
	static void __stdcall ProcessDBMessage_AccountLogin(int32_t client);
	static void __stdcall SaveUser(int32_t client);
	static void __stdcall CloseUser(int32_t client); 
	static bool __stdcall OnNpcClick(int32_t client, p28Bh* packet);

	static char* __stdcall ReadMessage(CPSock* thisPtr, int* ErrorCode, int* ErrorType);
	static BOOL __stdcall AddMessage(CPSock* thisPtr, char* pMsg, int Size);

	static int __stdcall HKD_AddMessage(int Socket, MSG_STANDARD* OldMsg, int Size);
	static BYTE* __stdcall HKD_ReadMessage(int instModule, int* unkParam1, int* unkParam2);

	static void ProcessDBMessage(char* Msg);

	static int __stdcall ControlExperience(int killer, int member, int experience);
	static bool __stdcall NewItemTime(int item);
	static bool __stdcall NewAffectValue(int loopIndex, CMob& mob, STRUCT_AFFECT* affects);
	static int __stdcall GetDamageControl(int type, int damage, int attacked, int attacker);
	 
	static int __stdcall GetParryRate(int rate, int attacked, int attacker);
	static int __stdcall changeDoubleCritical(STRUCT_MOB* mob, unsigned short* sProgress, unsigned short* cProgress, unsigned char* bDoubleCritical);
	static bool __stdcall ProcessDBMessage_CharacterLogin(const int conn, unsigned short* posX, unsigned short* posY);

	static void __stdcall ActionWarning(int conn);

	static void __stdcall LastReqParty(int conn, int Leader);

	static void __stdcall CheckPacket(char* pMsg);
	static void __stdcall CheckSumPacket(char* pMsg);

	static void processSecTimer();
	static void processMinTimer();

	static void BASE_GetCurrentScore(STRUCT_MOB& MOB, STRUCT_AFFECT* Affect, CMob* extra, int* PosX, int* PosY, int* ForceDamage, int* Abs, int* Accuracy, signed int a9, int MotalFace);

	static void __stdcall SetItemBonus2(STRUCT_ITEM* Dest);
	//Volatiles
	static bool __stdcall  FixRefItemCele(int32_t client, char* pMsg);
	static bool __stdcall  BarraMytril_Dano(int32_t client, char* pMsg);
	static bool __stdcall  BarraMytril_Defesa(int32_t client, char* pMsg);
	static bool __stdcall  BarraMytril_Crítico(int32_t client, char* pMsg);
	static bool __stdcall  BarraMytril_AtqMágico(int32_t client, char* pMsg); 
};
#endif // !HOOK_IMPL_H
