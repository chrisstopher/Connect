#include "NoTimer.h"

NoTimer::NoTimer() : Timer(0) {
	
}

int NoTimer::milliseconds() const {
	return 0;
}

int NoTimer::seconds() const {
	return 0;
}

bool NoTimer::timesUp() const {
	return true;
}

bool NoTimer::lessThanOneSecondBeforeTimesUp() {
	return false;
}

void NoTimer::reset() {
	
}

void NoTimer::reset(float seconds) {
	
}

void NoTimer::resetms(int ms) {
	
}

bool NoTimer::isRunning() const {
	return false;
}

int NoTimer::getDelayInSeconds() {
	return 0;
}