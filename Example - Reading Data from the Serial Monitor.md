parent::[[James A. Langbridge - Arduino Sketches]]
garden-topic:: [[Arduino Serial Monitor]], [[UART]]

## Example 1 - Basic Serial Monitor Usage

```cpp
char myName[] = {"Arduino"};
char userName[64];
char userAge[32];
int age;
int i;

void setup()
{
	// Configure the serial port:
	Serial.begin(9600);
	
	// Welcome the user
	Serial.println("Hello! What is your name?");
	
	//Wait for a few seconds, then read the serial buffer
	delay(10000);
	Serial.readBytes(userName, 64);
	
	//Say hello to the user
	Serial.print("Hello, ");
	Serial.print(userName);
	Serial.print(". My name is ");
	Serial.print(myName);
	Serial.print("\n");

   //Ask for user's age
   Serial.print("How old are you, ");
   Serial.print(userName);
   Serial.println("?");

   //Wait for a few seconds, then read the serial buffer
   delay(10000);
   age = Serial.parseInt();

   //Print out the user's age
   Serial.print("Oh, you are ");
   Serial.print(age);
   Serial.println("?");
   Serial.print("I am ");
   Serial.print(millis());
   Serial.println(" microseconds old. Well, my sketch is.");

   //Now print out the alphabet
   Serial.println("I know my alphabet! Let me show you!");
   Serial.println("Letter\tDec\tHex\t");
   for (i = 'A'; i <= 'Z'; i++)
   {
     Serial.write(i);
     Serial.print('\t');
     Serial.print(i);
     Serial.print('\t');
     Serial.print(i, HEX);
     Serial.print('\t');
     Serial.print('\n');
   }
 }

 void loop()
 {
 }

```

## Example 2 - Using Software Serial

```cpp
#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

// set up a new software serial port instance
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

void setup()
{
mySerial.begin(4800);
mySerial.println("Hello, world!");

bool result = mySerial.overflow(); // check the software serial buffer for an overvlow
}

```

`bool result = mySerial.overflow();` checks the internal overflow flag and automatically resets it. Subsequent calls to this function will report no overflow, unless more data has been received, causing another overflow.