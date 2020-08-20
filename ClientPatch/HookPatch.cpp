#include "stdafx.h"
#include <hook.h>
#include "HookPatch.h"
#include "Functions.h"
#include "CallBack.h"
#include "ConstantPatch.h"
#include "Anti_RE.h"

bool HookPatch::initialize()
{
	try
	{
		auto& hooks = HookMgr::instance();


		if (!Fixed::instance().initialize())
			return false;


		hooks.setHook(eHookType::JMP, 0x42082B, hooks.getAddress(&HookPatch::NKD_FixItemDescription), 4);

		hooks.setValue<unsigned char>(0x4B8BE4, 0xEB);

		hooks.setValue<int>(0x46ECE7 + 6, 0);
		hooks.setValue<int>(0x547CA6 + 6, 0);
		//hooks.setValue<int>(0x547CB0 + 6, 0);

		/* CheckSum ItemList and SkillData*/
		hooks.setValue<uint8_t>(0x54833A, 0xEB);
		hooks.setValue<uint8_t>(0x539A34, 0xEB);
		hooks.setValue<uint8_t>(0x539B1C, 0xEB);

		//protecao inject
		// Protect::CheckNewDll();                   

		/* Trajes */
		hooks.setHook(eHookType::JMP, 0x4DF208, hooks.getAddress(&NKD_FixIndex));
		hooks.setHook(eHookType::JMP, 0x4E045D, hooks.getAddress(&NKD_CorrectBones), 1);
		hooks.setHook(eHookType::JMP, 0x4CCBDC, hooks.getAddress(&NKD_LoadFiles), 4);


		/* Item MSGBOX */
		hooks.setHook(eHookType::JMP, 0x425A96, hooks.getAddress(&NKD_AddVolatileMessageItem), 2);
		hooks.setHook(eHookType::JMP, 0x4236FF, hooks.getAddress(&NKD_AddVolatileMessageBox), 5);

		/* Separar Item no Shift + Click*/
		hooks.setHook(eHookType::JMP, 0x423F69, hooks.getAddress(&NKD_AddAmountItem), 4);


		/* Mostrar a refinação do item */
		hooks.setHook(eHookType::JMP, 0x40CD2D, hooks.getAddress(&HookPatch::NKD_AddItemSanc), 4);
		hooks.setHook(eHookType::JMP, 0x40CD75, 0x40CD8F, 4);

		hooks.setHook(eHookType::JMP, 0x4211A6, hooks.getAddress(&NKD_ItemPriceString), 1);


		hooks.setHook(eHookType::JGE, 0x428BA9, hooks.getAddress(&NKD_ReadMessage));

		//Alteração no serverlist.bin
		//strcpy((char*)0x541736, ".Env/tile25253.wys"); // 00541736 | . 68 64905F00    PUSH WYD3.005F9064;  ASCII "./serverlist.bin"

		hooks.setHook(eHookType::JMP, 0x428FED, hooks.getAddress(&NKD_AddMessage));

		hooks.setHook(eHookType::JMP, 0x0048B718, hooks.getAddress(&NKD_1));
		hooks.setHook(eHookType::JMP, 0x004B93A9, hooks.getAddress(&NKD_2));


		/* Pula checksum dos arquivos trn (mapas)*/
		hooks.setHook(eHookType::JMP, 0x51DCE1, 0x51DD74, 1);
		hooks.setHook(eHookType::JMP, 0x52F02D, 0x52F0E3, 1);

		hooks.setHook(eHookType::JMP, 0x0483C3A, hooks.getAddress(&NKD_GreenTimerAdditionalMaps));

		hooks.setHook(eHookType::JMP, 0x413A16, hooks.getAddress(&NKD_AlquimistaMessage_1));
		hooks.setHook(eHookType::JMP, 0x413980, hooks.getAddress(&NKD_AlquimistaMessage_2));
		hooks.setHook(eHookType::JMP, 0x413AAD, hooks.getAddress(&NKD_AlquimistaMessage_3));

		hooks.setHook(eHookType::JMP, 0x413873, hooks.getAddress(&NKD_AlquimistaItens_1));
		hooks.setHook(eHookType::JMP, 0x413970, hooks.getAddress(&NKD_AlquimistaItens_2));

		hooks.setHook(eHookType::JMP, 0x465CB8, hooks.getAddress(&NKD_AlquimistaOpen));

		hooks.setHook(eHookType::JMP, 0x465E1E, hooks.getAddress(&NKD_CompositorOpen));

		hooks.setHook(eHookType::JMP, 0x4108C8, hooks.getAddress(&NKD_CompositorItens_1));
		hooks.setHook(eHookType::JMP, 0x410B21, hooks.getAddress(&NKD_CompositorItens_2));
		hooks.setHook(eHookType::JMP, 0x410B9D, hooks.getAddress(&NKD_CompositorItens_3));

		hooks.setHook(eHookType::JMP, 0x41EB7C, hooks.getAddress(&NKD_NewItensDays_1));
		hooks.setHook(eHookType::JMP, 0x41EB93, hooks.getAddress(&NKD_NewItensDays_2));

		hooks.setHook(eHookType::JE, 0x049B39A, hooks.getAddress(&NKD_FixMageMacro));
		hooks.setHook(eHookType::JE, 0x049B3AA, hooks.getAddress(&NKD_FixMageMacro));

		//hooks.setHook(eHookType::JMP, 0x4B80C4, hooks.getAddress(&NKD_GetHTTP));

		hooks.setHook(eHookType::JMP, 0x4BDA5D, hooks.getAddress(&NKD_Start), 1);
		hooks.setHook(eHookType::JMP, 0x54B5C5, hooks.getAddress(&NKD_Open), 13);

		//hooks.setHook(eHookType::JMP, 0x4AEC5A, hooks.getAddress(&HookPatch::NKD_WithOutNumeric));

		hooks.setHook(eHookType::JMP, 0x449DD0, hooks.getAddress(&NKD_Create_Scene_World));
		hooks.setHook(eHookType::JMP, 0x4DC869, hooks.getAddress(&NKD_Create_Scene_World_MobTarget), 2);
		hooks.setHook(eHookType::JMP, 0x47DF41, hooks.getAddress(&NKD_Create_Scene_World_Fix_Skill_Descricao), 4);
		hooks.setHook(eHookType::JMP, 0x4429D9, hooks.getAddress(&NKD_Create_Scene_World_Fix_Gui_Adjust), 1);
		hooks.setHook(eHookType::JMP, 0x442A35, hooks.getAddress(&NKD_Create_Scene_World_Fix_Gui_Message_Adjust), 1);
		hooks.setHook(eHookType::JMP, 0x448AA9, hooks.getAddress(&NKD_Create_Scene_World_Fix_Gui_Adjust2), 1);
		hooks.setHook(eHookType::JMP, 0x4B6E19, hooks.getAddress(&NKD_Create_Scene_Login_Fix_Gui_LoginScreen_Opacity), 4);

		//HUD 7.54

		 //hooks.setValue<int>(0x47DB08, 0xc1700000); //HUD 7.54
		// hooks.setValue<int>(0x47db80, 0xc1900000); //HUD 7.54

		///*Jumpa o set do Main Panel Skill set X*/
		//hooks.setHook(eHookType::JMP, 0x442960, 0x442971, 1); //HUD 7.54

		///*Jumpa o set X,Y do Exp Message Panel*/
		//hooks.setHook(eHookType::JMP, 0x442ACC, 0x442B02, 1); //HUD 7.54 

		/*Jumpa o set X,Y do Grupo Panel*/
		 hooks.setHook(eHookType::JMP, 0x448A99, 0x448AA9);  //HUD 7.54

		///*Jumpa o set X,Y da Carta*/
		//hooks.setHook(eHookType::JMP, 0x44A2FD, 0x44A34E, 1);

		/*Jumpa o set X,Y do MessageChat*/
		/*hooks.setHook(eHookType::JMP, 0x4429D9, 0x442A06, 1);*/ //bugado nunca ativar


		hooks.setHook(eHookType::JMP, 0x48E9A9, hooks.getAddress(&NKD_Att_Label_EXP), 1);

		/*Liberação de Load do UITextureSetList.bin*/
		hooks.setValue<int>(0x4C42A2, 1000);
		hooks.setValue<int>(0x4C453D, 1000);

		/*Liberação do Ressu em Grupo*/
		hooks.setValue<char>(0x477A8B + 2, 0x1F);

		hooks.setHook(eHookType::JMP, 0x4B4F88, hooks.getAddress(&NKD_Create_Scene_Login));
		hooks.setHook(eHookType::JMP, 0x4BF1F5, hooks.getAddress(&NKD_Create_Scene_Login_After), 2); 
		 

		hooks.setHook(eHookType::JMP, 0x40C65B, hooks.getAddress(&NKD_CallBack_Handle_Click), 2);
		hooks.setHook(eHookType::JMP, 0x403782, hooks.getAddress(&NKD_CallBack_Mouse), 1);
		hooks.setHook(eHookType::JMP, 0x402334, hooks.getAddress(&NKD_CallBack_Label), 4);
		hooks.setHook(eHookType::JMP, 0x4A6569, hooks.getAddress(&NKD_CallBack_Inf_Mouse), 2);
		hooks.setHook(eHookType::JMP, 0x40387D, hooks.getAddress(&NKD_CallBack_Event_Click), 2);
		hooks.setHook(eHookType::JMP, 0x454A4E, hooks.getAddress(&NKD_CallBack_Event_Esc), 3);

		 
		hooks.setHook(eHookType::JMP, 0x53CDF9, hooks.getAddress(&NKD_NewCythera));
		hooks.setHook(eHookType::JMP, 0x50EE56, hooks.getAddress(&NKD_NewCythera2));

		hooks.setHook(eHookType::JMP, 0x41E5C3, hooks.getAddress(&NKD_NewFada));
		hooks.setHook(eHookType::JMP, 0x4F79CA, hooks.getAddress(&NKD_NewFada1));
		hooks.setHook(eHookType::JMP, 0x4F7F68, hooks.getAddress(&NKD_NewFada2));

		/*Removedo Checksun do Sendpacket (Causa a Perda de Pacote)*/
		/*
		0x464B65 - > Ataque MG do Player com Mouse
		0x45FB44 - > Ataque MG do Player com Macro*/
		hooks.setValue<short>(0x54B0F3, 0x00EB);

		/*Liberação de Camera*/
		hooks.setHook(eHookType::JMP, 0x4BAC5F, hooks.getAddress(&HookPatch::NKD_Cam), 1);

		hooks.setHook(eHookType::JMP, 0x48FEFB, hooks.getAddress(&HookPatch::NKD_FixMobCount), 1);

		/*Call Back da Abertura do inventario*/
		hooks.setHook(eHookType::JMP, 0x0044F2E9, hooks.getAddress(&HookPatch::NKD_OpenInventory), 1);

		/*Informação de Janela (Main thread)*/
		hooks.setHook(eHookType::JMP, 0x40C57A, hooks.getAddress(&HookPatch::NKD_CheckJanelas), 4);

		/* Comando no Game */
		hooks.setHook(eHookType::JMP, 0x46ED5B, hooks.getAddress(&HookPatch::NKD_SendChat), 2);

		//modofoto
		hooks.setHook(eHookType::JMP, 0x46EC8A, hooks.getAddress(&HookPatch::NKD_ModoFoto), 0);


		return true;
	}
	catch (...)
	{
		return false;
	}
}

