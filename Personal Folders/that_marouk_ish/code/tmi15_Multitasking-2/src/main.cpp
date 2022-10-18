// Continued from Multitasking-1
// Here we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define DEFAULT_OFF_DELAY 50

#define BUTTON_PIN 2
#define BUTTON_DEBOUNCE_DELAY 30

#define LED_PIN 4
#define LED_ON_DELAY 10 // to check when turning off 
#define LED_OFF_DELAY 5 // note this becomes variable in the updateBlinkRate() function

#define SERVO_PIN 3
const int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7; // LCD pins



// Servo - later TODO - inherit class
Servo myServo;
boolean servoStarted = false;
int pos = 0;
int delta_pos = 1;
unsigned long tPreviousServo = 0;
unsigned long tDelayServo = 0;

// LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
unsigned long tPreviousLcd = 0;
unsigned long tDelayLcd = 80;

// Main Shared Class

class Led
{
    private:
        int PIN;
        long tDelayOn; // to check when turning OFF
        long tDelayOff; // to check when turning ON

        int statePrevious;
        unsigned long tPrevious; 

    // constructor
    public:
        Led(int pin, unsigned long on, unsigned long off) : 
            PIN(pin), tDelayOn(on), tDelayOff(off) {}

        void setup() { 
            pinMode(PIN, OUTPUT);
            digitalWrite(PIN, LOW);
        }

        void toggleState() {
            if (millis() - tPrevious >= tDelayOn) {
                tPrevious = millis();
                digitalWrite(PIN, !digitalRead(PIN));
            }
        }

        void toggleStateAdvanced() {
            // if ON: turns Off if tDelayOn has elapsed
            // if OFF: turns ON if tDelayOff has elapsed
            // non-inverted logic

            if (state == 1 && (millis() - tPrevious >= tDelayOn)) {
                state = 0;
                tPrevious = millis();
                digitalWrite(PIN, state); // write LOW
            }
            else if (state == 0 && (millis() - tPrevious >= tDelayOff)) {
                state = 1;
                tPrevious = millis();
                digitalWrite(PIN, state); // write HIGH
            }
            else {
                return; // so we don't change the statePrevious value
            }
            statePrevious = !state;
        }

        void updateBlinkRate(unsigned long newRate) {
            tDelayOff = newRate;
        }

    // TODO: add mapping function for analog write
}; // don't forget semicolo/

class Button {
    const byte PIN;
    long tDelayPressed; // better: add ms suffix
    unsigned long tPrevious; 
    int state;

    public: 
        Button(byte pin, unsigned long delay_pressed) : 
            PIN(pin),
            tDelayPressed(delay_pressed) {}

        void setup() { 
            pinMode(PIN, INPUT_PULLUP);
            digitalWrite(PIN, HIGH);
            state = 1; // normal HIGH for INPUT_PULLUP
        }

        void loop() {
            int statePrevious = state;
            state = digitalRead(PIN);
            if (statePrevious == HIGH && state == LOW) {
                // button is pressed (input_pullup)
                tPrevious = millis();
                statePrevious = state;
            }
            else if (statePrevious == LOW && state == HIGH) {
                // button has been released
                if (millis() - tPrevious < tDelayPressed) {
                    // reserved for later use
                    return;
                }
                else if (millis() - tPrevious >= tDelayPressed) {
                    // Testing only
                    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                }
            }
        }
}; 

class LedController {
    const byte pin;


}

// class MyServo : Peripheral {
//     int pos;
//     int delta_pos; 

//     // Need to extend the 
//     public:
//     MyServo(int pin, long delay) {
//         PIN = pin;
//         tDelay = delay;
//         state = 0
//         pos = 0;
//         delta_pos = 1; // {1, -1}
//         tPrevious = 0;
//     }

//     void moveOneStep() {
//         // TODO
//     }
// }

// make objects
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY);
Led led(LED_PIN, LED_ON_DELAY, LED_OFF_DELAY);

void setup () {
    // hardware dependencies
    button.setup();
    
    // For Testing
    pinMode(LED_PIN, OUTPUT);
    
}

void loop() {
    // First, simply toggle a led with a pushbutton

    button.loop();
}