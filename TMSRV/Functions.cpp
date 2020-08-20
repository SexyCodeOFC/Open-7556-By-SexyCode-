#include "stdafx.h"
#include "Functions.h"

bool Func::FileExist(const char* Name)
{
	if (FILE* file = fopen(Name, "r"))
	{
		fclose(file);
		return true;
	}
	return false;
}

char* Func::strFmt(const char* str, ...)
{
	static char buffer[512] = { 0, };
	va_list va;
	va_start(va, str);
	vsprintf_s(buffer, str, va);
	va_end(va);
	return buffer;
} 
bool Func::ClearAmountItem(uint16_t client, uint16_t item, uint16_t quant)
{
	auto mob = GetMobFromIndex(client);

	for (int a = 0; a < quant; a++)
	{
		int slot = Func::GetFirstSlot(client, SlotType::Inventory, item, 0);
		Func::AmountMinus(&mob->MOB.Carry[slot]);
		SendItem(client, (uint16_t)SlotType::Inventory, slot, &mob->MOB.Carry[slot]);
	}
	return true;
}

void Func::CloseWindows(int clientId)
{
	callCdecl(0x4015FF, void, int, int, int, int)(clientId, 0x7530, 0x3A7, 0);
}

CUser* Func::GetUserFromIndex(int conn)
{
	if (conn < 0 || conn > MAX_USER)
		return nullptr;

	return &pUser[conn];
}

int Func::ReturnAmount(STRUCT_ITEM* item)
{
	int totalAmount = 0;
	bool hasAmount = false;

	for (int a = 0; a < 3; a++)
	{
		if (item->stEffect[a].cEffect == EF_AMOUNT)
		{
			totalAmount += item->stEffect[a].cValue;
			hasAmount = true;
		}
	}

	if (!hasAmount)
	{
		if (item->stEffect[0].cEffect != EF_AMOUNT &&
			item->stEffect[1].cEffect != EF_AMOUNT &&
			item->stEffect[2].cEffect != EF_AMOUNT)
			totalAmount++;
	}

	return totalAmount;
}
int32_t Func::CheckGetLevel(int32_t client)
{
	__asm
	{
		MOV ECX, client
		IMUL ECX, ECX, 0x6BC
		ADD ECX, 0x1FDECA0
		CALL _CheckGetLevel
	}
}
void Func::GetCurrentScore(int32_t client)
{
	__asm
	{
		PUSH client
		MOV ECX, client
		IMUL ECX, ECX, 0x6BC
		ADD ECX, 0x1FDECA0
		CALL _GetCurrentScore
	}
}

void Func::AmountMinus(STRUCT_ITEM* item)
{
	auto amount = BASE_GetItemAmount(item);

	if (amount > 0)
	{
		BASE_SetItemAmount(item, amount - 1);
		return;
	}

	BASE_ClearItem(item);
}

void Func::SendDBPacket(char* pMsg, int32_t len)
{
	__asm
	{
		PUSH len
		PUSH pMsg
		MOV ECX, 0xBDEA50
		CALL CPSock_SendOneMessage
	}
}

void Func::SendPacket(int32_t client, uint8_t* pMsg, int32_t len)
{
	__asm
	{
		PUSH len
		PUSH pMsg
		MOV ECX, client
		IMUL ECX, ECX, 0xC58
		ADD ECX, 0x752BAF8
		CALL CPSock_SendOneMessage
	}
}
void Func::SendAddPacket(int32_t client, uint8_t* pMsg, int32_t len)
{
	__asm
	{
		PUSH len
		PUSH pMsg
		MOV ECX, client
		IMUL ECX, ECX, 0xC58
		ADD ECX, 0x752BAF8
		CALL CPSock_AddMessage
	}
}

bool Func::LoadAccount(int32_t client, const char* accountName)
{
	FILE* fs = nullptr;
	fopen_s(&fs, strFmt("../../DBSRV/run/DataBase/userdata/%s.bin", accountName), "rb");
	if (fs == nullptr)
	{
		memset(&pUserData[client], 0, sizeof(UserData));
		fopen_s(&fs, strFmt("../../DBSRV/run/DataBase/userdata/%s.bin", accountName), "wb");
		if (fs == nullptr)
			return false;

		fwrite(&pUserData[client], 1, sizeof(UserData) - sizeof(UserData::_Ingame), fs);
		fclose(fs);
		return true;
	}
	fread(&pUserData[client], 1, sizeof(UserData) - sizeof(UserData::_Ingame), fs);
	fclose(fs);
	return true;
}

bool Func::SaveAccount(int32_t client, const char* accountName)
{
	UserData temporary; 
	memcpy(&temporary, &pUserData[client], sizeof(UserData));

	FILE* fs = nullptr;
	fopen_s(&fs, strFmt("../../DBSRV/run/DataBase/userdata/%s.bin", accountName), "wb");
	if (fs == nullptr)
		return false;

	fwrite(&temporary, 1, sizeof(UserData) - sizeof(UserData::_Ingame), fs);
	fclose(fs);
	return true;
}

int32_t Func::GetPlayerClass(int32_t client)
{
	__asm
	{
		MOV ECX, client
		IMUL ECX, ECX, 0x6BC
		ADD ECX, 0x1FDECA0
		CALL _GetClass
	}
}

void Func::CMobInitialize(int Index)
{
	__asm
	{
		MOV ECX, Index
		IMUL ECX, ECX, 0x6BC
		ADD ECX, 0x1FDECA0
		CALL _Initialize
	}
}

int Func::GetUserFromSocket(int Sock)
{
	if (Sock == 0)
		return 0;

	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].cSock.Sock == (unsigned)Sock)
			return i;
	}

	return 0;
}

bool Func::LoadGuildInfo(int conn)
{
	if (conn < 0 || conn > MAX_USER)
		return false;

	if (pMob[conn].MOB.Equip[12].sIndex == 0)
		return false;

	std::ifstream inputFile(strFmt("../../DBSRV/run/guild/%d.bin", pMob[conn].MOB.Guild), std::ifstream::binary | std::ifstream::in);

	if (!inputFile.is_open())
	{
		std::ofstream outputFile(strFmt("../../DBSRV/run/guild/%d.bin", pMob[conn].MOB.Guild), std::ofstream::binary | std::ofstream::out);

		if (!outputFile.is_open())
			return false;


		outputFile.write(reinterpret_cast<char*>(&GuildInfo[conn]), sizeof(STRUCT_GUILD));
		outputFile.close();
		return true;
	}
	inputFile.read(reinterpret_cast<char*>(&GuildInfo[conn]), sizeof(STRUCT_GUILD));
	inputFile.close();
	return true;
}

void Func::SendGuildInfo(int conn)
{
	if (conn > 0 && conn < MAX_USER)
	{
		MSG_SendGuildInfo p;
		p.ID = conn;
		p.Type = 0x666;
		p.Size = sizeof(MSG_SendGuildInfo);
		memcpy(&p.GuildInfo, &GuildInfo[conn], sizeof(STRUCT_GUILD));
		Func::SendPacket(conn, (uint8_t*)&p, sizeof(MSG_SendGuildInfo));
	}
}

uint8_t Func::ReadMacList(char* macAddress)
{
	FILE* arq = NULL;
	fopen_s(&arq, "../../DBSRV/run/DataBase/MacList.txt", "r");

	if (!arq)
	{
		MessageBoxA(0, "Arquivo não encontrado", "MacList.txt", 0);
		ExitProcess(1);
	}

	char line[100];
	memset(&line, 0, 100);

	char mac[25];
	memset(&mac, 0, 25);

	while ((fscanf(arq, "%[^\n]", line)) != EOF)
	{
		fgetc(arq);
		sscanf(line, "%s", &mac);

		if (!strcmp(mac, macAddress))
		{
			fclose(arq);
			return 1;
		}
	}

	fclose(arq);
	return -1;
}

void Func::MacBan(uint16_t conn)
{
	if (conn <= NULL || conn >= MAX_USER)
		return;

	FILE* Arquivo;

	fopen_s(&Arquivo, "../../DBSRV/run/DataBase/MacList.txt", "a+");

	if (!Arquivo)
	{
		MessageBoxA(0, "Arquivo não encontrado", "MacAddress.txt", 0);
		ExitProcess(1);
		false;
	}

	char update[20];
	memset(update, 0, 20);
	sprintf(update, "%s \n", pUserData[conn].Ingame.MacAddress);
	fputs(update, Arquivo);
	fclose(Arquivo);

	CloseUser(conn);
	return;
}

void Func::SendChatColor(const uint16_t conn, char* Msg, int Color, const uint16_t Type)
{
	if (conn <= NULL || conn >= MAX_USER)
		return;

	MSG_SendChatColor p;
	p.Size = sizeof(MSG_SendChatColor);
	p.Type = 0xD1E;
	p.ID = conn;
	strcpy_s(p.Message, Msg);
	p.Color = Color;

	if (Type == 1)
		Func::SendPacket(conn, (uint8_t*)&p, p.Size);

	if (Type == 2)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[conn].Mode != USER_PLAY) 
				continue;

			Func::SendPacket(i, (uint8_t*)&p, p.Size);
		}
	}
}

bool Func::ReadMileageListItem()
{
	FILE* arq = NULL;
	fopen_s(&arq, "./DataBase/Mileage.txt", "r");
	memset(&pMileageStore, 0x0, sizeof(pMileageStore) / sizeof(STRUCT_MILEAGESTORE));

	if (!arq)
	{
		MessageBoxA(0, "Arquivo /DataBase/Mileage.txt não encontrado", "Erro", 0);
		ExitProcess(1);
		return false;
	}

	char line[100];
	memset(&line, 0, 100);
	memset(&g_MileageCountLine, 0, sizeof(g_MileageCountLine));

	while ((fscanf(arq, "%[^\n]", line)) != EOF)
	{
		if (*line == '\n' || *line == '#')
			continue;

		if (g_MileageCountLine < 500)
		{
			fgetc(arq);

			sscanf(line, "%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&pMileageStore[g_MileageCountLine].Item.sIndex,
				&pMileageStore[g_MileageCountLine].Item.stEffect[0].cEffect,
				&pMileageStore[g_MileageCountLine].Item.stEffect[0].cValue,
				&pMileageStore[g_MileageCountLine].Item.stEffect[1].cEffect,
				&pMileageStore[g_MileageCountLine].Item.stEffect[1].cValue,
				&pMileageStore[g_MileageCountLine].Item.stEffect[2].cEffect,
				&pMileageStore[g_MileageCountLine].Item.stEffect[2].cValue,
				&pMileageStore[g_MileageCountLine].Price,
				&pMileageStore[g_MileageCountLine].Store
			);
		}
		g_MileageCountLine++;
	}
	fclose(arq);
	return true;

}