__declspec(naked) void HookPatch::NKD_CheckJanelas()
{
	static int jmp_saida1 = 0x40C5FE;
	static int jmp_saida2 = 0x40C5AF;
	_asm
	{
		PUSH DWORD PTR SS : [EBP - 4]
		CALL  CallBack::HKD_CheckJanelas

		MOV ECX, DWORD PTR SS : [EBP - 4]
		CMP DWORD PTR DS : [ECX + 0x10] , 0
		JE pulo

		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR SS : [EBP - 0x14]
		FADD DWORD PTR DS : [EDX + 0x4C]
		FSTP DWORD PTR SS : [EBP - 0x14]
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR SS : [EBP - 0x10]
		FADD DWORD PTR DS : [EAX + 0x50]
		FSTP DWORD PTR SS : [EBP - 0x10]
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		ADD ECX, 1
		MOV DWORD PTR SS : [EBP - 0x8] , ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		MOV EAX, DWORD PTR DS : [EDX + 0x10]
		MOV DWORD PTR SS : [EBP - 0x4] , EAX

		JMP jmp_saida1

		pulo :
		JMP jmp_saida2

	}
}

__declspec(naked) void HookPatch::NKD_Cam()
{
	if (!Global::CameraLivre)
	{
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0xC]
			MOV ECX, DWORD PTR SS : [EBP - 0xC]
			MOV DWORD PTR DS : [ECX + 0xC0] , 0x41a00000 // 0x14
			FLD DWORD PTR DS : [EAX + 0x34]
			FCOMP DWORD PTR DS : [ECX + 0xC0]
			FSTSW AX
			TEST AH, 0x41
			JNZ label_saida

			PUSH 0x4BAC75
			RETN

			label_saida :
			PUSH 0x4BAC90
				RETN
		}
	}
	else
	{
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0xC]
			MOV ECX, DWORD PTR SS : [EBP - 0xC]
			MOV DWORD PTR DS : [ECX + 0xC0] , 0x41800000 // 0x20
			FLD DWORD PTR DS : [EAX + 0x34]
			FCOMP DWORD PTR DS : [ECX + 0xC0]
			FSTSW AX
			TEST AH, 0x41
			JNZ label_saida_2

			PUSH 0x4BAC75
			RETN

			label_saida_2 :
			PUSH 0x4BAC90
				RETN
		}
	}

}

__declspec(naked) void HookPatch::NKD_OpenInventory()
{
	_asm
	{
		PUSH ECX
		CALL CallBack::HKD_OpenInventory

		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x1C]
		MOV EAX, DWORD PTR DS : [EDX]
		MOV ECX, DWORD PTR SS : [EBP - 0x1C]
		CALL DWORD PTR DS : [EAX + 0x60]



		PUSH 0x44F2F5
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_FixMobCount()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x04]
		XOR EDX, EDX
		MOV DX, WORD PTR DS : [ECX + 0x0E]

		MOV DWORD PTR SS : [EBP - 0x8C] , EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		XOR ECX, ECX

		MOV CX, WORD PTR DS : [EAX + 0xC]
		MOV DWORD PTR SS : [EBP - 0x88] , ECX
		MOV EAX, 0x48FF22
		JMP EAX
	}
}

__declspec(naked) void HookPatch::NKD_SendChat()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x98]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x98]
		CALL DWORD PTR DS : [EDX + 0x88]

		PUSH EAX
		CALL CallBack::HKD_SendChat
		ADD ESP, 0x08

		TEST EAX, EAX
		JNZ chk_other_cmd

		MOV EAX, 0x01
		MOV ECX, 0x47A547
		JMP ECX

		chk_other_cmd :

		MOV ECX, 0x46EDD6
			JMP ECX
	}
}

