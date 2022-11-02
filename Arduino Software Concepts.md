parent::[[Arduino]]
previous::[[Intro to Arduino - Software]]
next:: [[Memory]]
sibling:: [[Other Software Concepts]]

> [!NOTE] A note about this page and the hierarchy.
> This page should be the jumping off page for learning the fundamental Arduino software concepts. For more advanced concepts see [[Other Software Concepts]] (e.g. specific C-functions, intermediate + usages, etc.)

#refactor  for sequence. , more into [[Other Software Concepts]]
1. variable types, reserved keyword s, c++ vs c 
2. scope, functions
3. non blocking delays
4. oop
5. strings and chars - char *
6. pointers
7. timers and interrupts m
8. best practices- define, header files, 
9. other things- enums, cool sequences, examples

Unsigned Long for timers -- [[Arduino Variable Types]]

[[Reserved Keywords]]

[[Multitasking and non blocking delays]]
- After learning about the basics of the software, an important part of programming for microcontrollers is about not blocking the software from doing other things.

[[Order of operation.md|Order of operation]]
- `millis() >= (delayStart + 1000)` is mathematically equal to `millis() - delayStart >= 1000` but the order of evaluation is important
	- for the first case, since it is an unsigned long, when `millis()` overflows to `0` after around 50 days the expression will now always be false
	- and in the other case when `delayStart` is initialized after 50 days, it will immediately evaluate to true

[[Avoid magic numbers.md|Avoid magic numbers]]
- instead of `if (val !== 32)` define a constant variable to hold `32` and compare against that instead - 