const std::vector<uint16_t> Func::PlayerInAreaMac(const int32_t client, const STRUCT_POSITION minPos, const STRUCT_POSITION maxPos, char* mac)
{
	auto mobsInArea = std::vector<uint16_t>();

	for (auto i = 0; i < MAX_USER; i++)
	{
		auto userData2 = &pUserData[i];
		CUser* cuser = (CUser*)Func::GetUserFromIndex(i);

		if (cuser->Mode == 22)
		{
			if (!strcmp(userData2->Ingame.MacAddress, mac))
			{ 

				if (pMob[i].TargetX >= minPos.X && pMob[i].TargetX <= maxPos.X && pMob[i].TargetY >= minPos.Y && pMob[i].TargetY <= maxPos.Y)
					mobsInArea.push_back(static_cast<uint16_t>(i));
			}
		}
	}

	return mobsInArea;
}

const std::vector<uint16_t> Func::CheckMacUserInArea(const STRUCT_POSITION minPos, const STRUCT_POSITION maxPos, char* mac)
{
	auto UserInArea = std::vector<uint16_t>();

	for (auto i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY)
		{
			if (!strcmp(pUserData[i].Ingame.MacAddress, mac))
			{
				if (pMob[i].TargetX >= minPos.X && pMob[i].TargetX <= maxPos.X && pMob[i].TargetY >= minPos.Y && pMob[i].TargetY <= maxPos.Y)
					UserInArea.push_back(static_cast<uint16_t>(i));
			}
		}
	}

	return UserInArea;
}
 

INT32 Func::getIndexStruct(UINT32 pBase, UINT32 pStruct, size_t sizeStruct)
{
	if (!pBase || !pStruct || !sizeStruct)
		return -1;

	return ((pStruct - pBase) / sizeStruct);
}

bool Func::File_exists(const char *filename)
{
	FILE *arquivo;
	arquivo = fopen(filename, "rb");

	if (arquivo)
	{
		fclose(arquivo);
		return true;
	}

	return false;
}
bool Func::WriteData(uint32_t connId, char *folderName)
{
	FILE* fs = NULL;

	//CMob *pMob = GetMobFromIndex(connId);
	CUser *pUser = Func::GetUserFromIndex(connId);
	auto userData = &pUserData[connId];

	char Diretorio[120];
	sprintf(Diretorio, "C:/%s/%s.rnk", folderName, pMob[connId].MOB.MobName);


	if (File_exists(Diretorio))
	{
		remove(Diretorio);
	}

	fs = fopen(Diretorio, "w+");

	if (!fs)
		return false;

	fprintf(fs, "%s,%s,%d,%d,%d,%d,%d",
		pMob[connId].MOB.MobName, //Nome Char
		pMob[connId].MOB.MobName, //Nome Char
		pMob[connId].MOB.Class,//Classe
		Func::GetPlayerClass(connId), //Evolução
		pMob[connId].MOB.Guild, //Guild Char
		pMob[connId].MOB.BaseScore.Level,// Level
		pMob[connId].MOB.Clan);//reino
		 

	fclose(fs);

	return true;
}
void Func::NpcTab(int mob, MSG_CreateMob *sm)
{
	if (mob < 0 || mob > MAX_USER)
		return; 

	auto curMob = GetMobFromIndex(mob);
	auto packetMob = GetMobFromIndex(sm->ID);
	auto user = Func::GetUserFromIndex(sm->ID);
	 

	if (strcmp((char*)sm->MobName, "Aki") == 0) sprintf(sm->Tab, "Vendedor para iniciantes");
	else if (strcmp((char*)sm->MobName, "Kibita") == 0) sprintf(sm->Tab, "Guardian de Armia");
	 

}

const std::vector<uint16_t> Func::getPlayerLoja(const int client, char* mac)
{
	auto valor = std::vector<uint16_t>();

	for (int i = 0; i < 1000; i++)
	{
		auto userData2 = &pUserData[i];
		CUser* cuser = (CUser*)Func::GetUserFromIndex(i);

		if (cuser->Mode == 22)
		{
			if (!strcmp(userData2->Ingame.MacAddress, mac))
			{
				if (userData2->Ingame.autoStore)
					valor.push_back(static_cast<uint16_t>(i));
			}
		}
	}
	return valor;
}

