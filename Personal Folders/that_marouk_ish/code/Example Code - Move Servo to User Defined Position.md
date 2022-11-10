#code 
garden-topic::[Serial Communication](../../../Serial%20Communication.md), [Servos](../../../Servos.md)

> Takes an integer input from the Serial Monitor and moves the servo to that position.
> Anything more than 3 digits will be truncated. 
> Serial code from [tmi12 Serial Input Basics](../tmi12%20Serial%20Input%20Basics.md)

```c
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int position = 90;

boolean newData = false;
char endMarker = '\n';
char rc;
byte i = 0;
const byte numChars = 4; // we can only store 3 digits
char receivedChars[numChars];

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("Starting Monitor...");
}

void readData() {

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read(); 

    if (rc != endMarker) {
      receivedChars[i] = rc;
      i++;

      if (i >= numChars) {
        i = numChars - 1;
      }
    }
    else {
      receivedChars[i] = '\0'; // then it is the end of the string so terminate it
      i = 0;
      newData = true;
    }
  }
}

void moveServo() {
  if (newData == true) {
    position = atoi(receivedChars);
    Serial.print("Moving servo to position = ");
    Serial.println(position);
    myservo.write(position);
    newData = false;
  }
}

void loop() {
  readData();    
  moveServo();
}
```

Improvements
- the position data is only valid between `0-180` so we could store this in one byte instead of an array of 3 chars (=  4 bytes)
- 