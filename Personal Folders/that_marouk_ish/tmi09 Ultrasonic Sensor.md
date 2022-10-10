parent::[tmi Examples](Personal%20Folders/that_marouk_ish/tmi%20Examples.md)
previous:: [tmi08 Micro Servo](Personal%20Folders/that_marouk_ish/tmi08%20Micro%20Servo.md)
next::
level:: #beginner
garden-topic::

>  (source)

Desired Goal:
- 

Concepts:

Ultrasonic Sensor
- using the `HC-SR04` library
- a trigger pulse (HIGH) is sent to the module 
	- on the `TRIG` pin
- the module sends a pulse out and detects whether it gets a pulse back
- the module responds with a echo pulse to the user (arduino) circuit
	- on the `ECHO` pin
	- the pulse duration is in proportion to the distance away
- timing diagram is important

Physical Setup:
> The 


Code:


``` c
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

```

Improvements:

Resources
- HC-SR04 datasheet ([sparkfun](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf))
- https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
- 