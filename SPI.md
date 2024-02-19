parent::[Serial Communication](Serial%20Communication.md)
		 
resource::[Example - Langbridge SPI Thermocouple](Example%20-%20Langbridge%20SPI%20Thermocouple.md)
next::[I2C](I2C.md)
previous::[UART](UART.md)

> Source: [James A. Langbridge - Arduino Sketches](James%20A.%20Langbridge%20-%20Arduino%20Sketches.md)

## Intro

"Serial Peripheral Interface" created to allow multiple devices to be used on a single serial port. Synchronous (requires clock) and full-duplex (both devices can send and receive at the same time). 

Uses a ~~Master/Slave~~ Main/Secondary control scheme - the Main can communicate with only one Secondary peripheral at a time. Compared to networking the Main is the Host and the Secondary is the Client.

![Pasted image 20221105125854](attachments/Pasted%20image%2020221105125854.png)

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

## Arduino Specifics

> [!tip] On Arduino boards the SPI is exposed via a combination of the ICSP header and a some digital pins.

The ICSP header exposes the MISO, MOSI, SCLK, Power and Ground pins. Any output pin can be used as the SS pin, since it is not used to transmit data

Arduinos can become a Secondary and have an input SS pin (pin 10 on the Uno, pin 53 on the Mega).

## Sensor Specifics

> [!CAUTION] Some sensors (like the DHT-11) require a small timeframe in which the conversion will be made. If this is required, the master must not initiate the clock until the slave has had time to complete the conversion.

## SPI Library Functions

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

## Resources
- 