parent::[Intro to Arduino - Software](Intro%20to%20Arduino%20-%20Software.md)
previous:: [Arduino Variable Types](Arduino%20Variable%20Types.md)
next::

**Input and Output Functions**

`pinMode(7, INPUT)`
`pinMode(7, INPUT_PULLUP)`
`pinMode(7, OUTPUT)`

`digitalWrite(7, HIGH)
`int digitalRead(7)`

`int analogRead()`: returns number from 0 to 1023
`analogWrite()`: changes the PWM rate on a PWM-enabled pin, accepts 0 to 255
 
`shiftOut(dataPin, clockPin, bitOrder, value)`: sends data to the shift register in order to expand the number of digital outputs

`unsigned long pulseIn(pin, value)`: measures the duration of a pulse coming on on a digital input

**Time Functions**

`unsigned long millis()`

`delay(ms)`

`delayMicroseconds(us)`

**Math Functions**

`min()`, `max()`, `abs()`, `constrain()`, `map()`, `pow()`, `sqrt()`

**Random Number Functions**

`randomSeed()`

**Serial Communication**

`Serial.begin(speed)`

`Serial.print(data, [encoding])`

`Serial.println(data, [encoding]`: adds a carriage return and line feed to simulate `Enter` (= `\r\n`)

`int Serial.available()`: returns how many unread bytes are available on the serial port 

> See [Serial Communication](Serial%20Communication.md) resources for an example of how this can be misused

`int Serial.read()`; fetches 1 byte of incoming serial data

`Serial.flush()`


`Serial.flush()`