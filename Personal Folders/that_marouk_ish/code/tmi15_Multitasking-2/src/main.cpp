// Continued from Multitasking-1
// Here we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>


// Main Shared Class

class Led
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
        int state; // needs to be callable from outside

    // constructor
    public:
    Led(int pin, unsigned long on, unsigned long off)
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

    void updateBlinkRate(unsigned long newRate) {
        tDelayOff = newRate;
    }

    // TODO: add mapping function for analog write
}; // don't forget semicolon

class Button {
    private:
        int PIN;
        long tDelayOn; // to check when turning OFF
        long tDelayOff; // to check when turning ON

        unsigned long tPrevious; 
        int statePrevious;
        boolean debouncing;

    public:
        int state;

    Button(int pin, unsigned long delay_pressed, unsigned long delay_unpressed)
    { 
        PIN = pin;
        tDelayPressed = delay_pressed; // debounce delay
        tDelayUnpressed = delay_unpressed;
        
        state = 0;
        statePrevious = 0;
        tPrevious = 0; 

        debouncing = false;
    }

    int checkState() {
        return state;
    }

    void initAsInputPullup() { 
        pinMode(PIN, INPUT_PULLUP);
        digitalWrite(PIN, HIGH);
     }

    void checkButton() { // INPUT_PULLUP has inverted logic
        tNow = millis();    
        state = digitalRead(PIN);

        if (state == LOW && statePrevious == HIGH) {
            tPrevious = 0;
            statePrevious = state;
            debouncing = true; 
        } 
            else if (debouncing && state = 0 && (tNow - tPrevious >= tDelayPressed)) {
            // TODO here is where we updated the motor state previously
            debouncing = false;
        }
    }
}; 

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


// Moves these to header
unsigned long tNow; // for each time through the loop

#define DEFAULT_OFF_DELAY 50;

#define BUTTON_PIN 2;
#define BUTTON_DEBOUNCE_DELAY 30;

#define LED_PIN 4;
#define LED_ON_DELAY 10; // to check when turning off 
#define LED_OFF_DELAY 5; // note this becomes variable in the updateBlinkRate() function

#define SERVO_PIN 3;
const int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7; // LCD pins


// make objects
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY, DEFAULT_OFF_DELAY);
Led led(LED_PIN, LED_ON_DELAY, LED_OFF_DELAY);

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

void updateLcd() {

}

void printLcdPos() {

}

void checkLcdPos() {

}


void setup () {
    // hardware dependencies
    button.initAsInputPullup();
    led.initAsOutput();

    myServo.attach(SERVO_PIN);
    lcd.begin(16, 2);
    updateLcd();

    Serial.begin(9600);
    Serial.println("Starting Serial Monitor...")
    
}

void loop() {
    // First, simply toggle a led with a pushbutton

    // check button for press
    button.checkButton();
    // update led 
        
}