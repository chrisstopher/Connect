#ifndef _NO_TIMER_H_
#define _NO_TIMER_H_

#include "Timer.h"

//class used if the user does not specify a time limit so I do not have to use if's

class NoTimer : public Timer {
public:
	NoTimer();
	int milliseconds() const;
	int seconds() const;
	bool timesUp() const;
	bool lessThanOneSecondBeforeTimesUp();
	void reset();
	void reset(float seconds);
	void resetms(int ms);
	bool isRunning() const;
	int getDelayInSeconds();
};

#endif