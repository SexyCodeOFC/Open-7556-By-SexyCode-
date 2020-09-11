#include "stdafx.h"
#include <hook.h>
#include "HookPatch.h"
#include "HookImpl.h"
#include "Functions.h"

static int jmp_addr;
static int reg_aux;

bool HookPatch::initialize()
{
	try
	{
		auto& hooks = HookMgr::instance();

		hooks.setHook(eHookType::JMP, 0x45E2F0, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage), 4);
		hooks.setHook(eHookType::JMP, 0x4BCF2E, hooks.getAddress(&HookPatch::NKD_MobKilled_Event), 5);
		 

		/* Corrige a compra de item no NPC */
		hooks.setHook(eHookType::JMP, 0x48ED3D, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_FixBuyItem), 4);

		/*Anula o Exp quando morre*/
		hooks.setHook(eHookType::JMP, 0x4BBE29, hooks.getAddress(&NKD_ExpControlInDead), 4);
		/* Correção do /gritar e @ para não ficar sem acentos.*/
		hooks.setHook(eHookType::JMP, 0x4896AF, 0x4896C1, 4);
		hooks.setHook(eHookType::JMP, 0x48D262, 0x48D274, 4);

		/* Correção para adicionar novos items agrupáveis */
		hooks.setHook(eHookType::JMP, 0x4086FD, hooks.getAddress(&HookPatch::NKD_FixJoinableItens), 1);
		// Definindo tempo menor na dominação do altar
		hooks.setHook(eHookType::JMP, 0x4AB6D1, hooks.getAddress(HookPatch::NKD_RegenMob_CastleStatus), 2);  



		hooks.setHook(eHookType::JNZ, 0x4C4DB1, hooks.getAddress(&NKD_SetAffect_FixNewAffects));
		hooks.setHook(eHookType::JMP, 0x40A2C0, hooks.getAddress(&NKD_BASE_GetCurrentScore_NewAffects), 1);
		hooks.setHook(eHookType::JMP, 0x464093, hooks.getAddress(&NKD_GetDamage));
		hooks.setHook(eHookType::JMP, 0x429396, hooks.getAddress(&NKD_GetDamage2));
		hooks.setHook(eHookType::JMP, 0x4646FB, hooks.getAddress(&NKD_GetSkillDamage));
		hooks.setHook(eHookType::JMP, 0x467642, hooks.getAddress(&NKD_GetParryRate));
		hooks.setHook(eHookType::JMP, 0x4D2397, hooks.getAddress(&NKD_GetParryRate2));

		/* Hooks para implementação do sistema de userData */
		hooks.setHook(eHookType::JMP, 0x4A2E49, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_AccountLogin), 2);
		hooks.setHook(eHookType::JMP, 0x4B95FD, hooks.getAddress(&HookPatch::NKD_SaveUser), 2);
		hooks.setHook(eHookType::JMP, 0x4B8273, hooks.getAddress(&HookPatch::NKD_CloseUser), 2);

		/* Manipulação de SendPacket and RecvPacket */
		//hooks.setHook(eHookType::JMP, 0x401203, hooks.getAddress(&HookPatch::NKD_AddMessage));
		//hooks.setHook(eHookType::JMP, 0x40124E, hooks.getAddress(&HookPatch::NKD_ReadMessage));

		/* Receive DB Packet */
		hooks.setHook(eHookType::JMP, 0x401136, hooks.getAddress(HookPatch::NKD_ProcessDBMessage));

		/* Pula definição de variável sem memória */
		hooks.fillWithNop(0x4A297E, 6);
		hooks.fillWithNop(0x4A2999, 6);

		/* Pula as HashKeys do Packet AccountLogin do ProcessDBMessage */
		hooks.setHook(eHookType::JMP, 0x4A2C43, 0x4A2C67, 6);
		hooks.setHook(eHookType::JMP, 0x4A2C87, 0x4A2CAA, 3);

		/* Reescreve a função GetEmptyUser para evitar acumulo de Connection */
		hooks.setHook(eHookType::JMP, 0x401726, hooks.getAddress(HookPatch::NKD_GetEmptyUser));

		/* Pula a verificação de ClientVersion no AccountLogin */
		hooks.setHook(eHookType::JMP, 0x45F71B, 0x45F7AB, 2);
			 

		/* Desativa a volta da refinação nas Poeiras */
		hooks.fillWithNop(0x471274, 3);
		hooks.fillWithNop(0x4712CE, 35);
 

		/* Desativa a reconexão com a DBSRV */
		hooks.setHook(eHookType::JMP, 0x45CE13, 0x45CEC2, 2);

		/* Corrige a reoganização no baú */
		hooks.setHook(eHookType::JMP, 0x4A2800, 0x4A28F3, 5);

		/* Corrige a utilização do Packet UpdateItem 0x374 */
		hooks.setHook(eHookType::JE, 0x45E50D, 0x47D690);

		/* Corrige para que as Torres do Castle War nascem */
		hooks.setHook(eHookType::JMP, 0x4B5481, hooks.getAddress(&HookPatch::NKD_GuildProcess_FixTowerSpawn), 5);

		/* Esse Hook descarta o resto do packet sem dar disconnect */
		hooks.setHook(eHookType::JMP, 0x4208CF, hooks.getAddress(&HookPatch::NKD_ReadMessage_Fix), 4);

		/* Controle de Mana atualizando em tempo real */
		//hooks.setHook(eHookType::JMP, 0x467F07, hooks.getAddress(&NKD_ProcessClientMessage_ManaUpdate), 1);

		/* Modifica o packet CharacterLogin para mandar a info da guild */
		hooks.setHook(eHookType::JMP, 0x4A64A1, hooks.getAddress(&HookPatch::NKD_ProcessDBMessage_CharacterLogin), 4);

		/* Adiciona um contador de movimento diferente */
		hooks.setHook(eHookType::JMP, 0x46131D, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_DiffrentMove), 3);

		/* Modifica as funções para adicionar um Anti PartyHack */
		hooks.setHook(eHookType::JMP, 0x49058C, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_LastReqParty), 1);
		hooks.setHook(eHookType::JMP, 0x4C089A, hooks.getAddress(&HookPatch::NKD_RemoveParty_LastReqParty), 4);

		/* Correção do Crítico */
		// FIX 1 (Para essa fix necessário structs mob ser modificada)hooks.setHook(eHookType::JMP, 0x463F98, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_ChangeDoubleCritical), 2);
		// FIX 2 
		/* Correção do Crítico 2 */
		hooks.setHook(eHookType::JMP, 0x410C87, hooks.getAddress(&NKD_CriticalBug));

		// Remover o Limitador de Exp
		hooks.setValue(0x004BDD55 + 6, 250000);
		hooks.setValue(0x004BDD61 + 6, 250000);

		/* BASE_GetCurrentScore */
		hooks.setHook(eHookType::JMP, 0x0040192E, hooks.getAddress(&HookImpl::BASE_GetCurrentScore));

		/* Controle no ProcessSecMinTimer */
		hooks.setHook(eHookType::JMP, 0x401082, hooks.getAddress(&HookImpl::processSecTimer));
		hooks.setHook(eHookType::JMP, 0x401AF0, hooks.getAddress(&HookImpl::processMinTimer));

		/* Desativa HellGate nativo */
		hooks.fillWithNop(0x4B0A4E, 14);
		hooks.setHook(eHookType::JMP, 0x4B5EC9, 0x4B5EEB);

		/* Desativa o LOG da função PutItem */
		hooks.setHook(eHookType::JMP, 0x44EF83, 0x44EFE5, 4);

		/* Corrige a Guerra de Castelos */
		hooks.setHook(eHookType::JMP, 0x4B174E, hooks.getAddress(&HookPatch::NKD_ProcessMinTimer_FixWarNoatun), 1);
		hooks.fillWithNop(0x4B17BD, 19);

		/* Usa outro SetItemBonus no lugar do Nativo para a Repletion */
		hooks.setHook(eHookType::JMP, 0x47C723, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_ReplationRate), 2);

		/* Desativa o Controle de Mana Nativo */
		hooks.setHook(eHookType::JMP, 0x467E00, 0x467F1F, 5);
		hooks.setHook(eHookType::JMP, 0x4D28A8, 0x4D296C, 4);
		hooks.setHook(eHookType::JMP, 0x4C9311, 0x4C940D, 4);

		/* Adiciona Guerra de Torres para 1 Canal */
		hooks.setHook(eHookType::JMP, 0x4B6209, hooks.getAddress(&HookPatch::NKD_GuildProcess_WarTower), 2);
		hooks.setHook(eHookType::JMP, 0x458367, hooks.getAddress(&HookPatch::NKD_GenerateMob_WarTower), 4);
		hooks.setHook(eHookType::JMP, 0x4BD3C2, hooks.getAddress(&HookPatch::NKD_MobKilled_WarTower));
		hooks.setHook(eHookType::JMP, 0x461A07, 0x461A8C, 2);

		/* Modificação para Sapphire estar ambos em reinos o valor de 20 */
		hooks.setHook(eHookType::JMP, 0x44150C, hooks.getAddress(&HookPatch::NKD_ProcessNPC_SapphireValue), 1);
		hooks.setHook(eHookType::JMP, 0x441521, hooks.getAddress(&HookPatch::NKD_ProcessNPC_SapphireValue2), 1);
		/* Modificação para Sendpacket */
		hooks.setHook(eHookType::JMP, 0x4211BD, hooks.getAddress(&HookPatch::NKD_processSend), 1);
		
		//Fix temporário para Dragão noatun
		hooks.setHook(eHookType::JMP, 0x4A6FD4, hooks.getAddress(&NKD_AfterEnterWorld));

		hooks.setHook(eHookType::JMP, 0x4BDE58, hooks.getAddress(&NKD_MobKilledExpControl));

		// Controle de Exp
		hooks.setHook(eHookType::JMP, 0x00401C8A, hooks.getAddress(&HookImpl::ExpControl));
		//hook responsavel por enviar informações da interface ao servidor.
	//	hooks.setHook(eHookType::JMP, 0x48960A, hooks.getAddress(&NKD_ProcessClientMessage_ReadCommand), 1);
		//hook para controle de movimento dos players
		hooks.setHook(eHookType::JMP, 0x461678, hooks.getAddress(&HookPatch::NKD_ProcessClientMessage_OnPlayerMovement), 4);

		// Desativa Pista de Runas nativa
		hooks.fillWithNop(0x4B0D16, 2);
		hooks.setValue(0x004B0D1F, 0xEB);


		hooks.setHook(eHookType::JMP, 0x4698FA, hooks.getAddress(&HookPatch::NKD_TeleportPosition), 2);



		assert(sizeof(STRUCT_ITEM) == 8);
		assert(sizeof(STRUCT_SCORE) == 28);
		assert(sizeof(STRUCT_MOB) == 756);
		assert(sizeof(CMob) == 1724);
		assert(sizeof(CUser) == 3160);
		assert(sizeof(CPSock) == 76);
		assert(sizeof(NPCGENLIST) == 2992);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

