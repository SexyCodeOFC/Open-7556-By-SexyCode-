#ifndef CONSTANT_PATCH_H
#define CONSTANT_PATCH_H

class ConstantPatch : public Singleton<ConstantPatch>
{
protected:
	friend class Singleton<ConstantPatch>;
	ConstantPatch() {}
	virtual ~ConstantPatch() {}
	ConstantPatch(const ConstantPatch&) = delete;
	ConstantPatch& operator=(const ConstantPatch&) = delete;

	void setSummonNames();
	void setFilePaths();
	void setVersion();
	void setOtherValues();
	void setPointer();
	void setPacket();
public:
	bool initialize();
};

#endif // !CONSTANT_PATCH_H
