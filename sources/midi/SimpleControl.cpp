#include "SimpleControl.h"
#include ".teensy/Teensy.h"

namespace midi {

SimpleControl::SimpleControl(const MidiTarget& iMidi,
		hardware::GenericController* iController) :
		SingleActionControl(iMidi), _controller(iController) {
}

SimpleControl::~SimpleControl() {
}

int SimpleControl::getValue() {
	return (_midi._maxValue - _midi._minValue) * _controller->getValue()
			+ _midi._minValue;
}

void SimpleControl::activate() {
	_controller->setOutput(_midi._value);
}

void SimpleControl::deactivate() {
	_controller->setOutput(LOW);
}

} /* namespace midi */
