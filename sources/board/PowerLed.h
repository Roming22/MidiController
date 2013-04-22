#ifndef POWERLED_H_
#define POWERLED_H_

#include "Output.h"

namespace board {

class PowerLed {
	board::DigitalOutput _output;
	int _on;
	int _off;
public:
	PowerLed(const int iPin, const int iOn = -1, const int iOff = -1);
	virtual ~PowerLed();

	void handle();
};

} /* namespace board */
#endif /* POWERLED_H_ */
