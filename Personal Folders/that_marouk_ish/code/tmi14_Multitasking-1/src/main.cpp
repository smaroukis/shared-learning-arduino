// Learning Objective: Demonstrate multitasking capabilities with non-blocking functions
// (without using OOP paradigm)
// Move a servo motor back in forth while changing the hue of an RGB LED and
// waiting for a pushbutton press to stop motor movement
// LED should stay at the current color

#include <Arduino.h>
#include <Servo.h>

// Pins
const byte PIN_SERVO1 = 9; // 9 <- SIGNAL (byte [0, 255])
const int BUTTON = 2; // 11 <- Button (will be normal HIGH)
const int RED = 13;
const int GREEN = 13;
const int BLUE= 13;

// Variables
unsigned long tNow; // for each time through the loop

// LED
byte redVal = 0;
byte greenVal = 0;
byte blueVal = 0;

// Servo Object and Variables
Servo thisServo; 
boolean thisServoStarted = false; // state machine variable
int pos = 0; // store position
int delta_pos = 1; // {1, -1}
unsigned long tPreviousStep = 0;
const int tDelay = 10; // used to control the "speed" of the motor

// Button and Debouncing
unsigned long tDebounceStart; // to store time for debouncing algo
const int tDebounceDelay = 50;
boolean debouncing = false;
int buttonState = 0; 
int buttonPreviousState = 1; // button is INPUT_PULLUP so normal is HIGH, active LOW

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(BUTTON, HIGH); // to avoid ambiguity

  thisServo.attach(PIN_SERVO1);
  Serial.begin(9600);
}

void updateLED() {
  // when: when servo motor is updated
  // need access to the servo position
  // where pos in [0, 180] is mapped between [0, 255]
  redVal = 1.1389 * pos + 50;
  greenVal = -0.0253 * pos + 255;
  blueVal = 0.02531 * pos + 50;

  analogWrite(RED, redVal);
  analogWrite(GREEN, greenVal);
  analogWrite(BLUE, blueVal);

  // Serial.print("(red, green, blue = {");
  // Serial.print(redVal); Serial.print(", "); 
  // Serial.print(greenVal); Serial.print(", "); 
  // Serial.print(blueVal); 
  // Serial.println("}");
}

// The beginning of the "state machine"
void servoStart() {
  // Set state
  thisServoStarted = true;
  Serial.println("Started Servo");
//  tPreviousStep = tNow; // #q do we need this? -> I think we do, otherwise it starts instantaneously and jitters
}

// Start the Servo Rotating - reverse directions when we get to the end;
void moveServoOneStep() {
// first check if we should actually move one step
// two conditions: 1) we are started and 2) the time condition has been met
  if (thisServoStarted && (tNow - tPreviousStep >= tDelay)) {
    pos += delta_pos; // increment the position to write new position
    thisServo.write(pos); 
    updateLED();
    Serial.print("Moved Servo to position = ");
    Serial.println(pos);

    if (pos == 180 || pos == 0) delta_pos = -delta_pos; 
    // update timer
    tPreviousStep = tNow; // #q - or should we use `millis()` function again? s
  }
}

void servoStop() {
  thisServoStarted = false;
//  tPreviousStep = tNow; 
  Serial.println("Stopped Servo");
}

void servoChangeState() {
  Serial.print("Changing Servo state from (");
  Serial.print(thisServoStarted);
  Serial.println(")");
  switch (thisServoStarted) {
    case false:
      servoStart();
      break;
    case true:
      servoStop();
      break;
  }
}

void checkButton() {
  buttonState = digitalRead(BUTTON); // INPUT_PULLUP
  if (buttonState != buttonPreviousState) {
    tDebounceStart = tNow; // #q again, should this be tNow or millis()
    buttonPreviousState = buttonState; 
    debouncing = true;
    Serial.println("Started Debouncing...");
  }
  else if (debouncing && buttonState == 0 && (tNow - tDebounceStart >= tDebounceDelay)) {
    Serial.print("Debouncing finished, taking current state = ");
    Serial.println(buttonState);
    // stop or start the motor
    servoChangeState();
    // update the variables
    debouncing = false;
  }
}



// Loop
void loop() {
  tNow = millis(); 

  checkButton();
  moveServoOneStep(); // also updates LED
  }