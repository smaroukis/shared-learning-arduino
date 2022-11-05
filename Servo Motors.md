parent::[Motors](Motors.md)

> Motors, even small servos, can draw a lot of current, so for more than 2 servos you'll need a separate power supply. Always check the datasheet.

**Pinout**
3 pins - Power, Ground, and Signal
- Power: typ red ➡️ 5V
- Ground: typ. brown or black ➡️ GND
- Signal: typ. yellow, orange, white ➡️ PWM Digital Pin 

Usually a delay is included because we don't have a feedback wire to make sure the servo has moved:

> Adding fixed-time delays to servo code works OK for simple applications, but can result in slow and/or jerky performance when trying to coordinate multiple servo motions or interactions between servos and other sensors or actuators. [2]

## References
[1] https://www.arduino.cc/reference/en/libraries/servo/
[2] https://learn.adafruit.com/analog-feedback-servos/using-feedback