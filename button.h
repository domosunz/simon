#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

// Initialize the buttons, the physical pin numbers are passed as parameters
void buttonInit(uint8_t green, uint8_t red, uint8_t blue, uint8_t yellow);
// This function waits for and returns the value of a button press
// 0:green, 1:red, 2:blue, 3:yellow, 4: User didn't press button in allotted time
uint8_t getInput(uint16_t timeUntilLoss);

#endif // BUTTON_H
