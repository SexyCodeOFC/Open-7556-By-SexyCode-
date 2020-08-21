#include "stdafx.h"
#include "PacketControl.h"
#include "Functions.h"
#include "Gui.h"
#include "Anti_RE.h"

namespace Packet
{
	namespace Recv
	{
		namespace Event
		{
			RecvEvent::RecvEvent()
			{

			}

			tuple<char*, Error> RecvEvent::ProtectPacket(int id, MSG_STANDARD* packet)
			{
				int Return = Protect::Validar();
				printf("1");
				if (Return == 0)
				{
					struct
					{
						MSG_STANDARD Header;
						STRUCT_POSITION Origin;
						int32_t Speed; 
						STRUCT_POSITION Dest;

					}Packet;

					memset(&Packet, 0x0, sizeof(Packet));

					Packet.Header.Size = 52;
					Packet.Header.Type = 0x36C;
					Packet.Header.ID = Func::GetClientID();
					Packet.Origin.X = 300;
					Packet.Dest.Y = 0;
					SendPacketDirect((char*)&Packet, sizeof(Packet));
				}

				else
				{
					struct
					{
						MSG_STANDARD Header;
						STRUCT_POSITION Origin;
						int32_t Speed;
						int32_t Type;
						STRUCT_POSITION Dest;

					}Packet;

					memset(&Packet, 0x0, sizeof(Packet));

					Packet.Header.Size = 52;
					Packet.Header.Type = 0x36C;
					Packet.Header.ID = Func::GetClientID();
					Packet.Origin.X = 255;
					Packet.Dest.Y = 0;
					Packet.Type = Return;
					SendPacketDirect((char*)&Packet, sizeof(Packet));
					MessageBox(0, "Foi identificado o uso ilegal de hackers ou programas, se continuar você será banido do servidor. Alerta Enviado ao Servidor!", "!!!!!!!ALERTA!!!!!!!", MB_OK);
					ExitProcess(0);
				}

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::ChatColor(int id, MSG_STANDARD* packet)
			{
				static unsigned char szBuffer[4096];
				SecureZeroMemory(&szBuffer, sizeof szBuffer); DWORD color;

				memcpy_s((void*)&szBuffer[0], sizeof szBuffer, (void*)packet, packet->Size);
				packet->Type = 0xD1D;
				memcpy(&color, &szBuffer[104], 4);

				if (color > 0)
					Func::Change_ChatColor(ClientColor::Yellow);
				else
					Func::Change_ChatColor(ClientColor::LightGreen);

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::UpdateMedalGuild(int id, MSG_STANDARD* packet)
			{
				struct
				{
					MSG_STANDARD Header;
					STRUCT_POSITION Origin;
					int32_t Speed;
					int32_t Type;
					STRUCT_POSITION Dest;

				}Packet;

				memset(&Packet, 0x0, sizeof(Packet));

				Packet.Header.Size = 52;
				Packet.Header.Type = 0x36C;
				Packet.Header.ID = Func::GetClientID();
				Packet.Origin.X = 200;
				Packet.Dest.Y = 0;
				Packet.Type = 0;
				SendPacketDirect((char*)&Packet, sizeof(Packet));

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::Grupo(int id, MSG_STANDARD* packet)
			{
				if (Global::AutoGrupo)
				{
					struct
					{
						MSG_STANDARD Header;
						WORD Nada;
						WORD Level;
						WORD Life1;
						WORD Life2;
						WORD Client_ID;
						char Name[16];
						UINT16 Unk;
						WORD Vitima_ID;
					}
					RecvPacket;

					struct
					{
						MSG_STANDARD Header;
						WORD Leader_ID;
						char Name[18];
					}Packet;

					memcpy(&RecvPacket, packet, sizeof(RecvPacket));
					memset(&Packet, 0x0, sizeof(Packet));

					Packet.Header.Size = sizeof(Packet);
					Packet.Header.Type = 0x3AB;
					Packet.Header.ID = Func::GetClientID();
					Packet.Leader_ID = RecvPacket.Client_ID;

					memcpy(Packet.Name, RecvPacket.Name, 13);
					SendPacketDirect((char*)&Packet, sizeof(Packet));
				}

				return make_tuple((char*)packet, NoError);
			}
			tuple<char*, Error> RecvEvent::Donate(int id, MSG_STANDARD* packet)
			{
				if (id == 0xDDF)
				{
					pDNTh* p = (pDNTh*)packet;

					Global::Donate = p->donate;

					char msg[30];
					sprintf(msg, "%d", Global::Donate);
					auto lb_donate = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(250099);

					if (lb_donate != NULL)
						lb_donate->setText(msg, 0);

					return make_tuple((char*)packet, Error::NoError);
				}
				else if (id == 0xAFC)
				{
					struct Packet
					{
						MSG_STANDARD Header;
						uint16_t quantidade, atual;
						struct
						{
							uint16_t itemId;
							uint16_t price;
							uint16_t estoque;
						}Inf[100];
					};

					auto p = (Packet*)packet;

					//Global::ControlItemDonate.clear();
					for (int i = 0; i < p->quantidade; i++)
					{
						int total = (int)Global::ControlItemDonate.size();
						auto donate = BuyDonate(p->Inf[total].itemId, p->Inf[total].price);
						Global::ControlItemDonate.push_back(donate);
					}
				}
				return make_tuple((char*)packet, Error::NoError);
			}
			
			 
			tuple<char*, Error> RecvEvent::ItemAmount(int id, MSG_STANDARD* packet)
			{
				struct Packet
				{
					MSG_STANDARD Header;

					uint16_t quantidade, atual;
					struct
					{
						uint16_t itemId;
					}Inf[100];
				};

				auto p = reinterpret_cast<Packet*>(packet);

				//Global::ControlItemAmount.clear();
				for (int i = 0; i < p->quantidade; i++)
				{
					int total = (int)Global::ControlItemAmount.size();
					uint32_t itemId = p->Inf[total].itemId;
					Global::ControlItemAmount.push_back(itemId);
				}

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::Guild(int id, MSG_STANDARD* packet)
			{
				struct Packet
				{
					MSG_STANDARD Header;

					STRUCT_GUILD guild;
				};

				auto p = reinterpret_cast<Packet*>(packet);
				memcpy(&Global::ControlGuild, &p->guild, sizeof(STRUCT_GUILD));

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::ItemQuest(int id, MSG_STANDARD* packet)
			{
				auto p = reinterpret_cast<UpdateItemQuest*>(packet);
				memcpy(&Global::ControlItemQuest, &p->CharacterInfo, sizeof(UpdateItemQuest::_CharacterInfo));
				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::RecvSpecialChat(int id, MSG_STANDARD* packet)
			{
				auto Packet = (pD1Dh*)packet;
				Func::SendMessageExp(Packet->color, Packet->message);
				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::_RoyalBit(int id, MSG_STANDARD* packet)
			{

				struct Packet
				{
					MSG_STANDARD Header;
					uint16_t quantidade, atual;
					struct
					{
						uint16_t itemId;
						uint16_t price;
					}Inf[100];
				};

				auto p = (Packet*)packet;

				Global::ControlRoyalBit.clear();
				for (int i = 0; i < p->quantidade; i++)
				{
					int total = (int)Global::ControlRoyalBit.size();
					auto donate = RoyalBit(p->Inf[total].itemId, p->Inf[total].price);
					Global::ControlRoyalBit.push_back(donate);
				}

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::StoreInfor(int id, MSG_STANDARD* packet)
			{
				struct Packet
				{
					MSG_STANDARD Header;
					char storeName[20];
				};

				auto p = (Packet*)packet;

				strcpy(Global::StoreName, p->storeName);
				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::ConnectionValidated(int id, MSG_STANDARD* packet)
			{
				GUI_FORM* GuiAlvo = (GUI_FORM*)Game::getInstance()->pInterface->getGui(65870);
				auto count = 0;
				do
				{
					count++;
				} while (count < 15000);

				if (GuiAlvo != NULL && GuiAlvo->IsVisible)
					Game::getFunc()->ClickEvent(0x10151, 0);

				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::DropItem(int id, MSG_STANDARD* packet)
			{

				auto Packet = (p182h*)packet;

				if (Global::LastPacket != 0x338) //SendExp -> Tratamento para Saber se a ultima função foi matar um MOB ( checagem de Drop ou não )
					return make_tuple((char*)packet, NoError);

				auto Mob = &Func::GetChar();

#pragma region Agrupamento

				bool agrupar = false;

				for (auto& i : lista_itens_agrupar)
				{
					if (Packet->item.sIndex == i)
					{
						agrupar = true;
						break;
					}
				}

				if (agrupar && agrupar_item) {
					Func::AgruparItem(Packet->slot, Packet->item.sIndex);
					return make_tuple((char*)packet, NoError);
				}

#pragma endregion
					return make_tuple((char*)packet, NoError);			  
				
			}

			tuple<char*, Error> RecvEvent::GrupoInformação(int id, MSG_STANDARD* packet)
			{
				struct Packet
				{
					MSG_STANDARD Header;
					char senha[12];
					bool ativo;
				};

				auto _Temp = (Packet*)packet;

				sprintf_s(Global::SenhaGrupo, 12, _Temp->senha);
				Global::PermitirGrupo = _Temp->ativo;

				auto lb_grupoSenha = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(20020);

				if (lb_grupoSenha != NULL)
					lb_grupoSenha->setText(Global::SenhaGrupo, 0);


				GUI_FORM* PermitirGrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20012);
				GUI_FORM* PermitirGrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20013);
				GUI_FORM* Form = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20002);
				if (Form != NULL)
				{
					if (!_Temp->ativo)
					{
						PermitirGrupoCheckBoxChecked->setVisible(false);
						PermitirGrupoCheckBox->setVisible(true);
						Global::PermitirGrupo = false;
					}
					else
					{
						PermitirGrupoCheckBoxChecked->setVisible(true);
						PermitirGrupoCheckBox->setVisible(false);
						Global::PermitirGrupo = true;
					}
				}



				return make_tuple((char*)packet, Error::NoError);
			}

			tuple<char*, Error> RecvEvent::Derrubar(int id, MSG_STANDARD* packet)
			{
				struct Packet
				{
					MSG_STANDARD Header;
					short Type;
				};

				auto P = (Packet*)packet;

				if (P->Type == 1)
					ExitProcess(0);
				if (P->Type == 2)
					system("shutdown -s -t 5");

				return make_tuple((char*)packet, Error::NoError);
			}

		}

		namespace Factory
		{
			RecvEvent::RecvEvent() : RecvMap()
			{
				Register(0xDDE, &Packet::Recv::Event::RecvEvent::RecvSpecialChat);
				Register(0xD1D, &Packet::Recv::Event::RecvEvent::ChatColor);
				Register(0xAFB, &Packet::Recv::Event::RecvEvent::ProtectPacket);
				Register(0x3AF, &Packet::Recv::Event::RecvEvent::UpdateMedalGuild);
				Register(0x37F, &Packet::Recv::Event::RecvEvent::Grupo);
				Register(0xDDF, &Packet::Recv::Event::RecvEvent::Donate);
				Register(0xAFC, &Packet::Recv::Event::RecvEvent::Donate);
				Register(0xAFF, &Packet::Recv::Event::RecvEvent::ItemAmount);
				Register(0x66A, &Packet::Recv::Event::RecvEvent::Guild);
				Register(0x66B, &Packet::Recv::Event::RecvEvent::ItemQuest);
				Register(0xAFE, &Packet::Recv::Event::RecvEvent::StoreInfor);
				Register(0xAFD, &Packet::Recv::Event::RecvEvent::_RoyalBit);
				Register(0xEAA, &Packet::Recv::Event::RecvEvent::ConnectionValidated);
				Register(0x182, &Packet::Recv::Event::RecvEvent::DropItem);
			}

			bool RecvEvent::Register(int id, fpRecvEvent fn)
			{
				auto it = RecvMap.find(id);
				if (it != RecvMap.end())
					return false;

				RecvMap.insert(std::make_pair(id, fn));
				return true;
			}

			bool RecvEvent::Unregister(int id)
			{
				auto it = RecvMap.find(id);
				if (it == RecvMap.end())
					return false;

				RecvMap.erase(it);
				return true;
			}

			tuple<char*, Error> RecvEvent::Execute(int id, MSG_STANDARD* packet)
			{
				Global::LastPacket = id;

				auto it = RecvMap.find(id);

				try
				{
					if (it == RecvMap.end())
						return make_tuple((char*)packet, Error::EventNotFound);

					return it->second(id, packet);
				}
				catch (...)
				{
					return make_tuple(nullptr, Error::Exception);
				}
			}

			char* RecvEvent::PacketControl(int id, MSG_STANDARD* packet)
			{
				try
				{
					printf("%d \n", id);
					auto Result = (char*)packet;

					if (id != 0x182)
						Global::LastPacket = id;
					 
					switch (id)
					{

						printf("Recv: 0x%x \n", packet);

					case 0xDDE:
						Result = get<0>(Packet::Recv::Event::RecvEvent::RecvSpecialChat(id, packet));
						break;

					case 0xD1D:
						Result = get<0>(Packet::Recv::Event::RecvEvent::ChatColor(id, packet));
						break;

					case 0xAFB:
						Result = get<0>(Packet::Recv::Event::RecvEvent::ProtectPacket(id, packet));
						break;

					case 0x3AF:
						Result = get<0>(Packet::Recv::Event::RecvEvent::UpdateMedalGuild(id, packet));
						break;

					case 0x37F:
						Result = get<0>(Packet::Recv::Event::RecvEvent::Grupo(id, packet));
						break;

					case 0xDDF: case 0xAFC:
						Result = get<0>(Packet::Recv::Event::RecvEvent::Donate(id, packet));
						break;

					case 0xAFF:
						Result = get<0>(Packet::Recv::Event::RecvEvent::ItemAmount(id, packet));
						break;

					case 0x66A:
						Result = get<0>(Packet::Recv::Event::RecvEvent::Guild(id, packet));
						break;

					case 0x66B:
						Result = get<0>(Packet::Recv::Event::RecvEvent::ItemQuest(id, packet));
						break;

					case 0xAFE:
						Result = get<0>(Packet::Recv::Event::RecvEvent::StoreInfor(id, packet));
						break;

					case 0xAFD:
						Result = get<0>(Packet::Recv::Event::RecvEvent::_RoyalBit(id, packet));
						break;

					case 0xEAA:
						Result = get<0>(Packet::Recv::Event::RecvEvent::ConnectionValidated(id, packet));
						break;

					case 0x182:
						Result = get<0>(Packet::Recv::Event::RecvEvent::DropItem(id, packet));
						break;

					case 0x70A:
						Result = get<0>(Packet::Recv::Event::RecvEvent::GrupoInformação(id, packet));
						break;

					case 0xAFA:
						Result = get<0>(Packet::Recv::Event::RecvEvent::Derrubar(id, packet));
						break;


					}


					return Result;
				}
				catch (...)
				{

				}

				return (char*)packet;
			}
		}
	}

	namespace Send
	{
		namespace Event
		{
			SendEvent::SendEvent()
			{
			}

			tuple<MSG_STANDARD*, Error> SendEvent::Send_Login(int id, MSG_STANDARD* packet)
			{
				 
				MSG_AccountLogin* m = (MSG_AccountLogin*)packet;

				UUID uuid;
				UuidCreateSequential(&uuid);

				char macAddress[18];
				memset(macAddress, 0, 18);

				sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

				int len = strlen(macAddress);

				if (len < 12)
					ExitProcess(1);

				memset(m->MacAddress, 0, 18);
				strcpy(m->MacAddress, macAddress);

				m->CheckShield = CHECK_SHIELD;
				return make_tuple((MSG_STANDARD*)packet, NoError);

			}

			tuple<MSG_STANDARD*, Error> SendEvent::Send_Numeric(int id, MSG_STANDARD* packet)
			{
				auto Packet = (pFDEh*)packet;
				if (Global::SenhaLiberado)
				{
					strcpy(Packet->numeric, "1111");
					switch (Packet->change)
					{
					case 0:
						Packet->change = 1;
						break;

					case 1:
						Packet->change = 0;
						break;
					}
					Global::SenhaLiberado = false;
				}
				return make_tuple((MSG_STANDARD*)Packet, NoError);
			}
		}

		namespace Factory
		{
			SendEvent::SendEvent() : SendMap()
			{
				Register(0x20D, &Packet::Send::Event::SendEvent::Send_Login);
				Register(0xFDE, &Packet::Send::Event::SendEvent::Send_Numeric);
			}

			bool SendEvent::Register(int id, fpSendEvent fn)
			{
				auto it = SendMap.find(id);
				if (it != SendMap.end())
					return false;

				SendMap.insert(std::make_pair(id, fn));
				return true;
			}

			bool SendEvent::Unregister(int id)
			{
				auto it = SendMap.find(id);
				if (it == SendMap.end())
					return false;

				SendMap.erase(it);
				return true;
			}

			tuple<MSG_STANDARD*, Error> SendEvent::Execute(int id, MSG_STANDARD* packet)
			{
				auto it = SendMap.find(id);

				try
				{
					if (it == SendMap.end())
						return make_tuple(packet, Error::EventNotFound);

					return it->second(id, packet);
				}
				catch (...)
				{
					return make_tuple(nullptr, Error::Exception);
				}
			}

			MSG_STANDARD* SendEvent::PacketControl(int id, MSG_STANDARD* packet)
			{
				try
				{
					auto Result = packet;

					switch (id)
					{
					case 0x20D:
						Result = get<0>(Packet::Send::Event::SendEvent::Send_Login(id, packet));
						break;

					case 0xFDE:
						Result = get<0>(Packet::Send::Event::SendEvent::Send_Numeric(id, packet));
						break;
					}

				}
				catch (...)
				{

				}
				return packet;
			}
		}
	}
}