void Func::SendPacket2(int32_t client, void* const pMsg, int32_t len)
{
	int32_t retnValue = 0;

	__asm
	{
		PUSH len
		PUSH pMsg
		MOV ECX, client
		IMUL ECX, ECX, 0xC58
		ADD ECX, 0x752BAF8

		MOV EAX, 0x40132A
		CALL EAX

		MOV retnValue, EAX
	}
}
void Func::SendSenhaGrupo(int clientId)
{
	auto userData = &pUserData[clientId];
	struct
	{
		MSG_STANDARD Header;
		char senha[12];
		bool ativo;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Header.Type = 0x70A;
	Packet.Header.ID = clientId;
	Packet.Header.Size = sizeof(Packet);
	Packet.ativo = userData->Ingame.GrupoAceitarSolicitação;
	sprintf_s(Packet.senha, 12, userData->Ingame.GrupoSenha);

	Func::SendPacket2(clientId, (BYTE*)&Packet, sizeof(Packet));
}
void Func::UpdateStatus(int clientId)
{
	auto Mob = GetMobFromIndex(clientId);

	callCdecl(0x4040F0, int, STRUCT_MOB*)(&Mob->MOB);
	__asm
	{
		PUSH clientId
		MOV ECX, clientId
		IMUL ECX, ECX, 0x6BC
		ADD ECX, 0x1FDECA0

		MOV EAX, 0x4016EF
		CALL EAX
	}

	callCdecl(0x401348, void, int)(clientId);
	callCdecl(0x4018B1, void, int, int)(clientId, 0);
	callCdecl(0x4018A7, void, int, int)(clientId, 0);
	callCdecl(0x449EE0, void, int)(clientId);
}

void Func::SendDonateUpdate(int clientId)
{

	auto userData = &pUserData[clientId];

	pDNTh p; 
	p.Header.Size = sizeof(pDNTh);
	p.Header.Type = 0xDDF;
	p.Header.ID = clientId;

	//p.donate = pUserData[clientId].AccountInfo.Cash;

	p.tgold = pUserData[clientId].AccountInfo.sTicketGold;

	//p.tprata = pUserData[clientId].AccountInfo.sTicketPrata;

	SendPacket2(clientId, &p, sizeof(p3BBh));

}
 
void Func::SendItem2(int clientId, STRUCT_ITEM* item)
{
	callCdecl(0x0401401, int, int, STRUCT_ITEM*)(clientId, item);
} 

int Func::ReturnSlotEmpty(int clientId, SlotType Type)
{
	int Return = -1;

	switch (Type)
	{
	case SlotType::Equipment:
		break;

	case SlotType::Inventory:
	{
		auto Mob = GetMobFromIndex(clientId);

		int Loop = 30;
		auto Andarilho = Mob->MOB.Carry[60].sIndex;
		auto Andarilho_2 = Mob->MOB.Carry[61].sIndex;

		if (Andarilho == 3467)
			Loop += 15;

		if (Andarilho_2 == 3467)
			Loop += 15;

		for (int i = 0; i < Loop; i++)
		{
			if (Mob->MOB.Carry[i].sIndex == 0)
				return i;
		}
	}break;

	case SlotType::Storage:
	{
		auto User =  Func::GetUserFromIndex(clientId);

		for (int i = 0; i < MAX_CARGO; i++)
		{
			if (User->Cargo[i].sIndex == 0)
				return i;
		}

	}break;

	}

	return Return;
}
 
bool Func::StartCoinsNPC()
{
	FILE* arq = NULL;
	fopen_s(&arq, "./DataBase/Moedas.txt", "r");
	memset(&coins, 0x0, sizeof(coins) / sizeof(Moeda));

	if (!arq)
	{
		MessageBoxA(0, "Arquivo /DataBase/Moedas.txt não encontrado", "Erro", 0);
		ExitProcess(1);
		return false;
	}

	char line[100];
	memset(&line, 0, 100);
	memset(&NumberMoedas, 0, sizeof(NumberMoedas));// ta vendo o ponteiro serve pra isso ele puxa o valor dentro do txt e armazena ai a função puxa o valor ai n precisa ficar botando id dentro da src

	while ((fscanf(arq, "%[^\n]", line)) != EOF)
	{
		if (*line == '\n' || *line == '#')
			continue;

		if (NumberMoedas < 500)
		{
			fgetc(arq);

			sscanf(line, "%d,%d,%d",
				&coins[NumberMoedas].item,// id 
				&coins[NumberMoedas].preço, // valor
				&coins[NumberMoedas].quantidades // quantidades que podem ser vendidas
			);
		}
		NumberMoedas++;
	}
	fclose(arq);
	return true;
}


int32_t Func::GetFirstSlot(int32_t client, SlotType slot, uint16_t itemId, char* Msg)
{
	 
	if (slot == SlotType::Inventory)
	{
		auto mob = GetMobFromIndex(client);

		int Loop = 30;
		auto Andarilho = pMob[client].MOB.Carry[60].sIndex;
		auto Andarilho_2 = pMob[client].MOB.Carry[61].sIndex;
		 
		if (Andarilho == 3467)
			Loop += 15;

		if (Andarilho_2 == 3467)
			Loop += 15;

		for (int i = 0; i < Loop; i++)
		{
			if (pMob[client].MOB.Carry[i].sIndex == itemId)
				return i;
		}
	}
	else if (slot == SlotType::Equipment)
	{
		auto mob = GetMobFromIndex(client);

		for (int i = 0; i < MAX_EQUIP; i++)
		{
			if (pMob[client].MOB.Equip[i].sIndex == itemId)
				return i;
		}
	}
	else if (slot == SlotType::Storage)
	{
		auto user = GetUserFromIndex(client);
		if (user)
		{
			for (int i = 0; i < MAX_CARGO; i++)
			{
				if (pUser[client].Cargo[i].sIndex == itemId)
					return i;
			}
		}
	}
	return -1;
}


int Func::ReturnItemSlot(int clientId, SlotType slot, int itemId)
{
	auto Mob = GetMobFromIndex(clientId);
	auto User = GetUserFromIndex(clientId);


	if (slot == SlotType::Inventory)
	{
		int Loop = 30;
		auto Andarilho = Mob->MOB.Carry[60].sIndex;
		auto Andarilho_2 = Mob->MOB.Carry[61].sIndex;

		if (Andarilho == 3467)
			Loop += 15;

		if (Andarilho_2 == 3467)
			Loop += 15;

		for (int i = 0; i < Loop; i++)
		{
			if (Mob->MOB.Carry[i].sIndex == itemId)
				return i;
		}
	}
	else if (slot == SlotType::Equipment)
	{
		for (int i = 0; i < MAX_EQUIP; i++)
		{
			if (Mob->MOB.Equip[i].sIndex == itemId)
				return i;
		}
	}
	else if (slot == SlotType::Storage)
	{
		for (int i = 0; i < MAX_CARGO; i++)
		{
			if (pUser[clientId].Cargo[i].sIndex == itemId)
				return i;
		}
	}
	return -1;
}

int Func::GetUserInAreaMac(int notUsage, int x1, int y1, int x2, int y2)
{
	int userCount = 0;

	for (int conn = 1; conn < MAX_USER; conn++)
	{
		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == 0)
			continue;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (i == conn) continue;

			if (pMob[i].Mode == 0)
				continue;

			if (pMob[conn].TargetX >= x1 && pMob[conn].TargetX <= x2 && pMob[conn].TargetY >= y1 && pMob[conn].TargetY <= y2)
			{
				if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
				{
					if (pUser[conn].Mac[0] == pUser[i].Mac[0])
					{
						if (pUser[conn].Mac[1] == pUser[i].Mac[1])
						{
							if (pUser[conn].Mac[2] == pUser[i].Mac[2])
							{
								if (pUser[conn].Mac[3] == pUser[i].Mac[3])
								{
									 
									//SendClientMessage(i, "Somente 1 conta por computador.");									 
									userCount++;
									continue;
								}
							}
						}

					}

				}
			}
		}
	}
	return userCount;
}
STRUCT_GUILD* Func::GetGuild(int guildIndex)
{
	static auto* g_Control = reinterpret_cast<STRUCT_GUILD*>(0x88B5EE8);

	return &g_Control[guildIndex];
}
void Func::UpdateItemInventory(int clientId, int slot)
{
	auto Mob = GetMobFromIndex(clientId);
	callCdecl(0x401960, void, int, int, int, STRUCT_ITEM*)(clientId, (int)SlotType::Inventory, slot, &Mob->MOB.Carry[slot]);
}
void Func::ClearItemInventory(int clientId, int slot)
{
	auto Mob = GetMobFromIndex(clientId);
	callCdecl(0x40D420, void, STRUCT_ITEM*)(&Mob->MOB.Carry[slot]);
	UpdateItemInventory(clientId, slot);
}

