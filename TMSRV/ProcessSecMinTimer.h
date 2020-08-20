#ifndef PROCESSSECMINTIER_H
#define PROCESSSECMINTIER_H

class Timer : public Singleton<Timer>
{
protected:
	friend class Singleton<Timer>;

	Timer();
	virtual ~Timer() {}
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

public:
	void ProcessMinTimer();
	void ProcessSecTimer();

private:
	uint64_t
		minCounter_,
		minPartCounter_,
		secCounter_,
		quarterMsCounter_;

};
#endif // !TIMER_H
