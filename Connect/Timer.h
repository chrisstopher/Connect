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
	virtual int milliseconds() const;
	virtual int seconds() const;
	virtual bool timesUp() const;
	virtual bool lessThanOneSecondBeforeTimesUp();
	virtual void reset();
	virtual void reset(float seconds);
	virtual void resetms(int ms);
	virtual bool isRunning() const;
	virtual int getDelayInSeconds();
private:
	Uint32 countdown;
	int delay;
};

#endif