__declspec(naked) void HookPatch::NKD_TeleportPosition()
{
	__asm
	{
		LEA EAX, [EBP - 0XC04]
		PUSH EAX
		LEA ECX, [EBP - 0XBF4]
		PUSH ECX
		LEA EDX, [EBP - 0xBF0]
		PUSH EDX
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::teleportPosition


		TEST EAX, EAX
		JNZ Pula

		LEA EAX, [EBP - 0xC04]
		PUSH EAX
		MOV EAX, 0x469901
		JMP EAX

		Pula :
		MOV EAX, 0x469917
			JMP EAX
	}
}
__declspec(naked) void HookPatch::NKD_ProcessClientMessage_OnPlayerMovement()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x318] // Packet
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::onPlayerMovement
		TEST AL, AL // return false
		JE lblContinueExecution
		PUSH 0x4915F7
		RETN

		lblContinueExecution :
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
			IMUL EAX, EAX, 0x6BC
			PUSH 0x461681
			RETN
	}
}
// aqui dentro vai chamar os comandos que serão enviado do cliente ao servidor
__declspec(naked) void HookPatch::NKD_ProcessClientMessage_ReadCommand()
{
	__asm
	{
		MOV DWORD PTR SS : [EBP - 0x3920] , ECX
		PUSH DWORD PTR SS : [EBP - 0x3914] // MSG
		PUSH DWORD PTR SS : [EBP + 0x8]    // USER
		CALL HookImpl::Commands
		TEST AL, AL
		JE lblContinue // Se retornar false (0), continua na TMSRV, true (1) sai fora
		PUSH 0x4915F7
		RETN

		lblContinue :
		MOV DWORD PTR SS : [EBP - 0x3920] , ECX
			PUSH 0x489610
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_RegenMob_CastleStatus()
{
	__asm
	{
		CMP DWORD PTR DS : [EAX + 0x752C470], 0x4
			JLE lblContinue
			PUSH 0x004AB6DE
			RETN

		lblContinue :
		PUSH 0x4AB7E7
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_CriticalBug()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
		XOR ECX, ECX
		MOV CX, WORD PTR DS : [EAX]
		MOV EDX, DWORD PTR SS : [EBP + 0xC]
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [EDX]
		CMP ECX, EAX
		JE lbl_saida

		PUSH 0x410D05
		RETN

		lbl_saida :
		PUSH 0x410D05
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_MobKilledExpControl()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x2A8] //Exp 
			PUSH DWORD PTR SS : [EBP - 0x290] //MemberID quem está no grupo
			PUSH DWORD PTR SS : [EBP + 0xC]	  //KillerID Quem está matando
			CALL HookImpl::ControlExperience

			MOV DWORD PTR SS : [EBP - 0x2A8], EAX

			MOV EDX, DWORD PTR SS : [EBP - 0x290]
			IMUL EDX, EDX, 0x6BC
			MOV EAX, DWORD PTR DS : [EDX + 0x1FDECBC]
			ADD EAX, DWORD PTR SS : [EBP - 0x2A8]

			PUSH 0x4BDE70
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_BASE_GetCurrentScore_NewAffects()
{
	__asm
	{
		PUSH[EBP + 0xC]
			PUSH[EBP + 0x8]
			PUSH DWORD PTR SS : [EBP - 0xB4]
			CALL HookImpl::NewAffectValue
			TEST AL, AL
			JNZ lblContinueLoop
			MOV EAX, DWORD PTR SS : [EBP - 0xB4]
			PUSH 0x40A2C6
			RETN

		lblContinueLoop :
		PUSH 0x40A29C
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_SetAffect_FixNewAffects()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0xC]
			CMP EAX, MAX_EFFECT_NAME
			JG lblNotFound
			PUSH 0x4C4DB7
			RETN

		lblNotFound :
		PUSH 0x4C4EEF
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_GetParryRate()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP + 8] // Mob que Ataca
			PUSH DWORD PTR SS : [EBP - 0x588] // Mob que Recebe Ataque
			PUSH EAX
			CALL HookImpl::GetParryRate
			MOV DWORD PTR SS : [EBP - 0x808], EAX // Valor da Evasão
			PUSH 0x467648
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GetParryRate2()
{
	static auto Call_Near = reinterpret_cast<void*>(0x4E46F0);
	__asm
	{
		PUSH DWORD PTR SS : [EBP + 0x8]
			PUSH DWORD PTR SS : [EBP + 0x0C]
			PUSH EAX
			CALL HookImpl::GetParryRate
			MOV DWORD PTR SS : [EBP - 0x48], EAX
			CALL Call_Near
			PUSH 0x4D239F
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GetDamage()
{
	static auto Call_Near = reinterpret_cast<void*>(0x401AA5);
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 560h]
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 5D0h]
			PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 58Ch]
			PUSH ECX
			CALL Call_Near
			ADD ESP, 0x0C
			PUSH DWORD PTR SS : [EBP + 8] // Mob que Ataca
			PUSH DWORD PTR SS : [EBP - 0x588] // Mob que Recebe Ataque
			PUSH EAX
			PUSH 1
			CALL HookImpl::GetDamageControl
			MOV DWORD PTR SS : [EBP - 0x58C], EAX
			PUSH 0x04640B6
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GetDamage2()
{
	static auto Call_Near = reinterpret_cast<void*>(0x401AA5);
	__asm
	{
		PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 0x50]
			PUSH ECX
			CALL Call_Near
			ADD ESP, 0x0C
			PUSH DWORD PTR SS : [EBP + 0x8] //Mob que Ataca
			PUSH DWORD PTR SS : [EBP + 0x0C] // Mob Atacado
			PUSH EAX // Dano Efetuado
			PUSH 2
			CALL HookImpl::GetDamageControl
			MOV DWORD PTR SS : [EBP - 0x50], EAX
			PUSH 0x4293A6
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GetSkillDamage()
{
	static auto Call_Near = reinterpret_cast<void*>(0x401A9B);
	static int id = 0, id1 = 0, id2 = 0;

	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x560]
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x5F4]
			PUSH EDX
			MOV EAX, DWORD PTR SS : [EBP - 0x58C]
			PUSH EAX
			CALL Call_Near
			ADD ESP, 0x0C
			PUSH DWORD PTR SS : [EBP + 0x8]
			PUSH DWORD PTR SS : [EBP - 0x588]
			PUSH EAX
			PUSH 3
			CALL HookImpl::GetDamageControl
			MOV DWORD PTR SS : [EBP - 0x58C], EAX
			PUSH 0x46471E
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_AfterEnterWorld()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x0C]
			CALL HookImpl::AfterEnterWorld

			CMP DWORD PTR DS : [0x8C76280], 0x0
			JNE LoopOriginal
			PUSH 0x4A6FDD
			RETN

		LoopOriginal :
		PUSH 0x4A6FE6
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_processSend()
{
	static const UINT32 dwContinue = 0x004211C3;

	__asm
	{
		MOV BYTE PTR SS : [EBP - 0Ch], AL
			PUSH DWORD PTR SS : [EBP + 0Ch]
			PUSH DWORD PTR SS : [EBP - 04h]
			PUSH DWORD PTR SS : [EBP + 08h]
			CALL HookImpl::SendPacket
			ADD ESP, 0Ch

			MOV DWORD PTR SS : [EBP + 08h], EAX

			MOV ECX, DWORD PTR SS : [EBP - 0Ch]
			//MOV DWORD PTR SS : [EBP - 08h], EAX

			JMP dwContinue
	}
}
__declspec(naked) void HookPatch::NKD_ProcessNPC_SapphireValue()
{
	__asm 
	{
		MOV ECX, 20
		PUSH 0x441512
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessNPC_SapphireValue2()
{
	__asm 
	{
		MOV EDX, 20
		PUSH 0x441527
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_MobKilled_WarTower()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x2C4] // PosY
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x2C0] // PosX
		PUSH ECX
		MOV EAX, DWORD PTR SS : [EBP + 0xC] // conn
		PUSH EAX
		PUSH DWORD PTR SS : [EBP + 0x8] // target
		CALL CWarTower::MobKilled
		MOV EAX, 0x4BEE40
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_GenerateMob_WarTower()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x30]
		IMUL EDX, EDX, 0x6BC
		MOV DWORD PTR DS : [EDX + 0x1FDF300] , 0x0


		MOV EDX, DWORD PTR SS : [EBP - 0x30] // tmob
		PUSH EDX
		MOV ECX, 0
		PUSH ECX // PosY
		MOV EAX, 0
		PUSH EAX // PosX
		PUSH DWORD PTR SS : [EBP + 0x8] // index
		CALL CWarTower::CGenerateMob
		MOV EAX, 0x45837A
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_GuildProcess_WarTower()
{
	__asm
	{
		MOV EDI, 0xAACD30
		PUSH EDI
		CALL CWarTower::GuildProcess
		MOV EAX, 0x4B68A1
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_ReplationRate()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x24B4]
		PUSH ECX
		CALL HookImpl::SetItemBonus2
		MOV EAX, 0x47C73D
		JMP EAX
		RETN
	}
}


__declspec(naked) void HookPatch::NKD_ProcessMinTimer_FixWarNoatun()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x14] , 0x0
		JNE lblNotWar
		PUSH 0x4B1779
		RETN

		lblNotWar :
		PUSH 0x4B1785
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_ChangeDoubleCritical()
{
	__asm
	{
		LEA EDX, DWORD PTR SS : [EBP - 0x574]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x4CC]
		ADD EAX, 0x1A
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP + 0x8]
		IMUL ECX, ECX, 0xC58
		ADD ECX, 0x752BF48
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		IMUL EDX, EDX, 0x06BC
		ADD EDX, 0x1FDECA0
		PUSH EDX
		CALL HookImpl::changeDoubleCritical
		MOV DWORD PTR SS : [EBP - 0x5CC] , EAX
		MOV EAX, 0x463FD7
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ReadMessage_CheckError()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		PUSH ECX
		CALL HookImpl::CheckPacket
		MOV EDX, 0x45CA5C
		JMP EDX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_RemoveParty_LastReqParty()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x2C]
		IMUL ECX, ECX, 0x6BC
		MOV EDX, DWORD PTR SS : [EBP - 0x20]
		MOV DWORD PTR DS : [ECX + 0x1FDF1D8] , EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x20]
		PUSH EAX
		MOV EDX, DWORD PTR SS : [EBP - 0x2C]
		PUSH EDX
		CALL HookImpl::LastReqParty
		PUSH 0x4C08AC
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_LastReqParty()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP + 0xFFFFB21C]
		PUSH ECX
		CALL HookImpl::LastReqParty
		MOV ECX, DWORD PTR SS : [EBP + 0xFFFFB220]
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP + 0xFFFFB220]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP + 0xFFFFB21C]
		PUSH EAX
		CALL SendReqParty
		ADD ESP, 0x0C
		MOV EAX, 0x4915F7
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_DiffrentMove()
{
	__asm
	{
		CALL Log
		ADD ESP, 0xC
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		PUSH EAX
		CALL HookImpl::ActionWarning
		PUSH 0x461325
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessDBMessage_CharacterLogin()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x104C] // Pacote
		LEA EAX, WORD PTR SS : [ECX + 0xE] // Y
		PUSH EAX
		LEA EDX, WORD PTR SS : [ECX + 0xC] // X
		PUSH EDX
		PUSH DWORD PTR SS : [EBP - 0xC] // ClientId
		CALL HookImpl::ProcessDBMessage_CharacterLogin
		TEST AL, AL
		JE lblContinueNormal
		PUSH 0x4A64F5
		RETN

		lblContinueNormal :
		MOV EDX, DWORD PTR SS : [EBP - 0xC]
			IMUL EDX, EDX, 0x6BC
			PUSH 0x4A64AA
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_ManaUpdate()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x588]
		IMUL ECX, ECX, 0x0C58
		MOV EDX, DWORD PTR SS : [EBP - 0x858]
		MOV DWORD PTR DS : [ECX + 0x752C438] , EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x588]
		PUSH EAX
		CALL SendScore
		ADD ESP, 0x4
		MOV EAX, 0x467F1F
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ReadMessage_Fix()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x0C]
		AND EDX, 0x0000FFFF
		MOV EAX, DWORD PTR SS : [EBP + 0x0C]
		MOV DWORD PTR DS : [EAX] , EDX
		CMP BYTE PTR SS : [EBP - 0x14] , 0x84
		JZ lblSet
		JMP lblContinue

		lblSet :
		MOV ECX, DWORD PTR SS : [EBP + 0x8]
			MOV DWORD PTR DS : [ECX] , 0x0
			JMP lblContinue

			lblContinue :
		PUSH 0x4208DD
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_GuildProcess_FixTowerSpawn()
{
	__asm
	{
		PUSH 0x0
		PUSH 0x0
		MOV EAX, DWORD PTR SS : [EBP - 0xC]
		ADD EAX, 0x17
		PUSH EAX
		CALL GenerateMob
		ADD ESP, 0xC
		MOV EAX, 0x4B54A1
		JMP EAX
		RETN
	}
}

