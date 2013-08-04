/*
 * AbstractControl.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef ABSTRACTCONTROL_H_
#define ABSTRACTCONTROL_H_

namespace midi {

class AbstractControl {
public:
	AbstractControl() {
	}

	virtual ~AbstractControl() {
	}

	virtual void handle() = 0;
	virtual void reset() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual int getValue() = 0;

protected:
	virtual void sendMessage() = 0;
};

} /* namespace midi */
#endif /* ABSTRACTCONTROL_H_ */
