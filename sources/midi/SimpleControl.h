#ifndef SIMPLECONTROL_H_
#define SIMPLECONTROL_H_

namespace midi {

class SimpleControl: public GenericControl {
protected:
	hardware::GenericController* _controller;
public:
	SimpleControl(const int iChannel, const int iNote,
			hardware::GenericController* iController, const int iMinValue = 0,
			const int iMaxValue = 127);
	virtual ~SimpleControl();

	virtual void activate();
	virtual void deactivate();
	int getValue();
};

} /* namespace midi */
#endif /* SIMPLECONTROL_H_ */
