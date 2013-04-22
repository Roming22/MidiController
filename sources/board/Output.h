#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "Teensy.h"
namespace board {

class Output {
protected:
	int _pin;
public:
	Output(const int iPin);
	virtual ~Output();
	virtual void write(const int iValue) const = 0;
};

} /* namespace board */
#endif /* OUTPUT_H_ */
