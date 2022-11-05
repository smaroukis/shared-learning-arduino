parent::[Arduino](Arduino.md)

> While serial devices send bits on a single wire, parallel devices send multiple bits on multiple wires. Although parallel communications can be faster than serial, they were often more expensive, requiring more wires. ([James A. Langbridge - Arduino Sketches](James%20A.%20Langbridge%20-%20Arduino%20Sketches.md))

> With recent technological advances, serial communications can reach faster speeds than parallel communications, do to the decreased complexity

### Definitions

RS-232
:    A popular serial communication standard and interface introduced in 1960, defines the electrical characteristics and timing of signals, the meaning of signals, and the physical size and [pinout](https://en.wikipedia.org/wiki/Pinout "Pinout") of connectors. Supplanted by the USB standard. Typically using the D-subminiature connector.

USB
:    Universal Serial Bus, the ubiquitous modern standard for interfacing and transmitting serial data.

UART
:    Universal Asynchronous Receive Transmit, a hardware serial protocol that translates  the parallel data from the CPU to serial data used by peripherals (and vice versa). Uses two pins, `RX` and `TX`, to communicate between devices. 

> [!tip] In Arduino, "Serial" by itself refers to the UART controller

> [!CAUTION] Watch out for voltage levels differing by protocol. 

### UART vs I2C vs SPI

[UART](UART.md)
- the most well documented, used for communicating with/between PCs
- uses 2 wires, `RX` and `TX`
- configuration required on both devices (baud rate, data/stop/parity bits)

[SPI](SPI.md)
- pins: `MISO`, `MOSI`, `SCLK`, `SS`
- the Main has to have a `SS` (Secondary Select) pin for each Secondary - it pulls this low to communicate with the Secondary
- full duplex - Main and Secondary can read/write at the same time
- configuration: bit order, clock polarity and phase, clock frequency

[I2C](I2C.md)
- pins: `SDA` and `SCLK`
- not duplex - since there is only one Data line
- All peripherals (Secondaries) and the Main connect to the Data line (`SDA`), and have unique addresses (self-defined, pre-shipped). 
- The Main communicates with each Secondary by broadcasting the address of the Secondary it wants to address, and then sends the data
- The Main then listens to the `SDA` line and processes data
- configuration: addresses, peripheral registers, clock speed

### Arduino Specifics

When plugging in the Arduino to the computer, the USB automatically configures the UART necessary configurations. For the Uno and Mega, the ATmega 16U2 handles the Serial/UART to USB translation.

The Uno only has one UART controller, which is connected to pins 0 and 1. Because of this, if we are using the Serial Monitor on the computer (connected via USB), we cannot use a serial peripheral on these pins at the same time. Note with the `SoftwareSerial` library we can use UART/Serial on other pins.

Interfacing with peripherals (instead of a computer) is done usually via I2C or SPI. 

SPI and I2C capable pins are defined in the datasheet - these will require some form of an interrupt for the pins to receive data. 

Data can arrive at the serial port faster than your program can process it, so it is kept in a buffer.

## Resources
- https://forum.arduino.cc/t/serial-input-basics-updated/382007
- https://web.engr.oregonstate.edu/~traylor/ece473/lectures/twi.pdf