__declspec(naked) void HookPatch::NKD_NewFada2()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x948]
		MOVSX ECX, WORD PTR DS : [EAX + 0x78A]
		PUSH ECX
		CALL CallBack::HKD_ItemTempo
		TEST AL, AL
		JNE Existe

		MOV EAX, DWORD PTR SS : [EBP - 0x948]
		MOVSX ECX, WORD PTR DS : [EAX + 0x78A]
		CMP ECX, 0x0F3C
		JL JL1
		PUSH 0x4F7F7D
		RETN

		Existe :
		PUSH 0x4F800C
			RETN

			JL1 :
		PUSH 0x4F7F91
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_NewFada1()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x948]
		MOVSX ECX, WORD PTR DS : [EAX + 0x78A]
		PUSH ECX
		CALL CallBack::HKD_ItemTempo
		TEST AL, AL
		JNE Existe

		MOV EAX, DWORD PTR SS : [EBP - 0x948]
		MOVSX ECX, WORD PTR DS : [EAX + 0x78A]
		CMP ECX, 0x0F3C
		JL JL1
		PUSH 0x4F79DF
		RETN

		Existe :
		PUSH 0x4F7A35
			RETN

			JL1 :
		PUSH 0x4F79F3
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_NewFada()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		MOVSX EAX, WORD PTR DS : [EDX]
		PUSH EAX
		CALL CallBack::HKD_ItemTempo
		TEST AL, AL
		JNE Existe

		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		MOVSX EAX, WORD PTR DS : [EDX]
		CMP EAX, 0x0F3C
		JL JL1
		PUSH 0x41E5DA
		RETN

		Existe :
		PUSH 0x0041E61B
			RETN

			JL1 :
		PUSH 0x41E840
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_NewCythera2()
{
	__asm
	{

		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [EDX + 0x2]
		AND EAX, 00000FFFh
		CMP EAX, 0x0DB3
		JE cont
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [EDX + 0x2]
		AND EAX, 00000FFFh
		CMP EAX, 0x1523
		JE cont
		PUSH 0x50EE6B
		RETN

		cont :
		PUSH 0x50EEB6
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_NewCythera()
{
	__asm
	{
		CMP EDX, 0x0DAE
		JE cont
		MOV ECX, DWORD PTR SS : [EBP + 0x8]
		MOVSX EDX, WORD PTR DS : [ECX]
		CMP EDX, 0x1523
		JE cont
		PUSH 0x53CE01
		RETN
		cont :
		PUSH 0x0053CE29
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_ModoFoto() {
	static int msg;
	__asm {
		mov eax, [ebp - 0x98]
		mov edx, [eax]
		mov ecx, [ebp - 0x98]
		call dword ptr[edx + 0x88]

		mov msg, eax
	}
	if (strcmp((char*)msg, "/modofoto") == 0)
	{
		__asm {
			mov eax, [ebp - 0x2098]
			mov ecx, [eax + 0x27E24]
			mov dword ptr[ecx + 0x28], 0
			mov edx, ds : 0x13FA9D4
			xor eax, eax
			cmp dword ptr[edx + 0x24CCC], 0
			setz al
			mov ecx, ds : 0x13FA9D4
			mov[ecx + 0x24CCC], eax
			mov eax, 1
			push 0x47A547
			retn
		}
	}
	else {
		__asm {
			push 0x5EC42C
			push 0x46EC8F
			retn
		}
	}
}

__declspec(naked) void HookPatch::NKD_FixMageMacro()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x118]
		CMP DWORD PTR DS : [ECX + 0x27D28] , 0x0
		JNZ lbl_JMP
		PUSH 0x049AFC9
		RETN

		lbl_JMP :
		PUSH 0x0049B1B5
			RETN
	}
}

#pragma region Saltar_Numeric
__declspec(naked) void HookPatch::NKD_WithOutNumeric() {
	__asm {

	}
}
#pragma endregion

#pragma region Alquimista
static char errorString[256] = { "Traga-me os itens para a composição." };

// Item Com Adicional 41E840
__declspec(naked) void HookPatch::NKD_NewItensDays_1() {
	__asm
	{
		CMP EAX, 0x0F8C
		JL LoopOriginal
		PUSH 0x41EB87
		RETN

		LoopOriginal :
		PUSH EAX
			CALL CallBack::NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41EBCC
			RETN

			VoltaOriginal :
		PUSH 0x41EE19
			RETN
	}

}

__declspec(naked) void HookPatch::NKD_NewItensDays_2() {
	__asm
	{
		CMP EAX, 0x0F9F
		JG LoopOriginal
		PUSH 0x41EB9E
		RETN

		LoopOriginal :
		PUSH EAX
			CALL CallBack::NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41EBCC
			RETN

			VoltaOriginal :
		PUSH 0x41EE19
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaMessage_1() {
	__asm
	{
		CMP DWORD PTR DS : [0x606DB4] , 0x0A
		JNE AddressOriginal
		PUSH 0x7D0
		LEA EAX, errorString
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [ECX + 0x84]
		MOV EAX, 0x40409D
		CALL EAX
		PUSH 1
		PUSH 1
		MOV EDX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [EDX + 0x84]
		MOV EAX, DWORD PTR SS : [EBP - 0x294]
		MOV EDX, DWORD PTR DS : [EAX + 0x84]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL NEAR DWORD PTR DS : [EAX + 0x88]
		MOV EAX, 1
		PUSH 0x4179FD
		RETN

		AddressOriginal :
		PUSH 0x7D0
			PUSH 0x413A1B
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaMessage_2() {
	__asm
	{
		CMP DWORD PTR DS : [0x606DB4] , 0x0A
		JNE AddressOriginal
		PUSH 0x7D0
		LEA EAX, errorString
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [ECX + 0x84]
		MOV EAX, 0x40409D
		CALL EAX
		PUSH 1
		PUSH 1
		MOV EDX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [EDX + 0x84]
		MOV EAX, DWORD PTR SS : [EBP - 0x294]
		MOV EDX, DWORD PTR DS : [EAX + 0x84]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL NEAR DWORD PTR DS : [EAX + 0x88]
		MOV EAX, 1
		PUSH 0x4179FD
		RETN

		AddressOriginal :
		PUSH 0x7D0
			PUSH 0x413985
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaMessage_3() {
	__asm
	{
		CMP DWORD PTR DS : [0x606DB4] , 0x0A
		JNE AddressOriginal
		PUSH 0x7D0
		LEA EAX, errorString
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [ECX + 0x84]
		MOV EAX, 0x40409D
		CALL EAX
		PUSH 1
		PUSH 1
		MOV EDX, DWORD PTR SS : [EBP - 0x294]
		MOV ECX, DWORD PTR DS : [EDX + 0x84]
		MOV EAX, DWORD PTR SS : [EBP - 0x294]
		MOV EDX, DWORD PTR DS : [EAX + 0x84]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL NEAR DWORD PTR DS : [EAX + 0x88]
		MOV EAX, 1
		PUSH 0x4179FD
		RETN

		AddressOriginal :
		PUSH 0x7D0
			PUSH 0x413AB2
			RETN

	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaOpen() {
	__asm
	{

		CMP EDX, 0x43 // Face do Mob
		JNE NewValidation
		MOV EAX, DWORD PTR SS : [EBP - 0x9C]
		MOV ECX, DWORD PTR DS : [EAX + 0x40]
		CMP DWORD PTR DS : [ECX + 0x20A20] , 0x0D // Posição do Mapa
		JNE NewValidation
		MOV EDX, DWORD PTR SS : [EBP - 0x9C]
		MOV EAX, DWORD PTR DS : [EDX + 0x40]
		CMP DWORD PTR DS : [EAX + 0x20A24] , 0x0D // Posição do Mapa
		JNE NewValidation
		PUSH 0x465CE1
		RETN


		NewValidation :
		PUSH EDX // Face do Mob
			MOV EAX, DWORD PTR SS : [EBP - 0x9C]
			MOV ECX, DWORD PTR DS : [EAX + 0x40]
			MOV EDX, DWORD PTR DS : [ECX + 0x20A20]
			PUSH EDX
			MOV EDX, DWORD PTR SS : [EBP - 0x9C]
			MOV EAX, DWORD PTR DS : [EDX + 0x40]
			MOV ECX, DWORD PTR DS : [EAX + 0x20A24]
			PUSH ECX
			CALL CallBack::Alquimista_FaceMap
			TEST AL, AL
			JE LoopOriginal
			MOV DWORD PTR DS : [0x606DB4] , 0x0A
			MOV ECX, DWORD PTR SS : [EBP - 0x9C]
			CMP DWORD PTR DS : [ECX + 0x27C10] , 0x0
			JE Continue
			PUSH 0x465CFA
			RETN

			Continue :
		PUSH 0x465D1B
			RETN

			LoopOriginal :
		PUSH 0x465D25
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaItens_1() {

	__asm
	{
		CMP DWORD PTR DS : [0x606DB4] , 0x1
		JNE NewComposer
		PUSH 0x00413880
		RETN

		NewComposer :
		CMP DWORD PTR DS : [0x606DB4] , 0x0A
			JNE JEN0

			MOV DWORD PTR SS : [EBP - 0x290] , 0x0
			JMP JMP1
			MOV EAX, DWORD PTR SS : [EBP - 0x290]
			ADD EAX, 0x1
			MOV DWORD PTR SS : [EBP - 0x290] , EAX
			JMP JMP1

			JMP1 :
		CMP DWORD PTR SS : [EBP - 0x290] , 0x7
			JGE JEN1

			MOV ECX, DWORD PTR SS : [EBP - 0x290]
			CMP DWORD PTR SS : [ECX * 0x4 + EBP - 0x288] , 0x0
			JE JEN2

			PUSH 0x0
			PUSH 0x0
			MOV EDX, DWORD PTR SS : [EBP - 0x290]
			MOV ECX, DWORD PTR SS : [EDX * 0x4 + EBP - 0x288]
			MOV EAX, DWORD PTR SS : [EBP - 0x290]
			MOV EDX, DWORD PTR SS : [EAX * 0x4 + EBP - 0x288]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x0B8]
			TEST EAX, EAX
			JNE JEN2

			MOV ECX, DWORD PTR SS : [EBP - 0x268]
			MOV EDX, DWORD PTR DS : [ECX + 0x670]
			MOVSX EAX, WORD PTR DS : [EDX]
			TEST EAX, EAX
			JE lblContinueNormalLoop

			PUSH DWORD PTR SS : [EBP - 0x290]
			MOV ECX, DWORD PTR SS : [EBP - 0x268]
			MOV EDX, DWORD PTR DS : [ECX + 0x670]
			PUSH EDX
			LEA EAX, errorString
			PUSH EAX
			CALL CallBack::Alquimista_CompareItem // Compara se o item é o nosso item
			CMP EAX, 0 // Retorna 0  se não nos interessa o item
			JE lblPrintErrorAndExit
			CMP EAX, 1 // Retorna 1 se o item é o nosso
			JE lblContinue
			CMP EAX, 2 // Retorna 2 se o item é o nosso, só que está em quantidade errada
			JE lblPrintErrorAndExit
			PUSH 0x413977 // Retorna ao loop normal
			RETN

			lblPrintErrorAndExit :
		PUSH 0x7D0
			LEA EAX, errorString
			PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 0x294]
			MOV ECX, DWORD PTR DS : [ECX + 0x84]
			MOV EAX, 0x40409D
			CALL EAX
			PUSH 1
			PUSH 1
			MOV EDX, DWORD PTR SS : [EBP - 0x294]
			MOV ECX, DWORD PTR DS : [EDX + 0x84]
			MOV EAX, DWORD PTR SS : [EBP - 0x294]
			MOV EDX, DWORD PTR DS : [EAX + 0x84]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL NEAR DWORD PTR DS : [EAX + 0x88]
			MOV EAX, 1
			PUSH 0x4179FD
			RETN

			lblContinue :
		PUSH 0x413AF6
			RETN

			lblContinueNormalLoop :
		PUSH 0x4139C9
			RETN

			JEN2 :
		PUSH 0x413C27
			RETN

			JEN1 :
		PUSH 0x413C2C
			RETN

			JEN0 :
		PUSH 0x413C31
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AlquimistaItens_2() {
	__asm
	{
		CMP	EAX, 0x279
		JE lblContinueNormalLoop
		CMP DWORD PTR DS : [0x606DB4] , 0x0A
		JNE lblContinueNormalLoop
		PUSH DWORD PTR SS : [EBP - 0x290]
		MOV ECX, DWORD PTR SS : [EBP - 0x268]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		PUSH EDX
		LEA EAX, errorString
		PUSH EAX
		CALL CallBack::Alquimista_CompareItem // Compara se o item é o nosso item
		CMP EAX, 0 // Retorna 0  se não nos interessa o item
		JE lblContinueNormalLoop
		CMP EAX, 1 // Retorna 1 se o item é o nosso
		JE lblContinue
		CMP EAX, 2 // Retorna 2 se o item é o nosso, só que está em quantidade errada
		JE lblPrintErrorAndExit
		PUSH 0x413977 // Retorna ao loop normal
		RETN

		lblPrintErrorAndExit :
		PUSH 0x7D0
			LEA EAX, errorString
			PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 0x294]
			MOV ECX, DWORD PTR DS : [ECX + 0x84]
			MOV EAX, 0x40409D
			CALL EAX
			PUSH 1
			PUSH 1
			MOV     EDX, DWORD PTR SS : [EBP - 0x294]
			MOV     ECX, DWORD PTR DS : [EDX + 0x84]
			MOV     EAX, DWORD PTR SS : [EBP - 0x294]
			MOV     EDX, DWORD PTR DS : [EAX + 0x84]
			MOV     EAX, DWORD PTR DS : [EDX]
			CALL    NEAR DWORD PTR DS : [EAX + 0x88]
			MOV     EAX, 1
			PUSH 0x4179FD
			RETN

			lblContinue :
		PUSH 0x413AF6
			RETN

			lblContinueNormalLoop :
		PUSH 0x4139C9
			RETN

	}
}

#pragma endregion

#pragma region Compositor
__declspec(naked) void HookPatch::NKD_CompositorOpen() {
	static int face, mapX, mapY;
	__asm
	{

		CMP EAX, 0x36
		JNE NewValidation
		MOV ECX, DWORD PTR SS : [EBP - 0x9C]
		MOV EDX, DWORD PTR DS : [ECX + 0x40]
		CMP DWORD PTR DS : [EDX + 0x20A20] , 0x13
		JNE NewValidation
		MOV EAX, DWORD PTR SS : [EBP - 0x9C]
		MOV ECX, DWORD PTR DS : [EAX + 0x40]
		CMP DWORD PTR DS : [ECX + 0x20A24] , 0x0D
		JNE NewValidation
		PUSH 0x465E47
		RETN

		NewValidation :
		PUSH EAX // Face do Mob
			MOV EDX, DWORD PTR SS : [EBP - 0x9C]
			MOV EAX, DWORD PTR DS : [EDX + 0x40]
			MOV ECX, DWORD PTR DS : [EAX + 0x20A24]
			PUSH ECX
			MOV EAX, DWORD PTR SS : [EBP - 0x9C]
			MOV ECX, DWORD PTR DS : [EAX + 0x40]
			MOV EDX, DWORD PTR DS : [ECX + 0x20A20]
			PUSH EDX
			CALL CallBack::Compositor_FaceMap
			TEST AL, AL
			JE LoopOriginal
			MOV DWORD PTR DS : [606DB4h] , 0x0B
			MOV ECX, DWORD PTR SS : [EBP - 9Ch]
			CMP DWORD PTR DS : [ECX + 27B6Ch] , 0
			JE Continue
			PUSH 0x465E60
			RETN

			Continue :
		PUSH 0x465E81
			RETN

			LoopOriginal :
		PUSH 0x465E8B
			RETN
	}


}

__declspec(naked) void HookPatch::NKD_CompositorItens_1() {
	__asm
	{
		CMP DWORD PTR DS : [606DB4h] , 0
		JNE NewComposer
		PUSH 0x4108D5
		RETN

		Original_Loop :
		PUSH 0x410D65
			RETN

			JGE_1 :
		PUSH 0x410D60
			RETN

			JNE_1 :
		PUSH 0x410D5B
			RETN

			JNE_2 :
		PUSH 0x410B18
			RETN

			NewComposer :
		CMP DWORD PTR DS : [606DB4h] , 0x0B
			JNE Original_Loop
			MOV DWORD PTR SS : [EBP - 0BCh] , 0
			JMP JMP_1
			MOV EDX, DWORD PTR SS : [EBP - 0BCh]
			ADD EDX, 1
			MOV DWORD PTR SS : [EBP - 0BCh] , EDX
			CMP DWORD PTR SS : [EBP - 0BCh] , 0x6
			JGE JGE_1
			JMP_1 :
		PUSH 0
			PUSH 0
			MOV EAX, DWORD PTR SS : [EBP - 0BCh]
			MOV ECX, DWORD PTR SS : [EAX * 4h + EBP - 0B4h]
			MOV EDX, DWORD PTR SS : [EBP - 0BCh]
			MOV EAX, DWORD PTR SS : [EDX * 4h + EBP - 0B4h]
			MOV EDX, DWORD PTR DS : [EAX]
			CALL DWORD PTR DS : [EDX + 0B8h]
			TEST EAX, EAX
			JNE JNE_1
			CMP DWORD PTR SS : [EBP - 0BCh] , 0
			JNE JNE_2

			PUSH DWORD PTR SS : [EBP - 0BCh]
			MOV EAX, DWORD PTR SS : [EBP - 94h]
			MOV ECX, DWORD PTR DS : [EAX + 670h]
			PUSH ECX
			LEA EAX, errorString
			PUSH EAX
			CALL CallBack::Compositor_CompareItem // Compara se o item é o nosso item
			CMP EAX, 1 // Retorna 1 se o item é o nosso
			JE lblContinue
			JMP lblPrintErrorAndExit

			lblPrintErrorAndExit :
		PUSH 0x7D0
			LEA EDX, errorString
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [EAX + 84h]
			MOV EDX, 0x40409D
			CALL EDX
			PUSH 1
			PUSH 1
			MOV ECX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [ECX + 84h]
			MOV EDX, DWORD PTR SS : [EBP - 0C0h]
			MOV EAX, DWORD PTR DS : [EDX + 84h]
			MOV EDX, DWORD PTR DS : [EAX]
			CALL NEAR  DWORD PTR DS : [EDX + 88h]
			MOV EAX, 1
			PUSH 0x4179FD
			RETN


			lblContinue :
		MOV EDX, DWORD PTR SS : [EBP - 94h]
			MOV EAX, DWORD PTR DS : [EDX + 670h]
			MOVSX ECX, WORD PTR DS : [EAX]
			IMUL ECX, ECX, 8Ch
			MOVSX EDX, WORD PTR DS : [ECX + 0D871D6h]
			TEST EDX, EDX
			PUSH 0x410B13
			RETN
	}

}

__declspec(naked) void HookPatch::NKD_CompositorItens_2() {
	__asm
	{
		CMP DWORD PTR DS : [606DB4h] , 0x0B
		JE VerificaItens
		MOV EAX, DWORD PTR SS : [EBP - 94h]
		PUSH 0x410B27
		RETN

		VerificaItens :
		PUSH DWORD PTR SS : [EBP - 0BCh]
			MOV EAX, DWORD PTR SS : [EBP - 94h]
			MOV ECX, DWORD PTR DS : [EAX + 670h]
			PUSH ECX
			LEA EAX, errorString
			PUSH EAX
			CALL CallBack::Compositor_CompareItem // Compara se o item é o nosso item
			CMP EAX, 1 // Retorna 1 se o item é o nosso
			JE lblContinue
			JMP lblPrintErrorAndExit

			lblPrintErrorAndExit :
		PUSH 0x7D0
			LEA EDX, errorString
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [EAX + 84h]
			MOV EDX, 0x40409D
			CALL EDX
			PUSH 1
			PUSH 1
			MOV ECX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [ECX + 84h]
			MOV EDX, DWORD PTR SS : [EBP - 0C0h]
			MOV EAX, DWORD PTR DS : [EDX + 84h]
			MOV EDX, DWORD PTR DS : [EAX]
			CALL NEAR  DWORD PTR DS : [EDX + 88h]
			MOV EAX, 1
			PUSH 0x4179FD
			RETN


			lblContinue :
		PUSH 0x00410C2A
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_CompositorItens_3() {
	__asm
	{
		CMP DWORD PTR DS : [606DB4h] , 0x0B
		JE VerificaItens
		MOV EAX, DWORD PTR SS : [EBP - 94h]
		PUSH 0x410BA3
		RETN

		VerificaItens :
		PUSH DWORD PTR SS : [EBP - 0BCh]
			MOV EAX, DWORD PTR SS : [EBP - 94h]
			MOV ECX, DWORD PTR DS : [EAX + 670h]
			PUSH ECX
			LEA EAX, errorString
			PUSH EAX
			CALL CallBack::Compositor_CompareItem // Compara se o item é o nosso item
			CMP EAX, 1 // Retorna 1 se o item é o nosso
			JE lblContinue
			JMP lblPrintErrorAndExit


			lblPrintErrorAndExit :
		PUSH 0x7D0
			LEA EDX, errorString
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [EAX + 84h]
			MOV EDX, 0x40409D
			CALL EDX
			PUSH 1
			PUSH 1
			MOV ECX, DWORD PTR SS : [EBP - 0C0h]
			MOV ECX, DWORD PTR DS : [ECX + 84h]
			MOV EDX, DWORD PTR SS : [EBP - 0C0h]
			MOV EAX, DWORD PTR DS : [EDX + 84h]
			MOV EDX, DWORD PTR DS : [EAX]
			CALL NEAR  DWORD PTR DS : [EDX + 88h]
			MOV EAX, 1
			PUSH 0x4179FD
			RETN

			lblContinue :
		PUSH 0x410C2A
			RETN
	}


}
#pragma endregion


__declspec(naked) void HookPatch::NKD_GreenTimerAdditionalMaps() {
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x788]
		MOV EAX, DWORD PTR DS : [EDX + 0x40]
		MOV ECX, DWORD PTR[EAX + 0x20A20]
		PUSH ECX

		MOV EDX, DWORD PTR SS : [EBP - 0x788]
		MOV EAX, DWORD PTR DS : [EDX + 0x40]
		MOV ECX, DWORD PTR[EAX + 0x20A24]
		PUSH ECX

		CALL CallBack::GreenTimeMap
		TEST AL, AL
		JE LoopOriginal
		PUSH 0x483C56
		RETN

		LoopOriginal :
		PUSH 0x483D35
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_1() {
	static const INT32 szContinue = 0x0048B722;
	__asm {
		MOV DWORD PTR SS : [EBP - 0x298] , 1905
		JMP szContinue
	}

}

__declspec(naked) void HookPatch::NKD_2() {
	static const INT32 szContinue = 0x004B93B3;
	__asm {
		MOV DWORD PTR SS : [EBP - 0x9CC] , 1905
		JMP szContinue
	}
}

__declspec(naked) void HookPatch::NKD_AddMessage() {
	__asm
	{
		PUSH CLIENT
		PUSH DWORD PTR SS : [EBP + 0xC]
		PUSH DWORD PTR SS : [EBP + 8]
		CALL CallBack::SendPacket
		ADD ESP, 12

		// Return to default PE's execution flow.
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOV DWORD PTR SS : [EBP - 0x114] , EAX
		PUSH 0x428FF6
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ReadMessage()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		PUSH ECX
		CALL CallBack::RecvPacket
		MOV DWORD PTR SS : [EBP - 0x18] , EAX
		PUSH 0x428C9F
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ItemPriceString()
{
	__asm
	{
		LEA EAX, DWORD PTR SS : [EBP - 0x1110] // MSG
		PUSH EAX
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		PUSH ECX
		CALL CallBack::SetItemPriceString
		TEST AL, AL
		JE lblContinueExec
		PUSH 0x4211FB
		RETN

		lblContinueExec :
		FLD DWORD PTR SS : [EBP - 0x1120]
			PUSH 0x4211AC
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AddItemSanc()
{
	__asm
	{

		MOV EAX, DWORD PTR SS : [EBP - 0x20]
		ADD EAX, 0xAC
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP + 0xC]
		PUSH ECX
		CALL CallBack::AddItemSanc
		PUSH 0x40CD39
		RETN
	}
}
__declspec(naked) void HookPatch::NKD_AddAmountItem()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x60]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		MOVSX EDX, WORD PTR DS : [ECX]
		CMP EDX, 0xC80
		JL lblNext
		CMP EDX, 0xC94
		JG lblNext
		JMP lblContinueExec

		lblNext :
		PUSH EDX
			CALL CallBack::AddAmountItem
			TEST AL, AL
			JE lblContinueExec
			MOV BYTE PTR SS : [EBP - 0x5C] , 1
			JMP lblContinueExec

			lblContinueExec :

		PUSH 0x423F95
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AddVolatileMessageItem()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP + 0xC] , 0xFD1
		JNZ lblNext
		JMP lblSuccess
		lblNext :
		PUSH DWORD PTR SS : [EBP + 0xC]
			CALL CallBack::AddVolatileMessageItem
			TEST EAX, EAX
			JE lblContinueExec
			lblSuccess :
		MOV EAX, 1
			lblContinueExec :
			PUSH 0x425AA6
			RETN 4
	}
}

__declspec(naked) void HookPatch::NKD_AddVolatileMessageBox()
{
	static char msg[128] = { 0 };

	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x118] , 0xD3
		JNZ lblNext
		PUSH 0x42370B
		RETN 4


		lblNext :
		LEA ECX, msg
		PUSH ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x11C]
		PUSH EAX
		CALL CallBack::SetVolatileMessageBoxText
		TEST AL, AL
		JE lblContinueExec

		MOV EAX, DWORD PTR DS : [0x6BDAF0]
		MOV DWORD PTR SS : [EBP - 0x29C] , EAX
		PUSH    0
		PUSH	0x373
		LEA EAX, msg
		PUSH EAX
		MOV     ECX, DWORD PTR SS : [EBP - 0x29C]
		MOV     ECX, DWORD PTR DS : [ECX + 0x8C]
		MOV     EDX, DWORD PTR SS : [EBP - 0x29C]
		MOV     EAX, DWORD PTR DS : [EDX + 0x8C]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x8C]
		MOV     EAX, DWORD PTR SS : [EBP + 0x8]
		SHL     EAX, 0x10
		OR      EAX, DWORD PTR SS : [EBP + 0xC]
		MOV     ECX, DWORD PTR SS : [EBP - 0x29C]
		MOV     EDX, DWORD PTR DS : [ECX + 0x8C]
		MOV     DWORD PTR DS : [EDX + 0x1E8] , EAX
		PUSH    1
		MOV     EAX, DWORD PTR SS : [EBP - 0x29C]
		MOV     ECX, DWORD PTR DS : [EAX + 0x8C]
		MOV     EDX, DWORD PTR SS : [EBP - 0x29C]
		MOV     EAX, DWORD PTR DS : [EDX + 0x8C]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x60]
		PUSH 0x4237EF
		RETN 4

		lblContinueExec :
		PUSH 0x42377E
		RETN 4
	}
}

__declspec(naked) void HookPatch::NKD_LoadFiles()
{
	__asm
	{
		CMP ECX, 0xB
		JNZ lblContinue
		PUSH 0x4CCBE5 // RedSanta
		RETN 4

		lblContinue:

		LEA EAX, DWORD PTR SS : [EBP - 0x30]
			PUSH EAX // Mesh (MSH)
			LEA EDX, DWORD PTR SS : [EBP - 0x80]
			PUSH EDX // Texture (WYT)
			MOV EAX, DWORD PTR SS : [EBP - 0xD4]
			MOVSX ECX, WORD PTR DS : [EAX + 0x350]
			PUSH ECX // Id
			CALL CallBack::LoadFile
			PUSH 0x4CCCFC
			RETN 4
	}
}

__declspec(naked) void HookPatch::NKD_CorrectBones()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x358]
		LEA EDX, DWORD PTR DS : [ECX + 0x5C]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		PUSH EAX
		CALL CallBack::CorrectBone
		MOV ECX, DWORD PTR SS : [EBP - 0x358]
		PUSH 0x4E0463
		RETN 4
	}
}

__declspec(naked) void HookPatch::NKD_FixIndex()
{
	__asm
	{
		CMP EAX, 0x1037
		JNZ lblContinue
		PUSH 0x4DF213
		RETN 4

		lblContinue:
		LEA ECX, DWORD PTR SS : [EBP - 0x18]
			PUSH ECX
			MOVSX   EDX, WORD PTR SS : [EBP - 0x10]
			PUSH EDX
			CALL CallBack::AddIndex
			PUSH 0x4DF303
			RETN 4
	}
}

__declspec(naked) void HookPatch::NKD_FixItemDescription() 
{
	static COLORREF line1Color = 0, line2Color = 0, line3Color = 0, line4Color = 0,
		line5Color = 0, line6Color = 0, line7Color = 0, line8Color = 0, line9Color = 0, line10Color = 0;
	static int32_t lineCounter = 0, index = 0;
	static char line2[128] = { 0 }, line3[128] = { 0 }, line4[128]{ 0, },
		line5[128] = { 0 }, line6[128] = { 0 }, line7[128]{ 0, },
		line8[128] = { 0 }, line9[128] = { 0 }, line10[128]{ 0, };

	__asm
	{
		LEA EAX, line10Color
		PUSH EAX
		LEA EAX, line9Color
		PUSH EAX
		LEA EAX, line8Color
		PUSH EAX
		LEA EAX, line7Color
		PUSH EAX
		LEA EAX, line6Color
		PUSH EAX
		LEA EAX, line5Color
		PUSH EAX
		LEA EAX, line4Color
		PUSH EAX
		LEA EAX, line3Color
		PUSH EAX
		LEA EAX, line2Color
		PUSH EAX
		LEA EAX, line1Color
		PUSH EAX
		LEA ECX, line10
		PUSH ECX
		LEA ECX, line9
		PUSH ECX
		LEA ECX, line8
		PUSH ECX
		LEA ECX, line7
		PUSH ECX
		LEA ECX, line6
		PUSH ECX
		LEA ECX, line5
		PUSH ECX
		LEA ECX, line4
		PUSH ECX
		LEA ECX, line3
		PUSH ECX
		LEA ECX, line2
		PUSH ECX
		LEA EDX, DWORD PTR SS : [EBP - 0xA8]
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		PUSH EDX
		CALL CallBack::AddItemDescription
		TEST EAX, EAX
		JE lblContinueExec

		MOV lineCounter, EAX // 2
		MOV index, 0
		JMP LoopStart

		LoopEnd :
		MOV EAX, index
			ADD EAX, 1
			MOV index, EAX
			LoopStart :
		MOV EAX, index
			CMP EAX, lineCounter
			JGE lblContinueExec


			PUSH 0
			CMP index, 0
			JG lblLine2
			LEA ECX, DWORD PTR SS : [EBP - 0xA8]
			PUSH ECX
			JMP lblContinuePush
			lblLine2 :
		CMP index, 1
			JG  lblLine3
			LEA ECX, line2
			PUSH ECX
			JMP lblContinuePush
			lblLine3 :
		CMP index, 2
			JG  lblLine4
			LEA ECX, line3
			PUSH ECX
			JMP lblContinuePush

			lblLine4 :
		CMP index, 3
			JG  lblLine5
			LEA ECX, line4
			PUSH ECX
			JMP lblContinuePush

			lblLine5 :
		CMP index, 4
			JG  lblLine6
			LEA ECX, line5
			PUSH ECX
			JMP lblContinuePush

			lblLine6 :
		CMP index, 5
			JG  lblLine7
			LEA ECX, line6
			PUSH ECX
			JMP lblContinuePush

			lblLine7 :
		CMP index, 6
			JG  lblLine8
			LEA ECX, line7
			PUSH ECX
			JMP lblContinuePush

			lblLine8 :
		CMP index, 7
			JG  lblLine9
			LEA ECX, line8
			PUSH ECX
			JMP lblContinuePush

			lblLine9 :
		CMP index, 8
			JG  lblEmptyLine
			LEA ECX, line9
			PUSH ECX
			JMP lblContinuePush

			lblEmptyLine :
		PUSH 0
			JMP lblContinuePush

			lblContinuePush :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x278C0]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x278C0]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x80]


			CMP index, 0
			JG lblColorLine2
			PUSH line1Color
			JMP lblContinueFuncCall

			lblColorLine2 :
		CMP index, 1
			JG lblColorLine3
			PUSH line2Color
			JMP lblContinueFuncCall

			lblColorLine3 :
		CMP index, 2
			JG lblColorLine4
			PUSH line3Color
			JMP lblContinueFuncCall

			lblColorLine4 :
		CMP index, 3
			JG lblColorLine5
			PUSH line4Color
			JMP lblContinueFuncCall

			lblColorLine5 :
		CMP index, 4
			JG lblColorLine6
			PUSH line5Color
			JMP lblContinueFuncCall

			lblColorLine6 :
		CMP index, 5
			JG lblColorLine7
			PUSH line6Color
			JMP lblContinueFuncCall

			lblColorLine7 :
		CMP index, 6
			JG lblColorLine8
			PUSH line7Color
			JMP lblContinueFuncCall

			lblColorLine8 :
		CMP index, 7
			JG lblColorLine9
			PUSH line8Color
			JMP lblContinueFuncCall

			lblColorLine9 :
		CMP index, 8
			JG lblNoColor
			PUSH line9Color
			JMP lblContinueFuncCall

			lblNoColor :
		PUSH 0
			JMP lblContinueFuncCall

			lblContinueFuncCall :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x278C0]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x278C0]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x84]

			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			ADD ECX, 0x1
			MOV DWORD PTR SS : [EBP - 0x28] , ECX

			JMP LoopEnd

			lblContinueExec :
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
			MOV EAX, DWORD PTR DS : [EDX + 0x670]

			PUSH 0x420834
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GetHTTP()
{
	static int AddrSave = 0;
	static int jmp_saida = 0x4B80E7;

	_asm
	{
		LEA EDX, DWORD PTR SS : [EBP - 0x458]
		MOV AddrSave, EDX
	}

	memcpy(&Global::ServerList.Server, "500 -1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1", 39);
	*(SvRtn*)(AddrSave) = Global::ServerList;

	_asm
	{
		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Start()
{
	_asm
	{
		CALL CallBack::HKD_Start

		MOV DWORD PTR DS : [0x6BDAF0] , 0
		PUSH 0x4BDA67
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_Open()
{
	static int call_1 = 0x5B7E64;
	_asm
	{
		CALL CallBack::HKD_Open

		PUSH 0x5F986C
		PUSH 0x5F9850
		CALL call_1
		ADD ESP, 0x8

		PUSH 0x54B5D7
		RETN
	}
}

#pragma region Hook_GUI_World


int i_arg1, i_arg2, i_arg3, i_arg4;
int i_arg_callback_mouse1 = 0, i_arg_callback_mouse2 = 0, i_arg_callback_mouse3 = 0, i_arg_callback_mouse4 = 0, i_arg_callback_mouse5 = 0, i_arg_callback_mouse6 = 0, i_arg_callback_mouse7 = 0, i_arg_callback_mouse8 = 0, i_arg_callback_mouse9 = 0, i_arg_callback_mouse10 = 0;
int i_arg_callback_1 = 0, i_arg_callback_2 = 0, i_arg_callback_3 = 0, i_arg_callback_4 = 0, i_arg_callback_5 = 0, i_arg_callback_6 = 0, i_arg_callback_7 = 0, i_arg_callback_8 = 0, i_arg_callback_9 = 0, i_arg_callback_10 = 0;
char Packet_Buffer379[24];

__declspec(naked) void HookPatch::NKD_Create_Scene_World()
{
	//hooks.setHook(eHookType::JMP, 0x449DD0 , hooks.getAddress(&HookPatch::NKD_Create_Scene_World));
	/*
		00449DD0  |. 68 1F030000    PUSH 31F
		00449DD5  |. 8B95 7CF9FFFF  MOV EDX,DWORD PTR SS:[EBP-684]
		00449DDB  |. 8B4A 28        MOV ECX,DWORD PTR DS:[EDX+28]
		00449DDE  |. 8B85 7CF9FFFF  MOV EAX,DWORD PTR SS:[EBP-684]
		00449DE4  |. 8B50 28        MOV EDX,DWORD PTR DS:[EAX+28]
		00449DE7  |. 8B02           MOV EAX,DWORD PTR DS:[EDX]
		00449DE9  |. FF50 48        CALL DWORD PTR DS:[EAX+48]
		00449DEC  |. 8B8D 7CF9FFFF  MOV ECX,DWORD PTR SS:[EBP-684]
		00449DF2  |. 8981 94870200  MOV DWORD PTR DS:[ECX+28794],EAX
		00449DF8  |. 68 6CC05E00    PUSH WYD.005EC06C                        ; /Arg1 = 005EC06C ASCII ">> Init Field Scene::End
		"
		00449DFD  |. E8 8F1DFFFF    CALL WYD.0043BB91                        ; \WYD.0043BB91
		00449E02  |. 83C4 04        ADD ESP,4
	*/



	static int jmp_saida = 0x449DF8;
	static int callFunc = 0x43BB91;
	_asm
	{
		PUSH 0x31F
		MOV EDX, DWORD PTR SS : [EBP - 0x684]
		MOV i_arg1, EDX
		MOV ECX, DWORD PTR DS : [EDX + 0x28]
		MOV i_arg2, ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x684]
		MOV EDX, DWORD PTR DS : [EAX + 0x28]
		MOV EAX, DWORD PTR DS : [EDX]
		MOV i_arg3, EAX
		CALL DWORD PTR DS : [EAX + 0x48]
		MOV ECX, DWORD PTR SS : [EBP - 0x684]
		MOV DWORD PTR DS : [ECX + 0x28794] , EAX
		MOV i_arg4, EAX

		PUSH i_arg4
		PUSH i_arg3
		PUSH i_arg2
		PUSH i_arg1
		CALL CallBack::HKD_Create_Scene_World
		PUSH 0x5EC06C
		CALL callFunc
		ADD ESP, 4
		PUSH 0x449E05
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_World_Fix_Skill_Descricao()
{
	//hooks.setHook(eHookType::JMP, 0x47DF41  , hooks.getAddress(&HookPatch::NKD_Create_Scene_World_Fix_Skill_Descricao), 4);


	static int jmp_saida = 0x47DF69;
	_asm
	{
		/*Preciso somar com a posição da GUI Main*/

		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV ECX, DWORD PTR SS : [EBP - 0x134]
		MOV EDX, DWORD PTR DS : [ECX + EAX * 0x4 + 0x28724] // Pega a Referencia do Elemento que o mouse ta em cima (skill buff)
		FLD DWORD PTR DS : [EDX + 0x50] //Carrega o Valor Float
		FADD DWORD PTR DS : [0x5CDC68] //soma

		MOV EAX, DWORD PTR SS : [EDX + 0x4] //Main Gui 
		FADD DWORD PTR DS : [EAX + 0x50]  //Soma com o float do main gui

		/*Guarda em EAX*/
		MOV EAX, DWORD PTR SS : [EBP - 0x4]

		MOV DWORD PTR SS : [EBP - 0x4] , 0x42700000
		FSUB DWORD PTR SS : [EBP - 0x4]

		/*Retorna pra EAX*/
		MOV DWORD PTR SS : [EBP - 0x4] , EAX

		MOV EAX, DWORD PTR SS : [EBP - 0x134]
		MOV ECX, DWORD PTR DS : [EAX + 0x28764] // pad_gui da descrição
		FSTP DWORD PTR DS : [ECX + 0x50]

		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_World_Fix_Gui_Adjust()
{
	//hooks.setHook(eHookType::JMP, 0x4429D9  , hooks.getAddress(&HookPatch::NKD_Create_Scene_World_Fix_Gui_Adjust), 1);


	static int jmp_saida = 0x442A06;
	_asm
	{

		MOV EDX, DWORD PTR SS : [EBP - 0x684]
		MOV EAX, DWORD PTR DS : [EDX + 0x27AB0]
		CMP DWORD PTR DS : [EAX + 0x44] , 0x10083
		JE lbl_saida

		MOV EDX, DWORD PTR SS : [EBP - 0x684]
		MOV EAX, DWORD PTR DS : [EDX + 0x27AB0]
		FSTP DWORD PTR DS : [EAX + 0x4C]

		lbl_saida :
		MOV ECX, DWORD PTR SS : [EBP - 0x684]
		MOV EDX, DWORD PTR DS : [ECX + 0x27AB0]
		MOV EAX, DWORD PTR SS : [EBP - 0x150]
		FLD DWORD PTR DS : [EAX + 0x50]
		FSUB DWORD PTR DS : [EDX + 0x58]
		FSTP DWORD PTR SS : [EBP - 0x714]


		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_World_Fix_Gui_Adjust2()
{
	//hooks.setHook(eHookType::JMP, 0x448AA9  , hooks.getAddress(&HookPatch::NKD_Create_Scene_World_Fix_Gui_Adjust2), 1);


	static int jmp_saida = 0x448AC7;
	_asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x268]
		CMP DWORD PTR DS : [EDX + 0x44] , 0x741
		JE lbl_fix

		MOV EDX, DWORD PTR SS : [EBP - 0x268]
		FLD DWORD PTR DS : [EDX + 0x50]
		FADD DWORD PTR DS : [0x5CE340]
		MOV EAX, DWORD PTR SS : [EBP - 0x268]
		FSTP DWORD PTR DS : [EAX + 0x50]
		MOV ECX, DWORD PTR SS : [EBP - 0x684]
		JMP jmp_saida

		lbl_fix :

		MOV EDX, DWORD PTR SS : [EBP - 0x268]
			FLD DWORD PTR DS : [EDX + 0x50]
			//FADD DWORD PTR DS : [0x5CE340]
			MOV EAX, DWORD PTR SS : [EBP - 0x268]
			FSTP DWORD PTR DS : [EAX + 0x50]
			MOV ECX, DWORD PTR SS : [EBP - 0x684]

			JMP jmp_saida



			MOV EDX, DWORD PTR SS : [EBP - 0x684]
			MOV EAX, DWORD PTR DS : [EDX + 0x27AB0]
			CMP DWORD PTR DS : [EAX + 0x44] , 0x10083
			JE lbl_saida

			MOV EDX, DWORD PTR SS : [EBP - 0x684]
			MOV EAX, DWORD PTR DS : [EDX + 0x27AB0]
			FSTP DWORD PTR DS : [EAX + 0x4C]

			lbl_saida :
			MOV ECX, DWORD PTR SS : [EBP - 0x684]
			MOV EDX, DWORD PTR DS : [ECX + 0x27AB0]
			MOV EAX, DWORD PTR SS : [EBP - 0x150]
			FLD DWORD PTR DS : [EAX + 0x50]
			FSUB DWORD PTR DS : [EDX + 0x58]
			FSTP DWORD PTR SS : [EBP - 0x714]


			JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_Login_Fix_Gui_LoginScreen_Opacity()
{
	//hooks.setHook(eHookType::JMP, 0x4B6E19  , hooks.getAddress(&HookPatch::NKD_Create_Scene_Login_Fix_Gui_LoginScreen_Opacity), 4);

	static int jmp_saida = 0x4B6E28;
	_asm
	{

		MOV EAX, DWORD PTR SS : [EBP - 0x24]
		MOV ECX, DWORD PTR DS : [EAX + 0x26E48]
		CMP DWORD PTR DS : [ECX + 0x44] , 0x1014E
		JE loginscren
		MOV DWORD PTR DS : [ECX + 0x94] , EDX
		JMP jmp_saida

		loginscren :
		MOV DWORD PTR DS : [ECX + 0x94] , 0xFFFFFFFF
			JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_CallBack_Handle_Click()
{
	static int jmp_saida = 0x40C674;
	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP + 0xC]
		MOV i_arg_callback_1, ECX
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		MOV i_arg_callback_2, EDX
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV i_arg_callback_3, EAX
		MOV ECX, DWORD PTR DS : [EAX + 0x8]
		MOV i_arg_callback_4, ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x4]

		MOV EAX, DWORD PTR DS : [EDX + 0x8]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV i_arg_callback_5, EDX
		CALL DWORD PTR DS : [EDX + 0x58] // 0x4B7DE9  VTable = 0x5CE588
		MOV i_arg_callback_6, EAX

		PUSH i_arg_callback_10
		PUSH i_arg_callback_9
		PUSH i_arg_callback_8
		PUSH i_arg_callback_7
		PUSH i_arg_callback_6
		PUSH i_arg_callback_5
		PUSH i_arg_callback_4
		PUSH i_arg_callback_3
		PUSH i_arg_callback_2
		PUSH i_arg_callback_1
		CALL CallBack::HKD_CallBack_Handle_Click

		MOV EAX, i_arg_callback_6

		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_CallBack_Mouse()
{
	static int call_1 = 0x401000;
	static int jmp_JE = 0x403877;
	static int jmp_saida = 0x4037C4;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV i_arg_callback_mouse1, ECX
		MOV EDX, DWORD PTR DS : [ECX + 0x58]
		MOV i_arg_callback_mouse2, EDX
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		MOV ECX, DWORD PTR DS : [EAX + 0x54]
		MOV i_arg_callback_mouse3, ECX
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EAX, DWORD PTR DS : [EDX + 0x50]
		MOV i_arg_callback_mouse4, EAX
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x4C]
		MOV i_arg_callback_mouse5, EDX
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP + 0x14]
		MOV i_arg_callback_mouse6, EAX
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP + 0x10]
		MOV i_arg_callback_mouse7, ECX
		PUSH ECX
		CALL call_1
		ADD ESP, 0x18

		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [EDX + 0x3C]
		MOV i_arg_callback_mouse10, EDX

		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV DWORD PTR DS : [EDX + 0x34] , EAX
		MOV i_arg_callback_mouse8, EAX
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		MOV i_arg_callback_mouse9, EAX




		PUSH i_arg_callback_mouse10
		PUSH i_arg_callback_mouse9
		PUSH i_arg_callback_mouse8
		PUSH i_arg_callback_mouse7
		PUSH i_arg_callback_mouse6
		PUSH i_arg_callback_mouse5
		PUSH i_arg_callback_mouse4
		PUSH i_arg_callback_mouse3
		PUSH i_arg_callback_mouse2
		PUSH i_arg_callback_mouse1
		CALL CallBack::HKD_CallBack_Mouse
		MOV EAX, i_arg_callback_mouse9


		CMP DWORD PTR DS : [EAX + 0x1F0] , 0
		JE jmp_saida_JE

		JMP jmp_saida

		jmp_saida_JE :
		JMP jmp_JE


	}
}

__declspec(naked) void HookPatch::NKD_CallBack_Inf_Mouse()
{
	static int jmp_saida = 0x4A658A;
	_asm
	{
		PUSH DWORD PTR SS : [EBP - 0x4]
		PUSH DWORD PTR SS : [EBP + 0x14]
		PUSH DWORD PTR SS : [EBP + 0x10]
		PUSH DWORD PTR SS : [EBP + 0xC]
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL CallBack::HKD_CallBack_Inf_Mouse

		MOV EDX, DWORD PTR SS : [EBP + 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP + 0xC]
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV ECX, DWORD PTR DS : [EAX + 0x28]
		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		MOV EAX, DWORD PTR DS : [EDX + 0x28]
		MOV EDX, DWORD PTR DS : [EAX]
		CALL DWORD PTR DS : [EDX + 0x8]

		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_CallBack_Event_Click()
{
	static int jmp_saida = 0x403A36;

	static int jmp_noclick = 0x4038A1;
	static int jmp_down = 0x4038D4;
	static int jmp_up = 0x403921;
	_asm
	{
		PUSH DWORD PTR SS : [EBP - 0xC]
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		PUSH ECX //Gui
		PUSH DWORD PTR DS : [ECX + 0x44] //Handle
		CALL CallBack::HKD_CallBack_Event_Click
		CMP DWORD PTR SS : [EBP - 0xC] , 0x200
		JE lbl_noclick
		CMP DWORD PTR SS : [EBP - 0xC] , 0x201
		JE lbl_click_down
		CMP DWORD PTR SS : [EBP - 0xC] , 0x202
		JE lbl_click_up
		PUSH 0x403A36
		RETN

		lbl_noclick :
		PUSH 0x4038A1
			RETN

			lbl_click_down :
		PUSH 0x4038D4
			RETN

			lbl_click_up :
		PUSH 0x403921
			RETN


	}

}

__declspec(naked) void HookPatch::NKD_CallBack_Label()
{
	static int call_1 = 0x539CCD;
	static int jmp_saida = 0x402340;

	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		PUSH EAX
		CALL CallBack::HKD_CallBack_Label

		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		PUSH EAX
		CALL call_1
		ADD ESP, 0x4
		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_CallBack_Event_Esc()
{
	static int call_1 = 0x40B980;

	static int addr_jmp_jnz = 0x454A72;
	static int addr_jmp_saida = 0x454CAE;

	_asm
	{
		/*Guarda o Valor em ECX*/
		MOV ECX, EAX

		CALL CallBack::HKD_CallBack_Event_Esc

		TEST AL, AL
		JNZ lbl_saida //retorna true ele jumpa, se retornar false ele n jumpa


		/*retorna o Valor pra EAX*/
		MOV EAX, ECX


		MOV ECX, DWORD PTR SS : [EBP - 0x38]
		CALL call_1
		CMP EAX, 1
		JNZ lbl_proximo
		PUSH 0x0
		PUSH 0x100E9
		MOV EAX, DWORD PTR SS : [EBP - 0x40]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x40]
		CALL DWORD PTR DS : [EDX + 0x58]
		JMP addr_jmp_saida


		lbl_proximo :
		JMP addr_jmp_jnz

			lbl_saida :
		/*retorna o Valor pra EAX*/
		MOV EAX, ECX

			JMP addr_jmp_saida

	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_Login()
{
	static int jmp_saida = 0x4B4FB0;
	_asm
	{
		PUSH 0x10156
		MOV EDX, DWORD PTR SS : [EBP - 0x5DC]
		MOV i_arg1, EDX
		MOV ECX, DWORD PTR DS : [EDX + 0x28]
		MOV i_arg2, ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x5DC]
		MOV EDX, DWORD PTR DS : [EAX + 0x28]
		MOV EAX, DWORD PTR DS : [EDX]
		MOV i_arg3, EAX
		CALL DWORD PTR DS : [EAX + 0x48]
		MOV ECX, DWORD PTR SS : [EBP - 0x5DC]
		MOV DWORD PTR DS : [ECX + 0x26E54] , EAX
		MOV i_arg4, EAX
		PUSH i_arg4
		PUSH i_arg3
		PUSH i_arg2
		PUSH i_arg1
		CALL CallBack::HKD_Create_Scene_Login
		MOV EAX, i_arg4

		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_Login_After()
{
	static int call_1 = 0x5344A9;
	static int jmp_saida = 0x4BF207;
	_asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x10]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x54]
		MOV ECX, DWORD PTR DS : [EAX + 0x21924]
		CALL call_1

		CALL CallBack::HKD_Create_Scene_Login_After
		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_Login_Panel()
{
	static int call_1 = 0x40332E;
	static int jmp_saida = 0x4A3319;
	_asm
	{
		/*Se for ele entra*/
		CMP DWORD PTR SS : [EBP - 0x14C] , 0x10151
		JE jmp_JE

		/*Se for ele entra*/
		CMP DWORD PTR SS : [EBP - 0x14C] , 0x10152
		JE jmp_JE_Voltar

		LEA ECX, DWORD PTR SS : [EBP - 0x120]
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x12C]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x130]
		PUSH EAX
		FILD DWORD PTR SS : [EBP - 0x134]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		FILD DWORD PTR SS : [EBP - 0x138]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		FILD DWORD PTR SS : [EBP - 0x13C]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		FILD DWORD PTR SS : [EBP - 0x140]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		MOV ECX, DWORD PTR SS : [EBP - 0x144]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x38C]
		CALL call_1
		MOV DWORD PTR SS : [EBP - 0x3CC] , EAX
		JMP jmp_saida


	}

	_asm
	{
	jmp_JE:
		MOV DWORD PTR SS : [EBP - 0x120] , 0
			//MOV DWORD PTR SS : [EBP - 0x144], 580

			LEA ECX, DWORD PTR SS : [EBP - 0x120] //Login
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x12C] //
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0x130] //Alinha?
			PUSH EAX
			FILD DWORD PTR SS : [EBP - 0x134] //height
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x138] //width
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x13C] //y
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x140] //x
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			MOV ECX, DWORD PTR SS : [EBP - 0x144]
			PUSH ECX
			MOV ECX, DWORD PTR SS : [EBP - 0x38C]
			CALL call_1
			MOV DWORD PTR SS : [EBP - 0x3CC] , EAX
			JMP jmp_saida

			jmp_JE_Voltar :
		MOV DWORD PTR SS : [EBP - 0x120] , 0
			//MOV DWORD PTR SS : [EBP - 0x144], 580

			LEA ECX, DWORD PTR SS : [EBP - 0x120] //Login
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x12C] //
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0x130] //Alinha?
			PUSH EAX
			FILD DWORD PTR SS : [EBP - 0x134] //height
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x138] //width
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x13C] //y
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			FILD DWORD PTR SS : [EBP - 0x140] //x
			PUSH ECX
			FSTP DWORD PTR SS : [ESP]
			MOV ECX, DWORD PTR SS : [EBP - 0x144]
			PUSH ECX
			MOV ECX, DWORD PTR SS : [EBP - 0x38C]
			CALL call_1
			MOV DWORD PTR SS : [EBP - 0x3CC] , EAX
			JMP jmp_saida

	}
}

