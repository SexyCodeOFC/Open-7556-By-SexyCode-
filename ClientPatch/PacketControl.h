#pragma once
#include <functional>
#include <map>

namespace Packet
{
	namespace Recv
	{
		namespace Event
		{
			class RecvEvent : public Singleton<RecvEvent>
			{
			protected:
				friend class Singleton<RecvEvent>;
				RecvEvent();
				virtual ~RecvEvent() {}
				RecvEvent(const RecvEvent&) = delete;
				RecvEvent& operator=(const RecvEvent&) = delete;

			public:
				static tuple<char*, Error> ProtectPacket(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> ChatColor(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> UpdateMedalGuild(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> Grupo(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> Donate(int id, MSG_STANDARD* packet); 
				static tuple<char*, Error> ItemAmount(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> Guild(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> ItemQuest(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> RecvSpecialChat(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> _RoyalBit(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> StoreInfor(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> ConnectionValidated(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> DropItem(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> GrupoInformação(int id, MSG_STANDARD* packet);
				static tuple<char*, Error> Derrubar(int id, MSG_STANDARD* packet);


			};
		}

		namespace Factory
		{
			class RecvEvent : public Singleton<RecvEvent>
			{
			protected:
				friend class Singleton<RecvEvent>;
				RecvEvent();
				virtual ~RecvEvent() {}
				RecvEvent(const RecvEvent&) = delete;
				RecvEvent& operator=(const RecvEvent&) = delete;
			public:
				using fpRecvEvent = std::function<std::tuple<char*, Error>(int, MSG_STANDARD*)>;
			private:
				std::map<int, fpRecvEvent> RecvMap; //Packet id, Packet size,
			public:
				bool Register(int id, fpRecvEvent fn);
				bool Unregister(int id);
				tuple<char*, Error> Execute(int id, MSG_STANDARD* packet);

				static char* PacketControl(int id, MSG_STANDARD* packet);
			};
		}
	}

	namespace Send
	{
		namespace Event
		{
			class SendEvent : public Singleton<SendEvent>
			{
			protected:
				friend class Singleton<SendEvent>;
				SendEvent();
				virtual ~SendEvent() {}
				SendEvent(const SendEvent&) = delete;
				SendEvent& operator=(const SendEvent&) = delete;
			public:
				static tuple<MSG_STANDARD*, Error> Send_Login(int id, MSG_STANDARD* packet);
				static tuple<MSG_STANDARD*, Error> Send_Numeric(int id, MSG_STANDARD* packet);
			};
		}

		namespace Factory
		{
			class SendEvent : public Singleton<SendEvent>
			{
			protected:
				friend class Singleton<SendEvent>;
				SendEvent();
				virtual ~SendEvent() {}
				SendEvent(const SendEvent&) = delete;
				SendEvent& operator=(const SendEvent&) = delete;
			public:
				using fpSendEvent = std::function<std::tuple<MSG_STANDARD*, Error>(int, MSG_STANDARD*)>;
			private:
				std::map<int, fpSendEvent> SendMap; //Packet id, Packet size,
			public:
				bool Register(int id, fpSendEvent fn);
				bool Unregister(int id);
				tuple<MSG_STANDARD*, Error> Execute(int id, MSG_STANDARD* packet);

				static MSG_STANDARD* PacketControl(int id, MSG_STANDARD* packet);
			};
		}

	}
}
