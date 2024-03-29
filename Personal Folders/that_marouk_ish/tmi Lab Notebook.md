Summarized in [tmi Log](tmi%20Log.md)

## [2022-10-27](2022-10-27)
- Some issues with the current code
	- for a very small debounce delay the toggle seems not to work (indeterminate state - sometimes turns off, sometimes does not)
	- reset the timer on the release so it doesn't skip the debounce

```cpp
// in Button::loop() switch(_state)
case SHORT_PRESS: // 1
	if (!newReading) {
		_state = UNPRESSED; // latch state to unpressed
		_tPrevious_ms = millis(); // <-- HERE resetting timer helps with debouncing on release 
	} else if (millis() - _tPrevious_ms > _tLongPress_ms) {
		_state = LONG_PRESS;
	} 
	break;
```

## [2022-10-26](2022-10-26)
- made the short / long button press easier to read, using a `_wasChanged` variable of +1  or -1, then forcing the controller to read the current state of the button to determine if it was long or short
```cpp
	// in Button::loopStateMachine()
	if (prevState != _state) {
		if (_state > prevState) _wasChanged = 1;
		else if (_state < prevState) _wasChanged = -1;
	}
	else _wasChanged = 0;
```

then the controller code is 
```cpp
    button.loopStateMachine();

    if (button._wasChanged > 0) {
        if (button._state == 1) {
            // short press
            led.togglePower();
        }
        if (button._state == 2) {
			//long press
        }
    }

    if (button._wasChanged < 0) Serial.println("Button unpressed");
```

