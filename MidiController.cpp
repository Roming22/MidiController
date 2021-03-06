
#include "WProgram.h"
#include "MidiController.h"

    

namespace board {

AnalogInput::AnalogInput(const int iPin, const bool iInverted) :
		Input(iPin, iInverted) {
	pinMode(_pin, INPUT);
}

AnalogInput::~AnalogInput() {
}

int AnalogInput::readPin() const {
	return analogRead(_pin);
}

} /* namespace board */

namespace board {

DigitalInput::DigitalInput(const int iPin, const bool iInverted) :
		Input(iPin, iInverted) {
	pinMode(_pin, INPUT_PULLUP);
	_minValue = LOW;
	_maxValue = HIGH;
}

DigitalInput::~DigitalInput() {
}

int DigitalInput::readPin() const {
	return digitalRead(_pin);
}

} /* namespace board */

namespace board {

DigitalOutput::DigitalOutput(const int iPin) :
		Output(iPin) {
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

DigitalOutput::~DigitalOutput() {
}

void DigitalOutput::write(const int iValue) const {
	digitalWrite(_pin, (iValue <= LOW ? LOW : HIGH));
}

} /* namespace board */

namespace board {

Input::Input(const int iPin, const bool iInverted) :
		_pin(iPin), _inverted(iInverted), _value(0), _minValue(1024), _maxValue(
				0) {
}

Input::~Input() {
}

float Input::read() {
	_value = readPin();
	autocalibrate();
	float pctValue = _value - _minValue; // Get value relative to the min value
	pctValue = (pctValue) / (float(_maxValue) - float(_minValue)); //get the value as a percentage
	if (_inverted) {
		pctValue = 1 - pctValue;
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

} /* namespace board */

namespace board {

Output::Output(const int iPin) :
		_pin(iPin) {
}

Output::~Output() {
}

} /* namespace board */

namespace board {

PowerLed::PowerLed(const int iPin, const int iOn, const int iOff) :
		_output(iPin), _on(iOn), _off(iOff) {
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

} /* namespace board */

namespace hardware {

ContinuousController::ContinuousController(const int iInputPin,
		const bool iInputInverted, const int iOutputPin) :
		GenericController(new board::AnalogInput(iInputPin, iInputInverted),
				new board::DigitalOutput(iOutputPin)), _knownMin(0), _knownMax(
				0) {
	_knownMin = getInternalValue();
	_knownMax = _knownMin;
}

ContinuousController::~ContinuousController() {
}

float ContinuousController::getValue() {
	_value = getInternalValue();
	if (_knownMin > _value) {
		_knownMin = _value;
	}
	if (_knownMax < _value) {
		_knownMax = _value;
	}
	return (_value - _knownMin) / (_knownMax - _knownMin);
}

} /* namespace hardware */

namespace hardware {

GenericController::GenericController(board::Input* iInput,
		board::Output const * iOutput) :
		_input(iInput), _output(iOutput), _value(0) {
	_value = getInternalValue();
}

GenericController::~GenericController() {
}

void GenericController::setOutput(const int iValue) {
	if (_output != 0) {
		_output->write(iValue);
	}
}

int GenericController::getInternalValue() {
	return _input->read();
}

} /* namespace hardware */

namespace hardware {

LatchedSwitch::LatchedSwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		OnOffController(iInputPin, iInputInverted, iOutputPin), _state(0), _value(
				0) {
	_state = getInternalValue();
	//Serial.println(_state);
}

LatchedSwitch::~LatchedSwitch() {
}

float LatchedSwitch::getValue() {
	if (_state == _restValue) {
		_state = getInternalValue();
		if (_state != _restValue) {
			_value = ++_value % 2;
		}
	}
	else{
		_state = getInternalValue();
	}
	//Serial.println(getInternalValue());
	return _value;
}

} /* namespace hardware */

namespace hardware {

MomentarySwitch::MomentarySwitch(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		OnOffController(iInputPin, iInputInverted, iOutputPin) {
}

MomentarySwitch::~MomentarySwitch() {
}

float MomentarySwitch::getValue() {
	_value = getInternalValue();
	return (_value == _restValue ? 0 : 1);
}

} /* namespace hardware */

namespace hardware {

OnOffController::OnOffController(const int iInputPin, const bool iInputInverted,
		const int iOutputPin) :
		GenericController(new board::DigitalInput(iInputPin, iInputInverted),
				new board::DigitalOutput(iOutputPin)), _restValue(0), _state(
				OFF_HOLD) {
	_restValue = getInternalValue();
}

OnOffController::~OnOffController() {
}

OnOffController::State OnOffController::getState() {
	return _state;
}

bool OnOffController::isState(const State iState) const {
	return _state == iState;
}

} /* namespace hardware */

namespace midi {

Bank::Bank(midi::AbstractControl** iBank, int iBankSize) :
		_bank(iBank), _bankSize(iBankSize) {
}

Bank::~Bank() {
}

void Bank::handle() {
	for (int id = 0; id < _bankSize; id++) {
		if (getControl(id) != 0) {
			getControl(id)->handle();
		}
	}

}

void Bank::activate() {
	for (int id = 0; id < _bankSize; id++) {
		if (getControl(id) != 0) {
			getControl(id)->activate();
		}
	}
}

void Bank::deactivate() {
	for (int id = 0; id < _bankSize; id++) {
		if (getControl(id) != 0) {
			getControl(id)->deactivate();
		}
	}
}

void Bank::reset() {
	for (int id = 0; id < _bankSize; id++) {
		if (getControl(id) != 0) {
			getControl(id)->reset();
		}
	}
}

midi::AbstractControl* Bank::getControl(const int index) {
	return _bank[index];
}

} /* namespace midi */

namespace midi {

BankSelector::BankSelector(hardware::OnOffController* iController,
		midi::Bank** iBanks, int iBankCount, bool iSharedLed) :
		_controller(iController), _bank(iBanks), _bankCount(iBankCount), _outputIsSharedWithPowerLed(
				iSharedLed), _currentBank(0) {
}

BankSelector::~BankSelector() {
}

void BankSelector::handle() {
	handleBankChange();
	getBank()->handle();
	if (_controller != 0) {
		handleOutput();
	}
}

void BankSelector::reset() {
	while (_currentBank < _bankCount) {
		getBank()->reset();
		++_currentBank;
	}
	_currentBank=0;
}

void BankSelector::handleBankChange() {
	int newBank = getValue();
	if (newBank != _currentBank) {
		getBank()->deactivate();
		_currentBank = newBank;
		getBank()->activate();
		Serial.print("Switching to bank ");
		Serial.println(_currentBank);
	}
}

void BankSelector::handleOutput() {
	if (_bankCount == 2) {
		if (_outputIsSharedWithPowerLed) {
			if (_currentBank == 1) {
				_controller->setOutput(HIGH);
			}
		} else {
			_controller->setOutput(_currentBank ? LOW : HIGH);
		}
	}
	// TODO : support more than 2 banks.
}

int BankSelector::getValue() {
	// TODO : support more than 2 banks.
	return int(_controller->getValue());
}

midi::Bank* BankSelector::getBank() {
	return _bank[_currentBank];
}

} /* namespace midi */
/*
 * DoubleActionControl.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */


namespace hardware {

DoubleActionControl::DoubleActionControl(const midi::MidiTarget iMidi1,
		const midi::MidiTarget iMidi2, hardware::GenericController* iController,
		const int iActivationDelay) :
		_midi1(iMidi1), _midi2(iMidi2), _activationDelay(iActivationDelay), _controller(
				iController), _currentDelay(0) {
}

DoubleActionControl::~DoubleActionControl() {
}

} /* namespace hardware */
/*
 * DoubleClickControl.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */


namespace midi {

DoubleClickControl::DoubleClickControl(const midi::MidiTarget iMidi1,
		const midi::MidiTarget iMidi2, hardware::GenericController* iController,
		const int iActivationDelay) : DoubleActionControl(iMidi1, iMidi2, iController, iActivationDelay) {
}

DoubleClickControl::~DoubleClickControl() {
}

} /* namespace midi */
/*
 * MidiTarget.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */


namespace midi {

MidiTarget::MidiTarget(const int iChannel, const int iNote, const int iMinValue,
		const int iMaxValue) :
		_channel(iChannel), _note(iNote), _value(iMinValue), _minValue(
				iMinValue), _maxValue(iMaxValue) {
}

MidiTarget::~MidiTarget() {
}

} /* namespace midi */

namespace midi {

SimpleControl::SimpleControl(const MidiTarget& iMidi,
		hardware::GenericController* iController) :
		SingleActionControl(iMidi), _controller(iController) {
}

SimpleControl::~SimpleControl() {
}

int SimpleControl::getValue() {
	return (_midi._maxValue - _midi._minValue) * _controller->getValue()
			+ _midi._minValue;
}

void SimpleControl::activate() {
	_controller->setOutput(_midi._value);
}

void SimpleControl::deactivate() {
	_controller->setOutput(LOW);
}

} /* namespace midi */

namespace midi {

SingleActionControl::SingleActionControl(const MidiTarget& iMidi) : _midi(iMidi) {
}

SingleActionControl::~SingleActionControl() {
}

void SingleActionControl::sendMessage() {
	usbMIDI.sendControlChange(_midi._note, _midi._value, _midi._channel);
	activate();
	Serial.print("Send control ");
	Serial.print(_midi._note);
	Serial.print("(");
	Serial.print(_midi._value);
	Serial.print(") on channel ");
	Serial.println(_midi._channel);
}

void SingleActionControl::handle() {
	int oldValue = _midi._value;
	_midi._value = getValue();
	if (oldValue != _midi._value) {
		sendMessage();
	}
}

void SingleActionControl::reset() {
	sendMessage();
}

} /* namespace midi */


namespace midi {

UpDownControl::UpDownControl(const MidiTarget& iMidi,
		hardware::GenericController* iDownController,
		hardware::GenericController* iUpController, const int iStep) :
		SingleActionControl(iMidi), _step(iStep), _downController(
				iDownController), _upController(iUpController), _delta(0) {
}

UpDownControl::~UpDownControl() {
}

int UpDownControl::getValue() {
	deactivate();
	_delta = 0;
	if (_downController->getValue() != 0) {
		_midi._value -= _step;
		_downController->setOutput(HIGH);
		--_delta;
	}
	if (_upController->getValue() != 0) {
		_midi._value += _step;
		_upController->setOutput(HIGH);
		++_delta;
	}

	if (_midi._value < _midi._minValue) {
		_midi._value = _midi._minValue;
	} else if (_midi._value > _midi._maxValue) {
		_midi._value = _midi._maxValue;
	}
	return _midi._value;
}

void UpDownControl::activate() {
	_downController->setOutput(_delta < 0 ? HIGH : LOW);
	_upController->setOutput(_delta > 0 ? HIGH : LOW);
}

void UpDownControl::deactivate() {
	_downController->setOutput(LOW);
	_upController->setOutput(LOW);
}

} /* namespace midi */
