// from Massimo - Getting Started with Arduino

// Constants
const int LED = 13;
const int BUTTON = 7; 

// Inputs
int val = 0;

// Other
int old_val = 0; // stores previous value of "val" (input)
int state = 0; // 0 = LED off and 1 = LED on
int brightness = 128; // out of 255 (1 byte for analogWrite())
unsigned long t_start = 0; 