## [2022-10-25](2022-10-25)
- thought I had the  [button working](https://github.com/smaroukis/shared-learning-arduino/commit/ea4728b10641cae2ba942d364e46e915bb854f65), but there is still the issue of "callback acknowledgement" (?) or  state acknowledgement - that is, when we check that if `button.state` is pressed to take an action, say `led.toggle()`, that toggle action will be repeated over and over until we end up in a random led state of when we release the button and `button.state` is false
- https://mypractic.com/lesson-7-classes-in-c-language-for-arduino-button-as-an-object/  -> [Example - MyPractic OOP Button as an Object](../../Example%20-%20MyPractic%20OOP%20Button%20as%20an%20Object.md) might be helpful as it introduces an **acknowledgement counter** and uses **inheritance** 
	- :➡️ actually it was easier than this, I just needed to do _edge_ detection instead of _state_ detection (see `b7d43fc`)
- next up is trying to add in the ability for a long press to change the brightness
	- can we do this without editing too much of the `Led` class? 
	- actually it might be easy since we can track the button `state` variable to check if it is in a `LongPress (==2)` state -- just do `while button._state == 2 { led.increaseBrightness()}`  `

## [2022-10-24](2022-10-24)
- added in a `Button::Reset()` function which helps us not loop through the led toggle state
	- but if the debounce delay is short, it will still toggle it
	- need to handle long presses
	- (later deleted this function)

## [2022-10-21](2022-10-21)
- every action must have timing
- still struggling with the timing in the OOP - my toggle LED is being hit too many times
	- I only need edge detection on the button, when I have just general state detection

### [2022-10-20](2022-10-20)
- tried to refactor the code towards OOP, and although I understand the concept, it is actually hard to implement since we need to have timers for everything
- for example. even just accessing a state (the button state) - with its helper function, that call itself is not debounced, 
- how [Example - Professional Grade OOP - Inheritance and Composition](../../Example%20-%20Professional%20Grade%20OOP%20-%20Inheritance%20and%20Composition.md) handled it it seems is by throwing a "flag" on a button click
	- HeadlampControlButton is a composition of the Headlamp and the Button
	- it inherits from the Button class, in the `shortClick()` function it calls the `lamp.brightnessClick()` function
	- the button loop is just constantly reading the button state, if it has a click (debounced), it calls its internal `shortClick()` function (extended by the HeadLampControlButton Class)
	- the `brightnessClick()` function of the `Headlamp` (inherited) adds a click to the click queu and increments the brigtness
	- it is the main `ClickQueue` class that has the `enum` state and a `loop()` including the `switch` case and checks for `pendingClicks` from `addAClick()` -- if 

### [2022-10-17](2022-10-17)
[tmi15 Multitasking-2](tmi15%20Multitasking-2.md)
	- a lot of [LCDs](../../LCDs.md) research - a more complex peripheral than the others, due to pin out and whatnot - probably spent a lot more time documenting than I needed to
	- got the non-OOP code working with the LCD 

### [2022-10-15](2022-10-15)
- [tmi14 Multitasking-1](tmi14%20Multitasking-1.md)
	- added some non blocking functions - pushbutton and LED blink rate 
	- had trouble getting the RGB led to work but I think I just forgot to set the Pins correctly
	- instead I switched to just blinking a red led at a rate propo to the position
		- the trick was adding another timer for the falling edge so it was bright enough when the motor was stopped

### [2022-10-14](2022-10-14)
- [tmi14 Multitasking-1](tmi14%20Multitasking-1.md)
	- 12:48 finished writing and testing code for non-blocking servo - 0 to 180 and back 

### [2022-10-13](2022-10-13)
- installed platform io on vs code, copied and ran blink code; 
	- VS code command pallet (`CMD + SHIFT + P`) -> `BUILD (PlatformIO)` 2) then `Upload`
- research notes in [Multitasking and non blocking delays](../../Multitasking%20and%20non%20blocking%20delays.md) 

### [2022-10-12](2022-10-12)
[tmi12 Serial Input Basics](tmi12%20Serial%20Input%20Basics.md)
- learned how *not* to use blocking functions like `Serial.parseInt()`, and instead using a `while(Serial.available() > 0 && newData == false)` check  to process and store _new data_ and a `if (newData == true)` check to _write_ the store data to the output

### [2022-10-11](2022-10-11)
- after the matrix kind of bummed out seeing the sensor projects using all just libraries - i guess i could just look at the library and learn how it is implemented and write it from scratch 
- but for sensors that i dont really use, what is the point
- need to have the intersection of learning goals, interesting project but not too hard
	- learning objectives
		- serial & parallel communicafion
		- real time clock
		- lcd 
	- project ideas / uses
		- door alarm
		- earthquake sensor
		- cycling - turning signals; distance beeper
		- button press
- [tmi10 Matrix Keypad](tmi10%20Matrix%20Keypad.md)
	- finished at 1400 - had to debug some code and rewrite - esp. since the indexing was reversed
- [tmi11 Temp and Humidity Sensor](tmi11%20Temp%20and%20Humidity%20Sensor.md)
	- I'm guessing non-blocking is like using the `millis()` for debouncing instead of `delay()`

### [2022-10-10](2022-10-10)
- refactored some stuff in the notebook, better understanding of Board differences and functions
Projects
- [tmi09 Ultrasonic Sensor](tmi09%20Ultrasonic%20Sensor.md)
- [tmi10 Matrix Keypad](tmi10%20Matrix%20Keypad.md)

### [2022-10-07]
**Projects**
07- audio - elegoo Lesson 7 & 8 - Buzzers -> [tmi07 Buzzers](tmi07%20Buzzers.md)
- we need to do _frequency modulation_ (not PWM) to change the pitch (frequency) of the buzzer
- if we used PWM as in `analogWrite()` we would just be varying the loudness (amplitude) of the buzzer
- #q/answered  if my passive buzzer is only 16Ohms, how can I connect it directly to the arduino as an output? Wouldn't it draw more than 20mA? 
	- the [Buzzers - Active and Passive](../../Buzzers%20-%20Active%20and%20Passive.md) acts like a capacitor - so we cannot use the 16 Ohm value as a DC value
	- the datasheets (e.g. https://www.jp.tdk.com/tefe02/ec211_sdr.pdf) give a max current 25mA - 85mA  - this must be current draw based on a given voltage and pulse width

08 - motors [tmi08 Micro Servo](tmi08%20Micro%20Servo.md)
- mostly just uses the Servo library (download from Library Manager or online) to handle everything
- with this one we can drive with 
- [Servos](../../Servos.md)

**Research/Notepad**
[Buzzers - Active and Passive](../../Buzzers%20-%20Active%20and%20Passive.md)

### [2022-10-06](2022-10-06)
(Project)
**[banziGettingStartedArduino](banziGettingStartedArduino.md) Examples 5-3 
 to 5-5**
- 5-4 LED + photoresistor - analogue read [tmi06 LDR analogWrite to LED](tmi06%20LDR%20analogWrite%20to%20LED.md)
	- NB: analog pins are automatically set as inputs 
- [tmi03 Digital Inputs Debounce w Millis](tmi03%20Digital%20Inputs%20Debounce%20w%20Millis.md) - debouncing

Project 2
- `byte` is smaller than an `int` - [Arduino Variable Types](../../Arduino%20Variable%20Types.md)
	
(Research)
[Serial Communication](../../Serial%20Communication.md) -> [UART](../../UART.md) - see wikipedia 
	
**Diagramming / Tools**
- Kicad 
	- https://www.build-electronic-circuits.com/kicad-tutorial/
	- https://www.youtube.com/watch?v=jTMjb-1SVHo

[DIY Arduino Schematic in KiCad | AddOhms #23](https://www.youtube.com/watch?v=5fvdxd0QhTw) -> [Clocks](Clocks.md)
- Arduino internal clock can be slow and not as accurate as an external clock circuit -> [Introduction to Arduino - Hardware](../../Introduction%20to%20Arduino%20-%20Hardware.md)
- [ATMega328P](ATMega328P.md) has two built in oscillators - uses ceramic resonator
- RC Circuit vs Ceramic Resonator vs Crystal for creating a clock signal
	- Crystal > Resonator > RC Circuit
	- ![attachments/Screen Shot 2022-10-06 at 6.59.33 PM.png](attachments/Screen%20Shot%202022-10-06%20at%206.59.33%20PM.png)

### [2022-10-05](2022-10-05)
- [State Machines](../../State%20Machines.md) 
- [banziGettingStartedArduino](banziGettingStartedArduino.md) Project - Fade in LED if pushbutton is pressed 
	- [tmi05 Pushbutton LED Fade](tmi05%20Pushbutton%20LED%20Fade.md)
- wiring vs processing vs Arduino language https://forum.arduino.cc/t/how-is-arduino-related-to-wiring/69064/
- more on [Serial Communication](../../Serial%20Communication.md) and [Serial to USB](Serial%20to%20USB) ⬇️ 
	- "Current Arduino boards are programmed via [Universal Serial Bus](https://en.wikipedia.org/wiki/Universal_Serial_Bus "Universal Serial Bus") (USB), implemented using USB-to-serial adapter chips such as the [FTDI](https://en.wikipedia.org/wiki/FTDI "FTDI") FT232. Some boards, such as later-model Uno boards, substitute the [FTDI](https://en.wikipedia.org/wiki/FTDI "FTDI") chip with a separate AVR chip containing USB-to-serial firmware, which is reprogrammable via its own [ICSP](https://en.wikipedia.org/wiki/In-system_programming "In-system programming") header."  [](https://en.wikipedia.org/wiki/Arduino#Hardware)]
- Main Learnings
	- longs vs ints -> see [Intro to Arduino - Software](../../Intro%20to%20Arduino%20-%20Software.md)
	- use `unsigned long` for `millis()` timekeeping (can go up to -4.2Ms = 50 days)
	- some tricks for fading in and out see below and in [tmi05 Pushbutton LED Fade](tmi05%20Pushbutton%20LED%20Fade.md)
		- ![Pasted image 20221005215410](attachments/Pasted%20image%2020221005215410.png)


### [2022-10-04](2022-10-04) ✅ 
- [RGB LEDs](../../RGB%20LEDs.md)  see [code](./Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi_04_RGB_LED/tmi_04_RGB_LED.ino)
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

### [2022-10-03](2022-10-03)
From https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 on `millis()` vs `delay()` -> see [tmi 02 millis() forum examples]()%20forum%20examples)%20forum%20examples/tmi%2002%20millis()%20forum%20examples.md)


### [2022-10-02](2022-10-02)
- install zip libraries directly (no need to unpackage)
- a serial terminal is important to see the interaction with the Arduino via a computer - this is the Serial Monitor
- "Selecting which port to open in the Serial Monitor is the same as selecting a port for uploading Arduino code. Go to Tools -> Serial Port, and select the correct port." (source: [elegooCompleteStarterMega2560](elegooCompleteStarterMega2560.md)) - should be the same COM port as in DeviceManager
- [Mega2560](../../Mega2560.md) led is digital pin 13, see `LED_BUILTIN` variable
- tools > set board
- tools > set port (forgot this one)
- changed it to 500ms
- https://ht-deko.com/arduino/usb2serial.html#06 for [Serial to USB](Serial%20to%20USB.md) things (see [Serial Communication](../../Serial%20Communication.md)