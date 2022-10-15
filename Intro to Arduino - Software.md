parent::[Arduino](Arduino.md)
previous::[Introduction to Arduino - Hardware](Introduction%20to%20Arduino%20-%20Hardware.md)
next::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
status:: #draft

#refactor `children` - put the children in their own hierarchy (e.g under [Arduino Software Concepts](Arduino%20Software%20Concepts.md))

**Fundamental Concepts**:
- Arduino cannot run multiple programs at the same time, and programs can't quit
- Predefined `setup()` function runs once, `loop()` function loops continuously
- ? interrups? #q 
- The Arduino pin type constrains us in some things (analog or digital, PWM capable or not), but we can define some pins as an input or an output

**Initialization - initialize variables**
- initialize global variables before `setup()`
- see [Arduino Variable Types](Arduino%20Variable%20Types.md) 
	- numbers that won't change - use `const int` or `const long`
	- pin numbers - use `const int`  (more in [Arduino Pin Numbers](Arduino%20Pin%20Numbers.md))
		- some analog pins can be defined in two ways: e.g. `A0` or `13` 
	- 

**Setup - runs once**
- setting pin mode as input or output
	- `pinMode(13, OUTPUT)`
	- `pinMode(7, INPUT_PULLUP) // sets digital pin 7 as an input with a pullup resistor (so will normally read HIGH)
	- `Serial.begin(9600); //initialize serial data rate at 9600 bits per second`

**Loop - Where it All Happens**
- `analogRead(<pin>)` vs. `ditialRead(<pin>)`
- `Serial.println()`
- `delay(<ms>)`

Working with Specific Components
- [Arduino LEDs](Arduino%20LEDs.md) are always active `HIGH` 
- #tdf 
- LED is just labeled "L" but is pin 13 for the [Mega2560](Mega2560.md)
	- https://forum.arduino.cc/t/digitalwrite-led-builtin-low-turns-on-the-led/965532/7
	- "The issue is that while there is a portable way to determine the Arduino digital pin number for the LED, LED_BUILTIN, there is no portable way to determine the i/o pin output active level needed to turn the built in LED on and off." ➡️  basically we don't know for the internal LEDs whether it is a pull down or pull up (is ON +5V or 0V? ) 
		- but for Arduino (c) boards LEDs are ==active high==
- look at the provided sketches for examples
- 
- #q why is 255 important?
	- $log_2(256)=8$
	- $2^8=256$: "a string of 8 bits, each bit having 2 values, can give us a decimal value between 0 and 256"
- #q why is 1023 important? 
	- $log_2(1024)=10$
	- The Uno has a 10 bit [Arduino - ADC](Arduino%20-%20ADC.md), so converts analog voltages between 0-5V to one of 1024 different integer values (starting with 0 up to 1023). 
- #q why is 32,768 important?
	- for Arduino, and specifically the ATMega328, the [word size](word%20size.md) is 16 bits.  This word-size worth of space, can take $2^{16}=65,536$ different values (in practice `0` to `65535`)   #tdf 
	- the word size is basically the size of the data that can be processed during one clock cycle
	

**Further**
- [Arduino - ADC](Arduino%20-%20ADC.md)
- [Multitasking and non blocking delays](Multitasking%20and%20non%20blocking%20delays.md) - instead of using `delay()` how to use `millis()`, Timers and beyond
