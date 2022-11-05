parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
see-also::[Preprocessing Directives](Preprocessing%20Directives.md)
previous::[Object Oriented Programming](Object%20Oriented%20Programming.md)
resource::[Example - Even Better OOP - Header Files](Example%20-%20Even%20Better%20OOP%20-%20Header%20Files.md)

When using [Object Oriented Programming](Object%20Oriented%20Programming.md), we will commonly have three separate files for our code:
- Header or Library files: typically have class definitions, end with `.h`, for example a custom `Led.h` class code
- cpp files
- main file

### Example Header File `Led.h`

> [!NOTE]- Only function prototypes are stated in the header file 
> Note we only define the names of the functions and member variables, we don't write any of the functionality here - this also allows us to quickly see what member functions are available to this class.

```cpp
#ifndef MY_LED_H // "if MY_LED_H is not defined..."
#define MY_LED_H

#include <Arduino.h>

class Led {
  
  private:
    byte _pin; 
    
  public:
    Led(byte pin); // constructor
    void init();
    void on();
    void off();
};

#endif
```

### Example Cpp file `Led.cpp`

> [!NOTE] Here we use _quotes_ to include the custom `Led.h` header file and write the main functionality of the member functions.

```cpp
#include "Led.h"

Led::Led(byte pin) {
	_pin = pin;
	init();
}

void Led::init() {
	pinMode(_pin, OUTPUT);
	off();
}

void Led::on() {
	digitalWrite(_pin, HIGH);
}

void Led::off() {
	digitalWrite(_pin, LOW);
}

```

### Example Main file `main.cpp`

> [!NOTE] In `Main.cpp` we have to include our custom header files, which will include the relevant `cpp` files

```cpp
#include "Led.h"
#include "Button.h"

#define LED_1_PIN 9

Led led1(LED_1_PIN);

void setup() {
	led1.init();
}

void loop() {
	led1.on();
	delay(1000);
	led1.off();
}
```

