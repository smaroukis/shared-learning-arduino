parent:: [tmi Examples](tmi%20Examples.md)
previous:: 
next::

> from [Getting Started With Arduino](Personal%20Folders/that_marouk_ish%20(Spencer)/banziGettingStartedArduino.md), example 5-2.

Desired Goal: 
- when you press the button it turns the LED on and off (without holding)
- when you push and hold the pushbutton the LED fades in and out repeatedly
	- the button can be released and the LED will stay at the same brightness

Concepts:
- [Arduino - PWM](Arduino%20-%20PWM.md) - for fading in and out the LED
- [Resistors. (Resistors.md) as current limiters
- [Switches](Switches.md) - Pushbuttons
- using `millis()` for timing`

Code:
- [tmi_05_pushbutton_led_fade](Personal%20Folders/that_marouk_ish%20(Spencer)/code/tmi_05_pushbutton_led_fade/tmi_05_pushbutton_led_fade.ino).

Physical setup:
![](attachments/Pasted%20image%2020221005220840.png)

Copy of code: 
``` c++
// adapted from "Make: Getting Started with Arduino" 
// and https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade

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
    state = 1 - state; // change the state from ON to OFF or vice-versa
    t_start = millis(); // record time
    delay(t_delay); // for debouncing
  }

  // check if the button is (still) being held down
  if ((val == HIGH) && (old_val == HIGH)){

    // If the button is held for more than 500 ms
    if ((state == 1) && (millis() - t_start) > 500) {
      brightness = brightness + fadeAmount; // increment/decrement brightness
      delay(t_delay);

      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount; // to allow the above code to work 
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