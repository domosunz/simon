#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "common.h"

#define getVal(PIN_STRUCT) ((*((PIN_STRUCT).port))&((PIN_STRUCT).val))

pin_t BUTTON1;
pin_t BUTTON2;
pin_t BUTTON3;
pin_t BUTTON4;

void setPinInfo(uint8_t pinNumber, pin_t* pinInfo)
{
  switch(pinNumber)
  {
    case 1:   // PC6
      pinInfo->port = &PINC;
      pinInfo->val = 1 << 6;
      DDRC &= ~(pinInfo->val);
      PORTC |= (pinInfo->val);
      break;
    case 2:   // PD0
    case 3:   // PD1
    case 4:   // PD2
    case 5:   // PD3
    case 6:   // PD4
      pinInfo->port = &PIND;
      pinInfo->val = 1 << (pinNumber - 2);
      DDRD &= ~(pinInfo->val);
      PORTD |= (pinInfo->val);
      break;
    case 11:  // PD5
    case 12:  // PD6
    case 13:  // PD7
      pinInfo->port = &PIND;
      pinInfo->val = 1 << (pinNumber - 6);
      DDRD &= ~(pinInfo->val);
      PORTD |= (pinInfo->val);
      break;
    case 14:  // PB0
    case 15:  // PB1
    case 16:  // PB2
    case 17:  // PB3
    case 18:  // PB4
    case 19:  // PB5
      pinInfo->port = &PINB;
      pinInfo->val = 1 << (pinNumber - 14);
      DDRB &= ~(pinInfo->val);
      PORTB |= (pinInfo->val);
      break;
    case 23:  // PC0
    case 24:  // PC1
    case 25:  // PC2
    case 26:  // PC3
    case 27:  // PC4
    case 28:  // PC5
      pinInfo->port = &PINC;
      pinInfo->val = 1 << (pinNumber - 23);
      DDRC &= ~(pinInfo->val);
      PORTC |= (pinInfo->val);
      break;
  }
}

void buttonInit(uint8_t green, uint8_t red, uint8_t blue, uint8_t yellow)
{
  setPinInfo(green, &BUTTON1); 
  setPinInfo(red, &BUTTON2); 
  setPinInfo(blue, &BUTTON3); 
  setPinInfo(yellow, &BUTTON4); 
}

uint8_t getInput(uint16_t timeUntilLoss)
{
  uint8_t flag = 0;
  startTimer();
  while(!flag && TCNT1 < timeUntilLoss)
  {
    if(!getVal(BUTTON1))
    {
      greenOn();
      flag = 1;
    }
    if(!getVal(BUTTON2))
    {
      redOn();
      flag = 2;
    }
    if(!getVal(BUTTON3))
    {
      blueOn();
      flag = 3;
    }
    if(!getVal(BUTTON4))
    {
      yellowOn();
      flag = 4;
    }
  }

  if (flag != 0)
  {
    while(!getVal(BUTTON1)||!getVal(BUTTON2)||!getVal(BUTTON3)||!getVal(BUTTON4))
    {
      while(!getVal(BUTTON1)||!getVal(BUTTON2)||!getVal(BUTTON3)||!getVal(BUTTON4));
      bouncewait();
    }
  }


  if(flag == 0)
    flag = 5;
     
  if(flag == 1)
    greenOff();
  if(flag == 2)
    redOff();
  if(flag == 3)
    blueOff();
  if(flag == 4)
    yellowOff();

  return flag - 1;
}
