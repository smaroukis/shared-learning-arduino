parent::[[Arduino Boards]]

> Note the Leonardo is now a retired product from Arduino, but you still may see projects in the wild using the board.

> The Leonardo differs from all preceding boards in that the ATmega32u4 has built-in USB communication, eliminating the need for a secondary processor. This allows the Leonardo to appear to a connected computer as a mouse and keyboard, in addition to a virtual (CDC) serial / COM port. (https://store.arduino.cc/products/arduino-leonardo-with-headers)

- the ATmega32U4 combines the functions of the 328 and 16U2, as in the 
- you can manipulate the USB behavior from your sketch using special `Mouse` and `Keyboard` libraries
- creates the USB port in the sketch -> resetting the Leonardo breaks the USB serial connection
- can `analogWrite()` on pin 13 (the internal LED)

**Further**
- see [[Personal Folders/that_marouk_ish/banziGettingStartedArduino]] Chapter 7 for a Leonardo project example