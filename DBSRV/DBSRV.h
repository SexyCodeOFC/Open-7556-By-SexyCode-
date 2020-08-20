#ifndef DBSRV_H
#define DBSRV_H

class DBSRV : public Singleton<DBSRV>
{
protected:
	friend class Singleton<DBSRV>;
	DBSRV() {}
	virtual ~DBSRV() {}
	DBSRV(const DBSRV&) = delete;
	DBSRV& operator=(const DBSRV&) = delete;
public:
	bool initialize();
	void cleanup();
};
#endif // !DBSRV_H
