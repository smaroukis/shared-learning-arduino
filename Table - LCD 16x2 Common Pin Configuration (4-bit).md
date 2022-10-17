#table 
source: [1] https://docs.wokwi.com/parts/wokwi-lcd1602

| Name | Description | Arduino Pin\* |
| --- | --- | --- |
| VSS | Ground | GND.1 |
| VDD | Supply voltage | 5V |
| V0 | Contrast adjustment (not simulated) |  |
| RS | Command/Data select | 12 |
| RW | Read/Write. Connect to Ground. | GND.1 |
| E | Enable | 11 |
| D0 | Parallel data 0 (optional) † |  |
| D1 | Parallel data 1 (optional) † |  |
| D2 | Parallel data 2 (optional) † |  |
| D3 | Parallel data 3 (optional) † |  |
| D4 | Parallel data 4 | 10 |
| D5 | Parallel data 5 | 9 |
| D6 | Parallel data 6 | 8 |
| D7 | Parallel data 7 | 7 |
| A | Backlight anode | 5V / 6‡ |
| K | Backlight cathode | GND.1 |

\* These are just example pin numbers, they are not mandatory. You need can use any digital/analog pin, but make sure to update the code accordingly!  
† Normally, you'd configure the chip in 4-bit parallel mode, which means you only need to connect RS, E, D4, D5, D6, and D7 pins to Arduino.  
‡ If you need to control the backlight, connect the anode to an I/O pin. Otherwise, connect it to the supply voltage. For a real circuit, you'd also need a current-limiting resistor, but you may skip it in the simulation environment.
