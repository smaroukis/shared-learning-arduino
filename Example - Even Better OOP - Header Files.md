garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md), [Preprocessing Directives](Preprocessing%20Directives.md)
previous::[Example - Better OOP - Private Functions](Example%20-%20Better%20OOP%20-%20Private%20Functions.md)
#code

> Source: https://roboticsbackend.com/arduino-object-oriented-programming-oop/

**General Structure and Syntax**
- now we need to `#include <Arduino.h>` in each file (for `pinMode()`, `digitalWrite()`, etc.)
	- for internal/local `includes` use quote style e.g. `#include "My_Led_Header_File.h"`
	- for external libraries use bracket style e.g. `#include <Arduino.h>`

> The header guards, `#ifndef...#define...#endif` (first 2 lines, and last line) will make sure that the Led class will not be included more than once if we have multiple `#include "Led.h"` in other parts of the program. (note they can be named whatever, usually for `<filename.h>` we use `FILENAME_H`)

### `Led.h`:
```cpp
// in Led.h we just define the class member variables
// the constructor is in `Led.cpp`

#ifndef MY_LED_H // "if MY_LED_H is not defined..."
#define MY_LED_H

#include <Arduino.h>

class Led {
  
  private:
    byte pin;
    
  public:
    Led(byte pin);
    void init();
    void on();
    void off();
};

#endif
```

### `Led.cpp`
```cpp
//in Led.cpp, we define the class functions (including constructor) 
// using the <Class_name>::<Function_name> syntax

#include "Led.h"

// Constructor
Led::Led(byte pin) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  this->pin = pin;
  init();
}

void Led::init() {
  pinMode(pin, OUTPUT);
  // Always try to avoid duplicate code.
  // Instead of writing digitalWrite(pin, LOW) here,
  // call the function off() which already does that
  off();
}

void Led::on() {
  digitalWrite(pin, HIGH);
}

void Led::off() {
  digitalWrite(pin, LOW);
}
```

### `Button.h`
```cpp
// in Button.h we provide function prototypes and define member variables
// definitions go in the c file

#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button {
  
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
    
  public:
    Button(byte pin);

    void init();
    void update();

    byte getState();
    bool isPressed();
};

#endif
```

### `Button.c`
```cpp
// in Button.c we add function definitions usince 

#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
  lastReading = LOW;
  init();
}

void Button::init() {
  pinMode(pin, INPUT);
  update();
}

void Button::update() {
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    byte newReading = digitalRead(pin);
    
    if (newReading != lastReading) {
      lastDebounceTime = millis();
    }

    if (millis() - lastDebounceTime > debounceDelay) {
      // Update the 'state' attribute only if debounce is checked
      state = newReading;
    }

    lastReading = newReading;
}

byte Button::getState() {
  update();
  return state;
}

bool Button::isPressed() {
  return (getState() == HIGH);
}
```

### `Main.cpp`
```cpp
#include "Led.h"
#include "Button.h"

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12

#define BUTTON_PIN 5

Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);
Led led4(LED_4_PIN);
Button button1(BUTTON_PIN);

void setup() { }

void loop() {
  if (button1.isPressed()) {
    led1.on();
    led2.off();
    led3.on();
    led4.off();
  }
  else {
    led1.off();
    led2.on();
    led3.off();
    led4.on();
  }
}
```
