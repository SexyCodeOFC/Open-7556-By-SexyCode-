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
	static void NKD_FixItemDescription();

	static void NKD_FixIndex();
	static void NKD_CorrectBones();
	static void NKD_LoadFiles();


	static void NKD_AddVolatileMessageBox();
	static void NKD_AddVolatileMessageItem();


	static void NKD_AddAmountItem();

	static void NKD_AddItemSanc();

	static void NKD_ItemPriceString();

	static void NKD_ReadMessage();

	static void NKD_AddMessage();

	static void NKD_1();
	static void NKD_2();

	static void NKD_montaria();
	static void NKD_montaria2();

	static void NKD_noSancID();
	static void NKD_noSancFace();

	static void NKD_OnlySelas();
	static void NKD_OnlySelas2();

	static void NKD_LevelMont();
	static void NKD_SendChat();

	static void NKD_GreenTimerAdditionalMaps();

	static void NKD_FixMageMacro();

	static void NKD_AlquimistaMessage_1();
	static void NKD_AlquimistaMessage_2();
	static void NKD_AlquimistaMessage_3();

	static void NKD_AlquimistaItens_1();
	static void NKD_AlquimistaItens_2();
	static void NKD_AlquimistaOpen();

	static void NKD_CompositorItens_1();
	static void NKD_CompositorItens_2();
	static void NKD_CompositorItens_3();
	static void NKD_CompositorOpen();

	static void NKD_NewItensDays_1();
	static void NKD_NewItensDays_2();

	static void NKD_WithOutNumeric();

	/* Hook Teste GUI */
	static void NKD_Create_Scene_World();
	static void NKD_Create_Scene_World_MobTarget();
	static void NKD_Create_Scene_World_Fix_Skill_Descricao();
	static void NKD_Create_Scene_World_Fix_Gui_Adjust();
	static void NKD_Create_Scene_World_Fix_Gui_Adjust2();
	static void NKD_Create_Scene_World_Fix_Gui_Message_Adjust();
	static void NKD_Create_Scene_Login_Fix_Gui_LoginScreen_Opacity();

	static void NKD_Att_Label_EXP();

	static void NKD_CallBack_Handle_Click();
	static void NKD_CallBack_Mouse();
	static void NKD_CallBack_Inf_Mouse();
	static void NKD_CallBack_Event_Click();
	static void NKD_CallBack_Label();
	static void NKD_CallBack_Event_Esc();

	static void NKD_Create_Scene_Login();
	static void NKD_Create_Scene_Login_After();
	static void NKD_Create_Scene_Login_Panel();

	static void NKD_GetHTTP();
	static void NKD_Start();
	static void NKD_Open();

	static void NKD_ModoFoto();

	static void NKD_NewCythera();
	static void NKD_NewCythera2();

	static void NKD_NewFada();
	static void NKD_NewFada1();
	static void NKD_NewFada2();

	static void NKD_Cam();

	static void NKD_OpenInventory();
	static void NKD_CheckJanelas();

	static void NKD_FixMobCount();
};

#endif // !HOOK_PATCH_H
