/*
 * RealTimeClock.h
 *
 *  Created on: 13 Oct 2022
 *      Author: DBY
 */

#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_


#include <ctime>
#include "Imutex.h"



class RealTimeClock {
public:
	RealTimeClock(int tickPerSecond);
	RealTimeClock(int tickPerSecond, tm now);
	RealTimeClock(int tickPerSecond, time_t rawtime);
	virtual ~RealTimeClock();
	void gettime(tm *now);
	void tick();

private:
	Imutex guard;
	volatile time_t rawtime;
	volatile int hour;
	volatile int min;
	volatile int sec;
	const volatile int ticks_per_second;
	volatile int ticks_passed;
};

#endif /* REALTIMECLOCK_H_ */
