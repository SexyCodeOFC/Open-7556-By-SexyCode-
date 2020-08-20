#ifndef HOOK_PATCH_H
#define HOOK_PATCH_H

class HookPatch : public Singleton<HookPatch>
{
protected:
	friend class Singleton<HookPatch>;
	HookPatch() {}
	virtual ~HookPatch() {}
	HookPatch(const HookPatch&) = delete;
	HookPatch& operator=(const HookPatch&) = delete;

public:
	bool initialize();


private:

	static void NKD_RegenMob_CastleStatus();

	static void NKD_ProcessClientMessage_ReadCommand();
	static void NKD_CriticalBug();
	static void NKD_ProcessClientMessage();
	static void NKD_MobKilled_Event();
	static void NKD_ProcessClientMessage_FixBuyItem();
	static void NKD_processSend(); // OK
	static void NKD_FixJoinableItens();
	static void NKD_ProcessClientMessage_AccountLogin();
	static void NKD_SaveUser();
	static void NKD_CloseUser();
	static void NKD_AfterEnterWorld();
	static void NKD_ProcessClientMessage_OnNpcClick(); 
	//static void NKD_MainWndProc_ReadMessageUser();
	static void NKD_SetAffect_FixNewAffects();
	static void NKD_ProcessClientMessage_ChangeDoubleCritical();

	static void NKD_BASE_GetCurrentScore_NewAffects();
	static void NKD_AddMessage();
	static void NKD_ReadMessage();

	static void NKD_ProcessDBMessage(char* Msg);

	static int NKD_GetEmptyUser();
	static int NKD_GetMaxCarry(STRUCT_ITEM* Carry, int Slot);

	static void NKD_GuildProcess_FixTowerSpawn();

	static void NKD_ReadMessage_Fix();

	static void NKD_ProcessClientMessage_ManaUpdate();
	static void NKD_ProcessDBMessage_CharacterLogin();
	static void NKD_GetDamage();
	static void NKD_GetDamage2();
	static void NKD_GetSkillDamage();
	static void NKD_GetParryRate();
	static void NKD_GetParryRate2();
	static void NKD_ProcessClientMessage_DiffrentMove();
	static void NKD_ProcessClientMessage_LastReqParty();
	static void NKD_RemoveParty_LastReqParty();
	static void NKD_ReadMessage_CheckError();

	static void NKD_ProcessMinTimer_FixWarNoatun();
	static void NKD_ProcessClientMessage_ReplationRate();
	static void NKD_GuildProcess_WarTower();
	static void NKD_GenerateMob_WarTower();
	static void NKD_MobKilled_WarTower();

	static void NKD_ProcessNPC_SapphireValue();
	static void NKD_ProcessNPC_SapphireValue2();
	static void NKD_ExpControlInDead();
	static void NKD_MobKilledExpControl();
};


#endif // !HOOK_PATCH_H
