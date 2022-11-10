parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
next:: [Interrupts, Timers and Callbacks](Interrupts,%20Timers%20and%20Callbacks.md)
level:: #beginner 

The basic theory is that we want to get the `loop()` flywheel running as fast as possible - we want nothing to hang it up, so we can do multiple things at once with the microprocessor.

This can involve ideas like "state machines",  task managers, and Timers. But the basic thing will be incrementing counters and raising flags to tell the microprocessor if, in each time through `loop()`, it should chip away at a task or check a state machine's value. 

![Pasted image 20221014223111](attachments/Pasted%20image%2020221014223111.png)
[source](https://forum.arduino.cc/t/a-demo-code-explaining-the-switch-case-state-machine-and-how-to-do-things-almost-in-parallel/888172/2)]

See [Example - Simple Debounce with MIllis](Example%20-%20Simple%20Debounce%20with%20MIllis.md)

**Start Here**
- https://learn.adafruit.com/multi-tasking-the-arduino-part-1 - categorized intermediate
	- blink without delay, flash without delay, state machine intro
	- then into OOP - classes for state machines
	- add in button input checks while sweeping a motor
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2
	- into interrupts - Timer, External, Pin-change
	- ditch the loop code to check for high priority interrupt conditions
- https://learn.adafruit.com/multi-tasking-the-arduino-part-3

## Resources
- https://www.baldengineer.com/?s=millis - some tricks on millis