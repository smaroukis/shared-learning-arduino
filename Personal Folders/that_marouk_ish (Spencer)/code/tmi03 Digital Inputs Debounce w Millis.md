parent::[tmi Examples](../../../tmi%20Examples.md)
next:: [[tmi04 RGB LED]], [tmi05 Pushbutton LED Fade](tmi05%20Pushbutton%20LED%20Fade.md)
previous:: [[tmi 02 ]]
level:: #beginner

>  Adapted from Elegoo Mega2560 Starter Kit Lesson 5 and https://forum.arduino.cc/t/long-press-toggle-output-high-and-low/587500/3

Desired Goal:
- Toggle the LED on and off with a pushbutton
- Debounce the pushbutton in software (see [tmi05 Pushbutton LED Fade](tmi05%20Pushbutton%20LED%20Fade.md) first for an easier example)

Concepts:
- debouncing - Blink Without Delay (BWD) - using `millis()` and not `delay()`
- `byte` vs `ints` vs `longs` 
- Digital inputs & pullup resistors

Physical Setup:
- 

Code:


``` c
// Inputs
const int LED = 9;
const int BUTTON = 7;

// Others
byte state = HIGH; // due to the pullup
byte old_state = HIGH;
byte led_state = LOW;
unsigned long debounce_start = 0;
unsigned long current_time; 
bool debouncing = false;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);  // pullup = normal HIGH or 5V   
}

void loop(){
  current_time = millis();

  state = digitalRead(BUTTON); // PULLUP so normal is HIGH
  if (state != old_state)
  { // either button is pressed or it is noise
    debounce_start = current_time;     // reset debouncing timer
    old_state = state;
    debouncing = true; // we are debouncing
  }
  else if (debouncing && state == LOW && (current_time - debounce_start > 50))
  { // else if is key here
    // take the current value as the actual state
      led_state = (led_state == LOW ? HIGH : LOW); // ternary operator to switch led state
      digitalWrite(LED, led_state);
      debouncing = false;
  }
}
```

Improvements:
- 