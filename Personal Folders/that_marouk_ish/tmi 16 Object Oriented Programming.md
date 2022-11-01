parent::[[tmi Examples]]
previous:: [[tmi15 Multitasking-2]]
next:: 
level:: #intermediate 
garden-topic:: [[../../Multitasking and non blocking delays]], [[../../Object Oriented Programming]]

>  (source)

Desired Goal:
-  Refactor some of the previous examples using object oriented programming structures

[[../../Example - A Basic OOP Class for Multitasking]] shows the basic concept, but does't implement any interesting control schemes.

Concepts:
- passing values back and forth between function calls and class objects forces you to really understand how to write non-blocking code and functions, and how to structure the flow of the program
- first I made a `Button` and `Led` class, to be re-usable in the future
- the `Button` class implements debouncing and short versus long button presses
- the `Led` class can be toggled on/off, be set to blinking, change the blink rate, and change the brightness (if connected to a PWM pin)
- the goal is to make the code easy to read and reuse, I tried to use "flags" that the individual class objects would check during their main `loop()` e.g. `Led::loop()` checks its `blinkActive` and `brightnessScan` values -- which are set by an external "Controller" (although here I just used the main `loop()` for this)
- I had to learn about pass by reference to be able to `Serial.print()` within the class, I created a custom `HasSerial` class which had a pointer to the `Serial` object so it could use it. Then I passed this by reference to each of the `Led` and `Button` classes

## Shortening the main `loop()` with OOP

Now the main loop is readable and extensible. Note I could've implemented a "Controller Class" here if I was going to use this same type of button functionality in the future (short / long press with different led functions)

```cpp
void loop() {
    // Testing Only
    led.loop();
    button.loopStateMachine();

    if (button._wasChanged > 0) {
        if (button._state == 2) { // state 3 does not exist
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

### Debugging Within a Class- Using a Serial Instance passed to a class to use `Serial.print()` within a class.

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

## Code:
``` c
// Object Oriented Demonstration of pushbutton LED control
// LED class can be blinked, toggled ON/OFF, or changed brightness
// Button class has debouncing, short and long press states and state change detection
// "Debugging" is from the HasSerial Class (can only print strings)

#include <Arduino.h>

const byte DEFAULT_OFF_DELAY=50;

const byte BUTTON_PIN=2;
const int BUTTON_DEBOUNCE_DELAY=50; //  aka short press
const int BUTTON_LONG=3000; // set long for testing;

const byte LED_PIN=4;
const int LED_MIN_ON_DELAY=500; // for blinking: the minimum time the LED should be on before we turn it off
const int LED_MIN_OFF_DELAY=1000; // for blinking: the min. time the LED should be off before we turn it on

class HasSerial{
// instantiate with eg HasSerial myinstance(&Serial);
// in setup() do Serial.begin();
// access with myinstance.send("Literal string")
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


class Led
{
    private:
        byte _pin;
        long _tMinTimeOn_ms; // to check when turning 0
        long _tMinTimeOff_ms; // to check when turning 1s
        unsigned long _tPrevious_ms; 
        int _delta; // for brightness
        byte _brightness;


        void blink() {
            unsigned long tNow_ms = millis();
                // rising edge - ready to turn ON
                if (_state == 0 && (tNow_ms - _tPrevious_ms >= _tMinTimeOff_ms)) {
                    on();
                    _tPrevious_ms = tNow_ms;
                }
                // falling edge - ready to turn Off
                else if (_state == 1 && (tNow_ms - _tPrevious_ms >= _tMinTimeOn_ms)) {
                    off();
                    _tPrevious_ms = tNow_ms;
            } 
        } 

        void sweepBrightness() {
            if (millis() - _tPrevious_ms >= 10) {
                analogWrite(_pin, _brightness);
                _brightness += _delta; // move down
                _tPrevious_ms = millis();
                if (_brightness == 255 || _brightness == 0) _delta = -_delta;
            }
        }

    public:
        HasSerial &mySerial; // reference object
        byte _state;
        byte _blinkActive;
        byte _brightnessScan;

        Led(byte pin, long on, long off, HasSerial &serialAttach) : 
            _pin(pin),
            _tMinTimeOn_ms(on),
            _tMinTimeOff_ms(off),
            mySerial(serialAttach) // now we can use e.g. mySerial.send("message");
            {}

