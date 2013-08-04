/*
 * The mother of all MIDI controls.
 *
 * A min and max value are available, but it is probably best to configure
 * your software instead of the controller.
 */
#ifndef SINGLEACTIONCONTROL_H_
#define SINGLEACTIONCONTROL_H_

#include "AbstractControl.h"
#include "MidiTarget.h"

namespace midi {

class SingleActionControl : public AbstractControl{
protected:
	MidiTarget _midi;

public:
	SingleActionControl(const MidiTarget& iMidi);
	virtual ~SingleActionControl();

	void handle();
	void reset();

protected:
	void sendMessage();
};

} /* namespace midi */
#endif /* SINGLEACTIONCONTROL_H_ */
