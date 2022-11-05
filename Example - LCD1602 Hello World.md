garden-topic::[[LCDs]]

LCD1602 refers to the common 16x2 LCD display which has 16 columns and 2 rows (typ. using the [HD44780 LCD Controller](https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller) by Hitachi.

> [!note]- Pin Descriptions 
> - `VSS:` A pin that connects to ground  
> - `VDD`: A pin that connects to a +5V power supply  
> - `VO`: A pin that adjust the contrast of LCD1602  
> - `RS`: A register select pin that controls where in the LCD’s memory you are writing data to. You can select either the data register, which holds what goes on the screen, or an instruction register, which is where the LCD’s controller looks for instructions on what to do next.
> - `R/W`: A Read/Write pin that selects reading mode or writing mode  
> - `E`: An enabling pin that, when supplied with low-level energy, causes the LDC module to execute relevant instructions.  
> - `D0-D7`:Pins that read and write data  
> - `A`: LED backlight anode (typ. connect to potentiometer or resistor)
> - `K`: LED backlight cathode (typ. -> GND)

Note if you print without clearing or resetting cursor it will just append the data.

> [!note]- Schematic: 16x2 LCD with HD44780 Driver in 4-bit Mode
> ![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221017115858.png]]

Note rows are labeled as COLS, ROWS and are 0-indexed:

> [!CAUTION] Route to the correct [[SPI]] pins on the Arduino side as required

> [!EXAMPLE]- Example Pin Configuration for LCD in 4-Bit Mode
> ![[Table - LCD 16x2 Common Pin Configuration (4-bit)]]

### Code

```c
// http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
```



