#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_

#include "Input.h"

namespace hardware {

class DigitalInput: public hardware::Input {
public:
	DigitalInput(const int iPin, const bool iInverted=false);
	virtual ~DigitalInput();
	virtual int readPin() const;
};

} /* namespace hardware */
#endif /* DIGITALINPUT_H_ */
