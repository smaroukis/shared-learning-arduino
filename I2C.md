---
alias: ["Two Wire", "TWI", "Wire"]
---
parent::[[Serial Communication]]
previous::[[SPI]]

> Source: [[James A. Langbridge - Arduino Sketches]]

## I2C Overview

[[I2C]] is a [[Serial Communication]] protocol (cf. [[UART]], [[SPI]]) used for communicating with many peripherals that can connect to the same bus. Unlike [[SPI]], we don't require select pins for the peripherals - each peripheral has its own unique address to know whether it is being requested by the Main.

I2C is short for Inter-IC bus, also goes by the name "Two Wire" - since we just need two wires (_plus_ a ground) to communicate with many devices. It is easier to configure than SPI, since there is no concept of mechanisms like chip select or chip activate (cf. [[SPI]]), but each device requires a unique address - and there is a lot of confusion around this.

Clock speed is 100kHz default and 400kHz maximum (the actual protocol maximum is 5MHz as of 2012). 

The two data wires are called SDA (Serial Data) and SCL (Serial Clock). 

I2C can only send data in 8-bit packages. Devices tend to be small with only a few pins, and usually we can't setup our own address. The Data is stored internally to the peripheral in a register - some devices only have one, some devices have multiple. 

I2C requires [[Pullup Resistors]] on the data lines since they are of "[[open drain]]" type. 

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221105150231.png]]

**Sequence**
- Mains automatically receive all information from Secondaries
- When the Main wants to write, it broadcasts the address of the Secondary that it wishes to address and whether the operation is a read or a write
	- Main communication must be done in a single transmission
- The correct Secondary responds with an ACK (acknowledge) signal
- We also need to know the length of data to be received
- We also need to know the register of the Secondary that the data is stored in
- When the secondary responds there is no data encapsulation

**Addressing**
- usually the peripheral's address is already predefined (rarely is it possible to configure your own)
- the original protocol defined 7-bit addressing, this was later extended to 10
- In 7-bit addressing, addresses are (of course) 7 bits long, and the last bit is used to select a read or a write, for a total of 8 bits.
- In 10-bit addressing, things are a little more complicated (since we can only send 8 bits at a time) - see the diagram below. The first 5 bits are always written as `11110` since this is reserved in 7-bit addressing. 

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221105150400.png]]

Cons
- not full duplex, so devices can't send and receive data at the same time
- more traps and pitfalls than SPI (voltage differences between 5V Arduinos and some 3.3V )
- all components will use the same bus speed defined by the Main (thus limited to 100kHz)

> [!CAUTION] Some I2C devices are 3.3V, but the Arduino input pullup-resistor connects to 5V, so make sure you are using the correct voltage levels


## The Arduino `Wire.h` Library

General functions:
```cpp
#include <Wire.h>

Wire.begin() // Arduino as a Main
Wire.begin(address) // Arduino as a Secondary

// Sending Data
Wire.beginTransmission(address)

Wire.write(value) // append a byte
Wire.write(string) // append a string
Wire.write(data, length) // append an arraw with a specified number of bytes
	// Wire.write returns the number of bytes appended to the message but we don't nec. need to store this

Wire.endTransmission() // sends whatever has been written to the message so far; by default the I2C bus is freed

// Requesting Data

Wire.requestFrom(address, quantity) // creates and sends a request message from the Main to the Secondaries

byte data = Wire.read(); // only reads one byte in from the buffer

// typ. use with Wire.available

while(Wire.available()){
	char c = Wire.read();
	Serial.print(c);
}
```

Callback demonstration:
```cpp
// Arduino as a Secondary - Callbacks Exampel

void receiveData(int byteCount){
// this function will be called by the callback Wire.onReceive()
// any time the Arduino operating as a Secondary receives information
// from a Main
}

void sendData() {
	// e.g. Wire.write(data);
}

void setup{
	Wire.onReceive(receiveData); // assign the receiveData() function to the Wire.onReceive callback
	// will call receiveData with the number of bytes receibed
	
	Wire.onRequest(sendData);
}

```

Arduino as a Secondary
- use Wire libraries callbacks - that is `Wire.onReceive()` and `Wire.onRequest()`

Example
- [[Example - Langbridge I2C Arduino as Secondary]]

## Resources
- https://www.arduino.cc/reference/en/language/functions/communication/wire/
- https://docs.arduino.cc/learn/communication/wire