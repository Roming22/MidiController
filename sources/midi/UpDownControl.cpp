#include "PairedControl.h"

namespace midi {

UpDownControl::UpDownControl(const int iChannel, const int iNote,
		hardware::GenericController* iDownController,
		hardware::GenericController* iUpController, const int iStep,
		const int iMinValue, const int iMaxValue) :
		GenericControl(iChannel, iNote, iMinValue, iMaxValue), _step(iStep), _downController(
				iDownController), _upController(iUpController), _delta(0) {
}

UpDownControl::~UpDownControl() {
}

int UpDownControl::getValue() {
	deactivate();
	_delta=0;
	if (_downController->getValue() != 0) {
		_midiValue -= _step;
		_downController->setOutput(HIGH);
		--_delta;
	}
	if (_upController->getValue() != 0) {
		_midiValue += _step;
		_upController->setOutput(HIGH);
		++_delta;
	}

	if (_midiValue < _minMidiValue) {
		_midiValue = _minMidiValue;
	} else if (_midiValue > _maxMidiValue) {
		_midiValue = _maxMidiValue;
	}
	return _midiValue;
}

void UpDownControl::activate() {
	Serial.println(_delta);
	_downController->setOutput(_delta<0?HIGH:LOW);
	_upController->setOutput(_delta>0?HIGH:LOW);
}

void UpDownControl::deactivate() {
	_downController->setOutput(LOW);
	_upController->setOutput(LOW);
}

} /* namespace midi */
