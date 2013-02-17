#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "Teensy.h"
namespace hardware {

class Output {
protected:
	int _pin;
public:
	Output(const int iPin);
	virtual ~Output();
	virtual void write(const int iValue) const = 0;
};

} /* namespace hardware */
#endif /* OUTPUT_H_ */
