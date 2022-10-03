Summarized in [tmi Log](tmi%20Log.md)

[2022-10-03](2022-10-03)
From https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 on `millis()` vs `delay()`
- `delay()` stops all activity until the delay is finished (can't do multiple tasks at once)
- fix: use the `millis()` function 
- Part 1 
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
- Part 2 -> see code [Code - millis() Beginner Guide - Changing LED Brightness 2 At a Time](code/Code%20-%20millis()%20Beginner%20Guide%20-%20Changing%20LED%20Brightness%202%20At%20a%20Time.md)
	- uses millis() with a 10ms delay to turn the brightness up by one setup from `analogWrite()`s 0 to 255 
	- uses a `byte` type for the brightness value (and increment) between 0 and 255
	- `byte brightness = 0, increment = 1;`
	- `brightness += increment` << using a byte plus a byte, this will roll over at $2^8=256$ (including 0, so 255)
	- when combing this with a second action, we just need separate variables for start times and end times (current time is shared)
- Part 3 - Button Pressing see [Code - millis() Beginner Guide - Part 3 - Button Pressing](Code%20-%20millis()%20Beginner%20Guide%20-%20Part%203%20-%20Button%20Pressing.md)
	- counts how long it takes to press the button 5 times
	- difference is we need to detect when the button **becomes** pressed rather than is pressed
	- no debouncing
- Part 4 - Debouncing see [Code - millis() Beginner Guide - Part 4 - Debouncing](Code%20-%20millis()%20Beginner%20Guide%20-%20Part%204%20-%20Debouncing.md)
	- uses new variables for the debounce start time, period, and a flag for checking if we are debouncing or not
	- TODO #q what is the requirement of checking the current buton state (`if (currentbuttonState == LOW)`)
	- stores the current button state
	- reads the current button state
	- if the button state has changed, 1) save the current time and 2) set the debouncing flag to true
	- 


[2022-10-02](2022-10-02)
- install zip libraries directly (no need to unpackage)
- a serial terminal is important to see the interaction with the Arduino via a computer - this is the Serial Monitor
- "Selecting which port to open in the Serial Monitor is the same as selecting a port for uploading Arduino code. Go to Tools -> Serial Port, and select the correct port." (source: [elegooCompleteStarterMega2560](elegooCompleteStarterMega2560.md)) - should be the same COM port as in DeviceManager
- [Mega2560](Mega2560.md) led is digital pin 13, see `LED_BUILTIN` variable
- tools > set board
- tools > set port (forgot this one)
- changed it to 500ms
- https://ht-deko.com/arduino/usb2serial.html#06 for [Serial to USB](Serial%20to%20USB.md) things (see [Serial Communication](Serial%20Communication.md)