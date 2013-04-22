#include "Bank.h"

namespace midi {

Bank::Bank(midi::GenericControl** iBank, int iBankSize) :
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

midi::GenericControl* Bank::getControl(const int index) {
	return _bank[index];
}

} /* namespace midi */
