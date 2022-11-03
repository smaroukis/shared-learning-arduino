parent::[[Arduino Software Concepts]], [[Switches]]

### A Basic Debounce with Delay

A physical button needs to be "debounced" - since the microprocessor is running so fast, `digitalRead()` will cycle between both the ON and OFF state for a few cycles before the physical contacts are seated correctly.

To debounce a button, we add a 10-50ms delay between reading/comparing a new value and performing an action (e.g. turning an LED on). 

Debouncing can be as simple as comparing the read value with the previous value and waiting 10ms before writing it e.g. 

```
if ((val == HIGH)) && (old_val ==LOW)){
	state = 1 - state;
	delay(10) // the next step is to turn on the LED if the button was pressed
}
```

or we can also add a delay on the falling edge

```
if ((val == LOW)) && (old_val == HIGH){
	delay(10) // from reader Tami Takamiya
}
```

> [!TIP] Level up! Avoid using `delay()`
> See [[Multitasking and non blocking delays]] for ways to debounce in a "non-blocking" fashion
For variables we need

### Non-blocking Debounce

Variables we need to store:
- a timer
- the previous state
- a debounce time to compare against

Non variables we can read in "live"
- current time
- current state

General Process
1. Check the current measured state (`digitalRead()`) against the last state of the button
2. If it has changed **start a timer** and **store the state** into `previous_state`
3. 

### Example - Non-blocking

![[Example - Simple Debounce with MIllis]]
