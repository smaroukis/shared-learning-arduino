// Continued from Multitasking-1
// Here we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>


// Main Shared Class

class Peripheral
{
    private:
        // constants
        int PIN;
        long tDelayOn; // to check when turning OFF
        long tDelayOff; // to check when turning ON

        // variable
        int statePrevious;
        unsigned long tPrevious; 
    
    public:
        // better OOP keeps these private but requires more functions
        int state;

    // constructor
    public:
    Peripheral(int pin, unsigned long on, unsigned long off)
    { 
        PIN = pin;
        tDelayOn = on;
        tDelayOff = off;
        
        state = 0;
        statePrevious = 0;
        tPrevious = 0; 
    }

    void initAsOutput() { 
        pinMode(PIN, OUTPUT); // call these in setup, not in the constructor
        digitalWrite(PIN, LOW);
     }

    void initAsInputPullup() { 
        pinMode(PIN, INPUT_PULLUP);
        digitalWrite(PIN, HIGH);
     }

    // main function
    void toggleState() {
        // if ON: turns Off if tDelayOn has elapsed
        // if OFF: turns ON if tDelayOff has elapsed
        // non-inverted logic
        unsigned long tNow = millis();

        if (state == 1 && (tNow - tPrevious >= tDelayOn)) {
            state = 0;
            tPrevious = tNow;
            digitalWrite(PIN, state); // write LOW
        }
        else if (state == 0 && (tNow - tPrevious >= tDelayOff)) {
            state = 1;
            tPrevious = tNow;
            digitalWrite(PIN, state); // write HIGH
        }
        else {
            return; // so we don't change the statePrevious value
        }
        statePrevious = !state;
    }

    // TODO: add mapping function for analog write
}; // don't forget semicolon

class Led : Peripheral {
// needs a function to change the on delay so we can control the blinking speed

    public:
    Led(int pin, unsigned long on, unsigned long off) : Peripheral(pin, on, off) {
        // "no new friends"
    }

    void updateBlinkRate(unsigned long newRate) {
        tDelayOff = newRate;
    }
}; 

class Button : Peripheral {
    // Button class extended member variables
    private:
        boolean debouncing = false; 
    
    public: 
    Button(int pin, unsigned long on, unsigned long off) : Peripheral(pin, on, off) {
        // "no new friends" i.e. no new member variables
    }
        
    void checkButton() { // INPUT_PULLUP has inverted logic
        tNow = millis();    
        state = digitalRead(PIN);

        if (state != statePrevious) {
            tPrevious = 0;
            statePrevious = state;
            debouncing = true; 
            Serial.println("Started Debouncing...");
        } 
            else if (debouncing && state = 0 && (tNow - tPrevious >= tDelay)) {
            // TODO here is where we updated the motor state previously
            debouncing = false;
            Serial.println("Debouncing Finished, Button is Pressed");
        }
    }
}

class MyServo : Peripheral {
    int pos;
    int delta_pos; 

    // Need to extend the 
    public:
    MyServo(int pin, long delay) {
        PIN = pin;
        tDelay = delay;
        state = 0
        pos = 0;
        delta_pos = 1; // {1, -1}
        tPrevious = 0;
    }

    void moveOneStep() {
        // TODO
    }

}

// LCD extended class
// many more pins

// Servo extended class
// + pos, delta_pos

// Moves these to header
#define DEFAULT_OFF_DELAY 50;

#define BUTTON_PIN 2;
#define BUTTON_DEBOUNCE_DELAY 30;

#define LED_PIN 4;
#define LED_ON_DELAY 10; // to check when turning off 
#define LED_OFF_DELAY 5; // note this becomes variable in the updateBlinkRate() function

#define SERVO_PIN 3;


// make objects
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY, DEFAULT_OFF_DELAY);
Led led(LED_PIN, LED_ON_DELAY, LED_OFF_DELAY);


void setup () {
    // hardware dependencies
    button.initAsInputPullup();
    led.initAsOutput();

    // not sure how to handle Servo class with my own, so I'll leave it as is
    thisServo.attach(SERVO_PIN);

    // lcd 


}

void loop() {
        
}