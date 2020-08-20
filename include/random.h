#ifndef RANDOM_H
#define RANDOM_H

#define MERS_N   624
#define MERS_M   397
#define MERS_R   31
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   18
#define MERS_A   0x9908B0DF
#define MERS_B   0x9D2C5680
#define MERS_C   0xEFC60000


class Rnd : public Singleton<Rnd>
{
protected:
	friend class Singleton<Rnd>;
	Rnd() {}
	virtual ~Rnd() {}
	Rnd(const Rnd&) = delete;
	Rnd& operator=(const Rnd&) = delete;

private:
	uint32_t mt[MERS_N];
	uint32_t idx;
	uint32_t LastInterval;              // Last interval length for IRandomX
	uint32_t RLimit;                    // Rejection limit used by IRandomX

public:
	void Seed(uint32_t seed)
	{
		const uint32_t factor = 1812433253UL;
		mt[0] = seed;
		for (idx = 1; idx < MERS_N; idx++) 
			mt[idx] = (factor * (mt[idx - 1] ^ (mt[idx - 1] >> 30)) + idx);
	}
	double Random() 
	{
		// Output random float number in the interval 0 <= x < 1
		// Multiply by 2^(-32)
		return (double)BRandom() * (1. / (65536.*65536.));
	}

	int32_t IRandom(int32_t min, int32_t max)
	{
		// Output random integer in the interval min <= x <= max
		// Relative error on frequencies < 2^-32
		if (max <= min) {
			if (max == min) return min; else return 0x80000000;
		}
		// Multiply interval with random and truncate
		auto r = int32_t((double)(uint32_t)(max - min + 1) * Random() + min);
		if (r > max) r = max;
		return r;
	}
	int32_t IRandomX(int32_t min, int32_t max) 
	{
		// Output random integer in the interval min <= x <= max
		// Each output value has exactly the same probability.
		// This is obtained by rejecting certain bit values so that the number
		// of possible bit values is divisible by the interval length
		if (max <= min) {
			if (max == min) return min; else return 0x80000000;
		}
		uint32_t interval;                    // Length of interval
		uint32_t bran;                        // Random bits
		uint32_t iran;                        // bran / interval
		uint32_t remainder;                   // bran % interval

		interval = uint32_t(max - min + 1);
		if (interval != LastInterval) {
			// Interval length has changed. Must calculate rejection limit
			// Reject when iran = 2^32 / interval
			// We can't make 2^32 so we use 2^32-1 and correct afterwards
			RLimit = (uint32_t)0xFFFFFFFF / interval;
			if ((uint32_t)0xFFFFFFFF % interval == interval - 1) RLimit++;
		}
		do { // Rejection loop
			bran = BRandom();
			iran = bran / interval;
			remainder = bran % interval;
		} while (iran >= RLimit);
		// Convert back to signed and return result
		return (int32_t)remainder + min;
	}
	uint32_t BRandom()
	{
		uint32_t y;

		if (idx >= MERS_N) {
			// Generate MERS_N words at one time
			const uint32_t LOWER_MASK = (1LU << MERS_R) - 1;       // Lower MERS_R bits
			const uint32_t UPPER_MASK = 0xFFFFFFFF << MERS_R;      // Upper (32 - MERS_R) bits
			static const uint32_t mag01[2] = { 0, MERS_A };

			int kk;
			for (kk = 0; kk < MERS_N - MERS_M; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + MERS_M] ^ (y >> 1) ^ mag01[y & 1];
			}

			for (; kk < MERS_N - 1; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + (MERS_M - MERS_N)] ^ (y >> 1) ^ mag01[y & 1];
			}

			y = (mt[MERS_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
			mt[MERS_N - 1] = mt[MERS_M - 1] ^ (y >> 1) ^ mag01[y & 1];
			idx = 0;
		}
		y = mt[idx++];

		// Tempering (May be omitted):
		y ^= y >> MERS_U;
		y ^= (y << MERS_S) & MERS_B;
		y ^= (y << MERS_T) & MERS_C;
		y ^= y >> MERS_L;

		return y;
	}
};
#endif // !RANDOM_H
