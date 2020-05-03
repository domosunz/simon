#ifndef SOUND_H
#define SOUND_H

/* These functions are used by the LED functions to use the speaker for *\
\*  the respective light. They need not be used by the user directly    */

// Initialize the speaker
void soundInit();

// Start playing the tone
void startFTone();
void startGTone();
void startATone();
void startBTone();

// Stop the speaker
void endTone();

#endif // SOUND_H
