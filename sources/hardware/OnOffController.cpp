#include "OnOffController.h"

namespace hardware {

OnOffController::OnOffController(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		GenericController(new board::DigitalInput(iInputPin, iInputInverted),
				new board::DigitalOutput(iOutputPin)), _restValue(0), _state(
				OFF_HOLD) {
	_restValue = getInternalValue();
}

OnOffController::~OnOffController() {
}

OnOffController::State OnOffController::getState() {
	return _state;
}

bool OnOffController::isState(const State iState) const {
	return _state == iState;
}

} /* namespace hardware */
