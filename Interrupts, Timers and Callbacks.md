parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
previous::[Multitasking and non blocking delays](Multitasking%20and%20non%20blocking%20delays.md)
level:: #intermediate 

### Interrupts

> **Interrupts** should really only be used for very high frequency events - not button presses. Button presses are examples of "doing something different".

Reasons to use interrupts:
- To detect pin changes (eg. rotary encoders, button presses)
- Watchdog timer (eg. if nothing happens after 8 seconds, interrupt me)
- Timer interrupts - used for comparing/overflowing timers
- SPI data transfers
- I2C data transfers
- USART data transfers
- ADC conversions (analog to digital)
- EEPROM ready for use
- Flash memory ready

### Callbacks

With some libraries we can use callbacks, for example when using an Arduino as a Secondary in a [I2C](I2C.md) communication scheme. The Arduino needs to be able to respond to the Main when requested.

See [Example - Langbridge I2C Arduino as Secondary](Example%20-%20Langbridge%20I2C%20Arduino%20as%20Secondary.md)

**Resources**
https://forum.arduino.cc/t/beginners-interrupts-why-when-and-how/518636
http://www.gammon.com.au/forum/?id=11488 - rec from `Robin2` on arduino forum as good interrupt 