parent::[Arduino](Arduino.md)
previous::[Intro to Arduino - Software](Intro%20to%20Arduino%20-%20Software.md)


Unsigned Long for timers -- [Arduino Variable Types](Arduino%20Variable%20Types.md)

[Non blocking delays](Non%20blocking%20delays.md)
- After learning about the basics of the software, an important part of programming for microcontrollers is about not blocking the software from doing other things.

Order of operation
- `millis() >= (delayStart + 1000)` is mathematically equal to `millis() - delayStart >= 1000` but the order of evaluation is important
	- for the first case, since it is an unsigned long, when `millis()` overflows to `0` after around 50 days the expression will now always be false
	- and in the other case when `delayStart` is initialized after 50 days, it will immediately evaluate to true