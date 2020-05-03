#ifndef COMMON_H
#define COMMON_H

#define setb(REG, SHIFT)  { REG |= 1<<(SHIFT); }
#define clrb(REG, SHIFT)  { REG &= ~(1<<(SHIFT)); }

typedef struct pin_t
{
  volatile uint8_t* port;
  uint8_t val;
} pin_t;

/* These two functions are used by the led functions */
// Wait for about 0.2 seconds, used between flashed
void shortwait();
// Wait for about 1 second, used to time how long a light should flash
void wait();

/* This function is used by the buttons */
// Waits for a little over 50ms, used to time the length of a button bounce
void bouncewait();

//Starts a timer so that TCNT1 can be used in other areas
void startTimer();

#endif // COMMON_H
