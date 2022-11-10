parent::[Introduction to Arduino - Hardware](Introduction%20to%20Arduino%20-%20Hardware.md)
previous::[Arduino Pin Considerations](Arduino%20Pin%20Considerations.md)

For a pin acting as a **source**, current will flow **out** of the pin, whereas for a pin acting as a **sink**, current will flow **in** to the pin.

> [!CAUTION] "Source" or "Sink" does not correspond to the pin functioning as an Input or an Output. Below the pin is an **output** in each case.

The following diagram shows the two ways to power an LED using digital outputs.

![Pasted image 20221104111436](attachments/Pasted%20image%2020221104111436.png)

**Source**
- the LED is connected between the IO pin and ground
- normally the IO pin is `LOW` and the Led is off
- when we tell the IO pin to go `HIGH`, it sets the pin to 5V in a low impedance state, and current flows from the IO pin to Ground, thus we say the IO pin "sources" current

**Sink**
- the LED is connected between 5V and the IO pin (note direction - the LED now points **into** the IO pin)
- normally we set the IO pin `HIGH` so the LED is Off
- when we tell the IO pin to go `LOW`, it sets the pin to 0V in a low impedance state, and current flows from the 5V pin **into** the IO Pin, thus we say the IO pin "sinks" current

> [!CAUTION] Some pins can source and sink different amount of currents (usually a pin can source more current than it can sink). For the Arduino it is a maximum of 40mA in both directions.