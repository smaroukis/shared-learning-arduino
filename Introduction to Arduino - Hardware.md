parent::[Arduino](Arduino.md)
next::[Intro to Arduino - Software](Intro%20to%20Arduino%20-%20Software.md)

## Index
- [Arduino - ADC](Arduino%20-%20ADC.md)
- [Arduino Pin Considerations](Arduino%20Pin%20Considerations.md)
  - [Pullup Resistors](Pullup%20Resistors.md)
- [Sources and Sinks](Sources%20and%20Sinks.md)

Other Topics
- [Arduino Boards](Arduino%20Boards.md)

## Introduction (Uno and Mega)

The Arduino [Uno](Uno.md) (Rev 3) uses the ATMega328P as the main microcontroller and the ATMetga 16U2 as an auxiliary microprocessor to communicate between the ATMega328P and the computer (it is used as a Serial-to-USB converter, see [Serial Communication](Serial%20Communication.md) for more)

The [Mega2560](Mega2560.md) also uses the 16U2 is a usb-serial converter but uses the ATMega 2560 as the main microprocessor which has more IO pins, more serial ports, more memory, etc. This makes it especially good for working with many peripherals. 

The [word size](word%20size.md) is 16 bits (2 bytes). The clock speed is 16MHz. 

**Power**
- Power can be purely from USB (which is how it runs when connected to your computer), or via the dedicated power plug - a 9V barrel jack (2.1mm tip, center positive). The microcontroller itself runs on 5V (some Arduino's run at 3.3V, so make sure you know which you are using).
- the V_in pin is the same voltage that is supplied to the board via the barrel jack (voltage between 7-12V), giving access to the unregulated (non 5V) voltage which can be used by external peripherals, e.g. motors
- there is also sometimes a 3.3V output power pin, with a maximum draw a bit more than the 5V pins, 50mA

The reset button reboots the uploaded program.

Pins - see [Arduino Pin Considerations](Arduino%20Pin%20Considerations.md). Generally the rule is to keep output draw <25mA (max in the spec sheet is 40mA).

## Resources
- [Afrotechmods 15minute intro video](https://www.youtube.com/watch?v=nL34zDTPkcs)
