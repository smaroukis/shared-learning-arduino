parent::[[Arduino Software Concepts]]
previous::[[Multitasking and non blocking delays]]
level:: #intermediate 

#tdf include code examples, also callbacks

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

**Resources**
https://forum.arduino.cc/t/beginners-interrupts-why-when-and-how/518636
http://www.gammon.com.au/forum/?id=11488 - rec from `Robin2` on arduino forum as good interrupt 