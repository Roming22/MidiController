#ifndef MOMENTARYSWITCH_H_
#define MOMENTARYSWITCH_H_

#include "Control.h"
/*
 * A momentary switch act on the engage and disengage actions.
 */
namespace midi {

class MomentarySwitch: public midi::Control {
public:
	MomentarySwitch(const int iChannel, const int iNote,
			hardware::Input* iInput, hardware::Output const * iOutput);
	virtual ~MomentarySwitch();

	virtual void handle();
};

} /* namespace midi */
#endif /* MOMENTARYSWITCH_H_ */
