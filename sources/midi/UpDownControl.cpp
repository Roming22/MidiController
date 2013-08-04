#include "PairedControl.h"

#include ".teensy/Teensy.h"

namespace midi {

UpDownControl::UpDownControl(const MidiTarget& iMidi,
		hardware::GenericController* iDownController,
		hardware::GenericController* iUpController, const int iStep) :
		SingleActionControl(iMidi), _step(iStep), _downController(
				iDownController), _upController(iUpController), _delta(0) {
}

UpDownControl::~UpDownControl() {
}

int UpDownControl::getValue() {
	deactivate();
	_delta = 0;
	if (_downController->getValue() != 0) {
		_midi._value -= _step;
		_downController->setOutput(HIGH);
		--_delta;
	}
	if (_upController->getValue() != 0) {
		_midi._value += _step;
		_upController->setOutput(HIGH);
		++_delta;
	}

	if (_midi._value < _midi._minValue) {
		_midi._value = _midi._minValue;
	} else if (_midi._value > _midi._maxValue) {
		_midi._value = _midi._maxValue;
	}
	return _midi._value;
}

void UpDownControl::activate() {
	_downController->setOutput(_delta < 0 ? HIGH : LOW);
	_upController->setOutput(_delta > 0 ? HIGH : LOW);
}

void UpDownControl::deactivate() {
	_downController->setOutput(LOW);
	_upController->setOutput(LOW);
}

} /* namespace midi */
