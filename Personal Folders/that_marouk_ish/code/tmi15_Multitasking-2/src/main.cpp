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

class Led
{
    private:
        const byte PIN;
        long tDelayOn; // to check when turning OFF
            // i.e. the minimum time we want to stay on
        long tDelayOff; // to check when turning ON

        byte state;
        unsigned long tPrevious; 

    // constructor
    public:
        Led(const byte pin, long on, long off) : 
            PIN(pin),
            tDelayOn(on),
            tDelayOff(off)  {}

        void setup() { 
            pinMode(PIN, OUTPUT);
            harddOff();
        }

        void hardOff() {
            // note this does not handle timing - "hard"
            digitalWrite(PIN, LOW);
            state = 0;
        }

        void hardOn() {
            digitalWrite(PIN, HIGH);
            state = 1;
        }

        void off() {
            if(millis() - tPrevious >= tDelayOff) {
                tPrevious = millis();
                hardOff();
            }
        }

        void on() {
            if (millis() - tPrevious >= tDelayOn) {
                tPrevious = millis();
                hardOn();
            }
        }

        void toggleState() {
            if (state == 1) { off(); }
            else if (state == 0) { on(); }
        }

        void updateOffRate(unsigned long newRate) {
            tDelayOff = newRate;
        }
}; // don't forget semicolo/

class Button {
    const byte PIN;
    long tDelayPressed; // better: add ms suffix
    unsigned long tPrevious; 
    byte lastReading;
    enum state {
        UNPRESSED,
        PRESSED
    };

    public: 
        Button(byte pin, unsigned long delay_pressed) : 
            PIN(pin),
            tDelayPressed(delay_pressed) {}

        void setup() { 
            pinMode(PIN, INPUT_PULLUP);
            digitalWrite(PIN, HIGH);
            state = UNPRESSED; 
            lastReading = 1; // for  PULLUP
        }

        void loop() {
            // updates state machine if button press
            // handles debouncing
            byte newReading = digitalRead(PIN);

            if (newReading != lastReading) {
                tPrevious = millis(); // start timer
                lastReading = newReading;
            }
            else if (millis() - tPrevious >= tDelayPressed) {
                // store the state, note pullup;
                if (newReading == HIGH) {
                    state == UNPRESSED; 
                    }
                else if (newReading == LOW) { 
                    state == PRESSED; 
                    }
            }
        }
}; 

class ServoControllerWithButton {
    // here we attach a button, better OOP would be to create a higher order class
    // so we can control it with non-button peripherals
    Servo myServo;
    Button &button;
    boolean isStarted;
    byte pin; 
    const unsigned long tDelay;
    byte pos; // pos in [0, 180]
    int delta_pos = 1; // {-1, 1}
    unsigned long tPrevious;

    public:
        ServoControllerWithButton(byte attachPin, byte &attachButton) :
            pin(attachPin),
            button(attachButton) {}

        setup() {
            myServo.attach(pin); 
        }

        loop() {
            // checks for a button press
            // and moves the servo / updates the  state/isStarted variable
            // to be used by others
        }

        moveOneStep() {
            // move the servo one setp
        }

        // the LCD controller can look at ServoControllerWithButton.isStarted
}


// class LedController {
//     private:
//         Led &led;  //  passing by reference allows us to access the led object, without creating the whole object inside
//         Button &button; 

//     public:
//         LedController(Led &attachToLed, Button &attachToButton) :
//             led(attachToLed),
//             button(attachToButton) {}
        
//         loop() {
//         // this loop turns on and off the led
//         // and checks to see if the servo pos has changed
//         // to update the blink ratee
//         }
// }; 

// // Servo - later TODO - inherit class
// Servo myServo;
// boolean servoStarted = false;
// int pos = 0;
// int delta_pos = 1;
// unsigned long tPreviousServo = 0;
// unsigned long tDelayServo = 0;

// // LCD
// LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
// unsigned long tPreviousLcd = 0;
// unsigned long tDelayLcd = 80;


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
Led led(LED_PIN, LED_ON_DELAY, LED_OFF_DELAY);
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY);
ServoController myServoControllerWithButton(SERVO_PIN, button); // or do we pass a reference?
// here
LedController ledController(led, button);

void setup () {
    // hardware dependencies
    led.setup();
    button.setup();
    
    // here  
    // For Testing
    pinMode(LED_PIN, OUTPUT);
    
}

void loop() {

    button.loop();
         // this button state machine handles debouncing
         // changes state when button is pressed 

    // here
    servoStateMachine.loop();
        // pass the button object to the servoStateMachine
        // this loop checks for a button press
        // and moves the servo depending on state

    ledController.loop();
        // pass the servoStateMachineObject to the ledController
        // this loop turns on and off the led
        // and checks to see if the servo pos has changed
        // to update the blink rate

    lcdController.loop();
        // pass the servoStateMachineObject to the lcdController
        // this loop updates the lcd screen
        // and looks at the state of the servoStateMachine

}