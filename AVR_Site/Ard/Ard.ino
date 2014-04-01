#include <Arduino.h>

void blink();

volatile int state = LOW;
volatile bool x = false;

void setup()
{
	Serial.begin(9600);

	// initialize the digital pin as an output.
    // Pin 13 has an LED connected on most Arduino boards:
    attachInterrupt(0, blink, CHANGE);
    pinMode(5, OUTPUT);
    pinMode(2, INPUT);
}

void loop()
{
  digitalWrite(5, state);
}

void blink()
{
    if(x) {
        state = !state;
        Serial.println("Ahoj");
    }
    x=!x;
}
