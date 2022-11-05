[[James A. Langbridge - Arduino Sketches]]

### Serial Communication
garden-topic::[[Serial Communication]]
⬇️ 

#### UART ✅ 
garden-topic::[[UART]]

RS-232 was the original standard, replaced by USB to connect more peripherals. USB can connect to RS-232 hardware using a special converter.  RS-232 was designed for longer runs(up to 1000ft) and is a low capacitance cable. RS-232 connections transmit 10 bits: a start bit, 8 data bits, and a stop bit

For Arduino, USB communication is sent to pins 0 and 1, so **you cannot use these pins if you want to communicate with the computer** (e.g. using the `Serial.print` functions).

USB has the benefit of auto configuring many of the UART configurations needed for other Serial protocols below.

UART is hardware that translates between serial and parallel. To begin using a UART device you need to set:
1. the speed (baud-rate)
2. the data/parity/stop bit configuration (e.g. 8N1 is default on Arduino, meaning 8 data-bits, no parity bits, and one stop bit -- this results in 10 bits as a start bit is also always needed). 

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221105105954.png]]

**Data encapsulation** is placing the data inside other bits that help the computer identify what is being sent:
- **Data bits**: can be between 5 and 9, but most systems use 8 bits because that is 1 byte. 
- **Parity bits**: for error checking, a parity bit is added to make the number of 1s in a packet even or odd, but is not really needed for modern signaling technology. 
- **Stop bits**: usually 1 stop bit is used, older systems are sometimes different

For Arduino, the native UART controller has a buffer of 64 bytes. Some Arduinos have several UART devices, meaning several pieces of hardware that can independently handle Serial communication. For example on the Mega these are called `Serial1`, `Serial2` and `Serial3` (for a total of 4 UART controllers including the first `Serial` on pins 0 and 1). 

The Leonardo's microcontroller (32U4) has built-in USB communication, separating the USB for communicating with the computer and the Serial UART hardware for using peripherals. (here the `Serial` class refers to a virtual serial driver, not the serial device on pins 0 and 1, which are connected to `Serial1`). Since the virtual serial port can take longer to be initialized, for the Leonardo it is useful to wait until the port has initialized with `if(Serial)`. (note on non 32U4-boards this will always return true)

SoftwareSerial requires pins that support change interrupts.
- The Mega2560 can use pins 10 through 15, 50 to 53, and A8 to A15 for RX. On the Leonardo, pins 8 through 11 and 14 to 16 can be used. ([Location 2695](https://readwise.io/to_kindle?action=open&asin=B00SL47ZJG&location=2695))

#### SPI ✅

"Serial Peripheral Interface" created to allow multiple devices to be used on a single serial port. Synchronous (requires clock) and full-duplex (both devices can send and receive at the same time). 

Uses a ~~Master/Slave~~ Main/Secondary control scheme - the Main can communicate with only one Secondary peripheral at a time. Compared to networking the Main is the Host and the Secondary is the Client.

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221105125854.png]]

Requires 4 wires
- `MOSI` and `MISO`: Data wires are MOSI (Main Out-Secondary In) and MISO (Main In-Secondary Out).
- `SCLK`: serial clock regulates the speed of the communication
- `SS`: "Secondary Select", used to select the peripheral

SPI Main's generate their own clock signal and sends it to every device (on the `SCLK` line). 
- Some devices are active on rising edge and some are active on falling edge.  
- The clock can be configured active low or high
- Peripherals may have a maximum clock speed, so don't exceed this

SPI can select any data length it wants. 
- You have to know if the device is expecting the MSB or LSB bit first.
- Data is normally shifted out with the MSB first

Cons
- each Secondary requires its own Secondary Select pin on the Main.
- only one peripheral can be selected at a time (active low) - so all other Secondaries must have outputs driven high when not communicating

> [!CAUTION] Some sensors (like the DHT-11) require a small timeframe in which the conversion will be made. If this is required, the master must not initiate the clock until the slave has had time to complete the conversion.

**Arduino Specifics**

> [!tip] On Arduino boards the SPI is exposed via a combination of the ICSP header and a some digital pins.

The ICSP header exposes the MISO, MOSI, SCLK, Power and Ground pins. Any output pin can be used as the SS pin, since it is not used to transmit data

Arduinos can become a Secondary and have an input SS pin (pin 10 on the Uno, pin 53 on the Mega).

##### SPI Library Functions

```cpp
// Library, Open and Close the SPI connection
#include <SPI.h>

SPI.begin(); // automatically sets the SCLK, MOSI, and SS pins to output
	// pulls SCLK, MOSI LOW
	// pulls SS HIGH
	// sets MISO pin as an input
SPI.end();

// Configuring the SPI Bus, prepend commands with SPI.
setBitOrder() // should the MSB or LSB be sent first?
setDataMode() // sets clock polarity and phase
setClockDivider() // sets the SCLK frequency in relation to the system clock
// the divider is a numerical constant, available as e.g. SPI_CLOCK_DIV4
// AVR-based systems default is a divider of 4
// so the SPI bus frequency is 16/4 = 4MHz

// Sending and Receiving
byte result = SPI.transer(byte val) 
// only transfers one byte per call
// input parameter is the byte to send on the SPI bus
// result is the byte received on the SPI bus

```

[[Example - Langbridge SPI Thermocouple]]

#### Wire ✅

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

##### `Wire.h` Library

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

#inbox/writing 🍊