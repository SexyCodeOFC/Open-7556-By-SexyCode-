#include "stdafx.h"
#include "CallBack.h"
#include "GuiControl.h"
#include "Gui.h"
#include "PacketControl.h"
#include "nativefunctions.h"
#include "Functions.h"

char* CallBack::RecvPacket(char* pMsg, int32_t pSize)
{
	auto header = reinterpret_cast<MSG_STANDARD*>(pMsg);
	return Packet::Recv::Factory::RecvEvent::PacketControl(header->Type, header);
	return pMsg;
}

void CallBack::SendPacket(MSG_STANDARD* pHeader, int pSize, PacketSide pSide)
{
	//auto R = Client::Packet::Send::Factory::SendEvent::instance().Execute(pHeader->PacketId, pHeader);
	Packet::Send::Factory::SendEvent::PacketControl(pHeader->Type, pHeader);
}

void CallBack::AddIndex(int32_t index, int32_t* value)
{
	switch (index)
	{
	case 4188: *value = RedSanta;
		break;
	case 4161:
	case 4187: *value = Purple_Rudolph;
		break;

	case 4162:  *value = Blue_Rudolph;
		break;

	case 4163: *value = White_Police;
		break;

	case 4164: *value = Black_Police;
		break;

	case 4165: *value = Blindness;
		break;

	case 4166: *value = Deafness;
		break;

	case 4167: *value = Hanbok;
		break;

	case 4168: *value = Rabbit_Girl;
		break;

	case 4169:
	case 4170: *value = ST_Set;
		break;

	case 4171: *value = Kingdom_Red;
		break;
	case 4172: *value = Kingdom_Blue;
		break;

	case 4173:
	case 4186: *value = Gandi;
		break;

	case 4174:
	case 4185: *value = Odin;
		break;

	case 4175: *value = Dancing_Girl;
		break;

	case 4176: *value = Rabbit;
		break;

	case 4177: *value = Oriental;
		break;

	case 4178: *value = Feudal;
		break;

	case 4179: *value = Feudal_F;
		break;

	case 4183: *value = Elegant;
		break;

	case 4180: *value = Plant;
		break;

	case 4181: *value = Succubus;
		break;

	case 4182: *value = Oriental_F;
		break;

	case 4184:
	case 4150: *value = Dosa;
		break;
	default:
		break;
	}
}

void CallBack::CorrectBone(int32_t index, int32_t* bone)
{
	switch (index)
	{
	case Valquiria:
	case Bruxa:
	case Romano:
	case Kalintz_F:
	case Deafness:
	case Rabbit_Girl:
	case Rabbit:
	case Oriental:
	case Plant:
	case Succubus:
		*bone = 0x1;
		break;

	case Draco:
	case Esqueleto:
	case Kalintz_M:
	case Feudal:
	case Kingdom_Blue:
	case Kingdom_Red:
	case Oriental_F: //novo 1
	case Elegant: //novo 2
	case Gandi: //novo 3
	case Purple_Rudolph: //novo 4
	case Black_Police: //novo 5
	case Blue_Rudolph: //novo 6
	case Hanbok: //novo 7
	case White_Police: //novo 8
	case Dancing_Girl: //hc tk
	case Dosa:
	case Blindness:
	case ST_Set:
	case Odin:
	case Feudal_F:
		*bone = 0x0;
		break;

	default:
		break;
	}
}

