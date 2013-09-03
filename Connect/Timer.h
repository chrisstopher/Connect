#ifndef _TIMER_H_
#define _TIMER_H_

#include "SDL.h"
#include "Position.h"
#include "Counter.h"

enum TIME_CONVERSION {
	MILLISECONDS_TO_SECONDS = 1000
};

class Timer {
public:
	Timer(float seconds);
	int milliseconds() const;
	int seconds() const;
	bool timesUp() const;
	bool lessThanOneSecondBeforeTimesUp();
	void reset();
	void reset(float seconds);
	void resetms(int ms);
	bool isRunning() const;
private:
	Uint32 countdown;
	bool start;
	int delay;
};

#endif
