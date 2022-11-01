parent::[[Arduino Software Concepts]]
garden-topic::[[Memory]]
see-also::[[Arduino Variable Types]], [[Arduino Serial Buffers]]

First read [[Memory]] which gives a brief overview of microcontroller memory organization. Then look for Arduino (AVR) specific memory tables and amounts on this page.

> [!example]- Table - Memory Amounts by Arduino Board 
> 
> ![[Table - Arduino Memory Amounts]]

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221019125029.png]]

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