void CallBack::LoadFile(int32_t index, char* textureName, char* meshName)
{
	auto loadCostume = [textureName, meshName](char* texture, char* msh1, char* msh2, char* msh3, char* msh4, char* msh5, char* msh6)
	{
		auto counter = reinterpret_cast<int32_t*>(0x5EEECC);

		strcpy(textureName, texture);

		switch (*counter)
		{
		case 1:
			strcpy(meshName, msh1); *counter = 2;
			break;
		case 2:
			strcpy(meshName, msh2); *counter = 3;
			break;
		case 3:
			strcpy(meshName, msh3); *counter = 4;
			break;
		case 4:
			strcpy(meshName, msh4); *counter = 5;
			break;
		case 5:
			strcpy(meshName, msh5); *counter = 6;
			break;
		case 6:
			strcpy(meshName, msh6); *counter = 1;
			break;
		}
	};

	switch (index)
	{
	case Purple_Rudolph:
		loadCostume("mesh\\ch010157.wys", "mesh\\ch010157.msh", "mesh\\ch010257.msh", "mesh\\ch010357.msh", "mesh\\ch010457.msh", "mesh\\ch010557.msh", "mesh\\ch010657.msh"); //novo 4
		break;
	case Blue_Rudolph:
		loadCostume("mesh\\ch010156.wys", "mesh\\ch010156.msh", "mesh\\ch010256.msh", "mesh\\ch010356.msh", "mesh\\ch010456.msh", "mesh\\ch010556.msh", "mesh\\ch010656.msh"); //novo 6
		break;
	case White_Police:
		loadCostume("mesh\\ch010165.wys", "mesh\\ch010165.msh", "mesh\\ch010265.msh", "mesh\\ch010365.msh", "mesh\\ch010465.msh", "mesh\\ch010565.msh", "mesh\\ch010665.msh");  //novo 8
		break;
	case Black_Police:
		loadCostume("mesh\\ch010175.wys", "mesh\\ch010175.msh", "mesh\\ch010275.msh", "mesh\\ch010375.msh", "mesh\\ch010475.msh", "mesh\\ch010575.msh", "mesh\\ch010675.msh"); //novo 5
		break;
	case Blindness:
		loadCostume("mesh\\DeathCos2.wyt", "mesh\\ch010189.msh", "mesh\\ch010289.msh", "mesh\\ch010389.msh", "mesh\\ch010489.msh", "mesh\\ch010589.msh", "mesh\\ch010689.msh");
		break;
	case Deafness:
		loadCostume("mesh\\DeathCos.wyt", "mesh\\ch020189.msh", "mesh\\ch020289.msh", "mesh\\ch020389.msh", "mesh\\ch020489.msh", "mesh\\ch020589.msh", "mesh\\ch020689.msh");
		break;
	case Dosa:
		loadCostume("mesh\\ch010199.wyt", "mesh\\ch010199.msh", "mesh\\ch010299.msh", "mesh\\ch010399.msh", "mesh\\ch010499.msh", "mesh\\ch010599.msh", "mesh\\ch010699.msh");
		break;
	case Hanbok:
		loadCostume("mesh\\ch010159.wys", "mesh\\ch010159.msh", "mesh\\ch010259.msh", "mesh\\ch010359.msh", "mesh\\ch010459.msh", "mesh\\ch010559.msh", "mesh\\ch010659.msh"); //novo 7
		break;
	case Rabbit_Girl:
		loadCostume("mesh\\ch0101101.wys", "mesh\\ch0101101.msh", "mesh\\ch0102101.msh", "mesh\\ch0103101.msh", "mesh\\ch0104101.msh", "mesh\\ch0105101.msh", "mesh\\ch0106101.msh");
		break;
	case ST_Set:
		loadCostume("mesh\\ch0101102.wyt", "mesh\\ch0101102.msh", "mesh\\ch0102102.msh", "mesh\\ch0103102.msh", "mesh\\ch0104102.msh", "mesh\\ch0105102.msh", "mesh\\ch0106102.msh");
		break;
	case Kingdom_Red:
		loadCostume("mesh\\ch0101103.wyt", "mesh\\ch0101103.msh", "mesh\\ch0102103.msh", "mesh\\ch0103103.msh", "mesh\\ch0104103.msh", "mesh\\ch0105103.msh", "mesh\\ch0105103.msh");
		break;
	case Kingdom_Blue:
		loadCostume("mesh\\ch0102103.wyt", "mesh\\ch0101103.msh", "mesh\\ch0102103.msh", "mesh\\ch0103103.msh", "mesh\\ch0104103.msh", "mesh\\ch0105103.msh", "mesh\\ch0105103.msh");
		break;
	case Gandi:
		loadCostume("mesh\\ch010171.wys", "mesh\\ch010171.msh", "mesh\\ch010271.msh", "mesh\\ch010371.msh", "mesh\\ch010471.msh", "mesh\\ch010571.msh", "mesh\\ch010671.msh"); //novo 3
		break;
	case Odin:
		loadCostume("mesh\\ch0101106.wyt", "mesh\\ch0101106.msh", "mesh\\ch0102106.msh", "mesh\\ch0103106.msh", "mesh\\ch0104106.msh", "mesh\\ch0105106.msh", "mesh\\ch0106106.msh");
		break;
	case Rabbit:
		loadCostume("mesh\\ch0101107.wyt", "mesh\\ch0101107.msh", "mesh\\ch0102107.msh", "mesh\\ch0103107.msh", "mesh\\ch0104107.msh", "mesh\\ch0105107.msh", "mesh\\ch0106107.msh");
		break;
	case Oriental:
		loadCostume("mesh\\ch0101108.wyt", "mesh\\ch0101108.msh", "mesh\\ch0102108.msh", "mesh\\ch0103108.msh", "mesh\\ch0104108.msh", "mesh\\ch0105108.msh", "mesh\\ch0106108.msh");
		break;
	case Feudal:
		loadCostume("mesh\\ch0101109.wyt", "mesh\\ch0101109.msh", "mesh\\ch0102109.msh", "mesh\\ch0103109.msh", "mesh\\ch0104109.msh", "mesh\\ch0105109.msh", "mesh\\ch0106109.msh");
		break;
	case Feudal_F:
		loadCostume("mesh\\ch0101110.wyt", "mesh\\ch0101110.msh", "mesh\\ch0102110.msh", "mesh\\ch0103110.msh", "mesh\\ch0104110.msh", "mesh\\ch0105110.msh", "mesh\\ch0106110.msh");
		break;
	case Plant:
		loadCostume("mesh\\ch0101111.wyt", "mesh\\ch0101111.msh", "mesh\\ch0102111.msh", "mesh\\ch0103111.msh", "mesh\\ch0104111.msh", "mesh\\ch0105111.msh", "mesh\\ch0106111.msh");
		break;
	case Succubus:
		loadCostume("mesh\\ch0101112.wyt", "mesh\\ch0101112.msh", "mesh\\ch0102112.msh", "mesh\\ch0103112.msh", "mesh\\ch0104112.msh", "mesh\\ch0105112.msh", "mesh\\ch0106112.msh");
		break;
	case Oriental_F:
		loadCostume("mesh\\ch010155.wys", "mesh\\ch010155.msh", "mesh\\ch010255.msh", "mesh\\ch010355.msh", "mesh\\ch010455.msh", "mesh\\ch010555.msh", "mesh\\ch010655.msh"); //novo 1
		break;
	case Elegant:
		loadCostume("mesh\\ch010158.wys", "mesh\\ch010158.msh", "mesh\\ch010258.msh", "mesh\\ch010358.msh", "mesh\\ch010458.msh", "mesh\\ch010558.msh", "mesh\\ch010658.msh"); //novo 2
		break;

	default:
		break;
	}
}

