#include "MomentarySwitch.h"

namespace hardware {

MomentarySwitch::MomentarySwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		OnOffController(iInputPin, iInputInverted, iOutputPin) {
}

MomentarySwitch::~MomentarySwitch() {
}

float MomentarySwitch::getValue() {
	_value = getInternalValue();
	return (_value == _restValue ? 0 : 1);
}

} /* namespace hardware */
