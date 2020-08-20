#include "stdafx.h"
#include "GuiControl.h"
#include "Gui.h"


namespace GuiControl
{
	namespace EventHandle
	{
		
		tuple<bool, Error> Handle::DonateControl(int handle, int gui)
		{
			// Abre Painel Ativar Serial
			if (handle == 196099)
			{
				GUI_FORM* GuiAlvo = (GUI_FORM*)Game::getInstance()->pInterface->getGui(195500);
				if (GuiAlvo != NULL)
				{
					if (!GuiAlvo->IsVisible)
					{
						GuiAlvo->setVisible(true);

						auto Edit = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(195501);
						Edit->setText2("");
					}
				}
			}

			// Fecha Painel de Ativar Serial
			else if (handle == 195503)
			{
				GUI_FORM* GuiAlvo = (GUI_FORM*)Game::getInstance()->pInterface->getGui(195500);
				if (GuiAlvo != NULL)
				{
					if (GuiAlvo->IsVisible)
					{
						GuiAlvo->setVisible(false);
					}
				}
			}

			// Envia Packet para Abrir o NPC
			else if (handle == 196100)
			{
				struct
				{
					MSG_STANDARD	Header;
					short npcID;
					short Warp;

				}Packet;

				memset(&Packet, 0x0, sizeof(Packet));

				Packet.Header.ClientTick = timeGetTime();
				Packet.Header.Size = sizeof(Packet);
				Packet.Header.Type = 0x27B;
				Packet.Header.ID = Func::GetClientID();
				Packet.npcID = 1000;
				Packet.Warp = 100;
				SendPacketDirect((char*)&Packet, sizeof(Packet));
			}

			// Envia o Serial pro Servidor Ativar
			else if (handle == 195502)
			{
				auto Edit = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(195501);

				struct
				{
					MSG_STANDARD	Header;
					char			Cmd[16];
					char			Msg[100];
				}Packet;

				memset(&Packet, 0, sizeof(Packet));

				Packet.Header.Size = sizeof(Packet);
				Packet.Header.Type = 0x334;
				Packet.Header.ID = Func::GetClientID();
				Packet.Header.ClientTick = timeGetTime();
				strcpy(Packet.Cmd, "pin");
				strcpy(Packet.Msg, Edit->getText());
				SendPacketDirect((char*)&Packet, sizeof(Packet));


				(GUI_FORM*)Game::getInstance()->pInterface->getGui(195500)->setVisible(false);
			}


			return make_tuple(true, NoError);
		}
		
		tuple<bool, Error> Handle::SecurityControl(int handle, int gui)
		{
			if (!Global::SenhaLiberado)
				Global::SenhaLiberado = true;
			else
				Global::SenhaLiberado = false;

			auto f = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(66433);
			auto g = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(66438);
			auto b = (GUI_FORM*)Game::getInstance()->pInterface->getGui(195501);

			if (b->IsVisible)
				b->setVisible(false);

			if (f != NULL && g != NULL)
			{
				Game::getFunc()->ClickEvent(66438, 1);
				Game::getFunc()->ClickEvent(66438, 1);
				Game::getFunc()->ClickEvent(66438, 1);
				Game::getFunc()->ClickEvent(66438, 1);

				Game::getFunc()->ClickEvent(66433, 1);
			}
			return make_tuple(true, NoError);

		}

