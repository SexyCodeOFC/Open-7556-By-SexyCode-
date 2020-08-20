#include "stdafx.h"
#include "Volatiles.h"
#include "Functions.h"

bool Volatiles::Feijoes(int32_t client, p373h* packet)
{
	auto mob = GetMobFromIndex(client);
	auto user = Func::GetUserFromIndex(client);
	auto srcItem = GetItemPointer(&mob->MOB, user->Cargo, packet->Src.Type, packet->Src.Slot);
	auto dstItem = GetItemPointer(&mob->MOB, user->Cargo, packet->Dst.Type, packet->Dst.Slot);

	auto result = true;

	if (packet->Dst.Type == (int)SlotType::Equipment && packet->Src.Type == (int)SlotType::Inventory)
	{
		const auto index = srcItem->sIndex - 3407;
		
		if (index >= 0 && index <= 10)
		{
			auto canGo = false;
			if (packet->Dst.Slot == 7)
			{
				auto iList = Func::GetItemListItem(dstItem->sIndex);

				if (iList->Pos == Shield)
					canGo = true;
			}
			else if (packet->Dst.Slot >= 0 && packet->Dst.Slot <= 5)
				canGo = true;

			if (canGo)
			{
				auto changed = false;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < sizeof(g_RefineTable) / sizeof(decltype(g_RefineTable[0])); j++)
					{
						if (dstItem->stEffect[i].cEffect == g_RefineTable[j])
						{
							dstItem->stEffect[i].cEffect = g_RefineTable[index];
							changed = true;
							break;
						}
					}

					if (changed)
						break;
				}

				if (changed)
				{
					Func::AmountMinus(srcItem);
					SendItem(client, packet->Dst.Type, packet->Dst.Slot, dstItem);
					SendItem(client, packet->Src.Type, packet->Src.Slot, srcItem);

					char buffer[180];
					GetCreateMob(client, buffer);
					GridMulticast(mob->TargetX, mob->TargetY, buffer, 0);

					SendClientMessage(client, "Successo!");
					return result;
				}
			}
		}
		SendClientMessage(client, "Uso somente para equipamentos.");
		return result;
	}
	SendClientMessage(client, "Ocorreu um erro. Contate o suporte.");
	return result;
}
