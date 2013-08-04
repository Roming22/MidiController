#ifndef SIMPLECONTROL_H_
#define SIMPLECONTROL_H_

namespace midi {

class SimpleControl: public SingleActionControl {
protected:
	hardware::GenericController* _controller;
public:
	SimpleControl(const MidiTarget& iMidi,
			hardware::GenericController* iController);
	virtual ~SimpleControl();

	virtual void activate();
	virtual void deactivate();
	int getValue();
};

} /* namespace midi */
#endif /* SIMPLECONTROL_H_ */
