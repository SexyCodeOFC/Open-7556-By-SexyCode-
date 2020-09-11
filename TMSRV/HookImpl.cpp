#include "stdafx.h"
#include "HookImpl.h"
#include "Functions.h"
#include "Volatiles.h"
#include "..\include\packetstruct.h"

typedef struct _HEADER
{
	short		  Size;
	char		  KeyWord;
	char		  CheckSum;
	short		  Type;
	short		  ID;
	unsigned int  ClientTick;
} HEADER, * PHEADER;

unsigned char pKeyWord[512] = { // 7.xx keys
	0x84, 0x87, 0x37, 0xd7, 0xea, 0x79, 0x91, 0x7d, 0x4b, 0x4b, 0x85, 0x7d, 0x87, 0x81, 0x91, 0x7c, 0x0f, 0x73, 0x91, 0x91, 0x87, 0x7d, 0x0d, 0x7d, 0x86, 0x8f, 0x73, 0x0f, 0xe1, 0xdd, 0x85, 0x7d,
	0x05, 0x7d, 0x85, 0x83, 0x87, 0x9c, 0x85, 0x33, 0x0d, 0xe2, 0x87, 0x19, 0x0f, 0x79, 0x85, 0x86, 0x37, 0x7d, 0xd7, 0xdd, 0xe9, 0x7d, 0xd7, 0x7d, 0x85, 0x79, 0x05, 0x7d, 0x0f, 0xe1, 0x87, 0x7e,
	0x23, 0x87, 0xf5, 0x79, 0x5f, 0xe3, 0x4b, 0x83, 0xa3, 0xa2, 0xae, 0x0e, 0x14, 0x7d, 0xde, 0x7e, 0x85, 0x7a, 0x85, 0xaf, 0xcd, 0x7d, 0x87, 0xa5, 0x87, 0x7d, 0xe1, 0x7d, 0x88, 0x7d, 0x15, 0x91,
	0x23, 0x7d, 0x87, 0x7c, 0x0d, 0x7a, 0x85, 0x87, 0x17, 0x7c, 0x85, 0x7d, 0xac, 0x80, 0xbb, 0x79, 0x84, 0x9b, 0x5b, 0xa5, 0xd7, 0x8f, 0x05, 0x0f, 0x85, 0x7e, 0x85, 0x80, 0x85, 0x98, 0xf5, 0x9d,
	0xa3, 0x1a, 0x0d, 0x19, 0x87, 0x7c, 0x85, 0x7d, 0x84, 0x7d, 0x85, 0x7e, 0xe7, 0x97, 0x0d, 0x0f, 0x85, 0x7b, 0xea, 0x7d, 0xad, 0x80, 0xad, 0x7d, 0xb7, 0xaf, 0x0d, 0x7d, 0xe9, 0x3d, 0x85, 0x7d,
	0x87, 0xb7, 0x23, 0x7d, 0xe7, 0xb7, 0xa3, 0x0c, 0x87, 0x7e, 0x85, 0xa5, 0x7d, 0x76, 0x35, 0xb9, 0x0d, 0x6f, 0x23, 0x7d, 0x87, 0x9b, 0x85, 0x0c, 0xe1, 0xa1, 0x0d, 0x7f, 0x87, 0x7d, 0x84, 0x7a,
	0x84, 0x7b, 0xe1, 0x86, 0xe8, 0x6f, 0xd1, 0x79, 0x85, 0x19, 0x53, 0x95, 0xc3, 0x47, 0x19, 0x7d, 0xe7, 0x0c, 0x37, 0x7c, 0x23, 0x7d, 0x85, 0x7d, 0x4b, 0x79, 0x21, 0xa5, 0x87, 0x7d, 0x19, 0x7d,
	0x0d, 0x7d, 0x15, 0x91, 0x23, 0x7d, 0x87, 0x7c, 0x85, 0x7a, 0x85, 0xaf, 0xcd, 0x7d, 0x87, 0x7d, 0xe9, 0x3d, 0x85, 0x7d, 0x15, 0x79, 0x85, 0x7d, 0xc1, 0x7b, 0xea, 0x7d, 0xb7, 0x7d, 0x85, 0x7d,
	0x85, 0x7d, 0x0d, 0x7d, 0xe9, 0x73, 0x85, 0x79, 0x05, 0x7d, 0xd7, 0x7d, 0x85, 0xe1, 0xb9, 0xe1, 0x0f, 0x65, 0x85, 0x86, 0x2d, 0x7d, 0xd7, 0xdd, 0xa3, 0x8e, 0xe6, 0x7d, 0xde, 0x7e, 0xae, 0x0e,
	0x0f, 0xe1, 0x89, 0x7e, 0x23, 0x7d, 0xf5, 0x79, 0x23, 0xe1, 0x4b, 0x83, 0x0c, 0x0f, 0x85, 0x7b, 0x85, 0x7e, 0x8f, 0x80, 0x85, 0x98, 0xf5, 0x7a, 0x85, 0x1a, 0x0d, 0xe1, 0x0f, 0x7c, 0x89, 0x0c,
	0x85, 0x0b, 0x23, 0x69, 0x87, 0x7b, 0x23, 0x0c, 0x1f, 0xb7, 0x21, 0x7a, 0x88, 0x7e, 0x8f, 0xa5, 0x7d, 0x80, 0xb7, 0xb9, 0x18, 0xbf, 0x4b, 0x19, 0x85, 0xa5, 0x91, 0x80, 0x87, 0x81, 0x87, 0x7c,
	0x0f, 0x73, 0x91, 0x91, 0x84, 0x87, 0x37, 0xd7, 0x86, 0x79, 0xe1, 0xdd, 0x85, 0x7a, 0x73, 0x9b, 0x05, 0x7d, 0x0d, 0x83, 0x87, 0x9c, 0x85, 0x33, 0x87, 0x7d, 0x85, 0x0f, 0x87, 0x7d, 0x0d, 0x7d,
	0xf6, 0x7e, 0x87, 0x7d, 0x88, 0x19, 0x89, 0xf5, 0xd1, 0xdd, 0x85, 0x7d, 0x8b, 0xc3, 0xea, 0x7a, 0xd7, 0xb0, 0x0d, 0x7d, 0x87, 0xa5, 0x87, 0x7c, 0x73, 0x7e, 0x7d, 0x86, 0x87, 0x23, 0x85, 0x10,
	0xd7, 0xdf, 0xed, 0xa5, 0xe1, 0x7a, 0x85, 0x23, 0xea, 0x7e, 0x85, 0x98, 0xad, 0x79, 0x86, 0x7d, 0x85, 0x7d, 0xd7, 0x7d, 0xe1, 0x7a, 0xf5, 0x7d, 0x85, 0xb0, 0x2b, 0x37, 0xe1, 0x7a, 0x87, 0x79,
	0x84, 0x7d, 0x73, 0x73, 0x87, 0x7d, 0x23, 0x7d, 0xe9, 0x7d, 0x85, 0x7e, 0x02, 0x7d, 0xdd, 0x2d, 0x87, 0x79, 0xe7, 0x79, 0xad, 0x7c, 0x23, 0xda, 0x87, 0x0d, 0x0d, 0x7b, 0xe7, 0x79, 0x9b, 0x7d,
	0xd7, 0x8f, 0x05, 0x7d, 0x0d, 0x34, 0x8f, 0x7d, 0xad, 0x87, 0xe9, 0x7c, 0x85, 0x80, 0x85, 0x79, 0x8a, 0xc3, 0xe7, 0xa5, 0xe8, 0x6b, 0x0d, 0x74, 0x10, 0x73, 0x33, 0x17, 0x0d, 0x37, 0x21, 0x19
};