        void setup() { 
            pinMode(_pin, OUTPUT);
            off();
            _blinkActive = 0; // default
            _brightness = 0;
            _delta = 1;
        }
        void loop() {
            _state = digitalRead(_pin);
            if (_blinkActive == 1) blink();

            if (_brightnessScan == 1) sweepBrightness();
        }

        void off() {
            digitalWrite(_pin, LOW);
        }

        void on() {
            digitalWrite(_pin, HIGH);
        }

        void togglePower() {
            
            digitalWrite(_pin, !_state);
            mySerial.send("Toggled LED -> ");
            if (_state) mySerial.sendln("ON");
            else mySerial.sendln("OFF");
        }

        void updateBlinkRate(int msOn, int msOff) {
            _tMinTimeOff_ms = msOff;
            _tMinTimeOn_ms = msOn;
        }

        void toggleBlink() {
            _blinkActive = !_blinkActive;
        }

}; // don't forget semicolo/

class Button {
    // an Input_Pullup button with short and long button press detection
    // detect changes using _wasChanged (short or long change = 1; unpressed = -1)
    // get state with _state 
    HasSerial &mySerial;  // debugging
    const byte _pin;
    long _tDebounce_ms; // better: add ms suffix
    unsigned long _tLongPress_ms;
    unsigned long _tPrevious_ms; 
    byte _lastReading;

    public: 
        enum States {
            UNPRESSED = 0,
            SHORT_PRESS = 1,
            LONG_PRESS = 2
        } _state;

        int _wasChanged; // going against common OOP practicies which uses accessor functions 

        Button(byte pin, unsigned long delay_short, unsigned long delay_long, HasSerial &serialAttach) : 
            _pin(pin),
            _tDebounce_ms(delay_short),
            _tLongPress_ms(delay_long),
            mySerial(serialAttach) {
            }

        void setup() { 
            pinMode(_pin, INPUT_PULLUP);
            digitalWrite(_pin, HIGH);
            _state = UNPRESSED; 
            _lastReading = 0; // 0 == unpressed (non-inverted logic)
            _wasChanged = 0;
        }

        void loopStateMachine() {
            byte newReading = !digitalRead(_pin); // invert logic for pullup 
            int prevState = _state; // for edge change detection

            switch (_state) {
                case UNPRESSED: // 0
                    if (newReading != _lastReading) {
                        _tPrevious_ms = millis();
                        _lastReading = newReading;
                        mySerial.sendln("Debouncing...");
                    } else if (newReading && (millis() - _tPrevious_ms > _tDebounce_ms)) {
                        _state = SHORT_PRESS;
                        mySerial.sendln("Changed state to SHORT_PRESS...");
                    } 
                    break;
                case SHORT_PRESS: // 1
                    if (!newReading) {
                        _state = UNPRESSED; // immmediately latch to unpressed
                        _tPrevious_ms = millis(); // helps with debouncing on release 
                        mySerial.sendln("Changed state to UNPRESSED...");
                    } else if (millis() - _tPrevious_ms > _tLongPress_ms) {
                        _state = LONG_PRESS; // increment state
                        mySerial.sendln("Changed state to LONG PRESS...");
                    } 
                    break;
                case LONG_PRESS: // 2
                    if (!newReading) {
                        _state = UNPRESSED;  
                        _tPrevious_ms = millis(); // helps with debouncing on release 
                        mySerial.sendln("Changed state to UNPRESSED...");
                    }
                    break;
            }

            if (prevState != _state) {
                if (_state > prevState) {
                    _wasChanged = 1;
                    mySerial.sendln("_wasChanged to 1...");
                } 
                else if (_state < prevState) {
                    _wasChanged = -1;
                    mySerial.sendln("_wasChanged to -1...");
                }
            }
            else {
                _wasChanged = 0;
            } 
        } 
}; 

HasSerial serialInstance(&Serial);
Led led(LED_PIN, LED_MIN_ON_DELAY, LED_MIN_OFF_DELAY, serialInstance);
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY, BUTTON_LONG, serialInstance);

void setup() {
    led.setup();
    button.setup();
    Serial.begin(9600);
    Serial.println("Hello..");
}

void loop() {
    // Testing Only
    led.loop();
    button.loopStateMachine();

    if (button._wasChanged > 0) {
        if (button._state == 2) { // state 3 does not exist
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

Improvements:
- 