#include "MomentarySwitch.h"

namespace midi {

MomentarySwitch::MomentarySwitch(const int iChannel, const int iNote,
		hardware::Input* iInput, hardware::Output const * iOutput) :
		Control(iChannel, iNote, iInput, iOutput) {
}

MomentarySwitch::~MomentarySwitch() {
}

void MomentarySwitch::handle() {
	if (hasChanged()) {
		sendMessage();
	}
}

} /* namespace midi */
