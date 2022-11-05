> Reverse chronological log of my learnings on Arduino
More Raw in [tmi Lab Notebook](tmi%20Lab%20Notebook.md)

[2022-11-01](2022-11-01)
- Cleaning up vault for publishing  in [Meta - Main Page](../../Meta%20-%20Main%20Page.md)

[2022-10-28](2022-10-28)
Days 12 - 21 - Object Oriented refactor and Final Thoughts

**Final Thoughts**
This will be the wrap-up post for here (thanks Mods for the sticky and support!). I have all my notes, resources and code on this [github repo](https://github.com/smaroukis/shared-learning-arduino) (I'm sure there are many errors in thought, which is why it is public - so you can tell me where I am thinking wrong), and although no-one joined me this time around, it is open for forks and contributions if others are interested. 

Like I said, my background is in electric power systems, so while I've taken programming courses and electrical circuits courses, I had never worked with microcontrollers before.

Some gotchas for me overall were:
- understanding the hardware interfaces (is a UART a protocol or a piece of hardware that handles I2C and SPI protocols?)
- using the wrong variable types (`int` vs `byte` vs `long`) or forgetting why I chose one 
- using `==` instead of `=` or vice versa
- generally not being able to think at 16MHz speed - I'm a power engineer so I only run at 60Hz.

**On Learning Resources**
tl;dr 
- find the resource for your level and desired pace, and it helps to do some basic projects before diving into the literature
- try to do things without libraries first 

I like books better than Youtube videos and articles since I can browse through them faster and they have a Table of Contents, and the most helpful book I found was Langbridge's Arduino Sketches. It's not just a cookbook of code, but rather helps you understand various protocols and hardware, and doesn't rely heavily on libraries in the example code. I also read Make: Getting Started with Arduino, but found the Langbridge book covered a broader variety of topics. 

I liked the Adafruit and Arduino.cc resources but the benefit of a book is that it is sequential and builds upon prior knowledge in the book itself.

**Object Oriented (OOP) Refactor**
tl;dr 
- OOP forced me to think differently, I had to go back to basic blinky projects to make sure it worked
- knowing OOP will make it easier to read Libraries
- but you will need to get comfortable with new syntax, pointers, pass-by-reference, and various scopes
- "debugging" is more difficult (harder to `Serial.print` just anywhere)
- a refresher course on C++ OOP or a book would have saved me some time, instead of trying to find code online for my specific use case (everyone implements OOP differently) - even though I had taken a C++ OOP course already!

I spent the majority of the past two weeks trying to re-factor my Project 15 code which did a servo sweep and updated an LCD screen and LED, but I quickly got in over my head. 

I ended up just refactoring to a Led and a Button class, and had a button short and long press perform different functions, in a non-blocking and object oriented way. For example here is the final loop. (full code [here](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/code/tmi16_Multitasking-OOP/src/main-working.cpp))

```cpp
void loop() {
    led.loop();
    button.loopStateMachine();

    if (button._wasChanged > 0) {
        if (button._state == 2) { 
            // long press
            led.toggleBlink();
            led.off(); // user indicator that blink is starting
        }
        if (button._state == 1) {
            // short press
            led.togglePower();
            led._blinkActive = 0; // stop blinking
        }
    }

    if (button._state == 3) { // state 3 does note exist
        led._brightnessScan = 1; // using flags which will be checked during led.loop
    }
    else led._brightnessScan = 0;
}
```

One of the obstacles I had to overcome was `Serial.print()`ing in a class, which would not have access to the `Serial` object at compile time. So I had to pass by reference a custom `HasSerial` class to my LED object for printing to the terminal ([source](https://forum.arduino.cc/t/using-serial-object-within-a-library-class/495564/4)): 

```cpp
//// Create Custom Serial Class /////
class HasSerial{
    protected:
        Stream* stream;
    
    public:
        HasSerial(HardwareSerial* serial){
            stream = serial;
        }
        void send(const char* mssg) {
            // mutable pointer to immutable strings
            stream -> print(mssg);
        }
        void sendln(const char* mssg) {
            stream -> println(mssg);
        }
}; 

//// Pass the Custom Serial Class by Reference to Other Classes /////
class Led {
	HasSerial &mySerial; // reference object

	Led(byte pin, long on, long off, HasSerial &serialAttach) : 
		_pin(pin),
		_tMinTimeOn_ms(on),
		_tMinTimeOff_ms(off),
		mySerial(serialAttach) // now we can use e.g. mySerial.send("message");
		{}

	void setupLed() {
		mySerial.sendln("Hello from inside the LED class");
	}
}

//// Create Objects /////

HasSerial serialInstance(&Serial);
Led led(LED_PIN, LED_MIN_ON_DELAY, LED_MIN_OFF_DELAY, serialInstance); 

//// Setup, Loop Below /////
```

OOP Resources:
- https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution
- https://forum.arduino.cc/t/using-serial-object-within-a-library-class/495564/3
- https://forum.arduino.cc/t/class-inheritance-and-polyphormism/93778/3
- https://paulmurraycbr.github.io/ArduinoTheOOWay.html - this goes really deep into inheritance and compound class objects and is the example of how a software engineer thinks about implementing classes for a headlamp and tail-light controller


2022-10-15
Days 10 and 11 - Multitasking Mania and New IDE
"Mania" because I found many ways to skin the multitasking cat, here I am trying to go with the most simple way, and progress towards some of the other techniques - see resources I found below. 


Finished [this project](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi13%20Multitasking-1.md) which demonstrates the first step of better multitasking(I would say this is now upper beginner level). I also started using VSCode with the PlatformIO extension - no issues so far.

The code rotates a servo motor from 0 to 180 position and stops when a pushbutton is pressed. An LED blinks at a rate proportional to the position of the servo (blinks fast at pos = 0 and slow at pos = 180). 

- user defined functions are introduced - so the main `loop()` is kept tight
- various user-defined timestamp variables are used to implement the multitasking
	- of particular note is two timers for blinking the LED - one for turning on and one for turning off. The turning on timer is used to control the blink rate, and the turning off timer is used so that when the motor is paused we can still "blink" for long enough (without a delay the blink is very dim because it immediately hits `digitalWrite(LED, OFF)` one main loop after `digitalWrite(LED, ON`). 

Questions
- when we update one of the timers with the current time, e.g. `tPreviousStep`, does it make a difference if we use the `tNow = millis()` that is at the beginning of the main `loop()` or if we do `tPreviousStep = millis()` within the user function?

Non-blocking & multitasking Resources
- https://learn.digilentinc.com/Documents/407 - basic, this was covered previously
- https://www.baldengineer.com/?s=millis - some tricks on millis
- https://learn.adafruit.com/multi-tasking-the-arduino-part-1 - nice three part walkthrough, similar to what I'm trying to do here (going from simple non-blocking toward OOP and Timers/interrupts)
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2
- https://learn.adafruit.com/multi-tasking-the-arduino-part-3
- https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html - good examples and uses an external library

Next up 
- add in object oriented programming structures to make it more readable and extendable

Code: 
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/code/tmi14_Multitasking-1/src/main.cpp

Of interest, here is where I used the rising and falling delays for the LED blink:
```c
void updateLED() {
  if (thisServoStarted) tLedDelayRising = map(pos, 0, 180, 50, 1000);

  if ((tNow - tPreviousLed >= tLedDelayRising)) {
    tPreviousLed = tNow; 
    digitalWrite(RED, HIGH);

  } else if (tNow - tPreviousLed >= tLedDelayFalling) {
    digitalWrite(RED, LOW); // need to add a falling timer so that we can light up brighter on time offs
  }
}
```

2022-10-13
Asked for input on what to learn next - people said non-blocking functions

2022-10-12
Day 8 - Serial Input Basics, Built In Example Reviews
Went through https://forum.arduino.cc/t/serial-input-basics-updated/382007/2 to understand Serial comms, non-blocking
- learned how *not* to use blocking functions like `Serial.parseInt()`, and instead using a `while(Serial.available() > 0 && newData == false)` check  to process and store _new data_ and a `if (newData == true)` check to _write_ the store data to the output

Did some diagramming about the things I still want to learn and some projects that are related. Perused the code on the [Arduino Built In Examples](https://docs.arduino.cc/built-in-examples/) to make sure I had seen most of the beginner stuff, which I had (well except for pots - but I already knew how voltage dividers work)

Something that was new (code-wise, not concept-wise) was the [Calibrate Sensor Input](https://docs.arduino.cc/built-in-examples/analog/Calibration) and the [Smoothing Readings From an Analog Input](https://docs.arduino.cc/built-in-examples/analog/Smoothing). 

I didn't really do too much of the String and USB examples since I think I'm generally more interested in sensors and whatnot. 

2022-10-11
Day 6 & 7 Ultrasonic Sensor, Matrix Keypad, Now What? 

`<commentary>`
I'm getting a little tired of just reading sensor data to the Serial Monitor, but now I think I have enough knowledge to try to interface a few different sensors into a novel larger project. I think the next day will be spent browsing interesting projects and creating some ideas. Things I still haven't covered and would like to incorporate before the end of day 15:
- Serial Communications other than with the Serial Monitor e.g. I2C, etc
- LCD screens
- real time clock
- shift register
- [x] strings and chars to the Serial Monitor
- stepper motors
- IR 
`</commentary>`

**Ultrasonic Sensor (SR04)** ([github](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi09%20Ultrasonic%20Sensor.md))

Goal: Write the real time distance measured by the sensor to the Serial Monitor

It is more fun to write it without the library, although it is nice that you can be up and running with just a library and some examples.

The sensor waits for a trigger pulse, then sends out a pulse and listens for the return, the data is returned via the ECHO pin, with a duration of a pulse equal to the time between sending and receiving. 

Use the built in  `pulseIn()` function to store the pulse (returns microseconds). e.g. 

```c
duration = pulseIn(ECHO, HIGH); // returns microseconds

// distance = 1/2 * (duration * k_speed-of-sound-in-air)
// k = 343 m/s (at T=20C) = 0.0343 cm/us
cm = (duration/2) * 0.0343; 
```

Resources/Further
- HC-SR04 datasheet ([sparkfun](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf))
- https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
- use the [NewPing](https://www.arduino.cc/reference/en/libraries/newping/) library which adds improvements

**Matrix Keypad** ([github](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi10%20Matrix%20Keypad.md))

Goal: Output the current button press to the Serial Monitor (no libraries)

Worked with arrays and nested loops. We loop through columns setting them as OUTPUTs, writing them LOW, then we loop through the rows setting them HIGH with an INPUT_PULLUP. If a button is pressed it completes the circuit pulling the input LOW. 

Interestingly I had setup my array incorrectly and the rows and columns were reversed - since the Keypad pins are defined right to left and bottom to top, but we loop/access the array from the opposite direction, one of them has to be reversed in the code. [Example](https://raw.githubusercontent.com/smaroukis/shared-learning-arduino/main/Personal%20Folders/that_marouk_ish/attachments/IMG_7355.jpg).

Resources
- https://forum.arduino.cc/t/keypad-without-keypad-library/656198/7 - mainly remixed this code
- https://www.baldengineer.com/arduino-keyboard-matrix-tutorial.html - provides good example of the theory
- Use `Keypad` [Library](https://www.arduino.cc/reference/en/libraries/keypad/) to implement the code more easilly

[2022-10-07](2022-10-07)
**Day 5 - Active vs Passive Buzzers, Servos (+Questions)**

**Mini Project 07 - Buzzers**  ([github](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi08%20Micro%20Servo.md))
- various types of buzzers, by operating principle (magnetic or piezo) and input (DC / AC)
- to change tone use _frequency modulation_ (not PWM which changes effective DC *amplitude*) 
- active buzzers have their own oscillating circuit, but for passive buzzers you must supply an oscillating square wave (the `tone()` function handles this for Arduino on any pin). 
- I used a pullup input plus a pushbutton to beep when pressed 

It is just a simple digital output - but notably my buzzer didn't require a limiting resistor unlike a speaker or LED.

``` c
void setup(){
  pinMode(BUZZER, OUTPUT); // digital output (DC HIGH/LOW) since it is an active buzzer
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop(){
  buttonState = !digitalRead(BUTTON); // due to pullup (unpressed = 5V), logic is reversed

  // if button is pressed, set the buzzer HIGH (DC)
  if (buttonState == 1){
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }
}
```

Using the `tone()` function with a passive buzzer:
``` c
for (int thisNote = 0; thisNote < 8; thisNote++) {
	tone(BUZZER_PASSIVE, melody[thisNote], 500); // where melody is an array of ints containing the notes, see the built in example
	delay(1000);
}
noTone(BUZZER_PASSIVE); // to stop it
```

References - Buzzer
- https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody - built in `tone()` example
- https://itp.nyu.edu/physcomp/labs/labs-arduino-digital-and-analog/tone-output-using-an-arduino/ - more on `tone()` and music theory


**Mini Project 08 - Servo** ([github](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi07%20Buzzers.md))
- one or two servos can be powered directly from 5V on the Arduino (at least for my mini servos - check the current draw is under 20mA as usual)
- to drive the servo we provide a pulse to a signal pin - the duration of the pulse is proportional to the rotation
- the `Servo` library handles this for us, we just need to provide an angle in degrees (download from Library Manager) 

e.g. 
``` c
#include <Servo.h>
Servo myservo; // create Servo object from the library

void setup(){
	myservo.attach(SERVO_PIN); // digital pin
	myservo.write(90); // moves servo to center position -> 90°
}
```

References - Servo
- https://www.arduino.cc/reference/en/libraries/servo/

Outstanding Questions
- why doesn't the buzzer need a current limiting resistor like a LED or speaker? Mine is 16 Ohms

[2022-10-06](2022-10-06)
Day 4 - LDR and `millis()` Debouncing, Using the Serial Monitor

Code Snippets
``` c
analogWrite(LED, val/4); // since analogRead() is 16 bit but analogWrite is 8 bit ()
```

``` c
led_state = (led_state == LOW ? HIGH : LOW); // ternary operator to switch led state
```

Hardware Learnings
- Using digital inputs as pullups allows you to forego the current limiting resistor if they were "ON" at 5V. (e.g. `pinMode(7, INPUT_PULLUP)`
- LDRs - use 10K load/sense resistor in the example -my LDR varies from 20kOhms (10 lux) to 2MOhms (0 lux) - the voltage sensed by the pin is over the sense resistor

Mini Projects
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi02%20Digital%20Inputs.md - digital inputs and pullup inputs
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi03%20Digital%20Inputs%20Debounce%20w%20Millis.md - debouncing with `millis()`
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/tmi06%20LDR%20analogWrite%20to%20LED.md - LDR, outputting value to Serial Monitor

Readings
- https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573/4 - millis() for debouncing e.g. Blink Without Delay
- https://forum.arduino.cc/t/serial-input-basics-updated/382007/2 -- didn't use this one but started to look at Serial things
- https://docs.arduino.cc/tutorials/generic/digital-input-pullup - digital input example
- https://forum.arduino.cc/t/long-press-toggle-output-high-and-low/587500/3 - more on debouncing and Blink Without Delay


[2022-10-05](2022-10-05) 
Day 3 - Fading LED, Pushbutton Orientation

Today I spent a lot of time debugging both some code errors and wiring errors. I kept forgetting the orientation of the pushbutton contacts - even looking at the schematics of the internals. But then I realized the orientation in the photo is the same as a breadboard if it spans the rails, so you don't need to look at the back to determine which contacts are connected...whew. 

The mini-project combined some code from the Built in [Fade Example](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade) and from the _Make:_ book Getting Started with Arduino (Banzi, Shiloh). 

I specifically liked the `fadeAmount = -fadeAmount` line to switch between fading in and out. (see line 47 of [the code](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish/code/tmi05_pushbutton_led_fade/tmi05_pushbutton_led_fade.ino) in the hosted version)

Mostly I felt good about self-identifying and fixing the wiring and coding errors, even though it took me longer than I thought. I like to type everything out by hand to get a feel for the syntax but it's easy to make software mistakes and then think it is a wiring issues and vice versa. 

[2022-10-04](2022-10-04) 
Day 2 - Party Time - RGB LEDs 
So today I was onto the first interesting project that I learned more than I expected from. Mostly on the analog side about LEDs and their I-V curves.  

The project was to fade/cycle through various colors using an RGB LED controlled with PWM from the Arduino.  

The RGB LED is three separate LEDs with a common node, and we can make "any" light color by varying the intensities of each channel - the LEDs are close enough in space that we see the combination as a singular color. The intensity of each channel is varied by PWM.  

I learned why I have a ton more of 220Ohm resistors in my kit than the others:  
Limiting the load on a pin to 20mA: assuming worst case (lowest forward voltage) of 1.8V across an LED when on, with a 5V input leaves 3.2V across a resistor. The 220Ohm resistor limits this to I=3.3V/220=15mA.  ➡️ [Resistor Calculation for LEDs](../../Resistor%20Calculation%20for%20LEDs.md)

But then I thought I could just use one resistor on the cathode instead of three separate resistors on the anodes. I quickly learned that due to the difference in forward voltage for the different colors, this wouldn't work. Basically, the red LED will turn on before the others. Also, the total current will change based on how intense each channel shines, so the light will change intensity based on the color, which we don't want

I changed the tutorial's `#define`s to `const int` - another thing I learned (define's are from the C language but const int is generally better for beginners)

Resources:
- RGB LED basics https://www.circuitbread.com/tutorials/how-rgb-leds-work-and-how-to-control-color 
- Why you need 3 resistors https://www.circuitbread.com/tutorials/why-cant-i-share-a-resistor-on-the-common-anode-or-cathode-of-my-rgb-led
- Define vs Const Int https://forum.arduino.cc/t/when-to-use-const-int-int-or-define/668071/ 

RGB LEDs Going further #tdf-project
-   Use finer tuned resistors for each color to get intensities to match
-   Avoid light intensity changing based on the color
-   Add more colors
-   Set the color by a potentiometer
- Better code (see [](https://os.mbed.com/users/4180_1/notebook/rgb-leds/#:~:text=The%20three%20LEDs%20inside%20a,may%20drop%20around%203%20volts.))


[2022-10-03](2022-10-03)
Nothing today except some reading about `millis()` vs `delay()` - basically just get comfortable with `millis()` since it allows you to do multiple things at (perceivable) the same time (see Notepad)

[2022-10-02](2022-10-02) - Day 1 - Unboxing  - a Mega?? and Blink

I thought I had ordered an (unofficial) Uno starter kit but when I opened it I found a Mega inside. Honestly I wanted an Uno, since I'm sure many tutorials are built off that, and if I want to use an Uno later I'll have to check and change the pin numbers in the code. 

 So I learned besides the main differences (more pins, more PWM, more storage, ATMega2560 vs ATMega328P), another one is that the Mega has a USB to Serial driver chip built in, where-as the Uno's ATMEGA328P needs an external ATMega 16U2 USB-to-Serial converter. 

Well, then, after that rabbit hole I did follow the instructions to get it to blink the led, and changed it from 1s to 0.5s. Also changed the variable `LED_BUILTIN` to `13` to verify that is the correct LED pin for the Mega. 


[2022-10-01](2022-10-01)
Started this Vault with [Arduino](../../Arduino.md). Learned that [Arduino - PWM](../../Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [Uno](../../Uno.md) is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).