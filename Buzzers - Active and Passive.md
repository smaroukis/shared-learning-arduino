parent::[Actuators and Sensors](Actuators%20and%20Sensors.md)

Summary
- There are different types of buzzers (also called transducers), based on construction (magnetic vs. piezo), and whether they include an oscillator drive circuit (passive vs. active). They function on the same fundamental property of using a AC electrical input to vibrate the air and produce sound of a certain frequency. 
- Note that _frequency_ modulation is employed and not _amplitude_ modulation as in [Arduino - PWM](Arduino%20-%20PWM.md) - as amplitude modulation will just change the loudness of the buzzer, not the tone.
- We can simply apply the correct voltage 

**Piezo**
- The piezoelectric effect is when a material deforms in the presence of an electric charge. A piezo buzzer is a thin disc of piezoelectric ceramic adhered to a metal plate, which vibrates when an AC signal is applied.

**Electromagnetic/Magnetic**
- A varying electric charge produces a magnetic field which causes a metal disc to vibrate. A coil of wire is inside a magnet in the buzzer, when an AC current is applied it creates a magnetic field that moves the metal disc. (note there may be circuitry allowing a DC signal to be applied to the buzzer pins)

### Electromagnetic Buzzers

Active vs Passive
![Pasted image 20221007132507](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221007132507.png)
- both are _polarized_

Active Buzzer
- can be driven with DC 
- has built in oscillator circuit 
- can't control the pitch (since we are not controlling the oscillator circuit)
- for [Arduino](Arduino.md) - use just like an LED e.g. `digitalWrite(PIN, HIGH)`
- 


Passive Buzzer
- must be driven by a square wave of frequency 2K-5K (but see datasheet)
- green PCB may be visible
- we can control the pitch since we set the square wave ourselves
- (!) don't drive the passive buzzer with `analogWrite()`, instead use the built in `tone()` /`noTone()` functions

> If you want to play different pitches on multiple pins, you need to call `noTone()` on one pin before calling `tone()` on the next pin.

Theory of operation
- a weighted metal film is vibrated at a certain frequency to produce a sound 
- a magnetic field is created by applying current to a coil.


![Pasted image 20221007132552](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221007132552.png)

**Further** - see [Example Circuits - Buzzers](Example%20Circuits%20-%20Buzzers.md)
- a piezo buzzer is driven by a voltage - we can model it as a capacitor. sometimes we use a reset resistor to discharge it when the switch connecting it is open
- a magnetic buzzer is driven by a current - we can model as an inductor (in series with a resistor). no resistor is needed

## Resources
- https://www.circuitbasics.com/how-to-use-active-and-passive-buzzers-on-the-arduino/
- https://www.avrfreaks.net/forum/buzzer-module-gets-warm-and-wastes-power - for modules, check which type of transistor (NPN or PNP) it is using
- https://www.americanpiezo.com/blog/piezo-buzzers-vs-magnetic-buzzers/#:~:text=Generally%20speaking%2C%20piezo%20buzzers%20tend,usable%20frequencies%20than%20magnetic%20buzzers.
- https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody 
- https://www.cuidevices.com/blog/buzzer-basics-technologies-tones-and-driving-circuits - drive signal vs output for piezo vs magnetic buzzers