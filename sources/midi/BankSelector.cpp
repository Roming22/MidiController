#include "BankSelector.h"
#include "Teensy.h"

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
