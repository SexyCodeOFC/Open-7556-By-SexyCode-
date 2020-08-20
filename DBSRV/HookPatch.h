#ifndef HOOK_PATCH_H
#define HOOK_PATCH_H

class HookPatch : public Singleton<HookPatch>
{
protected:
	friend class Singleton<HookPatch>;
	HookPatch() {}
	virtual ~HookPatch() {}
	HookPatch(const HookPatch&) = delete;
	HookPatch& operator=(const HookPatch&) = delete;

public:
	bool initialize();
	static void NKD_ReadMessage();
	static void NKD_AddMessage(); 
};

#endif // !HOOK_PATCH_H
