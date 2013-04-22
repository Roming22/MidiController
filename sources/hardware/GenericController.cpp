#include "GenericController.h"

namespace hardware {

GenericController::GenericController(board::Input* iInput,
		board::Output const * iOutput) :
		_input(iInput), _output(iOutput), _value(0) {
	_value = getInternalValue();
}

GenericController::~GenericController() {
}

void GenericController::setOutput(const int iValue) {
	if (_output != 0) {
		_output->write(iValue);
	}
}

int GenericController::getInternalValue() {
	return _input->read();
}

} /* namespace hardware */
