#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_

#include "Output.h"

namespace hardware {

class DigitalOutput: public hardware::Output {
public:
	DigitalOutput(const int iPin);
	virtual ~DigitalOutput();
	virtual void write(const int iValue) const;
};

} /* namespace hardware */
#endif /* DIGITALOUTPUT_H_ */
