#include "BankSelector.h"

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
