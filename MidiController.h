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
#ifndef BANK_H_
#define BANK_H_

namespace midi {

class Bank {
protected:
	int _bankSize;
	midi::GenericControl** _bank;

public:
	Bank(midi::GenericControl** iBank, int iBankSize);
	virtual ~Bank();

	void handle();
	void activate();
	void deactivate();
	void reset();

protected:
	midi::GenericControl* getControl(const int index);
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
