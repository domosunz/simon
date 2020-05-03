#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "led.h"
#include "common.h"
#include "button.h"
#include "rng.h"

void main()
{
  ledInit(2, 3, 4, 5);
  buttonInit(14, 15, 16, 17);

  const unsigned MAXSIZE = 30;

  uint8_t currentGuess;
  uint8_t currentLight;

  uint8_t difficulty;
  uint8_t pattern[MAXSIZE];

  uint8_t lost;

  // Start with a time of about 2 seconds for each button press
  uint16_t timeUntilLoss = 31250;

  uint8_t i;

  while (1)
  {
    lost = 0;
    difficulty = 0;
    while (!lost)
    {
      //Increases the amount in the pattern for each time player is correct
      difficulty += 1;
      
      for (i = 0; i < difficulty; i++)
      {
        currentLight = rand();
        pattern[i] = currentLight;
        switch(currentLight)
        {
        case 0:
          flashGreen();
          break;
        case 1:
          flashRed();
          break;
        case 2:
          flashBlue();
          break;
        case 3:
          flashYellow();
          break;
        }
      }

      i = 0;
      while (i < difficulty && !lost)
      {
        currentGuess = getInput(timeUntilLoss);
        if (currentGuess != pattern[i])
        {
          lost = 1;
        }
        i++;
      }
      wait();
    
    }

    //lose state
    allOn();
    wait();

    currentGuess = 4;
    
    //Wait for any button push
    
    i = 0;
    while(currentGuess == 4)
    {
      currentGuess = getInput(timeUntilLoss);
      
      // if we have to stay in this loop for 30 iterations, than about a minute has passed
      // we turn off lights and put cpu to sleep, waiting for a reset to wake it
      if (i == 30)
      {
        allOff();
        
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_cpu();
      }
      i++;
    }
    
    allOff();
    wait();
  }
}
