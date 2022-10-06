parent::[Serial Communication](Serial%20Communication.md)

UART is a Serial Communication hardware protocol (cp. [I2C](I2C.md) and [SPI](SPI.md)).

Important
- serial
- no clock signal -> asynchronous
- baud rate 9600 to 1500000 (must be set on both devices)

**Raw** #refactor

- hardware for serial communication that handles the tranmission/reception of serial communication (external device required to handle the singalling level of the transmitting/receiving device)
	- electric signalling level are handled by a external driver circuit, e.g. RS-232 (12V) and RS-485 (5V)
- an IC or part of an IC that allows data format and transmission speeds to be configurable
- asynchronous - so uses a [shift register](shift%20register.md) to convert between serial and parallel forms
- sends and receives bits one by one from LSB to MSB with start/stop bits
- precise timing is handled by the communication channel
- communication can be simplex, full duplex, half duplex
- settings: baud rate, parity bit, data bits size, stop bits size, flow control
- has internal clock faster than the bit rate
- [[bit-banging]] is omitting the UART and using the CPU to sample the state of an input port or directly manipulate an output port for transmission; but it is CPU intensive because of the timing


## Resources
- https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html