#pragma once

class CallBack
{
public:
	static char* __stdcall RecvPacket(char* pMsg, int32_t pSize);
	static void SendPacket(MSG_STANDARD* pHeader, int pSize, PacketSide pSide);

	static void __stdcall AddIndex(int32_t index, int32_t* value);
	static void __stdcall CorrectBone(int32_t index, int32_t* bone);
	static void __stdcall LoadFile(int32_t index, char* textureName, char* meshName);

	static int32_t __stdcall AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, DWORD* line1Color, DWORD* line2Color, DWORD* line3Color, DWORD* line4Color, DWORD* line5Color, DWORD* line6Color, DWORD* line7Color, DWORD* line8Color, DWORD* line9Color, DWORD* line10Color);

	static bool __stdcall SetVolatileMessageBoxText(int32_t itemID, char* text);
	static int32_t __stdcall AddVolatileMessageItem(int32_t itemID);
	static bool __stdcall AddAmountItem(int32_t itemID);
	static int32_t __stdcall AddItemSanc(STRUCT_ITEM* item, char* str);
	static bool __stdcall SetItemPriceString(STRUCT_ITEM* item, char* str);

	static bool __stdcall NewItensDay(int32_t Item);
	// Alquimista Novo NPC
	static bool Alquimista_FaceMap(int face, int mapX, int mapY);
	static int32_t __stdcall Alquimista_CompareItem(char* str, STRUCT_ITEM* item, int32_t loopIndex);

	// Compositor Novo NPC
	static bool Compositor_FaceMap(int mapX, int mapY, int face);
	static int32_t __stdcall Compositor_CompareItem(char* str, STRUCT_ITEM* item, int32_t loopIndex);

	static bool GreenTimeMap(int mapX, int mapY);
	static void __stdcall HKD_Att_Label_EXP();

	static void __stdcall HKD_Start();
	static void __stdcall HKD_Open();

	static void __stdcall HKD_Create_Scene_World(int arg1, int arg2, int arg3, int arg4);
	static void __stdcall HKD_CallBack_Handle_Click(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
	static void __stdcall HKD_CallBack_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
	static void __stdcall HKD_CallBack_Inf_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5);
	static void __stdcall HKD_CallBack_Event_Click(int handle, int gui, int clickstatus);
	static bool __stdcall HKD_CallBack_Event_Esc();
	static void __stdcall HKD_CallBack_Label(char* arg1);
	static void __stdcall HKD_Create_Scene_Login_After();
	static void __stdcall HKD_Create_Scene_Login(int arg1, int arg2, int arg3, int arg4);

	static bool __stdcall HKD_ItemTempo(int index);

	static void __stdcall HKD_OpenInventory(UINT32 Open);
	static int HKD_SendChat(char* command);
	static void __stdcall HKD_CheckJanelas(UINT32 addr1);
};