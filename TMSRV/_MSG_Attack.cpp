#include "stdafx.h"

bool Exec_MSG_Attack(int conn, char* pMsg)
{
	MSG_Attack_7556* m = (MSG_Attack_7556*)pMsg;

	unsigned int SystemTime = *(unsigned int*)0x8A58B8;

	// Define affects by class
	const static int TransKnightAffect[] = { 0, 3, 5, 11 };
	const static int ForemaAffect[] = { 29, 37, 41, 42, 43, 44, 45, 46 };
	const static int BeastMasterAffect[] = { 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 68, 70, 71 };
	const static int HuntressAffect[] = { 75, 76, 77, 81, 83, 84, 86, 87, 95, 89, 92 };

	// Invalid player index
	if (conn != m->ID || conn <= NULL || conn >= MAX_USER)
		return false;
	 
	
	// OneHit Hack
	if (*(short*)&pMsg[48] == 7 && *(short*)&pMsg[73] == 0xBBB)
		return false;

	if (conn < MAX_USER)
	{
		unsigned int CurrentTime = timeGetTime();

		if (pUserData[conn].Ingame.MSG.Attack.LastAttackTime != 0)
		{
			unsigned int Threshold = CurrentTime - pUserData[conn].Ingame.MSG.Attack.LastAttackTime;

			if (Threshold < 850)
			{
				// Skill Speed Hack
				if (m->Motion == 255 && Threshold < 300)
				{
					if (++pUserData[conn].Ingame.Warning >= 5)
					{
						//pMob[conn].CrackError = SystemTime + 10800;
						//Log("SpeedAttack hack detected", pUser[conn].AccountName, pUser[conn].IP);
						return false;
					}
				}

				// Attack Speed Hack
				if (m->Motion != 255)
				{
					if (++pUserData[conn].Ingame.Warning >= 5)
					{
						//pMob[conn].CrackError = SystemTime + 10800;
						//Log("SpeedAttack hack detected", pUser[conn].AccountName, pUser[conn].IP);
						return false;
					}
				}
			}
		}

		pUserData[conn].Ingame.MSG.Attack.LastAttackTime = CurrentTime;
	}

	int idx = m->Dam[0].TargetID;

	int SkillIndex = m->SkillIndex;

	// Use KHEPRA skill
	if (SkillIndex == 110 || SkillIndex == 96 || SkillIndex == 90)
	{
		//pMob[conn].CrackError = SystemTime + 10800;
		Log("Kicked for hacking", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	// Use VINE skill
	if (SkillIndex == 98)
	{
		if (pMob[conn].MOB.LearnedSkill & (1 << 26))
			return true;

		//pMob[conn].CrackError = SystemTime + 10800;
		Log("Kicked for hacking", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	// Use SOUL BOUND skill
	if (SkillIndex == 103)
	{
		if (pMob[conn].MOB.LearnedSkill & (1 << 31))
			return true;

		//pMob[conn].CrackError = SystemTime + 10800;
		Log("Kicked for hacking", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	// Use SOUL BOUND skill
	if (SkillIndex == 102)
	{
		if (pMob[conn].MOB.LearnedSkill & (1 << 30))
			return true;

		//pMob[conn].CrackError = SystemTime + 10800;
		Log("Kicked for hacking", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	// Use RESURRECTION skill
	if (SkillIndex == 99)
	{
		if (pMob[conn].MOB.LearnedSkill & (1 << 27))
			return true;

		//pMob[conn].CrackError = SystemTime + 10800;
		Log("Kicked for hacking", pUser[conn].AccountName, pUser[conn].IP);
		//CloseUser(conn);
		return false;
	}

	// Check for skill use by class
	for (int i = 0; i < 15; i++)
	{
		// TransKnight skills
		if (i < (sizeof(TransKnightAffect) / 4))
		{
			if (SkillIndex == TransKnightAffect[i])
			{
				if (pMob[conn].MOB.Class == 0 && pMob[conn].MOB.LearnedSkill & (1 << SkillIndex))
					return true;

				return false;
			}
		}

		//Forema skills
		if (i < (sizeof(ForemaAffect) / 4))
		{
			if (SkillIndex == ForemaAffect[i])
			{
				if (pMob[conn].MOB.Class == 1 && pMob[conn].MOB.LearnedSkill & (1 << (SkillIndex - 24)))
					return true;

				return false;
			}
		}

		// Huntress skills
		if (i < (sizeof(HuntressAffect) / 4))
		{
			if (SkillIndex == HuntressAffect[i])
			{
				if (pMob[conn].MOB.Class == 3 && pMob[conn].MOB.LearnedSkill & (1 << (SkillIndex - 72)))
					return true;

				return false;
			}
		}

		// BeastMaster skills
		if (i < (sizeof(BeastMasterAffect) / 4))
		{
			if (SkillIndex == BeastMasterAffect[i])
			{
				if (pMob[conn].MOB.Class == 2 && pMob[conn].MOB.LearnedSkill & (1 << (SkillIndex - 48)))
					return true;

				return false;
			}
		}
	}

	if (CWarTower::TowerAttack(conn, idx) == FALSE)
		return false; 
	return true;
}
