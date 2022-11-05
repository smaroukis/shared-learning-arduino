parent::[[Arduino Boards]]

- Uses an ATmega328 as the main microcontroller
- Uses an ATmega16U2 to process USB connections (which ATmega328 can't)

### Pin specifics 
For a basic intro see [[Arduino Pin Considerations]]

-   Serial: 0 (RX) and 1 (TX). Used to receive (RX) and transmit (TX) TTL serial data. These pins are connected to the corresponding pins of the ATmega8U2 USB-to-TTL Serial chip.
-   External Interrupts: 2 and 3. These pins can be configured to trigger an interrupt on a low value, a rising or falling edge, or a change in value. See the attachInterrupt() function for details.
-   PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function.
-   SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK). These pins support SPI communication using the SPI library.
-   LED: 13. There is a built-in LED driven by digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off.
-   TWI: A4 or SDA pin and A5 or SCL pin. Support TWI communication using the Wire library

The Uno has 6 analog inputs, labeled A0 through A5, each of which provide 10 bits of resolution (i.e. 1024 different values). By default they measure from ground to 5 volts, though is it possible to change the upper end of their range using the AREF pin and the analogReference() function

The ATmega328 provides UART TTL (5V) serial communication, which is available on digital pins 0 (RX) and 1 (TX). An ATmega16U2 on the board channels this serial communication over USB and appears as a virtual com port to software on the computer. The 16U2 firmware uses the standard USB COM drivers, and no external driver is needed. However, [on Windows, a .inf file is required](https://www.arduino.cc/en/Guide/Windows#toc4)

Source: https://store-usa.arduino.cc/products/arduino-uno-rev3



>  There are three more breakout pins on the PCB, next to the AREF pin there is are two I2C pins (SDA/SCL) - this is a **duplication** of the Analog 4 and 5 pins. There is not an extra I2C interface or anything, its just that they made a copy of those pins there for future shields since the I2C pins are in a different place on Mega. There is also an IOREF pin which is next to the Reset pin - this is to let shields know what the running I/O pin voltage is on the board (for the UNO, its 5V). Again, this is a **duplication** of the power pin, it does not add voltage level shifting to the UNO. (source: https://learn.adafruit.com/arduino-tips-tricks-and-techniques#uno-r2-and-r3-1884396)

**Uploading code other than the serial monitor**
You can also bypass the bootloader and program the microcontroller through the ICSP (In-Circuit Serial Programming) header using [Arduino ISP](https://www.arduino.cc/en/Main/ArduinoISP)

### Resources
- https://learn.adafruit.com/arduino-tips-tricks-and-techniques#uno-r2-and-r3-1884396
