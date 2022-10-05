parent::[Debouncing](Debouncing.md)

To debounce a button, we add a 10-50ms delay between reading/comparing a new value and performing an action (e.g. turning an LED on). 

From [banziGettingStartedArduino](Personal%20Folders/that_marouk_ish%20(Spencer)/banziGettingStartedArduino.md), debouncing can be as simple as comparing the read value with the previous value and waiting 10ms before writing it e.g. 

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
