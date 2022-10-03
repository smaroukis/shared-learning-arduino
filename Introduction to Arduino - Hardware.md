parent::[[Arduino]]
next::[[Intro to Arduino - Software]]
status:: #draft-outline

Outline
- Microcontroller vs microprocessor vs arduino
	- [[Arduino Comparison]]
- ATMEL ATMEGA AVR microcontroller(now Microchip)
- Resonator - Crystals and Oscillator
- Mega8U2 microcontroller handles uploading the code to the AVR microcontroller
- Power - purely from USB, or dedicated power plug barrel jack 9V
	- aside: power for microcontrollers
	- uno has voltage regulator to reduce to 5V
- Reset button reboots the uploaded program
- aside: arduino schematic walkthrough
- Pins
	- Power
		- 2 grounds, 3.3Vout, 5Vout, Vin - make sure the power draw is below ~30mA 
			- aside: link to power draw req's
	- Serial (TX/RX)
		- TX pin sends data
		- RX pin receives data
		- ➡️ [[Serial Communication]]
	- 2-13: Digital I/O
		- Digital Output: Output is two states - High (=1) or Low (=0)
			- in reality these are analog voltages that the receiving device can recognize as a 1 or 0
		- Digital Input: You have to define what your "high" voltage reference level is, but then you can use these pins as digital input
		- Tilder `~`: PWM output (note more powerful arduinos have an converter that can provide _actual_ analog voltages, instead of PWM square waves oscillating between two High and Low states)
		- ➡️ [[Tri-State Logic]]
	- Analog input


## Resources
- [Afrotechmods 15minute intro video](https://www.youtube.com/watch?v=nL34zDTPkcs)
