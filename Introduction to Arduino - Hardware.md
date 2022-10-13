parent::[[Arduino]]
next::[[Intro to Arduino - Software]]
status:: #draft


Outline
- Microcontroller vs microprocessor vs arduino
	- [[Arduino Comparison]]
- ATMEL ATMEGA AVR microcontroller(now Microchip)
- [Resonators](Resonators.md) - Crystals and Oscillator
- Mega8U2 microcontroller handles uploading the code to the AVR microcontroller
- Power - purely from USB, or dedicated power plug barrel jack 9V (2.1mm tip, center positive) (ref. [Power Components](Power%20Components.md)) 
	- uno has voltage regulator to reduce to 5V
- Reset button reboots the uploaded program
- Pins
	- Power
		- 2 grounds, 3.3Vout, 5Vout, Vin - make sure the power draw is below ~30mA (see [Resistor Calculation for LEDs](Resistor%20Calculation%20for%20LEDs.md))
		- Vin is for voltage between 7-12V for use by e.g. motors
	- Serial (TX/RX)
		- TX pin sends data
		- RX pin receives data
		- ➡️ [[Serial Communication]]
	- 2-13: Digital I/O
		- Digital Output: Output is two states - High (=1) or Low (=0)
			- in reality these are analog voltages that the receiving device can recognize as a 1 or 0
		- Digital Input: You have to define what your "high" voltage reference level is, but then you can use these pins as digital input
		- Tilde `~`: PWM output -> #q can Arduinos actually output real DC voltages or do they always just require an [RC Filters](RC%20Filters.md) to achieve a DC voltage
		- ➡️ [[Tri-State Logic]]
	- Analog input


## Resources
- [Afrotechmods 15minute intro video](https://www.youtube.com/watch?v=nL34zDTPkcs)
- https://learn.adafruit.com/arduino-tips-tricks-and-techniques
