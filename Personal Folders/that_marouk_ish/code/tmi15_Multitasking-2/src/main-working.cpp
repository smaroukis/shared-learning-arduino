
#include <Arduino.h>

#define DEFAULT_OFF_DELAY 50

#define BUTTON_PIN 2
#define BUTTON_DEBOUNCE_DELAY 200 // set long for testing
#define BUTTON_LONG 500 // set long for testing

#define LED_PIN 4
#define LED_MIN_ON_DELAY 500 
#define LED_MIN_OFF_DELAY 1000

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
    // could implement this without the "state" variable
    private:
        byte _pin;
        long _tMinTimeOn_ms; // to check when turning 0
        long _tMinTimeOff_ms; // to check when turning 1s
        unsigned long _tPrevious_ms; 

    // constructor
    public:
        HasSerial &mySerial; // reference object
        byte state;
        byte blinkState;

        Led(byte pin, long on, long off, HasSerial &serialAttach) : 
            _pin(pin),
            _tMinTimeOn_ms(on),
            _tMinTimeOff_ms(off),
            mySerial(serialAttach) // now we can use e.g. mySerial.send("message");
            {}

        void setup() { 
            pinMode(_pin, OUTPUT);
            off();
            state = 0; // default
            blinkState = 0; // default
        }

        void loop() {
        // TODO - under development
        // if we are in blink mode, run the blink command
        if (blinkState) blink();

        // if toggle...

        }

        void off() {
            digitalWrite(_pin, LOW);
        }

        void on() {
            digitalWrite(_pin, HIGH);
        }

        void toggle() {
            state = !state;
            digitalWrite(_pin, state);
            mySerial.sendln("Toggled LED ");
        }

        void blink() {
            unsigned long tNow_ms = millis();
                // rising edge - ready to turn ON
                if (state == 0 && (tNow_ms - _tPrevious_ms >= _tMinTimeOff_ms)) {
                    on();
                    state = 1;
                    _tPrevious_ms = tNow_ms;
                }
                // falling edge - ready to turn Off
                else if (state == 1 && (tNow_ms - _tPrevious_ms >= _tMinTimeOn_ms)) {
                    off();
                    state = 0;
                    _tPrevious_ms = tNow_ms;
            } 
        } 

        void updateBlinkRate(int msOn, int msOff) {
            _tMinTimeOff_ms = msOff;
            _tMinTimeOn_ms = msOn;
        }
}; // don't forget semicolo/

class Button {
    HasSerial &mySerial;  // debugging
    // FUTURE - implement short and long button pressses
    const byte _pin;
    long _tDebounce_ms; // better: add ms suffix
    unsigned long _tLongPress_ms;
    unsigned long _tPrevious_ms; 
    byte _lastReading;
    byte wasChanged; 

    enum States {
        UNPRESSED = 0,
        SHORT_PRESS = 1,
        LONG_PRESS = 2
    } _state;

    public: 
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

        // void loop() {
        //     byte newReading = !digitalRead(_pin); // invert logic for pullup 
        //     // TODO here - to implement short and long button presses

        //     if (newReading != _lastReading) {
        //         _tPrevious_ms = millis(); // start timer
        //         _lastReading = newReading; // lastReading persists
        //         // _state = DEBOUNCING; FUTURE use
        //         mySerial.sendln("Debouncing started..");
        //     } else if (millis() - _tPrevious_ms >= _tDebounce_ms) {
        //         // last reading must == new reading
        //         if (newReading == 0) {
        //             _state = UNPRESSED; 
        //             mySerial.sendln("Updated Button to Unpressed..");
        //             }
        //         else if (newReading == 1) { 
        //             _state = SHORT_PRESS;
        //             mySerial.sendln("Updated Button to Pressed..");
        //             }
        //         _tPrevious_ms = millis(); // reset timer
        //     } 
        // }

        void loopWithLongPress() {
            // this still does not work because when we reset we start over again
            // potentially more efficient would be to use a case/switch statement
            byte newReading = !digitalRead(_pin); // invert logic for pullup 

            if (newReading != _lastReading) {
                // start debounce
                _tPrevious_ms = millis(); // start timer
                _lastReading = newReading; // lastReading persists
            } 
            else if (millis() - _tPrevious_ms < _tDebounce_ms) {
                    //  do nothing, debouncing
                    mySerial.sendln("Debouncing..");
            } 
            else if (newReading && (millis() - _tPrevious_ms < _tLongPress_ms)) {
                    _state == SHORT_PRESS; 
                    mySerial.sendln("Short Press..");
            } 
            else if (newReading && (millis() - _tPrevious_ms >= _tLongPress_ms)) {
                _state = LONG_PRESS;
                mySerial.sendln("Long Press..");
            } else {
                _state == UNPRESSED; 
            }
        }

        void loopStateMachine() {
            byte newReading = !digitalRead(_pin); // invert logic for pullup 
// if previous state was unpressed and new state is short press, throw flag
int prevState = _state;

            switch (_state) {
                case UNPRESSED:
                    if (newReading != _lastReading) {
                        _tPrevious_ms = millis();
                        _lastReading = newReading;
                        mySerial.sendln("Debouncing...");
                    }
                    else if (newReading && (millis() - _tPrevious_ms > _tDebounce_ms)) {
                        _state = SHORT_PRESS;
                        mySerial.sendln("Changed state to Short Press...");
// throw has changed flag here
                    } 
                    break;
                case SHORT_PRESS:
                    mySerial.sendln("Short Press...");
                    if (!newReading) {
                        _state = UNPRESSED; // immmediately latch to unpressed
                    } else if (millis() - _tPrevious_ms > _tLongPress_ms) {
                        _state = LONG_PRESS; // increment state
                        mySerial.sendln("Changed state to Long Press...");
                    } 
                    break;
                case LONG_PRESS:
                    mySerial.sendln("Long Press...");
                    if (!newReading) {
                        _state = UNPRESSED;  
                    }
                    break;
            }

if (prevState == 0 and _state == 1) _wasChanged = 1;
else if (prevState == 1 and _state == 2) _wasChanged = 2;
else _wasChanged = 0;
        }

        void reset() {
            // sets _state back to Unpressed so we can use button.isPressed(); only on an edge change
            _state = UNPRESSED;
        }

        byte getState() {
            return _state;
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
    button.loopStateMachine();

    if (button.getState() > 0) {
        led.toggle();
        button.reset(); // set the button state back to unpressed since we have previously toggled the led
    }
}
