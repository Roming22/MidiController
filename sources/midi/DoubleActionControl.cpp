/*
 * DoubleActionControl.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#include "DoubleActionControl.h"

namespace hardware {

DoubleActionControl::DoubleActionControl(const midi::MidiTarget iMidi1,
		const midi::MidiTarget iMidi2, hardware::GenericController* iController,
		const int iActivationDelay) :
		_midi1(iMidi1), _midi2(iMidi2), _activationDelay(iActivationDelay), _controller(
				iController), _currentDelay(0) {
}

DoubleActionControl::~DoubleActionControl() {
}

} /* namespace hardware */
