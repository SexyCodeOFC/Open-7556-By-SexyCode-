#include "stdafx.h"
#include "ProcessClientMessage.h"

void Fix_MSG_Attack_SEND(char* NewMsg, MSG_STANDARD* OldMsg)
{
	MSG_Attack* sm = (MSG_Attack*)NewMsg;
	MSG_Attack_7556* m = (MSG_Attack_7556*)OldMsg;

	sm->Type = OldMsg->Type == 0x367 ? 0x36C : m->Type;
	sm->Size = m->Size;
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

	int MaxTarget = OldMsg->Type == 0x367 ? 13 : OldMsg->Type == 0x39D ? 1 : 2;

	for (int i = 0; i < MaxTarget; i++)
	{
		sm->Dam[i].Damage = m->Dam[i].Damage;
		sm->Dam[i].TargetID = m->Dam[i].TargetID;
	}
}

void Fix_MSG_Attack_RECV(MSG_STANDARD* pMsg, bool* pRetn)
{
	MSG_Attack* m = (MSG_Attack*)pMsg;

	MSG_Attack_7556 sm;
	memset(&sm, 0, sizeof(MSG_Attack_7556));

	memcpy(&sm, m, sizeof(MSG_STANDARD));
	sm.Size = m->Size;
	sm.Type = pMsg->Type == 0x36C ? 0x367 : m->Type;

	sm.Motion = m->Motion;
	sm.SkillParm = m->SkillParm;
	sm.DoubleCritical = m->DoubleCritical;
	sm.FlagLocal = m->FlagLocal;
	sm.PosX = m->PosX;
	sm.PosY = m->PosY;
	sm.TargetX = m->TargetX;
	sm.TargetY = m->TargetY;
	sm.AttackerID = m->AttackerID;
	sm.Progress = m->Progress;
	sm.CurrentMp = m->CurrentMp;
	sm.SkillIndex = m->SkillIndex;
	sm.Hold = m->Hold;
	sm.ReqMp = m->ReqMp;
	sm.Rsv = m->Rsv;
	sm.CurrentExp = m->CurrentExp;

	int MaxTarget = pMsg->Type == 0x36C ? 13 : pMsg->Type == 0x39D ? 1 : 2;

	for (int i = 0; i < MaxTarget; i++)
	{
		sm.Dam[i].Damage = m->Dam[i].Damage;
		sm.Dam[i].TargetID = m->Dam[i].TargetID;
	}

	memcpy(m, &sm, m->Size);

	*pRetn = false;
}