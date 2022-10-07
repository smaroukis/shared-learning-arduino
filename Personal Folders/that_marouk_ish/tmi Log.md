> Reverse chronological log of my learnings on Arduino

More Raw in [tmi Lab Notebook](tmi%20Lab%20Notebook.md)

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
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi02%20Digital%20Inputs.md - digital inputs and pullup inputs
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi03%20Digital%20Inputs%20Debounce%20w%20Millis.md - debouncing with `millis()`
- https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi06%20LDR%20analogWrite%20to%20LED.md - LDR, outputting value to Serial Monitor

Readings
- https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573/4 - millis() for debouncing e.g. Blink Without Delay
- https://forum.arduino.cc/t/serial-input-basics-updated/382007/2 -- didn't use this one but started to look at Serial things
- https://docs.arduino.cc/tutorials/generic/digital-input-pullup - digital input example
- https://forum.arduino.cc/t/long-press-toggle-output-high-and-low/587500/3 - more on debouncing and Blink Without Delay


[2022-10-05](2022-10-05) 
Day 3 - Fading LED, Pushbutton Orientation

Today I spent a lot of time debugging both some code errors and wiring errors. I kept forgetting the orientation of the pushbutton contacts - even looking at the schematics of the internals. But then I realized the orientation in the photo is the same as a breadboard if it spans the rails, so you don't need to look at the back to determine which contacts are connected...whew. 

The mini-project combined some code from the Built in [Fade Example](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade) and from the _Make:_ book Getting Started with Arduino (Banzi, Shiloh). 

I specifically liked the `fadeAmount = -fadeAmount` line to switch between fading in and out. (see line 47 of [the code](https://github.com/smaroukis/shared-learning-arduino/blob/main/Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi05_pushbutton_led_fade/tmi05_pushbutton_led_fade.ino) in the hosted version)

Mostly I felt good about self-identifying and fixing the wiring and coding errors, even though it took me longer than I thought. I like to type everything out by hand to get a feel for the syntax but it's easy to make software mistakes and then think it is a wiring issues and vice versa. 

[[2022-10-04]] 
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
- Better code (see [example](https://os.mbed.com/users/4180_1/notebook/rgb-leds/#:~:text=The%20three%20LEDs%20inside%20a,may%20drop%20around%203%20volts.))


[2022-10-03](2022-10-03)
Nothing today except some reading about `millis()` vs `delay()` - basically just get comfortable with `millis()` since it allows you to do multiple things at (perceivable) the same time (see Notepad)

[2022-10-02](2022-10-02) - Day 1 - Unboxing  - a Mega?? and Blink

I thought I had ordered an (unofficial) Uno starter kit but when I opened it I found a Mega inside. Honestly I wanted an Uno, since I'm sure many tutorials are built off that, and if I want to use an Uno later I'll have to check and change the pin numbers in the code. 

 So I learned besides the main differences (more pins, more PWM, more storage, ATMega2560 vs ATMega328P), another one is that the Mega has a USB to Serial driver chip built in, where-as the Uno's ATMEGA328P needs an external ATMega 16U2 USB-to-Serial converter. 

Well, then, after that rabbit hole I did follow the instructions to get it to blink the led, and changed it from 1s to 0.5s. Also changed the variable `LED_BUILTIN` to `13` to verify that is the correct LED pin for the Mega. 


[[2022-10-01]]
Started this Vault with [Arduino](Arduino.md). Learned that [Arduino - PWM](Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [Uno](Uno.md) is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).