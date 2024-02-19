
> Even though the HIGH and LOW pins are connected to 5V and ground, respectively, there is really about 40 ohms of resistance in each pin path. This means when you plug a red LED between these two pins, the 80 ohm resistance in the output transistors of the pins themselves will limit the current. With a 2V drop across the LED, the voltage across the internal resistance is about 3V. This means the current will be about 3V/80 ohms = 38 mA

Check the datasheet, but I think the arduino pin source current can go up to 40mA

Note that you would only want to power one LED like this, and limit any other load to near 0, as the max current is usually for a set of pins together, not any one individual pin.

See also [[Resistor Calculation for LEDs]]

Source
https://www.nutsvolts.com/magazine/article/build-an-instant-heart-pulse-sensor