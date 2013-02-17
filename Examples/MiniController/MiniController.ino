/*
 * This code is for a device with 3 momentary switches and 3 LEDs.
 *
 * It is able to send 4 different CC messages.
 *
 * The fist step is to define which pins will be used for input and output.
 * The second step is to define the MIDI controls and link them to the I/O pins.
 * The third step is to create banks and link the selection to an I/O.
 */

#include <MIDI.h>
#include <MidiController.h>

#define SWITCH_COUNT 3 		// How many physical switches we have
#define MIDI_CTRL_COUNT 2	// How many physical switches will send MIDI messages
#define BANK_COUNT 2		// How many banks are going to be created
#define MIDI_CHANNEL 1		// MIDI channel on which the CC will be sent


/*
 * Create hardware inputs/outputs
 */

// The list of pins to read
hardware::Input* gInput[SWITCH_COUNT] = {
		new hardware::DigitalInput(4, true),
		new hardware::DigitalInput(7, true),
		new hardware::DigitalInput(9, true)
};

// The list of pins to write
hardware::Output* gOutput[SWITCH_COUNT] = {
		new hardware::DigitalOutput(5),
		new hardware::DigitalOutput(8),
		new hardware::DigitalOutput(10)
};

// The output for the PowerLed will be shared with the bank selector
hardware::PowerLed gPowerLed(*gOutput[0], 13, 26);


/*
 *  Create MIDI controls
 */

// The list of MIDI commands the device supports.
midi::Control* gMidiControl[4] = {
		new midi::LatchedSwitch(MIDI_CHANNEL, 20, gInput[1], gOutput[1]),
		new midi::MomentarySwitch(MIDI_CHANNEL, 21, gInput[2], gOutput[2]),
		new midi::MomentarySwitch(MIDI_CHANNEL, 110, gInput[1], gOutput[1]),
		new midi::LatchedSwitch(MIDI_CHANNEL, 111, gInput[2], gOutput[2])
};

/*
 * Create the BankSelector
 */

// The first bank has the CC20 and CC21 controls
midi::Control* gBank0[MIDI_CTRL_COUNT] = { gMidiControl[0], gMidiControl[1] };

// The second bank has the CC110 and CC111 controls
midi::Control* gBank1[MIDI_CTRL_COUNT] = { gMidiControl[2], gMidiControl[3] };

// Put the 2 banks together
midi::Control** gBanks[BANK_COUNT] = { gBank0, gBank1 };

// The bank selection is controlled by the first switch
midi::BankSelector gBankSelector(gInput[0], gOutput[0], gBanks, BANK_COUNT, MIDI_CTRL_COUNT, true);

void setup() {
	Serial.begin(38400);
	// Turn on PCB LED during boot sequence
	pinMode(6, OUTPUT);
	digitalWrite(6, HIGH);

	// Turn on each output
	for (int index = 0; index < SWITCH_COUNT; index++) {
		gOutput[index]->write(HIGH);
		delay(50);
	}

	// Turn off each output in reverse order
	for (int index = SWITCH_COUNT - 1; index >= 0; index--) {
		delay(50);
		gOutput[index]->write(LOW);
	}

	// Turn off PCB LED
	digitalWrite(6, LOW);
	Serial.println("Setup OK.");
}

void loop() {
	// Handle the PowerLed first, as it is shared with the BankControl.
	gPowerLed.handle();
	gBankSelector.handle();
	delay(50);
}
