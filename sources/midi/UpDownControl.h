/*
 * Pair two switches to be able to increment/decrement a value.
 */

#ifndef UPDOWNCONTROL_H_
#define UPDOWNCONTROL_H_

namespace midi {

class UpDownControl: public GenericControl {
protected:
	hardware::GenericController* _upController;
	hardware::GenericController* _downController;
	int _step;
	int _delta;
public:
	UpDownControl(const int iChannel, const int iNote,
			hardware::GenericController* iDownController,
			hardware::GenericController* iUpController, const int iStep = 1,
			const int iMinValue = 0, const int iMaxValue = 127);
	virtual ~UpDownControl();

	virtual void activate();
	virtual void deactivate();
	int getValue();
};

} /* namespace midi */
#endif /* UPDOWNCONTROL_H_ */
