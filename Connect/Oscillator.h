#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

#include "Timer.h"

class Oscillator {
public:
	Oscillator(float initialValue, float moveAmount, float minValue, float maxValue, bool oscil, float seconds);
	void update();
	float getValue() const;
	void setValue(float val);
private:
	float value, amount;
	float min, max;
	bool oscillate;
	Timer timer;
};

#endif

//template <class T>
//class Oscillator {
//public:
//	Oscillator(T& Value, T& Amount, T& Min, T& Max, bool Oscillate);
//	void update();
//	float getValue() const;
//private:
//	T value, amount, min, max;
//	bool oscillate;
//};