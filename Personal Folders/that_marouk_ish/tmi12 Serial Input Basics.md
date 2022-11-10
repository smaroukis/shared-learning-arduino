parent::[tmi Examples](tmi%20Examples.md)
previous:: [tmi11 Temp and Humidity Sensor](tmi11%20Temp%20and%20Humidity%20Sensor.md)
next:: [tmi14 Multitasking-1](tmi14%20Multitasking-1.md)
level:: #beginner
garden-topic:: [Serial Communication](../../Serial%20Communication.md)

## **Fundamental**

> Source: https://forum.arduino.cc/t/serial-input-basics-updated/382007/2 

### 1) Writing Data to the Monitor

**Numbers**
- by default `Serial.print()` will write in decimal, but we can write something like a binary number by providing the encoding e.g. `Serial.print(136, BIN)` -> outputs `10001000`

### 2) Reading Data From a User

Reading data from the user/serial input
1. Ask
2. Wait
3. Read

**Blocking functions (poor)**
- These hang up the Arduino and prevent it from doing anything else
- It is best to design the `loop()` to run as many times as possible (no delays, no blocking)
- So try to avoid these functions:

`while (Serial.available == 0)``
`Serial.parseInt()`   / `Serial.pareseFloat()`
`Serial.readBytes()` / `Serial.readBytesUntil()`


**Non-blocking functions**: 
- All of the examples below are non-blocking (from the source above)
- Basic Theory
	- 1) check if there is data available and the data is valid (e.g. between start and end characters)
	- 2) read each char into an array until the end-line character is reached
	- 3) print the data

---

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

---

**Example 2- Receiving Several Characters from Serial Monitor**

For receiving strings of more than one character, we need to let Arduino know it has received the full message. ➡️ set the line-ending to newline in the Serial Monitor

Cons: Doesn't work if the user sending the data doesn't know when the Arduino is ready to receive the data (e.g. they can't see the Serial Monitor)

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

---

**Example 3 - Including a Start Marker**

Use a new boolean that is true only after a start marker and before and end marker (`recvInProgress`)

```c
// this replaces code in 1) Store New Data above
void recvWithStartEndMarkers(){
	static boolean recvInProgress = false; // new boolean flag
	static byte i = 0;
	char startMarker = '<';
	char endMarker = '>';
	char rc;

	while (Serial.available() > 0 && newData == false) {
		rc = Serial.read();

		if (recvInProgress == true) {
			if (rc != endMarker) {
				// store the chars
				receivedChars[i] = rc;
				i++;

				if (i >= numChars) {
					i = numChars - 1;
				}
			}
			else {
				receivedChars[i] = '\0'; // terminate string
				i = 0; // reset index
				recvInProgress = false; // change flag
				newData = true; // ready to print
			}
		}
		// check if the user entered a start marker
		else if (rc == startMarker) {
			recvInProgress = true;
		}
	}
}

```

> Note that the 64 byte size of the Arduino serial input buffer does not limit the number of characters that you can receive because the code in the examples can empty the buffer faster than new data arrives.

> `Serial.flush()` does not empty the input buffer but is used when the Arduino is sending data and blocks the Arduino until all outgoing data is sent.

To ensure the Serial input buffer is empty do:

```c
while (Serial.available > 0) {
	Serial.read(); // this will clear the Serial input buffer
}
```

---

**Example 4 - Receiving a Single Number**

As in Example 1 but when printing the data the `if (newData == true)` block we use `atoi()` to convert

```c
// relevant variables just for this code
int dataNumber = 0; // new
char receivedChars[32]; // hard coded size

// setup things

void loop() {
	// 1) Receive and Store the Data - see Example 1

	// 2) Show the Data - Now a Number
	if (newData == true) {
		dataNumber = 0; //new
		dataNumber = atoi(receivedChars); // new
		Serial.println(receivedChars); // prints as ASCII string
		Serial.println(dataNumber); // prints as int
		newData = false;
		}
}
```

---

## Resources

**Further**
- Examples 5 and 6 of the [forum example](https://forum.arduino.cc/t/serial-input-basics-updated/382007/11) go into parsing multiple numbers and parsing binary
- for sending binary data, if the data matches the start and end markers: https://forum.arduino.cc/t/demo-of-pc-arduino-comms-using-python/219184
- [Table - ASCII Values](../../Table%20-%20ASCII%20Values.md)