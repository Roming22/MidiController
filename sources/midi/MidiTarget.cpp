/*
 * MidiTarget.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: rarnaud
 */

#include "MidiTarget.h"

namespace midi {

MidiTarget::MidiTarget(const int iChannel, const int iNote, const int iMinValue,
		const int iMaxValue) :
		_channel(iChannel), _note(iNote), _value(iMinValue), _minValue(
				iMinValue), _maxValue(iMaxValue) {
}

MidiTarget::~MidiTarget() {
}

} /* namespace midi */
