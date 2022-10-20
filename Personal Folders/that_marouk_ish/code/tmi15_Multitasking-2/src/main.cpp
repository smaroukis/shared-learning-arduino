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
    // could implement this without the "state" variable
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
            hardOff();
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

        void blink() {
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

        int getState() {
            return state;
        }
}; 

class ServoCustom {
    // here we attach a button, better OOP would be to create a higher order class
    // so we can control it with non-button peripherals
    private:
        Servo _servo;
        byte pin; 
        const unsigned long tDelay;
        byte pos; // pos in [0, 180]
        int delta_pos; // {-1, 1}
        unsigned long tPrevious;
        boolean state; // stopped = 0, started = 1

    public:
        ServoCustom(byte attachPin) :
            pin(attachPin) {}

        void setup() {
            _servo.attach(pin); 
            delta_pos = 1;
            state = 0;
        }

        void loop() {
            // keep all the timing in here unless we access from the outside
            if (state && (millis() - tPrevious >= tDelay)){
                moveOneStep();
                tPrevious = millis();
            }
        }

        void moveOneStep() {
            // move the servo one setp
            _servo.write(pos);
            pos += delta_pos;

            if (pos == 180 || pos == 0) delta_pos = -delta_pos; 
            // previously we updated the LCD here but now we do that from a controller
        }

        boolean isStarted() { return state;}

        void start() { state = 1; } // accessed by controllers

        void stop() { state = 0; }

        void toggle() { state = !state; }

        byte getPos() { return pos; }
};

// demonstrates how to pass by reference other objects to a controller
// having a controller class helps us see what uses what
class Controller {
    Led &led;
    Button &button;
    ServoCustom &servo;

    public:
        Controller(Led &attachLed, Button &attachButton, ServoCustom &servoAttach) :
            led(attachLed),
            button(attachButton),
            servo(servoAttach) {}

        loop() {
            led.blink();
            button.loop();
            servo.loop();

            // when the button is pressed, change the state of the servo
            if (button.getState() == PRESSED) {
                servo.toggle(); // servo will handle the move during loop
            }

            // update the blink rate to be proportional to the servo position
            ledBlinkRate = map(servo.getPos(), 0, 180, 50, 1000);
            led.updateOffRate(ledBlinkRate);
        }
};

// make objects
Led led(LED_PIN, LED_ON_DELAY, LED_OFF_DELAY);
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY);
ServoCustom servo(SERVO_PIN);
Controller controller(led, button, servo);

void setup () {
    // hardware dependencies
    led.setup();
    button.setup();
    servo.setup();
}

void loop() {
    controller.loop();
}