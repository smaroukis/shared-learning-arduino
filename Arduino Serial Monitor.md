parent::[[UART]]

[[Example - Reading Data from the Serial Monitor]]

### Writing Data

By default numbers are displayed in decimal and rounded two places. Quotation marks, backslashes and single quotes need to be escaped -- also see [[Table - ASCII Values]]. 

Write text with `Serial.print()`. Write data with `Serial.write()`. 

The default serial connection can send 8 bits of data per packet, so you can send a byte in a single data packet. To write more with `Serial.write()` you can pass a buffer length. 

### Reading Data

When the UART device receives data, it store it in a 64-byte internal buffer. Interrupts can be put in place to tell the microcontroller to retrieve information from this buffer before too much data arrives. 

`Serial.available()` returns the number of bytes in the buffer
- the data is returned as an `int`, since it needs to return `-1` if no data is available

`Serial.read()` takes one byte from the buffer and returns it as an `int`  - note this modifies the buffer (cf. `Serial.peek()`)

`Serial.readBytes()` reads multiple bytes from a serial port and places them into a buffer. `Serial.readBytesUntil()` reads bytes in until all the characters are read in, when there is a time-out, or when a special character is read. 

> [!CAUTION] `readBytesUntil()` is an example of a blocking function

The time-out for reading serial data is set by `Serial.setTime-out()`

`Serial.peek()` returns the first byte of data from the UART buffer without modifying it, this way we can check if the first character is an ASCII data that should be put into a string or binary data that should be put in another buffer to be processed.

### Parse Data

`Serial.parseInt()` will scan through text and extract any `ints` encountered


### Ending a Serial Connection

`Serial.end()`

