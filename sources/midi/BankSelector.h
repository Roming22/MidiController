#ifndef BANKSELECTOR_H_
#define BANKSELECTOR_H_

#include "LatchedSwitch.h"

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
