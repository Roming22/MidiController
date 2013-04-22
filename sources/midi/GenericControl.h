/*
 * The mother of all MIDI controls.
 *
 * A min and max value are available, but it is probably best to configure
 * your software instead of the controller.
 */
#ifndef GENERICCONTROL_H_
#define GENERICCONTROL_H_

namespace midi {

class GenericControl {
protected:
	int _channel;
	int _note;
	int _midiValue;
	int _minMidiValue;
	int _maxMidiValue;

public:
	GenericControl(const int iChannel, const int iNote, const int iMinValue,
			const int iMaxValue);
	virtual ~GenericControl();

	void handle();
	void reset();

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual int getValue() = 0;

protected:
	void sendMessage();
};

} /* namespace midi */
#endif /* GENERICCONTROL_H_ */
