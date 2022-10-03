[2022-10-03](2022-10-03)
From https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 on `millis()` vs `delay()`
- `delay()` stops all activity until the delay is finished (can't do multiple tasks at once)
- fix: use the `millis()` function 
- assumptions
	- input pins defined as pullups in `pinMode()` -> that is they are defined with a pullup rsistor connecting them to 5V (normally OFF/"open"/0 state), thus closing the switch takes the pin low (ON/"closed"/1 state) -> add this to [Intro to Arduino - Software](../../Intro%20to%20Arduino%20-%20Software.md)
- calling `milis()`  returns an unsigned long of the current time in milliseconds (since the program began) (thus it can roll over back to 0 and not affect things) [source](https://www.arduino.cc/reference/en/language/functions/time/millis/)
- #q what is a byte variable type? (`const byte ledPin = 13;`)
- use in conjunction with a **constant period**, **start** and **end** `millis()` calls we
	- grab the start time in millis (in setup) -> [Common Setup Declarations](Common%20Setup%20Declarations.md)
	- get the current time at the beginning of the loop
	- check whether the period time has passed (`current`)

``` // e.g.
unsigned long startMillis;  
unsigned long currentMillis;  
const unsigned long period = 1000; 
```


[2022-10-02](2022-10-02)
- install zip libraries directly (no need to unpackage)
- a serial terminal is important to see the interaction with the Arduino via a computer - this is the Serial Monitor
- "Selecting which port to open in the Serial Monitor is the same as selecting a port for uploading Arduino code. Go to Tools -> Serial Port, and select the correct port." (source: [elegooCompleteStarterMega2560](elegooCompleteStarterMega2560.md)) - should be the same COM port as in DeviceManager
- [Mega2560](Mega2560.md) led is digital pin 13, see `LED_BUILTIN` variable
- tools > set board
- tools > set port (forgot this one)
- changed it to 500ms
- https://ht-deko.com/arduino/usb2serial.html#06 for [Serial to USB](Serial%20to%20USB.md) things (see [Serial Communication](Serial%20Communication.md)