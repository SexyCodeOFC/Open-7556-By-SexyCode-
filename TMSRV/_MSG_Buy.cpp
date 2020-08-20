#include "stdafx.h"

bool Exec_MSG_Buy(int conn, char* pMsg)
{
	MSG_Buy* m = (MSG_Buy*)pMsg;
	p379h* packet = (p379h*)pMsg;

	int TargetID = m->TargetID;
	int TargetInvenPos = m->TargetInvenPos;
	int MyInvenPos = m->MyInvenPos;

	int Village = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY);

	if (conn < 0 || conn > MAX_USER)
		return false;

	if (Village < 0 || Village > 5)
		return false;

	if (TargetID < MAX_USER || TargetID > MAX_MOB)
		return false;

	STRUCT_ITEM* ItemMob = &pMob[TargetID].MOB.Carry[TargetInvenPos];
	int itemIndex = pMob[TargetID].MOB.Carry[TargetInvenPos].sIndex;

	if (pMob[TargetID].MOB.BaseScore.Dex == 1001)
	{
		for (int i = 0; i < g_MileageCountLine; i++)
		{
			if (pMob[TargetID].MOB.Carry[TargetInvenPos].sIndex == pMileageStore[i].Item.sIndex)
			{
				uint32_t PriceItem = pMileageStore[i].Price;

				// Exemplo
				if (pMob[TargetID].MOB.Carry[TargetInvenPos].sIndex == 3326 && pMob[TargetID].MOB.Carry[TargetInvenPos].stEffect[0].cEffect == EF_AMOUNT)
				{
					if (pMob[TargetID].MOB.Carry[TargetInvenPos].stEffect[0].cValue == 5)
						PriceItem = 400;
				}

				if (pMileageStore[i].Store <= 0)
				{
					sprintf(temp, "Item indisponível.");
					SendClientMessage(conn, temp);
					return false;
				}

				if (pUserData[conn].AccountInfo.Cash < PriceItem)
				{
					sprintf(temp, "Você não possui Doante Coins suficiente.");
					SendClientMessage(conn, temp);
					return false;
				}

				if (itemIndex == 0)
				{
					Log("err,buy request null item from shop donate - MSG_BUY", pUser[conn].AccountName, pUser[conn].IP);
					return false;
				}

				if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
				{
					SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
					return false;
				}

				if (PutItemCargo(conn, 0, ItemMob))
				{
					pMileageStore[i].Store--;
					pUserData[conn].AccountInfo.Cash -= PriceItem;
					SendClientMessage(conn, Func::strFmt("Compra realizada com sucesso, Donate Coins atual é: [%d]", pUserData[conn].AccountInfo.Cash));
					Func::SaveAccount(conn, pUser[conn].AccountName);

					char szLog[128];
					sprintf(szLog, "MSG_BUY ITEM DONATECOINS SUCCESS %s:%d", g_pItemList[ItemMob->sIndex].Name, PriceItem);
					Log(szLog, pUser[conn].AccountName, pUser[conn].IP);
					Func::SendDonateUpdate(conn);
					return false;
				}
				else
				{
					SendClientMessage(conn, "Não há espaço no baú para realizar transações");
					Func::SendDonateUpdate(conn);
					return false;
				}

				return false;
			}
		}

		return false;
	}



	if (pMob[TargetID].MOB.BaseScore.Dex == 1002)
	{
		auto moeda = 5440;

		STRUCT_ITEM* item = &pMob[TargetID].MOB.Carry[packet->sellSlot];

		auto pItem = Func::GetItemListItem(item->sIndex);// recebe os itens que estao sendo vendidos do npc.
		auto moedaName = Func::GetItemListItem(moeda);// item pedido para realizar a função
		char temp[512]; // char para o sprintf
		auto userData = &pUserData[conn];

		auto slot = Func::GetFirstSlot(conn, SlotType::Inventory, 0, 0);

		int amount = 0;
		int Loop = 30;

		auto Andarilho = pMob[conn].MOB.Carry[60].sIndex;
		auto Andarilho_2 = pMob[conn].MOB.Carry[61].sIndex;

		if (Andarilho == 3467)
			Loop += 15;

		if (Andarilho_2 == 3467)
			Loop += 15;

		for (int i = 0; i < Loop; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == moeda)
				amount += BASE_GetItemAmount(&pMob[conn].MOB.Carry[i]);
		}

		auto user = Func::GetUserFromIndex(conn);

		for (int i = 0; i < NumberMoedas; i++)
		{
			if (pMob[TargetID].MOB.Carry[packet->sellSlot].sIndex == coins[i].item)
			{

				if (slot == -1)
				{
					// sprintf e quando for imprimir um valor na msg ok.
					SendClientMessage(conn, "Sem espaço no inventario");
					return false;// true continua a função da tmsrv, false entra somente nessa função
				}

				if (amount < coins[i].preço)
				{
					SendClientMessage(conn, "Moedas insufiencte");
					return false;
				}

				if (coins[i].quantidades <= 0)
				{
					SendClientMessage(conn, "item indisponivel");
					return false;
				}

				int price = coins[i].preço;

				Func::ClearAmountItem(conn, moeda, price);	// aqui retira do pack, ok funcional.		 

				STRUCT_ITEM ItemFinalizado;
				memset(&ItemFinalizado, 0, sizeof(STRUCT_ITEM));

				PutItem(conn, &ItemFinalizado);
				sprintf(temp, "Obrigado por comprar %s ", moedaName->Name);
				SendSay(TargetID, temp);
				return true;
			}
		}
		sprintf(temp, "traga-me a moeda lojinha %s !", moedaName->Name);
		SendSay(conn, temp);

		return false;
	}

	/*if (pMob[TargetID].MOB.BaseScore.Dex == 1003) //RECICLADOR BETA
	{
		STRUCT_ITEM* item = &pMob[TargetID].MOB.Carry[packet->sellSlot]; //define o item da função quando clica em cima

		auto pItem = Func::GetItemListItem(item->sIndex);// itens que estão no NPC
		auto moedaName = Func::GetItemListItem(item->sIndex);// item pedido para realizar a função
		char temp[512];
		auto userData = &pUserData[conn];

		auto slot = Func::GetFirstSlot(conn, SlotType::Inventory, 0, 0); //define que irá pegar o item do primeiro slot que encontrar
		int amountcount = 0;

		int itemsell[2][2] =
		{
			{ 412, 60000 },
			{ 413, 120000 },
		};
						
		for (int i = 0; i < 60; i++)  
		{
			if (pMob[TargetID].MOB.Carry[packet->sellSlot].sIndex == itemsell)
			{
				if (pMob[conn].MOB.Coin > 1900000000) //define o fim da função caso falte 100kk para estourar o limite do inventário
				{
					SendClientMessage(conn, "Você está próximo do gold máximo!");
					return true;
				}

				for (int i = 0; i < 60; i++) // define os slots onde poderão ser encontrado os itens
				{
					if (pMob[conn].MOB.Carry[i].sIndex == i)
						amountcount += BASE_GetItemAmount(&pMob[conn].MOB.Carry[i]); //conta quantos itens tem no inventário
				}

				if (amountcount < 60) //define que precisa ter mais de 60 itens
				{
					SendClientMessage(conn, "Você precisa ter pelo menos 60 Itens");
					return true;
				}

				for (int i = 0; i < 60; i++) //define a retirada de 60 itens
				{
					Func::AmountMinus(&pMob[conn].MOB.Carry[i]);
					SendItem(conn, (uint16_t)SlotType::Inventory, slot, &pMob[conn].MOB.Carry[i]);
				}
																
				
				pMob[conn].MOB.Coin += price; //define o acréscimo do valor do item
				sprintf(temp, "Obrigado por vender %s ", moedaName->Name);
				SendEtc(conn);
				return true;
			}
		}
		SendClientMessage(conn, "Traga-me Itens Recicláveis");
		SendSay(conn, temp);

		return false;
	}*/

	/*unsigned int Donate = BASE_GetItemAbility(ItemMob, EF_DONATE);

	if (Donate)
	{
		if (Donate > pUserData[conn].AccountInfo.Mileage)
		{
			sprintf(temp, "Você não possui Mileage suficiente.");
			SendClientMessage(conn, temp);
			return false;
		}

		if (itemIndex == 0)
		{
			Log("err,buy request null item from shop donate - MSG_BUY", pUser[conn].AccountName, pUser[conn].IP);
			return false;
		}

		if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
		{
			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			return false;
		}

		if (PutItem(conn, ItemMob))
		{
			pUserData[conn].AccountInfo.Mileage -= Donate;
			SendClientMessage(conn, Func::strFmt("Compra realizada com sucesso, Mileage atual é: [%d]", pUserData[conn].AccountInfo.Mileage));
			return false;
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
			return false;
		}

		return false;
	}*/

	return true;
}

