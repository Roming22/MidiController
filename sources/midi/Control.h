#ifndef CONTROL_H_
#define CONTROL_H_

#include "Teensy.h"

#include "hardware/Input.h"
#include  "hardware/Output.h"

namespace midi {

class Control {
protected:
	// Bridge to hardware
	hardware::Input* _input;
	hardware::Output const * _output;

	// Bridge to MIDI
	int _channel;
	int _note;
	int _midiValue;
	int _minMidiValue;
	int _maxMidiValue;
public:
	Control(const int iChannel, const int iNote, hardware::Input* iInput,
			hardware::Output const * iOutput);
	virtual ~Control();

	virtual void handle() = 0;

	void activate();
	void deactivate();
protected:
	virtual bool hasChanged();
	void sendMessage();
};

} /* namespace midi */
#endif /* CONTROL_H_ */
