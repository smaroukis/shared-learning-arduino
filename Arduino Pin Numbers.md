parent::[[Introduction to Arduino - Hardware]]
also see:: [[Arduino Functions]]

For specific board pinouts see
- [[Mega2560]]

### General
**Digital vs Analog**
- **digital** pins can write and read only `HIGH` or `LOW`
	- `HIGH` is 5V, `LOW` is 0V
	- for [[Arduino - PWM]] they can _output_ a quasi-analog voltage by cycling between HIGH and LOW for a fixed duty cycle (PWM capable pins are prefixed with a _tilde_)
	- they cannot read an analog voltage
- **analog** pins can directly read analog voltages (as inputs)
	- `analogRead()`
	- most analog pins can also function as digital pins (either input or output)
	- (!) "analog" refers to as an **input only**; these "analog" pins _cannot_ output a quasi-analog PWM wave
- **PWM-capable**
	- `analogWrite()`: accepts value between 0 and 255

**Output vs Input**
- output pins can drive LEDs, etc
	- low impedance state - thus they can provide a lot of current (well up to 40mA)
	- (!) generally we want to connect a 470 or 1K resistor in series with the pin to limit the current to <20mA. 
- **input** pins are in a high impedance state
	- we can easily change these by driving them with 5V or 0V (`digitalWrite()`)
	- it's recommended to use a pull-up or pull-down resistor so they don't "float" and give indeterminate behavior

**Numbering**
- digital pins with `D` prefixes can be referenced just as the number (e.g. `D7` can be referenced in code as pin `7`).
- analog pins can be referenced with the `A<Number>` or as above (e.g. pin `A0` can be called with `A0` or `54`)

**Communications** ➡️ see [[Serial Communication]]
- pins 0 and 1 are used for communicating with the computer - avoid connecting peripherals

**Further**
- INPUT_PULLUP activates an internal pullup resistor (either 20K or 50K)
- Don't use digital pin 13 as an input due to the internal LED attached (it affects the (voltage [[source](https://docs.arduino.cc/learn/microcontrollers/digital-pins)]
