parent::[Electronic Components](Electronic%20Components.md)
garden-topic::

Summary

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


Theory of operation
- a weighted metal film is vibrated at a certain frequency to produce a sound 
- a magnetic field is created by applying current to a cil 


![](Pasted%20image%2020221007132552.png)



## Resources
- https://www.circuitbasics.com/how-to-use-active-and-passive-buzzers-on-the-arduino/
- 