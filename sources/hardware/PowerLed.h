#ifndef POWERLED_H_
#define POWERLED_H_

#include "Output.h"

namespace hardware {

class PowerLed {
	const hardware::Output& _output;
	int _on;
	int _off;
public:
	PowerLed(const hardware::Output& iOutput, const int iOn = -1,
			const int iOff = -1);
	virtual ~PowerLed();

	void handle();
};

} /* namespace hardware */
#endif /* POWERLED_H_ */
