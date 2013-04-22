#include "LatchedSwitch.h"

namespace hardware {

LatchedSwitch::LatchedSwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		OnOffController(iInputPin, iInputInverted, iOutputPin), _state(0), _value(
				0) {
	_state = getInternalValue();
	//Serial.println(_state);
}

LatchedSwitch::~LatchedSwitch() {
}

float LatchedSwitch::getValue() {
	if (_state == _restValue) {
		_state = getInternalValue();
		if (_state != _restValue) {
			_value = ++_value % 2;
		}
	}
	else{
		_state = getInternalValue();
	}
	//Serial.println(getInternalValue());
	return _value;
}

} /* namespace hardware */
