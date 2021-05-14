
#include "headers.h"
#include "tm4c123gh6pm.h"

// a smooth digital value for analog sine wave
const unsigned char SINE_WAVE[16] = {
    8, 10, 13, 14, 15, 14, 13, 10,
    8, 5, 2, 1, 0, 1, 2, 5
};

// index variable of SINE_WAVE varies from 0-15
unsigned char index = 0;

// convert from the frequency of the SysTick

const unsigned long FREQ_SYSTICK_TO_WAVE[8] = {
    9550, 8508, 7570, 6366, 5532, 4423, 3588, 2499
};


// Initializes Systick periodic interrupts and DAC.
void InitSound(void) {
    // DAC Initialization
    InitDac();                     // call the InitDac() function in DAC.c
    index = 0;                     // init value of index is 0
    // SysTick Initialization
    NVIC_ST_CTRL_R = 0;            // disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // maximize the RELOAD value
    NVIC_ST_CURRENT_R = 0;         // any write to CURRENT clears it
    NVIC_ST_CTRL_R = 0x00000005;   // enable SysTick with core clock
    // priority 1
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R = 0x0007;       // enable, source clock, and interrupts
}
// SysTick interrupt service routine
void SysTick_Handler(void) {
    if (freq_index != 8) {
        // only executes if there is non-zero input
        index = (index + 1) & 0x0F; // cycles from 0-15
        OutDac(SINE_WAVE[index]);   // output 1 data each interrupt
    }
}


// Changes SysTick periodic interrupts to start sound output
void PlaySound(unsigned long period) {
    // reset the RELOAD value for different frequencies
    NVIC_ST_RELOAD_R = (period - 1) & 0x00FFFFFF;
}


// Stops outputing to DAC
void StopSound(void) {
    GPIO_PORTB_DATA_R &= ~0x0F; // clear PB7-PB0
}