STRUCT_ITEMLIST* Func::GetItemListItem(uint16_t itemId)
{
	static auto *itemlist = reinterpret_cast<STRUCT_ITEMLIST*>(0x9CCC40);

	if (itemId > MAX_ITEMLIST)
		return nullptr;

	return &itemlist[itemId];
}

int Func::GetArmorType(short ItemID)
{
	int SetType = 0;
	int Pos = pItem(ItemID)->nPos;
	switch (Pos)
	{
	case ARMA_TYPE1:
	case ARMA_TYPE2:
		SetType = 1;
		break;
	case ELMO_TYPE:
	case PEITO_TYPE:
	case BOTA_TYPE:
	case CALCA_TYPE:
		SetType = 2;
		break;
	case LUVA_TYPE:
		SetType = 3;
		break;
	default:
		SetType = 0;
		break;
	}
	return SetType;
}



bool Func::CheckArchItem(int id)
{
	bool retorno = false;
	///SET'S
	if (id >= 1221 && id <= 1224) retorno = true;
	else if (id >= 1356 && id <= 1359) retorno = true;
	else if (id >= 1506 && id <= 1509) retorno = true;
	else if (id >= 1656 && id <= 1659) retorno = true;
	///ARMAS ARCH
	else if (id == 811 || id == 826 || id == 841) retorno = true;
	else if (id == 856 || id == 871 || id == 886) retorno = true;
	else if (id == 871 || id == 886 || id == 903 || id == 904) retorno = true;
	else if (id == 912 || id == 937 || id == 2379 || id == 2380) retorno = true;
	///ARMAS ARCH ANCT
	else if ((id >= 2491 && id <= 2494) || (id >= 2551 && id <= 2554)) retorno = true;
	else if ((id >= 2611 && id <= 2614) || (id >= 2671 && id <= 2674)) retorno = true;
	else if ((id >= 2791 && id <= 2794) || (id >= 2859 && id <= 2866)) retorno = true;
	else if ((id >= 2895 && id <= 2898) || (id >= 2935 && id <= 2938)) retorno = true;
	else if (id >= 2731 && id <= 2734) retorno = true;
	return retorno;
}


