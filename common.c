#include <avr/io.h>
#include <avr/interrupt.h>
#include "common.h"

void startwait()
{
  // Set a TOP value
  //setb(TIMSK1, OCIE1A);
  TCNT1 = 0;

  // Prescalar of 1024
  setb(TCCR1B, CS10);
  clrb(TCCR1B, CS11);
  setb(TCCR1B, CS12);

  // Wait for the flag to be set
  while(!(TIFR1 & (1 << OCF1A)));

  // Turn off the prescalar
  clrb(TCCR1B, CS10);
  clrb(TCCR1B, CS12);

  TIFR1 = 1 << OCF1A;
}

// This stops for about a second
void wait()
{
  OCR1A = 15625;
  startwait();
}

// This stops for about 0.2 seconds
void shortwait()
{
  OCR1A = 3125;
  startwait();
}

// This waits for a little over 50ms, the time of a button bounce
void bouncewait()
{
  OCR1A = 800;
  startwait();
}

void startTimer()
{
  TCNT1 = 0;

  // Prescalar of 1024
  setb(TCCR1B, CS10);
  clrb(TCCR1B, CS11);
  setb(TCCR1B, CS12);
}