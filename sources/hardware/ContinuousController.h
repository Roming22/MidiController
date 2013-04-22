/*
 * The continuous controller is self-calibrating.
 */
#ifndef CONTINUOUSCONTROLLER_H_
#define CONTINUOUSCONTROLLER_H_

namespace hardware {

class ContinuousController: public GenericController {
protected:
	int _knownMin;
	int _knownMax;

public:
	ContinuousController(const int iInputPin, const bool iInputInverted,
		const int iOutputPin);
	virtual ~ContinuousController();

	float getValue();
};

} /* namespace hardware */
#endif /* CONTINUOUSCONTROLLER_H_ */
