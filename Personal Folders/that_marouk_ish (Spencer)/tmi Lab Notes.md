Summarized in [tmi Log](tmi%20Log.md)

[2022-10-05](2022-10-05)
[State Machines](State%20Machines.md) #tdf

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