parent::[Actuators and Sensors](Actuators%20and%20Sensors.md)


**Operating Principle**
- we can access the "state" of any button by creating a path from 5V to ground through the button
- we need one output (to supply voltage or ground) and one input (to sense - it will be the "other end" of the circuit)
- we loop over columns and rows (nested), checking each pin to see if it is pressed

**Notes**
- use a `INPUT_PULLUP` type for the row and set the output column to `LOW`,  then we check to see if this input pin is pulled low to see if the button is pressed (see example below).

**Example**:
For example, here we are checking the button in Row 2, Column 2. If we measure `LOW` at the input, then we know the button is pressed, otherwise it is being pulled up to 5V as defined (i.e `pinMode(1, INPUT_PULLUP)`). We use a [pull-up resistor ](pull-up%20resistor%20.md)on the input here so we can be sure of the state (and not require an external pull-down resistor). 

![Pasted image 20221010234949](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221010234949.png)

For a common membrane keypad the buttons are connected in rows and columns:
- columns:  pins 1-4
- rows: pins 5-8

![Pasted image 20221010232424](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221010232424.png)

![Pasted image 20221010232802](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221010232802.png)



## Resources
- https://www.baldengineer.com/arduino-keyboard-matrix-tutorial.html
- 