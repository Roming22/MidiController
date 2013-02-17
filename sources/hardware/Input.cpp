#include "Input.h"

namespace hardware {

Input::Input(const int iPin, const bool iInverted) :
		_pin(iPin), _inverted(iInverted), _value(0), _minValue(1024), _maxValue(0) {
}

Input::~Input() {
}

float Input::read() {
	_value = readPin();
	autocalibrate();
	float pctValue = _value - _minValue; // Get value relative to the min value
	pctValue = (pctValue) / (float(_maxValue) - float(_minValue)); //get the value as a percentage
	if (_inverted){
		pctValue = 1-pctValue;
	}
	return pctValue;
}

void Input::autocalibrate() {
	if (_value < _minValue) {
		_minValue = _value;
	}
	if (_value > _maxValue) {
		_maxValue = _value;
	}
	if (_minValue >= _maxValue) {
		if (_maxValue > 0) {
			_minValue = _maxValue - 1;
		} else {
			_maxValue = _minValue + 1;
		}
	}
}

} /* namespace hardware */
