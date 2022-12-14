parent::[Arduino Memory Specifics](Arduino%20Memory%20Specifics.md), [Serial Communication](Serial%20Communication.md)
level:: #intermediate 
also see: [Pointers](Pointers.md)

The Harvard model turns out to be a good match for embedded applications and the Atmega 328 used in the Arduino UNO use a relatively pure Harvard architecture. Programs are stored in Flash memory and data is stored in SRAM.

**Raw Notes** 

> By default the core Arduino runtime firmware actually has an array to buffer the bytes already to store these in and the default length of **this buffer is 64 bytes** at the time of this writing

#code handling Arduino memory with our own buffer and using [C Functions - memmove](C%20Functions%20-%20memmove.md) - note the code here is not checked or verified, just a rough example
```c
#define BUFSIZE 128

unsigned char buf[BUFSIZE]; // define an array for our own buffer
int buflen = 0;

void setup() {
	Serial.begin(115200);
}

void loop() {
	if (Serial.available() > 0) {
		unsigned char b = Serial.read(); // remove the next byte from the Arduino buffer
		if (buflen < BUFSIZE) {
			// we have room to store the byte into our own
			buf[buflen++] = b; // first store the char/byte at the buflen index, then increment
			}
	}

	// check our local buffer to see if it has something in it
	if (buflen > 0) {
		unsigned char c = buf[0]; // grab the 0-index char
		buflen--; 

		// now we need to move the bytes in memory in our buf array up one byte
		// so that the next byte will be at 0 index
		memmove(&buf[0], &buf[1], buflen); // moves the addresses of buf[1] to buf[1]+buflen-1 to the address of buf[0]

		// now do something with the `c` char ...
		}

}
```
#q/answered how does the above `memmove()` move all the "downstream" bytes past the `&buf[1]` address? the `buflen` tells us how many bytes in memory to move.
	**Notes on `memmove()`** -> [C Functions - memmove](C%20Functions%20-%20memmove.md)
	
**References**:
-   https://www.reddit.com/r/arduino/comments/y2tv7s/comment/isbs6kw/?utm_source=share&utm_medium=web2x&context=3 

**Further**
- Ring Buffers
