parent::[tmi Examples](Personal%20Folders/that_marouk_ish/tmi%20Examples.md)
previous::
next::
level:: #beginner
garden-topic:: [Serial Communication](Serial%20Communication.md)

## **Fundamental**

### Writing Data to the Monitor
#tdf

**Numbers**
- by default `Serial.print()` will write in decimal, but we can write something like a binary number by providing the encoding e.g. `Serial.print(136, BIN)` -> outputs `10001000`

### Reading Data From a User

Reading data from the user/serial input
1. Ask
2. Wait
3. Read

`while (Serial.available ==0)`  hangs the program up until something is entered
`Serial.parseInt()`   / `Serial.pareseFloat()`

**Example 1 - Receiving a Single Character**

Cons: a `char` can only store 62 options

```c
char receivedChar;
boolean newData = false;

// void setup() things omitted for conciseness

void loop() {
	if (Serial.available() > 0) {
		receivedChar = Serial.read();
		newData = true;
		}
		

	if (newData == true) {
		Serial.print("This just in ... ");
		Serial.println(receivedChar);
		newData = false;
	    }
}
```

**Source**
- https://forum.arduino.cc/t/serial-input-basics-updated/382007

**Example 2- Receiving Several Characters from Serial Monitor**

For receiving strings of more than one character, we need to let Arduino know it has received the full message. ➡️ set the line-ending to newline in the Serial Monitor

```c
// Example 2 - Receive with an end-marker

const byte numChars = 32; // define the size of array of chars 
char receivedChars[numChars]; // initialize array of size numChars to store data
boolean newData = false;

// setup() omitted for brevity

void loop(){
	static byte i = 0;  // index
	char endMarker = '\n'; // this will signal to the Serial Monitor that the user is done inputting (when they press `Enter`)
	char rc; // to store each char read in Serial.read()

	// 1) Store New Data
	while (Serial.available() > 0 && newData == false) {
	rc = Serial.read(); // one char at a time

		if (rc != endMarker) {
			receivedChars[i] = rc;
			i++;

			if (i >= numChars) {
				i = numChars - 1; // set the index to the end
			}
		}
		else {
			receivedChars[i] = '\0'; // terminate the string
			i = 0; // reset index
			newData = true; // set flag that means we have stored the data and it is ready to be shown to the Monitor
		}
	}

	// 2) Show New Data
	if (newData == true) {
		Serial.print(receivedChars);
		newData = false; // reset the flag
	}
}
```

## Intermediate

## Resources
**Basic**
- https://www.youtube.com/watch?v=7aP5KL5clWA&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=19