int32_t CallBack::AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, DWORD* line1Color, DWORD* line2Color, DWORD* line3Color, DWORD* line4Color, DWORD* line5Color, DWORD* line6Color, DWORD* line7Color, DWORD* line8Color, DWORD* line9Color, DWORD* line10Color)
{
	memset(line1, 0x0, sizeof(line1));
	memset(line2, 0x0, sizeof(line2));
	memset(line3, 0x0, sizeof(line3));
	memset(line4, 0x0, sizeof(line4));
	memset(line5, 0x0, sizeof(line5));
	memset(line6, 0x0, sizeof(line6));
	memset(line7, 0x0, sizeof(line7));
	memset(line8, 0x0, sizeof(line8));
	memset(line9, 0x0, sizeof(line9));
	memset(line10, 0x0, sizeof(line10));

	try
	{
		if (item->sIndex == 508 || item->sIndex >= 526 && item->sIndex <= 528)
		{
			auto guild = &Global::ControlGuild;

			if (!guild->Index)
				return 0;

			sprintf_s(line1, 128, "Guild:__%s", guild->Name);
			*line1Color = White;


			if (guild->Clan == 7)
			{
				sprintf(line2, "Reino:__Hekalotia");
				*line2Color = Blue;
			}
			else if (guild->Clan == 8)
			{
				sprintf(line2, "Reino:__Akelonia");
				*line2Color = Red;
			}

			return 2;
		}

		if (item->sIndex == 509)
		{
			auto guild = &Global::ControlGuild;

			if (!guild->Index)
				return 0;

			sprintf_s(line1, 128, "Guild:__%s", guild->Name);
			*line1Color = White;

			sprintf_s(line2, 128, "GuildIndex:__%d", guild->Index);
			*line2Color = White;

			sprintf_s(line3, 128, "Fama Atual:__%d", guild->Fame);
			*line3Color = White;

			if (guild->Clan == 7)
			{
				sprintf(line4, "Reino:__Hekalotia");
				*line4Color = Blue;
			}
			else if (guild->Clan == 8)
			{
				sprintf(line4, "Reino:__Akelonia");
				*line4Color = Red;
			}

			return 4;
		}
		 
	}
	catch (...)
	{

	}
	return 0;
}


bool CallBack::SetVolatileMessageBoxText(int32_t itemID, char* text)
{
	try
	{

		if (itemID == 5422)
		{
			sprintf(text, "Deseja mudar a classe de seu personagem?");
			return true;
		}
		else if (itemID == 5423)
		{
			sprintf(text, "Deseja mudar o corpo de seu personagem?");
			return true;
		}
	}
	catch (...)
	{

	}
	return false;
}

int32_t CallBack::AddVolatileMessageItem(int32_t itemID)
{
	try
	{
		switch (itemID) {
		case 5401:
		case 5402:
		case 5403:
			return 1;
		}
		return 0;
	}
	catch (...)
	{

	}
	return 0;
}

bool CallBack::AddAmountItem(int32_t itemID)
{
	try
	{
		switch (itemID)
		{
		case 413:
			return true;
		case 419:
			return true;
		case 420:
			return true;
		case 412:
			return true;
		case 4017:
			return true;
		case 4018:
			return true;
		case 4019:
			return true;
		case 4020:
			return true;
		case 4117:
			return true;
		case 4118:
			return true;
		case 4119:
			return true;
		case 4120:
			return true;
		case 4121:
			return true;
		case 5440:
			return true;
		case 4140:
			return true;
		case 4016:
			return true;
		case 4041:
			return true;
		case 3314:
			return true;
		case 777:
			return true;
		case 3182:
			return true;
		case 5450:
			return true;
		case 3200:
			return true;
		case 3201:
			return true;
		case 3202:
			return true;
		case 3203:
			return true;
		case 3204:
			return true;
		case 3205:
			return true;
		case 5459:
			return true;
		case 5460:
			return true;
		case 5461:
			return true;
		case 3326:
			return true;
		case 1774:
			return true;
		case 5480:
			return true;
		case 4011:
			return true;
		case 4026:
			return true;
		case 4027:
			return true;
		case 4028:
			return true;
		case 4029:
			return true;
		case 454:
			return true;
		case 455:
			return true;
		case 5489:
			return true;
		case 4144:
			return true;
		case 3171:
			return true;
		case 3172:
			return true;
		case 2441:
			return true;
		case 2442:
			return true;
		case 2443:
			return true;
		case 2444:
			return true;
		case 5441:
			return true;
		case 5451:
			return true;
		case 5442:
			return true;
		case 5446:
			return true;
		case 5447:
			return true;
		case 5448:
			return true;
		case 5449:
			return true;
		case 5453:
			return true;
		case 5454:
			return true;

		}
	}
	catch (...)
	{

	}
	return false;
}