		tuple<bool, Error> Handle::SaveAccount(int handle, int gui)
		{
			struct CredencialLogin
			{
				struct
				{
					char Login[12];
					char Senha[12];
				}Credencial[4];
			};

			CredencialLogin CLogin = CredencialLogin();

			FILE* ft;
			errno_t err3;
			if ((err3 = fopen_s(&ft, "UI/SelectServerAccount.bin", "wb")) != NULL)
				return make_tuple(false, Error::EventNotFound);
			else
			{
				fread(&CLogin, 1, sizeof(CLogin), ft);


				for (auto t = 0; t < 4; t++)
				{
					/*Elementos onde fica os dados*/
					auto GuiText_Login = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209950 + (t * 2));
					auto GuiText_Senha = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209951 + (t * 2));

					char login[12];
					char senha[12];

					strcpy(login, GuiText_Login->getText());
					strcpy(senha, GuiText_Senha->getText());


					strcpy_s(CLogin.Credencial[t].Login, 12, GuiText_Login->getText());
					strcpy_s(CLogin.Credencial[t].Senha, 12, GuiText_Senha->getText());
				}
				fwrite(&CLogin, 1, sizeof(CLogin), ft);
				fclose(ft);
			}
			return make_tuple(true, NoError);

		}

		tuple<bool, Error> Handle::AutoConnectAccount(int handle, int gui)
		{
			GUI_FORM* GuiAlvo = (GUI_FORM*)Game::getInstance()->pInterface->getGui(65870);
			if (GuiAlvo != NULL)
			{
				if (!GuiAlvo->IsVisible)
				{
					Func::Shown(0xFFef7204, "Selecione um Servidor para Conectar-se.");
					return make_tuple(false, EventNotFound);
				}
			}

			auto Base = handle - 209980;

			auto GuiText_Login = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209950 + (Base * 2));
			auto GuiText_Senha = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209951 + (Base * 2));

			/*Elementos de Login*/
			auto TextBox_Login = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(0x1014F);
			auto TextBox_Senha = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(0x10150);

			/*Seta o Text de Login*/
			TextBox_Login->setText2(GuiText_Login->getText());
			TextBox_Senha->setText2(GuiText_Senha->getText());

			/*Envia o Click no Button de Login*/
			Game::getFunc()->ClickEvent(0x10151, 0);

			return make_tuple(true, NoError);
		}

		tuple<bool, Error> Handle::AutoGroup(int handle, int gui)
		{
			if (handle == 20009)
			{
				GUI_FORM* GrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20010);
				GUI_FORM* GrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20011);

				if (!GrupoCheckBox->IsVisible)
				{
					GrupoCheckBoxChecked->setVisible(false);
					GrupoCheckBox->setVisible(true);
					Global::AutoGrupo = false;
				}
				else
				{
					GrupoCheckBoxChecked->setVisible(true);
					GrupoCheckBox->setVisible(false);
					Global::AutoGrupo = true;
				}
			}

			else if (handle == 20014)
			{

				if (!Global::PermitirGrupo)
				{
					p334h Packet;

					Packet.Header.Size = sizeof(Packet);
					Packet.Header.Type = 0x334;
					Packet.Header.ID = Func::GetClientID();

					sprintf_s(Packet.Cmd, 16, "xTGrupoTx");
					sprintf_s(Packet.Msg, 100, "Ativar");

					SendPacketDirect((char*)&Packet, sizeof(Packet));
				}

				else
				{
					p334h Packet;

					Packet.Header.Size = sizeof(Packet);
					Packet.Header.Type = 0x334;
					Packet.Header.ID = Func::GetClientID();

					sprintf_s(Packet.Cmd, 16, "xTGrupoTx");
					sprintf_s(Packet.Msg, 100, "Desativar");

					SendPacketDirect((char*)&Packet, sizeof(Packet));
				}
			}

			else if (handle == 20004 || handle == 1864)
			{
				GUI_FORM* Form = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20002);
				Form->setVisible(false);
			}

			else if (handle == 20001)
			{
				GUI_FORM* Form = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20002);
				Form->setVisible(true);

#pragma region Auto_Grupo
				GUI_FORM* GrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20010);
				GUI_FORM* GrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20011);

				switch (Global::AutoGrupo)
				{
				case true:
					GrupoCheckBoxChecked->setVisible(true);
					GrupoCheckBox->setVisible(false);
					break;


				case false:
					GrupoCheckBoxChecked->setVisible(false);
					GrupoCheckBox->setVisible(true);
					break;
				}
#pragma endregion

#pragma region Permitir_Grupo
				GUI_FORM* PermitirGrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20012);
				GUI_FORM* PermitirGrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20013);

				switch (Global::PermitirGrupo)
				{
				case true:
					PermitirGrupoCheckBoxChecked->setVisible(true);
					PermitirGrupoCheckBox->setVisible(false);
					break;


				case false:
					PermitirGrupoCheckBoxChecked->setVisible(false);
					PermitirGrupoCheckBox->setVisible(true);
					break;
				}
#pragma endregion

