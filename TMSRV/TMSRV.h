#ifndef TMSRV_H
#define TMSRV_H

class TMSRV : public Singleton<TMSRV>
{
protected:
	friend class Singleton<TMSRV>;
	TMSRV() {}
	virtual ~TMSRV() {}
	TMSRV(const TMSRV&) = delete;
	TMSRV& operator=(const TMSRV&) = delete;

public:
	bool initialize();
	void cleanup();
};

#endif // !TMSRV_H
