---
alias: ["pull-up resistor", "pullup resistor", "pull-up resistors", "pullup resistors"]
---
parent::[Arduino Pin Considerations](Arduino%20Pin%20Considerations.md)
next::[Sources and Sinks](Sources%20and%20Sinks.md)

Digital pins set as inputs are in a high impedance state. A small change in current will cause a large change in voltage at the input. 

When using a digital pin as an input (e.g. to detect the state of a pushbutton), we need to force the pin to normally HIGH or LOW -- otherwise the pin will be in an indeterminate state and susceptible to noise.

We do this through a pull-up or pull-down resistor. Pull-up resistors connect the pin HIGH or to 5V for the Arduino, whereas Pull-down resistors connect the pin normally LOW or to 0V. 

The Arduino AVR microprocessor has an internal pull-up resistor that can be enabled in code as `pinMode(INPUT_PULLUP)` (and is actually enabled when the pin is used as an output, to limit short circuits, see below). This activates the internal resistor (typ. 20K-50K) that allows us to not use an external resistor, but at the cost of **inverting the logic** (e.g. the input will now be normally `HIGH`)

![Pasted image 20221104114045](attachments/Pasted%20image%2020221104114045.png)

> [!CAUTION]+ Using `INPUT_PULLUP` and Pushbuttons
> There is a cost of saving an external resistor -- the logic is inverted.
> 
> `HIGH` is now "unpressed" and `LOW` is "pressed"
> 
> We must now wire the pushbutton to ground, and when pressed it pulls the input pin to ground (remember it is a high impedance input and can easily be pulled to ground). Also it is good to use a 10K resistor - since we don't need much current to change the voltage of the pin.

> [!NOTE]+ An INPUT_PULLUP Pin Changed to an Output Yields `HIGH`
> The pullup resistors are controlled by the same registers (internal chip memory locations) that control whether a pin is `HIGH` or `LOW`. Consequently, a pin that is configured to have pullup resistors turned on when the pin is an `INPUT`, will have the pin configured as `HIGH` if the pin is then switched to an `OUTPUT` with `pinMode()`. This works in the other direction as well, and an output pin that is left in a HIGH state will have the pullup resistors set if switched to an input with `pinMode()`.
>
> Source: https://docs.arduino.cc/learn/microcontrollers/digital-pins

> [!CAUTION] Don't use the `INPUT_PULLUP` on Pin 13
> If you enable pin 13's internal 20k pull-up resistor, it will hang at around 1.7V instead of the expected 5V because the onboard LED and series resistor pull the voltage level down, meaning it always returns `LOW`. If you must use pin 13 as a digital input, set its `pinMode()` to `INPUT` and use an external pull down resistor.
> 
> Source: https://docs.arduino.cc/learn/microcontrollers/digital-pins