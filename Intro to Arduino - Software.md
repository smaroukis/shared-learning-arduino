parent::[Arduino](Arduino.md)
previous::[Introduction to Arduino - Hardware](Introduction%20to%20Arduino%20-%20Hardware.md)
status:: #draft-outline 

- Arduino cannot run multiple programs at the same time, and programs can't quit

**Initialization - initialize variables**
- see [Arduino Variable Types](Arduino%20Variable%20Types.md) 
- initialize pin number variables as `const int` (e.g. `const int analogInPin = A0;`)
- for number variables that can get large, such as when using `millis()`, use `unsigned long` so it rolls over back to 0

**Setup - runs once**
- `Serial.begin(9600); //initialize serial data rate at 9600 bits per second`

**Loop - Where it All Happens**
- HIGH means the pin will be set to 5V, while LOW means the pin will be set to 0V 
- `analogRead(<pin>)`
- `Serial.println()`
- `delay(<ms>)`
- `map(value, fromLow, fromHigh, toLow, toHigh)`
[Arduino Variable Types](Arduino%20Variable%20Types.md)

Working with Specific Components
- [Arduino LEDs](Arduino%20LEDs.md) are always active `HIGH` 

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
	- for Arduino, [[word size]] is 16 bits.  For Arduino all variables can take up a word-size worth of space, or $2^{16}=65,536$ values (in practice `0` to `65535`)  ➡️  $65,536/2 = 32,768$
	- 

**Further**
- [Arduino - ADC](Arduino%20-%20ADC.md)
