#ifndef VOLATILES_H
#define VOLATILES_H

class Volatiles
{
private:
	Volatiles() = delete;
	virtual ~Volatiles() = delete;
	Volatiles(const Volatiles&) = delete;
	Volatiles& operator=(const Volatiles&) = delete;
public:
	static bool Feijoes(int32_t client, p373h* packet);

};
#endif // !VOLATILES_H