void HookImpl::SetItemBonus2(STRUCT_ITEM* Dest)
{
	// Bota
	int g_pBonusValue5[36][4] =
	{
		{ 73, 30, 74, 18 },
		{ 73, 30, 74, 15 },
		{ 73, 30, 74, 12 },

		{ 73, 24, 74, 18 },
		{ 73, 24, 74, 15 },
		{ 73, 24, 74, 12 },

		{ 73, 18, 74, 18 },
		{ 73, 18, 74, 15 },
		{ 73, 18, 74, 12 },

		{ 73, 12, 74, 18 },
		{ 73, 12, 74, 15 },
		{ 73, 12, 74, 12 },

		{ 73, 6, 74, 18 },
		{ 73, 6, 74, 15 },
		{ 73, 6, 74, 12 },

		{ 73, 30, 60, 10 },
		{ 73, 30, 60, 8 },
		{ 73, 30, 60, 6 },

		{ 73, 24, 60, 10 },
		{ 73, 24, 60, 8 },
		{ 73, 24, 60, 6 },
		{ 73, 24, 60, 8 },
		{ 73, 24, 60, 6 },

		{ 73, 18, 60, 10 },
		{ 73, 18, 60, 8 },
		{ 73, 18, 60, 6 },
		{ 73, 18, 60, 8 },
		{ 73, 18, 60, 6 },

		{ 73, 12, 60, 10 },
		{ 73, 12, 60, 8 },
		{ 73, 12, 60, 6 },
		{ 73, 12, 60, 8 },
		{ 73, 12, 60, 6 },

		{ 73, 6, 60, 10 },
		{ 73, 6, 60, 8 },
		{ 73, 6, 60, 6 }
	};
	// Luva
	int g_pBonusValue4[35][4] =
	{
		{ 2, 30, 72, 30 },
		{ 2, 30, 72, 25 },
		{ 2, 30, 72, 20 },
		{ 2, 30, 72, 20 },
		{ 2, 30, 72, 20 },
		//{ 2, 30, 72, 15 },
		//{ 2, 30, 72, 10 },

		{ 2, 24, 72, 30 },
		{ 2, 24, 72, 25 },
		{ 2, 24, 72, 20 },
		{ 2, 24, 72, 20 },
		{ 2, 24, 72, 20 },
		//{ 2, 24, 72, 15 },
		//{ 2, 24, 72, 10 },

		{ 2, 18, 72, 30 },
		{ 2, 18, 72, 25 },
		{ 2, 18, 72, 20 },
		{ 2, 18, 72, 20 },
		{ 2, 18, 72, 20 },
		//{ 2, 18, 72, 15 },
		//{ 2, 18, 72, 10 },

		{ 60, 10, 72, 30 },
		{ 60, 10, 72, 25 },
		{ 60, 10, 72, 20 },
		{ 60, 10, 72, 20 },
		{ 60, 10, 72, 20 },
		//{ 60, 10, 72, 15 },

		{ 60, 8, 72, 30 },
		{ 60, 8, 72, 25 },
		{ 60, 8, 72, 20 },
		//{ 60, 8, 72, 15 },

		{ 60, 6, 72, 30 },
		{ 60, 6, 72, 25 },
		{ 60, 6, 72, 20 },
		//{ 60, 6, 72, 15 },

		{ 74, 18, 72, 30 },
		{ 74, 18, 72, 25 },
		{ 74, 18, 72, 20 },
		//{ 74, 18, 72, 15 },

		{ 74, 15, 72, 30 },
		{ 74, 15, 72, 25 },
		{ 74, 15, 72, 20 },
		//{ 74, 15, 72, 15 },

		{ 74, 12, 72, 30 },
		{ 74, 12, 72, 25 },
		{ 74, 12, 72, 20 }
	};

	// Elmo
	int g_pBonusValue3[32][4] =
	{
		{ 4, 60, 26, 18 },
		{ 4, 60, 26, 15 },
		{ 4, 60, 26, 12 },
		{ 4, 60, 26, 12 },
		{ 4, 60, 26, 12 },

		{ 4, 50, 26, 18 },
		{ 4, 50, 26, 15 },
		{ 4, 50, 26, 12 },

		{ 4, 40, 26, 18 },
		{ 4, 40, 26, 15 },
		{ 4, 40, 26, 12 },

		{ 4, 30, 26, 18 },
		{ 4, 30, 26, 15 },
		{ 4, 30, 26, 12 },
		{ 4, 30, 26, 12 },
		{ 4, 30, 26, 12 },

		{ 4, 60, 60, 12 },
		{ 4, 60, 60, 10 },
		{ 4, 60, 60, 8 },
		{ 4, 60, 60, 6 },

		{ 4, 50, 60, 12 },
		{ 4, 50, 60, 10 },
		{ 4, 50, 60, 8 },
		{ 4, 50, 60, 6 },
		{ 4, 50, 60, 6 },
		{ 4, 50, 60, 6 },

		{ 4, 40, 60, 12 },
		{ 4, 40, 60, 10 },
		{ 4, 40, 60, 8 },
		{ 4, 40, 60, 6 },
		{ 4, 40, 60, 6 },
		{ 4, 40, 60, 4 }
	};

	// Peito e Calça
	int g_pBonusValue2[53][4] =
	{
		{ 2, 30, 3, 30 }, //1 chance de add full
		{ 2, 30, 3, 25 },
		{ 2, 30, 3, 20 },
		{ 2, 30, 3, 20 },
		{ 2, 30, 3, 20 },
		{ 2, 24, 3, 30 },
		{ 2, 24, 3, 25 },
		{ 2, 24, 3, 20 },
		{ 2, 18, 3, 30 },
		{ 2, 18, 3, 25 },
		{ 2, 18, 3, 20 }, //11 opções de add dano/defesa

		{ 2, 30, 71, 50 },
		{ 2, 30, 71, 60 },
		{ 2, 30, 71, 70 }, //1 chance de add full
		{ 2, 24, 71, 50 },
		{ 2, 24, 71, 50 },
		{ 2, 24, 71, 50 },
		{ 2, 24, 71, 60 },
		{ 2, 24, 71, 70 },
		{ 2, 18, 71, 50 },
		{ 2, 18, 71, 60 },
		{ 2, 18, 71, 70 }, //11 opções de add dano/critico
		
		{ 60, 10, 3, 30 }, //1 chance de add full
		{ 60, 10, 3, 25 },
		{ 60, 10, 3, 20 },
		{ 60, 8, 3, 30 },
		{ 60, 8, 3, 25 },
		{ 60, 8, 3, 20 },
		{ 60, 6, 3, 30 },
		{ 60, 6, 3, 25 },
		{ 60, 6, 3, 20 },
		{ 60, 6, 3, 20 },
		{ 60, 6, 3, 20 }, //11 opções de add mago/defesa
		

		{ 60, 10, 71, 50 },
		{ 60, 10, 71, 60 },
		{ 60, 10, 71, 70 }, //1 chance de add full
		{ 60, 8, 71, 50 },
		{ 60, 8, 71, 60 },
		{ 60, 8, 71, 70 },
		{ 60, 6, 71, 50 },
		{ 60, 6, 71, 60 },
		{ 60, 6, 71, 70 },
		{ 60, 4, 71, 50 },
		{ 60, 4, 71, 60 }, //11 opções de add mago/critico

		{ 3, 15, 71, 50 },
		{ 3, 15, 71, 60 },
		{ 3, 15, 71, 70 },
		{ 3, 20, 71, 50 },
		{ 3, 20, 71, 60 },
		{ 3, 20, 71, 70 }, //6 opções de add defesa/critico  -  1 chance de add full
		
		{ 3, 45, 0, 0 }, //3 opções de add defesa
		{ 3, 45, 0, 0 },
		{ 3, 50, 0, 0 } //1 chance de add full
	};

	int nPos = g_pItemList[Dest->sIndex].nPos;

	if (nPos == 2)//Elmo
	{
		int _rand = rand() % (sizeof(g_pBonusValue3) / 16);

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}
		Dest->stEffect[1].cEffect = g_pBonusValue3[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue3[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue3[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue3[_rand][3];
	}
	//Peito calça
	if (nPos == 4 || nPos == 8)
	{
		int _rand = rand() % (sizeof(g_pBonusValue2) / 16);

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue2[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue2[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue2[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue2[_rand][3];
	}

	//Luva
	if (nPos == 16)
	{
		int _rand = rand() % (sizeof(g_pBonusValue4) / 16);

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue4[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue4[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue4[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue4[_rand][3];
	}

	//Bota
	if (nPos == 32)
	{
		int _rand = rand() % (sizeof(g_pBonusValue5) / 16);

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue5[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue5[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue5[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue5[_rand][3];
	}
}

BOOL HookImpl::AddMessage(CPSock* thisPtr, char* pMsg, int Size)
{
	char temp[256];
	MSG_STANDARD* std = (MSG_STANDARD*)pMsg;

	if (thisPtr->nSendPosition + Size >= 0x20000)
	{
		sprintf(temp, "err,add buffer full %d %d %d %d\n", thisPtr->nSendPosition, Size, std->Type, thisPtr->Sock);
		Log(temp, "-system", 0);

		return FALSE;
	}

	// check socket valid
	if (thisPtr->Sock <= 0)
	{
		sprintf(temp, "err,add buffer invalid %d %d %d %d\n", thisPtr->nSendPosition, Size, std->Type, thisPtr->Sock);
		Log(temp, "-system", 0);

		return FALSE;
	}

	unsigned char iKeyWord = rand() % 256;
	unsigned char KeyWord = pKeyWord[iKeyWord * 2];
	unsigned char CheckSum = 0;
	std->Size = Size;
	std->KeyWord = iKeyWord;
	std->CheckSum = CheckSum;
	std->ClientTick = timeGetTime();

	unsigned char Sum1 = 0;
	unsigned char Sum2 = 0;
	int			  pos = KeyWord;

	for (int i = 4; i < Size; i++, pos++)
	{
		Sum1 += pMsg[i];

		int rst = pos % 256;

		unsigned char Trans = pKeyWord[rst * 2 + 1];

		int mod = i & 0x3;

		if (mod == 0)
			thisPtr->pSendBuffer[thisPtr->nSendPosition + i] = pMsg[i] + (Trans << 1);

		if (mod == 1)
			thisPtr->pSendBuffer[thisPtr->nSendPosition + i] = pMsg[i] - (Trans >> 3);

		if (mod == 2)
			thisPtr->pSendBuffer[thisPtr->nSendPosition + i] = pMsg[i] + (Trans << 2);

		if (mod == 3)
			thisPtr->pSendBuffer[thisPtr->nSendPosition + i] = pMsg[i] - (Trans >> 5);

		Sum2 += thisPtr->pSendBuffer[thisPtr->nSendPosition + i];
	}

	CheckSum = Sum2 - Sum1;
	std->CheckSum = CheckSum;

	memcpy(thisPtr->pSendBuffer + thisPtr->nSendPosition, pMsg, 4);

	thisPtr->nSendPosition = thisPtr->nSendPosition + Size;

	return TRUE;
}

void HookImpl::BASE_GetCurrentScore(STRUCT_MOB& MOB, STRUCT_AFFECT* Affect, CMob* extra, int* PosX, int* PosY, int* ForceDamage, int* Abs, int* Accuracy, signed int a9, int MotalFace)
{
	bGetCurrentScore(MOB, Affect, extra, PosX, PosY, ForceDamage, Abs, Accuracy, a9, MotalFace);	

#pragma region Balanceamento
	//Transknight = 0,
	//Foema = 1,
	//BeastMaster = 2,
	//Huntress = 3

	if (MOB.Class == 0)
	{
		MOB.CurrentScore.Damage += MOB.CurrentScore.Damage * 20 / 100;
		MOB.Magic += 20;
	}

	if (MOB.Class == 1)
	{
		if (MOB.CurrentScore.Int < MOB.CurrentScore.Dex)
		{
			MOB.CurrentScore.Damage += MOB.CurrentScore.Damage * 45 / 100;
		}

		MOB.Magic += 45;
		MOB.CurrentScore.Ac += MOB.CurrentScore.Ac * 35 / 100;
	}

	if (MOB.Class == 2)
	{
		MOB.CurrentScore.Damage += MOB.CurrentScore.Damage * 25 / 100;
		MOB.Magic += 50;
	}

	if (MOB.Class == 3)
	{
		MOB.CurrentScore.Damage += MOB.CurrentScore.Damage * 15 / 100;
		MOB.CurrentScore.MaxMp += MOB.CurrentScore.MaxMp * 250 / 100;
		MOB.Magic += 15;
	}

#pragma endregion

}


void HookImpl::CheckSumPacket(char* pMsg)
{
	//if (pMsg == NULL)
	//	return;

	MSG_STANDARD* debug = (MSG_STANDARD*)pMsg;

	//if (pMsg != NULL && BASE_CheckPacket(debug))
	{
		sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d\n", debug->Type, debug->Size);
		Log(temp, "-system", 0);
	}
}

void HookImpl::CheckPacket(char* pMsg)
{
	if (pMsg == NULL)
		return;

	MSG_STANDARD* debug = (MSG_STANDARD*)pMsg;

	BASE_CheckPacket(debug);
}

void HookImpl::LastReqParty(int conn, int Leader)
{
	if (conn < MAX_USER && Leader < MAX_USER)
		pUserData[conn].Ingame.MSG.SendReqParty.LastReqParty = Leader;
}

bool HookImpl::ProcessDBMessage_CharacterLogin(const int conn, unsigned short* posX, unsigned short* posY)
{
	auto userData = &pUserData[conn];
	if (conn < NULL || conn > MAX_USER)
		return false;
	char* pMsg[2000];
	Func::LoadGuildInfo(conn);
	Func::SendGuildInfo(conn); 
	Func::WriteData(conn, "Sistema/Ranking");
	Func::SendDonateUpdate(conn); 
	Func::SendSenhaGrupo(conn);
	userData->Ingame.StoreActived = false;
	userData->Ingame.StorePoints = 0;
	memset(pUserData[conn].Ingame.PartyPassword, 0, sizeof(pUserData[conn].Ingame.PartyPassword));
	 
	return false;
}

bool HookImpl::Commands(const int32_t client, p334h* const packet)
{
	if (client <= NULL || client >= MAX_USER)
		return false;

	auto Packet = (p334h*)packet;

	static char PlayerCommand[][10] = { "pin", "xTGrupoTx", "relo", "summon", "Relo", "Summon" };

	for (int i = 0; i < 12; i++) //ja volto so um 
	{
		if (!strcmp(Packet->Cmd, PlayerCommand[i]))
		{
			return Exec_MSG_ComandClienter(client, Packet);
		}
	}

	return false;
}

char* HookImpl::ReadMessage(CPSock* thisPtr, int* ErrorCode, int* ErrorType)
{
	*ErrorCode = 0;

	if (thisPtr->nProcPosition >= thisPtr->nRecvPosition)
	{
		thisPtr->nRecvPosition = 0;
		thisPtr->nProcPosition = 0;

		return 0;
	}

	//  Init packet authentication
	if (thisPtr->Init == 0)
	{
		if (thisPtr->nRecvPosition - thisPtr->nProcPosition < 4)
			return 0;

		int InitCode = *((unsigned int*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition));

		if (InitCode != 0x1F11F311)
		{
			*ErrorCode = 2;
			*ErrorType = InitCode;

			return 0;
		}

		thisPtr->Init = 1;
		thisPtr->nProcPosition += 4;
	}

	//	Check received message is larger than HEADER
	if (thisPtr->nRecvPosition - thisPtr->nProcPosition < sizeof(HEADER))
		return 0;

	//	Check full message arrived
	unsigned short	Size = *((unsigned short*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition));
	unsigned char	iKeyWord = *((unsigned char*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition + 2));
	unsigned char	KeyWord = pKeyWord[iKeyWord * 2];
	unsigned char	CheckSum = *((unsigned char*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition + 3));
	unsigned int	SockType = *((unsigned int*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition + 4));
	unsigned int	SockID = *((unsigned int*)(thisPtr->pRecvBuffer + thisPtr->nProcPosition + 6));

	if (Size > 8192 || Size < sizeof(HEADER))
	{
		thisPtr->nRecvPosition = 0;
		thisPtr->nProcPosition = 0;

		*ErrorCode = 2;
		*ErrorType = Size;

		char temp[256];
		sprintf(temp, "LastPacket, Type: 0x%X - Size: %d - ID: %d\n", LastPacket.Type, LastPacket.Size, LastPacket.ID);
		Log(temp, "-system", 0);

		return 0;
	}

	unsigned int Rest = thisPtr->nRecvPosition - thisPtr->nProcPosition;

	if (Size > Rest)
		return 0;

	//	Get message
	char* pMsg = &(thisPtr->pRecvBuffer[thisPtr->nProcPosition]);

	thisPtr->nProcPosition = thisPtr->nProcPosition + Size;

	if (thisPtr->nRecvPosition <= thisPtr->nProcPosition)
	{
		thisPtr->nRecvPosition = 0;
		thisPtr->nProcPosition = 0;
	}

	// Compare check_sum in packet
	unsigned char Sum1 = 0;
	unsigned char Sum2 = 0;

	int	pos = KeyWord;

	for (int i = 4; i < Size; i++, pos++)
	{
		int rst = pos % 256;

		Sum2 += pMsg[i];

		unsigned char Trans = pKeyWord[rst * 2 + 1];

		int mod = i & 0x3;

		if (mod == 0)
			pMsg[i] = pMsg[i] - (Trans << 1);

		if (mod == 1)
			pMsg[i] = pMsg[i] + (Trans >> 3);

		if (mod == 2)
			pMsg[i] = pMsg[i] - (Trans << 2);

		if (mod == 3)
			pMsg[i] = pMsg[i] + (Trans >> 5);

		Sum1 += pMsg[i];
	}

	unsigned char Sum = Sum2 - Sum1;

	MSG_STANDARD* std = (MSG_STANDARD*)pMsg;

	LastPacket.Size = std->Size;
	LastPacket.ID = std->ID;
	LastPacket.CheckSum = std->CheckSum;
	LastPacket.KeyWord = std->KeyWord;
	LastPacket.Type = std->Type;
	LastPacket.ClientTick = std->ClientTick;

	/*if (std->Type == 0x36C || std->Type == 0x39D || std->Type == 0x39E)
	{
		char nMsg[100];
		memset(nMsg, 0, 100);

		MSG_Attack* m = (MSG_Attack*)pMsg;
		MSG_Attack_7556* sm = (MSG_Attack_7556*)nMsg;

		memcpy(nMsg, pMsg, sizeof(MSG_STANDARD));

		sm->Size = m->Size + 4;
		sm->Type = std->Type == 0x36C ? 0x367 : m->Type;
		sm->Motion = m->Motion;
		sm->SkillParm = m->SkillParm;
		sm->DoubleCritical = m->DoubleCritical;
		sm->FlagLocal = m->FlagLocal;
		sm->PosX = m->PosX;
		sm->PosY = m->PosY;
		sm->TargetX = m->TargetX;
		sm->TargetY = m->TargetY;
		sm->AttackerID = m->AttackerID;
		sm->Progress = m->Progress;
		sm->CurrentMp = m->CurrentMp;
		sm->SkillIndex = m->SkillIndex;
		sm->Hold = m->Hold;
		sm->ReqMp = m->ReqMp;
		sm->Rsv = m->Rsv;
		sm->CurrentExp = m->CurrentExp;
		sm->CurrentHp = 0;

		int MaxTarget = std->Type == 0x36C ? 13 : std->Type == 0x39D ? 1 : 2;

		for (int i = 0; i < MaxTarget; i++)
		{
			sm->Dam[i].Damage = m->Dam[i].Damage;
			sm->Dam[i].TargetID = m->Dam[i].TargetID;
		}	

		return nMsg;
	}*/

	// return packet, even check_sum not match
	if (Sum != CheckSum)
	{
		*ErrorCode = 1;
		*ErrorType = Size;

		return pMsg;
	}

	return pMsg;
}

// Função que é executada quando um Mob é morto
// Se retornar false, a execução continua para a TMSRV, procurando outros ids para executar.
// Se retornar true, a execução sai dessa parte.
bool HookImpl::MobKilledEvent(int32_t generID, int32_t killed, int32_t killer)
{
	
#pragma region Mob_Killed_By_Player 
 
	 if (killed > MAX_USER && killer > 0 && killer < MAX_USER) // mob foi morto por um usuário
		{
			auto Mob = GetMobFromIndex(killed);
			auto Player = GetMobFromIndex(killer); 
			auto masterId = [&Player, &killer] { return Player->Leader <= 0 ? killer : Player->Leader; }();
			auto result = ClueOfRunesMgr::instance().onMobKilled(Mob->TargetX, Mob->TargetY, killed, masterId); 
		 
		}
	 
	return false; 
}
#pragma endregion
// Função que administra o click nos npcs
// Retornar true, se o npc executou toda a sua função (vai pro fim da func na tmsrv)
// Retornar false se não foi executado nenhuma função (volta para a tmsrv)

bool HookImpl::onPlayerMovement(const int32_t client, MSG_Action_7556* const packet)
{
	if (client <= NULL || client >= MAX_USER)
		return false;

	auto result = ClueOfRunesMgr::instance().onMoviment(packet->PosX, packet->PosY, client); 

	return false;
}
bool HookImpl::OnNpcClick(int32_t client, p28Bh* packet)
{
	// Retornar true se 
	auto user = Func::GetUserFromIndex(client);

	if (user->Mode != Playing)return true;
	
	auto player = GetMobFromIndex(client),
		npc = GetMobFromIndex(packet->npcID);

	auto distance = BASE_GetDistance(player->TargetX, player->TargetY, npc->TargetY, npc->TargetY);

	if (distance > 12)return true;
		

	switch (npc->MOB.Info.Merchant)
	{
	case 2:
		SendClientMessage(client, "Presente de páscoa para a CB!");
		break;

	default:
		SendClientMessage(client, Func::strFmt("NPC [%s]", npc->MOB.MobName));
		break;
	}
	return true;
}


/*
bool HookImpl::OnNpcClick(int32_t client, p28Bh* packet)
{
	auto user = Func::GetUserFromIndex(client);

	if (client <= NULL || client >= MAX_USER)
		return true;

	if (user->Mode != Playing)
		return true;

	auto
		player = GetMobFromIndex(client),
		npc = GetMobFromIndex(packet->npcID);

	auto distance = BASE_GetDistance(player->TargetX, player->TargetY, npc->TargetY, npc->TargetY);

	if (distance > 12)
		return true;


	auto merchant = *(uint8_t*)(&npc->MOB.CurrentScore.Int);

	return merchant, npc->MOB.BaseScore.Dex, client, packet;
}
*/

// Corrige para os itens comprados na loja venham com add's.
void HookImpl::FixBuyItem(int conn, MSG_Buy* m)
{
	memcpy(&pMob[conn].MOB.Carry[m->MyInvenPos], &pMob[m->TargetID].MOB.Carry[m->TargetInvenPos], sizeof(STRUCT_ITEM));
}

// Adicionar items aqui para que seja possível separar unidades e juntar
bool HookImpl::AddJoinableItens(STRUCT_ITEM* item)
{
	switch (item->sIndex)
	{
		case 413:
		case 419:
		case 420:
		case 412:
		case 4017:
		case 4018:
		case 4019:
		case 4020:
		case 4117:
		case 4118:
		case 4119:
		case 4120:
		case 4121:
		case 5440:
		case 5452:
		case 3171:
		case 3172:
		case 3314:
		case 2441:
		case 2442:
		case 2443:
		case 2444:
		case 1774:
		case 5451:
		case 5446:
		case 5447:
		case 5448:
		case 5449:
		case 5453:
		case 5454:
		case 3392:

		return true;
	}
	return false;
}

void HookImpl::ProcessDBMessage_AccountLogin(int32_t client)
{
	auto user = Func::GetUserFromIndex(client);

	if (!Func::LoadAccount(client, user->AccountName))
		Log(Func::strFmt("Failed to Load UserData for Account [%s]", user->AccountName), "-system", user->IP);

}
void HookImpl::SaveUser(int32_t client)
{
	auto user = Func::GetUserFromIndex(client);

	if (!Func::SaveAccount(client, user->AccountName))
		Log(Func::strFmt("Failed to Save UserData for Account [%s]", user->AccountName), "-system", user->IP);

}
void HookImpl::CloseUser(int32_t client)
{
	auto user = Func::GetUserFromIndex(client);

	if (!Func::SaveAccount(client, user->AccountName))
		Log(Func::strFmt("Failed to Save UserData for Account [%s]", user->AccountName), "-system", user->IP);

	memset(pUserData[client].Ingame.PartyPassword, 0, sizeof(pUserData[client].Ingame.PartyPassword));

	memset(&pUserData[client], 0, sizeof(UserData));
}

void HookImpl::processSecTimer()
{
	Timer::instance().ProcessSecTimer();

	ProcessSecTimer();
}

void HookImpl::processMinTimer()
{
	Timer::instance().ProcessMinTimer();

	ProcessMinTimer();
}

int HookImpl::changeDoubleCritical(STRUCT_MOB* mob, unsigned short* sProgress, unsigned short* cProgress, unsigned char* bDoubleCritical)
{
	static auto g_pHitRate = reinterpret_cast<int*>(0x8CBC40);

	*bDoubleCritical = 0;

	if (cProgress == 0)
		return FALSE;

	if (*cProgress >= 1024)
	{
		if ((*cProgress & 0x3FF) < 0)
			*cProgress = ((*cProgress & 0x3FF) - 1 | 0xFC00) + 1;
	}

	if (sProgress != 0 && *sProgress >= 1024)
	{
		int val = *sProgress & 0x3FF;

		if (val < 0)
			val = ((val - 1) | 0xFC00) + 1;

		*sProgress = val;
	}

	int ret = 1;

	int hitvalue[2];

	hitvalue[0] = 100 * ((mob->CurrentScore.AttackRun >> 4) - 5);
	hitvalue[1] = mob->Critical;

	if ((sProgress != NULL && cProgress != NULL) && *cProgress != *sProgress)
	{
		*sProgress = *cProgress;

		int tProgress = *cProgress;

		if (tProgress < *sProgress)
			tProgress += 256;

		if (tProgress < *sProgress && tProgress < *sProgress + 5)
			ret = 1;
	}

	int value = g_pHitRate[*cProgress];

	for (int i = 0; i < 2; i++)
	{
		int bit = 0;

		if (i == 0)
		{
			if (value < hitvalue[0])
				bit = 1;
		}

		if (i == 1)
		{
			if (rand() % 255 < hitvalue[1])
				bit = 1;
		}

		*bDoubleCritical |= bit << i;
	}

	if (sProgress)
		++* sProgress;

	++* cProgress;

	return ret;
}

BYTE* HookImpl::SendPacket(BYTE *pBuffer, UINT32* socketId, UINT32 packetSize)
{
	try
	{
		bool clear = false;

		MSG_STANDARD* header = (MSG_STANDARD*)pBuffer;

		int clientid = Func::getIndexStruct((UINT32)0x0752BAF8, (UINT32)socketId, 0xC58);
		auto mob = GetMobFromIndex(clientid);
		auto user = Func::GetUserFromIndex(clientid);

		if (header->ID != header->ID) // Proteção 
			header->ID = header->ID;


		if (header->Type == 0x364)
		{
			Func::NpcTab(clientid, (MSG_CreateMob*)pBuffer);
		}

		else if (header->Type == 0x37F)
		{
			auto Packet = (p37Fh*)pBuffer;
		}

		if (clear)
			memset(pBuffer, 0, packetSize);

		_asm MOV EAX, pBuffer

	}

	catch (...)
	{

	}

	return pBuffer;

}


bool HookImpl::AfterEnterWorld(int clientId)
{
	 
	if (clientId <= 0 || clientId >= 1000) 
		return true;

	auto User = Func::GetUserFromIndex(clientId);

	if (User->Mode != Playing)
		return false;
	 
		auto Player = GetMobFromIndex(clientId);

		if (Player->MOB.Guild > 0)
		{
			if (Player->MOB.Equip[12].sIndex == 509)
			{
				int guildId = *(int*)((4 * 4) + 0x5A39F0);
				auto guild = Func::GetGuild(Player->MOB.Guild);
				 int  dragaoId = Player->MOB.Clan == 8 ? 3993 : 3994;
					auto dragao = Func::ReturnItemSlot(clientId, SlotType::Inventory, dragaoId);

					 if (dragao != -1)
					 Func::ClearItemInventory(clientId, dragao);
					return true;
			}
			return true;
		}
		return true;

}

int HookImpl::GetDamageControl(int type, int damage, int attacked, int attacker)
{

	char pMsg[4096];
	memset(pMsg, 0x0, sizeof (pMsg));

	MSG_Attack_7556* m = (MSG_Attack_7556*)pMsg;
	// attacker -> Player me atacando
	// attacked -> eu recebendo dano

#pragma region Players VS Players

	if (attacker > 0 && attacker < 1000)
	{
		auto player = GetMobFromIndex(attacker);
		auto mob = GetMobFromIndex(attacked);
		int Spectral = -1;
		int WeaponRange = -1;
		int Range = 1;
		int Distance = -1; 

		if (attacked > 0 && attacked < 1000)
		{
			if (player->MOB.Carry[63].stEffect[0].cEffect <= 5)
				return -1000;
		}

#pragma region  Player is not logged

		if (pUser[attacker].Mode != USER_PLAY)
		{
			return false;
		}

#pragma endregion

#pragma region Anti Range Hack & Controle de Mana

		if (attacker != attacked)
		{

			// Wall Hack
			if ((m->PosX != pMob[attacker].TargetX || m->PosY != pMob[attacker].TargetY) && attacker == m->AttackerID)
				return false;

			if (pMob[attacker].MOB.LearnedSkill & (1 << 29))
				Spectral = 1;

			if (pMob[attacker].MOB.Equip[6].sIndex != 0)
			{
				for (int i = 0; i < MAX_STATICEFFECT; i++)
				{
					if (g_pItemList[pMob[attacker].MOB.Equip[6].sIndex].stEffect[i].sEffect == EF_RANGE)
						WeaponRange = g_pItemList[pMob[attacker].MOB.Equip[6].sIndex].stEffect[i].sValue;
				}
			}

			if (Spectral != -1)
				Range = Range + 1;
			//Contra MOB ou Player
			if (attacked > 0 && attacked < MAX_MOB)
				Distance = BASE_GetDistance(pMob[attacker].TargetX, pMob[attacker].TargetY, pMob[attacked].TargetX, pMob[attacked].TargetY);

			if (Distance <= 0 || Distance >= 350)
				Distance = -1;
			// Astaroth transformation
			if (pMob[attacker].MOB.Equip[0].sIndex == 24 && Distance > Range + 5)
			{
				return -1000;
			}

			// Magic range attack
			else if (m->Motion == 255)
			{
				if (Distance > Range + g_pSpell[m->SkillIndex].Range + 3)
				{
					return false;
				}
			}
			else
			{
				// Attacked without possessing any weapon
				if (WeaponRange == -1)
				{
					if (Distance > Range + 4)
						//if (Distance > Range + 2)
					{
						return -1000;
					}
				}
				// Attacked too far
				else
				{
					if (Distance > Range + WeaponRange + 4)
						//if (Distance > Range + WeaponRange + 2)
					{
						return -1000;
					}
				}

			}


#pragma region  Controle de mana contra Player deve ficar aqui para funcionar contra range
			if (pMob[attacked].MOB.Class == 1)
			{
				bool ControleMana = false;
				for (size_t i = 0; i < 16; i++)
				{
					if (pMob[attacked].Affect[i].Type != 18)
						continue;

					ControleMana = true;
					break;
				}

				if (ControleMana)
				{

					if (pMob[attacked].MOB.CurrentScore.Mp > ((pMob[attacked].MOB.CurrentScore.MaxMp / 100) * 20))
					{
						int mana = pMob[attacked].MOB.CurrentScore.Mp - damage;
						if (mana < 0)
						{
							damage -= mana;
							mana = 0;
						}
						auto cal = ((damage / 100) * 40);
						damage -= (int)cal;
						pMob[attacked].MOB.CurrentScore.Mp = mana;
						SendSetHpMp(attacked);
					}
				}
			}
#pragma endregion
		}
#pragma endregion

	}
#pragma endregion

	// attacker -> Mob me atacando
	// attacked -> eu recebendo dano

#pragma region Players VS Mob
	else if (attacker > MAX_USER && attacker < MAX_MOB && attacked > 0 && attacked < 1000)
	{

#pragma region Controle de mana contra MOBS

		if (pMob[attacked].MOB.Class == 1)
		{
			bool ControleMana = false;
			for (size_t i = 0; i < 16; i++)
			{
				if (pMob[attacked].Affect[i].Type != 18)
					continue;

				ControleMana = true;
				break;
			}

			if (ControleMana)
			{

				if (pMob[attacked].MOB.CurrentScore.Mp > ((pMob[attacked].MOB.CurrentScore.MaxMp / 100) * 20))
				{
					int mana = pMob[attacked].MOB.CurrentScore.Mp - damage;
					if (mana < 0)
					{
						damage -= mana;
						mana = 0;
					}
					auto cal = ((damage / 100) * 40);
					damage -= (int)cal;
					pMob[attacked].MOB.CurrentScore.Mp = mana;
					SendSetHpMp(attacked);
				}
			}
		}
#pragma endregion	


#pragma region Proteção Kefra

		if (!strcmp(pMob[attacker].MOB.MobName, "Kefra") && pMob[attacked].MOB.Guild == 0)// Dano anulado para player sem guild
			return -1000;
#pragma endregion

#pragma region Proteção Guerra de Torres

		if (attacker > 1000)
		{

			if (!strcmp(pMob[attacker].MOB.MobName, "Torre Nordica"))// Nome da Torre sobre o altar
			{
				if (pMob[attacked].MOB.Guild == 0)//Player sem Guild não tira dano da torre
					return -1000;
			}
		}
#pragma endregion 
	}

	return damage;
}

int HookImpl::GetParryRate(int rate, int attacked, int attacker)
{
	return rate;
}

bool HookImpl::NewAffectValue(int loopIndex, CMob& mob, STRUCT_AFFECT* affects)
{
	STRUCT_AFFECT& affect = affects[loopIndex];
	 if (affect.Type == 25)
		{
			int calculo = (int)((mob.MOB.CurrentScore.Special[1] * 3) / 2);
			mob.MOB.CurrentScore.Ac += (uint16_t)calculo;
		}

		if (affect.Type == 13 || affect.Type == 14 || affect.Type == 17) // Proteção uso de Skill de Outra Classe TransKnight
		{
			if (mob.MOB.Class != 0)
			{
				affect.Time = 1;
			}
		}

		if (affect.Type == 18 || affect.Type == 22) // Proteção uso de Skill de Outra Classe Foema
		{
			if (mob.MOB.Class != 1)
			{
				affect.Time = 1;
			}
		}

		if (affect.Type == 16 || affect.Type == 23 || affect.Type == 25) // Proteção uso de Skill de Outra Classe BeastMaster
		{
			if (mob.MOB.Class != 2)
			{
				affect.Time = 1;
			}
		}

		if (affect.Type == 19 || affect.Type == 21 || affect.Type == 26 || affect.Type == 27
			|| affect.Type == 31 || affect.Type == 38 || affect.Type == 28 || affect.Type == 37) // Proteção uso de Skill de Outra Classe Hunters
		{
			if (mob.MOB.Class != 3)
			{
				affect.Time = 1;
			}
		}
	 

	return false;
}


bool HookImpl::NewItemTime(int item)
{
	if (item == 5414)
		return true;

	return false;
}


int HookImpl::ControlExperience(int killer, int member, int experience)
{
	return experience;
}
bool HookImpl::FixRefItemCele(int32_t client, char* pMsg)
{
	MSG_UseItem* m = (MSG_UseItem*)pMsg;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->DestType, m->DestPos);


	if (srcItem->sIndex != 413)
		return true;



	int Sucesso = 0;
	auto Chance = Rnd::instance().IRandomX(0, 100);

	if (m->DestType == ITEM_PLACE_CARRY && m->SourType == ITEM_PLACE_CARRY)
	{
		int Coisas[] = { 1901, 1902, 1903, 1904,
			1905, 1906, 1907, 1908,
			1234, 1235, 1236, 1237,
			1369, 1370, 1371, 1372,
			1519, 1520, 1521, 1522,
			1669, 1670, 1671, 1672,
			1909, 1910, 1714
		};
		int szCoisas = ((sizeof Coisas) / (sizeof(int)));
		bool Refi = false;
		for (int i = 0; i <= szCoisas; i++)
		{
			if (dstItem->sIndex == Coisas[i])
			{
				Refi = true;
				break;
			}
		}

		if (Refi)
		{
			Func::AmountMinus(srcItem);
			int Ref = BASE_GetItemSanc(&player->Carry[m->DestPos]);
			int continua = 0;
			if (Ref >= 0 && Ref <= 8)
				continua = 9;
			else
				return true;

			if (Chance <= Ref_Selado)
			{
				if (continua == 9)
					
				BASE_SetItemSanc(&player->Carry[m->DestPos], Ref + 1, 0);
				SendClientMessage(client, Func::strFmt("Refinação Bem Sucedida %d/%d", Chance, Ref_Selado));
				SendEmotion(client, 14, 3);

			}
			else
			{


				SendClientMessage(client, Func::strFmt("Refinação Falhou %d/%d", Chance, Ref_Selado));
				BASE_SetItemSanc(&player->Carry[m->DestPos], Ref - 1, 0);
				SendEmotion(client, 15, 2);
			}
			SendItem(client, m->DestType, m->DestPos, dstItem);
			SendItem(client, m->SourType, m->SourPos, srcItem);
			return false;
		}
		return false;
	}


	if (m->DestType == ITEM_PLACE_EQUIP && m->SourType == ITEM_PLACE_CARRY)
	{

		bool ItemCele = Func::CheckItemCelestial(dstItem->sIndex);
		if (ItemCele)
		{
			if (Func::PossivelRefinar(dstItem))
			{
				int Refinação = BASE_GetItemSanc(&player->Equip[m->DestPos]);

				if (Refinação >= 0 && Refinação <= 9)//+1 ~ +9
					Sucesso = RateRefItemCele[0];
				else if (Refinação >= 10 && Refinação < 14)//+10
					Sucesso = RateRefItemCele[1];
				else if (Refinação >= 14 && Refinação < 17)//+11
					Sucesso = RateRefItemCele[2];
				else if (Refinação >= 17 && Refinação < 20)//+12
					Sucesso = RateRefItemCele[3];
				else if (Refinação >= 20 && Refinação < 24)//+13
					Sucesso = RateRefItemCele[4];
				else if (Refinação >= 24 && Refinação < 27)//+14
					Sucesso = RateRefItemCele[5];
				else if (Refinação >= 27 && Refinação < 30)//+15
					Sucesso = RateRefItemCele[6];
				else if (Refinação >= 30 && Refinação < 34)//+16
				{
					SendClientMessage(client, "Impossivel de Refinar");
					SendItem(m->ID, m->SourType, m->SourPos, srcItem);
					return false;
				}
				else
					Sucesso = 0;

				if (Sucesso >= Chance)
				{
					SendClientMessage(client, Func::strFmt("Refinação Bem Sucedida %d/%d", Chance, Sucesso));
					if (Refinação >= 0 && Refinação <= 9)
						BASE_SetItemSanc(&player->Equip[m->DestPos], Refinação + 1, 0);
					else
						BASE_SetItemSanc(&player->Equip[m->DestPos], Refinação + 4, 0);


					SendItem(client, m->DestType, m->DestPos, dstItem);
					Func::AmountMinus(srcItem);
					SendItem(client, m->SourType, m->SourPos, srcItem);
					SendEmotion(client, 14, 3);
					Log(Func::strFmt("%s, %s Ref %d Item Cele (%d)%s -Sucess", user->AccountName, player->MobName, Refinação, dstItem->sIndex, pItem(dstItem->sIndex)->Name), "FixRefItemCele", user->IP);
					SendItem(client, m->DestType, m->DestPos, dstItem);
					SendItem(client, m->SourType, m->SourPos, srcItem);
					return false;
				}
				else
				{
					if (Refinação >= 0 && Refinação <= 10)
						BASE_SetItemSanc(&player->Equip[m->DestPos], Refinação - 1, 0);
					else
						BASE_SetItemSanc(&player->Equip[m->DestPos], Refinação - 4, 0);

					Func::AmountMinus(srcItem);
					SendItem(client, m->DestType, m->DestPos, dstItem);
					SendItem(client, m->SourType, m->SourPos, srcItem);
					SendEmotion(client, 15, 2);
					SendClientMessage(client, Func::strFmt("Refinação Falhou %d/%d", Chance, Sucesso));
					Log(Func::strFmt("%s, %s Ref %d Item Cele (%d)%s -Fail", user->AccountName, player->MobName, Refinação, dstItem->sIndex, pItem(dstItem->sIndex)->Name), "FixRefItemCele", user->IP);

					return false;
				}
			}
			else
			{
				SendClientMessage(client, "O item está sem refinação");
				SendItem(client, m->DestType, m->DestPos, dstItem);
				Log(Func::strFmt("%s, %s  Item Cele (%d)%s -Fail No EF_SANC or EF_COLOR", user->AccountName, player->MobName, dstItem->sIndex, pItem(dstItem->sIndex)->Name), "FixRefItemCele", user->IP);
				return true;
			}
		}
		return true;
	}
	return false;
}
 
bool HookImpl::BarraMytril_Dano(int32_t client, char* pMsg)
{

	MSG_UseItem* m = (MSG_UseItem*)pMsg;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->DestType, m->DestPos);


	if (srcItem->sIndex != 3027)
		return true;

	int SetType = Func::GetArmorType(dstItem->sIndex);



	if (!SetType)
	{
		SendClientMessage(m->ID, "Possível usar somente em armas ou armaduras.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return true;
	}
	auto Slot = -1;
	for (int EF = 0; EF < 3; EF++)
	{
		if (dstItem->stEffect[EF].cEffect == EF_DAMAGE || dstItem->stEffect[EF].cEffect == EF_DAMAGE2 || dstItem->stEffect[EF].cEffect == EF_DAMAGEADD)
		{
			Slot = EF;
			break;
		}
	}

	if (Slot == -1)
	{
		SendClientMessage(m->ID, "Composição incorreta.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return true;
	}
	if (!Func::CheckArchItem(dstItem->sIndex))
	{
		SendClientMessage(m->ID, "Somente equipamento Arch.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return true;
	}
	if (BASE_GetItemSanc(dstItem) <= 9)
	{
		SendClientMessage(m->ID, "Itens devem estar de acima +9.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return true;
	}

	if (SetType == 2)
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_DAMAGE_SET)
		{

			dstItem->stEffect[Slot].cValue = MAX_DAMAGE_SET;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->SourType, m->SourPos, srcItem);
			SendEmotion(client, 15, 3);
			return true;
		}
	}
	else
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_DAMAGE_ARMA)
		{
			dstItem->stEffect[Slot].cValue = MAX_DAMAGE_ARMA;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->DestType, m->DestPos, dstItem);
			return true;
		}
	}

	auto Chance = Rnd::instance().IRandomX(0, 100);
	Func::AmountMinus(srcItem);
	auto isADDOns = 4;
	if (Chance <= RATE_Mytrill_Falha)
	{
		dstItem->stEffect[Slot].cValue -= isADDOns;
		if (dstItem->stEffect[Slot].cValue < 4)
			dstItem->stEffect[Slot].cValue = 0;

		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		SendClientMessage(m->ID, Func::strFmt("Falha na Composição %d/%d", Chance, RATE_Mytrill_Falha));
		return true;
	}
	else if (Chance >= RATE_Mytrill_Sucesso)
	{
		dstItem->stEffect[Slot].cValue += isADDOns;
		if (dstItem->stEffect[Slot].cValue < 4)
			dstItem->stEffect[Slot].cValue = 0;

		SendClientMessage(m->ID, Func::strFmt("Composição Bem Sucedida %d/%d", Chance, RATE_Mytrill_Sucesso));
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 14, 3);
		return true;
	}
	else
	{
		SendClientMessage(m->ID, "Falha na composição.");
		return true;
	}
	for (int i = 0; i < MAX_EQUIP; i++)
	{
		SendItem(client, (uint16_t)SlotType::Equipment, i, &pMob[client].MOB.Equip[i]);
	}
	return false;
}
bool HookImpl::BarraMytril_AtqMágico(int32_t client, char* pMsg)
{
	MSG_UseItem* m = (MSG_UseItem*)pMsg;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->DestType, m->DestPos);


	if (srcItem->sIndex != 3028)
		return false;

	int SetType = Func::GetArmorType(dstItem->sIndex);
	if (!SetType)
	{
		SendClientMessage(m->ID, "Possível usar somente em armas ou armaduras.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	auto Slot = -1;
	for (int EF = 0; EF < 3; EF++)
	{
		if (dstItem->stEffect[EF].cEffect == EF_MAGIC )//|| dstItem->stEffect[EF].cEffect == EF_MAGICADD)
		{
			Slot = EF;
			break;
		}
	}

	if (Slot == -1)
	{
		SendClientMessage(m->ID, "Composição incorreta.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	if (!Func::CheckArchItem(dstItem->sIndex))
	{
		SendClientMessage(m->ID, "Somente equipamento Arch.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	if (BASE_GetItemSanc(dstItem) <= 9)
	{
		SendClientMessage(m->ID, "Itens devem estar de acima +9.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}

	if (SetType == 2)//Sets
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_MAGIC_SET)
		{
			dstItem->stEffect[Slot].cValue = MAX_MAGIC_SET;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->SourType, m->SourPos, srcItem);
			SendEmotion(client, 15, 3);
			return false;
		}
	}
	else//Armas
	{

		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_MAGIC_ARMA)
		{
			dstItem->stEffect[Slot].cValue = MAX_MAGIC_ARMA;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->DestType, m->DestPos, dstItem);
			SendEmotion(client, 15, 3);
			return false;
		}
	}

	auto Chance = Rnd::instance().IRandomX(0, 100);
	Func::AmountMinus(srcItem);
	auto isADDOns = 2;
	if (Chance <= RATE_Mytrill_Falha)
	{

		dstItem->stEffect[Slot].cValue -= isADDOns;

		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		SendClientMessage(m->ID, Func::strFmt("Falha na Composição %d/%d", Chance, RATE_Mytrill_Falha));
		return false;
	}
	else if (Chance >= RATE_Mytrill_Sucesso)
	{

		dstItem->stEffect[Slot].cValue += isADDOns;


		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		SendClientMessage(m->ID, Func::strFmt("Composição Bem Sucedida %d/%d", Chance, RATE_Mytrill_Sucesso));
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 14, 3);
		return false;
	}
	else
	{
		SendClientMessage(m->ID, "Falha na composição.");
		return false;
	}
	for (int i = 0; i < MAX_EQUIP; i++)
	{
		SendItem(client, (uint16_t)SlotType::Equipment, i, &pMob[client].MOB.Equip[i]);
	}
	return true;
}
bool HookImpl::BarraMytril_Defesa(int32_t client, char* pMsg)
{
	MSG_UseItem* m = (MSG_UseItem*)pMsg;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->DestType, m->DestPos);

	if (srcItem->sIndex != 3029)
		return false;

	int SetType = Func::GetArmorType(dstItem->sIndex);

	if (!SetType)
	{
		SendClientMessage(m->ID, "Possível usar somente em armas ou armaduras.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	auto Slot = -1;
	for (int EF = 0; EF < 3; EF++)
	{
		if (dstItem->stEffect[EF].cEffect == EF_AC )//|| dstItem->stEffect[EF].cEffect == EF_ACADD || dstItem->stEffect[EF].cEffect == EF_ACADD2)
		{
			Slot = EF;
			break;
		}
	}

	if (Slot == -1)
	{
		SendClientMessage(m->ID, "Composição incorreta.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	if (!Func::CheckArchItem(dstItem->sIndex))
	{
		SendClientMessage(m->ID, "Somente equipamento Arch.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	if (BASE_GetItemSanc(dstItem) <= 9)
	{
		SendClientMessage(m->ID, "Itens devem estar de acima +9.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}

	if (SetType == 2)
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_AC_SET)
		{
			dstItem->stEffect[Slot].cValue = MAX_AC_SET;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->SourType, m->SourPos, srcItem);
			SendEmotion(client, 15, 3);
			return false;
		}
	}
	if (SetType == 3)
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_AC_LUVA)
		{
			dstItem->stEffect[Slot].cValue = MAX_AC_LUVA;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->SourType, m->SourPos, srcItem);
			SendItem(m->ID, m->DestType, m->DestPos, dstItem);
			SendEmotion(client, 15, 3);
			return false;
		}
	}

	auto Chance = Rnd::instance().IRandomX(0, 100);
	Func::AmountMinus(srcItem);
	auto isADDOns = 4;
	if (Chance <= RATE_Mytrill_Falha)
	{
		dstItem->stEffect[Slot].cValue -= isADDOns;

		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		SendClientMessage(m->ID, Func::strFmt("Falha na   %d/%d", Chance, RATE_Mytrill_Falha));
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		return false;
	}
	else if (Chance >= RATE_Mytrill_Sucesso)
	{
		dstItem->stEffect[Slot].cValue += isADDOns;


		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		SendClientMessage(m->ID, Func::strFmt("Composição Bem Sucedida %d/%d", Chance, RATE_Mytrill_Sucesso));
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 14, 3);
		return false;
	}
	else
	{
		SendClientMessage(m->ID, "Falha na composição.");
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		return false;
	}
	for (int i = 0; i < MAX_EQUIP; i++)
	{
		SendItem(client, (uint16_t)SlotType::Equipment, i, &pMob[client].MOB.Equip[i]);
	}
	return true;
}
bool HookImpl::BarraMytril_Crítico(int32_t client, char* pMsg)
{
	MSG_UseItem* m = (MSG_UseItem*)pMsg;
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, m->DestType, m->DestPos);

	if (srcItem->sIndex != 3030)
		return false;


	int SetType = Func::GetArmorType(dstItem->sIndex);



	if (!SetType)
	{
		SendClientMessage(m->ID, "Possível usar somente em armas ou armaduras.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		return false;
	}
	auto Slot = -1;
	for (int EF = 0; EF < 3; EF++)
	{
		if (dstItem->stEffect[EF].cEffect == EF_CRITICAL2 )//|| dstItem->stEffect[EF].cEffect == EF_CRITICAL)
		{
			Slot = EF;
			break;
		}
	}

	if (Slot == -1)
	{
		SendClientMessage(m->ID, "Composição incorreta.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		SendEmotion(client, 11, 3);
		return false;
	}
	if (!Func::CheckArchItem(dstItem->sIndex))
	{
		SendClientMessage(m->ID, "Somente equipamento Arch.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		SendEmotion(client, 11, 3);
		return false;
	}
	if (BASE_GetItemSanc(dstItem) <= 9)
	{
		SendClientMessage(m->ID, "Itens devem estar de acima +9.");
		SendItem(m->ID, m->SourType, m->SourPos, srcItem);
		SendEmotion(client, 11, 3);
		return false;
	}

	if (SetType == 2)
	{
		if ((dstItem->stEffect[Slot].cValue + 4) > MAX_CRITICO_SET)
		{
			dstItem->stEffect[Slot].cValue = MAX_CRITICO_SET;
			SendClientMessage(m->ID, "Limite de Adicional atingido !");
			SendItem(m->ID, m->SourType, m->SourPos, srcItem);
			SendEmotion(client, 15, 3);
			return false;
		}
	}


	auto Chance = Rnd::instance().IRandomX(0, 100);
	auto isADDOns = 20;
	Func::AmountMinus(srcItem);

	if (Chance <= RATE_Mytrill_Falha)
	{
		dstItem->stEffect[Slot].cValue -= isADDOns;
		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		SendClientMessage(m->ID, Func::strFmt("Falha na Composição %d/%d", Chance, RATE_Mytrill_Falha));
		return false;
	}
	else if (Chance >= RATE_Mytrill_Sucesso)
	{
		dstItem->stEffect[Slot].cValue += isADDOns;
		if (dstItem->stEffect[Slot].cValue < 0)
			dstItem->stEffect[Slot].cValue = 0;

		//SendClientMessage(m->ID, "Sucesso na Composição");
		SendClientMessage(m->ID, Func::strFmt("Composição Bem Sucedida %d/%d", Chance, RATE_Mytrill_Sucesso));
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 14, 3);
		return false;
	}
	else
	{
		SendClientMessage(m->ID, "Falha na composição.");
		SendItem(m->ID, m->DestType, m->DestPos, dstItem);
		SendEmotion(client, 11, 3);
		return false;
	}
	for (int i = 0; i < MAX_EQUIP; i++)
	{
		SendItem(client, (uint16_t)SlotType::Equipment, i, &pMob[client].MOB.Equip[i]);
	}
	return true;
}

bool HookImpl::ExtraElmo(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg;
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 1;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex >= 3500 && mob->MOB.Equip[Destino].sIndex <= 3507)
	{
		SendClientMessage(client, "Não é possível utilizar em Cytheras.");
		SendItem(client, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	}

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client,  ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}

	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 50 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendCarry(client);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
		
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 50 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}

bool HookImpl::ExtraPeito(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg;
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 2;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client,  ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}

	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 50 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 50 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}

bool HookImpl::ExtraCalça(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg;
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 3;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client,  ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}

	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 50 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 50 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}

bool HookImpl::ExtraLuva(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg;
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 4;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client,  ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}

	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 50 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 50 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}

bool HookImpl::ExtraBota(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg;
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 5;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client, ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}

	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 50 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 50 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}

bool HookImpl::ExtraArma(int32_t client, char* pMsg)
{
	MSG_UseItem* packet = (MSG_UseItem*)pMsg; 
	auto mob = GetMobFromIndex(packet->ID);
	STRUCT_MOB *player = (STRUCT_MOB*)GetMobFromIndex(client);
	CUser *user = (CUser*)Func::GetUserFromIndex(client);
	STRUCT_ITEM *srcItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->SourType, packet->SourPos);
	STRUCT_ITEM *dstItem = (STRUCT_ITEM*)GetItemPointer(player, pUser->Cargo, packet->DestType, packet->DestPos);

	int Destino = 6;
	INT8 Random = rand() % 100, Chances = 0;

	if (mob->MOB.Equip[Destino].sIndex == 0)
	{
		SendClientMessage(client, "Não possui o item determinado a Extração.");
		SendItem(client, ITEM_PLACE_CARRY, packet->SourPos, &mob->MOB.Carry[packet->SourPos]);
		return true;
	}
	if (BASE_GetItemSanc(dstItem) > 9)
	{
		SendClientMessage(packet->ID, "Refinação deve ser menor ou igual +9");
		SendItem(packet->ID, ITEM_PLACE_CARRY, packet->SourPos, srcItem);
		return true;
	} 
	if (mob->MOB.Carry[packet->SourPos].EFV1 >= 1 || mob->MOB.Carry[packet->SourPos].EF2 >= 1 || mob->MOB.Carry[packet->SourPos].EFV2 >= 1
		|| mob->MOB.Carry[packet->SourPos].EF3 >= 1 || mob->MOB.Carry[packet->SourPos].EFV3 >= 1)
	{

		if (Random <= 35 + Chances)
		{
			//Do Extração para o Item
			int index = mob->MOB.Equip[Destino].sIndex;
			memcpy(&mob->MOB.Equip[Destino], &mob->MOB.Carry[packet->SourPos], sizeof STRUCT_ITEM);
			mob->MOB.Equip[Destino].sIndex = index;


			Func::AmountMinus(srcItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Enviado ao Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(client, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha ao Enviar o Adicional ao Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	else
	{

		if (Random <= 35 + Chances)
		{
			//Do Item para a Extração
			int index = mob->MOB.Carry[packet->SourPos].sIndex;
			memcpy(&mob->MOB.Carry[packet->SourPos], &mob->MOB.Equip[Destino], sizeof STRUCT_ITEM);
			mob->MOB.Carry[packet->SourPos].sIndex = index;

			Func::AmountMinus(&mob->MOB.Equip[Destino]);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendClientMessage(client, "Adicional Removido do Item com Sucesso.");
			SendCarry(client);
			return true;
		}
		else
		{
			Func::AmountMinus(srcItem);
			SendItem(client, packet->SourType, packet->SourPos, srcItem);
			SendItem(client, packet->SourType, packet->SourPos, dstItem);
			SendItem(packet->ID, ITEM_PLACE_EQUIP, Destino, &mob->MOB.Equip[Destino]);
			SendClientMessage(client, "Houve uma falha em Remover o Adicional do Item.");
			SendCarry(client);
			return true;
		}
		return true;
	}
	return true;
}


int HookImpl::ExpControl(int conn, int Exp)
{
	if (conn <= 0 || conn >= MAX_USER || !Exp)
		return 0;

	auto* mob = GetMobFromIndex(conn);
	int Level = mob->MOB.BaseScore.Level;

	if (Func::GetPlayerClass(conn) >= Celestial)
	{
		
			if (Level < 120)
				Exp /= 16;

			else if (Level < 140)
				Exp /= 24;

			else if (Level < 160)
				Exp /= 32;

			else if (Level < 180)
				Exp /= 48;

			else if (Level < 190)
				Exp /= 64;

			else if (Level < 200)
				Exp /= 128; 
	}
	else if (Func::GetPlayerClass(conn) == God)
	{//Arch
		if (Level >= 1)
		{
			if (Level < 255)
				Exp /= 1;

			else if (Level < 349)
				Exp /= 1;

			else if (Level < 355)
				Exp /= 2;

			else
				Exp /= 1;
		}
	}
	else if (Func::GetPlayerClass(conn) == Mortal)
	{//Mortal
		if (Level >= 319)
		{
			if (Level < 349)
				Exp /= 1;

			else if (Level < 355)
				Exp /= 2;

			else
				Exp /= 1;
		}
		 
	} 
	return Exp;
}

int __stdcall HookImpl::teleportPosition(uint32_t client, short* ptrX, short* ptrY, uint32_t* Unknown)
{
	short posX = (*ptrX & 0xFFC);
	short posY = (*ptrY & 0xFFC);

	int returnValue = 0;

	if (client <= NULL || client >= MAX_USER)
		return returnValue;

	auto mob = GetMobFromIndex(client);
	auto kingdom = mob->MOB.Clan;

	//if (posX >= 1054 && posY >= 1722 && posX <= 1060 && posY <= 1728)// RvR
	//{
	//	if (gameServer.rvr.Action.happening)
	//	{
	//		if (!gameServer.rvr.Action.redWins && kingdom == 7)
	//		{
	//			*ptrX = (1063 + (rand() % 2));
	//			*ptrY = (2136 + (rand() % 2));
	//			*Unknown = 0;
	//			returnValue = 0;
	//		}

	//		if (!gameServer.rvr.Action.blueWins && kingdom == 8)
	//		{
	//			*ptrX = (1237 + (rand() % 2));
	//			*ptrY = (1960 + (rand() % 2));
	//			*Unknown = 0;
	//			returnValue = 0;
	//		}
	//	}
	//	*Unknown = 0;
	//	returnValue = 0;
	//}
	if (posX >= 2364 && posY >= 2284 && posX <= 2366 && posY <= 2286)
	{
		*ptrX = (149 + (rand() % 1));
		*ptrY = (3789 + (rand() % 1));
		*Unknown = 0;
		returnValue = 0;
	}

	if (posX >= 144 && posY >= 3788 && posX <= 147 && posY <= 3790)
	{
		*ptrX = (2365 + (rand() % 1));
		*ptrY = (2281 + (rand() % 1));
		*Unknown = 0;
		returnValue = 0;
	}

	if (posX >= 2668 && posY >= 2155 && posX <= 2670 && posY <= 2157)
	{
		*ptrX = (149 + (rand() % 1));
		*ptrY = (3773 + (rand() % 1));
		*Unknown = 0;
		returnValue = 0;
	}

	if (posX >= 144 && posY >= 3772 && posX <= 147 && posY <= 3774)
	{
		*ptrX = (2669 + (rand() % 1));
		*ptrY = (2153 + (rand() % 1));
		*Unknown = 0;
		returnValue = 0;
	}

	if (posX >= 1050 && posY >= 1706 && posX <= 1057 && posY <= 1713)//Noatun to gelo para corrigir n aparecer no teto
	{
		*ptrX = (3649 + (rand() % 1));
		*ptrY = (3109 + (rand() % 1));

		mob->MOB.Info.CityID = 3;
		*Unknown = 0;
		returnValue = 700;
	}

	if (posX >= 2360 && posY >= 3913 && posX <= 2376 && posY <= 3941)//Kefra to UxMall
	{

		*ptrX = (3248 + (rand() % 1));
		*ptrY = (1701 + (rand() % 1));
		*Unknown = 0;
		returnValue = 700;
	}


	return returnValue;
}
