parent::[James A. Langbridge - Arduino Sketches](James%20A.%20Langbridge%20-%20Arduino%20Sketches.md)
garden-topic::[SPI](SPI.md), [Bitwise Operations](Bitwise%20Operations.md)

> Source:: [James A. Langbridge - Arduino Sketches](James%20A.%20Langbridge%20-%20Arduino%20Sketches.md)

Hardware
- [MAX31855 thermocouple](MAX31855%20thermocouple.md)
- Arduino [Due](Due.md) (3.3V)

> [!NOTE]- Hardware Layout
> 
> ![Pasted image 20221105132150](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221105132150.png)

After taking a look at the datasheet of the [MAX31855 thermocouple](MAX31855%20thermocouple.md) we can see what data it gives back on the SPI bus. It is a 32 bit package, with the first 16 bits (D31 to D18) as the temperature data and the second 16 bits (D15 to D0) as an error or fault status if applicable.

We read the data in 8 bits at a time with `SPI.transfer()`, then combine the data into to 16-bit variables with `word()`. 

We check the second 16-bit value for an error message, and display that if it exists.

Otherwise we convert it to celsius and print that out.

```cpp
#include <SPI.h>

const int secondarySelectPin = 10;

void setup()
{
	Serial.begin(9600);
	
	// Initialize the bus for a device on pin 10
	SPI.begin(secondarySelectPin);
}

void loop()
{
	// Read in 4 bytes of data
	// calling SPI.transfer() will pull the secondary select pin low to transfer **8 bits** of data
	// the MAX31855 will wait for a valid clock to write 32 bits to the Main
	// each 
	//  SPI_CONTINUE keeps the select pin low so we can keep writing data
	byte data1 = SPI.transfer(secondarySelectPin, 0, SPI_CONTINUE);
	byte data2 = SPI.transfer(secondarySelectPin, 0, SPI_CONTINUE);
	byte data3 = SPI.transfer(secondarySelectPin, 0, SPI_CONTINUE);
	byte data4 = SPI.transfer(secondarySelectPin, 0, SPI_LAST); // Stop
	
	// Create two 16-bit variables
	word temp1 = word(data1, data2); // word(<higest order>, <lowest order>)
	word temp2 = word(data3, data4);
		// temp1 is the first 16-bits which is the essential information
		// temp 2 is now the second 16-bits which is the error data
	
	// Is the reading negative?
	bool neg = false;
	if (temp1 & 0x8000) // 0b1000000000000000
	{
		neg = true;
	}
	
	// Is the MAX31855 reporting an error?
	if (temp1 & 0x1) // this is the fault status bit
	{
	// temp2 stores the error data
	  Serial.println("Thermocouple error!");
	  if (temp2 & 0x1) // 0b0001 i.e D0 is 1 -> OC Fault
		Serial.println("Open circuit");
	  if (temp2 & 0x2) // 0b0010 i.e. D1 is 1 -> SGC Fault
		Serial.println("GND Short");
	  if (temp2 & 0x4) // 0b0100 i.e. D2 is 1 -> SCV Fault
		Serial.println("VCC short");
	}
	
	// Keep only the bits that interest us
	temp1 &= 0x7FFC; // 0b111111111111100 this is D[31:18], the last two bits can be discarded (well, here they are just replaced with zeros)
	
	// Shift the data
	temp1 >>= 2;
	
	// Create a celcius variable, the value of the thermocouple temp
	double celsius = temp1;
	
	// The thermocouple returns values in 0.25 degrees celsius
	celsius *= 0.25;
	if (neg == true) celsius *= -1;
	
	// Now print out the data
	Serial.print("Temperature: ");
	Serial.print(celsius);
	Serial.println();
	
	// Sleep for two seconds
	delay(2000);
}
```