int32_t CallBack::AddItemSanc(STRUCT_ITEM* item, char* str)
 {
		auto uni = BASE_GetItemAmount(item);

		if (uni > 0) // Unidades
		{
			sprintf(str, "%d", uni);
			return uni;
		}
		 
		auto level = item->stEffect[1].cEffect;

		static int ids[] = { 2360, 2361, 2362, 2363, 2364, 2365, 2366, 2367, 2368,
			2369, 2370, 2371, 2372, 2373, 2374, 2375,
			2376, 2377, 2378, 2379, 2380, 2381, 2382,
			2383, 2384, 2385, 2386, 2387, 2388 };

		for (int i = 0; i < 29; i++)
			if (item->sIndex == ids[i])
			{
				if (level > 0)
				{

					sprintf(str, "Lv:%d", level);
					return level;

				}
			}

		auto ref = BASE_GetItemSanc(item);

		if (ref >= 0)
		{
			if (ref > 10)
			{
				if (ref >= 10 && ref < 14)
					ref = 10;
				else if (ref >= 14 && ref < 18)
					ref = 11;
				else if (ref >= 18 && ref < 22)
					ref = 12;
				else if (ref >= 22 && ref < 26)
					ref = 13;
				else if (ref >= 26 && ref < 30)
					ref = 14;
				else if (ref >= 30 && ref < 34)
					ref = 15;
			}
			sprintf(str, "+%d", ref);
			return ref;
		}

		return -1;
	}
bool CallBack::SetItemPriceString(STRUCT_ITEM* item, char* str)
{

#pragma region DIVERSOS EM GOLD

	if (item->sIndex == 4011)
	{
		sprintf(str, "Gold: 1.000.000.000");
		return true;
	}
#pragma endregion


#pragma region ARMIA STORE

	else if (item->sIndex == 3379) // POÇAO DIVINA 7 DIAS
	{
		sprintf(str, "Preço: 350 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3380) // POÇAO DIVINA 15 DIAS
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3381) // POÇAO DIVINA 30 DIAS
	{
		sprintf(str, "Preço: 1000 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3364) // POÇAO SAÚDE 7 DIAS
	{
		sprintf(str, "Preço: 200 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3365) // POÇAO SAÚDE 15 DIAS
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3319) // POÇAO KAPPA 20HORAS
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3313) // POÇAO VIGOR 20HORAS
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3206) // JOIA DO PODER
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3207) // JOIA DA ARMAZENAGEM
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3208) // JOIA DA PRECISÃO
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3209) // JOIA DA MAGIA
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
#pragma endregion


#pragma region AZRAN STORE

	else if (item->sIndex == 3173) // PERGAMINHO AGUA N
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 777) // PERGAMINHO AGUA M
	{
		sprintf(str, "Preço: 200 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3182) // PERGAMINHO AGUA A
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3172) // CARTA DE DUELO N
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3171) // CARTA DE DUELO M
	{
		sprintf(str, "Preço: 200 Donate Coins");
		return true;
	}
	else if (item->sIndex == 1731) // CARTA DE DUELO A
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3324) // PESADELO N
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3325) // PESADELO M
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3326) // PESADELO A
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
	else if (item->sIndex == 4019) // REPLATION D
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 4020) // REPLATION E
	{
		sprintf(str, "Preço: 200 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3900) // FADA VERDE 3D
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3901) // FADA AZUL 3D
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3902) // FADA VERMELHA 3D
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3916) // FADA DO VALE 7D
	{
		sprintf(str, "Preço: 700 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3467) // BOLSA ANDARILHO
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex >= 4151 && item->sIndex <= 4158) // TRAJES SIMPLES
	{
		sprintf(str, "Preço: 800 Donate Coins");
		return true;
	}
	else if (item->sIndex >= 4159 && item->sIndex <= 4188) // TRAJES PREMIUM
	{
		sprintf(str, "Preço: 1200 Donate Coins");
		return true;
	}
	else if (item->sIndex == 5451) // FRAGMENTO DE CHAVE
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 5442) // TESOURO DE SET
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
#pragma endregion


#pragma region ERION STORE

	else if (item->sIndex == 3344) // CATALIZADOR KAPEL
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3345) // CATALIZADOR
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3346) // CATALIZADOR
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3347) // CATALIZADOR
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
	else if (item->sIndex >= 3351 && item->sIndex <= 3356) // RESTAURADORES
	{
		sprintf(str, "Preço: 1500 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3373) // RAÇAO CAVALO PACK
	{
		sprintf(str, "Preço: 50 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3376) // RAÇAO UNI PACK
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3377) // RAÇAO GRIFO PACK
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3438) // ACELERADOR
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}

	else if (item->sIndex == 4128) // ESFERA N
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}

	else if (item->sIndex == 4129) // ESFERA M
	{
		sprintf(str, "Preço: 300 Donate Coins");
		return true;
	}

	else if (item->sIndex == 4130) // ESFERA A
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
#pragma endregion