#pragma region Senha_Grupo
				char pass[12] = { 0, };
				sprintf_s(pass, 12, Global::SenhaGrupo);
				auto lb_senhagrupo = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(20020);

				if (lb_senhagrupo != NULL)
					lb_senhagrupo->setText(pass, 0);
#pragma endregion
			}

			else if (handle == 20015)
			{
				auto lb_Senha = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(20018);

				p334h Packet;

				Packet.Header.Size = sizeof(Packet);
				Packet.Header.Type = 0x334;
				Packet.Header.ID = Func::GetClientID();

				sprintf_s(Packet.Cmd, 16, "xTGrupoTx");
				sprintf_s(Packet.Msg, 100, "Pedido %4s", lb_Senha->getText());

				SendPacketDirect((char*)&Packet, sizeof(Packet));
			}

			return make_tuple(true, NoError);

		}
	}


	namespace Event
	{
		GuiControl::GuiControl()
		{

		}

		void GuiControl::Create_Scene_World(int arg1, int arg2, int arg3, int arg4)
		{
			(GUI_FORM*)Game::getInstance()->pInterface->getGui(195500)->setVisible(false);
			(GUI_FORM*)Game::getInstance()->pInterface->getGui(589832)->setVisible(true);

#pragma region Auto_Grupo
			GUI_FORM* GrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20010);
			GUI_FORM* GrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20011);

			switch (Global::AutoGrupo)
			{
			case true:
				GrupoCheckBoxChecked->setVisible(true);
				GrupoCheckBox->setVisible(false);
				break;


			case false:
				GrupoCheckBoxChecked->setVisible(false);
				GrupoCheckBox->setVisible(true);
				break;
			}
#pragma endregion

#pragma region Permitir_Grupo
			GUI_FORM* PermitirGrupoCheckBox = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20012);
			GUI_FORM* PermitirGrupoCheckBoxChecked = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20013);

			switch (Global::PermitirGrupo)
			{
			case true:
				PermitirGrupoCheckBoxChecked->setVisible(true);
				PermitirGrupoCheckBox->setVisible(false);
				break;


			case false:
				PermitirGrupoCheckBoxChecked->setVisible(false);
				PermitirGrupoCheckBox->setVisible(true);
				break;
			}
#pragma endregion

#pragma region Senha_Grupo
			char pass[12] = { 0, };
			sprintf_s(pass, 12, Global::SenhaGrupo);
			auto lb_senhagrupo = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(20020);

			if (lb_senhagrupo != NULL)
				lb_senhagrupo->setText(pass, 0);
#pragma endregion

#pragma region Show_DonateInventory
			char msg[30];
			sprintf_s(msg, "%d", Global::Donate);
			auto lb_donate = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(250099);

			if (lb_donate != NULL) 
				lb_donate->setText(msg, 0); 
#pragma endregion	

#pragma region Show_TicketGoldInventory
			 
			char zmsg[30];
			sprintf_s(zmsg, "%d", Global::pTicketGold);
			auto lb_tgold = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(260099);

			if (lb_tgold != NULL)
				lb_tgold->setText(zmsg, 0);
#pragma endregion	

#pragma region Show_TicketPrataInventory
			char msgz[30];
			sprintf_s(msgz, "%d", Global::pTicketPrata);
			auto lb_tprata = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(260100);

			if (lb_tprata != NULL)
				lb_tprata->setText(msgz, 0);

