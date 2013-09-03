#include "Timer.h"

Timer::Timer(float seconds) {
	start = seconds > 0;
	reset(seconds);
}

int Timer::milliseconds() const {
	return countdown - SDL_GetTicks();
}

int Timer::seconds() const {
	return (countdown - SDL_GetTicks()) / MILLISECONDS_TO_SECONDS;
}

bool Timer::timesUp() const {
	if (!start) {
		return true;
	}
	if (SDL_GetTicks() >= countdown) {
		return true;
	}
	return false;
}

bool Timer::lessThanOneSecondBeforeTimesUp() {
	if (!start) {
		return false;
	}
	return seconds() < 1;
}

void Timer::reset() {
	if (!start) {
		return;
	}
	countdown = SDL_GetTicks() + delay;
}

/*
converts the number to milliseconds
then adds the start time minus the last three digits the hundreds, tens, ones placement
minus 1 for offset so it will not show 1 seconds above
*/
void Timer::reset(float seconds) {
	if (!start) {
		return;
	}
	delay = seconds * MILLISECONDS_TO_SECONDS;
	countdown = SDL_GetTicks() + delay;
	countdown--;
}
void Timer::resetms(int ms) {
	if (!start) {
		return;
	}
	delay = ms;
	countdown = SDL_GetTicks() + ms;
}

bool Timer::isRunning() const {
	return start;
}