__declspec(naked) void HookPatch::NKD_Att_Label_EXP()
{
	//hooks.setHook(eHookType::JMP, 0x48E9A9 , hooks.getAddress(&HookPatch::NKD_Att_Label_EXP),1);

	static int jmp_saida = 0x48E9B6;
	_asm
	{
		CALL CallBack::HKD_Att_Label_EXP

		MOV EDX, DWORD PTR SS : [EBP - 0xDC]
		MOVSX EAX, BYTE PTR DS : [EDX + 0x26E94]
		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_World_Fix_Gui_Message_Adjust()
{
	//hooks.setHook(eHookType::JMP, 0x442A35  , hooks.getAddress(&HookPatch::NKD_Create_Scene_World_Fix_Gui_Message_Adjust), 1);



	static int jmp_saida = 0x442A50;
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x684]
		MOV ECX, DWORD PTR DS : [EAX + 0x27ABC]
		CMP DWORD PTR DS : [ECX + 0x44] , 0x10197
		JE lbl_saida

		MOV EAX, DWORD PTR SS : [EBP - 0x684]
		MOV ECX, DWORD PTR DS : [EAX + 0x27ABC]
		FSTP DWORD PTR DS : [ECX + 0x4C]

		lbl_saida :
		MOV EDX, DWORD PTR SS : [EBP - 0x684]
		MOV ESI, DWORD PTR DS : [EDX + 0x027AB0]

		JMP jmp_saida
	}
}

__declspec(naked) void HookPatch::NKD_Create_Scene_World_MobTarget()
{
	//hooks.setHook(eHookType::JMP, 0x4DC869 , hooks.getAddress(&HookPatch::NKD_Create_Scene_World_MobTarget),2);

	static int jmp_saida = 0x4DC8A5;
	static int call_CreateProgress = 0x404CB4;
	_asm
	{
		// sprite, curr, max, X, Y, Width, Height, color, backcolor, 1);
		PUSH 1
		PUSH 0x40333333
		PUSH 0x80800000
		PUSH 0x41900000
		PUSH 0x43480000
		MOV EAX, 0x428c0000
		PUSH EAX			//y
		PUSH 0x428c0000		//x
		PUSH 0				//max
		PUSH 0x1E			//curr
		PUSH - 2				//sprite
		MOV ECX, DWORD PTR SS : [EBP - 0x60]
		CALL call_CreateProgress
		MOV DWORD PTR SS : [EBP - 0x98] , EAX
		JMP jmp_saida
	}
}

#pragma endregion