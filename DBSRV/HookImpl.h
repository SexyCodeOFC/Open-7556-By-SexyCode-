#ifndef HOOK_IMPL_H
#define HOOK_IMPL_H

class HookImpl
{
private:
	HookImpl() = delete;
	virtual ~HookImpl() = delete;
	HookImpl(const HookImpl&) = delete;
	HookImpl& operator=(const HookImpl&) = delete;

public:
	static char* __stdcall ReadMessage(CPSock* thisPtr, int* ErrorCode, int* ErrorType);
	static BOOL __stdcall AddMessage(CPSock* thisPtr, char* pMsg, int Size);
	static bool __stdcall HKD_PacketControlRECV(const int32_t code);
	static int __stdcall HKD_AddMessage(int Socket, MSG_STANDARD* OldMsg, int Size);
	static BYTE* __stdcall HKD_ReadMessage(int instModule, int* unkParam1, int* unkParam2);
};
#endif // !HOOK_IMPL_H
