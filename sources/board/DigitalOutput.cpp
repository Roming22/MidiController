#include "DigitalOutput.h"

namespace board {

DigitalOutput::DigitalOutput(const int iPin) :
		Output(iPin) {
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

DigitalOutput::~DigitalOutput() {
}

void DigitalOutput::write(const int iValue) const {
	digitalWrite(_pin, (iValue <= LOW ? LOW : HIGH));
}

} /* namespace board */
