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
