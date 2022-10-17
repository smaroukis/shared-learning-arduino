// Continued from Multitasking-1
// Here we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>


// Main Shared Class

class Peripheral
{
    // constants
    int PIN;
    long tDelayOn; // also just update time delay
    long tDelayOff;

    // variable, maintain the current state
    int state;
    unsigned long tPrevious; 

    // constructor
    public:
    Peripheral(int pin, long on, long off)
    {
        PIN = pin;
        pinMode(PIN, OUTPUT);
        tDelayOn = on;
        tDelayOff = off;
        statePrevious = 0;
        state = 0;
        tPrevious = 0; 
    }

    // main function
    // update function is too difficult to combine
    void toggleState() {
        // only works for digital pins, non-inverted logic
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
        statePrevious = !state;
    }
}

class Button : public Peripheral {
   boolean debouncing = false;
    
    public: 
    Button(int pin, long on, long off)
    {
        PIN = pin;
        pinMode(PIN, INPUT_PULLUP); // change from parent class
        tDelayOn = on;
        tDelayOff = off;
        statePrevious = 0;
        state = 0;
        tPrevious = 0; 
    }
    void checkButton() {
        tNow = millis();    
        state = digitalRead(PIN);

        if (state != statePrevious) {
            tPrevious = 0;
            statePrevious = state;
            debouncing = true; 
        } 
            else if (debouncing && state = 0 && (tNow - tPrevious >= tDelayOn)) {
            // here is where we updated the motor state previously
            debouncing = false;
        }
    }
       
}

// LCD extended class
// many more pins

// Servo extended class
// + pos, delta_pos

// Button extended class
// has debouncing boolean

// Led extended class
// is basically the same

void setup () {

}

void loop() {
        
}