#pragma region NIPPLE STORE

	else if (item->sIndex >= 3397 && item->sIndex <= 3406) // TINTURAS
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3417) // REMOVEDOR DE TINTURA
	{
		sprintf(str, "Preço: 500 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3343) // PERGAMINHO DO PERDAO
	{
		sprintf(str, "Preço: 700 Donate Coins");
		return true;
	}
	else if (item->sIndex == 4140) // BAU EXP
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 3314) // FRANGO PVE
	{
		sprintf(str, "Preço: 100 Donate Coins");
		return true;
	}
	else if (item->sIndex == 1739) // CHOCOLATE DO AMOR
	{
		sprintf(str, "Preço: 100");
		return true;
	}
	else if (item->sIndex == 4145) // CORAÇAO DOCE
	{
		sprintf(str, "Preço: 100");
		return true;
	}
#pragma endregion

	return false;
}

bool CallBack::NewItensDay(int32_t Item)
{
	return false;
}

bool CallBack::Alquimista_FaceMap(int mapX, int mapY, int face)
{
	if (face == 200)
		if (mapX == 16 && mapY == 16)
			return true;

	return false;
}

int32_t CallBack::Alquimista_CompareItem(char* str, STRUCT_ITEM* item, int32_t loopIndex)
{
	auto amount = BASE_GetItemAmount(item);

	if (loopIndex == 0 && item->sIndex == 5409)
	{
		if (amount == 20)
			return 1;
		else
			return 0;
	}

	if (loopIndex == 1 && item->sIndex == 5410)
	{
		if (amount == 20)
			return 1;
		else
			return 0;
	}

	if (loopIndex == 2 && item->sIndex == 1742)
		return 1;

	if (loopIndex >= 3 && loopIndex <= 6)
	{
		if (item->sIndex == 4127)
			return 1;
		else
			return 0;
	}

	return 0;
}

bool CallBack::Compositor_FaceMap(int mapX, int mapY, int face)
{
	return false;
}

int32_t CallBack::Compositor_CompareItem(char* str, STRUCT_ITEM* item, int32_t loopIndex)
{
	return int32_t();
}

bool CallBack::GreenTimeMap(int mapX, int mapY)
{
	return false;
}

void CallBack::HKD_Att_Label_EXP()
{

}

void CallBack::HKD_Start()
{
	static bool Startado = false;

	if (!Startado)
	{
		Startado = true;

		/*Alteração no Server List e Server Name*/
		static auto ServerList = reinterpret_cast<STRUCT_SERVERLIST*>(0x972FF8);
		static auto ServerName = reinterpret_cast<STRUCT_SERVERNAME*>(0x13FA84D);

#ifdef DEBUG
		//memcpy(ServerList->ServerList[0].IP, IPTeste, 16); //Test
		//memcpy(ServerList->ServerList[1].IP, IPServer, 16); //Test
		//memcpy(ServerList->ServerList[2].IP, IPLocal, 16); //Test
		//
		//memcpy(ServerName->ServerName[0].Nome, "Local", 9);  //Local
		//memcpy(ServerName->ServerName[0].Nome, "Oficial", 9);  //Local
		//memcpy(ServerName->ServerName[0].Nome, "Test", 9);  //Local
#else
		memcpy(ServerList->ServerList[1].IP, IPServer, 16); //Test
#endif // DEBUG



		memcpy(ServerName->ServerName[1].Nome, "WYD Open 756", 9);	  //Servidor
		memcpy(ServerName->ServerName[2].Nome, "WYD Open 756 ", 9);  //Novato
		memcpy(ServerName->ServerName[3].Nome, "WYD Open 756 ", 9);	  //Servidor
	}

	try
	{


	}
	catch (...)
	{

	}
}

void CallBack::HKD_Open()
{
	static bool Aberto = false;

	if (!Aberto)
	{
		Aberto = true;

		static auto JanelaNome = reinterpret_cast<STRUCT_NOMEJANELA*>(0x5F9320);
		memcpy(JanelaNome->Nome, "WYD Open 756", 20);
	}
}

void  CallBack::HKD_Create_Scene_World(int arg1, int arg2, int arg3, int arg4)
{
	try
	{
		return GuiControl::Event::GuiControl::instance().Create_Scene_World(arg1, arg2, arg3, arg4);
	}
	catch (...)
	{

	}
}

void CallBack::HKD_CallBack_Handle_Click(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)
{
	printf("\n	Handle Elemento: 0x%X\n\n", arg2);
}

void CallBack::HKD_CallBack_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)
{

}

void CallBack::HKD_CallBack_Inf_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5)
{
	return;

	if (arg1 == 0x201 || arg1 == 0x202)
		printf("\n{"
			"	ClickStatus: 0x%X\n"
			"	Mouse: %d\n"
			"	X: %d\n"
			"	Y: %d\n"
			"	0x%X\n"
			"\n}", arg1, arg2, arg3, arg4, arg5);
}

void CallBack::HKD_CallBack_Event_Click(int handle, int gui, int clickstatus)
{
	try
	{
		static bool ClickLiberado;

		GUI_BUTTON* Button = (GUI_BUTTON*)gui;

		if (clickstatus == 0x200)
			return;

		if (clickstatus == 0x202)
			ClickLiberado = true;


		if (Button->MouseOver == 1 && clickstatus == 0x202 && ClickLiberado)
		{
			auto Result = GuiControl::Factory::GuiControl::instance().Execute(Button->getHandle(), gui);

			if (!get<0>(Result) && get<1>(Result) != NoError)
				return;
		}
	}
	catch (...)
	{

	}
}

