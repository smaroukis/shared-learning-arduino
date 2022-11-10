parent::[Actuators and Sensors](Actuators%20and%20Sensors.md)

> [!NOTE]- Data Output
> ![Pasted image 20221105132319](attachments/Pasted%20image%2020221105132319.png)

> The data is delivered in a 32-bit package, but there is something interesting about the layout. It can be seen as two 16-bit values: bits D31 to D16 and D15 to D0. The first 16-bits contains everything that is essential: the temperature detected on the thermocouple and a fault bit. If there is a fault, or if the user wants to know the cold-junction temperature, then the second 16-bit value can be read, but otherwise, it is not required. ([James A. Langbridge - Arduino Sketches](James%20A.%20Langbridge%20-%20Arduino%20Sketches.md))