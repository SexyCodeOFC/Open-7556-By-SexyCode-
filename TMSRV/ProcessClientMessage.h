#ifndef PROCESSCLIENTMESSAGE_H
#define PROCESSCLIENTMESSAGE_H

// Fix
void Fix_MSG_Action_RECV(MSG_STANDARD* pMsg, bool* pRetn);
void Fix_MSG_Action_SEND(char* NewMsg, MSG_STANDARD* OldMsg);
void Fix_MSG_Attack_RECV(MSG_STANDARD* pMsg, bool* pRetn);
void Fix_MSG_Attack_SEND(char* NewMsg, MSG_STANDARD* OldMsg);

// Exec
bool Exec_MSG_ComandClienter(const int32_t client, p334h* const packet);
bool Exec_MSG_MessageWhisper(int conn, char* pMsg);
bool Exec_MSG_GriffinMaster(int conn, char* pMsg);
bool Exec_MSG_Action(int conn, char* pMsg);
bool Exec_MSG_Attack(int conn, char* pMsg);
bool Exec_MSG_AccountLogin(int conn, char* pMsg);
void Exec_MSG_DropItem(int conn, char* pMsg);
void Exec_MSG_GetItem(int conn, char* pMsg);
bool Exec_MSG_UseItem(int conn, char* pMsg);
bool Exec_MSG_Quest(int conn, char* pMsg);
bool Exec_MSG_TradingItem(int conn, char* pMsg);
bool Exec_MSG_AcceptParty(int conn, char* pMsg);
bool Exec_MSG_Buy(int conn, char* pMsg);
bool Exec_MSG_UpdateItem(int conn, char* pMsg);
bool Exec_MSG_CombineItemAilyn(int conn, char* pMsg);
bool Exec_MSG_OpenLojinha(int conn, char* pMsg);
bool Exec_MSG_ClosedLojinha(int conn, char* pMsg);
bool Exec_MSG_ActionLojinha(int conn, char* pMsg);
bool onPaymentGold(int conn, char* pMsg);
//bool Exec_MSG_LimiteAccount(int conn, char* pMsg);
bool Exec_MSG_OdinFixRefinação(int32_t client, char* pMsg);
bool Exec_MSG_ComposiçãoPistaDeRunas(int32_t client, char* pMsg);
bool Exec_MSG_OdinFixArmaCele(int32_t client, char* pMsg); 
int GetChanceRefOdin(STRUCT_ITEM *Item);
#endif // !PROCESSCLIENTMESSAGE_H