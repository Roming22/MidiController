#ifndef INPUT_H_
#define INPUT_H_


namespace hardware {

class Input {
protected:
	int _pin;
	bool _inverted;
	int _value;
	int _minValue;
	int _maxValue;
public:
	Input(const int iPin, const bool iInverted=false);
	virtual ~Input();
	virtual float read(); // Should return a value between 0 and 1.
protected:
	void autocalibrate();
	virtual int readPin() const = 0;
};

} /* namespace hardware */
#endif /* INPUT_H_ */
#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_


namespace hardware {

class DigitalInput: public hardware::Input {
public:
	DigitalInput(const int iPin, const bool iInverted=false);
	virtual ~DigitalInput();
	virtual int readPin() const;
};

} /* namespace hardware */
#endif /* DIGITALINPUT_H_ */
#ifndef ANALOGINPUT_H_
#define ANALOGINPUT_H_


namespace hardware {

class AnalogInput: public hardware::Input {
public:
	AnalogInput(const int iPin, const bool iInverted=false);
	virtual ~AnalogInput();
	virtual int readPin() const;
};

} /* namespace hardware */
#endif /* ANALOGINPUT_H_ */
#ifndef OUTPUT_H_
#define OUTPUT_H_
namespace hardware {

class Output {
protected:
	int _pin;
public:
	Output(const int iPin);
	virtual ~Output();
	virtual void write(const int iValue) const = 0;
};

} /* namespace hardware */
#endif /* OUTPUT_H_ */
#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_


namespace hardware {

class DigitalOutput: public hardware::Output {
public:
	DigitalOutput(const int iPin);
	virtual ~DigitalOutput();
	virtual void write(const int iValue) const;
};

} /* namespace hardware */
#endif /* DIGITALOUTPUT_H_ */
#ifndef POWERLED_H_
#define POWERLED_H_


namespace hardware {

class PowerLed {
	const hardware::Output& _output;
	int _on;
	int _off;
public:
	PowerLed(const hardware::Output& iOutput, const int iOn = -1,
			const int iOff = -1);
	virtual ~PowerLed();

	void handle();
};

} /* namespace hardware */
#endif /* POWERLED_H_ */
#ifndef CONTROL_H_
#define CONTROL_H_



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
#ifndef MOMENTARYSWITCH_H_
#define MOMENTARYSWITCH_H_

/*
 * A momentary switch act on the engage and disengage actions.
 */
namespace midi {

class MomentarySwitch: public midi::Control {
public:
	MomentarySwitch(const int iChannel, const int iNote,
			hardware::Input* iInput, hardware::Output const * iOutput);
	virtual ~MomentarySwitch();

	virtual void handle();
};

} /* namespace midi */
#endif /* MOMENTARYSWITCH_H_ */
#ifndef LATCHEDSWITCH_H_
#define LATCHEDSWITCH_H_


/*
 * A latched switch acts only on the engage action.
 * Note: if your hardware switch is already a latched switch,
 * you should use the UnlatchedSwitch class.
 */

namespace midi {

class LatchedSwitch: public midi::Control {
protected:
	int _state;
public:
	LatchedSwitch(const int iChannel, const int iNote,
			hardware::Input* iInput, hardware::Output const * iOutput);
	virtual ~LatchedSwitch();

	virtual void handle();
protected:
	int invert(int iValue);
	virtual bool hasChanged();
};

} /* namespace midi */
#endif /* LATCHEDSWITCH_H_ */
#ifndef BANKSELECTOR_H_
#define BANKSELECTOR_H_


namespace midi {

class BankSelector: public midi::LatchedSwitch {
	int _bankCount;
	int _bankSize;
	int _selectedId;
	midi::Control*** _bank;
	bool _outputIsSharedWithPowerLed;
public:
	//BankSelector(hardware::Input* iInput, hardware::Output* iOutput,
	//	int iBankCount, int iBankSize,
	//	bool iSharedLed);
	BankSelector(hardware::Input* iInput, hardware::Output* iOutput,
			midi::Control*** iBanks, int iBankCount, int iBankSize,
			bool iSharedLed);
	virtual ~BankSelector();

	void handle();

	void handleBankChange();
	void handleMidiControls();
	void handleOutput();

	midi::Control* getControl(int index);
};

} /* namespace midi */
#endif /* BANKSELECTOR_H_ */
