// Description:

// Constants
const int LED = 9;
const int analogPin = A0;

// Inputs
unsigned int val = 0; // analog input read value

// Other Variables

void setup() {
  pinMode(analogPin, INPUT); //analog pins are INPUT by default, but explicit here
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(analogPin);
  analogWrite(LED, val/4); // since analogRead() is 16 bit but analogWrite is 8 bit ()
  delay(10);
}
