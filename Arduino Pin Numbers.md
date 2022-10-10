parent::[Introduction to Arduino - Hardware](Introduction%20to%20Arduino%20-%20Hardware.md)

### General
**Digital vs Analog**
- **digital** pins can write and read only `HIGH` or `LOW`
	- `HIGH` is 5V, `LOW` is 0V
	- for [Arduino - PWM](Arduino%20-%20PWM.md) they can _output_ a quasi-analog voltage by cycling between HIGH and LOW for a fixed duty cycle (PWM capable pins are prefixed with a _tilde_)
	- they cannot read an analog voltage
- **analog** pins can directly read analog voltages

**Numbering**
- digital pins with `D` prefixes can be referenced just as the number (e.g. `D7` can be referenced in code as pin `7`).
- analog pins can be referenced with the `A<Number>` or as above (e.g. pin `A0` can be called with `A0` or `54`)


### [Mega2560](Mega2560.md)
- General Purpose Digital Pins
	- `2` to `13`
- RX/TX
	- `0` and `1` are used for `RXO` and `TXO` respectively - also used by the Serial Montior ? #q 
	- 
	- 
