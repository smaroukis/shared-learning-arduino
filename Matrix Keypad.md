parent::[Arduino Peripherals](Arduino%20Peripherals.md)


Operating Principle
- we can access the "state" of any button by creating a path from 5V to ground through the button
- we need one output (to supply voltage or ground) and one input (to sense - it will be the "other end" of the circuit)
- we loop over columns and rows (nested), checking each pin to see if it is pressed



The buttons are connected in rows and columns:
- columns:  pins 1-4
- rows: pins 5-8

![](Pasted%20image%2020221010232424.png)

![](Pasted%20image%2020221010232802.png)


**Example**

For example, here we are checking the button in Row 2, Column 2. If we measure `LOW` at the input, then we know the button is pressed, otherwise it is being pulled up to 5V as defined (i.e `pinMode(1, INPUT_PULLUP)`). We use a pull-up resistor on the input here so we can be sure of the state (and not require an external pull-down resistor). 

![](Pasted%20image%2020221010234949.png)