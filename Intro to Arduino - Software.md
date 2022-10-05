parent::[Arduino](Arduino.md)
previous::[Introduction to Arduino - Hardware](Introduction%20to%20Arduino%20-%20Hardware.md)
status:: #draft-outline 

- Initialization - initialize variables
	- initialize pin number variables as `const int` (e.g. `const int analogInPin = A0;`)
	- integer values that can change, just as `int`
- Setup - runs once
	- `Serial.begin(9600); //initialize serial data rate at 9600 bits per second`
- Loop - loops
	- Arduino cannot run multiple programs at the same time, and programs can't quit
	- HIGH means the pin will be set to 5V, while LOW means the pin will be set to 0V 
	- `analogRead(<pin>)`
	- `Serial.println()`
	- `delay(<ms>)`
	- `map(value, fromLow, fromHigh, toLow, toHigh)`
		- `analogRead()` returns a value between 0 and 1023 but `analogWrite()` can only write between 0 and 255. For the Uno, it results in a [Arduino - PWM](Arduino%20-%20PWM.md) output waveform at the desired pin.	(note `map()` uses integer math - for decimal precision you will need to write your own)
```arduino
void loop() {
  int val = analogRead(0);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(9, val);
}
```

Variable Types

**Numbers**
- Integers: `int` and `long`
	- by default variables are _signed_. 
		- for _n-bits_ of storage there is $2^n$ values; this includes 0, and we take away one possible value from the positive side, so we are left with a $2^{n-1}$ signed values and a range of $\text{int} \in [-2^{n-1}, 2^{n-1} - 1]$ since we take away one on the positive side. 
		- e.g. for 16 bits (the [word size](word%20size) of Arduino) it is $2^{16}=65,536$ values. For both positive and negative we have $32,768$ but since we want to include 0 as a positive number the range is $-32,768$ to $32,767$.
	- `int`: from -16,384 to 16,383
		- `unsigned int`: 0 to 32,768
	- `long`: 
		- for large numbers; stores 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647 (default unsigned)
		- `unsigned long`  from 0 to 4,294,967,295
		- note: for doing math with integers **at least one of them must be of type `long`**

[Integer Constants](https://www.arduino.cc/reference/en/language/variables/constants/integerconstants/) - `const int`
- are usually type `int` (unsigned) but can be other variable types using specific formatting e.g. `const int 10000L` (constant long integer) or `const int 33u` (constant unsigned integer) or `const int 32767UL` (constant unsigned long integer)
- [[const int vs define macro]]

Table of various types:
![](Personal%20Folders/that_marouk_ish%20(Spencer)/attachments/Pasted%20image%2020221005161457.png)

- _U/L formatters (appends)_
	- `u|U`: to force the constant into an **unsigned** data format. Example: `33u`
	- `l|L`: to force the constant into a **long** data format. Example: `100000L`
	- `ul|UL`: to force the constant into an **unsigned** **long** constant. Example: `32767ul`

> If doing math with integers a**t least one of the values must be of type long**, either an integer constant followed by an L or a variable of type long, forcing it to be a long. See the [Integer Constants](https://www.arduino.cc/reference/en/language/variables/constants/integerconstants) page for details.

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

[1]: for hexadecimal, `A-F` is case _independent_