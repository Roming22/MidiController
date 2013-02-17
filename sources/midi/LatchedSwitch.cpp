#include "LatchedSwitch.h"

namespace midi {
LatchedSwitch::LatchedSwitch(const int iChannel, const int iNote, hardware::Input* iInput,
		hardware::Output const * iOutput) :
		Control(iChannel, iNote, iInput, iOutput), _state(0) {
}

LatchedSwitch::~LatchedSwitch() {
}

void LatchedSwitch::handle() {
	if (hasChanged()) {
		_midiValue = invert(_midiValue);
		sendMessage();
	}
}

int LatchedSwitch::invert(int iValue){
	return (iValue==_minMidiValue?_maxMidiValue:_minMidiValue);
}

bool LatchedSwitch::hasChanged(){
	int tmpMidi = _midiValue;
	_midiValue = _state;
	bool hasChanged = Control::hasChanged();
	_state = _midiValue;
	_midiValue = tmpMidi;
	return ( hasChanged && _state == _maxMidiValue);
}

} /* namespace midi */
