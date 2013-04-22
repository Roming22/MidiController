#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_

#include "Output.h"

namespace board {

class DigitalOutput: public board::Output {
public:
	DigitalOutput(const int iPin);
	virtual ~DigitalOutput();
	virtual void write(const int iValue) const;
};

} /* namespace board */
#endif /* DIGITALOUTPUT_H_ */
