parent:: [Memory](Memory.md)
resource::
related::[Arduino Variable Types](Arduino%20Variable%20Types.md), [Arduino Serial Buffers](Arduino%20Serial%20Buffers.md)

First read [Memory](Memory.md) which gives a brief overview of microcontroller memory organization. Then look for Arduino (AVR) specific memory tables and amounts on this page.

> [!example]- Table - Memory Amounts by Arduino Board 
> 
> ![Table - Arduino Memory Amounts](Table%20-%20Arduino%20Memory%20Amounts.md)

![Pasted image 20221019125029](attachments/Pasted%20image%2020221019125029.png)

> [!example]+ Checking the size of an `int` vs a `byte`
> We can see here that the `bytes` only take-up one byte, whereas the `ints` take up two, since all of the variables are next to each other in memory starting from `0xF6`
> ```cpp
> void setup() {
>   int foo = 1;
>   int bar = 1;
>   byte baz = 1;
>   byte qux = 1;
>   Serial.begin(9600);
>   Serial.println(long(&foo)); // 2296 = 0xF8
>   Serial.println(long(&bar)); // 2294 = 0xF6
>   Serial.println(long(&baz)); // 2299 = 0xFB
>   Serial.println(long(&qux)); // 2298 = 0xFA
> }
> 
> void loop() {
> }
> ```

## Resources
- HackadayU Reverse Engineering AVR / Arduino Youtube Video
- https://docs.arduino.cc/learn/programming/memory-guide
- 