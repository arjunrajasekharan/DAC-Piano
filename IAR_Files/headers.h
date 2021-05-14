
// Initializes 8-bit DAC.
void InitDac(void);


// Writes output to DAC.
void OutDac(unsigned long data);

extern unsigned short freq_index;

// Initializes piano key inputs.
void InitPiano(void);


//Reads the input from PE3-PE0 and PF3-PF0.
void PianoIn(void);

// convert from the frequency of the SysTick
extern const unsigned long Frequency_Period[8];


// Initializes Systick periodic interrupts and DAC.
void InitSound(void);

// Changes SysTick periodic interrupts to start sound output.
void PlaySound(unsigned long period);

// Stops outputing to DAC.
void StopSound(void);