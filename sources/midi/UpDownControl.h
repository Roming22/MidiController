/*
 * Pair two switches to be able to increment/decrement a value.
 */

#ifndef UPDOWNCONTROL_H_
#define UPDOWNCONTROL_H_

namespace midi {

class UpDownControl: public SingleActionControl {
protected:
	hardware::GenericController* _upController;
	hardware::GenericController* _downController;
	int _step;
	int _delta;
public:
	UpDownControl(const MidiTarget& iMidi,
			hardware::GenericController* iDownController,
			hardware::GenericController* iUpController, const int iStep = 1);
	virtual ~UpDownControl();

	virtual void activate();
	virtual void deactivate();
	int getValue();
};

} /* namespace midi */
#endif /* UPDOWNCONTROL_H_ */