int Func::PossivelRefinar(STRUCT_ITEM *item)
{

	int ret = false;
	for (int i = 0; i < 3; i++)
	{
		if (item->EF1 == EF_SANC || item->EF2 == EF_SANC || item->EF3 == EF_SANC)
		{
			ret = true;
			break;
		}
		else
		{
			if (item->EF1 >= EF_STARTCOLOR && item->EF1 <= EF_STOPCOLOR || item->EF2 >= EF_STARTCOLOR && item->EF2 <= EF_STOPCOLOR || item->EF3 >= EF_STARTCOLOR && item->EF3 <= EF_STOPCOLOR)
			{
				ret = true;
				break;
			}
		}
	}
	return ret;
}
bool Func::CheckItemCelestial(uint16_t ItemId)
{
	int ItensCelestial[] = {
		1665, 1666, 1667, 1668,//Urânia
		1230, 1231, 1232, 1233,//Melpômene
		1365, 1366, 1367, 1368,//Potâmides
		1515, 1516, 1517, 1518,//Dríade
		1713,//Svalin
		3605, 3606, 3607, 3608,//Machado_Gaoth(Anct)
		3785, 3786, 3787, 3788,//Martelo_Kaumodaki(Anct)
		3665, 3666, 3667, 3668,//Gae_Bulg(Anct)
		3625, 3626, 3627, 3628,//Eithna(Anct)
		3729, 3730, 3731, 3732,//Cetro_Rithil(Anct)
		3705, 3706, 3707, 3708,//Kenten(Anct)
		3645, 3646, 3647, 3648,//Lupercus(Anct)
		3685, 3686, 3687, 3688,//Tyrfing(Anct)
		3733, 3734, 3735, 3736,//Dordje(Anct)
		3765, 3766, 3767, 3768//Hrotti(Anct)
	};

	size_t szItensCelestial = ((sizeof ItensCelestial) / (sizeof(int)));
	for (size_t i = 0; i <= szItensCelestial; i++)
		if (ItemId == ItensCelestial[i])
			return true;



	return false;
}


void Func::DoRemoveHide(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 28)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		Func::GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}


int Func::GetAttackMiss(int conn, int a_iTarget)
{
	int Min = pMob[a_iTarget].MOB.CurrentScore.Dex;
	int Max = pMob[conn].MOB.CurrentScore.Dex;

	int Res = 1;
	int Rsv = 75;

	int EvE = pMob[conn].MOB.Rsv;

	if (EvE & 0x20)		Max += 100;

	if (EvE & 0x40)		Max += 100;

	if (EvE & 0x80)		Max += 50;

	if (EvE & 0x200)	Max += 50;

	if (Min > Max)
	{
		Res = (Min - Max) / 100;

		Res *= 3; //3

		Res = Res > Rsv ? Rsv : Res;
	}

	if (Max > Min)
	{
		Res = (Max - Min) / 100;

		if (Res > 10)	Res = 10;

	}

	return Res;
}



void Func::UpdateItemEquip(int clientId, int slot)
{ 
	callCdecl(0x401960, void, int, int, int, STRUCT_ITEM*)(clientId, (int)SlotType::Equipment, slot, &pMob[clientId].MOB.Equip[slot]);
}
void Func::ClearItemEquip(int clientId, int slot)
{ 
	callCdecl(0x40D420, void, STRUCT_ITEM*)(&pMob[clientId].MOB.Equip[slot]);
	UpdateItemEquip(clientId, slot);
}

int Func::GetDistance(int x1, int y1, int x2, int y2)
{
	int valor1 = x1 >= x2 ? x1 - x2 : x2 - x1;
	int valor2 = y1 >= y2 ? y1 - y2 : y2 - y1;

	int result = valor1 >= valor2 ? valor1 - valor2 : valor2 - valor1;
	return result;
}


