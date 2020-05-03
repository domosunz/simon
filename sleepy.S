#define __SFR_OFFSET 0
#include <avr/io.h>
#include <avr/interrupt.h>

.text
.global PCINT0_vect
.global idling

PCINT0_vect:
  reti

idling:
  sbi SMCR, SM1 ; set to power down mode
  
  sbi PCICR, PCIE0 ; enable Bank 0 interrupts
  
  ;ldi r18, 0x0f
  ;in PCMSK0, r18 ; enable PB0, PB1, PB2, PB3, PB4

  sbi PCMSK0, PCINT0 ; enable PB0 interrupts

  cli
  sei
  SLEEP

  ret
