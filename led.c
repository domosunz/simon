/* Name: Ulysses Butler
 * Project 3
 * =========
 * This file defines the facilities to interact with the lcd panel.
 */

#include <avr/io.h>
#include "led.h"
#include "sound.h"
#include "common.h"

#define setLow(PIN_STRUCT) (*((PIN_STRUCT).port)&=~((PIN_STRUCT).val))
#define setHigh(PIN_STRUCT) (*((PIN_STRUCT).port)|=(PIN_STRUCT).val)

#define assert(E) if(!(E)) return

// This variable stores the information about each pin as indicated by the user
pin_t GREEN_OUT;
pin_t BLUE_OUT;
pin_t RED_OUT;
pin_t YELLOW_OUT;

// This function takes in a pin number (e.g., 12 for PD6), sets the
// appropriate DDR (e.g., DDRD |= 1 << 6), and updates the pin_t
// value for future use.
void setPortInfo(uint8_t pinNumber, pin_t* pinInfo)
{
  switch(pinNumber)
  {
    case 1:   // PC6
      pinInfo->port = &PORTC;
      pinInfo->val = 1 << 6;
      DDRC |= pinInfo->val;
      break;
    case 2:   // PD0
    case 3:   // PD1
    case 4:   // PD2
    case 5:   // PD3
    case 6:   // PD4
      pinInfo->port = &PORTD;
      pinInfo->val = 1 << (pinNumber - 2);
      DDRD |= pinInfo->val;
      break;
    case 11:  // PD5
    case 12:  // PD6
    case 13:  // PD7
      pinInfo->port = &PORTD;
      pinInfo->val = 1 << (pinNumber - 6);
      DDRD |= pinInfo->val;
      break;
    case 14:  // PB0
    case 15:  // PB1
    case 16:  // PB2
    case 17:  // PB3
    case 18:  // PB4
    case 19:  // PB5
      pinInfo->port = &PORTB;
      pinInfo->val = 1 << (pinNumber - 14);
      DDRB |= pinInfo->val;
      break;
    case 23:  // PC0
    case 24:  // PC1
    case 25:  // PC2
    case 26:  // PC3
    case 27:  // PC4
    case 28:  // PC5
      pinInfo->port = &PORTC;
      pinInfo->val = 1 << (pinNumber - 23);
      DDRC |= pinInfo->val;
      break;
  }
}

void ledInit(uint8_t green, uint8_t red, uint8_t blue, uint8_t yellow)
{
  // This is the step where we initialize the DDR and save the
  // information about each pin for later use
  setPortInfo(green, &GREEN_OUT);
  setPortInfo(red, &RED_OUT);
  setPortInfo(blue, &BLUE_OUT);
  setPortInfo(yellow, &YELLOW_OUT);

  soundInit();
}

void greenOn() { setHigh(GREEN_OUT); startFTone(); }
void redOn() { setHigh(RED_OUT); startGTone(); }
void blueOn() { setHigh(BLUE_OUT); startATone(); }
void yellowOn() { setHigh(YELLOW_OUT); startBTone(); }

void greenOff() { setLow(GREEN_OUT); endTone(); }
void redOff() { setLow(RED_OUT); endTone(); }
void blueOff() { setLow(BLUE_OUT); endTone(); }
void yellowOff() { setLow(YELLOW_OUT); endTone(); }

void flashGreen()
{
  greenOn();
  wait();
  greenOff();
  shortwait();
}

void flashRed()
{
  redOn();
  wait();
  redOff();
  shortwait();
}

void flashBlue()
{
  blueOn();
  wait();
  blueOff();
  shortwait();
}

void flashYellow()
{
  yellowOn();
  wait();
  yellowOff();
  shortwait();
}

void allOn()
{
  greenOn();
  redOn();
  blueOn();
  yellowOn();
}

void allOff()
{
  greenOff();
  redOff();
  blueOff();
  yellowOff();
}