int Func::GetMatchCombineOdin(STRUCT_ITEM *Item)
{
	for (int i = 0; i < 8; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[7].sIndex < 0 || Item[7].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex == g_pItemList[Item[1].sIndex].Extra && BASE_GetItemSanc(&Item[0]) >= 9 && BASE_GetItemSanc(&Item[1]) == REF_15
		&& (Item[2].sIndex == 542 || Item[2].sIndex == 772) && Item[3].sIndex == 5334 && Item[4].sIndex == 5335 && Item[5].sIndex == 5336 && Item[6].sIndex == 5337)
		return 1;//Item celestial

	else if ((Item[0].sIndex == 413 && BASE_GetItemAmount(&Item[0]) >= 10 && Item[1].sIndex == 413 && BASE_GetItemAmount(&Item[1]) >= 10 || Item[0].sIndex == 4043 && Item[1].sIndex == 4043)
		&& BASE_GetItemSanc(&Item[2]) > REF_10 && BASE_GetItemSanc(&Item[2]) <= REF_15 && (Item[3].sIndex >= 5334 && Item[3].sIndex <= 5337 || Item[3].sIndex == 3338) && (Item[4].sIndex >= 5334 && Item[4].sIndex <= 5337 || Item[4].sIndex == 3338)
		&& (Item[5].sIndex >= 5334 && Item[5].sIndex <= 5337 || Item[5].sIndex == 3338) && (Item[6].sIndex >= 5334 && Item[6].sIndex <= 5337 || Item[6].sIndex == 3338) && (g_pItemList[Item[2].sIndex].nPos == 2 || g_pItemList[Item[2].sIndex].nPos == 4 || g_pItemList[Item[2].sIndex].nPos == 8 || g_pItemList[Item[2].sIndex].nPos == 16 || g_pItemList[Item[2].sIndex].nPos == 32 || g_pItemList[Item[2].sIndex].nPos == 64 || g_pItemList[Item[2].sIndex].nPos == 192 || g_pItemList[Item[2].sIndex].nPos == 128))
		return 2;//Ref+12+

	else if (Item[0].sIndex == 413 && Item[1].sIndex == 413 && Item[2].sIndex == 413 && Item[3].sIndex == 413 && Item[4].sIndex == 413 && Item[5].sIndex == 413 && Item[6].sIndex == 413)
		return 3;//Pista de runas

	else if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 5135 && Item[3].sIndex == 5113 && Item[4].sIndex == 5129 && Item[5].sIndex == 5112 && Item[6].sIndex == 5110)
		return 4;//Level40 Celestial

	else if (Item[0].sIndex == 5125 && Item[1].sIndex == 5115 && Item[2].sIndex == 5111 && Item[3].sIndex == 5112 && Item[4].sIndex == 5120 && Item[5].sIndex == 5128 && Item[6].sIndex == 5119)
		return 5;//Pedra da fúria

	else if (Item[0].sIndex == 5126 && Item[1].sIndex == 5127 && Item[2].sIndex == 5121 && Item[3].sIndex == 5114 && Item[4].sIndex == 5125 && Item[5].sIndex == 5111 && Item[6].sIndex == 5118)
		return 6;//Secreta da Agua

	else if (Item[0].sIndex == 5131 && Item[1].sIndex == 5113 && Item[2].sIndex == 5115 && Item[3].sIndex == 5116 && Item[4].sIndex == 5125 && Item[5].sIndex == 5112 && Item[6].sIndex == 5114)
		return 7;//Secreta da Terra

	else if (Item[0].sIndex == 5110 && Item[1].sIndex == 5124 && Item[2].sIndex == 5117 && Item[3].sIndex == 5129 && Item[4].sIndex == 5114 && Item[5].sIndex == 5125 && Item[6].sIndex == 5128)
		return 8;//Secreta do Sol

	else if (Item[0].sIndex == 5122 && Item[1].sIndex == 5119 && Item[2].sIndex == 5132 && Item[3].sIndex == 5120 && Item[4].sIndex == 5130 && Item[5].sIndex == 5133 && Item[6].sIndex == 5123)
		return 9;//Secreta do Vento

	else if (Item[0].sIndex == 421 && Item[1].sIndex == 422 && Item[2].sIndex == 423 && Item[3].sIndex == 424 && Item[4].sIndex == 425 && Item[5].sIndex == 426 && Item[6].sIndex == 427)
		return 10;//Semente de cristal

	else if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 5135 && Item[3].sIndex == 413 && Item[4].sIndex == 413 && Item[5].sIndex == 413 && Item[6].sIndex == 413)
		return 11;//Capa

	return 0;
}



int Func::BASE_GetItemSanc(STRUCT_ITEM *item)
{
	if (item->sIndex >= 2330 && item->sIndex < 2390)
		return FALSE;

	unsigned char sanc = 0;

	if (item->stEffect[0].cEffect >= 116 && item->stEffect[0].cEffect <= 125)
		sanc = item->stEffect[0].cValue;

	else if (item->stEffect[1].cEffect >= 116 && item->stEffect[1].cEffect <= 125)
		sanc = item->stEffect[1].cValue;

	else if (item->stEffect[2].cEffect >= 116 && item->stEffect[2].cEffect <= 125)
		sanc = item->stEffect[2].cValue;

	else if (item->stEffect[0].cEffect == EF_SANC || item->stEffect[1].cEffect == EF_SANC || item->stEffect[2].cEffect == EF_SANC)
	{
		if (item->stEffect[0].cEffect == EF_SANC)
			sanc = item->stEffect[0].cValue;
		else if (item->stEffect[1].cEffect == EF_SANC)
			sanc = item->stEffect[1].cValue;
		else
			sanc = item->stEffect[2].cValue;
	}

	int isanc = sanc;

	if (isanc == 9)
		isanc = 9;
	else if (isanc >= 230 && isanc <= 233)
		isanc = REF_10;
	else if (isanc >= 234 && isanc <= 237)
		isanc = REF_11;
	else if (isanc >= 238 && isanc <= 241)
		isanc = REF_12;
	else if (isanc >= 242 && isanc <= 245)
		isanc = REF_13;
	else if (isanc >= 246 && isanc <= 249)
		isanc = REF_14;
	else if (isanc >= 250 && isanc <= 253)
		isanc = REF_15;
	else
		isanc = isanc % 10;

	return isanc;
}

