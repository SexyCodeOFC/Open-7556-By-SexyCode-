#include "stdafx.h"

Timer::Timer()
	: minCounter_(0)
	, secCounter_(0)
	, quarterMsCounter_(0)
	, minPartCounter_(0)
{
}

void Timer::ProcessMinTimer()
{
	minPartCounter_++;

	if (minPartCounter_ >= 6)
	{
		minPartCounter_ = 0;
		minCounter_++;

		time_t rawtime;
		tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		auto sec = timeinfo->tm_sec;
		auto min = timeinfo->tm_min;
	}
}

void Timer::ProcessSecTimer()
{
	quarterMsCounter_++;

	if (quarterMsCounter_ >= 4)
	{
		ClueOfRunesFactory::TimerControl();

		quarterMsCounter_ = 0;
		secCounter_++;

		time_t rawtime;
		tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		std::time_t now = time(0);
		std::tm when;
		::localtime_s(&when, &now);

		int conn = 0;

		auto sec = timeinfo->tm_sec;
		auto min = timeinfo->tm_min;
		auto domingo = timeinfo->tm_wday;


#pragma region Chamada de um Segundo
		if (!(secCounter_ % 1))
		{



#pragma region Chama Guerra de Torres FIM
			CWarTower::ProcessEnd(timeinfo); 
#pragma endregion

#pragma region Chama Guerra de Torres INICIO
			CWarTower::GuildProcess(timeinfo);
#pragma endregion

#pragma region Definição de tempo altar Noatun
			if (when.tm_wday == 0)
			{
				if (when.tm_hour == 21 && when.tm_min == 06 && when.tm_sec == 05)
				{
					ServerInfo.CastleWar.AltarTime = 120;
				}
			}
#pragma endregion

#pragma region For chamando Players

		 for (int client = 1; client < MAX_USER; client++)
		 { 
//
//
//#pragma region Verificações Mac
//			  
//			 auto mobinArea1 = Func::CheckMacUserInArea({ 2973, 1018 }, { 3453, 1655 }, { pUserData[conn].AccountInfo.MacAddress });
//			   
//			 if (mobinArea1.size() > 0)
//			 {
//				 goto fim;
//			 fim:
//				 Func::SendBackCity(client);
//			 } 
//
//#pragma endregion
#pragma region Atualiza bag para o uso de pergaminhos agua
			 if (pMob[client].TargetX >= 1965 - 10 && pMob[client].TargetX <= 1965 + 10 && pMob[client].TargetY >= 1770 - 10 && pMob[client].TargetY <= 1770 + 10)
			 {
				 SendCarry(client);
				 return;
			 }
#pragma endregion

#pragma region AUTO VENDA
			 auto userData = &pUserData[client];

			 if (userData->Ingame.autoStore)
			 {
				 userData->Ingame.PointStore++;

				 if (userData->Ingame.PointStore > 415)//
				 {
					 userData->Ingame.PointStore = 0;

					 time_t now;
					 time(&now);
					 tm when;
					 localtime_s(&when, &now);

					 auto slot = Func::GetFirstSlot(client, SlotType::Inventory, 0, 0);

					 if (slot == -1)
					 {
						 SendClientMessage(client, "falta de  espaço no inventario");
					 }

					 else
					 {
						 char tmp[256] = { 0, };
						 strftime(tmp, 256, "!%d-%m-%y %H:%M:%S  Recebeu seu prêmio.", &when);
						 STRUCT_ITEM moedas = { 5440, 0, 0, 0 };
						 //STRUCT_ITEM moedas = { Event::Premio, 0, 0, 0, 0, 0, 0 };
						 PutItem(client, &moedas);
						 SendClientMessage(client, tmp);
					 }
				 }
			 }
#pragma endregion

#pragma region Chamada ALTAR WAR NOATUN
				auto mob = GetMobFromIndex(client);
				if (when.tm_wday == 0)
				{
					if (*(int*)0x8C76348 > 1)
					{
						if (mob->TargetX == 1046 && mob->TargetY == 1690)
							conn = client;
					}
				}

#pragma endregion

		 }
#pragma endregion

#pragma region Contador Altar Noatun	

			if (when.tm_wday == 0)
			{
				if (*(int*)0x8C76348 > 1)
				{
					if (conn != 0)
					{
						if (pMob[conn].MOB.Equip[12].sIndex == 509)
						{
							if (ServerInfo.CastleWar.AltarTime >= 0)
							{
								Func::SendSignalParmArea(1024, 1664, 1160, 1790, 30000, 944, ServerInfo.CastleWar.AltarTime);
								ServerInfo.CastleWar.AltarTime--;

								if (ServerInfo.CastleWar.AltarTime == -1)
								{
									*(int*)((conn * 0xC58) + 0x752C470) = 5;
									RegenMob(conn);
								}
								else
									*(int*)((conn * 0xC58) + 0x752C470) = 0;

								if (ServerInfo.CastleWar.AltarTime < 0)
									ServerInfo.CastleWar.AltarTime = 0;
							}
						}
					}
					else
						ServerInfo.CastleWar.AltarTime = 120; // fim 1160 1790 // inicio 1024 1664
				}
			}
			
#pragma endregion

		}
#pragma endregion

	}
}