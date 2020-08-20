#pragma once

namespace GuiControl
{
	namespace Event
	{
		class GuiControl : public Singleton<GuiControl>
		{
		protected:
			friend class Singleton<GuiControl>;
			GuiControl();
			virtual ~GuiControl() {}
			GuiControl(const GuiControl&) = delete;
			GuiControl& operator=(const GuiControl&) = delete;
		public:
			void Create_Scene_World(int arg1, int arg2, int arg3, int arg4);
			void Create_Scene_Login();
		};
	}

	namespace EventHandle
	{
		class Handle
		{
		public:
			static tuple<bool, Error> DonateControl(int handle, int gui);
			static tuple<bool, Error> SecurityControl(int handle, int gui);
			static tuple<bool, Error> SaveAccount(int handle, int gui);
			static tuple<bool, Error> AutoConnectAccount(int handle, int gui);
			static tuple<bool, Error> AutoGroup(int handle, int gui);
		};
	}

	namespace Factory
	{
		class GuiControl : public Singleton<GuiControl>
		{
		protected:
			friend class Singleton<GuiControl>;
			GuiControl();
			virtual ~GuiControl() {}
			GuiControl(const GuiControl&) = delete;
			GuiControl& operator=(const GuiControl&) = delete;

		public:
			using fpGuiEvent = std::function<std::tuple<bool, Error>(int, int)>;
		private:
			std::map<int, fpGuiEvent> GuiMap; //Packet id, Packet size,
		public:
			bool RegisterRange(const int minIndex, const int maxIndex, fpGuiEvent fn);
			bool RegisterRange(const std::initializer_list<int>& IndexRange, fpGuiEvent fn);
			bool unRegisterRange(const int minIndex, const int maxIndex);
			bool unRegisterRange(const std::initializer_list<int>& IndexRange);

			bool Register(int id, fpGuiEvent fn);
			bool Unregister(int id);
			tuple<bool, Error> Execute(int handle, int gui);
		};
	}
}

