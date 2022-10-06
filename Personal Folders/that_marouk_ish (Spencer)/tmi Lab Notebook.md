Summarized in [tmi Log](tmi%20Log.md)

[2022-10-06](2022-10-06)
Plan
- keep going through the Banzi Book & Collecting Examples

[[UART]] - see wikipedia #refactor
- the UART port is also called the Serial Port [[Serial Communication]]
- hardware for serial communication that handles the tranmission/reception of serial communication (external device required to handle the singalling level of the transmitting/receiving device)
	- electric signalling level are handled by a external driver circuit, e.g. RS-232 (12V) and RS-485 (5V)
- an IC or part of an IC that allows data format and transmission speeds to be configurable
- asynchronous - so uses a [shift register](shift%20register.md) to convert between serial and parallel forms
- sends and receives bits one by one from LSB to MSB with start/stop bits
- precise timing is handled by the communication channel
- communication can be simplex, full duplex, half duplex
- settings: baud rate, parity bit, data bits size, stop bits size, flow control
- has internal clock faster than the bit rate
- [[bit-banging]] is omitting the UART and using the CPU to sample the state of an input port or directly manipulate an output port for transmission; but it is CPU intensive because of the timing

[2022-10-05](2022-10-05)
- [State Machines](State%20Machines.md) #tdf
- [banziGettingStartedArduino](banziGettingStartedArduino.md) Project - Fade in LED if pushbutton is pressed 
	- [tmi05 Pushbutton LED Fade](code/tmi05%20Pushbutton%20LED%20Fade.md)
- wiring vs processing vs Arduino language https://forum.arduino.cc/t/how-is-arduino-related-to-wiring/69064/5?u=that_marouk_ish
- more on [Serial Communication](../../Serial%20Communication.md) and [Serial to USB](Serial%20to%20USB) ⬇️ 
	- "Current Arduino boards are programmed via [Universal Serial Bus](https://en.wikipedia.org/wiki/Universal_Serial_Bus "Universal Serial Bus") (USB), implemented using USB-to-serial adapter chips such as the [FTDI](https://en.wikipedia.org/wiki/FTDI "FTDI") FT232. Some boards, such as later-model Uno boards, substitute the [FTDI](https://en.wikipedia.org/wiki/FTDI "FTDI") chip with a separate AVR chip containing USB-to-serial firmware, which is reprogrammable via its own [ICSP](https://en.wikipedia.org/wiki/In-system_programming "In-system programming") header."  [[source](https://en.wikipedia.org/wiki/Arduino#Hardware)]
- Main Learnings
	- longs vs ints -> see [Intro to Arduino - Software](../../Intro%20to%20Arduino%20-%20Software.md)
	- use `unsigned long` for `millis()` timekeeping (can go up to -4.2Ms = 50 days)
	- some tricks for fading in and out see below and in [tmi05 Pushbutton LED Fade](code/tmi05%20Pushbutton%20LED%20Fade.md)
		- ![](attachments/Pasted%20image%2020221005215410.png)


[2022-10-04](2022-10-04) ✅ 
- [RGB LEDs](../../RGB%20LEDs.md)  see [code](./Personal Folders/that_marouk_ish (Spencer)/code/tmi_04_RGB_LED/tmi_04_RGB_LED.ino)
	- further: use pots to change color; simplify code w functions; use optimal resistors dependent on colors for equal brightness
	- R, G, and B channels are mixed - from this we can develop many different colros
	- https://www.circuitbread.com/tutorials/how-rgb-leds-work-and-how-to-control-color
		- we are going to use PWM to adjust the intensity of the red, green, and blue LEDs individually and the trick here is that our eyes will see the combination of the colors, instead of the individual colors because the LEDs are very close to each other inside. 
		-  each color has a different forward voltage (red ~2V, blue/green ~3.3V) - datasheet will have this
	- can't use one on the cathode "In fact it would not work at all because the LED with the lowest forward voltage (the red one) would stop enough forward voltage being across the higher forward voltage LEDs."
	- https://www.circuitbread.com/tutorials/why-cant-i-share-a-resistor-on-the-common-anode-or-cathode-of-my-rgb-led
		- the luminous intensity of an LED depends on the forward current. However, the forward current of an LED also depends on the forward voltage or the voltage drop across the LED. So if the voltage drop across the LED is not enough to have the required forward current, you won’t get the desired luminous intensity of the LED.
		- for ideal led's only the red one would light up - the forward drop of the blue and green are not met
		- also, with one resistor at the cathode/anode, the current across and individual led will be lower (?) when all are on, and higher (?) when they are off - thus the brightness of the combination will also vary based on the color
- learned for Arduino IDE the `.ino` file needs to  be inside a folder of the same name
- failed installing Arduino extension in VS Code :/
- https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics#sketchbook
	- "When you upload a sketch, you're using the Arduino **bootloader**, a small program that has been loaded on to the microcontroller on your board. It allows you to upload code without using any additional hardware." 
	- "Please note that the Serial Monitor does not process control characters; if your sketch needs a complete management of the serial communication with control characters, you can use an external terminal program and connect it to the COM port assigned to your Arduino board."

[2022-10-03](2022-10-03)
From https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 on `millis()` vs `delay()` -> see [tmi 02 millis() forum examples](code/tmi%2002%20millis()%20forum%20examples/tmi%2002%20millis()%20forum%20examples.md)


[2022-10-02](2022-10-02)
- install zip libraries directly (no need to unpackage)
- a serial terminal is important to see the interaction with the Arduino via a computer - this is the Serial Monitor
- "Selecting which port to open in the Serial Monitor is the same as selecting a port for uploading Arduino code. Go to Tools -> Serial Port, and select the correct port." (source: [elegooCompleteStarterMega2560](elegooCompleteStarterMega2560.md)) - should be the same COM port as in DeviceManager
- [Mega2560](Mega2560.md) led is digital pin 13, see `LED_BUILTIN` variable
- tools > set board
- tools > set port (forgot this one)
- changed it to 500ms
- https://ht-deko.com/arduino/usb2serial.html#06 for [Serial to USB](Serial%20to%20USB.md) things (see [Serial Communication](Serial%20Communication.md)