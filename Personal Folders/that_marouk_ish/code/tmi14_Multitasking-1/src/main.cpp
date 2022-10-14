// Learning Objective: Demonstrate multitasking capabilities with non-blocking functions
// (without using OOP paradigm)
// Move a servo motor back in forth while changing the hue of an RGB LED and
// waiting for a pushbutton press to stop motor movement
// LED should stay at the current color


#include <Arduino.h>
#include <Servo.h>

// Pins
const byte PIN_SERVO1 = 9; // 9 <- SIGNAL (byte [0, 255])

// Constants

// Variables
unsigned long tNow; // for each time through the loop

// Objects and Their Variables (before OOP)
Servo thisServo; 
boolean thisServoStarted = 0; // state machine variable
int pos = 0; // store position
int delta_pos = 1; // {1, -1}
unsigned long tPreviousStep = 0;
const int tDelay = 10; // used to control the "speed" of the motor

void setup() {
// Setup the Servos
thisServo.attach(PIN_SERVO1);

}

// The beginning of the "state machine"
void servoStart() {
  // Set state
  thisServoStarted = true;
}

// Start the Servo Rotating - reverse directions when we get to the end;
void moveServoOneStep() {
// first check if we should actually move one step
// two conditions: 1) we are started and 2) the time condition has been met
  if (thisServoStarted && (tNow - tPreviousStep >= tDelay)) {
    // ok now we can move one step only
    pos += delta_pos; // increment the position to write new position
    thisServo.write(pos); 

    // if pos =180 or 0 we need to reverse the delta_pos variable
    if (pos == 180 || pos == 0) delta_pos = -delta_pos; 

    // update timer
    tPreviousStep = tNow; // #q - or should we use `millis()` function again? 

  }

}

void servoStop() {
  thisServoStarted = false;
  tPreviousStep = tNow; 
}

// Loop
void loop() {
  tNow = millis(); 

  servoStart();
  moveServoOneStep();
  servoStop();
}