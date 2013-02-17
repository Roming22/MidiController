
#include "WProgram.h"
#include "MidiController.h"

    

namespace hardware {

AnalogInput::AnalogInput(const int iPin, const bool iInverted) :
		Input(iPin, iInverted) {
	pinMode(_pin, INPUT);
}

AnalogInput::~AnalogInput() {
}

int AnalogInput::readPin() const {
	return analogRead(_pin);
}

} /* namespace hardware */

namespace hardware {

DigitalInput::DigitalInput(const int iPin, const bool iInverted) :
		Input(iPin ,iInverted) {
	pinMode(_pin, INPUT_PULLUP);
	_minValue = LOW;
	_maxValue = HIGH;
}

DigitalInput::~DigitalInput() {
}

int DigitalInput::readPin() const {
	return digitalRead(_pin);
}

} /* namespace hardware */

namespace hardware {

DigitalOutput::DigitalOutput(const int iPin) : Output(iPin) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

DigitalOutput::~DigitalOutput() {
}

void DigitalOutput::write(const int iValue) const{
    digitalWrite(_pin, (iValue<=LOW?LOW:HIGH));
}

} /* namespace hardware */

namespace hardware {

Input::Input(const int iPin, const bool iInverted) :
		_pin(iPin), _inverted(iInverted), _value(0), _minValue(1024), _maxValue(0) {
}

Input::~Input() {
}

float Input::read() {
	_value = readPin();
	autocalibrate();
	float pctValue = _value - _minValue; // Get value relative to the min value
	pctValue = (pctValue) / (float(_maxValue) - float(_minValue)); //get the value as a percentage
	if (_inverted){
		pctValue = 1-pctValue;
	}
	return pctValue;
}

void Input::autocalibrate() {
	if (_value < _minValue) {
		_minValue = _value;
	}
	if (_value > _maxValue) {
		_maxValue = _value;
	}
	if (_minValue >= _maxValue) {
		if (_maxValue > 0) {
			_minValue = _maxValue - 1;
		} else {
			_maxValue = _minValue + 1;
		}
	}
}

} /* namespace hardware */

namespace hardware {

Output::Output(const int iPin) :
		_pin(iPin) {
}

Output::~Output() {
}

} /* namespace hardware */

namespace hardware {

PowerLed::PowerLed(const hardware::Output& iOutput, const int iOn,
		const int iOff) :
		_output(iOutput), _on(iOn), _off(iOff) {
	if (iOn < 0) {
		_on = 10;
	}
	if (iOff < 0) {
		_off = iOn;
	}
}

PowerLed::~PowerLed() {
}

void PowerLed::handle() {
	static int counter = 0;
	static bool state = true;

	// Asymmetrical blinking
	if (state) {
		counter = (1 + counter) % _on;
	} else {
		counter = (1 + counter) % _off;
	}

	// Blink the LED
	if (1 == counter) {
		state = !state;
		_output.write(state ? HIGH : LOW);
	}
}

} /* namespace hardware */

namespace midi {

BankSelector::BankSelector(hardware::Input* iInput, hardware::Output* iOutput,
		midi::Control*** iBanks, int iBankCount, int iBankSize, bool iSharedLed) :
		LatchedSwitch(0, 0, iInput, iOutput), _bank(iBanks), _bankCount(
				iBankCount), _bankSize(iBankSize), _outputIsSharedWithPowerLed(
				iSharedLed), _selectedId(0) {
}

BankSelector::~BankSelector() {
}

void BankSelector::handle() {
	handleBankChange();

	handleMidiControls();

	if (_output != 0) {
		handleOutput();
	}
}

void BankSelector::handleBankChange() {
	if (hasChanged()) {
		for (int id = 0; id < _bankSize; id++) {
			if (getControl(id) != 0) {
				getControl(id)->deactivate();
			}
		}
		_selectedId = (_selectedId + 1) % _bankCount;
		for (int id = 0; id < _bankSize; id++) {
			if (getControl(id) != 0) {
				getControl(id)->activate();
			}
		}
		Serial.print("Switching to bank ");
		Serial.println(_selectedId);
	}
}

void BankSelector::handleMidiControls() {
	for (int id = 0; id < _bankSize; id++) {
		if (getControl(id) != 0) {
			getControl(id)->handle();
		}
	}

}

void BankSelector::handleOutput() {
	if (_bankCount == 2) {
		if (_outputIsSharedWithPowerLed) {
			if (_selectedId == 1) {
				_output->write(HIGH);
			}
		} else {
			_output->write(_selectedId ? LOW : HIGH);
		}
	}
	// TODO : support more than 2 banks.
}
midi::Control* BankSelector::getControl(int index) {
	return _bank[_selectedId][index];
}

} /* namespace midi */

namespace midi {

Control::Control(const int iChannel, const int iNote,
		hardware::Input* iInput, hardware::Output const * iOutput) :
		_input(iInput), _output(iOutput), _channel(iChannel), _note(iNote), _midiValue(
				0), _minMidiValue(0), _maxMidiValue(127) {
}

Control::~Control() {
}

bool Control::hasChanged() {
	if (_input != 0) {
		float newValue = _input->read();

		// Apply to the control range
		newValue = (newValue * (_maxMidiValue - _minMidiValue)) + _minMidiValue;
		if(newValue<_minMidiValue){
			newValue = _minMidiValue;
		}
		else if (newValue>_maxMidiValue){
			newValue = _maxMidiValue;
		}

		if (int(newValue) != _midiValue) {
			_midiValue = int(newValue);
			return true;
		}
	}
	return false;
}

void Control::sendMessage() {
	usbMIDI.sendControlChange(_note, _midiValue, _channel);
	activate();
	Serial.print("Send control ");
	Serial.print(_note);
	Serial.print("(");
	Serial.print(_midiValue);
	Serial.print(") on channel ");
	Serial.println(_channel);
}

void Control::activate() {
	if (_output != 0) {
		_output->write(_midiValue);
	}
}

void Control::deactivate() {
	if (_output != 0) {
		_output->write(LOW);
	}
}

} /* namespace midi */

namespace midi {
LatchedSwitch::LatchedSwitch(const int iChannel, const int iNote, hardware::Input* iInput,
		hardware::Output const * iOutput) :
		Control(iChannel, iNote, iInput, iOutput), _state(0) {
}

LatchedSwitch::~LatchedSwitch() {
}

void LatchedSwitch::handle() {
	if (hasChanged()) {
		_midiValue = invert(_midiValue);
		sendMessage();
	}
}

int LatchedSwitch::invert(int iValue){
	return (iValue==_minMidiValue?_maxMidiValue:_minMidiValue);
}

bool LatchedSwitch::hasChanged(){
	int tmpMidi = _midiValue;
	_midiValue = _state;
	bool hasChanged = Control::hasChanged();
	_state = _midiValue;
	_midiValue = tmpMidi;
	return ( hasChanged && _state == _maxMidiValue);
}

} /* namespace midi */

namespace midi {

MomentarySwitch::MomentarySwitch(const int iChannel, const int iNote,
		hardware::Input* iInput, hardware::Output const * iOutput) :
		Control(iChannel, iNote, iInput, iOutput) {
}

MomentarySwitch::~MomentarySwitch() {
}

void MomentarySwitch::handle() {
	if (hasChanged()) {
		sendMessage();
	}
}

} /* namespace midi */
