#ifndef ANALOGINPUT_H_
#define ANALOGINPUT_H_

#include "Input.h"

namespace board {

class AnalogInput: public board::Input {
public:
	AnalogInput(const int iPin, const bool iInverted = false);
	virtual ~AnalogInput();
	virtual int readPin() const;
};

} /* namespace board */
#endif /* ANALOGINPUT_H_ */
