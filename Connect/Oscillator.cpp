#include "Oscillator.h"

/*
Example if oscillate is true
Oscillator example(0, 1, -5, 5, true, 1);
So it starts out at 0 and every 1 second it moves down 1
If the value touches 5 or goes past it the value = 5 and the amount gets negated
If the value touches -5 or goes past it the value = -5 and the amount gets negative
Value getting updated every 1 second with the move amount being 1
0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> -1 -> -2 -> -3 -> -4 -> -5 -> -4 -> -3 -> -2 -> -1 -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> ...

Oscillator example(0, -1, -5, 5, true, 1);//with negative move
0 -> -1 -> -2 -> -3 -> -4 -> -5 -> -4 -> -3 -> -2 -> -1 -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> -1 -> -2 -> -3 -> -4 -> -5 ...

Example if no oscillation: may or may not hit the value at the max and min limit
Oscillator example(0, 2, -5, 5, false, 1);
So this one jumps
If value <= min value = max
If value >= max value = min
Value getting updated every 1 second with the move amount being 2
0 -> 2 -> 4 -> -5 -> -3 -> -1 -> 1 -> 3 -> 5 -> -5 -> -3 -> -1 -> 1 -> 3 -> 5 ...


Oscillator example(0, -2, -5, 5, true, 1);//with negative move
0 -> -2 -> -4 -> 5 -> 3 -> 1 -> -1 -> -3 -> -5 -> 5 -> 3 -> 1 ...
*/

Oscillator::Oscillator(float initialValue, float moveAmount, float minValue, float maxValue, bool oscil, float seconds)
		   : value(initialValue), amount(moveAmount), min(minValue), max(maxValue), oscillate(oscil), timer(seconds) {

}

void Oscillator::update() {
	if (!timer.timesUp()) {
		return;
	}
	timer.reset();
	value += amount;
	if (oscillate) {
		if (value <= min) {
			value = min;
			amount = -amount;
		} else if (value >= max) {
			value = max;
			amount = -amount;
		}
	} else {
		if (value < min) {
			value = max;
		} else if (value > max) {
			value = min;
		}
	}
}

float Oscillator::getValue() const {
	return value;
}

void Oscillator::setValue(float val) {
	value = val;
}