#include "AnalogInput.h"

namespace board {

AnalogInput::AnalogInput(const int iPin, const bool iInverted) :
		Input(iPin, iInverted) {
	pinMode(_pin, INPUT);
}

AnalogInput::~AnalogInput() {
}

int AnalogInput::readPin() const {
	return analogRead(_pin);
}

} /* namespace board */
