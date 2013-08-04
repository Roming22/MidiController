#ifndef INPUT_H_
#define INPUT_H_


namespace board {

class Input {
protected:
	int _pin;
	bool _inverted;
	int _value;
	int _minValue;
	int _maxValue;
public:
	Input(const int iPin, const bool iInverted = false);
	virtual ~Input();
	virtual float read(); // Should return a value between 0 and 1.
protected:
	void autocalibrate();
	virtual int readPin() const = 0;
};

} /* namespace board */
#endif /* INPUT_H_ */
#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_


namespace board {

class DigitalInput: public board::Input {
public:
	DigitalInput(const int iPin, const bool iInverted = false);
	virtual ~DigitalInput();
	virtual int readPin() const;
};

} /* namespace board */
#endif /* DIGITALINPUT_H_ */
#ifndef ANALOGINPUT_H_
#define ANALOGINPUT_H_


namespace board {

class AnalogInput: public board::Input {
public:
	AnalogInput(const int iPin, const bool iInverted = false);
	virtual ~AnalogInput();
	virtual int readPin() const;
};

} /* namespace board */
#endif /* ANALOGINPUT_H_ */
#ifndef OUTPUT_H_
#define OUTPUT_H_
namespace board {

class Output {
protected:
	int _pin;
public:
	Output(const int iPin);
	virtual ~Output();
	virtual void write(const int iValue) const = 0;
};

} /* namespace board */
#endif /* OUTPUT_H_ */
#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_


namespace board {

class DigitalOutput: public board::Output {
public:
	DigitalOutput(const int iPin);
	virtual ~DigitalOutput();
	virtual void write(const int iValue) const;
};

} /* namespace board */
#endif /* DIGITALOUTPUT_H_ */
#ifndef POWERLED_H_
#define POWERLED_H_


namespace board {

class PowerLed {
	board::DigitalOutput _output;
	int _on;
	int _off;
public:
	PowerLed(const int iPin, const int iOn = -1, const int iOff = -1);
	virtual ~PowerLed();

	void handle();
};

} /* namespace board */
#endif /* POWERLED_H_ */
/* The mother of all hardware controls.
 * A control must have an input, the output can be null.
 * The input sends a value between 0 and 1.
 * 0 is off, 1 is on, values in between are used by ContinuousController.
 */
#ifndef GENERICCONTROLLER_H_
#define GENERICCONTROLLER_H_

namespace hardware {

class GenericController {
protected:
	board::Input* _input;
	board::Output const * _output;
	int _value;

public:
	GenericController(board::Input* iInput, board::Output const * iOutput);
	virtual ~GenericController();

	void setOutput(int iValue);

	virtual float getValue() = 0; // Not const because it triggers a refresh

protected:
	int getInternalValue();
};

} /* namespace hardware */
#endif /* GENERICCONTROLLER_H_ */
#ifndef ONOFFCONTROLLER_H_
#define ONOFFCONTROLLER_H_

namespace hardware {

class OnOffController: public GenericController {

	enum State { ON_FRONT, ON_HOLD, OFF_FRONT, OFF_HOLD };

protected:
	int _restValue;
	State _state;

	State getState();

public:
	OnOffController(const int iInputPin, const bool iInputInverted,
			const int iOutputPin);
	virtual ~OnOffController();

	bool isState(const State iState) const;
};

} /* namespace hardware */
#endif /* ONOFFCONTROLLER_H_ */
/*
 * A latched switch acts only on the engage action.
 * Note: if your hardware switch is already a latched switch,
 * you should use the MomentarySwitch class.
 */

#ifndef LATCHEDSWITCH_H_
#define LATCHEDSWITCH_H_

namespace hardware {

class LatchedSwitch: public OnOffController {
protected:
	float _state;
	int _value;
public:
	LatchedSwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin);
	virtual ~LatchedSwitch();

	float getValue();
};

} /* namespace hardware */
#endif /* LATCHEDSWITCH_H_ */
/*
 * A momentary switch acts on the engage and disengage actions.
 */

#ifndef MOMENTARYSWITCH_H_
#define MOMENTARYSWITCH_H_

namespace hardware {

class MomentarySwitch: public OnOffController {
public:
	MomentarySwitch(const int iInputPin, const bool iInputInverted,
			const int iOutputPin);
	virtual ~MomentarySwitch();

	float getValue();
};

} /* namespace hardware */
#endif /* MOMENTARYSWITCH_H_ */
/*
 * The continuous controller is self-calibrating.
 */
#ifndef CONTINUOUSCONTROLLER_H_
#define CONTINUOUSCONTROLLER_H_

namespace hardware {

class ContinuousController: public GenericController {
protected:
	int _knownMin;
	int _knownMax;

public:
	ContinuousController(const int iInputPin, const bool iInputInverted,
		const int iOutputPin);
	virtual ~ContinuousController();

	float getValue();
};

} /* namespace hardware */
#endif /* CONTINUOUSCONTROLLER_H_ */
/*
 * MidiTarget.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef MIDITARGET_H_
#define MIDITARGET_H_

namespace midi {

class MidiTarget {
public:
	int _channel;
	int _note;
	int _value;
	int _minValue;
	int _maxValue;

	MidiTarget(const int iChannel, const int iNote, const int iMinValue=0,
			const int iMaxValue=127);
	virtual ~MidiTarget();
};

} /* namespace midi */
#endif /* MIDITARGET_H_ */
/*
 * AbstractControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef ABSTRACTCONTROL_H_
#define ABSTRACTCONTROL_H_

namespace midi {

class AbstractControl {
public:
	AbstractControl() {
	}

	virtual ~AbstractControl() {
	}

	virtual void handle() = 0;
	virtual void reset() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual int getValue() = 0;

protected:
	virtual void sendMessage() = 0;
};

} /* namespace midi */
#endif /* ABSTRACTCONTROL_H_ */
/*
 * The mother of all MIDI controls.
 *
 * A min and max value are available, but it is probably best to configure
 * your software instead of the controller.
 */
#ifndef SINGLEACTIONCONTROL_H_
#define SINGLEACTIONCONTROL_H_


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
/*
 * DoubleActionControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef DOUBLEACTIONCONTROL_H_
#define DOUBLEACTIONCONTROL_H_


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
/*
 * DoubleClickControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef DOUBLECLICKCONTROL_H_
#define DOUBLECLICKCONTROL_H_


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
#ifndef BANK_H_
#define BANK_H_

namespace midi {

class Bank {
protected:
	int _bankSize;
	midi::AbstractControl** _bank;

public:
	Bank(midi::AbstractControl** iBank, int iBankSize);
	virtual ~Bank();

	void handle();
	void activate();
	void deactivate();
	void reset();

protected:
	midi::AbstractControl* getControl(const int index);
};

} /* namespace midi */
#endif /* BANK_H_ */
#ifndef BANKSELECTOR_H_
#define BANKSELECTOR_H_

namespace midi {

class BankSelector {
	hardware::OnOffController* _controller;
	int _bankCount;
	int _currentBank;
	midi::Bank** _bank;
	bool _outputIsSharedWithPowerLed;
public:
	BankSelector(hardware::OnOffController* iController, midi::Bank** iBanks,
			int iBankCount, bool iSharedLed);
	virtual ~BankSelector();

	void handle();
	void reset();

protected:
	midi::Bank* getBank();
	void handleOutput();
	int getValue();
	void handleBankChange();
};

} /* namespace midi */
#endif /* BANKSELECTOR_H_ */
