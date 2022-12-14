
- https://learn.digilentinc.com/Documents/407 - basic 
- https://www.baldengineer.com/?s=millis - some tricks on millis
- https://learn.adafruit.com/multi-tasking-the-arduino-part-1 - categorized intermediate
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2
- https://learn.adafruit.com/multi-tasking-the-arduino-part-3
- https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html - good examples and uses an external library
- [Demonstration code for several things at the same time](https://forum.arduino.cc/t/demonstration-code-for-several-things-at-the-same-time/217158) by Robin2
	- converts the blink without delay into a state machine
	- `previousMillis += durationToCheck` is better than `previousMillis = currentMillis`  "to ensure that successive periods are identical"  #q I'm guessing this comes from the fact that we don't know what is happening between `currentMillis` which is checked at the beginning of the loop, and when this assignment is being carried out? 
	- loop steps are 
		- 1) get current time (stored in global variable that other functions can access)
		- 2)`updateLEDStatus()` check each LED "state machines" to see if they are ready to be turned on or off (compares individual state machine interval with previously stored time and current time) -- instead of turning on or off we just raise a flag to do so in ...
		- 3) `switchLEDs()` - writes the state stored during hte UpdateStatus() functions
- [Sandwich Analogy by StefanL38](https://forum.arduino.cc/t/easy-to-understand-analogy-how-to-code-doing-things-in-almost-parallel-multi-tasking/991589)
	- by `StefanL38` ; explains the fundamental concept of why we should write non blocking code; calls it "step chain" ;  code is just pseudocode, just take the concepts and internalize
	- if we are making a sandwich we want to both cut the onions in parallel and cut the tomatoes
	- each unique step chain (e.g. cutting a tomato or cutting the onions) has its own function
	- for each unique step chain function we need a constant for each step
		- e.g. when cutting a tomato if there are four steps we need four constants/indices - these become `switch case` or `if` conditions that we check when we enter the "cut the tomato" function - when done with one step we increment the counter/pointer to the next step chain constant/index
		- you can use an `enum` type to specify the constant values for switch/case
	- then for each step chain we can further break it down it to more steps, ad infinitem...
- [Multitasking made easy by smathieu13](https://forum.arduino.cc/t/multitasking-made-easy/1013708) - heavy use of object oriented programming 
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
		- [software control structures](software%20control%20structures) -> use the correct boolean operator so that the ingredients are not added  _sequentially_ but evaluated concurrently
			- ![Pasted image 20221013232938](Pasted%20image%2020221013232938.png)
	- summary
		- each time we encounter a waiting condition, we create a state for the machine
		- the machine waits for the waiting condition to clear; a state machine returning true means that the task is not finished
		- since the task is not finished the caller or somewhere higher is responsible to come back and call the function again until the task is done
		- so basically we are task hunting during each loop seeing what tasks have been completed (by checking the value of the state machine) 
			- but while doing the tasks we make sure to 1) not do too much at once and 2) use timers not to hang it up on one tasks
		- the longest loop period must be shorter than any time counted
- [Switch case state machine example by StefanL38](https://forum.arduino.cc/t/a-demo-code-explaining-the-switch-case-state-machine-and-how-to-do-things-almost-in-parallel/888172) - has some nice timer functions that let you pass the delay time in on the fly
- Task Macros - this guy - https://forum.arduino.cc/u/DrDiettrich  - https://forum.arduino.cc/t/projekt-multitasking/399677