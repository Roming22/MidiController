#include "DigitalInput.h"

namespace hardware {

DigitalInput::DigitalInput(const int iPin, const bool iInverted) :
		Input(iPin ,iInverted) {
	pinMode(_pin, INPUT_PULLUP);
	_minValue = LOW;
	_maxValue = HIGH;
}

DigitalInput::~DigitalInput() {
}

int DigitalInput::readPin() const {
	return digitalRead(_pin);
}

} /* namespace hardware */
