#include "stdafx.h"
#include "HookImpl.h"
#include "Functions.h"
#include "ProcessClientMessage.h"

// Função que é executada quando um pacote é recebido do client
// Retornar false, para não processar o pacote
// Retorna true para a tmsrv processar o pacote
bool HookImpl::ProcessClientMessage(int32_t conn, char* pMsg)
{ 
	 
	bool rt = true; 
	MSG_STANDARD* std = (MSG_STANDARD*)pMsg;
	 
	switch (std->Type)
	{

	case 0x334:
		rt = Exec_MSG_MessageWhisper(conn, pMsg);
		break;
	case 0x373:
		rt = Exec_MSG_UseItem(conn, pMsg);
		break;
	case 0x28B:
		rt = Exec_MSG_Quest(conn, pMsg);
		break;
	case 0xAD9:
		rt = Exec_MSG_GriffinMaster(conn, pMsg);
		break;
	case 0x36C:
	case 0x366:
	case 0x368:
		rt = Exec_MSG_Action(conn, pMsg);
		break;
	case 0x39D:
	case 0x39E:
	case 0x367:
		rt = Exec_MSG_Attack(conn, pMsg);
		break;
	case 0x20D:
		rt = Exec_MSG_AccountLogin(conn, pMsg);
		break;
	/*case 0x213:
		rt = Exec_MSG_LimiteAccount(conn, pMsg);
		break;*/
	case 0x376:
		rt = Exec_MSG_TradingItem(conn, pMsg);
		break;
	case 0x3AB:
		rt = Exec_MSG_AcceptParty(conn, pMsg);
		break;
	case 0x379:
		rt = Exec_MSG_Buy(conn, pMsg);
		break;
	case 0x374:
		rt = Exec_MSG_UpdateItem(conn, pMsg);
		break;
	case 0x3B5:
		rt = Exec_MSG_CombineItemAilyn(conn, pMsg);
		break;  
	case 0x2E2:
		rt = Exec_MSG_OdinFixArmaCele(conn, pMsg);
		break;
	case 0x397:
		rt = Exec_MSG_OpenLojinha(conn, pMsg);
		break;
	case 0x384:
		rt = Exec_MSG_ClosedLojinha(conn, pMsg);
		break;
	case 0x398:
		rt = Exec_MSG_ActionLojinha(conn, pMsg);
		break;  
	case 0x2C3:
		rt = Exec_MSG_Alquimista_Real(conn, pMsg);
		break;
	}


	return rt;
}