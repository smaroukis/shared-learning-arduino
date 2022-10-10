// Description: Continuously prints the distance measured 
// by an ultrasonic sensor to the Serial Monitor
// hardware from elegoo Mega Ultimate Starter Kit Lesson 10

#include "SR04.h"

// Pins
const int TRIGGER = 12;
const int ECHO = 11;

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
