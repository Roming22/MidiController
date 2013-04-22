#ifndef ONOFFCONTROLLER_H_
#define ONOFFCONTROLLER_H_

namespace hardware {

class OnOffController: public GenericController {

	enum State { ON_FRONT, ON_HOLD, OFF_FRONT, OFF_HOLD };

protected:
	int _restValue;
	State _state;

	State getState();

public:
	OnOffController(const int iInputPin, const bool iInputInverted,
			const int iOutputPin);
	virtual ~OnOffController();

	bool isState(const State iState) const;
};

} /* namespace hardware */
#endif /* ONOFFCONTROLLER_H_ */
