#include "ContinuousController.h"

namespace hardware {

ContinuousController::ContinuousController(const int iInputPin,
		const bool iInputInverted, const int iOutputPin) :
		GenericController(new board::AnalogInput(iInputPin, iInputInverted),
				new board::DigitalOutput(iOutputPin)), _knownMin(0), _knownMax(
				0) {
	_knownMin = getInternalValue();
	_knownMax = _knownMin;
}

ContinuousController::~ContinuousController() {
}

float ContinuousController::getValue() {
	_value = getInternalValue();
	if (_knownMin > _value) {
		_knownMin = _value;
	}
	if (_knownMax < _value) {
		_knownMax = _value;
	}
	return (_value - _knownMin) / (_knownMax - _knownMin);
}

} /* namespace hardware */
