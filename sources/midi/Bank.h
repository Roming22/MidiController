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
