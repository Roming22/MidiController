#include "GenericControl.h"

namespace midi {

GenericControl::GenericControl(const int iChannel, const int iNote,
		const int iMinValue, const int iMaxValue) :
		_channel(iChannel), _note(iNote), _midiValue(iMinValue), _minMidiValue(
				iMinValue), _maxMidiValue(iMaxValue) {
}

GenericControl::~GenericControl() {
}

void GenericControl::sendMessage() {
	usbMIDI.sendControlChange(_note, _midiValue, _channel);
	activate();
	Serial.print("Send control ");
	Serial.print(_note);
	Serial.print("(");
	Serial.print(_midiValue);
	Serial.print(") on channel ");
	Serial.println(_channel);
}

void GenericControl::handle() {
	int oldValue = _midiValue;
	_midiValue = getValue();
	if (oldValue != _midiValue) {
		sendMessage();
	}
}

void GenericControl::reset() {
	sendMessage();
}

} /* namespace midi */
