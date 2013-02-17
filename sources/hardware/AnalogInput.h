#ifndef ANALOGINPUT_H_
#define ANALOGINPUT_H_

#include "Input.h"

namespace hardware {

class AnalogInput: public hardware::Input {
public:
	AnalogInput(const int iPin, const bool iInverted=false);
	virtual ~AnalogInput();
	virtual int readPin() const;
};

} /* namespace hardware */
#endif /* ANALOGINPUT_H_ */