__declspec(naked) void HookPatch::NKD_ReadMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HookImpl::HKD_ReadMessage
	}
}

int HookPatch::NKD_GetMaxCarry(STRUCT_ITEM* Carry, int Slot)
{
	return 1;
}

int HookPatch::NKD_GetEmptyUser()
{
	int conn = 0;

	for (int i = 1; i < MAX_USER; i++)
	{
		if (!pUser[i].Mode)
		{
			conn = i;
			break;
		}
	}

	*(DWORD*)0x8C76194 = conn;

	return conn;
}


void HookPatch::NKD_ProcessDBMessage(char* Msg)
{
	unsigned int ProcessDBMessage = 0x49F100;
	HookImpl::ProcessDBMessage(Msg);

	__asm
	{
		PUSH DWORD PTR SS : [Msg]
		CALL DWORD PTR DS : [ProcessDBMessage]
		ADD ESP, 0x4
	}
}

__declspec(naked) void HookPatch::NKD_AddMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HookImpl::HKD_AddMessage
	}
}


/*__declspec(naked) void HookPatch::NKD_MainWndProc_ReadMessageUser()
{
	__asm
	{
		LEA EAX, [EBP - 0x14]
		PUSH EAX
		LEA ECX, [EBP - 0x10]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		PUSH ECX
		CALL HookImpl::ReadMessage_
		MOV DWORD PTR SS : [EBP - 0x18] , EAX
		MOV EAX, 0x45C95C
		JMP EAX
		RETN
	}
}*/

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_OnNpcClick()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0xC24]
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::OnNpcClick
		TEST AL, AL // Retorna true, a função executou toda a função, false procura na tmsrv
		JNZ lblExit

		MOV EAX, DWORD PTR SS : [EBP - 0xC34]
		PUSH 0x469D92
		RETN

		lblExit :
		PUSH 0x4915F7
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_CloseUser()
{
	__asm
	{
		CMP DWORD PTR DS : [ECX + 0x752BAF0] , 0x16
		JNZ lblContinue

		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::CloseUser
		PUSH 0x4B827C
		RETN
		lblContinue :
		PUSH 0x4B82F5
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_SaveUser()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x8F0] , 0
		JE lblFunctionFail
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::SaveUser
		PUSH 0x4B9633
		RETN

		lblFunctionFail :
		PUSH 0x4B9606
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_ProcessClientMessage_AccountLogin()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0xC]
		CALL HookImpl::ProcessDBMessage_AccountLogin
		CMP DWORD PTR DS : [0x8C761A0] , 1
		JNZ lblContinueExec
		PUSH 0x4A2E56
		RETN

		lblContinueExec :
		PUSH 0x4A2F16
			RETN
	}
}
__declspec(naked) void HookPatch::NKD_FixJoinableItens()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
			MOVSX EAX, WORD PTR DS : [EDX]
			CMP EAX, 0x956
			JL lblNext
			CMP EAX, 0x973
			JG lblNext
			PUSH 0x408718
			RETN
		lblNext :
		PUSH DWORD PTR SS : [EBP + 0x8]
			CALL HookImpl::AddJoinableItens
			TEST AL, AL
			JE lblFail
			MOV EAX, 1
			PUSH 0x40874B
			RETN
		lblFail :
		PUSH 0x408749
			RETN
	}
}

