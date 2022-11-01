parent::[[Resistors]], [[LEDs]]

220Ohm (red-red-brown) are common for LEDs since they limit the current from a 5V supply to around 15mA.

Limiting the load on a pin to 20mA: assuming worst case (lowest forward voltage) of 1.8V across an LED when on, with a 5V input leaves 3.2V across a resistor. The 220Ohm resistor limits this to I=3.3V/220=15mA. 

#TODO #img 

**Further**: 
- 