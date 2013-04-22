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
