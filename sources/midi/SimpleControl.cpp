#include "SimpleControl.h"

namespace midi {

SimpleControl::SimpleControl(const int iChannel, const int iNote,
		hardware::GenericController* iController, const int iMinValue,
		const int iMaxValue) :
		GenericControl(iChannel, iNote, iMinValue, iMaxValue), _controller(
				iController) {
}

SimpleControl::~SimpleControl() {
}

int SimpleControl::getValue() {
	return (_maxMidiValue - _minMidiValue) * _controller->getValue()
			+ _minMidiValue;
}

void SimpleControl::activate() {
		_controller->setOutput(_midiValue);
}

void SimpleControl::deactivate() {
	_controller->setOutput(LOW);
}

} /* namespace midi */
