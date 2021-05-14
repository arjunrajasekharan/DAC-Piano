// Creates sound wave using 8-bit DAC and simulate C, D, E, F, G, A, B and C notes of the piano.
//Hardware config in doc
#include "tm4c123gh6pm.h"
#include "musicnotes.c"
#include "keys.c"
#include "dig_to_ang.c"


int main(void) {
    InitSound();        // initialize SysTick and DAC
    InitPiano();        // initialize Switches
    // Loop
    while (1) {
        PianoIn(); // read input from switches
       // if the index is out of range (no switch is pressed)
        if (freq_index == 8) {
            StopSound(); // turn off the sound
        }
        else {
            // adjust the frequency similarly to C, D, E, F, G, A, B and C(Higher Freq)
            PlaySound(FREQ_SYSTICK_TO_WAVE[freq_index]);
        }
    }
}