__declspec(naked) void HookPatch::NKD_ProcessClientMessage_FixBuyItem()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0xFFFFB4D0]
		PUSH EAX
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HookImpl::FixBuyItem
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		IMUL EDX, EDX, 0x6BC
		MOV EAX, 0x48EE1E
		JMP EAX
		RETN
	}
}
__declspec(naked) void HookPatch::NKD_MobKilled_Event()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP + 0xC] // Killer
		PUSH DWORD PTR SS : [EBP + 0x8] // Killed
		PUSH DWORD PTR SS : [EBP - 0x230] // GenerateIndex
		CALL HookImpl::MobKilledEvent
		TEST AL, AL // Se for false, vai pra próxima comparação
		JE lblContinueExec
		MOV EAX, 0x4BD175
		JMP EAX

		lblContinueExec :
		CMP DWORD PTR SS : [EBP - 0x230] , 0x10E
			JL lblNext
			MOV EAX, 0x4BCF3E
			JMP EAX

			lblNext :
		MOV EAX, 0x4BCFF2
			JMP EAX
	}
}
__declspec(naked) void HookPatch::NKD_ProcessClientMessage()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x4] // MSG
		PUSH DWORD PTR SS : [EBP + 0x8] // USER
		CALL HookImpl::ProcessClientMessage
		TEST AL, AL
		JE lblAbortExec
		MOV ECX, DWORD PTR SS : [EBP + 0x8]
		IMUL ECX, ECX, 0xC58
		MOV EAX, 0x45E2F9
		JMP EAX

		lblAbortExec :
		MOV EAX, 0x4915F7
			JMP EAX
	}
}

__declspec(naked) void HookPatch::NKD_ExpControlInDead()
{
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
			IMUL EAX, EAX, 0x6BC
			MOV ECX, DWORD PTR DS : [EAX + 0x1FDECBC]
			MOV DWORD PTR SS : [EBP - 0x9C], 0
			SUB ECX, DWORD PTR SS : [EBP - 0x9C]
			MOV EDX, DWORD PTR SS : [EBP + 0x8]
			IMUL EDX, EDX, 0x6BC
			MOV DWORD PTR DS : [EDX + 0x1FDECBC], ECX
			PUSH 0x4BBE4D
			RETN
	}
}
 