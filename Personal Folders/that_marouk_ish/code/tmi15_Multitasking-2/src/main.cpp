// Continued from Multitasking-1
// Here we add in an LCD screen
// and start to use OOP

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// Pins
const byte PIN_SERVO1 = 3; // SIGNAL (byte [0, 255])
const int BUTTON = 2; // Button (will be normal HIGH)
const int RED = 4;
const int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7; // LCD pins

// Variables
unsigned long tNow; // for each time through the loop

// LED
unsigned long tLedDelayRising = 5;
const int tLedDelayFalling = 10;
unsigned long tPreviousLed = 0; 

// Servo Object and Variables
Servo thisServo; 
boolean thisServoStarted = false; // state machine variable
int pos = 0; // store position
int delta_pos = 1; // {1, -1}
unsigned long tPreviousStep = 0;
unsigned long tDelay = 20; // instead of constant, it will be set by the motor position

// Button and Debouncing
unsigned long tDebounceStart; // to store time for debouncing algo
const int tDebounceDelay = 30;
boolean debouncing = false;
int buttonState = 0; 
int buttonPreviousState = 1; // button is INPUT_PULLUP so normal is HIGH, active LOW
  
// LCD 
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
unsigned long tPreviousStepLcd = 0;
unsigned long tDelayLcd = 500; // lcd update should be slower


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(BUTTON, HIGH); // to avoid ambiguity
  digitalWrite(RED, LOW);

  thisServo.attach(PIN_SERVO1);
  Serial.begin(9600);
  Serial.println("Starting Serial Monitor ...");

  lcd.begin(16, 2);
  lcd.print("Servo at pos:");
}

void updateLED() {
  // flash the LED at a speed relative to the motors position
  // this will demonstrate "loops within loops" for multitasking purposes
  // keep flashing if button is unpressed
  if (thisServoStarted) tLedDelayRising = map(pos, 0, 180, 50, 1000);

  if ((tNow - tPreviousLed >= tLedDelayRising)) {
    tPreviousLed = tNow; 
    digitalWrite(RED, HIGH);

  } else if (tNow - tPreviousLed >= tLedDelayFalling) {
    digitalWrite(RED, LOW); // need to add a falling timer so that we can light up brighter on time offs
  }
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
    Serial.print("Moved Servo to position = ");
    Serial.println(pos);

    if (pos == 180 || pos == 0) delta_pos = -delta_pos; 
    // update timer
    tPreviousStep = tNow; 
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
    tDebounceStart = tNow;
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

void updateLcd() {
  // requres: tPreviousStepLcd, tDelayLcd, thisServoStarted
  // needs its own timing to avoid flicker - 
  // could also use previous servo state to only change on an edge

  if(thisServoStarted && (tNow - tPreviousStepLcd >= tDelayLcd)) {
    lcd.clear(); // also returns the cursor to top left
    lcd.print("Servo is running, position is:");
    updateLcdPos();
    tPreviousStepLcd = tNow;

  } else if (!thisServoStarted && (tNow - tPreviousStepLcd >= tDelayLcd)) {
    lcd.clear();
    lcd.print("Servo is stopped at position:");
    updateLcdPos();
    tPreviousStepLcd = tNow;
  }
}

void updateLcdPos() {
  lcd.setCursor(0, 1);
  lcd.print(pos);
}

// Loop
void loop() {
  tNow = millis(); 

  checkButton(); // 
  moveServoOneStep(); 
  updateLED();
  updateLcd();
}