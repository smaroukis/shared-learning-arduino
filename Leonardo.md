parent::[[Arduino Boards]]


- the ATmega32U4 combines the functions of the 328 and 16U2, as in the [[]]
- you can manipulate the USB behavior from your sketch using special `Mouse` and `Keyboard` libraries
- creates the USB port in the sketch -> resetting the Leonardo breaks the USB serial connection
- can `analogWrite()` on pin 13 (the internal LED)

**Further**
- see [[Personal Folders/that_marouk_ish/banziGettingStartedArduino]] Chapter 7 for a Leonardo project example