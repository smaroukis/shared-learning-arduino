parent:: [tmi Examples](tmi%20Examples.md)
previous:: [tmi04 RGB LED](tmi04%20RGB%20LED.md), [tmi03 Digital Inputs Debounce w Millis](tmi03%20Digital%20Inputs%20Debounce%20w%20Millis.md)
next:: [tmi06 LDR analogWrite to LED](tmi06%20LDR%20analogWrite%20to%20LED.md)
level:: #beginner 

> Inspiration from [Getting Started With Arduino](banziGettingStartedArduino.md), example 5-2 and https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade


Desired Goal: 
- when you press the button it turns the LED on and off (without holding)
- when you push and hold the pushbutton the LED fades in and out repeatedly
	- the button can be released and the LED will stay at the same brightness

Concepts:
- [Arduino - PWM](../../Arduino%20-%20PWM.md) - for fading in and out the LED
- [Resistors](../../Resistors.md) as current limiters
- [Switches](../../Switches.md) - Pushbuttons
- [Multitasking and non blocking delays](../../Multitasking%20and%20non%20blocking%20delays.md) using `millis()` for timing

Further:
- try to eliminate the pushbutton pulldown resistor (see [tmi02 Digital Inputs](tmi02%20Digital%20Inputs.md))

Code:
- [tmi_05_pushbutton_led_fade](Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi_05_pushbutton_led_fade/tmi_05_pushbutton_led_fade.ino).

Physical setup:
![Pasted image 20221005220840](attachments/Pasted%20image%2020221005220840.png)

Copy of code: 
``` c++
// The code (1) turns on and off an LED when the pushbutton is pressed and
// (2) fades the LED in and out when the pushbutton is held down)

// Constants
const int LED = 9;
const int BUTTON = 7; 
const int t_delay = 20;

// Inputs
int val = 0;

// Other
int fadeAmount = 5;
int old_val = 0; // stores previous value of "val" (input)
int state = 0; // 0 = LED off and 1 = LED on
int brightness = 128; // out of 255 (1 byte for analogWrite())
unsigned long t_start = 0; // unsigned long is 0 to ~4.2 million

void setup(){
  pinMode(LED, OUTPUT); 
  pinMode(BUTTON, INPUT);
}

void loop(){
  
  val = digitalRead(BUTTON);

  //check for a button press (tranisition LOW->HIGH)
  if ((val == HIGH) && (old_val == LOW)){
    state = 1 - state; // change the LED state variable from ON to OFF or vice-versa
    t_start = millis(); // record time
    delay(t_delay); // do I need this? 
  }

  // check if the button is (still) being held down
  if ((val == HIGH) && (old_val == HIGH)){

    // If the button is held for more than 500 ms
    if ((state == 1) && (millis() - t_start) > 500) {
      brightness = brightness + fadeAmount; // increment/decrement brightness
      delay(t_delay); // so the brightness doesn't shoot up

      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount; // cool switch for fading in and out
        }
    } 
  }

  old_val = val; // don't forget to store the old value for the next loop

  if (state == 1) {
    analogWrite(LED, brightness); // turn LED ON at the brightness level
  } else {
    analogWrite(LED, 0); // turn LED OFF
  }
}
```