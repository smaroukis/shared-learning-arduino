parent::[Buzzers - Active and Passive](Buzzers%20-%20Active%20and%20Passive.md)

There is a polarity to the buzzer due to the designed for magnetic field interactions with the metal plate (the buzzer will still make a sound if reversed, but it could be the incorrect sound). 

A **magnetic buzzer** (transconductor) **does not need a resistor**, It is modeled just as an inductor. Usually a [flyback diode](flyback%20diode.md) will be placed at the buzzer terminals when it is driven by a transistor to avoid voltage spikes due to the inductor resisting change in current

A **piezo buzzer** will have a resistor to "bleed" it when the switch opens.

The current defined in the datasheet is the **average consumption current** when rated voltage is applied. Note that we should allow for 3x this current to allow for this as peak current. 




_Figure: Flyback diode placed across the terminals of an inductive magnetic buzzer_ ![](Pasted%20image%2020221007225401.png)

## References
- https://www.allaboutcircuits.com/industry-articles/an-overview-of-driver-circuits-for-piezo-transducer-buzzers/ - for driving circuits
	- https://www.flezon.com/wp-content/uploads/2018/04/Magnetic-Transducer-Technical-Information.pdf - whitepaper, technical details on both piezo and magnetic, external resonators