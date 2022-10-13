parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
#draft 

The basic theory is that we want to get the `loop()` flywheel running as fast as possible - we want nothing to hang it up, so we can do multiple things at once with the microprocessor.

This can involve ideas like "state machines",  task managers, and Timers. But the basic thing will be incrementing counters and raising flags to tell the microprocessor if, in each time through `loop()`, it should chip away at a task or check a state machine's value. 



## Resources
- https://learn.digilentinc.com/Documents/407
- https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
- https://www.instructables.com/Simple-Multi-tasking-in-Arduino-on-Any-Board/
- [Sandwich Analogy by StefanL38](https://forum.arduino.cc/t/easy-to-understand-analogy-how-to-code-doing-things-in-almost-parallel-multi-tasking/991589)
	- by `StefanL38` ; explains the fundamental concept of why we should write non blocking code; calls it "step chain" ;  code is just pseudocode, just take the concepts and internalize
	- if we are making a sandwich we want to both cut the onions in parallel and cut the tomatoes
	- each unique step chain (e.g. cutting a tomato or cutting the onions) has its own function
	- for each unique step chain function we need a constant for each step
		- e.g. when cutting a tomato if there are four steps we need four constants/indices - these become `switch case` or `if` conditions that we check when we enter the "cut the tomato" function - when done with one step we increment the counter/pointer to the next step chain constant/index
		- you can use an `enum` type to specify the constant values for switch/case
	- then for each step chain we can further break it down it to more steps, ad infinitem...
- [Multitasking made easy by smathieu13](https://forum.arduino.cc/t/multitasking-made-easy/1013708)
	- cake analogy and Timers for control flows
	- defines his Timer classes
		- more than one timer is needed for each CakeMaker
	- defines an oven class- likes using classes clearly
		- has booleans: on/off state (state machine) and one for another condition (temperature)
		- see the `heating()` function - main function that uses a switch/case to decide what to do
		- defines functions as e.g. `addingIngredient()` instead of `addIngredient()` to reinforce that state machines have waiting states
			- flow is 1) do a task 2) check the condition 3) handle any errors 4) increment state machine counter to do the next task
			- uses timers within these functions to make sure it doesn't hang up
			- the function that calls the `addingIngredient()` , the "caller", should acknowledge that the task has been done and reset the state
		- [software control structures](software%20control%20structures.md) -> use the correct boolean operator so that the ingredients are not added  _sequentially_ but evaluated concurrently
			- ![](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221013232938.png)
	- summary
		- each time we encounter a waiting condition, we create a state for the machine
		- the machine waits for the waiting condition to clear; a state machine returning true means that the task is not finished
		- since the task is not finished the caller or somewhere higher is responsible to come back and call the function again until the task is done
		- so basically we are task hunting during each loop seeing what tasks have been completed (by checking the value of the state machine) 
			- but while doing the tasks we make sure to 1) not do too much at once and 2) use timers not to hang it up on one tasks
		- the longest loop period must be shorter than any time counted