#include <avr/io.h>
#include "common.h"

#define setToneTimer() { TCCR0A = (1<<WGM01) | (1<<WGM00) | (1<<COM0B1); TCCR0B = (1<<WGM02) | (1<<CS02); }

void soundInit()
{
  setb(DDRD, PD5);
}

// Play an F, 349Hz, TOP = ~179 
void startFTone()
{
  OCR0A = 178;
  OCR0B = 89;
  setToneTimer();
}

// Play a G, 392Hz, TOP = ~159
void startGTone()
{
  OCR0A = 158;
  OCR0B = 79;
  setToneTimer();
}

// Play an A, 440Hz, TOP = ~143
void startATone()
{
  OCR0A = 142;
  OCR0B = 71;
  setToneTimer();
}

// Play a B, 493.9Hz, TOP = ~127
void startBTone()
{
  OCR0A = 126;
  OCR0B = 63;
  setToneTimer();
}

void endTone()
{
  TCCR0A = 0;
  TCCR0B = 0;
}
