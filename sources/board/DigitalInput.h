#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_

#include "Input.h"

namespace board {

class DigitalInput: public board::Input {
public:
	DigitalInput(const int iPin, const bool iInverted = false);
	virtual ~DigitalInput();
	virtual int readPin() const;
};

} /* namespace board */
#endif /* DIGITALINPUT_H_ */
