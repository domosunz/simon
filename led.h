#ifndef LED_H
#define LED_H

#include <avr/io.h>

void ledInit(uint8_t green, uint8_t red, uint8_t blue, uint8_t yellow);

// Turn on the light and start the associated sound
void greenOn();
void redOn();
void blueOn();
void yellowOn();

// Tone off the light and turn off the speaker
void greenOff();
void redOff();
void blueOff();
void yellowOff();

// Turn the light on for a second, the off for about 0.2 seconds before returning
void flashGreen();
void flashRed();
void flashBlue();
void flashYellow();

//Turns all lights and sounds on/off
void allOn();
void allOff();

#endif // LED_H
