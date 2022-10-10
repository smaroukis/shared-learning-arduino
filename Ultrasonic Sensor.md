parent::[Arduino Sensors](Arduino%20Sensors.md), [Electronic Components](Electronic%20Components.md)

The speed of sound in air at 20C is 343 m/s or 0.0343 cm/us.

 The HC-SR04 is a popular low-cost ultrasonic sensor with various libraries.
- a trigger pulse (HIGH) is sent to the module 
	- on the `TRIG` pin
- the module sends a pulse out and detects whether it gets a pulse back
- the module responds with a echo pulse to the user (arduino) circuit
	- on the `ECHO` pin
	- the pulse duration is in proportion to the distance away

Libraries: 
- NewPing

## Resources
- HC-SR04 datasheet ([sparkfun](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf))