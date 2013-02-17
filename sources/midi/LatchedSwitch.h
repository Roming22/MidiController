#ifndef LATCHEDSWITCH_H_
#define LATCHEDSWITCH_H_

#include "Control.h"

/*
 * A latched switch acts only on the engage action.
 * Note: if your hardware switch is already a latched switch,
 * you should use the UnlatchedSwitch class.
 */

namespace midi {

class LatchedSwitch: public midi::Control {
protected:
	int _state;
public:
	LatchedSwitch(const int iChannel, const int iNote,
			hardware::Input* iInput, hardware::Output const * iOutput);
	virtual ~LatchedSwitch();

	virtual void handle();
protected:
	int invert(int iValue);
	virtual bool hasChanged();
};

} /* namespace midi */
#endif /* LATCHEDSWITCH_H_ */
