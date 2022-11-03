parent::[[Arduino]]
previous::[[Introduction to Arduino - Hardware]]
next::[[Arduino Software Concepts]]

### **Fundamental Concepts**:
- Arduino cannot run multiple programs at the same time, and programs can't quit
- When uploaded to the board the `setup()` function runs once, and the `loop()` function loops continuously
- The Arduino pin type constrains us in some software functions  - see [[Arduino Pin Considerations]]

**Step 1: Import Headers and Initialization of Variables**
- Import headers as needed (note using the Arduino IDE we don't need `#include <Arduino.h>` but if not using the Arduino IDE we do) ➡️ for more see [[Common Code Structure for Arduino Projects]] and [[Preprocessing Directives]]
- initialize global variables before `setup()`
- see [[Arduino Variable Types]] 
	- numbers that won't change - use `const int` or `const long`
	- for numbers representing time use unsigned values to prevent unintentional consequences when exceeding the variable type’s maximum value
	- pin numbers - use `const int`  (more in [[Arduino Pin Considerations]])

**Setup - runs once**
- setting pin mode as input or output
	- `pinMode(13, OUTPUT)`
	- `pinMode(7, INPUT_PULLUP) // sets digital pin 7 as an input with a pullup resistor (so will normally read HIGH)
	- `Serial.begin(9600); //initialize serial data rate at 9600 bits per second`

**Loop - Where it All Happens**
- `analogRead(<pin>)` vs. `ditialRead(<pin>)`
- `Serial.println()`
- `delay(<ms>)`

### Test Your Knowledge Questions 
- #q/answered  Why is 255 important?
	- $log_2(256)=8$
	- $2^8=256$: "a string of 8 bits, each bit having 2 values, can give us a decimal value between 0 and 256"
- #q/answered  why is 1023 important? 
	- $log_2(1024)=10$
	- The Uno has a 10 bit [[Arduino - ADC]], so converts analog voltages between 0-5V to one of 1024 different integer values (starting with 0 up to 1023). 
- #q/answered  why is 32,768 important?
	- for Arduino, and specifically the ATMega328, the [[word size]] is 16 bits.  This word-size worth of space, can take $2^{16}=65,536$ different values (in practice `0` to `65535`)   
	- the word size is basically the size of the data that can be processed during one clock cycle

**Further**
- See other topics in [[Arduino Software Concepts]]
- [[Arduino - ADC]]
- [[Multitasking and non blocking delays]] - instead of using `delay()` how to use `millis()`, Timers and beyond