/*
 * MidiTarget.h
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#ifndef MIDITARGET_H_
#define MIDITARGET_H_

namespace midi {

class MidiTarget {
public:
	int _channel;
	int _note;
	int _value;
	int _minValue;
	int _maxValue;

	MidiTarget(const int iChannel, const int iNote, const int iMinValue=0,
			const int iMaxValue=127);
	virtual ~MidiTarget();
};

} /* namespace midi */
#endif /* MIDITARGET_H_ */
