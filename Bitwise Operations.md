parent::[Other Software and Computer Concepts](Other%20Software%20and%20Computer%20Concepts.md)

Bitwise operators can be used in many contexts and can be quicker since we are just comparing underlying bits instead of storing numbers as ints, longs etc.

`&` as an alternate to an equal sign to check hex values
- `temp1 & 0x8000` returns true for negative values since for a `int` the MSB is 1 for negative values (`0x8000` == `0b1000000000000000`)

Examples
- [Example - Langbridge SPI Thermocouple](Example%20-%20Langbridge%20SPI%20Thermocouple.md)