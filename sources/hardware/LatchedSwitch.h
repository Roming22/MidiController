/*
 * A latched switch acts only on the engage action.
 * Note: if your hardware switch is already a latched switch,
 * you should use the MomentarySwitch class.
 */

#ifndef LATCHEDSWITCH_H_
#define LATCHEDSWITCH_H_

namespace hardware {

class LatchedSwitch: public OnOffController {
protected:
	float _state;
	int _value;
public:
	LatchedSwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin);
	virtual ~LatchedSwitch();

	float getValue();
};

} /* namespace hardware */
#endif /* LATCHEDSWITCH_H_ */
