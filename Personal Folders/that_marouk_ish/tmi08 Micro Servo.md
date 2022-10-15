parent::[tmi Examples](../../../tmi%20Examples.md)
previous:: [tmi07 Buzzers](./tmi07%20Buzzers.md)
next:: [tmi09 Ultrasonic Sensor](tmi09%20Ultrasonic%20Sensor.md)
garden-topic:: [Servos](../../Servos.md)
level:: #beginner

>  Inspired by Elegoo Ultimate Starter Kit Lesson 9

Desired Goal:
- Uses the `Servo` library to drive a small servo motor. The library can be downloaded from Library Manager in the Arduino IDE or is included in the `code/` files in this repo. 

Concepts:
- Using the Library Manager
- [Servos](../../Servos.md)
- 

Physical Setup:

> Using a small SG90 servo motor from the Elegoo kit. It is light weight so it doesn't need a transistor to drive it, and it can be connected directly to 5V. 

- The motor (+) lead is connected directly to 5V on the Arduino and (-) to ground. The motor is driven by an Arduino PWM output pin to the `pulse` pin on the motor.

![](attachments/Pasted%20image%2020221007173416.png)

Code:


``` c
// Description: Driving a small servor motor directly from 5V, using Servo library
// Servo is supplied 5V and driven by PWM on Pin 7 (see datasheet for details)

const int SERVO_PIN = 7;

#include <Servo.h>
Servo myservo; // create Servo object 

void setup(){
  myservo.attach(SERVO_PIN);

  myservo.write(0);// move servos to center position -> 90°
  delay(500);
  myservo.write(45);// move servos to center position -> 60°
  delay(500);
  myservo.write(90);// move servos to center position -> 90°
  delay(500);
  myservo.write(135);// move servos to center position -> 120°
  delay(500);
  myservo.write(180);// move servos to center position -> 120°
  delay(500);
}
 
void loop(){
}
```

Improvements:
- use a potentiometer to control the position (see the built in Arduino sketch)

Resources
- https://www.arduino.cc/reference/en/libraries/servo/
- https://docs.arduino.cc/tutorials/generic/basic-servo-control