int Func::BASE_GetItemGem(STRUCT_ITEM *item)
{
	if (item->sIndex >= 2330 && item->sIndex < 2390)
		return FALSE;

	unsigned char sanc = 0;

	if (item->stEffect[0].cEffect >= 116 && item->stEffect[0].cEffect <= 125)
		sanc = item->stEffect[0].cValue;

	else if (item->stEffect[1].cEffect >= 116 && item->stEffect[1].cEffect <= 125)
		sanc = item->stEffect[1].cValue;

	else if (item->stEffect[2].cEffect >= 116 && item->stEffect[2].cEffect <= 125)
		sanc = item->stEffect[2].cValue;

	else if (item->stEffect[0].cEffect == EF_SANC || item->stEffect[1].cEffect == EF_SANC || item->stEffect[2].cEffect == EF_SANC)
	{
		if (item->stEffect[0].cEffect == EF_SANC)
			sanc = item->stEffect[0].cValue;
		else if (item->stEffect[1].cEffect == EF_SANC)
			sanc = item->stEffect[1].cValue;
		else
			sanc = item->stEffect[2].cValue;
	}

	int isanc = sanc;

	if (isanc < 230)
		return -1;

	return (isanc - 230) % 4;
}

int Func::GetItemSanc(STRUCT_ITEM *item)
{
	for (int i = 0; i < 3; i++)
		if (item->stEffect[i].cEffect == EF_SANC || (item->stEffect[i].cEffect >= 116 && item->stEffect[i].cEffect <= 125))
			return item->stEffect[i].cValue;

	return 0;
}


void Func::RefinarItemMais(STRUCT_ITEM *item, int value)
{
	if (item->EF1 == EF_SANC || (item->EF1 >= EF_STARTCOLOR && item->EF1 <= EF_STOPCOLOR))
		item->EFV1 += value;
	else if (item->EF2 == EF_SANC || (item->EF2 >= EF_STARTCOLOR && item->EF2 <= EF_STOPCOLOR))
		item->EFV2 += value;
	else if (item->EF3 == EF_SANC || (item->EF3 >= EF_STARTCOLOR && item->EF3 <= EF_STOPCOLOR))
		item->EFV3 += value;
	else
	{
		if (!item->EF1)
		{
			item->EF1 = EF_SANC;
			item->EFV1 = value;
		}
		else if (!item->EF2)
		{
			item->EF2 = EF_SANC;
			item->EFV2 = value;
		}
		else if (!item->EF3)
		{
			item->EF3 = EF_SANC;
			item->EFV3 = value;
		}
	}

	return;
}

void Func::RemoveItens(int  loop, STRUCT_MOB *player, MSG_CombineItem *p)
{
	for (INT8 j = 0; j < loop; j++)
	{
		memset(&player->Carry[p->InvenPos[j]], 0, sizeof STRUCT_ITEM);
		SendItem(p->ID, (int)SlotType::Inventory, p->InvenPos[j], &player->Carry[p->InvenPos[j]]);
	}
}


void Func::GiveItem(int clientid, int ItemID, int add1, int add2, int add3)
{
	if (ItemID <= 0 || ItemID >= 6500)
		return;

	STRUCT_ITEM Give = { ItemID, add1, add2, add3};

	int Ret = PutItem(clientid, &Give);
	if (!Ret)
		SendClientMessage(clientid, "Item Não foi entregue !");
	else
		SendClientMessage(clientid, Func::strFmt("Recebeu [ %s ]", pItem(ItemID)->Name));

	return;
}


void Func::SendSignalParmArea(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm)
{
	static auto pMobGrid = reinterpret_cast<unsigned short*>(0x34EA550);

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= 4096 || y < 0 || y >= 4096)
				continue;

			int tmob = pMobGrid[4096 * y + x];

			if (tmob >= MAX_USER || tmob == 0)
				continue;

			auto user = Func::GetUserFromIndex(tmob);

			if (user->Mode != 22)
				continue;

			SendClientSignalParm(tmob, id, signal, parm);
		}
	}
}
 

void Func::SendGuildMedal(int clientId)
{
	auto player =  GetMobFromIndex(clientId);

	if (player->MOB.Guild == 0)
		return;


	auto guild = Func::GetGuild(player->MOB.Guild);

	struct Packet
	{
		MSG_STANDARD Header;
		STRUCT_GUILD guild;
	};

	Packet packet;
	memset(&packet, 0x0, sizeof(Packet));


	packet.Header.ID = clientId;
	packet.Header.Type = 0x66A;
	packet.Header.Size = sizeof(Packet);
	memcpy(&packet.guild, guild, sizeof(STRUCT_GUILD));

	Func::SendPacket2(clientId, &packet, sizeof(Packet));
}