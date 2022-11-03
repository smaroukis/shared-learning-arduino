parent::[[Introduction to Arduino - Hardware]]
also see:: [[Arduino Functions]]

For specific board pinouts see
- [[Mega2560]]
- [[Uno]]

### Overview

All pins can be used as digital input or output (see tri state logic), with a sink and source limit of 40mA (although this is the maximum, so it is better to run lower, at 20mA or less). 

Some digital pins can output a PWM signal, which is a quasi-analog output. Note this output value is defined between 0 and 255. To get an actual analog output voltage an RC filter is needed. 

Pins defined as "Analog" mean they can read an **analog** **input** and store it as a value between 0 and 1023.

### **Digital vs Analog**

- **Digital** pins can write and read only `HIGH` or `LOW`
	- `HIGH` is 5V, `LOW` is 0V
	- for [[Arduino - PWM]] they can _output_ a quasi-analog voltage by cycling between HIGH and LOW for a fixed duty cycle
- **Analog** pins can directly read analog voltages (as inputs)
	- `analogRead()` returns a value between 0 and 255
	- most analog pins can also function as digital pins (either input or output)
	- these Anlaog pins are _not_ analog output pins, for an analog output use the digital PWM capable pins with an RC filter.
- **PWM-capable**
	- `analogWrite()`: accepts value between 0 and 255

### Output vs Input

**Output** pins can drive LEDs, etc. As an output the pin is in a low impedance state - thus they can provide, or source, a lot of current (well up to 40mA).
- low impedance means z=dv/di is small, so a change in current results in barely any change in voltage (an ideal source has no voltage change no matter what the current draw)
	
> [!CAUTION] Generally we want to connect a 470 or 1K resistor in series with a pin to limit the current to <20mA (esp. for LEDs)

**Input** pins are in a high impedance state (available to _sink_ current _in_ to the pin)
- we can easily change these by driving them with 5V or 0V (`digitalWrite()`)
- equivalent of a 10MOhm resistor in series with the pin
- since high impedance means z=dv/di  is large, any change in current will also easily change the voltage (z is fixed)
- it's recommended to use a pull-up or pull-down resistor so they don't "float" and give indeterminate behavior :➡️ we can use a resistor internal to the microprocessor by setting `pinMode(INPUT_PULLUP)`, see  [[Pullup Resistors]]

### Other Considerations and Special Pins

**Numbering**
- digital pins with `D` prefixes can be referenced just as the number (e.g. `D7` can be referenced in code as pin `7`).
- analog pins can be referenced with the `A<Number>` or the full pin number (e.g. pin `A0` can be called with `A0` or `54`)

**Communications** ➡️ see [[Serial Communication]]
- pins 0 and 1 are used for communicating with the computer - avoid connecting peripherals when using for example the Serial Monitor

**Internal LED is connected to Pin 13**
- Don't use digital pin 13 as an input due to the internal LED attached, see more in [[Pullup Resistors]]

**Further**
- Timers are internally connected to some pins - PWM can be limited because of this, see [[Interrupts and Timers]]