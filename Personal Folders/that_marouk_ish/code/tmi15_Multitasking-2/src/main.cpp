// Continued from Multitasking-1
// we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>

#define DEFAULT_OFF_DELAY 50

#define BUTTON_PIN 2
#define BUTTON_DEBOUNCE_DELAY 50

#define LED_PIN 4
#define LED_MIN_ON_DELAY 500 
#define LED_MIN_OFF_DELAY 1000

#define SERVO_PIN 3

//// LED CLASS
// -----
// -----
// ------


// BUTTON CLASS
/// --------------
// ------------
// ------------


class ServoCustom {
    // we attach a button, better OOP would be to create a higher order class
    // so we can control it with non-button peripherals
    private:
        Servo _servo;
        byte PIN; 
        const unsigned long tDelay;
        byte pos; // pos in [0, 180]
        int delta_pos; // {-1, 1}
        unsigned long tPrevious;
        boolean state; // stopped = 0, started = 1

    public:
        ServoCustom(byte attachPin) :
            PIN(attachPin) {}

        void setup() {
            _servo.attach(PIN); 
            delta_pos = 1;
            state = 0;
        }

        void loop() {
            // keep all the timing in unless we access from the outside
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
            // previously we updated the LCD but now we do that from a controller
        }

        boolean isStarted() { return state;}

        void start() { state = 1; } // accessed by controllers

        void stop() { state = 0; }

        void toggle() { state = !state; }

        byte getPos() { return pos; }
};

// demonstrates how to pass by reference other objects to a controller
// having a controller class helps us see what uses what
// class Controller {
//     Led &led;
//     Button &button;
//     ServoCustom &servo;

//     public:
//         Controller(Led &attachLed, Button &attachButton, ServoCustom &servoAttach) :
//             led(attachLed),
//             button(attachButton),
//             servo(servoAttach) {}

//         loop() {
//             led.blink();
//             button.loop();
//             servo.loop();

//             // when the button is pressed, change the state of the servo
//             // note _non_ inverted logic - 
//             if (button.getState() == 1) {
//                 servo.toggle(); // servo will handle the move during loop
//             }

//             // update the blink rate to be proportional to the servo position
//             int ledBlinkRate = map(servo.getPos(), 0, 180, 50, 1000);
//             led.updateOffRate(ledBlinkRate);
//         }
// };



// make objects
Led led(LED_PIN, LED_MIN_ON_DELAY, LED_MIN_OFF_DELAY);
Button button(BUTTON_PIN, BUTTON_DEBOUNCE_DELAY);
ServoCustom servo(SERVO_PIN);
// Controller controller(led, button, servo);

void setup () {
    // hardware dependencies
    led.setup();
    button.setup();
    servo.setup();

    Serial.begin(9600);
    Serial.println("Starting Monitor");
}

void loop() {
    // button.loop();
    // led.update();
    // servo.loop();

    // // update the blink rate to be proportional to the servo position
    // int ledBlinkRate = map(servo.getPos(), 0, 180, 50, 1000);
    // led.updateOffRate(ledBlinkRate)

}