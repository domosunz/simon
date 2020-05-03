#include <avr/io.h>
#include "common.h"

// A random value from 0 to 3, inclusive
// Uses the internal thermometer to get said value
uint8_t rand()
{
  clrb(PRR, PRADC);

  setb(ADCSRA, ADEN);
  setb(ADCSRA, ADPS0);
  setb(ADCSRA, ADPS1);
  setb(ADCSRA, ADPS2);
  
  setb(ADMUX, REFS1);
  setb(ADMUX, REFS0);

  clrb(ADMUX, ADLAR);

  setb(ADMUX, MUX3);
  clrb(ADMUX, MUX2);
  clrb(ADMUX, MUX1);
  clrb(ADMUX, MUX0);

  setb(ADCSRA, ADSC);
  while(!(ADCSRA & (1 << ADIF)));

  setb(ADCSRA, ADIF);
  uint8_t low = ADCL;
  uint8_t tmp = ADCH;

  clrb(ADCSRA, ADEN);

  // return the last two bits
  return low & 3;
}
