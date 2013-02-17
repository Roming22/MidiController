#ifndef INPUT_H_
#define INPUT_H_

#include "Teensy.h"

namespace hardware {

class Input {
protected:
	int _pin;
	bool _inverted;
	int _value;
	int _minValue;
	int _maxValue;
public:
	Input(const int iPin, const bool iInverted=false);
	virtual ~Input();
	virtual float read(); // Should return a value between 0 and 1.
protected:
	void autocalibrate();
	virtual int readPin() const = 0;
};

} /* namespace hardware */
#endif /* INPUT_H_ */
