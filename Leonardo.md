parent::[Arduino Boards](Arduino%20Boards.md)


- the ATmega32U4 combines the functions of the 328 and 16U2, as in the [Leonardo](Leonardo.md)
- you can manipulate the USB behavior from your sketch using special `Mouse` and `Keyboard` libraries
- creates the USB port in the sketch -> resetting the Leonardo breaks the USB serial connection
- can `analogWrite()` on pin 13 (the internal LED)

**Further**
- see [banziGettingStartedArduino](Personal%20Folders/that_marouk_ish/banziGettingStartedArduino.md) Chapter 7 for a Leonardo project example