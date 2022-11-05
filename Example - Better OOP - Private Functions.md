garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
previous::[Example - A Basic OOP Class for Multitasking](Example%20-%20A%20Basic%20OOP%20Class%20for%20Multitasking.md)
next::[Example - Even Better OOP - Header Files](Example%20-%20Even%20Better%20OOP%20-%20Header%20Files.md), [Example - OOP with Traffic Light Controller](Example%20-%20OOP%20with%20Traffic%20Light%20Controller.md)
#code

> Source: https://roboticsbackend.com/arduino-object-oriented-programming-oop/

### LED Class Example
- now we are using `private` variables - the pin doesn't need to be accessed by any other code but this class
- watch out for the syntax gotchas 
	- `;` at the end of the class
	- `this->` if you are using the same name for the class member variable/attribute and the parameter-created local variable in the constructor function

```cpp
class Led {
  private:
    byte pin;
  public:
    Led(byte pin) {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->pin = pin;
      init();
    }

    void init() {
      pinMode(pin, OUTPUT);
      // Always try to avoid duplicate code.
      // Instead of writing digitalWrite(pin, LOW) here,
      // call the function off() which already does that
      off();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }
}; // don't forget the semicolon at the end of the class
```

### Complete Code - Single File

```cpp
#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12

#define BUTTON_PIN 5

class Led {
  private:
    byte pin;
  public:
    Led(byte pin) {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->pin = pin;
      init();
    }

    void init() {
      pinMode(pin, OUTPUT);
      // Always try to avoid duplicate code.
      // Instead of writing digitalWrite(pin, LOW) here,
      // call the function off() which already does that
      off();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }
}; // don't forget the semicolon at the end of the class

class Button {
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
  public:
    Button(byte pin) {
      this->pin = pin;
      lastReading = LOW;
      init();
    }

    void init() {
      pinMode(pin, INPUT);
      update();
    }

    void update() {
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

    byte getState() {
      update();
      return state;
    }

    bool isPressed() {
      return (getState() == HIGH);
    }
}; // don't forget the semicolon at the end of the class

// Create your objects in the global scope so you can
// get access to them in the setup() and loop() functions
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