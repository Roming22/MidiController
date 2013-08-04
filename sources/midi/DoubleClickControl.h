/*
 * DoubleClickControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef DOUBLECLICKCONTROL_H_
#define DOUBLECLICKCONTROL_H_

#include "DoubleActionControl.h"

namespace midi {

class DoubleClickControl: public hardware::DoubleActionControl {
public:
	DoubleClickControl(const midi::MidiTarget iMidi1,
			const midi::MidiTarget iMidi2, hardware::GenericController* iController,
			const int iActivationDelay);
	virtual ~DoubleClickControl();
};

} /* namespace midi */
#endif /* DOUBLECLICKCONTROL_H_ */
