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
