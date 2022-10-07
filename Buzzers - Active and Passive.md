parent::[Electronic Components](Electronic%20Components.md)
garden-topic::[tmi07 Buzzers](Personal%20Folders/that_marouk_ish/code/tmi07%20Buzzers.md)

Summary
- 

**Piezo**
- The piezoelectric effect is when a material deforms in the presence of an electric charge. A piezo buzzer is a thin disc of piezoelectric ceramic adhered to a metal plate, which vibrates when an AC signal is applied.

**Electromagnetic/Magnetic**
- A varying electric charge produces a magnetic field which causes a metal disc to vibrate. A coil of wire is inside a magnet in the buzzer, when an AC current is applied it creates a magnetic field that moves the metal disc. (note there may be circuitry allowing a DC signal to be applied to the buzzer pins)

### Electromagnetic Buzzers

Active vs Passive
![](Pasted%20image%2020221007132507.png)
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


![](Pasted%20image%2020221007132552.png)



## Resources
- https://www.circuitbasics.com/how-to-use-active-and-passive-buzzers-on-the-arduino/
- https://www.avrfreaks.net/forum/buzzer-module-gets-warm-and-wastes-power - for modules, check which type of transistor (NPN or PNP) it is using
- https://www.americanpiezo.com/blog/piezo-buzzers-vs-magnetic-buzzers/#:~:text=Generally%20speaking%2C%20piezo%20buzzers%20tend,usable%20frequencies%20than%20magnetic%20buzzers.
- https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody