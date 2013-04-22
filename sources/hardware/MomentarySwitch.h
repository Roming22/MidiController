/*
 * A momentary switch acts on the engage and disengage actions.
 */

#ifndef MOMENTARYSWITCH_H_
#define MOMENTARYSWITCH_H_

namespace hardware {

class MomentarySwitch: public OnOffController {
public:
	MomentarySwitch(const int iInputPin, const bool iInputInverted,
			const int iOutputPin);
	virtual ~MomentarySwitch();

	float getValue();
};

} /* namespace hardware */
#endif /* MOMENTARYSWITCH_H_ */
