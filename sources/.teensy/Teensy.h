#ifndef TEENSY_H_
#define TEENSY_H_

#define LOW 0
#define HIGH 1

#define INPUT 0
#define INPUT_PULLUP 0
#define OUTPUT 0

typedef int byte;

void pinMode(int, int);
int analogRead(int);
int digitalRead(int);
void digitalWrite(int, int);
void delay(int);

class UsbMidi {
public:
	void sendControlChange(int, int, int);
	void setHandleRealTimeSystem(void (*fptr)(byte realtimebyte));
};
UsbMidi usbMIDI;

class SerialOutput {
	void begin(int);
	void print(void*);
	void print(double);
	void println(void*);
	void println(double);
};
SerialOutput Serial;
#endif /* TEENSY_H_ */
