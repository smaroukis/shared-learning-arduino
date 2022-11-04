parent::[[Arduino]]
next::[[Intro to Arduino - Software]]

#refactor  with tables and links to [[Arduino Boards]]

#inbox/writing 

[[word size]] is 16 bits (2 bytes)\

1. [[Arduino Pin Considerations]]
2. [[Sources and Sinks]]
3. 

Outline
- Microcontroller vs microprocessor vs arduino
- ATMEL ATMEGA AVR microcontroller(now Microchip)
- [[Resonators]] - Crystals and Oscillator
- Mega16U2 microcontroller handles uploading the code to the AVR microcontroller --> note you can even [[Update the 16U2 Firmware]]
- Power - purely from USB, or dedicated power plug barrel jack 9V (2.1mm tip, center positive) 
	- uno has voltage regulator to reduce to 5V
- Reset button reboots the uploaded program
- Pins
	- Power
		- 2 grounds, 3.3Vout, 5Vout, Vin - make sure the power draw is below ~30mA (see [[Resistor Calculation for LEDs]])
		- Vin is for voltage between 7-12V for use by e.g. motors
	- Serial (TX/RX)
		- TX pin sends data
		- RX pin receives data
		- ➡️ [[Serial Communication]]
	- 2-13: Digital I/O
		- Digital Output: Output is two states - High (=1) or Low (=0)
			- in reality these are analog voltages that the receiving device can recognize as a 1 or 0
			- [[Sources and Sinks]]
		- Digital Input: You have to define what your "high" voltage reference level is, but then you can use these pins as digital input
		- Tilde `~`: PWM output -> the PWM output is not a real analog output, to get a real analog output you need an [[RC Filter]] to achieve a DC voltage
	- Analog input


## Resources
- [Afrotechmods 15minute intro video](https://www.youtube.com/watch?v=nL34zDTPkcs)
- https://learn.adafruit.com/arduino-tips-tricks-and-techniques
