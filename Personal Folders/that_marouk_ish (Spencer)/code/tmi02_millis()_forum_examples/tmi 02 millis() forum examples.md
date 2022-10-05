Source: https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573

## Notes
- `delay()` stops all activity until the delay is finished (can't do multiple tasks at once)
- fix: use the `millis()` function 

### Part 1 
- assumptions
	- input pins defined as pullups in `pinMode()` -> that is they are defined with a pullup rsistor connecting them to 5V (normally OFF/"open"/0 state), thus closing the switch takes the pin low (ON/"closed"/1 state) -> add this to [Intro to Arduino - Software](../../Intro%20to%20Arduino%20-%20Software.md)
- calling `milis()`  returns an unsigned long of the current time in milliseconds (since the program began) (thus it can roll over back to 0 and not affect things) [source](https://www.arduino.cc/reference/en/language/functions/time/millis/)
	- `unsigned long start = millis()`
	- `const unsigned long period = <ms>`
- #q what is a byte variable type? (`const byte ledPin = 13;`)
- use in conjunction with a **constant period**, **start** and **end** `millis()` calls we
	- grab the start time in millis (in setup) -> [Common Setup Declarations](Common%20Setup%20Declarations.md)
	- get the current time at the beginning of the loop
	- check whether the period time has passed (`current - start >= period`)
		- if so, perform some action #1 (and don't forget to save the new start time)
		- ... code continues to action #2 <= ==the key here is that the loop executes so fast that we can't tell there is any delay between the action 1 and action 2==

### Part 2 -> see [02.02 - Changing LED Brightness 2 At a Time](02.02%20-%20Changing%20LED%20Brightness%202%20At%20a%20Time.ino)
- uses millis() with a 10ms delay to turn the brightness up by one setup from `analogWrite()`s 0 to 255 
- uses a `byte` type for the brightness value (and increment) between 0 and 255
- `byte brightness = 0, increment = 1;`
- `brightness += increment` << using a byte plus a byte, this will roll over at $2^8=256$ (including 0, so 255)
- when combing this with a second action, we just need separate variables for start times and end times (current time is shared)
### Part 3 - Button Pressing 
- counts how long it takes to press the button 5 times
- difference is we need to detect when the button **becomes** pressed rather than is pressed
- no debouncing

### Part 4 - Debouncing 
- uses new variables for the debounce start time, period, and a flag for checking if we are debouncing or not
- TODO #q what is the requirement of checking the current buton state (`if (currentbuttonState == LOW)`)
- stores the current button state
- reads the current button state
- if the button state has changed, 1) save the current time and 2) set the debouncing flag to true
- 