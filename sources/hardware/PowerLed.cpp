#include "PowerLed.h"

namespace hardware {

PowerLed::PowerLed(const hardware::Output& iOutput, const int iOn,
		const int iOff) :
		_output(iOutput), _on(iOn), _off(iOff) {
	if (iOn < 0) {
		_on = 10;
	}
	if (iOff < 0) {
		_off = iOn;
	}
}

PowerLed::~PowerLed() {
}

void PowerLed::handle() {
	static int counter = 0;
	static bool state = true;

	// Asymmetrical blinking
	if (state) {
		counter = (1 + counter) % _on;
	} else {
		counter = (1 + counter) % _off;
	}

	// Blink the LED
	if (1 == counter) {
		state = !state;
		_output.write(state ? HIGH : LOW);
	}
}

} /* namespace hardware */
