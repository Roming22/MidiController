#include "SingleActionControl.h"

namespace midi {

SingleActionControl::SingleActionControl(const MidiTarget& iMidi) : _midi(iMidi) {
}

SingleActionControl::~SingleActionControl() {
}

void SingleActionControl::sendMessage() {
	usbMIDI.sendControlChange(_midi._note, _midi._value, _midi._channel);
	activate();
	Serial.print("Send control ");
	Serial.print(_midi._note);
	Serial.print("(");
	Serial.print(_midi._value);
	Serial.print(") on channel ");
	Serial.println(_midi._channel);
}

void SingleActionControl::handle() {
	int oldValue = _midi._value;
	_midi._value = getValue();
	if (oldValue != _midi._value) {
		sendMessage();
	}
}

void SingleActionControl::reset() {
	sendMessage();
}

} /* namespace midi */
