parent::[[Arduino]]
previous::[[Intro to Arduino - Software]]
sibling:: [[Other Software and Computer Concepts]]

> [!NOTE] A note about this page and the hierarchy.
> This page should be the jumping off page for learning the fundamental Arduino software concepts. For more advanced concepts see [[Other Software and Computer Concepts]] (e.g. specific C-functions, intermediate + usages, etc.)

1. [[Arduino Variable Types]], [[Arduino Case Statements]], [[Arduino Boolean and Arithmetic]], [[Arduino Functions]]
2. [[Multitasking and non blocking delays]]
	After learning about the basics of the software, an important part of programming for microcontrollers is about not blocking the software from doing other things.
3. [[Scope]], [[Preprocessing Directives]], [[Compilers]], [[Memory]]
4. [[Object Oriented Programming]]
5. [[Common Code Structure for Arduino Projects]] best practices- define, header files, 
6. [[Pointers]]
7. [[Pointers - Working with Strings]] strings and chars - char *
8. [[Interrupts, Timers and Callbacks]] timers and interrupts

[[Avoid magic numbers]]
- instead of `if (val !== 42)` define a constant variable to hold `42` and compare against that instead