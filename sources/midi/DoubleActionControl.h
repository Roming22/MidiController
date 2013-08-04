/*
 * DoubleActionControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef DOUBLEACTIONCONTROL_H_
#define DOUBLEACTIONCONTROL_H_

#include "AbstractControl.h"

namespace hardware {

class DoubleActionControl: public midi::AbstractControl {
protected:
	hardware::GenericController* _controller;
	midi::MidiTarget _midi1;
	midi::MidiTarget _midi2;
	int _currentDelay;
	int _activationDelay;

public:
	DoubleActionControl(const midi::MidiTarget iMidi1,
			const midi::MidiTarget iMidi2,
			hardware::GenericController* iController,
			const int iActivationDelay=10);
	virtual ~DoubleActionControl();
};

} /* namespace hardware */
#endif /* DOUBLEACTIONCONTROL_H_ */
