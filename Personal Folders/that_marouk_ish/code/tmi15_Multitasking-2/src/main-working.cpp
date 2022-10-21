
#include <Arduino.h>

#define DEFAULT_OFF_DELAY 50

#define BUTTON_PIN 2
#define BUTTON_DEBOUNCE_DELAY 50

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
        boolean state;

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
    const byte PIN;
    long tDelayDebounce; // better: add ms suffix
    unsigned long tPrevious; 
    byte lastReading;

    enum States {
        UNPRESSED = 0,
        PRESSED = 1
    } state;

    public: 
        Button(byte pin, unsigned long delay_short, HasSerial &serialAttach) : 
            PIN(pin),
            tDelayDebounce(delay_short),
            mySerial(serialAttach) {
            }

        void setup() { 
            pinMode(PIN, INPUT_PULLUP);
            digitalWrite(PIN, HIGH);
            state = UNPRESSED; 
            lastReading = 0; // 0 == unpressed (non-inverted logic)
        }

        void loop() {
            byte newReading = !digitalRead(PIN); // invert logic for pullup 

            if (newReading != lastReading) {
                tPrevious = millis(); // start timer
                lastReading = newReading; // lastReading persists
                // state = DEBOUNCING; FUTURE use
                mySerial.sendln("Debouncing started..");
            } else if (millis() - tPrevious >= tDelayDebounce) {
                // last reading must == new reading
                if (newReading == 0) {
                    state = UNPRESSED; 
                    mySerial.sendln("Updated Button to Unpressed..");
                    }
                else if (newReading == 1) { 
                    state = PRESSED; 
                    mySerial.sendln("Updated Button to Pressed..");
                    }
                tPrevious = millis(); // reset timer
            }
        }

        boolean getState() {
            return state;
        }
}; 

HasSerial serialInstance(&Serial);
Led led(LED_PIN, LED_MIN_ON_DELAY, LED_MIN_OFF_DELAY, serialInstance);
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY, serialInstance);

void setup() {
    led.setup();
    button.setup();
    Serial.begin(9600);
    Serial.println("Hello..");
}

void loop() {

    // Testing Only
    button.loop();

    if (button.getState() == 1) {
        led.toggle();
    }
}