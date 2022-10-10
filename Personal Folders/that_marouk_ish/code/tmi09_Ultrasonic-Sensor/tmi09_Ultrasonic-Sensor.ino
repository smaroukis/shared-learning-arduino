// Description: Continuously prints the distance measured 
// by an ultrasonic sensor to the Serial Monitor
// hardware from elegoo Mega Ultimate Starter Kit Lesson 10

// Pins
const int TRIGGER = 12;
const int ECHO = 11;

// ----- Using SR04 Library ------
/* 
#include "SR04.h"

// Constants
long a;

// Other Variables
SR04 sr04 = SR04(ECHO, TRIGGER);

void setup() {
  Serial.begin(9600);
  delay(1000);

}

void loop() {
  a = sr04.Distance();
  Serial.print(a);
  Serial.println(" cm");
  delay(1000);
}
*/

// ----- Wihtout Library ------
long duration, cm, inches; 

void setup(){
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop(){
  // Trigger the sensor by a HIGH pulse of >10us -- note MICROseconds
  digitalWrite(TRIGGER, LOW); // write LOW first for a clean HIGH pulse
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW); 

  // Read the signal from the ECHO pin
  // pinMode(ECHO, INPUT); // commented out 
  duration = pulseIn(ECHO, HIGH); // using a builtin Arduino function

  // Microseconds to Distance Formula:
  // distance = 1/2 * (duration * k_speed-of-sound-in-air)
  // k = 343 m/s (at T=20C)

}
