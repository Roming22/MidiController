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
 * Create hardware controllers
 */
hardware::GenericController* gController[5] = {
		// This switch will be used to control the banks
		new hardware::LatchedSwitch(4, true, 5),

		// Switches for Bank0
		new hardware::LatchedSwitch(7, true, 8),
		new hardware::MomentarySwitch(9, true, 10),

		// Switches for Bank1
		new hardware::MomentarySwitch(7, true, 8),
		new hardware::MomentarySwitch(9,true, 10) };

// The output for the PowerLed will be shared with the bank selector
board::PowerLed gPowerLed(5, 13, 26);


/*
 * Create the MIDI banks
 */
midi::GenericControl* gBank0[MIDI_CTRL_COUNT] = {
		new midi::SimpleControl(MIDI_CHANNEL, 20, gController[1]),
		new midi::SimpleControl(MIDI_CHANNEL, 21, gController[2]) };

midi::GenericControl* gBank1[1] = {
		new midi::UpDownControl(MIDI_CHANNEL, 110, gController[3], gController[4], 4) };

// Put the 2 banks together
midi::Bank* gBanks[BANK_COUNT] = {
		new midi::Bank(gBank0, MIDI_CTRL_COUNT),
		new midi::Bank(gBank1, 1) };

// The bank selection is controlled by the first switch
midi::BankSelector gBankSelector((hardware::OnOffController*) gController[0],
		gBanks, BANK_COUNT, true);

void setup() {
	Serial.begin(38400);
	// Turn on PCB LED during boot sequence
	pinMode(6, OUTPUT);
	digitalWrite(6, HIGH);

	gBankSelector.reset();

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