bool CallBack::HKD_CallBack_Event_Esc()
{
	return false;
}

void CallBack::HKD_CallBack_Label(char* arg1)
{
}

void CallBack::HKD_Create_Scene_Login_After()
{
	try
	{
		return GuiControl::Event::GuiControl::instance().Create_Scene_Login();
	}
	catch (...)
	{

	}
}

void CallBack::HKD_Create_Scene_Login(int arg1, int arg2, int arg3, int arg4)
{
}

bool CallBack::HKD_ItemTempo(int index)
{
	if (index == 5414)
		return true;

	return false;
}

void CallBack::HKD_OpenInventory(UINT32 Open)
{
}

int CallBack::HKD_SendChat(char* command)
{  
	if (strcmp(command, "/agrupador") == 0)
	{

		uint16_t itemId = 413;
		uint16_t itemId2 = 412;
		uint16_t itemId3 = 4019;
		uint16_t itemId4 = 4020;
		uint16_t itemId5 = 419;
		uint16_t itemId6 = 420;
		uint16_t itemId7 = 4117;
		uint16_t itemId8 = 4118;
		uint16_t itemId9 = 4119;
		uint16_t itemId10 = 4120;
		uint16_t itemId11 = 4121;
		uint16_t itemId12 = 5453;
		uint16_t itemId13 = 5454;
		switch (agrupar_item)
		{
		case true:
			Func::SendMessageExp(Red, "Auto Agrupador Desativado");
			agrupar_item = false;
			break;

		case false:
			Func::SendMessageExp(LightGreen, "Auto Agrupador Ativado");
			agrupar_item = true;
			lista_itens_agrupar.push_back(itemId);
			lista_itens_agrupar.push_back(itemId2);
			lista_itens_agrupar.push_back(itemId3);
			lista_itens_agrupar.push_back(itemId4);
			lista_itens_agrupar.push_back(itemId5);
			lista_itens_agrupar.push_back(itemId6);
			lista_itens_agrupar.push_back(itemId7);
			lista_itens_agrupar.push_back(itemId8);
			lista_itens_agrupar.push_back(itemId9);
			lista_itens_agrupar.push_back(itemId10);
			lista_itens_agrupar.push_back(itemId11);
			lista_itens_agrupar.push_back(itemId12);
			lista_itens_agrupar.push_back(itemId13);

			break;
		}
		return false;
	}

	/*if (strcmp(command, "/macroperga") == 0)
	{
		switch (MacroPega)
		{
		case true:
			Func::SendMessageExp(Red, "Macro de Pergaminho Desativado");
			MacroPega = false;
			break;

		case false:

			Func::SendMessageExp(LightGreen, "Macro de Pergaminho Ativado");
			MacroPega = true;
			break;
		}
		return false;
	}*/
	return true;
}

