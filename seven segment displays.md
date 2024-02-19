

Common Anode - pull down to drive; Common Cathode - pull up to drive
![[Pasted image 20230821161422.png]]
> Note GND and VCC are switched depending on CA vs CC

> [!TIP] Don't forget to include resistors, unless they are included in a driver

Multiplexed
![[Screenshot 2023-08-21 at 4.10.28 PM.png]]
> Common Cathode display digit can be strobed by gating the common connection with an NPN 

Multiplexing: 4 displays requires 8 + 4 = 12 pins, generally pins are 8 + N Digits
$P = 8 + N$

Multiplexing algorithm: 
- Strobe display / digit 1: 
	- provide a-e segment control lines (8 if including decimal)
	- for common cathode, provide power to Q1 base, connecting the common cathode to ground, lighting up the segments previously provided
	- take away power from the base and continue to the next
- Strobe display digit 2
	- provide new a-e sements
	- drive Q2, all other transistors bases to ground
- Etc.

> Note that we can run at a higher current than normal since we are at a 25% duty cycle for each display


==Control pins can be further reduced with drivers==
- Typically driven with a driver such as the 4511 BCD to 7 segment, so only 4 control pins are required (2^4 = 16 and we only need to go to 9)
- jmax7219 - serial interfaced 8 *digit* led driver, reqs only three pins from the mcu (MOSI, SCI, I/O)
- alternatively use a shift register 74HC595


## Refs
- http://lednique.com/display-technology/7-segment-display-basics/
- has some multipliex implementation code https://www.youtube.com/watch?v=E9lUH5dT6Xc
- ++