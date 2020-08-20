#include "stdafx.h"
#include "ProcessClientMessage.h"

void Fix_MSG_Action_SEND(char* NewMsg, MSG_STANDARD* OldMsg)
{
	if (OldMsg->Type == 0x36C && OldMsg->Size > 52)
		return;

	MSG_Action* sm = (MSG_Action*)NewMsg;
	MSG_Action_7556* m = (MSG_Action_7556*)OldMsg;

	sm->PosX = m->PosX;
	sm->PosY = m->PosY;

	sm->Effect = m->Effect;
	sm->Speed = m->Speed;

	strncpy(sm->Route, m->Route, 24);

	sm->TargetX = m->TargetX;
	sm->TargetY = m->TargetY;

	sm->Type = m->Type;

	switch (m->Type)
	{
	case 0x36C:
		sm->Type = 0x366;
		break;

	case 0x366:
		sm->Type = 0x367;
		break;
	}
}

void Fix_MSG_Action_RECV(MSG_STANDARD* pMsg, bool* pRetn)
{
	MSG_Action* m = (MSG_Action*)pMsg;

	MSG_Action_7556 sm;
	memset(&sm, 0, sizeof(MSG_Action_7556));

	sm.ClientTick = m->ClientTick;
	sm.KeyWord = m->KeyWord;
	sm.ID = m->ID;

	sm.Type = m->Type;

	switch (pMsg->Type)
	{
	case 0x366:
		sm.Type = 0x36C;
		break;

	case 0x367:
		sm.Type = 0x366;
		break;
	}

	sm.Size = sizeof(MSG_Action_7556);

	sm.PosX = m->PosX;
	sm.PosY = m->PosY;

	sm.Effect = m->Effect;
	sm.Speed = m->Speed;

	strncpy(sm.Route, m->Route, 24);

	sm.TargetX = m->TargetX;
	sm.TargetY = m->TargetY;

	memcpy(m, &sm, sizeof(MSG_Action_7556));

	*pRetn = false;
}