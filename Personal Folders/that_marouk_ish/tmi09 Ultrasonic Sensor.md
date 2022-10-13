parent::[tmi Examples](Personal%20Folders/that_marouk_ish/tmi%20Examples.md)
previous:: [tmi08 Micro Servo](Personal%20Folders/that_marouk_ish/tmi08%20Micro%20Servo.md)
next:: [tmi10 Matrix Keypad](tmi10%20Matrix%20Keypad.md)
level:: #beginner
garden-topic:: [Ultrasonic Sensor](../../Ultrasonic%20Sensor.md)

>  (source)

Desired Goal:
- 

Concepts:

[Ultrasonic Sensor](Ultrasonic%20Sensor.md) -

Physical Setup:

The sensor is connected directly to the Arduino as follows:
- 5V <- VCC
- GND <- GND
- 12 <- Trigger
- 13 <- Echo

Code:

``` c
// Description: Continuously prints the distance measured 
// by an ultrasonic sensor to the Serial Monitor
// hardware from elegoo Mega Ultimate Starter Kit Lesson 10

// Pins
const int TRIGGER = 12;
const int ECHO = 11;


// ----- 09A Without Library ------
long duration, cm;

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
  duration = pulseIn(ECHO, HIGH); // builtin Arduino function; returns microseconds
 // try to do this without pulseIn since it is blocking

  // Microseconds to Distance Formula:
  // distance = 1/2 * (duration * k_speed-of-sound-in-air)
  // k = 343 m/s (at T=20C) = 0.0343 cm/us
  cm = (duration/2) * 0.0343;

  Serial.print(cm);
  Serial.println(" cm");
  delay(250);
}

// ----- 09B Using SR04 Library ------
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

// ----- 09C With NewPing Library ------
#include <NewPing.h>
const int MAX_DISTANCE = 200;

NewPing sonar(TRIGGER, ECHO, MAX_DISTANCE);

void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(1000);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println("cm");
}

```

Improvements:
- use the [NewPing](https://www.arduino.cc/reference/en/libraries/newping/) library which adds improvements
- try to implement without `pulseIn()` since it is blocking, using pin interrupts instead

Resources
- HC-SR04 datasheet ([sparkfun](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf))
- https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/