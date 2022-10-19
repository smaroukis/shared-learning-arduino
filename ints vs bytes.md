an `int` takes up 2 bytes (16-bits) whereas a `byte` takes up 1 byte.

- [ ] #q : for a 16-bit bus address, is the memory assigned e.g. 

> Using ints means that things wind up on even byte boundaries, which might be a good thing (It was a thing back in the day on x86 processors). If your sketch is just one byte short of being able to fit into ram, you probably need a mega. ^[https://forum.arduino.cc/t/arduino-the-object-oriented-way/354998/4]