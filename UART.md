parent::[Serial Communication](Serial%20Communication.md)
next::[SPI](SPI.md)
child:: [Arduino Serial Monitor](Arduino%20Serial%20Monitor.md)

### Overview

Universal Asynchronous Reception and Transmission (UART) is a Serial Communication hardware protocol (cf. [I2C](I2C.md) and [SPI](SPI.md)). When we refer to the UART controller we are talking about the hardware that can send and receive Serial messages and relay them asynchronously to the CPU. 

Pins required
- `TX`: transmit pin
- `RX`: receive pin

![Pasted image 20221105121633](attachments/Pasted%20image%2020221105121633.png)

Transmitting UART converts parallel data from the master device (eg. CPU) into serial form and transmit in serial to receiving UART. It will then convert the serial data back into parallel data for the receiving device

The "universal" term means UART is generic - it doesn't define voltage levels, the number of data, parity, or stop bits - thus it can be configured to support many specific serial protocols. (See Configuration below)

Important
- Serial
- Asynchronous means no clock signal
- Baud rate 9600 to 1500000 (must be set on both devices)

> [!NOTE]+ UART in Arduino is `Serial`, `Serial1`, etc.
>  UART is called `Serial` in Arduino - this is the physical hardware that receives and transmits data when using e.g. `Serial.read()` or `Serial.print()`. A UART interface is used because it simply only needs a `TX` and `RX` pin to communicate with a peripheral. The Serial-USB conversion to send it to a Computer is done by the ATmega16U2, since the [Uno](Uno.md) and [Mega2560](Mega2560.md) MCUs (the ATMega 328P and 2560 respectively) do not have built-in USB communication.
> 
> Since pins `0` and `1` are also used by the USB communication (through the ATMega16U2) to communicate with the Serial Monitor, we cannot use these to connect an external UART peripheral and talk to the Serial Monitor at the same time.
>
> The native UART controller has an internal buffer of 64 bytes to store incoming data.
>
> The [Mega2560](Mega2560.md) has 4 total UART controllers, including pins `0` and `1` that are used by USB. We can access these in software as `Serial`, `Serial1`, `Serial2`, and `Serial3`.
> 
> The [Leonardo](Leonardo.md)'s MCU (ATMega32U4) has built-in USB communication, separating the USB for communicating with the computer from the Serial UART hardware for peripherals, so here the `Serial` class refers to the **virtual serial driver**, **not** the serial device on pins `0` and `1`.  Note the virtual Serial port can take longer to initialize. 

### Configuration

To begin using a UART device you need to set the speed (baud-rate) and the data/parity/stop bit configuration (e.g. 8N1 is default on Arduino and many other devices, meaning 8 data-bits, no parity bits, and one stop bit -- this results in 10 bits as a start bit is also always needed).

![Pasted image 20221105105954](attachments/Pasted%20image%2020221105105954.png)

The UART does not define voltage levels, refer to the specific protocol (e.g. [RS-232](RS-232.md)) if that is needed.

---

- hardware for serial communication that handles the transmission/reception of serial communication (external device required to handle the signaling level of the transmitting/receiving device)
	- electric signaling level are handled by a external driver circuit, e.g. RS-232 (12V) and RS-485 (5V)
- an IC or part of an IC that allows data format and transmission speeds to be configurable
- asynchronous - so uses a [shift register](shift%20register.md) to convert between serial and parallel forms
- sends and receives bits one by one from LSB to MSB with start/stop bits
- precise timing is handled by the communication channel
- communication can be simplex, full duplex, half duplex
- settings: baud rate, parity bit, data bits size, stop bits size, flow control
- has internal clock faster than the bit rate
- [bit-banging](bit-banging.md) is omitting the UART and using the CPU to sample the state of an input port or directly manipulate an output port for transmission; but it is CPU intensive because of the timing


## Resources
- https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html
- https://www.seeedstudio.com/blog/2019/09/25/uart-vs-i2c-vs-spi-communication-protocols-and-uses/
- https://electronics.stackexchange.com/questions/110478/difference-between-uart-and-rs-232