#pragma endregion	

		}

		void  GuiControl::Create_Scene_Login()
		{
			auto f = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10006);
			auto g = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10007);

			if (f != NULL && g != NULL)
			{
				if (f->IsVisible)
				{
					Game::getFunc()->ClickEvent(0x10006, 1);
					Game::getFunc()->ClickEvent(0x10007, 1);
					*(int*)((int)f + 0x1FC) = 0;
					*(int*)((int)g + 0x1FC) = 0;
					Game::getFunc()->ClickEvent(0x10002, 1);
				}
			}

			auto SalveAccount = (GUI_FORM*)Game::getInstance()->pInterface->getGui(209900);
			if (SalveAccount != NULL && SalveAccount->IsVisible)
			{
				struct CredencialLogin
				{
					struct
					{
						char Login[12];
						char Senha[12];
					}Credencial[4];
				};

				CredencialLogin CLogin = CredencialLogin();

				FILE* ft;
				errno_t err3;
				if ((err3 = fopen_s(&ft, "UI/SelectServerAccount.bin", "r")) != NULL)
				{
					return;
				}
				else
				{
					fread(&CLogin, 1, sizeof(CLogin), ft);

					for (auto t = 0; t < 4; t++)
					{
						/*Elementos onde fica os dados*/
						auto GuiText_Login = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209950 + (t * 2));
						auto GuiText_Senha = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(209951 + (t * 2));

						GuiText_Login->setText2(CLogin.Credencial[t].Login);
						GuiText_Senha->setText2(CLogin.Credencial[t].Senha);
					}
					fclose(ft);
				}

			}

			auto OpçãoGrupo = (GUI_FORM*)Game::getInstance()->pInterface->getGui(20002);
			if (OpçãoGrupo != NULL && OpçãoGrupo->IsVisible)
			{
				OpçãoGrupo->setVisible(false);
			}
			/* REMOVE OS NUMEROS DA TELA DE LOGIN DO LADO ESQUERDO */
			auto Numbers = (GUI_FORM*)Game::getInstance()->pInterface->getGui(4623);
			if (Numbers != NULL && Numbers->IsVisible)
			{
				Numbers->setVisible(false);
			}
			/* REMOVE OS NUMEROS DA TELA DE LOGIN DO LADO ESQUERDO */
			auto Numbers2 = (GUI_FORM*)Game::getInstance()->pInterface->getGui(4624);
			if (Numbers2 != NULL && Numbers2->IsVisible)
			{
				Numbers2->setVisible(false);
			}
		}
	}

	namespace Factory
	{
		GuiControl::GuiControl() : GuiMap()
		{
			Register(196099, &EventHandle::Handle::DonateControl);
			Register(195503, &EventHandle::Handle::DonateControl);
			Register(196100, &EventHandle::Handle::DonateControl);
			Register(195502, &EventHandle::Handle::DonateControl);

			Register(195599, &EventHandle::Handle::SecurityControl);

			Register(209970, &EventHandle::Handle::SaveAccount);

			RegisterRange(209980, 209983, &EventHandle::Handle::AutoConnectAccount);

			Register(20009, &EventHandle::Handle::AutoGroup);
			Register(20014, &EventHandle::Handle::AutoGroup);
			Register(20004, &EventHandle::Handle::AutoGroup);
			Register(20001, &EventHandle::Handle::AutoGroup);
			Register(20015, &EventHandle::Handle::AutoGroup);
			Register(1864, &EventHandle::Handle::AutoGroup);
		}

		bool GuiControl::RegisterRange(const int minIndex, const int maxIndex, fpGuiEvent fn)
		{
			for (auto i = minIndex; i <= maxIndex; i++)
				if (!Register(i, fn))
					return false;

			return true;
		}

		bool GuiControl::RegisterRange(const std::initializer_list<int>& IndexRange, fpGuiEvent fn)
		{
			for (auto& i : IndexRange)
				if (!Register(i, fn))
					return false;

			return true;
		}

		bool GuiControl::unRegisterRange(const int minIndex, const int maxIndex)
		{
			for (auto i = minIndex; i <= maxIndex; i++)
				if (!Unregister(i))
					return false;

			return true;
		}

		bool GuiControl::unRegisterRange(const std::initializer_list<int>& IndexRange)
		{
			for (auto& i : IndexRange)
				if (!Unregister(i))
					return false;

			return true;
		}

		bool GuiControl::Register(int id, fpGuiEvent fn)
		{
			auto it = GuiMap.find(id);
			if (it != GuiMap.end())
				return false;

			GuiMap.insert(std::make_pair(id, fn));
			return true;
		}

		bool GuiControl::Unregister(int id)
		{
			auto it = GuiMap.find(id);
			if (it == GuiMap.end())
				return false;

			GuiMap.erase(it);
			return true;
		}

		tuple<bool, Error> GuiControl::Execute(int handle, int gui)
		{
			auto it = GuiMap.find(handle);

			try
			{
				if (it == GuiMap.end())
					return make_tuple(true, Error::EventNotFound);


				return it->second(handle, gui);
			}
			catch (...)
			{
				return make_tuple(false, Error::Exception);
			}
		}
	}
}