auto Contador = 0;
void CallBack::HKD_CheckJanelas(UINT32 addr1)
{
	try
	{
		if (!(Contador % 500))
		{
			auto AtaqueLabel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(0x100C5);
			if (AtaqueLabel != NULL)
			{

				auto AtaqueLabelPanel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690007);
				if (AtaqueLabelPanel != NULL)
					AtaqueLabelPanel->setText(AtaqueLabel->getText(), 0);
			}

			auto AtqMagLabel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(0x100C7);
			if (AtqMagLabel != NULL)
			{

				auto AtqMagLabelPanel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690008);
				if (AtqMagLabelPanel != NULL)
					AtqMagLabelPanel->setText(AtqMagLabel->getText(), 0);
			}

			auto DefesaLabel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(0x100CB);
			if (DefesaLabel != NULL)
			{

				auto DefesaLabelPanel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690009);
				if (DefesaLabelPanel != NULL)
					DefesaLabelPanel->setText(DefesaLabel->getText(), 0);

				DefesaLabelPanel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690010);
				if (DefesaLabelPanel != NULL)
					DefesaLabelPanel->setText(DefesaLabel->getText(), 0);
			}


			auto ExpAtualLabel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(0x100AE);
			auto ExpMetaLabel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(0x100AF);

			if (ExpAtualLabel != NULL && ExpMetaLabel != NULL)
			{
				auto ExpAtualPanel = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690012);
				if (ExpAtualPanel != NULL)
					ExpAtualPanel->setText(Func::stringFormat("%s / %s", ExpAtualLabel->getText(), ExpMetaLabel->getText()), 0);
			}

			auto AtalhoQ = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690013);
			auto AtalhoW = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690014);
			auto AtalhoE = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690015);
			auto AtalhoV = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690016);
			auto AtalhoB = (GUI_LABEL*)Game::getInstance()->pInterface->getGui(690017);

			if (AtalhoQ != NULL && AtalhoW != NULL && AtalhoE != NULL && AtalhoV != NULL && AtalhoB != NULL)
			{

				auto Inventario_1 = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10600);
				auto Inventario_2 = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10601);
				auto Inventario_3 = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10602);
				auto Inventario_4 = (GUI_LISTBOX*)Game::getInstance()->pInterface->getGui(0x10603);

				auto Slots_Inv_1 = *(int*)((int)Inventario_1 + 0x1FC + 4 * 0);
				auto Slots_Inv_2 = *(int*)((int)Inventario_2 + 0x1FC + 4 * 0);
				auto Slots_Inv_3 = *(int*)((int)Inventario_3 + 0x1FC + 4 * 0);
				auto Slots_Inv_4 = *(int*)((int)Inventario_4 + 0x1FC + 4 * 0);

				auto QuantidadePotQ = 0;
				auto QuantidadePotW = 0;
				auto QuantidadeErvaE = 0;
				auto QuantidadeRacaoV = 0;
				auto QuantidadePergaB = 0;

				for (auto i = 1; i <= 15; i++)
				{
					auto Slot_Inv_1_Addr = *(int*)((int)Inventario_1 + 0x1FC + 4 * i);
					auto Slot_Inv_2_Addr = *(int*)((int)Inventario_2 + 0x1FC + 4 * i);
					auto Slot_Inv_3_Addr = *(int*)((int)Inventario_3 + 0x1FC + 4 * i);
					auto Slot_Inv_4_Addr = *(int*)((int)Inventario_4 + 0x1FC + 4 * i);

					if (Slot_Inv_1_Addr != 0)
					{
						auto Addr_Base = Slot_Inv_1_Addr;
						auto Elemento_Item_Slot = *(int*)((int)Addr_Base + 0x1B0);
						auto Elemento_Item_Slot_addr = (*(int*)((int)Elemento_Item_Slot + 0x1B0));
						STRUCT_ITEM Item_Slot = *(STRUCT_ITEM*)((int)Elemento_Item_Slot_addr);

						auto IsPotQ =
							(
								Item_Slot.sIndex == 400 ||
								Item_Slot.sIndex == 401 ||
								Item_Slot.sIndex == 402 ||
								Item_Slot.sIndex == 403 ||
								Item_Slot.sIndex == 404
								);

						auto IsPotW =
							(
								Item_Slot.sIndex == 405 ||
								Item_Slot.sIndex == 406 ||
								Item_Slot.sIndex == 407 ||
								Item_Slot.sIndex == 408 ||
								Item_Slot.sIndex == 409
								);

						auto IsErva =
							(
								Item_Slot.sIndex == 415
								);

						auto IsRacao =
							(
								Item_Slot.sIndex >= 2420 &&
								Item_Slot.sIndex <= 2432
								);

						auto IsPerga =
							(
								Item_Slot.sIndex == 777 ||
								Item_Slot.sIndex == 3173
								);


						if (IsPotQ || IsPotW || IsErva || IsRacao || IsPerga)
						{
							auto Quantidade = 0;
							if (Item_Slot.EF1 == 61)
								Quantidade = Item_Slot.EFV1;
							else if (Item_Slot.EF2 == 61)
								Quantidade = Item_Slot.EFV2;
							else if (Item_Slot.EF3 == 61)
								Quantidade = Item_Slot.EFV3;
							else
								Quantidade = 1;

							if (IsPotQ)
								QuantidadePotQ += Quantidade;
							else if (IsPotW)
								QuantidadePotW += Quantidade;
							else if (IsErva)
								QuantidadeErvaE += Quantidade;
							else if (IsRacao)
								QuantidadeRacaoV += Quantidade;
							else if (IsPerga)
								QuantidadePergaB += Quantidade;
						}

					}
					if (Slot_Inv_2_Addr != 0)
					{
						auto Addr_Base = Slot_Inv_2_Addr;
						auto Elemento_Item_Slot = *(int*)((int)Addr_Base + 0x1B0);
						auto Elemento_Item_Slot_addr = (*(int*)((int)Elemento_Item_Slot + 0x1B0));
						STRUCT_ITEM Item_Slot = *(STRUCT_ITEM*)((int)Elemento_Item_Slot_addr);

						auto IsPotQ =
							(
								Item_Slot.sIndex == 400 ||
								Item_Slot.sIndex == 401 ||
								Item_Slot.sIndex == 402 ||
								Item_Slot.sIndex == 403 ||
								Item_Slot.sIndex == 404
								);

						auto IsPotW =
							(
								Item_Slot.sIndex == 405 ||
								Item_Slot.sIndex == 406 ||
								Item_Slot.sIndex == 407 ||
								Item_Slot.sIndex == 408 ||
								Item_Slot.sIndex == 409
								);

						auto IsErva =
							(
								Item_Slot.sIndex == 415
								);

						auto IsRacao =
							(
								Item_Slot.sIndex >= 2420 &&
								Item_Slot.sIndex <= 2432
								);

						auto IsPerga =
							(
								Item_Slot.sIndex == 777 ||
								Item_Slot.sIndex == 3173
								);


						if (IsPotQ || IsPotW || IsErva || IsRacao || IsPerga)
						{
							auto Quantidade = 0;
							if (Item_Slot.EF1 == 61)
								Quantidade = Item_Slot.EFV1;
							else if (Item_Slot.EF2 == 61)
								Quantidade = Item_Slot.EFV2;
							else if (Item_Slot.EF3 == 61)
								Quantidade = Item_Slot.EFV3;
							else
								Quantidade = 1;

							if (IsPotQ)
								QuantidadePotQ += Quantidade;
							else if (IsPotW)
								QuantidadePotW += Quantidade;
							else if (IsErva)
								QuantidadeErvaE += Quantidade;
							else if (IsRacao)
								QuantidadeRacaoV += Quantidade;
							else if (IsPerga)
								QuantidadePergaB += Quantidade;
						}
					}
					if (Slot_Inv_3_Addr != 0)
					{
						auto Addr_Base = Slot_Inv_3_Addr;
						auto Elemento_Item_Slot = *(int*)((int)Addr_Base + 0x1B0);
						auto Elemento_Item_Slot_addr = (*(int*)((int)Elemento_Item_Slot + 0x1B0));
						STRUCT_ITEM Item_Slot = *(STRUCT_ITEM*)((int)Elemento_Item_Slot_addr);

						auto IsPotQ =
							(
								Item_Slot.sIndex == 400 ||
								Item_Slot.sIndex == 401 ||
								Item_Slot.sIndex == 402 ||
								Item_Slot.sIndex == 403 ||
								Item_Slot.sIndex == 404
								);

						auto IsPotW =
							(
								Item_Slot.sIndex == 405 ||
								Item_Slot.sIndex == 406 ||
								Item_Slot.sIndex == 407 ||
								Item_Slot.sIndex == 408 ||
								Item_Slot.sIndex == 409
								);

						auto IsErva =
							(
								Item_Slot.sIndex == 415
								);

						auto IsRacao =
							(
								Item_Slot.sIndex >= 2420 &&
								Item_Slot.sIndex <= 2432
								);

						auto IsPerga =
							(
								Item_Slot.sIndex == 777 ||
								Item_Slot.sIndex == 3173
								);


						if (IsPotQ || IsPotW || IsErva || IsRacao || IsPerga)
						{
							auto Quantidade = 0;
							if (Item_Slot.EF1 == 61)
								Quantidade = Item_Slot.EFV1;
							else if (Item_Slot.EF2 == 61)
								Quantidade = Item_Slot.EFV2;
							else if (Item_Slot.EF3 == 61)
								Quantidade = Item_Slot.EFV3;
							else
								Quantidade = 1;

							if (IsPotQ)
								QuantidadePotQ += Quantidade;
							else if (IsPotW)
								QuantidadePotW += Quantidade;
							else if (IsErva)
								QuantidadeErvaE += Quantidade;
							else if (IsRacao)
								QuantidadeRacaoV += Quantidade;
							else if (IsPerga)
								QuantidadePergaB += Quantidade;
						}
					}
					if (Slot_Inv_4_Addr != 0)
					{
						auto Addr_Base = Slot_Inv_4_Addr;
						auto Elemento_Item_Slot = *(int*)((int)Addr_Base + 0x1B0);
						auto Elemento_Item_Slot_addr = (*(int*)((int)Elemento_Item_Slot + 0x1B0));
						STRUCT_ITEM Item_Slot = *(STRUCT_ITEM*)((int)Elemento_Item_Slot_addr);

						auto IsPotQ =
							(
								Item_Slot.sIndex == 400 ||
								Item_Slot.sIndex == 401 ||
								Item_Slot.sIndex == 402 ||
								Item_Slot.sIndex == 403 ||
								Item_Slot.sIndex == 404
								);

						auto IsPotW =
							(
								Item_Slot.sIndex == 405 ||
								Item_Slot.sIndex == 406 ||
								Item_Slot.sIndex == 407 ||
								Item_Slot.sIndex == 408 ||
								Item_Slot.sIndex == 409
								);

						auto IsErva =
							(
								Item_Slot.sIndex == 415
								);

						auto IsRacao =
							(
								Item_Slot.sIndex >= 2420 &&
								Item_Slot.sIndex <= 2432
								);

						auto IsPerga =
							(
								Item_Slot.sIndex == 777 ||
								Item_Slot.sIndex == 3173
								);


						if (IsPotQ || IsPotW || IsErva || IsRacao || IsPerga)
						{
							auto Quantidade = 0;
							if (Item_Slot.EF1 == 61)
								Quantidade = Item_Slot.EFV1;
							else if (Item_Slot.EF2 == 61)
								Quantidade = Item_Slot.EFV2;
							else if (Item_Slot.EF3 == 61)
								Quantidade = Item_Slot.EFV3;
							else
								Quantidade = 1;

							if (IsPotQ)
								QuantidadePotQ += Quantidade;
							else if (IsPotW)
								QuantidadePotW += Quantidade;
							else if (IsErva)
								QuantidadeErvaE += Quantidade;
							else if (IsRacao)
								QuantidadeRacaoV += Quantidade;
							else if (IsPerga)
								QuantidadePergaB += Quantidade;
						}
					}
				}

				char Texto[30];
				memset(Texto, 0, 30);
				sprintf(Texto, "%d", QuantidadePotQ);
				AtalhoQ->setText(Texto, 0);

				memset(Texto, 0, 30);
				sprintf(Texto, "%d", QuantidadePotW);
				AtalhoW->setText(Texto, 0);

				memset(Texto, 0, 30);
				sprintf(Texto, "%d", QuantidadeErvaE);
				AtalhoE->setText(Texto, 0);

				memset(Texto, 0, 30);
				sprintf(Texto, "%d", QuantidadeRacaoV);
				AtalhoV->setText(Texto, 0);

				memset(Texto, 0, 30);
				sprintf(Texto, "%d", QuantidadePergaB);
				AtalhoB->setText(Texto, 0);
			}
		}


		Contador++;
	}
	catch (...)
	{

	}
}
