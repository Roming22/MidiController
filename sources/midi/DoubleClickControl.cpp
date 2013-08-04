/*
 * DoubleClickControl.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#include "DoubleClickControl.h"

namespace midi {

DoubleClickControl::DoubleClickControl(const midi::MidiTarget iMidi1,
		const midi::MidiTarget iMidi2, hardware::GenericController* iController,
		const int iActivationDelay) : DoubleActionControl(iMidi1, iMidi2, iController, iActivationDelay) {
}

DoubleClickControl::~DoubleClickControl() {
}

} /* namespace midi */
