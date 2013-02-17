#include "Control.h"

namespace midi {

Control::Control(const int iChannel, const int iNote,
		hardware::Input* iInput, hardware::Output const * iOutput) :
		_input(iInput), _output(iOutput), _channel(iChannel), _note(iNote), _midiValue(
				0), _minMidiValue(0), _maxMidiValue(127) {
}

Control::~Control() {
}

bool Control::hasChanged() {
	if (_input != 0) {
		float newValue = _input->read();

		// Apply to the control range
		newValue = (newValue * (_maxMidiValue - _minMidiValue)) + _minMidiValue;
		if(newValue<_minMidiValue){
			newValue = _minMidiValue;
		}
		else if (newValue>_maxMidiValue){
			newValue = _maxMidiValue;
		}

		if (int(newValue) != _midiValue) {
			_midiValue = int(newValue);
			return true;
		}
	}
	return false;
}

void Control::sendMessage() {
	usbMIDI.sendControlChange(_note, _midiValue, _channel);
	activate();
	Serial.print("Send control ");
	Serial.print(_note);
	Serial.print("(");
	Serial.print(_midiValue);
	Serial.print(") on channel ");
	Serial.println(_channel);
}

void Control::activate() {
	if (_output != 0) {
		_output->write(_midiValue);
	}
}

void Control::deactivate() {
	if (_output != 0) {
		_output->write(LOW);
	}
}

} /* namespace midi */
